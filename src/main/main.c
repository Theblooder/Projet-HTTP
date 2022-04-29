#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

// for librequest 
#include "request.h"

// for parser 

// this will declare internal type used by the parser
#include "api.h"

#include "tree.h"
#include "verifSemantique.h"
#include "constructAnswer.h"

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
			
			initAnswer(requete->clientId);

			node *root = getRootTree();
			char reasonPrase[32]; int codeError;
			if(codeError = verificationSemantique(root, requete, reasonPrase)) {
				constructFirstLine("1.0", codeError, reasonPrase);
			}

			if(codeError = constructAnswer(root, requete, reasonPrase)) {
				constructFirstLine("1.0", codeError, reasonPrase);
			}
			else {
				constructFirstLine("1.1", 200, "OK");
			}

			purgeTree(root);



			
		} else {
			// writeDirectClient(requete->clientId,ERROR,strlen(ERROR)); 
		}


		// endWriteDirectClient(requete->clientId); 

		/* new function who send  the answer in once thanks to he structure Answer contructed before */
		sendAnswerToClient();
		purgeAnswer();

		requestShutdownSocket(requete->clientId); 

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest(requete); 
	}

	return 1;
}