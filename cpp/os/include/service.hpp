#pragma once

#include <boost/thread.hpp>
#include <boost/asio.hpp>

class Service
{
public:
    Service();
    ~Service();
    bool start();
    bool stop();
    boost::asio::io_service& get();

private:
    void run();
    boost::asio::io_service m_ioService;
    std::shared_ptr<boost::thread> m_thread;
    boost::asio::io_service::work m_work;
};
