/*
  Copyright (c) 2019 Sogou, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

	  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  Author: Xie Han (xiehan@sogou-inc.com;63350856@qq.com)
*/

#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "workflow/HttpMessage.h"
#include "workflow/HttpUtil.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/WFFacilities.h"
#include <nlohmann/json.hpp>
#include <iostream>


using namespace std;

using json = nlohmann::json;


#define REDIRECT_MAX    5
#define RETRY_MAX       2

void wget_callback(WFHttpTask *task)
{
	protocol::HttpRequest *req = task->get_req();
	protocol::HttpResponse *resp = task->get_resp();
	int state = task->get_state();
	int error = task->get_error();

	switch (state)
	{
	case WFT_STATE_SYS_ERROR:
		fprintf(stderr, "system error: %s\n", strerror(error));
		break;
	case WFT_STATE_DNS_ERROR:
		fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
		break;
	case WFT_STATE_SSL_ERROR:
		fprintf(stderr, "SSL error: %d\n", error);
		break;
	case WFT_STATE_TASK_ERROR:
		fprintf(stderr, "Task error: %d\n", error);
		break;
	case WFT_STATE_SUCCESS:
		break;
	}

//	if (state != WFT_STATE_SUCCESS)
//	{
//		fprintf(stderr, "Failed. Press Ctrl-C to exit.\n");
//		return;
//	}

	std::string name;
	std::string value;

	/* Print request. */
	fprintf(stderr, "%s %s %s\r\n", req->get_method(),
									req->get_http_version(),
									req->get_request_uri());

	protocol::HttpHeaderCursor req_cursor(req);

	while (req_cursor.next(name, value))
		fprintf(stderr, "%s: %s\r\n", name.c_str(), value.c_str());
	fprintf(stderr, "\r\n");

	/* Print response header. */
	fprintf(stderr, "%s %s %s\r\n", resp->get_http_version(),
									resp->get_status_code(),
									resp->get_reason_phrase());

	protocol::HttpHeaderCursor resp_cursor(resp);

	while (resp_cursor.next(name, value))
		fprintf(stderr, "%s: %s\r\n", name.c_str(), value.c_str());
	fprintf(stderr, "\r\n");

	/* Print response body. */
	const void *body;
	size_t body_len;
//    ostringstream c;
    string res;
	resp->get_parsed_body(&body, &body_len);
    void* pChar = const_cast<void*>(body);
    const char *p = static_cast<const char*>(pChar);

//    cout << string (p)<<endl;
    auto j=json::parse(p);
    cout <<"res is : " <<j<<endl;

//	fwrite(body, 1, body_len, stdout);
//    fflush(stdout);

//	string res=string (static_cast<const char*>(const_cast<void *>(body)));
//    auto j=json::parse(static_cast<const char*>(const_cast<void *>(body)));
    cout << body;

//    return j;

}


void wget_callback2(WFHttpTask *task)
{
    protocol::HttpRequest *req = task->get_req();
    protocol::HttpResponse *resp = task->get_resp();
    int state = task->get_state();
    if (state==WFT_STATE_SUCCESS && string(resp->get_status_code())=="200"){

        const void *body;
        size_t body_len;

        resp->get_parsed_body(&body, &body_len);
        void* pChar = const_cast<void*>(body);
        const char *p = static_cast<const char*>(pChar);
        auto j=json::parse(p);
        cout <<"res is : " <<j<<endl;

    }





}

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

json getSpaceInfo(){

    signal(SIGINT, sig_handler);

    WFHttpTask *task;





    std::string url="https://openapi.alipan.com/adrive/v1.0/user/getSpaceInfo";

    task = WFTaskFactory::create_http_task(url, REDIRECT_MAX, RETRY_MAX,
                                           wget_callback2);
    protocol::HttpRequest *req = task->get_req();
    task->get_req()->set_method("POST");
    req->add_header_pair("Content-Type", "application/json");
    req->add_header_pair("Authorization", "Bearer eyJraWQiOiJLcU8iLCJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiI5YTNhMzk0N2NkYTY0MTQ3YWNmM2NiNjM3NDQ5OWE2MyIsImF1ZCI6Ijc2OTE3Y2NjY2Q0NDQxYzM5NDU3YTA0ZjYwODRmYjJmIiwiaXNzIjoiaHR0cHM6Ly9vcGVuLmFsaXl1bmRyaXZlLmNvbSIsImV4cCI6MTY5MDE4MjA3NywiaWF0IjoxNjkwMTc0Mjc3fQ.mnTFc4mHbvHPgw1-fYMPJi5dnt3VImO7CdEQIiFerak");

    task->start();
    wait_group.wait();

}


int main(int argc, char *argv[])
{


//    signal(SIGINT, sig_handler);
//    WFHttpTask *task;
//
//
//
//
//
//    std::string url="https://openapi.alipan.com/adrive/v1.0/user/getSpaceInfo";
//
//    task = WFTaskFactory::create_http_task(url, REDIRECT_MAX, RETRY_MAX,
//                                           wget_callback);
//    protocol::HttpRequest *req = task->get_req();
//    task->get_req()->set_method("POST");
//    req->add_header_pair("Content-Type", "application/json");
//    req->add_header_pair("Authorization", "Bearer eyJraWQiOiJLcU8iLCJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiI5YTNhMzk0N2NkYTY0MTQ3YWNmM2NiNjM3NDQ5OWE2MyIsImF1ZCI6Ijc2OTE3Y2NjY2Q0NDQxYzM5NDU3YTA0ZjYwODRmYjJmIiwiaXNzIjoiaHR0cHM6Ly9vcGVuLmFsaXl1bmRyaXZlLmNvbSIsImV4cCI6MTY5MDE4MjA3NywiaWF0IjoxNjkwMTc0Mjc3fQ.mnTFc4mHbvHPgw1-fYMPJi5dnt3VImO7CdEQIiFerak");
//
//    task->start();
//
//	wait_group.wait();
//    sleep(2);
getSpaceInfo();
	return 0;
}

