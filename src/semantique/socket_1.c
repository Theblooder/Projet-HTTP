#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "fastcgi.h"
#include "socket_1.h"	

// =========================================================================================================== //
void writeSocket(int fd,FCGI_Header *h,unsigned int len)
{
	int w;

	h->contentLength=htons(h->contentLength);
	h->paddingLength=htons(h->paddingLength);


	while (len) {
	// try to write
		do {
			w = write(fd, h, len);
		} while (w == -1 && errno == EINTR);
	len-=w;
	}
}

// =========================================================================================================== //
void writeLen(int len, char **p) {
	if (len > 0x7F ) {
		*((*p)++)=(len>>24)&0x7F;
		*((*p)++)=(len>>16)&0xFF;
		*((*p)++)=(len>>8)&0xFF;
		*((*p)++)=(len)&0xFF;
	} else *((*p)++)=(len)&0x7F;
}

// =========================================================================================================== //
int addNameValuePair(FCGI_Header *h,char *name,char *value)
{
	char *p;
	unsigned int nameLen=0,valueLen=0;

	if (name) nameLen=strlen(name);
	if (value) valueLen=strlen(value);

	if ((valueLen > FASTCGIMAXNVPAIR) || (valueLen > FASTCGIMAXNVPAIR) ) return -1;
	if ((h->contentLength+((nameLen>0x7F)?4:1)+((valueLen>0x7F)?4:1)) > FASTCGILENGTH ) return -1;

	p=(h->contentData)+h->contentLength;
	writeLen(nameLen,&p);
	writeLen(valueLen,&p);
	strncpy(p,name,nameLen);
	p+=nameLen;
	if (value) strncpy(p,value,valueLen);
	h->contentLength+=nameLen+((nameLen>0x7F)?4:1);
	h->contentLength+=valueLen+((valueLen>0x7F)?4:1);

	return 0;
}
// =========================================================================================================== //

void sendGetValue(int fd)
{
FCGI_Header h;

	h.version=FCGI_VERSION_1;
	h.type=FCGI_GET_VALUES;
	h.requestId=htons(FCGI_NULL_REQUEST_ID);
	h.contentLength=0;
	h.paddingLength=0;
	addNameValuePair(&h,FCGI_MAX_CONNS,NULL);
	addNameValuePair(&h,FCGI_MAX_REQS,NULL);
	addNameValuePair(&h,FCGI_MPXS_CONNS,NULL);
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
void sendBeginRequest(int fd,unsigned short requestId,unsigned short role,unsigned char flags)
{
FCGI_Header h;
FCGI_BeginRequestBody *begin;

	h.version=FCGI_VERSION_1;
	h.type=FCGI_BEGIN_REQUEST;
	h.requestId=htons(requestId);
	h.contentLength=sizeof(FCGI_BeginRequestBody);
	h.paddingLength=0;
	begin=(FCGI_BeginRequestBody *)&(h.contentData);
	begin->role=htons(role);
	begin->flags=flags;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
// =========================================================================================================== //
void sendAbortRequest(int fd,unsigned short requestId)
{
FCGI_Header h;

	h.version=FCGI_VERSION_1;
	h.type=htons(FCGI_ABORT_REQUEST);
	h.requestId=requestId;
	h.contentLength=0;
	h.paddingLength=0;
	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}
#define sendStdin(fd,id,stdin,len) sendWebData(fd,FCGI_STDIN,id,stdin,len)
#define sendData(fd,id,data,len) sendWebData(fd,FCGI_DATA,id,data,len)
//============================================================================================================ //

void sendWebData(int fd,unsigned char type,unsigned short requestId,char *data,unsigned int len)
{
FCGI_Header h;

	if (len > FASTCGILENGTH) return ;

	h.version=FCGI_VERSION_1;
	h.type=type;
	h.requestId=htons(requestId);
	h.contentLength=len;
	h.paddingLength=0;
	memcpy(h.contentData,data,len);

	writeSocket(fd,&h,FCGI_HEADER_SIZE+(h.contentLength)+(h.paddingLength));
}

// =========================================================================================================== //
static int createSocket(int port)
{
	int fd;
	struct sockaddr_in serv_addr;
	int enable = 1;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket creation failed\n");
		return (-1);
	}

	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1",&serv_addr.sin_addr);
	serv_addr.sin_port = htons(port);

	if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("connect failed\n");
		return (-1);
	}

	return fd;
}

void readSocket(int fd)
{
	FCGI_Header h;
	int type;
	while(type != FCGI_END_REQUEST) {

		int nb_lu = read(fd, &h, 8);

		type = h.type;

		int len = htons(h.contentLength) + h.paddingLength;

		char *answer = malloc(len * sizeof(char));
		char *cpy_answer = answer;
		nb_lu = 0;
		while(nb_lu < len) {
			nb_lu += read(fd, cpy_answer, len-nb_lu);
			cpy_answer += nb_lu;
		}
		printf("%.*s", len, answer);
		free(answer);
	}
}
// =========================================================================================================== //
/**
 * @brief Get the Result From P H P Interpreter object
 * 
 * @param result we need to allocate in this function
 * @param contentType 
 * @param contentLength 
 * @param path 
 * @param method 
 * @return int html reponse code
 */
