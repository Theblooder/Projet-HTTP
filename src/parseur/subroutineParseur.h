#ifndef __SUBROUTINEPARSEUR_H__
#define __SUBROUTINEPARSEUR_H__

/*Prototype*/

int HTTP_message(int *p, const char *req, node *pere);


    int header_field(int *p, const char *req, node *pere);

        int Unknow_header(int *p, const char *req, node *pere);

    /* CRLF */

    int message_body(int *p, const char *req, node *pere);


#endif
