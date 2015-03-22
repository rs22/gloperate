#pragma once

#include <gloperate/pipeline/DoubleBufferedData.h>


namespace gloperate 
{

template <typename T>
DoubleBufferedData<T>::DoubleBufferedData(const T & d)
: m_writeData(d)
{
}

template <typename T>
template <typename... Args>
DoubleBufferedData<T>::DoubleBufferedData(Args&&... args)
: m_writeData(std::forward<Args>(args)...)
{
}

template <typename T>
T & DoubleBufferedData<T>::startWriting()
{
    return m_writeData;
}

template <typename T>
void DoubleBufferedData<T>::finishWriting()
{
    m_mutex.lock();
    std::swap(m_writeData, m_readData);
    m_mutex.unlock();

    this->invalidated();
}

template <typename T>
const T & DoubleBufferedData<T>::startReading()
{
    m_mutex.lock();

    return m_readData;
}

template <typename T>
void DoubleBufferedData<T>::finishReading()
{
    m_mutex.unlock();
}

} // namespace gloperate
