#include "Servent.h"
#include "rssreader.h"

//#pragma comment( lib , "libcurl_imp.lib" )
//#ifdef DEBUG
//	#pragma comment( lib , "rssreaderd.lib")
//#else
	#pragma comment( lib , "rssreader.lib")
//#endif

Servent::Servent(boost::function<void(const std::string&,const std::string&)> pfn):m_pfnComplete(pfn)
{
}

Servent::~Servent(void)
{
}

std::string normalize(const std::string& str)
{
	std::string result = str;
	const char symbols[]="//\\.,:";
	int size = sizeof(symbols)/sizeof(char);
	for(int i=0;i<size;++i)
	{
		size_t pos = str.find(symbols[i]);
		while(pos!=std::string::npos)
		{
			result.replace(pos,1,"_");
			pos = str.find(symbols[i],pos+1);
		}
	}
	return result;
}

bool Servent::Connect(const std::string& url)
{
	CRssReader reader;
	tstring strXml;
	//std::fstream file;
	//file.open(normalize(url).c_str(),std::ios::app);
	reader.GetRss( url,strXml );
	//file<<strXml;
	m_pfnComplete(url,strXml);
	return true;
}