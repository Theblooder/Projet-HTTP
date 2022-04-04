#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// for librequest 
#include "request.h"   

// for parser 

// this will declare internal type used by the parser
#include "httpparser.h"
#include "api.h"

#include "verifSemantique.h"

#define ERROR "HTTP/1.0 400 SUCKA\r\n\r\n"
#define REPONSE "HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"

int main(int argc, char *argv[])
{
	message *requete; 
	int res; 
	while ( 1 ) {
		// on attend la reception d'une requete HTTP requete pointera vers une ressource allouée par librequest. 
		if ((requete=getRequest(8080)) == NULL ) return -1; 

		// Affichage de debug 
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId); 
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf);  
		if (res=parseur(requete->buf,requete->len)) {
			/* Vérification de la sémantique */


			_Token *r,*tok;
			Lnode *root;
			
			// get the root of the tree this is no longer opaque since we know the internal type with httpparser.h 
			//void *root; 
			root=getRootTree();
			r=searchTree(root,"request_line"); 
			tok = searchTree(r->node, "absolute_path");
			purgeElement(&r);

			// node is no longer opaque 
			Lnode *node;
			node=(Lnode *)tok->node;
			purgeElement(&tok);
			int l = node->length;
			char *f = malloc((l + 6 + 1) * sizeof(char)); /* 6 fos htdocs */
			char *copyFile = f;
			char *absPath = "htdocs";
			while(*absPath != '\0') {
				*f++ = *absPath++;
			}
			char *copyBuf = &requete->buf[node->pStart];
			for(int i=0; i<l; i++) {
				*f++ = *copyBuf++;
			}
			*f = '\0';

			purgeTree(root); 

			FILE *file = fopen(copyFile, "r");
			if(file == NULL) {
				writeDirectClient(requete->clientId,ERROR,strlen(ERROR)); 
			}
			else {
				char *rep = malloc(2000 * sizeof(char));
				char *copy = rep;
				int len = 0;
				while((*rep=fgetc(file))!=EOF) {
					rep++;
					len++;
				}
				//writeDirectClient(requete->clientId, copyFile, l + 6);
				writeDirectClient(requete->clientId,REPONSE,strlen(REPONSE)); 
				writeDirectClient(requete->clientId, copy, len);
				free(copy);
				fclose(file);
			}
			free(copyFile);
			
		} else {
			writeDirectClient(requete->clientId,ERROR,strlen(ERROR)); 
		}
		
		endWriteDirectClient(requete->clientId); 
		requestShutdownSocket(requete->clientId); 
	// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
	freeRequest(requete); 
	}
	return (1);
}