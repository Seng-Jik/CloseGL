#pragma once
#include "GeometryDataFormat.h"
#include "GeometryPass.h"
#include <memory>
#include <thread>
#include <algorithm>

//Debug
#include <iostream>
#include <mutex>
#include <CppUnitTestLogger.h>
#include <sstream>

namespace CloseGL::Geometry
{

	template<typename TData = float>
	struct GeometryPipelineOutput
	{
		struct ThreadOut
		{
			std::vector<TData> VertexData;
			std::vector<bool> StripData;
		};
		std::vector<ThreadOut> outputs;
	};

	template<typename TData = float, int VertexPerPrimitive = 4>	//TData = double/float
	class GeometryPipeline
	{
	public:

		GeometryPipeline(GeometryDataFormat format);
		void SetChildThreads(unsigned childThreads);
		GeometryPipelineOutput<TData> Process(std::vector<TData>& inputData, bool clearAfterProcess = false) const;
		//If not readonly,this vector maybe destroyed.

		void AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass);
		void ClearPass();

	private:
		static void processThread(bool singleThreadAndInputDestroyable, const std::vector<std::shared_ptr<GeometryPass<TData>>>& passes,const GeometryDataFormat& format, std::vector<TData>& inputData,size_t primitiveBegin,size_t primitiveCount, typename GeometryPipelineOutput<TData>::ThreadOut& outputData);
		std::vector<std::shared_ptr<GeometryPass<TData>>> passes_;
		GeometryDataFormat format_;
		unsigned childThreads_ = 0;

	};



	template<typename TData, int VertexPerPrimitive>
	inline GeometryPipeline<TData, VertexPerPrimitive>::GeometryPipeline(GeometryDataFormat format):
		format_(format)
	{
	}

	template<typename TData, int VertexPerPrimitive>
	inline void GeometryPipeline<TData, VertexPerPrimitive>::SetChildThreads(unsigned childThreads)
	{
		childThreads_ = childThreads;
	}


	template<typename TData, int VertexPerPrimitive>
	inline GeometryPipelineOutput<TData> GeometryPipeline<TData, VertexPerPrimitive>::Process(std::vector<TData>& inputData, bool clearAfterProcess) const
	{
		const size_t primitiveCount = (inputData.size() / format_.ElementCount) / VertexPerPrimitive;
		const auto childThreads = primitiveCount  < childThreads_ ? 0 : childThreads_;
		const size_t primitiveCountEveryThread = primitiveCount / (childThreads + 1);


		std::vector<std::thread> threads;
		GeometryPipelineOutput<TData> out;
		out.outputs.emplace_back();

		auto& mainOutput = out.outputs.back();

		const size_t mainThreadCount = primitiveCountEveryThread;
		size_t offset = mainThreadCount;
		for (size_t i = 0; i < childThreads; ++i)
		{
			const size_t begin = offset;
			const size_t count = i == childThreads - 1 ? primitiveCount - begin : primitiveCountEveryThread;
			offset += count;

			out.outputs.emplace_back();
			auto& threadOut = out.outputs.back();

			threads.emplace_back(processThread, false, passes_,format_, inputData, begin, count, threadOut);
		}
		processThread(childThreads == 0 && clearAfterProcess, passes_,format_, inputData,0, mainThreadCount, mainOutput);

		for (size_t i = 0; i < childThreads; ++i)
		{
			threads[i].join();
		}

		if (clearAfterProcess) inputData.clear();

		return out;
	}


	template<typename TData, int VertexPerPrimitive>
	inline void GeometryPipeline<TData, VertexPerPrimitive>::AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass)
	{
		passes_.push_back(pass);
	}

	template<typename TData, int VertexPerPrimitive>
	inline void GeometryPipeline<TData, VertexPerPrimitive>::ClearPass()
	{
		passes_.clear();
	}

	template<typename TData, int VertexPerPrimitive>
	inline void GeometryPipeline<TData, VertexPerPrimitive>::processThread(bool singleThreadAndInputDestroyable, const std::vector<std::shared_ptr<GeometryPass<TData>>>& passes,const GeometryDataFormat& format, std::vector<TData>& inputData, size_t primitiveBegin, size_t primitiveCount, typename GeometryPipelineOutput<TData>::ThreadOut& outputData)
	{
		typename GeometryPass<TData>::GeometryPassIO io(format);
		io.StripData.resize(primitiveCount*VertexPerPrimitive);

		if (singleThreadAndInputDestroyable)
		{
			//Move
			io.VertexData = std::move(inputData);
		}
		else
		{
			//Copy
			io.VertexData.resize(primitiveCount*format.ElementCount*VertexPerPrimitive);
			auto inputBegin = inputData.cbegin() + primitiveBegin*format.ElementCount*VertexPerPrimitive;
			std::copy(inputBegin, inputBegin + io.VertexData.size(), io.VertexData.begin());
		}

		for (const auto& p : passes)
			p->Process(io);

		std::stringstream ss;
		ss << "ProcessThread:" << inputData.size() << "\t" << primitiveBegin << "\t" << primitiveCount << "\t" << &outputData <<"\t"<<io.VertexData.at(0)<< std::endl;
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(ss.str().c_str());
	}

}
