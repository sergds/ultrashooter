#include <string>
#include <nlohmann/json.hpp>

class Filesystem {
public:
    Filesystem();
    std::string GetFileName(std::string wantedfile);
};