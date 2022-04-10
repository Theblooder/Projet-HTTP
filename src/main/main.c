#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

// for librequest 
#include "request.h"   

// for parser 

// this will declare internal type used by the parser
#include "api.h"

#include "tree.h"
#include "verifSemantique.h"

#define ERROR "HTTP/1.0 400 SUCKA\r\n\r\n"
#define REPONSE "HTTP/1.0 200 OK\r\nContent-type: text/html\r\nContent-length: 200\r\n\r\n"

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
			node *n, *root;
			
			// get the root of the tree this is no longer opaque since we know the internal type with httpparser.h 
			//void *root;
			root = getRootTree();
			r = searchTree(root,"request_line"); 
			tok = searchTree(r->node, "absolute_path");
			purgeElement(&r);

			// node is no longer opaque 
			n = tok->node;
			purgeElement(&tok);

			char *filePath;
			filePath = constructAbsolutePath(&requete->buf[n->pStart], n->length, filePath);
			construct
			purgeTree(root);


			int file = open(filePath, O_RDONLY);
			if(file == -1) {
				writeDirectClient(requete->clientId,ERROR,strlen(ERROR)); 
			}
			else {
				struct stat st;

				fstat(file, &st);
				char *addr = mmap(NULL, st.st_size, PROT_WRITE, MAP_PRIVATE, file, 0);
				//writeDirectClient(requete->clientId, copyFile, l + 6);
				writeDirectClient(requete->clientId,REPONSE,strlen(REPONSE)); 
				writeDirectClient(requete->clientId, addr, st.st_size);

			}
			free(filePath);
			
		} else {
			writeDirectClient(requete->clientId,ERROR,strlen(ERROR)); 
		}

		endWriteDirectClient(requete->clientId); 
		requestShutdownSocket(requete->clientId); 

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest(requete); 
	}

	return 1;
}