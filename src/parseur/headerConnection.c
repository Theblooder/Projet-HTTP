#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerConnection.h"


#define true 1
#define false 0

int Connection_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Connection")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Connection(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Connection_header", pere);
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

int Connection(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), ',')) {
            if(OWS(p, req, createFils(pere))) {
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 0) {
        if(connection_option(p, req, createFils(pere))) {
            nbr = 0;
            while(1) {
                c = *p;
                if(OWS(p, req, fils = createFils(pere))) {
                    if(case_insensitive_char(p, req, createFils(pere), ',')) {
                        int c2 = *p;
                        if(OWS(p, req, fils2 = createFils(pere))) {
                            if(connection_option(p, req, createFils(pere))) {
                                nbr++;
                                continue;
                            }
                        }
                        *p = c2;
                        purgeNodeAndRightFrere(fils2);
                        nbr++;
                        continue;
                    }
                }
                purgeNodeAndRightFrere(fils);
                *p = c;
                break;
            }
            if(nbr >= 0) {
                putValueInNode(save, *p-save, "Connection", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int connection_option(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "connection_option", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}