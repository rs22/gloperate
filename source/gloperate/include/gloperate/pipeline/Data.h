#pragma once

#include <gloperate/gloperate_api.h>

#include <gloperate/pipeline/AbstractData.h>


namespace gloperate 
{

template <typename T>
class Data : public AbstractData
{
public:
    virtual T & startWriting() = 0;
    virtual void finishWriting() = 0;

    virtual const T & startReading() = 0;
    virtual void finishReading() = 0;

    virtual std::string type() const override;
};

} // namespace gloperate


#include <gloperate/pipeline/Data.hpp>
