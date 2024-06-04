
#include <awsmock/service/common/AbstractDomainSocket.h>

namespace AwsMock::Service {

    AbstractDomainSocket::AbstractDomainSocket(boost::asio::io_context &ioc, const std::string &socketPath) : _socketPath(socketPath), _acceptor(boost::asio::make_strand(ioc)) {
    }

    void AbstractDomainSocket::Run() {

        boost::asio::io_service ioService;

        ::unlink(_socketPath.c_str());
        stream_protocol::endpoint ep(_socketPath);
        stream_protocol::acceptor acceptor(ioService, ep);
        stream_protocol::socket socket(ioService);
        _acceptor.accept(socket);
    }

}// namespace AwsMock::Service
