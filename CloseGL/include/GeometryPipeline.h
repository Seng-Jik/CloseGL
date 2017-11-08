#pragma once
#include "GeometryDataFormat.h"
#include "GeometryPass.h"
#include <memory>
#include <thread>
#include <algorithm>

namespace CloseGL::Geometry
{

	struct GeometryPipelineOutput
	{
		struct ThreadOut
		{
			std::vector<float> VertexData;
			std::vector<bool> StripData;
		};
		std::vector<ThreadOut> Outputs;
		GeometryDataFormat Format;
	};

	template<int VertexPerPrimitive = 4>	//TData = double/float
	class GeometryPipeline
	{
	public:

		GeometryPipeline(GeometryDataFormat format);

		//		Warning£ºIf you want to modify strip data in geometry pass, and it may push a striping vertex as a head of vertex buffer,you must 
		//set child threads to 0 to make no striping vertex as head of thread output set.
		void SetChildThreads(unsigned childThreads);	
		GeometryPipelineOutput Process(std::vector<float>& inputData, std::vector<bool>& stripData, bool clearAfterProcess = false) const;
		GeometryPipelineOutput Process(const std::vector<float>& inputData, const std::vector<bool>& stripData) const;
		//If not readonly,this vector maybe destroyed.

		void AddPass(const std::shared_ptr<const GeometryPass<VertexPerPrimitive>>& pass);
		void ClearPass();
	private:
		static void processThread(bool singleThreadAndInputDestroyable, const std::vector<std::shared_ptr<const GeometryPass<VertexPerPrimitive>>>& passes,const GeometryDataFormat& format, std::vector<float>& inputData,size_t primitiveBegin,size_t primitiveCount, GeometryPipelineOutput::ThreadOut* outputData, std::vector<bool>& stripData);
		std::vector<std::shared_ptr<const GeometryPass<VertexPerPrimitive>>> passes_;
		GeometryDataFormat format_;
		unsigned childThreads_ = 0;
	};


	template<int VertexPerPrimitive>
	inline GeometryPipeline<VertexPerPrimitive>::GeometryPipeline(GeometryDataFormat format):
		format_(format)
	{
	}

	template<int VertexPerPrimitive>
	inline void GeometryPipeline<VertexPerPrimitive>::SetChildThreads(unsigned childThreads)
	{
		childThreads_ = childThreads;
	}


	template<int VertexPerPrimitive>
	inline GeometryPipelineOutput GeometryPipeline<VertexPerPrimitive>::Process(std::vector<float>& inputData, std::vector<bool>& stripData, bool clearAfterProcess) const
	{
		const size_t primitiveCount = (inputData.size() / format_.ElementCount) / VertexPerPrimitive;
		const auto childThreads = primitiveCount  < childThreads_ ? 0 : childThreads_;
		const size_t primitiveCountEveryThread = primitiveCount / (childThreads + 1);


		std::vector<std::thread> threads;
		GeometryPipelineOutput out;
		out.Format = format_;
		out.Outputs.resize(childThreads + 1);


		const size_t mainThreadCount = primitiveCountEveryThread;
		size_t offset = mainThreadCount;
		for (size_t i = 0; i < childThreads; ++i)
		{
			const size_t begin = offset;
			const size_t count = i == childThreads - 1 ? primitiveCount - begin : primitiveCountEveryThread;
			offset += count;


			threads.emplace_back(processThread, false, passes_,format_, inputData, begin, count, &out.Outputs[i],stripData);
		}

		processThread(childThreads == 0 && clearAfterProcess, passes_,format_, inputData,0, mainThreadCount, &out.Outputs[childThreads],stripData);

		for (auto& p : threads) p.join();

		if (clearAfterProcess) inputData.clear();

		return out;
	}

	template<int VertexPerPrimitive>
	inline GeometryPipelineOutput GeometryPipeline<VertexPerPrimitive>::Process(const std::vector<float>& inputData, const std::vector<bool>& stripData) const
	{
		std::vector<float>& input = const_cast<std::vector<float>&>(inputData);
		std::vector<bool>& strip = const_cast<std::vector<bool>&>(stripData);
		return Process(input, strip);
	}


	template<int VertexPerPrimitive>
	inline void GeometryPipeline<VertexPerPrimitive>::AddPass(const std::shared_ptr<const GeometryPass<VertexPerPrimitive>>& pass)
	{
		passes_.push_back(pass);
	}

	template<int VertexPerPrimitive>
	inline void GeometryPipeline<VertexPerPrimitive>::ClearPass()
	{
		passes_.clear();
	}

	template<int VertexPerPrimitive>
	inline void GeometryPipeline<VertexPerPrimitive>::processThread(bool singleThreadAndInputDestroyable, const std::vector<std::shared_ptr<const GeometryPass<VertexPerPrimitive>>>& passes,const GeometryDataFormat& format, std::vector<float>& inputData, size_t primitiveBegin, size_t primitiveCount, typename GeometryPipelineOutput::ThreadOut* outputData, std::vector<bool>& stripData)
	{
		typename GeometryPass<VertexPerPrimitive>::GeometryPassIO io(format);
		//io.StripData.resize(primitiveCount*VertexPerPrimitive);

		if (singleThreadAndInputDestroyable)
		{
			//Move
			io.VertexData = std::move(inputData);
			io.StripData = std::move(stripData);
		}
		else
		{
			//Copy
			io.VertexData.resize(primitiveCount*format.ElementCount*VertexPerPrimitive);
			auto inputBegin = inputData.cbegin() + primitiveBegin*format.ElementCount*VertexPerPrimitive;
			std::copy(inputBegin, inputBegin + io.VertexData.size(), io.VertexData.begin());

			io.StripData.resize(primitiveCount*VertexPerPrimitive);
			auto stripBegin = stripData.cbegin() + primitiveBegin * VertexPerPrimitive;
			std::copy(stripBegin, stripBegin + io.StripData.size(), io.StripData.begin());
		}
		
		for (const auto& p : passes)
			p->Process(io);

		{
			outputData->StripData = std::move(io.StripData);
			outputData->VertexData = std::move(io.VertexData);
		}
	}

}
