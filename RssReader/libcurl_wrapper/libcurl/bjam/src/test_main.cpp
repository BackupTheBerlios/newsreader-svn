#include <rssreader.h>
#include <iostream>



#ifdef _DEBUG
	#pragma comment( lib , "..\\..\\lib\\rssreaderd.lib")
#else
	#pragma comment( lib , "..\\..\\lib\\rssreader.lib")
#endif

int main()
{
	CRssReader reader;
	tstring strXml;
	reader.GetRss( "http://gorod.dp.ua/export/rss.php",strXml );
	std::cout<<strXml<<std::endl;
	return 0;
}