#pragma once

#include <gloperate/pipeline/TripleBufferedData.h>


namespace gloperate 
{

template <typename T>
TripleBufferedData<T>::TripleBufferedData(const T & d)
: m_writeData(d)
{
}

template <typename T>
template <typename... Args>
TripleBufferedData<T>::TripleBufferedData(Args&&... args)
: m_writeData(std::forward<Args>(args)...)
, m_update(false)
{
}

template <typename T>
T & TripleBufferedData<T>::startWriting()
{
    return m_writeData;
}

template <typename T>
void TripleBufferedData<T>::finishWriting()
{
    m_mutex.lock();
    std::swap(m_writeData, m_intermediateData);
    m_update = true;
    m_mutex.unlock();

    this->invalidated();
}

template <typename T>
const T & TripleBufferedData<T>::startReading()
{
    m_mutex.lock();
    if (m_update)
    {
        m_update = false;
        std::swap(m_intermediateData, m_readData);
    }
    m_mutex.unlock();

    return m_readData;
}

template <typename T>
void TripleBufferedData<T>::finishReading()
{
}

} // namespace gloperate
