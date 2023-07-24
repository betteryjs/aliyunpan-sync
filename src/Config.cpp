//
// Created by yjs on 23-7-22.
//

#include "Config.h"


static std::string LeftTrim(const char *source) {
    std::string copy(source);
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](unsigned char ch) { return !::isspace(ch); }));
    return copy;
}

static std::string RightTrim(const char *source) {
    std::string copy(source);
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](unsigned char ch) { return !::isspace(ch); }).base(),
               copy.end());
    return copy;
}

static std::string Trim(const char *source) {
    return LeftTrim(RightTrim(source).c_str());
}

static std::string LeftTrimQuotes(const char *source) {
    std::string copy(source);
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](int ch) { return !(ch == '"'); }));
    return copy;
}

static std::string RightTrimQuotes(const char *source) {
    std::string copy(source);
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](int ch) { return !(ch == '"'); }).base(), copy.end());
    return copy;
}

static std::string TrimQuotes(const char *source) {
    return LeftTrimQuotes(RightTrimQuotes(source).c_str());
}


Config::Config() {
    fstream jsonConfig;
    json config;
    if (fs::exists("config.json")) {
        jsonConfig.open("config.json", ios::in);
        jsonConfig >> config;
        this->refresh_token = config["refresh_token"].get<string>();
        this->client_id = config["client_id"].get<string>();
        this->client_secret = config["client_secret"].get<string>();
        this->code = config["code"].get<string>();
        this->grant_type = config["grant_type"].get<string>();
        this->access_token = config["access_token"].get<string>();
        this->removeDir = config["removeDir"].get<std::vector<std::string>>();
        this->drive_id = config["drive_id"].get<std::string>();

        spdlog::info("config.json loads success !");
        spdlog::info("access_token {}", this->access_token);
    } else {
        spdlog::error("config.json not find");

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

int Config::setDriveId(const string &driverId) {
    if (!driverId.empty()) {

        this->drive_id = driverId;
        this->saveConfig();
        spdlog::info("driverId  set success !");
        spdlog::info("save config.json  success !");
        spdlog::info("driverId  is {}", driverId);
        return 0;
    }
    spdlog::error("driverId  set error");

    return 1;
}

int Config::saveConfig() {
    json  dict;
    dict["refresh_token"]= this->refresh_token;
    dict["client_id"]= this->client_id;
    dict["code"]= this->code;
    dict["grant_type"]= this->grant_type;
    dict["access_token"]= this->access_token;
    dict["removeDir"]= this->removeDir;
    dict["client_secret"]= this->client_secret;

    fstream fconfig;
    fconfig.open("config.json", ios::out);

    fconfig << dict;

    spdlog::info("oldDirs.json save success !");
    fconfig.close();


    return 0;
}





