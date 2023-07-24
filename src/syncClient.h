//
// Created by yjs on 23-7-24.
//

#ifndef TEST_SYNCCLIENT_H
#define TEST_SYNCCLIENT_H

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cpr/cpr.h>
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"


using namespace std;

using json = nlohmann::json;




class syncClient {
public:
    json getSpaceInfo();
    json getDriveInfo();
    json  getFileList();
    json  getFileListOpenapi();

    void checkAllDir(const fs::path &dirs);


};


#endif //TEST_SYNCCLIENT_H
