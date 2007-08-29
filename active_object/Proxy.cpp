#include "Proxy.h"
#include "Servent.h"
#include "Scheduler.h"
#include "ConnectRequest.h"


Proxy::Proxy(boost::shared_ptr<TEvent> spEvent,boost::function<void(const std::string&,const std::string&)> pfnComplete):
m_spScheduler(new Scheduler(spEvent)),m_spServant(new Servent(pfnComplete))
{
}

Proxy::~Proxy(void)
{
}


bool Proxy::Connect(const std::string& url)
{
	boost::shared_ptr<CConnectRequest> obj(new CConnectRequest(m_spServant,url));
	m_spScheduler->enqueue(obj);
	return true;
}