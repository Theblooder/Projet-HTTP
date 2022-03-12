#ifndef __HEADERACCEPTENCODING_H__
#define __HEADERACCEPTENCODING_H__

/*Prototype*/

int Accept_Encoding_header(int *p, const char *req, node *pere);

    int Accept_Encoding(int *p, const char *req, node *pere);

        int codings(int *p, const char *req, node *pere);

            int content_coding(int *p, const char *req, node *pere);

#endif