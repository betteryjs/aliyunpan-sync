//
// Created by yjs on 23-7-22.
//

#ifndef ALIYUNPAN_SYNC_CONFIG_H
#define ALIYUNPAN_SYNC_CONFIG_H

#include <string>
#include <vector>

class Config {
public:
    std::string client_id;  // 应用标识，创建应用时分配的 appId
    std::string client_secret; // 应用密钥，创建应用时分配的 secret
    std::string refresh_token; //  用来刷新 access_token，默认 90 天有效期。刷新后，返回新的 refresh_token。
    std::string code;          // 授权码
    std::string grant_type;    //  身份类型 authorization_code 或 refresh_token
    std::string access_token;  // 用来获取用户信息的 access_token。 刷新后，旧 access_token 不会立即失效。
    std::vector<std::string>  removeDir;
public:

    Config(const std::string &client_id, const std::string &client_secret);

    Config();

public:

    int updateAccessToken();

    int updateRefreshToken();


};


#endif //ALIYUNPAN_SYNC_CONFIG_H
