#include <boost/lambda/lambda.hpp>

#include <boost/thread/thread.hpp>
#pragma once 
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/xtime.hpp>
#include <libs/thread/src/timeconv.inl>

////////////////////////////////////////////////////////////////////////////////
template <typename TEvent = int, TEvent TNoneValue=0>
class event
{
    volatile TEvent m_Value;
    boost::mutex m_Monitor;
    boost::condition m_Condition;

    struct wait_functor
    {
        const event& m_Owner;
        wait_functor(const event& Owner) : m_Owner(Owner) {}
        bool operator()()
        {
            return m_Owner.m_Value != TNoneValue;
        }
    };

public:

    event() : m_Value(TNoneValue) {}
    event(TEvent Value) : m_Value(Value) {}

    TEvent wait(bool bReset = false)
    {
        boost::mutex::scoped_lock lock(m_Monitor);
        m_Condition.wait(lock, wait_functor(*this));
        TEvent e = m_Value;
        if (bReset)
            m_Value = TNoneValue;
        return e;
    }

    TEvent timed_wait(const boost::xtime& xt, bool bReset = false)
    {
        boost::mutex::scoped_lock lock(m_Monitor);
        m_Condition.timed_wait(lock, xt, wait_functor(*this));
        TEvent e = m_Value;
        if (bReset)
            m_Value = TNoneValue;
        return e;
    }

    void set(TEvent Value)
    {
        boost::mutex::scoped_lock lock(m_Monitor);
        m_Value = Value;
        m_Condition.notify_all();
    }

    friend struct wait_functor;
};


enum events_t { none_evt, queue_not_empty_evt,queue_is_empty_evt, stop_evt , thread_stop_evt };
typedef event<events_t, none_evt> TEvent;
