#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <vector>

class FileUtil {
public:
    static bool save(const std::string& filename, std::stringstream& ss);
    static bool load(const std::string& filename, std::stringstream& ss);

    static bool load(const std::string& filename, std::vector<std::string>& v);

    static bool parseDouble(const std::string& string_value, double& parsed_value);
    static bool parseInt(const std::string& string_value, int& parsed_value);
private:
    static std::vector<std::string> stringStreamToVector(std::stringstream& ss);
};