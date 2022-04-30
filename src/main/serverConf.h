#ifndef __SERVERCONF_H__
#define __SERVERCONF_H__

/*Prototype*/

#define MAX_LENGTH_SITE 64
#define NAME_CONF_FILE "server.conf"
#define DEFAULT_SITE "htdocs/wwwtotocom"

void getRepertoryFromHost(char *repository, const char *host, int len);


#endif