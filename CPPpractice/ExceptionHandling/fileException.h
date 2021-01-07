#ifndef FILEEXCEPTIONS_SENTRY
#define FILEEXCEPTIONS_SENTRY

class FileException
{
private:
    int errorCode;
    char* fileName;
    char* comment;

public:
    FileException(const char* fName, const char* comment);
    FileException(const FileException& other);
    ~FileException();

    const char* GetName() const { return fileName; }
    const char* GetComment() const { return comment; }
    int GetErrno() const { return errorCode; }
private:   
    /* this function returns new string according to str */
    static char* strdup1(const char* str);
};

#endif