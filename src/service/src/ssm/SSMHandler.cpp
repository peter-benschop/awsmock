
#include <awsmock/service/ssm/SSMHandler.h>

namespace AwsMock::Service {

    boost::beast::http::response<boost::beast::http::dynamic_body> SSMHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "SSM POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::SSMClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        switch (clientCommand.command) {

            case Dto::Common::SSMCommandType::PUT_PARAMETER: {

                Dto::SSM::PutParameterRequest ssmRequest;
                ssmRequest.FromJson(clientCommand.payload);
                ssmRequest.region = clientCommand.region;

                Dto::SSM::PutParameterResponse kmsResponse;// = _ssmService.PutParameter(ssmRequest);

                log_info << "Parameter created, name: " << ssmRequest.name << " version: " << kmsResponse.version;
                return SendOkResponse(request, kmsResponse.ToJson());
            }

            default:
            case Dto::Common::SSMCommandType::UNKNOWN: {
                log_error << "Unimplemented command called";
                throw Core::ServiceException("Unimplemented command called");
            }
        }
    }
}// namespace AwsMock::Service
