#include "def.h"
#include <boost/shared_ptr.hpp>

class CRssReaderImpl;

#pragma comment( lib , "libcurl.lib" )

#ifdef _DEBUG
	#pragma comment( lib , "rssreaderd.lib")
#else
	#pragma comment( lib , "rssreader.lib")
#endif

class CRssReader
{
public:
	void GetRss( const tstring& url, tstring& xml );
	CRssReader();
private:
	boost::shared_ptr<CRssReaderImpl> m_RssImpl;
};