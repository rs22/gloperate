#pragma once

#include <mutex>

#include <gloperate/gloperate_api.h>

#include <gloperate/pipeline/Data.h>


namespace gloperate 
{

template <typename T>
class DoubleBufferedData : public Data<T>
{
public:
    DoubleBufferedData(const T & d);
    template <typename... Args>
    DoubleBufferedData(Args&&... args);

    T & startWriting();
    void finishWriting();

    const T & startReading();
    void finishReading();
protected:
    T m_writeData;
    T m_readData;
    std::mutex m_mutex;
};

} // namespace gloperate


#include <gloperate/pipeline/DoubleBufferedData.hpp>
