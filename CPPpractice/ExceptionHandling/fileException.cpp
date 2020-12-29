#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "fileException.h"

FileException::FileException(const char* fName, const char* comnt)
{
    errorCode = errno;
    fileName = strdup1(fName);
    comment = strdup1(comnt);
}

FileException::FileException(const FileException& other)
{
    errorCode = other.errorCode;
    fileName = strdup1(other.fileName);
    comment = strdup1(other.comment);
}

FileException::~FileException()
{
    delete[] fileName;
    delete[] comment;
}

char* FileException::strdup1(const char* str)
{
    char* res = new char[strlen(str)+1];
    strcpy(res, str);
    return res;
}