#pragma once

#include <gloperate/pipeline/UnbufferedData.h>


namespace gloperate 
{

template <typename T>
UnbufferedData<T>::UnbufferedData(const T & d)
: m_data(d)
{
}

template <typename T>
template <typename... Args>
UnbufferedData<T>::UnbufferedData(Args&&... args)
: m_data(std::forward<Args>(args)...)
{
}

template <typename T>
T & UnbufferedData<T>::startWriting()
{
    m_mutex.lock();

    return m_data;
}

template <typename T>
void UnbufferedData<T>::finishWriting()
{
    m_mutex.unlock();

    this->invalidated();
}

template <typename T>
const T & UnbufferedData<T>::startReading()
{
    m_mutex.lock();

    return m_data;
}

template <typename T>
void UnbufferedData<T>::finishReading()
{
    m_mutex.unlock();
}

} // namespace gloperate
