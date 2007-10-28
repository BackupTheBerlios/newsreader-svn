#include "Scheduler.h"
#include <boost/mem_fn.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "IMethodRequest.h"

Scheduler::Scheduler():m_StopThread(false)
{
	m_spThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Scheduler::thread_entry,this)));
}

void sleep(int ms);

Scheduler::~Scheduler(void)
{
}

void Scheduler::thread_entry()
{
	//while(m_spEvent->wait(true)!=queue_not_empty_evt)
	boost::xtime xt;
	to_time(10,xt);
	while(!m_StopThread)
	{
		boost::mutex::scoped_lock lock(m_lock);
		m_condition.timed_wait(lock,xt);

		if(m_StopThread)
				return;
		while(m_ActiveQueue.size())
		{
			boost::shared_ptr<IMethodRequest> obj = m_ActiveQueue.front();
			m_ActiveQueue.pop_front();
			obj->call();
		}
		sleep(1);
	}
}


void Scheduler::enqueue(boost::shared_ptr<IMethodRequest> obj)
{
	lock lk(m_lock);
	m_ActiveQueue.push_back(obj);
	m_condition.notify_one();
}

void Scheduler::stop()
{
	m_StopThread = true;
	m_condition.notify_one();
}