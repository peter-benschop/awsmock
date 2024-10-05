//
// Created by vogje01 on 10/5/24.
//

#ifndef AWSMOCK_CORE_THREAD_POOL_H
#define AWSMOCK_CORE_THREAD_POOL_H

/*#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/beast/core.hpp>
//#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/detail/thread_group.hpp>
*/
// https://gist.github.com/autosquid/c5e5b3964524130d1c4d
/*namespace AwsMock::Core {

    typedef std::unique_ptr<boost::asio::io_service::work> asio_worker;

    // the actual thread pool
    struct ThreadPool {

        explicit ThreadPool(size_t threads) : service(), working(new asio_worker::element_type(service)) {

            // Capture SIGINT and SIGTERM to perform a clean shutdown
            boost::asio::signal_set signals(service, SIGINT, SIGTERM);
            signals.async_wait(
                    [&](boost::beast::error_code const &, int) {
                        // Stop the `io_context`. This will cause `run()` to return immediately, eventually
                        // destroying the `io_context` and all the sockets in it.
                        log_info << "Manager stopped on signal";
                        working.reset();//allow run() to exit
                        g.join_all();
                        service.stop();
                    });


            for (std::size_t i = 0; i < threads; ++i) {
                auto worker = [ObjectPtr = &(this->service)] { return ObjectPtr->run(); };
                g.add_thread(new boost::thread(worker));
            }
        }

        template<class F>
        void enqueue(F f) {
            service.post(f);
        }

        ~ThreadPool() {
            working.reset();//allow run() to exit
            g.join_all();
            service.stop();
        }

      private:

        boost::asio::io_service service;//< the io_service we are wrapping
        asio_worker working{};
        boost::thread_group g;//< need to keep track of threads so we can join them
    };
}// namespace AwsMock::Core
 */
#endif//AWSMOCK_CORE_THREAD_POOL_H
