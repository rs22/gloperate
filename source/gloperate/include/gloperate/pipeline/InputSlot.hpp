#pragma once

#include <gloperate/pipeline/InputSlot.h>

#include <typeinfo>
#include <type_traits>


namespace gloperate 
{

template <typename T>
const T InputSlot<T>::s_defaultValue = T();

template <typename T>    
InputSlot<T>::InputSlot()
: m_data(nullptr)
{
}

template <typename T>
T InputSlot<T>::data()
{
    return data(s_defaultValue);
}

template <typename T>
T InputSlot<T>::data(const T & defaultValue)
{
    T d = isConnected() ? m_data->startReading() : defaultValue;

    if (isConnected())
    {
        m_data->finishReading();
    }

    return d;
}

template <typename T>
const T & InputSlot<T>::startReading()
{
    return startReading(s_defaultValue);
}

template <typename T>
const T & InputSlot<T>::startReading(const T & defaultValue)
{
    return isConnected() ? m_data->startReading() : defaultValue;
}

template <typename T>
void InputSlot<T>::finishReading()
{
    if (isConnected())
    {
        m_data->finishReading();
    }
}

template <typename T>
bool InputSlot<T>::connectTo(const AbstractData & data)
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
bool InputSlot<T>::matchType(const AbstractData & data)
{
    const Data<T> * data_ptr = dynamic_cast<const Data<T>*>(&data);

    return data_ptr != nullptr;
}

template <typename T>
template <typename U>
const Data<U> & InputSlot<T>::operator=(const Data<U> & data)
{
    connect(data);

    return data;
}

template <typename T>
template <typename U>
InputSlot<T> & InputSlot<T>::operator=(InputSlot<U> & slot)
{
    if (slot.isConnected())
    {
        connect(*slot.m_data);
    }

    return *this;
}

template <typename T>
template <typename U>
void InputSlot<T>::connect(const Data<U> & data)
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
const Data<T> * InputSlot<T>::connectedData() const
{
    return m_data;
}

} // namespace gloperate
