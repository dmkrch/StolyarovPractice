#ifndef SERVERUSER_H_SENTRY
#define SERVERUSER_H_SENTRY


#define MAX_USERS 10

struct UserLoginData
{
    char* login;
    char* password;
};

struct ServerUser
{
    char* name;
    struct UserLoginData data;
};


/* prints user information by name */
int CreateUserInfoByNameString(char* userName, char* bufferString);

#endif
