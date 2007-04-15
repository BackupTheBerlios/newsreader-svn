#include <def.h>
#include <boost/shared_ptr.hpp>

class CRssReaderImpl;

class CRssReader
{
public:
	void GetRss( const tstring& url, tstring& xml );
	CRssReader();
private:
	boost::shared_ptr<CRssReaderImpl> m_RssImpl;
};