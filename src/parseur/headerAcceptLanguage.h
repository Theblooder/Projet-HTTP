#ifndef __HEADERACCEPTLANGUAGE_H__
#define __HEADERACCEPTLANGUAGE_H__

/*Prototype*/
int Accept_Language_header(int *p, const char *req, node *pere);

    int Accept_Language(int *p, const char *req, node *pere);

        int language_range(int *p, const char *req, node *pere);

            int alphanum(int *p, const char *req, node *pere);

#endif