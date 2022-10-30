#include <nlohmann/json.hpp>
#include <fstream>
#include <ios>
using json = nlohmann::json;

class UserData {
public:
    int hiscore = 0;
    std::string name = "Unnamed";
public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UserData, hiscore, name)
};