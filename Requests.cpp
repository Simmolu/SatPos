#include "Requests.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) 
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



Requests::Requests() {

    carl= curl_easy_init();
    satAPIKey = "&apiKey=M74XYK-3X82GL-5PRATH-5D91";
    satURL = "https://api.n2yo.com/rest/v1/satellite/";

    if (carl) {
        curl_easy_setopt(carl, CURLOPT_WRITEFUNCTION, WriteCallback);
     
    }
}

string Requests::SatTLE(string ID) {

    requestURL = satURL + "tle/" + ID + satAPIKey;

    curl_easy_setopt(carl, CURLOPT_URL, requestURL.c_str());
    curl_easy_setopt(carl, CURLOPT_WRITEDATA, &readBuffer);


    res = curl_easy_perform(carl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return " ";
    }

    return readBuffer;
}

string Requests::SatPos(string satID, string latitude, string longitude)

{
    requestURL = satURL +
        "positions/"
        + satID + "/"
        + latitude + "/"
        + longitude 
        + "/1/1/"
        + satAPIKey;

    curl_easy_setopt(carl, CURLOPT_URL, requestURL.c_str());
    curl_easy_setopt(carl, CURLOPT_WRITEDATA, &readBuffer);


    res = curl_easy_perform(carl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return " ";
    }

    return readBuffer;
}

string Requests::GeoAboveMe(string latitude, string longitude)
{
    requestURL = satURL +
        "above/"
        + latitude + "/"
        + longitude
        + "/90/10/"
        + satAPIKey;
    
    curl_easy_setopt(carl, CURLOPT_URL, requestURL.c_str());
    curl_easy_setopt(carl, CURLOPT_WRITEDATA, &readBuffer);


    res = curl_easy_perform(carl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return " ";
    }

    return readBuffer;
}


void Requests::cleanup() {
    curl_easy_cleanup(carl);
}