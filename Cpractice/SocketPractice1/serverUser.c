#include <string.h>
#include <stdio.h>
#include "serverUser.h"

#define AMOUNT_OF_USERS 4

/* users of server. Lets pretend that this array is configurated with conf file */
struct ServerUser ServerUsers[AMOUNT_OF_USERS] = {
    {"Max\n", {"maxPshonka2005", "minecraft21045"}},
    {"Sasha\n", {"pison", "ytrewq22"}},
    {"Dima\n", {"superLogin", "sashaloh"}},
    {"Antoha\n", {"anton@gmail.com", "qwerty123"}}
};


/* prints user information by name */
int CreateUserInfoByNameString(char* userName, char* bufferString)
{
    for (int i = 0; i < AMOUNT_OF_USERS; ++i)
    {
        if (strcmp(ServerUsers[i].name, userName) == 0)
        {
            /* if founded user */
            snprintf(bufferString, 100, "<server>: name: %slogin: %s\r\npassword: %s\r\n\n", ServerUsers[i].name, ServerUsers[i].data.login, ServerUsers[i].data.password);
            return 0;
        }
        else
        {
            /* if no such users */
            snprintf(bufferString, 100, "<server> no such users\n\n");
        }
    }

    return -1;
}
