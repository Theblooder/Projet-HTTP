#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerContentLength.h"


#define true 1
#define false 0

int Content_Length_Header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Content-Length")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Content_Length(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Content_Length_Header", pere);
                        return true;
                    }
                }
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int Content_Length(int *p, const char *req, node *pere)
{
    int save = *p;

    int nbr = 0;
    node *fils;
    while(1) {
        if(DIGIT(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        else {
            break;
        }
    }
    purgeNode(fils);
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "Content_Length", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}