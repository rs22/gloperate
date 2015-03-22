#pragma once

#include <mutex>

#include <gloperate/gloperate_api.h>

#include <gloperate/pipeline/Data.h>


namespace gloperate 
{

template <typename T>
class UnbufferedData : public Data<T>
{
public:
    UnbufferedData(const T & d);
    template <typename... Args>
    UnbufferedData(Args&&... args);

    T & startWriting() override;
    void finishWriting() override;

    const T & startReading() override;
    void finishReading() override;
protected:
    T m_data;
    std::mutex m_mutex;
};

} // namespace gloperate


#include <gloperate/pipeline/UnbufferedData.hpp>
