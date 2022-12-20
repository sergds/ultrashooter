#include "HTTP.h"
#if !defined(PLATFORM_WEB)
#include "curl/curl.h"
#include "curl/easy.h"
#endif
#include "globals.h"
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
} 

HTTP::HTTP() {
}

std::string HTTP::GET(std::string url) {
#if !defined(PLATFORM_WEB)
    std::string readBuffer;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curlerr = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if(curlerr == CURLE_OK) {
        return readBuffer;
    }
    readBuffer = "CURL ERROR";
    return readBuffer;
#else
    return "NETWORKING DISABLED ON WEB BUILD!!!";
#endif
}

HTTP::~HTTP() {
    //curl_easy_cleanup(curl);
}