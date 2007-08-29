#pragma once
#include "imethodrequest.h"
#include <boost/shared_ptr.hpp>
#include <string>

class Servent;

class CConnectRequest :
	public IMethodRequest
{
public:
	CConnectRequest(boost::shared_ptr<Servent> spServant,const std::string& url);
	virtual bool call();
public:
	~CConnectRequest(void);
private:
	boost::shared_ptr<Servent> m_spServant;
	std::string m_strUrl;
};
