#include "fix_winapi_conflicts.h"
#if US_NETWORKING_ENABLED
#include "curl/curl.h"
#endif
#include <string>

class HTTP {
public:
    HTTP();
    ~HTTP();
    std::string GET(std::string url);
private:
#if US_NETWORKING_ENABLED
    CURL* curl;
    CURLcode curlerr;
#endif
};