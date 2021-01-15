#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cerrno>

#include "EventSelector.h"
#include "ChatServer.h"

static int port = 7777;

int main()
{
    EventSelector* selector = new EventSelector;
    ChatServer* serv = ChatServer::Start(selector, port);
    if (!serv)
    {
        perror("server");
        return 1;
    }
    selector->Run();
    return 0;   
}