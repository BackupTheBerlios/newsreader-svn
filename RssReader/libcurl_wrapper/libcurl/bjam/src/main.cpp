
///////////////////////////////////////////////////////////////////////////////////////
#include "CRssReaderImpl"

CRssReader::CRssReader():m_RssImpl( new CRssReaderImpl )
{
}

tstring CRssReader::GetRss( const tstring& url )
{
	return m_RssImpl->GetRss( url );
}
///////////////////////////////////////////////////////////////////////////////////////


class CRssReaderImpl
{
public:
	virtual tstring GetRss( const tstring& url ) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////

#include "CRssReaderImpl" 

class CRssReaderLibCURL : public CRssReaderImpl
{
public:
	typedef boost::shared_ptr<CURL> SPUrl;
	tstring GetRss( const tstring& url );
	
	CRssReaderLibCURL();
private:
	SPUrl m_spCurl;
}

///////////////////////////////////////////////////////////////////////////////////////


CRssReaderLibCURL::CRssReaderLibCURL()
{
	m_spCurl = SPUrl( curl_easy_init() , curl_easy_cleanup );
}

tstring CRssReaderLibCURL::GetRss( const tstring& url )
{
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	struct curl_slist *headerlist=NULL;
	char buf[] = "Expect:";	
	
	CURLcode code = curl_easy_setopt(m_spCurl.get(), CURLOPT_URL,url.c_str());
	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_VERBOSE,TRUE); 
	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_GET, TRUE);

	headerlist = curl_slist_append(headerlist, buf);
	curl_easy_setopt(m_spCurl.get(), CURLOPT_HTTPHEADER, headerlist);

	//code = curl_easy_setopt(m_spCurl.get(), CURLOPT_HTTPPOST, post);
	code = curl_easy_perform(m_spCurl.get());
}