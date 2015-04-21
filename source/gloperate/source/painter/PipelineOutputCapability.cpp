#include <gloperate/painter/PipelineOutputCapability.h>

#include <gloperate/base/collection.hpp>

#include <gloperate/pipeline/AbstractPipeline.h>

namespace gloperate
{

/**
*  @brief
*    Constructor
*/
PipelineOutputCapability::PipelineOutputCapability(const gloperate::AbstractPipeline & pipeline)
    : AbstractOutputCapability{}
    , m_pipeline ( pipeline )
{
}

/**
*  @brief
*    Destructor
*/
PipelineOutputCapability::~PipelineOutputCapability()
{
}

std::vector<gloperate::AbstractData*> PipelineOutputCapability::allOutputs() const
{
	std::vector<gloperate::AbstractData*> result;
	std::vector<gloperate::AbstractData*> tmpOutputs = m_pipeline.allOutputs();

	std::copy(tmpOutputs.begin(), tmpOutputs.end(), std::back_inserter(result));
	std::copy(m_pipeline.parameters().begin(), m_pipeline.parameters().end(), std::back_inserter(result));
	
    return result;
}

}
