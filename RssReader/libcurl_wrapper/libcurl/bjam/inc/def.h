#include <string>

#if defined(UNICODE) || defined(_UNICODE)	
	typedef std::wstring tstring;
#else
	typedef std::string tstring;
#endif
