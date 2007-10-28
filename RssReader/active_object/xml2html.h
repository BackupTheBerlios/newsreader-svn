#pragma once



#ifdef _DEBUG
	#pragma comment( lib , "tinyxmld.lib")
#else
	#pragma comment( lib , "tinyxml.lib")
#endif

#include <tinyxml.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

class INewsEntry
{
public:
	void virtual CreateEntry(TiXmlNode* /* xml node ??? */) = 0;
	void virtual Print(std::string&) = 0; 

};

typedef std::vector<boost::shared_ptr<INewsEntry> > TNewsVector;

class CNewsRss2 : public INewsEntry
{
public:
	void CreateEntry(TiXmlNode* it)
	{
		TiXmlElement* title = it->FirstChildElement("title");
		m_strTitle = title->GetText();
		title = it->FirstChildElement("link");
		m_strLink = title->GetText();
		title = it->FirstChildElement("description");
		m_strDesc = title->GetText();
	};

	void Print(std::string& strStorage)
	{	
		strStorage+="<a href =";
		strStorage+=m_strLink;
		strStorage+=">";
		strStorage+=m_strTitle;
		strStorage+="</a>\n";
		strStorage+="<H4>";
		strStorage+=m_strDesc;
		strStorage+="</H4>";
	};
private:
	std::string m_strTitle;
	std::string m_strLink;
	std::string m_strDesc;
};




class CHtmlDoc
{
	std::string m_strHtml;
	TNewsVector m_News;
public:
	TNewsVector& GetNews()
	{
		return m_News;
	}
	void GenerateHtml()
	{
		m_strHtml = "<html><body>";
		boost::function<void (boost::shared_ptr<INewsEntry>)> f;
		f = std::bind1st(std::mem_fun(&CHtmlDoc::print_entry),this);
		std::for_each(m_News.begin(),m_News.end(),f);
		m_strHtml+="</html></body>";
	}
	void Print() const
	{
		std::cout<<m_strHtml<<std::endl;
	}

	std::string GetHtmlString() const
	{
		return m_strHtml;
	}

	void some_func(std::string& xml)
	{
		TiXmlDocument doc;
		doc.Parse(xml.c_str() , 0);
		if( !doc.Error() )
		//TiXmlDocument doc("F:\\project\\xml\\tinyxml\\attrmp1\\xml.xml");
		//if (doc.LoadFile())
		{
			TiXmlNode* root = doc.FirstChildElement();
			TiXmlElement*el = root->FirstChildElement("channel");
			for(TiXmlNode* it = el->FirstChild("item");it!=el->LastChild();it = el->IterateChildren(it))
			{
				boost::shared_ptr<INewsEntry> spEntry(new CNewsRss2);
				m_News.push_back( spEntry );
				spEntry->CreateEntry(it);
			}
		}
	}

protected:
	void print_entry(boost::shared_ptr<INewsEntry> entry) 
	{
		entry->Print(m_strHtml);
	}
};