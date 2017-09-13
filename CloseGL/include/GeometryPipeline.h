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
			std::unique_ptr<std::vector<TData>> VertexData;
			std::unique_ptr<std::vector<bool>> StripData;
		};

		std::vector<ThreadOut> outputs;
	};

	template<typename TData = float>	//TData = double/float
	class GeometryPipeline
	{
	public:

		GeometryPipeline(GeometryDataFormat format,int primitiveVertexCount);
		void SetChildThreads(unsigned childThreads);
		GeometryPipelineOutput<TData> Process(const std::vector<TData>& inputData) const;

		void AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass);
		void ClearPass();

	private:
		static void processThread(const std::vector<TData>& inputData,size_t vertexBegin,size_t vertexCount, GeometryPipelineOutput<TData>::ThreadOut& outputData);
		std::vector<std::shared_ptr<GeometryPass<TData>>> passes_;
		GeometryDataFormat format_;
		unsigned childThreads_ = 0;
		int primitiveVertexCount_;

	};



	template<typename TData>
	inline GeometryPipeline<TData>::GeometryPipeline(GeometryDataFormat format,int primitiveVertexCount):
		format_(format),
		primitiveVertexCount_(primitiveVertexCount)
	{}

	template<typename TData>
	inline void GeometryPipeline<TData>::SetChildThreads(unsigned childThreads)
	{
		childThreads_ = childThreads;
	}

	template<typename TData>
	inline GeometryPipelineOutput<TData> GeometryPipeline<TData>::Process(const std::vector<TData>& inputData) const
	{
		const size_t primitiveCount = (inputData.size() / format_.ElementCount) / primitiveVertexCount_;
		const auto childThreads = primitiveCount  < childThreads_ ? 0 : childThreads_;
		const size_t primitiveCountEveryThread = primitiveCount / (childThreads + 1);


		std::vector<std::thread> threads;
		GeometryPipelineOutput out;

		const size_t mainThreadCount = primitiveCountEveryThread;
		size_t offset = mainThreadCount;
		for (size_t i = 0; i < childThreads; ++i)
		{
			const size_t begin = offset;
			size_t count = i == childThreads - 1 ? primitiveCount - begin : primitiveCountEveryThread;
			offset += count;

			outputs.emplace_back();

			threads.emplace_back(processThread,inputData, begin, count, outputs.back());
		}
		GeometryPipelineOutput<TData> mainOutput;
		processThread(inputData, 0, mainThreadCount, mainOutput);

		for (size_t i = 0; i < childThreads; ++i)
		{
			threads[i].join();
		}

		return mainOutput;
	}



	template<typename TData>
	inline void GeometryPipeline<TData>::AddPass(const std::shared_ptr<const GeometryPass<TData>>& pass)
	{
		passes_.push_back(pass);
	}

	template<typename TData>
	inline void GeometryPipeline<TData>::ClearPass()
	{
		passes_.clear();
	}
	template<typename TData>
	inline void GeometryPipeline<TData>::processThread(const std::vector<TData>& inputData, size_t vertexBegin, size_t vertexCount, GeometryPipelineOutput<TData>::ThreadOut& outputData)
	{
		std::stringstream ss;
		ss << "ProcessThread:" << inputData.size() << "\t" << vertexBegin << "\t" << vertexCount<<"\t" << &outputData << std::endl;
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(ss.str().c_str());

		std::vector<TData> data;
		//data.resize(
		std::copy(inputData.cbegin() + vertexBegin,inputData.cbegin() + (vertexBegin + vertexCount),data.begin());
		
	}
}
