#include <service.hpp>

Service::Service()
    : m_work(m_ioService)
{
}


Service::~Service()
{
    stop();
}

bool Service::start()
{
    if (m_thread.get()) {
        return false;
    }

    m_thread.reset(new boost::thread(boost::bind(&Service::run, this)));

    return true;
}

void Service::run()
{
    m_ioService.run();
}

bool Service::stop()
{
    if (!m_thread.get())
    {
        return false;
    }

    m_ioService.stop();
    m_thread->join();

    return true;
}

boost::asio::io_service& Service::get()
{
    return m_ioService;
}


