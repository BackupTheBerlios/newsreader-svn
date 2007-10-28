#include "ConnectRequest.h"
#include "servent.h"

CConnectRequest::CConnectRequest(boost::shared_ptr<Servent> spServant,const std::string& url):m_spServant(spServant),m_strUrl(url)
{
}

CConnectRequest::~CConnectRequest(void)
{
}

bool CConnectRequest::call()
{
	return m_spServant->Connect(m_strUrl);
}