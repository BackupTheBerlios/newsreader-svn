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
	Scheduler();
public:
	~Scheduler(void);
	void enqueue(boost::shared_ptr<IMethodRequest>);
	void stop();
private:
	boost::shared_ptr<boost::thread> m_spThread;
	MethodList m_ActiveQueue;
	boost::mutex m_lock;
	boost::condition m_condition;
	volatile bool m_StopThread; 
};
