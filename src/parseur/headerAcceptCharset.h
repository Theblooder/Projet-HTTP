#ifndef __HEADERACCEPTCHARSET_H__
#define __HEADERACCEPTCHARSET_H__

/*Prototype*/

int Accept_Charset_header(int *p, const char *req, node *pere);

    int Accept_Charset(int *p, const char *req, node *pere);

        int charset(int *p, const char *req, node *pere);

#endif