#pragma once

#include <gloperate/pipeline/TripleBufferedData.h>


namespace gloperate 
{

template <typename T>
template <typename... Args>
TripleBufferedData<T>::TripleBufferedData(Args&&... args)
: m_data(std::forward<Args>(args)...)
{
}

template <typename T>
T & TripleBufferedData<T>::data()
{
    return m_data;
}

template <typename T>
const T & TripleBufferedData<T>::data() const
{
    return m_data;
}

template <typename T>
T & TripleBufferedData<T>::operator*()
{
    return m_data;
}

template <typename T>
const T & TripleBufferedData<T>::operator*() const
{
    return m_data;
}

template <typename T>
T * TripleBufferedData<T>::operator->()
{
    return &m_data;
}

template <typename T>
const T * TripleBufferedData<T>::operator->() const
{
    return &m_data;
}

template <typename T>
TripleBufferedData<T>::operator const T &() const
{
    return m_data;
}

template <typename T>
TripleBufferedData<T> & TripleBufferedData<T>::operator=(const TripleBufferedData<T> & data)
{
    *this = data.data();

    return *this;
}

template <typename T>
const T & TripleBufferedData<T>::operator=(const T & value)
{
    m_data = value;
    invalidated();

    return value;
}

template <typename T>
void TripleBufferedData<T>::setData(const T & value)
{
    m_data = value;
    invalidated();
}
    
} // namespace gloperate
