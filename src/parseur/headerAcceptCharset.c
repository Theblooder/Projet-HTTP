#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAcceptCharset.h"
#include "headerAccept.h"


#define true 1
#define false 0

int Accept_Charset_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Accept-Charset")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Accept_Charset(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Accept_Charset_header", pere);
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

int Accept_Charset(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;
    node *fils3;

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
        fils = createFils(pere);
        if(charset(p, req, fils) || case_insensitive_char(p, req, fils, '*')) {
            if(!weight(p, req, fils = createFils(pere))) {
                purgeNode(fils);
            }
            nbr = 0;
            while(1) {
                c = *p;
                if(OWS(p, req, fils = createFils(pere))) {
                    if(case_insensitive_char(p, req, createFils(pere), ',')) {
                        int c2 = *p;
                        if(OWS(p, req, fils2 = createFils(pere))) {
                            fils3 = createFils(pere);
                            if(charset(p, req, fils3) || case_insensitive_char(p, req, fils3, '*')) {
                                if(!weight(p, req, fils3 = createFils(pere))) {
                                    purgeNode(fils3);
                                }
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
                putValueInNode(save, *p-save, "Accept_Charset", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int charset(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "charset", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}