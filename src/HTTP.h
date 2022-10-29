#include "fix_winapi_conflicts.h"
#include "curl/curl.h"
#include <string>

class HTTP {
public:
    HTTP();
    ~HTTP();
    std::string GET(std::string url);
private:
    CURL* curl;
    CURLcode curlerr;
};