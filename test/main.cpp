#include <curl/curl.h>
#include <boost/shared_ptr.hpp>

/**
 this program posts file to web site
   command lie
    - URL
   - file name
   e.g
    post_file.exe http://peacebird.host.sk/upload.php d:\garbage\some_file.txt
*/
int main(int argc, char* argv[])
{
	if( argc < 3 )
		return 1;
	
	
	typedef boost::shared_ptr<CURL> SPUrl;
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	struct curl_slist *headerlist=NULL;
	char buf[] = "Expect:";	
	

	SPUrl curl = SPUrl( curl_easy_init() , curl_easy_cleanup );
	CURLcode code = curl_easy_setopt(curl.get(), CURLOPT_URL,/*"http://peacebird.host.sk/upload.php"*/ argv[1] );
	code = curl_easy_setopt(curl.get(), CURLOPT_VERBOSE,TRUE); 
	code = curl_easy_setopt(curl.get(), CURLOPT_POST, TRUE);

	headerlist = curl_slist_append(headerlist, buf);
	curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headerlist);
	
	CURLFORMcode ret = curl_formadd(&post, &last,
		       CURLFORM_COPYNAME, "MAX_FILE_SIZE",
               CURLFORM_COPYCONTENTS, "3000000",
			   CURLFORM_CONTENTSLENGTH, 7,
			   CURLFORM_END);	

	curl_formadd(&post, &last, CURLFORM_COPYNAME, "userfile",CURLFORM_FILE, argv[2],CURLFORM_END);	

	code = curl_easy_setopt(curl.get(), CURLOPT_HTTPPOST, post);
	code = curl_easy_perform(curl.get());
	return 0;
}

