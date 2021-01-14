#ifndef EVENTSELECTOR_SENTRY
#define EVENTSELECTOR_SENTRY

#include "FdHandler.h"

/* class that contains pointers to all objects of FdHandler */
class EventSelector
{
private:
    FdHandler** fd_array;
    int fd_array_len;
    int max_fd;
    bool quit_flag;

public:
    EventSelector() : fd_array(0), quit_flag(false) {}
    ~EventSelector();
    void Add(FdHandler* h);
    bool Remove(FdHandler* h);
    void BreakLoop() { quit_flag = true; }
    void Run();
};

#endif