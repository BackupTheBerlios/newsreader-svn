#include <def.h>

class CRssReaderImpl
{
public:
	virtual void GetRss( const tstring& url , tstring& ) = 0;
};