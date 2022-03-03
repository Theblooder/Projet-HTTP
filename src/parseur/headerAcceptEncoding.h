#ifndef __HEADERACCEPTENCODING_H__
#define __HEADERACCEPTENCODING_H__

/*Prototype*/

int Accept_Encoding_header(int p, const char *req, node *pere);

    int Accept_Encoding(int p, const char *req, node *pere);

        int __accept_Encoding__1(int p, const char *req, node *pere);

            int codings__AND__weight(int p, const char *req, node *pere);

                int codings(int p, const char *req, node *pere);

                    int content_coding(int p, const char *req, node *pere);

        int __accept_Encoding__2(int p, const char *req, node *pere);

            int optional__accept_Encoding__2(int p, const char *req, node *pere);



#endif