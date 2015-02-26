#pragma once

#include <gloperate/gloperate_api.h>

#include <gloperate/painter/AbstractOutputCapability.h>
#include <gloperate/pipeline/AbstractPipeline.h>

#include <string>
#include <vector>


namespace gloperate
{

class AbstractData;
template <typename T>
class Data;

/**
*  @brief
*    Base class for output capabilities
*
*/
class GLOPERATE_API OutputCapability : public AbstractOutputCapability
{


public:
    /**
    *  @brief
    *    Constructor
    */
    OutputCapability(gloperate::AbstractPipeline & pipeline);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~OutputCapability();

    virtual std::vector<gloperate::AbstractData*> findOutputs(const std::string & name) const;

    template <typename T>
    Data<T> * getOutput(const std::string & name) const;
    template <typename T>
    Data<T> * getOutput() const;

    virtual std::vector<gloperate::AbstractData*> allOutputs() const;

protected:
    gloperate::AbstractPipeline & m_pipeline;
};

} // namespace gloperate

#include <gloperate/painter/OutputCapability.hpp>