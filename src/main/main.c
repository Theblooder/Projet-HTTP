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
#include "constructAnswer.h"
#include "Answer.h"

/* Si la requete est mal parser */
#define ERROR "HTTP/1.1 400 Bad Request\r\n\r\nRequete fausse syntaxiquement (le parseur retourne faux)"

int main(int argc, char *argv[])
{
	message *requete;
	int res;
	node *root;
	//while ( 1 ) {
		// on attend la reception d'une requete HTTP requete pointera vers une ressource allouée par librequest.
		if ((requete=getRequest(8080)) == NULL ) return -1;

		// Affichage de debug
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId);
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf);


		if (res=parseur(requete->buf,requete->len)) {

			initAnswer(requete->clientId);

			root = getRootTree();

			char reasonPrase[MAX_REASON_PHRASE]; int code; int version;
			code = constructAnswer(root, requete, reasonPrase, &version);

			/* ===== To construct the version we will answer ======*/
			char v[4];
			int minor = version % 10;
			int major = (version - minor) / 10;
			if(version >= 11) {
				sprintf(v, "%d.%d", 1, 1); v[3] = '\0';
			}
			else {
				sprintf(v, "%d.%d", major, minor); v[3] = '\0';
			}
			/*=======================================================*/

			constructFirstLine(v, code, reasonPrase);

			if(code != 200) {
				purgeHeaders();
			}
			else {
				/* If the reponse is OK we add all of the headers belows */
				constructHostHeader();
			}
			

			/* new function who send the answer in once thanks to he structure Answer contructed before */
			sendAnswerToClient();
			purgeAnswer();




		} else {
			writeDirectClient(requete->clientId,ERROR,strlen(ERROR));
			endWriteDirectClient(requete->clientId);
		}
		

		/* Faire une fonction qui dit oui ou non si la connection doit s'arréter (oui si 1.1 et connection keep-alive, non si connection close)*/
		if(needToCloseConnection()) {
			requestShutdownSocket(requete->clientId);
		}

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer...
		freeRequest(requete);
		purgeTree(root);
	//}

	return 1;
}
