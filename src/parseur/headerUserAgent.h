#ifndef __HEADERUSERAGENT_H__
#define __HEADERUSERAGENT_H__

/*Prototype*/
int User_Agent_header(int *p, const char *req, node *pere);

    int User_Agent(int *p, const char *req, node *pere);

        int product(int *p, const char *req, node *pere);

            int product_version(int *p, const char *req, node *pere);

        int comment(int *p, const char *req, node *pere);

            int ctext(int *p, const char *req, node *pere);

#endif