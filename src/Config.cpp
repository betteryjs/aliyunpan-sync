//
// Created by yjs on 23-7-22.
//

#include "Config.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;


//std::string Config::client_id;
//std::string Config::client_secret;
//std::string Config::refresh_token;
//std::string Config::code;
//std::string Config::grant_type;
//std::string Config::access_token;


static std::string LeftTrim(const char* source)
{
    std::string copy(source);
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](unsigned char ch) { return !::isspace(ch); }));
    return copy;
}

static std::string RightTrim(const char* source)
{
    std::string copy(source);
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](unsigned char ch) { return !::isspace(ch); }).base(), copy.end());
    return copy;
}

static std::string Trim(const char* source)
{
    return LeftTrim(RightTrim(source).c_str());
}

static std::string LeftTrimQuotes(const char* source)
{
    std::string copy(source);
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](int ch) { return !(ch == '"'); }));
    return copy;
}

static std::string RightTrimQuotes(const char* source)
{
    std::string copy(source);
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](int ch) { return !(ch == '"'); }).base(), copy.end());
    return copy;
}

static std::string TrimQuotes(const char* source)
{
    return LeftTrimQuotes(RightTrimQuotes(source).c_str());
}


Config::Config() {
    fstream jsonConfig;
    json  config;
    if(fs::exists("config.json")){
        jsonConfig.open("config.json",ios::in);
        jsonConfig>> config;
        this->refresh_token=config["refresh_token"].get<string>();
        this->client_id=config["client_id"].get<string>();
        this->client_secret=config["client_secret"].get<string>();
        this->code=config["code"].get<string>();
        this->grant_type=config["grant_type"].get<string>();
        this->access_token=config["access_token"].get<string>();
        this->removeDir=config["removeDir"].get<std::vector<std::string>>();
    }
    jsonConfig.close();



}

Config::Config(const std::string &client_id, const std::string &client_secret) {

}

int Config::updateAccessToken() {
    return 0;
}

int Config::updateRefreshToken() {
    return 0;
}



