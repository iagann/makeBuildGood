#include "FileUtil.h"

#include <iterator>
#include <iostream>
#include <sstream>

bool FileUtil::save(const std::string& filename, std::stringstream& ss) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << ss.str();
    outFile.close();
    return true;
}

bool FileUtil::load(const std::string& filename, std::stringstream& ss) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }
    std::string content;
    std::getline(inFile, content, '\0'); // Read entire file into string
    ss << content;
    inFile.close();
    return true;
}

bool FileUtil::load(const std::string& filename, std::vector<std::string>& v) {
    std::stringstream ss;
    if (!load(filename, ss))
        return false;
    v = stringStreamToVector(ss);
    return true;
}

std::vector<std::string> FileUtil::stringStreamToVector(std::stringstream& ss) {
    std::vector<std::string> words;
    std::string word;
    while (std::getline(ss, word, '\n')) { // Use a specific delimiter if needed
        words.push_back(word);
    }
    return words;
}

bool FileUtil::parseDouble(const std::string& string_value, double& parsed_value) {
    std::stringstream ss(string_value);
    ss >> parsed_value;
    return !(ss.fail());
}

bool FileUtil::parseInt(const std::string& string_value, int& parsed_value) {
    std::stringstream ss(string_value);
    ss >> parsed_value;
    return !(ss.fail());
}