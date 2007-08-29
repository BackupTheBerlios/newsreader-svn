#include "Scheduler.h"
#include <boost/mem_fn.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "IMethodRequest.h"

Scheduler::Scheduler(boost::shared_ptr<TEvent> spEvent):m_spEvent(spEvent)
{
	m_spThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Scheduler::thread_entry,this)));
}

Scheduler::~Scheduler(void)
{
}

void Scheduler::thread_entry()
{
	//while(m_spEvent->wait(true)!=queue_not_empty_evt)
	do
	{
		events_t e = m_spEvent->wait(true);
		switch(e)
		{
			case queue_not_empty_evt:
				{
					while(m_ActiveQueue.size())
					{
						boost::shared_ptr<IMethodRequest> obj = m_ActiveQueue.front();
						m_ActiveQueue.pop_front();
						obj->call();
					}
					m_spEvent->set(queue_is_empty_evt);
				};break;
			case stop_evt:
				{
					//m_spEvent->set(thread_stop_evt);	
					return;
				}
		};
	}
	while(true);
}


void Scheduler::enqueue(boost::shared_ptr<IMethodRequest> obj)
{
	lock lk(m_lock);
	m_ActiveQueue.push_back(obj);
	m_spEvent->set(queue_not_empty_evt);
}