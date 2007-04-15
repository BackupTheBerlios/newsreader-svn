
#include <rssreader.h>
#include <RssImplLibvURL.h>

CRssReader::CRssReader():m_RssImpl( new CRssReaderLibCURL )
{
}

void CRssReader::GetRss(const tstring &url, tstring& xml)
{
	m_RssImpl->GetRss( url , xml );
}