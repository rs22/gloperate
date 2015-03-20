#pragma once

#include <gloperate/pipeline/DoubleBufferedData.h>


namespace gloperate 
{

template <typename T>
template <typename... Args>
DoubleBufferedData<T>::DoubleBufferedData(Args&&... args)
: m_data(std::forward<Args>(args)...)
{
}

template <typename T>
T & DoubleBufferedData<T>::data()
{
    return m_data;
}

template <typename T>
const T & DoubleBufferedData<T>::data() const
{
    return m_data;
}

template <typename T>
T & DoubleBufferedData<T>::operator*()
{
    return m_data;
}

template <typename T>
const T & DoubleBufferedData<T>::operator*() const
{
    return m_data;
}

template <typename T>
T * DoubleBufferedData<T>::operator->()
{
    return &m_data;
}

template <typename T>
const T * DoubleBufferedData<T>::operator->() const
{
    return &m_data;
}

template <typename T>
DoubleBufferedData<T>::operator const T &() const
{
    return m_data;
}

template <typename T>
DoubleBufferedData<T> & DoubleBufferedData<T>::operator=(const DoubleBufferedData<T> & data)
{
    *this = data.data();

    return *this;
}

template <typename T>
const T & DoubleBufferedData<T>::operator=(const T & value)
{
    m_data = value;
    invalidated();

    return value;
}

template <typename T>
void DoubleBufferedData<T>::setData(const T & value)
{
    m_data = value;
    invalidated();
}
    
} // namespace gloperate
