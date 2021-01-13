#include "ChatServer.h"
#include <stdio.h>
#include "FdHandler.h"
#include "ConstantsEnum.h"
#include "EventSelector.h"
#include <sys/socket.h>

ChatServer* ChatServer::Start(EventSelector* sel, int port)
{
    //int ls, opt, res;
    //struct sockaddr_in addr;
}