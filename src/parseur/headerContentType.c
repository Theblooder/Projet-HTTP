#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerContentType.h"


#define true 1
#define false 0

int Content_Type_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Content-Type")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Content_Type(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Content_Type_header", pere);
                        return true;
                    }
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int Content_Type(int *p, const char *req, node *pere)
{
    int save = *p;

    if(media_type(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "Content_Type", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int media_type(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(type(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '/')) {
            if(subtype(p, req, createFils(pere))) {
                int nbr = 0;
                int c;
                while(1) {
                    c = *p;

                    if(OWS(p, req, fils = createFils(pere))) {
                        if(case_insensitive_char(p, req, createFils(pere), ';')) {
                            if(OWS(p, req, fils = createFils(pere))) {
                                if(parameter(p, req, createFils(pere))) {
                                    nbr++;
                                    continue;
                                }
                            }
                        }
                    }
                    purgeNodeAndRightFrere(fils);
                    *p = c;
                    break;
                }
                if(nbr >= 0) {
                    putValueInNode(save, *p-save, "media_type", pere);
                    return true;
                }
            }
        } 
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int type(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "type", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int subtype(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "subtype", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int parameter(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(token(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '=')) {
            fils = createFils(pere);
            if(token(p, req, fils)) {
                putValueInNode(save, *p-save, "parameter", pere);
                return true;
            }
            else if(quoted_string(p, req, fils)) {
                putValueInNode(save, *p-save, "parameter", pere);
                return true;
            }
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}