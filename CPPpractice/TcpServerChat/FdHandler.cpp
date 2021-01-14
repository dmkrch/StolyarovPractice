#include "FdHandler.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <cerrno>

FdHandler::~FdHandler()
{
    if(own_fd)
        close(fd);
}