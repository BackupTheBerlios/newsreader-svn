// post_file.cpp : Defines the entry point for the console application.
//


#include <curl/curl.h>



int main(int argc, char* argv[])
{
	CURL *curl;
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	char namebuffer[] = "name buffer";
	long namelength = strlen(namebuffer);
	char buffer[] = "test buffer";
	char htmlbuffer[] = "<HTML>test buffer</HTML>";
	long htmlbufferlength = strlen(htmlbuffer);
	struct curl_forms forms[3];
	char file1[] = "D:\\wolk-folder\\curl\\post_file\\ReadMe.txt";
	char file2[] = "D:\\wolk-folder\\curl\\post_file\\ReadMe.txt";



	typedef /*CURL_EXTERN*/ CURL*(*Tcurl_easy_init)(void);
	typedef CURLcode (*Tcurl_easy_setopt)(CURL *, CURLoption , ...);
	typedef CURLFORMcode (*Tcurl_formadd)(struct curl_httppost **, struct curl_httppost **, ...);
	typedef CURLcode (*Tcurl_easy_perform) (CURL *curl);

	HMODULE hM = LoadLibrary( "libcurl-4.dll" );

	Tcurl_easy_init c_init = 0;
	Tcurl_easy_setopt c_set_opt = 0;
	Tcurl_formadd c_formadd = 0;
	Tcurl_easy_perform c_perform = 0;


	//c_init = (Tcurl_easy_init)GetProcAddress( hM , "curl_easy_init" );
	//c_set_opt = (Tcurl_easy_setopt)GetProcAddress( hM , "curl_easy_setopt" );
	//c_formadd = (Tcurl_formadd)GetProcAddress( hM , "curl_formadd" );
	//c_perform = (Tcurl_easy_perform)GetProcAddress( hM , "curl_easy_perform" );


	curl = curl_easy_init();
	//curl = c_init();

	CURLcode code = curl_easy_setopt(curl, CURLOPT_URL,"http://pigeon/upload.php");

	/* Now specify we want to POST data */
	code = curl_easy_setopt(curl, CURLOPT_POST, TRUE);

	/* add null character into htmlbuffer, to demonstrate that   transfers of buffers containing null characters actually work  */
	htmlbuffer[8] = '0';

	/* Add two file section using CURLFORM_ARRAY */
	forms[0].option = CURLFORM_FILE;
	forms[0].value  = file1;
	forms[1].option = CURLFORM_FILE;
	forms[1].value  = file2;
	forms[2].option  = CURLFORM_END;


	/* Add simple file section */

	//CURLFORMcode ret = c_formadd(&post, &last, CURLFORM_COPYNAME, "userfile",CURLFORM_ARRAY, forms, CURLFORM_END);

	char fn[] = "D:\\library\\svnindex.xsl";



	CURLFORMcode ret = curl_formadd(&post, &last, CURLFORM_COPYNAME, "userfile",   CURLFORM_FILE, fn , CURLFORM_CONTENTSLENGTH , strlen(fn)+1 ,  CURLFORM_END);
	code = curl_easy_perform(curl);
	return 0;
}

