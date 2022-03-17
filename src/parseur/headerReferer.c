#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerReferer.h"
#include "subroutineFirstLine.h"
#include "headerHost.h"


#define true 1
#define false 0

int Referer_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Referer")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Referer(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Referer_header", pere);
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

int Referer(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(absolute_URI(p, req, fils)) {
        putValueInNode(save, *p-save, "Referer", pere);
        return true;
    }
    else if(partial_URI(p, req, fils)) {
        putValueInNode(save, *p-save, "Referer", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int absolute_URI(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(scheme(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(hier_part(p, req, createFils(pere))) {
                int c = *p;
                if(case_insensitive_char(p, req, fils = createFils(pere), '?')) {
                    if(query(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "absolute_URI", pere);
                        return true;
                    }
                }
                *p = c;
                purgeNodeAndRightFrere(fils);
                putValueInNode(save, *p-save, "absolute_URI", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int scheme(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(ALPHA(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;
            fils = createFils(pere);

            if(ALPHA(p, req, fils)) {
                nbr++;
                continue;
            }
            else if(DIGIT(p, req, fils)) {
                nbr++;
                continue;
            }
            else if(case_insensitive_char(p, req, fils, '+')) {
                nbr++;
                continue;
            }
            else if(case_insensitive_char(p, req, fils, '-')) {
                nbr++;
                continue;
            }
            else if(case_insensitive_char(p, req, fils, '.')) {
                nbr++;
                continue;
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "scheme", pere);
            return true;
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int hier_part(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    
    if(case_insensitive_string(p, req, fils = createFils(pere), "//")) {
        if(authority(p, req, createFils(pere))) {
            if(path_abempty(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "hier_part", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeNodeAndRightFrere(fils);

    fils = createFils(pere);
    if(path_absolute(p, req, fils)) {
        putValueInNode(save, *p-save, "hier_part", pere);
        return true;
    }
    else if(path_rootless(p, req, fils)) {
        putValueInNode(save, *p-save, "hier_part", pere);
        return true;
    }
    else if(path_empty(p, req, fils)) {
        putValueInNode(save, *p-save, "hier_part", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int authority(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int pass = 0;
    if(userinfo(p, req, fils = createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '@')) {
            pass = 1;
        }
    }
    if(!pass) {
        purgeNodeAndRightFrere(fils);
        *p = save;
    }
    
    if(host(p, req, createFils(pere))) {
        int c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
            if(port(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "authority", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "authority", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int userinfo(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {  
        c = *p;
        fils = createFils(pere);

        if(unreserved(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(pct_encoded(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(sub_delims(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, ':')) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "userinfo", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    putValueInNode(save, *p-save, "userinfo", pere);
    return true;
}

int path_abempty(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;

        if(case_insensitive_char(p, req, fils = createFils(pere), '/')) {
            if(segment(p, req, createFils(pere))) {
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "path_abempty", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    putValueInNode(save, *p-save, "path_abempty", pere);
    return true;
}

int path_absolute(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;

    if(case_insensitive_char(p, req, createFils(pere), '/')) {
        int c = *p;
        if(segment_nz(p, req, fils = createFils(pere))) {
            int nbr = 0;
            int c;
            while(1) {
                c = *p;

                if(case_insensitive_char(p, req, fils2 = createFils(pere), '/')) {
                    if(segment(p, req, createFils(pere))) {
                        nbr++;
                        continue;
                    }
                }
                purgeNodeAndRightFrere(fils2);
                *p = c;
                break;
            }
            if(nbr >= 0) {
                putValueInNode(save, *p-save, "path_absolute", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "path_absolute", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int segment_nz(int *p, const char *req, node *pere)
{
    int save = *p;

    int nbr = 0;
    node *fils;
    while(1) {
        if(pchar(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        else {
            break;
        }
    }
    purgeNode(fils);
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "segment_nz", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int path_rootless(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(segment_nz(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), '/')) {
                if(segment(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "path_rootless", pere);
            return true;
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int path_empty(int *p, const char *req, node *pere)
{
    int save = *p;

    putValueInNode(save, *p-save, "path_empty", pere);
    return true;
}

int partial_URI(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(relative_part(p, req, createFils(pere))) {
        int c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), '?')) {
            if(query(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "partial_URI", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "partial_URI", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int relative_part(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    
    if(case_insensitive_string(p, req, fils = createFils(pere), "//")) {
        if(authority(p, req, createFils(pere))) {
            if(path_abempty(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "relative_part", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeNodeAndRightFrere(fils);

    fils = createFils(pere);
    if(path_absolute(p, req, fils)) {
        putValueInNode(save, *p-save, "relative_part", pere);
        return true;
    }
    else if(path_noscheme(p, req, fils)) {
        putValueInNode(save, *p-save, "relative_part", pere);
        return true;
    }
    else if(path_empty(p, req, fils)) {
        putValueInNode(save, *p-save, "relative_part", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int path_noscheme(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(segment_nz_nc(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), '/')) {
                if(segment(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "path_noscheme", pere);
            return true;
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int segment_nz_nc(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(unreserved(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(pct_encoded(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(sub_delims(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '@')) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "segment_nz_nc", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}