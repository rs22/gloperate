#pragma once

#include <gloperate/pipeline/Data.h>

#include <typeinfo>

namespace gloperate 
{

template <typename T>
std::string Data<T>::type() const
{
    return typeid(T).name();
}

} // namespace gloperate
