#ifndef __HEADERAUTHORIZATION_H__
#define __HEADERAUTHORIZATION_H__

/*Prototype*/

int Authorization_header(int *p, const char *req, node *pere);

    int Authorization(int *p, const char *req, node *pere);

        int credentials(int *p, const char *req, node *pere);

            int auth_scheme(int *p, const char *req, node *pere);

            int token68(int *p, const char *req, node *pere);

            int auth_param(int *p, const char *req, node *pere);

#endif