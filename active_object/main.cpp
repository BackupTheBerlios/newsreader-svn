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
	enum EActiveObjectStatus
	{
		AO_WORKING,
		AO_WAITING
	};

	struct CAOEntry
	{
		boost::shared_ptr<Proxy> m_spAOProxy;
		EActiveObjectStatus m_eStatus;
	};
public:

	CAOPool(boost::shared_ptr<TEvent> spEvent,TDownloadCompleteEvent pfnEvent):m_spEvent(spEvent),m_pfnDownloadComplete(pfnEvent)
	{
		for(int i=0;i<10;++i)
		{
			CAOEntry aoEntry;
			aoEntry.m_spAOProxy = boost::shared_ptr<Proxy>(new Proxy(m_spEvent,m_pfnDownloadComplete));
			aoEntry.m_eStatus = AO_WAITING ;
			m_ActiveObjectPool.insert(aoEntry);
		}
		m_ActiveObjectPool.initialize();
	}

	boost::shared_ptr<Proxy> GetProxy()
	{
		//std::vector<CAOEntry>::iterator it = m_ActiveObjectPool.begin();
		//for(;it!=m_ActiveObjectPool.end();++it)
		//{
		//	if( (*it).m_eStatus == AO_WAITING)
		//		return (*it).m_spAOProxy;
		//}
		//CAOEntry aoEntry = { boost::shared_ptr<Proxy>(new Proxy(m_spEvent,m_pfnDownloadComplete)) , AO_WORKING };
		//m_ActiveObjectPool.push_back(aoEntry);
		AOPool<CAOEntry>::citerator it = m_ActiveObjectPool.getAO();
		return (*it).m_spAOProxy;
	}

private:
	AOPool<CAOEntry> m_ActiveObjectPool;
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

// (new TEvent);

CRssManager::CRssManager():m_spEvent(new TEvent),m_ActiveObjectPool(m_spEvent,boost::bind(&CRssManager::OnDownloadComplete,this,_1,_2))
{
}

void CRssManager::Subscribe(const tstring& url)
{
//	m_SubscriptionMap.insert(std::make_pair(url,""));
	boost::shared_ptr<Proxy> spProxy = m_ActiveObjectPool.GetProxy();
	//std::cout<<spProxy.get()<<"-"<<url<<std::endl;
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
	//while(m_spEvent->wait()!=thread_stop_evt);
}

void CRssManager::Print()
{
	boost::mutex::scoped_lock lock(m_SyncObject);
	TSubscriptionMap::iterator it = m_SubscriptionMap.begin();
	for(;it!=m_SubscriptionMap.end();++it)
	{
		std::fstream file;
		file.open(normalize((*it).first).c_str(),std::ios::app );
		file<<(*it).second;		
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