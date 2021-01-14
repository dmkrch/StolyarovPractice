#ifndef CHATSERVER_SENTRY
#define CHATSERVER_SENTRY

#include "FdHandler.h"
#include "EventSelector.h"
#include "ConstantsEnum.h"

/* single session of chat (user) */
class ChatSession : private FdHandler
{
private:    
    friend class ChatServer; /* functlty opened for ChatServer */
    char buffer[max_line_length + 1];
    int buf_used;
    bool ignoring;
    char* name; 
    ChatServer* the_master;
    
    ChatSession(ChatServer* a_master, int fd);
    ~ChatSession();
    void Send(const char* msg);
    virtual void Handle(bool r, bool w);
    void ReadAndIgnore();
    void ReadAndCheck();
    void CheckLines();
    void ProcessLine(const char* str);
};



/* class for server of chat */
class ChatServer : public FdHandler
{
private:
    EventSelector* the_selector;

    struct item /* list of sessions */
    {
        ChatSession* s;
        item* next;
    };
    
    item* first;  /* head of list */
    ChatServer(EventSelector* sel, int fd); /* constructor */
    
public:
    ~ChatServer();
    static ChatServer* Start(EventSelector* sel, int port);
    void RemoveSession(ChatSession* s);
    void SendAll(const char* msg, ChatSession* except = 0);
private:
    virtual void Handle(bool r, bool w);
};


#endif