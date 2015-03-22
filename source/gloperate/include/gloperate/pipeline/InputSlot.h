#pragma once

#include <gloperate/gloperate_api.h>

#include <signalzeug/ScopedConnection.h>

#include <gloperate/pipeline/AbstractInputSlot.h>
#include <gloperate/pipeline/Data.h>


namespace gloperate 
{

void GLOPERATE_API printIncompatibleMessage(const AbstractInputSlot* slot, const std::string& typeName,
                              const AbstractData & data);

template <typename T>
class InputSlot : public AbstractInputSlot
{
public:
    InputSlot();

    /**
     * @brief Convenience call for startReading and finishReading.
     * Creates a copy, usage strongly discouraged.
     *
     * @return the currently stored data
     */
    T data();
    T data(const T & defaultValue);

    const T & startReading();
    const T & startReading(const T & defaultValue);
    void finishReading();

    virtual bool connectTo(AbstractData &data) override;
    virtual bool matchType(const AbstractData & data) override;

    template <typename U>
    Data<U> & operator=(Data<U> & data);
    template <typename U>
    InputSlot<T> & operator=(InputSlot<U> & slot);

    virtual const Data<T> * connectedData() const override;

protected:
    Data<T>* m_data;
    signalzeug::ScopedConnection m_connection;

    static const T s_defaultValue;

    template <typename U>
    void connect(Data<U> & data);

private:
};

} // namespace gloperate


#include <gloperate/pipeline/InputSlot.hpp>
