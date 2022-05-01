#ifndef __SERVERCONF_H__
#define __SERVERCONF_H__

/*Prototype*/

#define MAX_LENGTH_SITE 64
#define NAME_CONF_FILE "server.conf"
#define DEFAULT_SITE "htdocs/wwwtotocom"

/**
 * @brief Get the Repertory From Host object
 * 
 * @param repository The repository (it will give a default if none found (you can check the DEFAULT_SITE define to change it))
 * @param host 
 * @param len len of the host
 */
void getRepertoryFromHost(char *repository, const char *host, int len);


#endif