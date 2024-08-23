
#include <awsmock/service/ssm/SSMHandler.h>

namespace AwsMock::Service {

    boost::beast::http::response<boost::beast::http::dynamic_body> SSMHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "SSM POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::SSMClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            switch (clientCommand.command) {

                case Dto::Common::SSMCommandType::PUT_PARAMETER: {

                    Dto::SSM::PutParameterRequest ssmRequest;
                    ssmRequest.FromJson(clientCommand.payload);
                    ssmRequest.region = clientCommand.region;

                    Dto::SSM::PutParameterResponse ssmResponse = _ssmService.PutParameter(ssmRequest);

                    log_info << "Parameter created, name: " << ssmRequest.name << " version: " << ssmResponse.version;
                    return SendOkResponse(request, ssmResponse.ToJson());
                }

                case Dto::Common::SSMCommandType::GET_PARAMETER: {

                    Dto::SSM::GetParameterRequest ssmRequest;
                    ssmRequest.FromJson(clientCommand.payload);
                    ssmRequest.region = clientCommand.region;

                    Dto::SSM::GetParameterResponse ssmResponse = _ssmService.GetParameter(ssmRequest);

                    log_info << "Parameter found, name: " << ssmRequest.name;
                    return SendOkResponse(request, ssmResponse.ToJson());
                }

                case Dto::Common::SSMCommandType::DELETE_PARAMETER: {

                    Dto::SSM::DeleteParameterRequest ssmRequest;
                    ssmRequest.FromJson(clientCommand.payload);
                    ssmRequest.region = clientCommand.region;

                    _ssmService.DeleteParameter(ssmRequest);

                    log_info << "Parameter deleted, name: " << ssmRequest.name;
                    return SendOkResponse(request);
                }

                default:
                case Dto::Common::SSMCommandType::UNKNOWN: {
                    log_error << "Unimplemented command called";
                    throw Core::ServiceException("Unimplemented command called");
                }
            }
        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::JsonException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (std::exception &exc) {
            log_error << exc.what();
            return SendInternalServerError(request, exc.what());
        }
    }
}// namespace AwsMock::Service
