#ifndef __HEADERCONTENTTYPE_H__
#define __HEADERCONTENTTYPE_H__

/*Prototype*/

int Content_Type_header(int *p, const char *req, node *pere);

    int Content_Type(int *p, const char *req, node *pere);

        int media_type(int *p, const char *req, node *pere);

            int type(int *p, const char *req, node *pere);

            int subtype(int *p, const char *req, node *pere);

            int parameter(int *p, const char *req, node *pere);

#endif