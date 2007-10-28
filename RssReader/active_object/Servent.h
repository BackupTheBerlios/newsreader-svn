#pragma once
#include <string>
#include <boost/function.hpp>

class Servent
{
	boost::function<void(const std::string&,const std::string&)> m_pfnComplete;
public:
	Servent(boost::function<void(const std::string&,const std::string&)>);
	bool Connect(const std::string& url);
public:
	~Servent(void);
};
