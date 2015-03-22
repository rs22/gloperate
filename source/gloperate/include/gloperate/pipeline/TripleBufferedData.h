#pragma once

#include <mutex>

#include <gloperate/gloperate_api.h>

#include <gloperate/pipeline/Data.h>


namespace gloperate 
{

template <typename T>
class TripleBufferedData : public Data<T>
{
public:
    TripleBufferedData(const T & d);
    template <typename... Args>
    TripleBufferedData(Args&&... args);

    T & startWriting();
    void finishWriting();

    const T & startReading();
    void finishReading();
protected:
    T m_writeData;
    T m_intermediateData;
    T m_readData;
    std::mutex m_mutex;
    bool m_update;
};

} // namespace gloperate


#include <gloperate/pipeline/TripleBufferedData.hpp>
