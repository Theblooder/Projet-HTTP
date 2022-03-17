#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerTransfertEncoding.h"


#define true 1
#define false 0


int Transfer_Encoding_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Transfer-Encoding")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Transfer_Encoding(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Transfer_Encoding_header", pere);
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

int Transfer_Encoding(int *p, const char *req, node *pere)
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
        if(transfer_coding(p, req, createFils(pere))) {
            nbr = 0;
            while(1) {
                c = *p;
                if(OWS(p, req, fils = createFils(pere))) {
                    if(case_insensitive_char(p, req, createFils(pere), ',')) {
                        int c2 = *p;
                        if(OWS(p, req, fils2 = createFils(pere))) {
                            if(transfer_coding(p, req, createFils(pere))) {
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
                putValueInNode(save, *p-save, "Transfer_Encoding", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int transfer_coding(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_string(p, req, fils, "chunked")) {
        putValueInNode(save, *p-save, "transfer_coding", pere);
        return true;
    }
    else if(case_insensitive_string(p, req, fils, "compress")) {
        putValueInNode(save, *p-save, "transfer_coding", pere);
        return true;
    }
    else if(case_insensitive_string(p, req, fils, "deflate")) {
        putValueInNode(save, *p-save, "transfer_coding", pere);
        return true;
    }
    else if(case_insensitive_string(p, req, fils, "gzip")) {
        putValueInNode(save, *p-save, "transfer_coding", pere);
        return true;
    }
    else if(transfer_extension(p, req, fils)) {
        putValueInNode(save, *p-save, "transfer_coding", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int transfer_extension(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(token(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(OWS(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ';')) {
                    if(OWS(p, req, createFils(pere))) {
                        if(transfert_parameter(p, req, createFils(pere))) {
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
            putValueInNode(save, *p-save, "transfer_extension", pere);
            return true;
        }
    }
    
    *p = save;
    purgeFils(pere);
    return false;
}

int transfert_parameter(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(token(p, req, createFils(pere))) {
        if(BWS(p, req, createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), '=')) {
                if(BWS(p, req, createFils(pere))) {
                    fils = createFils(pere);
                    if(token(p, req, fils)) {
                        putValueInNode(save, *p-save, "transfert_parameter", pere);
                        return true;
                    }
                    else if(quoted_string(p, req, fils)) {
                        putValueInNode(save, *p-save, "transfert_parameter", pere);
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