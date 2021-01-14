#include "ChatServer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


/* REALISATIONS OF ChatServer */
ChatServer* ChatServer::Start(EventSelector* sel, int port)
{
    int ls, opt, res;
    struct sockaddr_in addr;
    ls = socket(AF_INET, SOCK_STREAM, 0);

    if (ls == -1)
        return 0;

    opt = 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    res = bind(ls, (struct sockaddr*) &addr, sizeof(addr));

    if (res == -1)
        return 0;
    res = listen(ls, qlen_for_listen);

    if (res == -1)
        return 0;

    return new ChatServer(sel, ls);
}

ChatServer::ChatServer(EventSelector* sel, int fd)
    : FdHandler(fd, true), the_selector(sel), first(0)
{
    the_selector->Add(this);
}

ChatServer::~ChatServer()
{
    while(first)
    {
        item* tmp = first;
        first = first->next;
        the_selector->Remove(tmp->s);
        delete tmp->s;
        delete tmp;
    }
    the_selector->Remove(this);
}


/* When listen socket is ready - we need to accept
the connection via accept and create the instance 
of chatSession */
void ChatServer::Handle(bool r, bool w)
{
    if (!r)
        return; // must not happen
    
    int sd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    sd = accept(GetFd(), (struct sockaddr*) &addr, &len);
    if(sd == -1)
        return;
    item* p = new item;
    p->next = first;
    p->s = new ChatSession(this, sd);
    first = p;
    the_selector->Add(p->s);
}


void ChatServer::RemoveSession(ChatSession* s)
{
    the_selector->Remove(s);
    item** p;
    
    for(p = &first; *p; p = &((*p)->next))
    {
        if ((*p)->s == s)
        {
            item* tmp = *p;
            *p = tmp->next;
            delete tmp->s;
            delete tmp;
            return;
        }
    }
}

/* sends message to all sessions of server except session 'except' */
void ChatServer::SendAll(const char* msg, ChatSession* except)
{
    item *p;
    
    for (p = first; p; p = p->next)
        if (p->s != except)
            p->s->Send(msg);
}



/* REALISATIONS OF ChatSession */


/* sends message to session */
void ChatSession::Send(const char* msg)
{
    write(GetFd(), msg, strlen(msg));
}

ChatSession::ChatSession(ChatServer* a_master, int fd)
    : FdHandler(fd, true), buf_used(0), ignoring(false),
    name(0), the_master(a_master)
{
    Send("Your name please: ");
}

ChatSession::~ChatSession()
{
    if (name)
        delete[] name;
}
