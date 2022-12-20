#include "fix_winapi_conflicts.h"
#if !defined(PLATFORM_WEB)
#include "curl/curl.h"
#endif
#include <string>

class HTTP {
public:
    HTTP();
    ~HTTP();
    std::string GET(std::string url);
private:
#if !defined(PLATFORM_WEB)
    CURL* curl;
    CURLcode curlerr;
#endif
};