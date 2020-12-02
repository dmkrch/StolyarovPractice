#include <string.h>
#include <stdio.h>
#include "serverUser.h"

#define MAX_USERS 10

/* users of server. Lets pretend that this array is configurated with conf file */
struct ServerUser ServerUsers[MAX_USERS] = {
    {"Max", {"maxPshonka2005", "minecraft21045"}},
    {"Sasha", {"pison", "ytrewq22"}},
    {"Dima", {"superLogin", "sashaloh"}},
    {"Antoha", {"anton@gmail.com", "qwerty123"}}
};


/* prints user information by name */
void PrintUserInfoByName(char* name)
{
    for (int i = 0; i < MAX_USERS; ++i)
    {
        if (strcmp(ServerUsers[i].name, name) == 0)
        {
            printf("name: %s\r\nlogin: %s\r\npassword: %s\r\n", ServerUsers[i].name, ServerUsers[i].data.login, ServerUsers[i].data.password);
            return;
        }
    }

    printf("no such users: %s\r\n", name);
}
