#ifndef __HEADERACCEPT_H__
#define __HEADERACCEPT_H__

/*Prototype*/

int Accept_header(int *p, const char *req, node *pere);

    int Accept(int *p, const char *req, node *pere);

        int media_range(int *p, const char *req, node *pere);

        int accept_params(int *p, const char *req, node *pere);

            int weight(int *p, const char *req, node *pere);

                int qvalue(int *p, const char *req, node *pere);

            int accept_ext(int *p, const char *req, node *pere);

#endif