#pragma once

#include <gloperate/pipeline/Data.h>

#include <typeinfo>

namespace gloperate 
{

template <typename T>
T Data<T>::data()
{
    T d = startReading();

    finishReading();

    return d;
}

template <typename T>
void Data<T>::setData(const T & newData)
{
    T & d = startWriting();

    d = newData;

    finishWriting();
}

template <typename T>
std::string Data<T>::type() const
{
    return typeid(T).name();
}

} // namespace gloperate
