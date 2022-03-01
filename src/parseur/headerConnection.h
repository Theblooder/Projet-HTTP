#ifndef __HEADERCONNECTION_H__
#define __HEADERCONNECTION_H__

/*Prototype*/

int Connection_header(int p, const char *req, node *pere);

    int Connection(int p, const char *req, node *pere);

        int case__AND__OWS(int p, const char *req, node *pere);

        int connection_option(int p, const char *req, node *pere);

        int OWS__AND__case__AND__optional(int p, const char *req, node *pere);

            int OWS__AND__connection_option(int p, const char *req, node *pere);


#endif