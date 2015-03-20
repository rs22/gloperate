#pragma once

#include <gloperate/pipeline/DoubleBufferedInputSlot.h>

#include <typeinfo>
#include <type_traits>


namespace gloperate 
{

template <typename T>
const T DoubleBufferedInputSlot<T>::s_defaultValue = T();

template <typename T>    
DoubleBufferedInputSlot<T>::DoubleBufferedInputSlot()
: m_data(nullptr)
{
}

template <typename T>
const T & DoubleBufferedInputSlot<T>::data() const
{
    return data(s_defaultValue);
}

template <typename T>
const T & DoubleBufferedInputSlot<T>::data(const T & defaultValue) const
{
    return isConnected() ? m_data->data() : defaultValue;
}
    
template <typename T>
const T & DoubleBufferedInputSlot<T>::operator*() const
{
    return data();
}
    
template <typename T>
const T * DoubleBufferedInputSlot<T>::operator->() const
{
    return &data();
}

template <typename T>
bool DoubleBufferedInputSlot<T>::connectTo(const AbstractData & data)
{
    const Data<T> * data_ptr = dynamic_cast<const Data<T>*>(&data);
    
    if (!data_ptr)
    {
        printIncompatibleMessage(this, typeid(T).name(), data);
        return false;
    }
    
    connect(*data_ptr);
    
    return true;
}

template <typename T>
bool DoubleBufferedInputSlot<T>::matchType(const AbstractData & data)
{
    const Data<T> * data_ptr = dynamic_cast<const Data<T>*>(&data);

    return data_ptr != nullptr;
}

template <typename T>
template <typename U>
const Data<U> & DoubleBufferedInputSlot<T>::operator=(const Data<U> & data)
{
    connect(data);

    return data;
}

template <typename T>
template <typename U>
DoubleBufferedInputSlot<T> & DoubleBufferedInputSlot<T>::operator=(DoubleBufferedInputSlot<U> & slot)
{
    if (slot.isConnected())
    {
        connect(*slot.m_data);
    }

    return *this;
}

template <typename T>
template <typename U>
void DoubleBufferedInputSlot<T>::connect(const Data<U> & data)
{
    using Tp = typename std::remove_pointer<T>::type;
    using Up = typename std::remove_pointer<U>::type;

    static_assert(std::is_same<T, U>::value || (std::is_pointer<T>::value && std::is_pointer<U>::value && std::is_base_of<Tp, Up>::value), "Types incompatible");

    m_data = reinterpret_cast<const Data<T>*>(&data);
    m_connection = data.invalidated.connect([this]() { this->changed(); });
    connectionChanged();
    changed();
}

template <typename T>
const AbstractData * DoubleBufferedInputSlot<T>::connectedData() const
{
    return m_data;
}

} // namespace gloperate
