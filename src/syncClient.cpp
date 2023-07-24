//
// Created by yjs on 23-7-24.
//

#include "syncClient.h"
#include "Config.h"


Config config;






json syncClient::getSpaceInfo() {
    std::string url = "https://openapi.alipan.com/adrive/v1.0/user/getSpaceInfo";

    cpr::Response response = cpr::Post(
            cpr::Url{url},
            cpr::Header{
                    {"Content-Type", "application/json"}
            },
            cpr::Bearer{config.access_token}
    );
    if (response.status_code == 200) {
        spdlog::info("get personal_space_info success !");
        spdlog::info("personal_space_info is {}", response.text);
        return json::parse(response.text);
    }

}


json syncClient::getDriveInfo() {
    std::string url = "https://openapi.alipan.com/adrive/v1.0/user/getDriveInfo";

    cpr::Response response = cpr::Post(
            cpr::Url{url},
            cpr::Header{
                    {"Content-Type", "application/json"}
            },
            cpr::Bearer{config.access_token}
    );
    if (response.status_code == 200) {
        spdlog::info("get getDriveInfo success !");
        spdlog::info("getDriveInfo is {}", response.text);
        json jsonData=json::parse(response.text);
        config.setDriveId(jsonData.at("default_drive_id").get<std::string>());
        return jsonData;
    }

}


json syncClient::getFileListOpenapi() {
    std::string url = "https://openapi.alipan.com/adrive/v1.0/openFile/list";

    json body = json{
            {"drive_id", "438817"},
            {"parent_file_id", "root"},
            {"order_by", "name"}
    };

    cpr::Response response = cpr::Post(
            cpr::Url{url},
            cpr::Header{
                    {"Content-Type", "application/json"},
            },
            cpr::Bearer{config.access_token},
            cpr::Body{body.dump()}

    );
    if (response.status_code == 200) {
        spdlog::info("get getFileList success !");
        spdlog::info("getFileList is {}", response.text);
        return json::parse(response.text);
    }



}


json syncClient::getFileList() {
    return json{};

}


void syncClient::checkAllDir(const fs::path &dirs) {
    json dict;
    vector<string> removeDirs=config.removeDir;
    fs::directory_iterator dictsIterator(dirs);
    for (fs::directory_entry dir:dictsIterator)
    {
        if (fs::is_directory(dir) && std::find(removeDirs.begin(), removeDirs.end(), dir.path().filename()) == removeDirs.end()){
//            cout << dir.path()<<endl;
            dict[dir.path().string()] = true;
        }

    }
    fstream jsonDirs;
    jsonDirs.open("oldDirs.json",ios::out);
    jsonDirs<< dict;
    spdlog::info("oldDirs.json save success !");
    jsonDirs.close();

}

