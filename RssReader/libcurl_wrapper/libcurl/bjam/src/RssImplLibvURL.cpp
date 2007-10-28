#include <curl/curl.h>
#include <Rssimpllibvurl.h>

CRssReaderLibCURL::CRssReaderLibCURL()
{
	m_spCurl = SPUrl( curl_easy_init() , curl_easy_cleanup );
}



size_t CRssReaderLibCURL::function( void *ptr, size_t size, size_t nmemb, void *stream)
{
	if( size>0 )
	{
		CRssReaderLibCURL* pThis = reinterpret_cast<CRssReaderLibCURL*>( stream );
		//pThis->m_strXml.assign( (char*)ptr , (char*)ptr + size*nmemb );
		pThis->m_strXml.append((char*)ptr,(char*)ptr+size*nmemb);
		return size*nmemb;
	}
	return 0;
}

void CRssReaderLibCURL::GetRss( const tstring& url, tstring& xml )
{
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	struct curl_slist *headerlist=NULL;
	char buf[] = "Expect:";	
	
	CURLcode code = curl_easy_setopt(m_spCurl.get(), CURLOPT_URL,url.c_str());
	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_VERBOSE,TRUE); 
	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_HTTPGET, TRUE);

	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_WRITEFUNCTION, &CRssReaderLibCURL::function);
	code = curl_easy_setopt(m_spCurl.get(), CURLOPT_WRITEDATA, this);


	headerlist = curl_slist_append(headerlist, buf);
	curl_easy_setopt(m_spCurl.get(), CURLOPT_HTTPHEADER, headerlist);

	//code = curl_easy_setopt(m_spCurl.get(), CURLOPT_HTTPPOST, post);
	code = curl_easy_perform(m_spCurl.get());
	xml = m_strXml;
}