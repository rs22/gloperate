#pragma once

#include <gloperate/gloperate_api.h>

#include <gloperate/base/ScopedConnection.h>

#include <gloperate/pipeline/AbstractInputSlot.h>
#include <gloperate/pipeline/Data.h>


namespace gloperate 
{

template <typename T>
class DoubleBufferedInputSlot : public AbstractInputSlot
{
public:
    DoubleBufferedInputSlot();

    const T & data() const;
    const T & data(const T & defaultValue) const;
    const T & operator*() const;
    const T * operator->() const;

    virtual bool connectTo(const AbstractData & data) override;
    virtual bool matchType(const AbstractData & data) override;

    template <typename U>
    const Data<U> & operator=(const Data<U> & data);
    template <typename U>
    DoubleBufferedInputSlot<T> & operator=(DoubleBufferedInputSlot<U> & slot);

    virtual const AbstractData * connectedData() const override;

protected:
    const Data<T>* m_data;
    gloperate::ScopedConnection m_connection;

    static const T s_defaultValue;

    template <typename U>
    void connect(const Data<U> & data);

private:
};

} // namespace gloperate


#include <gloperate/pipeline/DoubleBufferedInputSlot.hpp>
