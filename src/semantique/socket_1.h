#ifndef __SOCKET_1_H__
#define __SOCKET_1_H__

void writeSocket(int fd, FCGI_Header *h, unsigned int len);

void writeLen(int len, char **p);

int addNameValuePair(FCGI_Header *h, char *name, char *value);

void sendGetValue(int fd);

void sendBeginRequest(int fd,unsigned short requestId,unsigned short role,unsigned char flags);

void sendAbortRequest(int fd,unsigned short requestId);

void sendWebData(int fd,unsigned char type,unsigned short requestId,char *data,unsigned int len);

static int createSocket(int port);

void readSocket(int fd);

int getResultFromPHPInterpreter(char **result, char *contentType, int *contentLength, char *path, char *method, char **forFreeMessageBody);


#endif