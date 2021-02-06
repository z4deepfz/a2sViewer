#include "IO.h"

boost::asio::ip::udp::socket* psocket;
static boost::asio::deadline_timer* ptimer;
static boost::asio::io_context* pcontext;


static void create_context()
{
    pcontext = new boost::asio::io_context;
    ptimer = new boost::asio::deadline_timer(*pcontext);
}

static void clean_context()
{
    ptimer->cancel();
    if(ptimer != nullptr) {
        delete ptimer;
        ptimer = nullptr;
    }
    if(pcontext != nullptr) {
        delete pcontext;
        pcontext = nullptr;
    }
}

static void timeout_handler(const boost::system::error_code& error)
{
    std::cerr << "Timer Triggerred.";
    psocket->close();
    //clean_context();
}

void set_timeout(int timeout_time, boost::asio::ip::udp::socket* socket)
{
    create_context();
    psocket = socket;
    ptimer->expires_from_now(boost::posix_time::seconds(timeout_time));
    ptimer->async_wait(&timeout_handler);
    pcontext->run();
}

void cancel_timeout()
{
    ptimer->cancel();
    clean_context();
}
