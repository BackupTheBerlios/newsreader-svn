// post_file.cpp : Defines the entry point for the console application.
//


#include <curl/curl.h>
#include <boost/shared_ptr.hpp>


int main(int argc, char* argv[])
{
	//CURL *curl;
	
	typedef boost::shared_ptr<CURL> SPUrl;

	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;

	SPUrl curl = SPUrl( curl_easy_init() , curl_easy_cleanup );



	CURLcode code = curl_easy_setopt(curl.get(), CURLOPT_URL,"http://peacebird.host.sk/upload.php");

	
	code = curl_easy_setopt(curl.get(), CURLOPT_VERBOSE,TRUE); 
	
	code = curl_easy_setopt(curl.get(), CURLOPT_POST, TRUE);

	char fn[] = "D:\\projects\\libcurl\\bjam\\upload.php";

	struct curl_slist *headerlist=NULL;
	char buf[] = "Expect:";	

	headerlist = curl_slist_append(headerlist, buf);
	curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headerlist);
	
	CURLFORMcode ret = curl_formadd(&post, &last,
		       CURLFORM_COPYNAME, "MAX_FILE_SIZE",
               CURLFORM_COPYCONTENTS, "3000000",
			   CURLFORM_CONTENTSLENGTH, 7,
			   CURLFORM_END);	


	curl_formadd(&post, &last, CURLFORM_COPYNAME, "userfile",CURLFORM_FILE, fn,CURLFORM_END);	

	code = curl_easy_setopt(curl.get(), CURLOPT_HTTPPOST, post);
	code = curl_easy_perform(curl.get());
	return 0;
}