int getResultFromPHPInterpreter(char **result, char *contentType, int *contentLength, char *path, char *method, char **forFreeMessageBody, char *responsePhrase, char *referer, int lenReferer, char *query, int queryLength, char *contLength, int contLengthLength, char *contType, int contTypeLength, char *messagebody, int messageBodyLength)
{
	int fd;
	int reponseCode = 200;
	fd=createSocket(9000);
	// sendGetValue(fd);
	sendBeginRequest(fd,10,FCGI_RESPONDER,FCGI_KEEP_CONN);

	FCGI_Header *h;
	h = malloc(sizeof(FCGI_Header));
	h->contentLength = 0;
	h->paddingLength = 0;

	char absPath[64];
	getcwd(absPath, 64);
	char *absolutPath = malloc(strlen(path) + strlen(absPath) + 2);

	strcpy(absolutPath, absPath);
	strcat(absolutPath, "/");
	strcat(absolutPath, path);
	printf("%s\n", absolutPath);

	// char *ref = malloc((lenReferer + 1) * sizeof(char));
	// strncpy(ref, referer, lenReferer);
	// ref[lenReferer] = '\0';

	if(!strcmp(method, "GET")) {
		char *que;
		if(query != NULL) {
			que = malloc((queryLength + 1) * sizeof(char));
			strncpy(que, query, queryLength);
			que[queryLength] = '\0';
			addNameValuePair(h, "QUERY_STRING", que);
			free(que);
		}
	}
	if(!strcmp(method, "POST")) {
		char *typ;
		typ = malloc((contTypeLength + 1) * sizeof(char));
		strncpy(typ, contType, contTypeLength);
		typ[contTypeLength] = '\0';
		addNameValuePair(h, "CONTENT_TYPE", typ);
		free(typ);

		char *leng;
		leng = malloc((contLengthLength + 1) * sizeof(char));
		strncpy(leng, contLength, contLengthLength);
		leng[contLengthLength] = '\0';
		addNameValuePair(h, "CONTENT_LENGTH", leng);
		free(leng);
	}

	addNameValuePair(h,"REQUEST_METHOD", method);
	addNameValuePair(h,"SCRIPT_FILENAME", absolutPath);
	free(absolutPath);
	sendWebData(fd,FCGI_PARAMS,10,h->contentData,h->contentLength);
	sendWebData(fd,FCGI_PARAMS,10,NULL,0);
	if(!strcmp(method, "POST")) {
		sendStdin(fd, 10, messagebody, messageBodyLength);
		sendStdin(fd, 10, NULL, 0);
	}
	free(h);

	FCGI_Header h2;
	int type = FCGI_STDOUT;
	char *answer = malloc(1 * sizeof(char));
	int totLen = 0;
	int tempTotLen = 0;
	while(type != FCGI_END_REQUEST) {

		int nb_lu = read(fd, &h2, 8);

		type = h2.type;

		if(type == FCGI_STDERR) {
			int len = htons(h2.contentLength) + h2.paddingLength;
			char *error = malloc(len * sizeof(char));
			char *cpyerror = error;

			nb_lu = 0;
			while(nb_lu < len) {
				nb_lu += read(fd, cpyerror, len-nb_lu);
				cpyerror += nb_lu;
			}
			free(error);
		}

		if(type == FCGI_STDOUT) {
			int len = htons(h2.contentLength) + h2.paddingLength;

			tempTotLen = totLen;
			totLen += htons(h2.contentLength);

			answer = realloc(answer, totLen * sizeof(char));

			char *tempAnswer = malloc(len * sizeof(char));
			char *cpyTempAnswer = tempAnswer;

			nb_lu = 0;
			while(nb_lu < len) {
				nb_lu += read(fd, cpyTempAnswer, len-nb_lu);
				cpyTempAnswer += nb_lu;
			}
			strncpy(answer + tempTotLen, tempAnswer, htons(h2.contentLength));
			free(tempAnswer);
		}
	}
	*contentLength = totLen;

	char *startContentType;
	int i;
	for(i=0; i<100; i++) {
		if(answer[i] == 'C' && answer[i+1] == 'o' && answer[i+2] == 'n') {
			startContentType = &answer[i];
			if(i!=0) { /* There is an error */
				char *c = strchr(answer, ':');
				char taberror[4];
				for(int j=0; j<3; j++) {
					taberror[j] = c[j+2];
				}
				taberror[3] = '\0';
				reponseCode = atoi(taberror);
				c += 6;
				int k = 0;
				while(*c != '\r') {
					responsePhrase[k++] = *c++;
				}
				responsePhrase[k] = '\0';
			}
			break;
		}
	}
	i = 0;
	while(i < 100) {
		if(startContentType[i] == '\r' && startContentType[i+1] == '\n') {
			strncpy(contentType, startContentType, i+2);
			contentType[i+2] = '\0';
			break;
		}
		i++;
	}

	for(i=0; i<(*contentLength); i++) {
		if(answer[i] == '\r') {
			if(answer[i+1] == '\n' && answer[i+2] == '\r' && answer[i+3] == '\n') {
				*result = answer + i + 4;
				(*contentLength) -= (i + 4);
				break;
			}
		}
	}

	*forFreeMessageBody = answer;
	return reponseCode;
}
