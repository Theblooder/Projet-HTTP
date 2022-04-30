#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serverConf.h"


void getRepertoryFromHost(char *repository, const char *host, int len)
{
    FILE *f = fopen(NAME_CONF_FILE, "r");
    if(f == NULL) {
        printf("Erreur dans l'ouverture du fichier server.conf");
        strcpy(repository, DEFAULT_SITE);
        repository[strlen(DEFAULT_SITE)] = '\0';
        return;
    }
    char line[128];

    int i;
    while(fgets(line, 128, f) != NULL) {
        i = 0;
        while(line[i] != '=') {
            i++;
        }
        int end = i;
        while(line[end] != '\n') {
            end++;
        }
        int min;
        if(i <= len) {
            min = i;
        }
        else {
            min = len;
        }
        if(!strncmp(line, host, min)) {
            strncpy(repository, line + i+1, end - i-1);
            repository[end - i-1] = '\0';
            fclose(f);
            return;
        }
    }
    strcpy(repository, DEFAULT_SITE);
    repository[strlen(DEFAULT_SITE)] = '\0';
    fclose(f);
    return;
}

