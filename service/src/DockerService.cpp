//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/DockerService.h>
#include <fstream>

namespace AwsMock::Service {

    DockerService::DockerService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("DockerService")), _configuration(configuration) {
        Initialize();
    }

    void DockerService::Initialize() {

    }

    // curl --unix-socket /var/run/docker.sock --data-binary '@docker.tar.gz' -XPOST -H "Content-Type: application/octet-stream" http://localhost/v1.42/build
    long DockerService::BuildImage(const std::string &dockerFile, const std::string &tag) {
        poco_debug(_logger, "Build image request, dockerFile: " + dockerFile + " tag: " + tag);

        std::ifstream ifs(dockerFile, std::ios::binary);

        long size = ifs.tellg();
        ifs.seekg(0,  std::ios::beg);
        std::vector<char> buffer;
        buffer.reserve(size);
        ifs.read(buffer.data(), size);
        ifs.close();

        long status = 0;
        std::string url = "http://" + std::string(DOCKER_VERSION) + "/build?t=" + tag;

        struct curl_slist *headers = nullptr;
        //headers = curl_slist_append(headers, "Content-Type: application/gzip");

/*        curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, &buffer);
        CURLcode response = SendRequest((char *) url.c_str(), &status);
        curl_slist_free_all(headers);
        poco_debug(_logger, "Send to docker daemon, response: " + std::to_string(response));*/

        return status;
    }

    CURLcode DockerService::SendRequest(char *url, long *httpStatus) {

       /* curl_easy_setopt(client->curl, CURLOPT_URL, url);
        CURLcode response = curl_easy_perform(client->curl);
        if (httpStatus) {
            curl_easy_getinfo(client->curl, CURLINFO_RESPONSE_CODE, httpStatus);
        }
        curl_easy_reset(client->curl);

        return response;*/
    }
}