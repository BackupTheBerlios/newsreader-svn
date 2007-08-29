#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "event.h"

class Servent;
class Scheduler;


class Proxy
{
	boost::shared_ptr<Servent>		m_spServant;
	boost::shared_ptr<Scheduler>	m_spScheduler;
public:
	Proxy(boost::shared_ptr<TEvent> spEvent,boost::function<void(const std::string&,const std::string&)>);
	bool Connect(const std::string& url);
public:
	virtual ~Proxy(void);
};
