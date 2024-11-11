#ifndef REQUESTS_H
#define REQUESTS_H
#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

class Requests 
{
private:
	string satAPIKey;
	string satURL;
	string requestURL;
	CURL* carl;
	string readBuffer;
	CURLcode res;
public:

	Requests();
	
	
	string SatTLE(string satID);
	string SatPos(string satID, string latitude, string longitude);
	string GeoAboveMe(string latitude, string longitude);

	void cleanup();


};






#endif