#pragma once

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "event.h"

class IMethodRequest;

class Scheduler
{
	typedef boost::mutex::scoped_lock lock;
	typedef std::list<boost::shared_ptr<IMethodRequest> > MethodList;
	void thread_entry();
public:
	Scheduler(boost::shared_ptr<TEvent> spEvent);
public:
	~Scheduler(void);
	void enqueue(boost::shared_ptr<IMethodRequest>);
private:
	boost::shared_ptr<boost::thread> m_spThread;
	MethodList m_ActiveQueue;
	//boost::thread m_thread;
	boost::mutex m_lock;
	boost::condition m_condition;
	boost::shared_ptr<TEvent>	m_spEvent;
};
