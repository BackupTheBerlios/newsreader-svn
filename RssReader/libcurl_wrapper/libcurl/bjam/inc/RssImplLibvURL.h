#include <boost/shared_ptr.hpp>
#include "RssReaderImpl.h" 
#include <curl/curl.h>

class CRssReaderLibCURL : public CRssReaderImpl
{
public:
	typedef boost::shared_ptr<CURL> SPUrl;
	void GetRss( const tstring& url, tstring& );
	
	CRssReaderLibCURL();
private:
	static size_t function( void *ptr, size_t size, size_t nmemb, void *stream);
private:
	SPUrl m_spCurl;
	tstring m_strXml;
};