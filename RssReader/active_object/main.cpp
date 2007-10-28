#include "proxy.h"
#include <windows.h>
#include <map>
#include <vector>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include <iostream>

#include "AOPool.h"
#include "xml2html.h"

std::string normalize(const std::string& str);

void sleep(int ms)
{
    boost::xtime delay;
    to_time(ms, delay);
    boost::thread().sleep(delay);
}

typedef std::string tstring;
typedef boost::function<void(const tstring&,const tstring&)> TDownloadCompleteEvent;

class CAOPool
{
public:

	CAOPool(boost::shared_ptr<TEvent> spEvent,TDownloadCompleteEvent pfnEvent):m_spEvent(spEvent),m_pfnDownloadComplete(pfnEvent)
	{
		for(int i=0;i<3;++i)
		{
			m_ActiveObjectPool.insert(boost::shared_ptr<Proxy>(new Proxy(m_pfnDownloadComplete)));
		}
		m_ActiveObjectPool.initialize();
	}

	boost::shared_ptr<Proxy> GetProxy()
	{
		return 	*(m_ActiveObjectPool.getAO());
	}

	void Stop()
	{
		m_ActiveObjectPool.stop();
	}

private:
	AOPool<boost::shared_ptr<Proxy> > m_ActiveObjectPool;
	boost::shared_ptr<TEvent> m_spEvent;
	TDownloadCompleteEvent m_pfnDownloadComplete;
};


class CRssManager
{
public:
	typedef std::map<tstring,tstring> TSubscriptionMap;
	void Subscribe(const tstring& url);
	void Stop();
	void Print();
	CRssManager();
private:
	void OnDownloadComplete(const tstring& url,const tstring& xml );
private:
	TSubscriptionMap m_SubscriptionMap;
	boost::mutex m_SyncObject;
	boost::shared_ptr<TEvent>  m_spEvent;
	CAOPool m_ActiveObjectPool;
};



CRssManager::CRssManager():m_spEvent(new TEvent),m_ActiveObjectPool(m_spEvent,boost::bind(&CRssManager::OnDownloadComplete,this,_1,_2))
{
}

void CRssManager::Subscribe(const tstring& url)
{
	boost::shared_ptr<Proxy> spProxy = m_ActiveObjectPool.GetProxy();
	spProxy->Connect(url);
}

void CRssManager::OnDownloadComplete(const tstring &url, const tstring &xml)
{
	boost::mutex::scoped_lock lock(m_SyncObject);
	m_SubscriptionMap.insert(std::make_pair(url,xml));
}
void CRssManager::Stop()
{
	m_spEvent->set(stop_evt);
}

void CRssManager::Print()
{
	boost::mutex::scoped_lock lock(m_SyncObject);
	TSubscriptionMap::iterator it = m_SubscriptionMap.begin();
	for(;it!=m_SubscriptionMap.end();++it)
	{
		CHtmlDoc htmlDoc;
		htmlDoc.some_func((*it).second);
		htmlDoc.GenerateHtml();
		std::fstream f(normalize((*it).first).c_str(),std::ios::out);
		f << htmlDoc.GetHtmlString();
		//std::fstream file;
		//file.open(normalize((*it).first).c_str(),std::ios::app );
		//file<<(*it).second;		
	}
}

int main()
{
	CRssManager manager;
	manager.Subscribe("http://gorod.dp.ua/export/rss.php");
	manager.Subscribe("http://wwu.korrespondent.net/korr.xml");
	manager.Subscribe("http://itnews.com.ua/export/all.rss");
	manager.Subscribe("http://feeds.feedburner.com/rsdn/cpp");
	manager.Subscribe("http://feeds.feedburner.com/rsdn/cpp/applied");
	sleep(10000);
	manager.Stop();
	manager.Print();
	return 0;
}