#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerHost.h"


#define true 1
#define false 0

int Host_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Host")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Host(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Host_header", pere);
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

int Host(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(uri_host(p, req, createFils(pere))) {
        int c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
            if(port(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "Host", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "Host", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int uri_host(int *p, const char *req, node *pere)
{
    int save = *p;

    if(host(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "uri_host", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int host(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(IP_literal(p, req, fils)) {
        putValueInNode(save, *p-save, "host", pere);
        return true;
    }
    else if(IPv4address(p, req, fils)) {
        putValueInNode(save, *p-save, "host", pere);
        return true;
    }
    else if(reg_name(p, req, fils)) {
        putValueInNode(save, *p-save, "host", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int IP_literal(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(case_insensitive_char(p, req, createFils(pere), '[')) {
        int c = *p;
        if(IPv6address(p, req, fils = createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), ']')) {
                putValueInNode(save, *p-save, "IP_literal", pere);
                return true;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        if(IPvFuture(p, req, fils = createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), ']')) {
                putValueInNode(save, *p-save, "IP_literal", pere);
                return true;
            }
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int IPv6address(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils;
    node *fils2;

    int nbr = 0;
    int c;

    while(1) {
        c = *p;

        if(h16(p, req, fils = createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), ':')) {
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr == 6) {
        if(ls32(p, req, createFils(pere))) {
            putValueInNode(save, *p-save, "IPv6address", pere);
            return true;
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        while(1) {
            c = *p;

            if(h16(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ':')) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr == 5) {
            if(ls32(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "IPv6address", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(!h16(p, req, fils = createFils(pere))) {
        purgeNode(fils);
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        while(1) {
            c = *p;

            if(h16(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ':')) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr == 4) {
            if(ls32(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "IPv6address", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 1) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        nbr = 0;
        while(1) {
            c = *p;

            if(h16(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ':')) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr == 3) {
            if(ls32(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "IPv6address", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 2) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        nbr = 0;
        while(1) {
            c = *p;

            if(h16(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ':')) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr == 2) {
            if(ls32(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "IPv6address", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 3) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        if(h16(p, req, createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), ':')) {
                if(ls32(p, req, createFils(pere))) {
                    putValueInNode(save, *p-save, "IPv6address", pere);
                    return true;
                }
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 4) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        if(ls32(p, req, createFils(pere))) {
            putValueInNode(save, *p-save, "IPv6address", pere);
            return true;
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 5) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        if(h16(p, req, createFils(pere))) {
            putValueInNode(save, *p-save, "IPv6address", pere);
            return true;
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(h16(p, req, createFils(pere))) {
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ':')) {
                if(h16(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr <= 6) {
            1 == 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
        }
    }
    if(case_insensitive_string(p, req, createFils(pere), "::")) {
        putValueInNode(save, *p-save, "IPv6address", pere);
        return true;
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int IPvFuture(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(case_insensitive_char(p, req, createFils(pere), 'v')) {
        int nbr = 0;
        while(1) {
            if(HEXDIG(p, req, fils = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils);
        if(nbr >= 1) {
            if(case_insensitive_char(p, req, createFils(pere), '.')) {
                nbr = 0;
                int c;
                while(1) {
                    c = *p;
                    fils = createFils(pere);

                    if(unreserved(p, req, fils)) {
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
                    putValueInNode(save, *p-save, "IPvFuture", pere);
                    return true;
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int IPv4address(int *p, const char *req, node *pere)
{
    int save = *p;

    if(dec_octet(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '.')) {
            if(dec_octet(p, req, createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), '.')) {
                    if(dec_octet(p, req, createFils(pere))) {
                        if(case_insensitive_char(p, req, createFils(pere), '.')) {
                            if(dec_octet(p, req, createFils(pere))) {
                                putValueInNode(save, *p-save, "IPv4address", pere);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int dec_octet(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils;

    if(case_insensitive_string(p, req, createFils(pere), "25")) {
        if(range(p, req, createFils(pere), 0x30, 0x35)) {
            putValueInNode(save, *p-save, "dec_octet", pere);
            return true;
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);

    if(case_insensitive_string(p, req, createFils(pere), "2")) {
        if(range(p, req, createFils(pere), 0x30, 0x34)) {
            if(DIGIT(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "dec_octet", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);

    if(case_insensitive_string(p, req, createFils(pere), "1")) {
        if(DIGIT(p, req, createFils(pere))) {
            if(DIGIT(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "dec_octet", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);

    if(range(p, req, createFils(pere), 0x31, 0x39)) {
        if(DIGIT(p, req, createFils(pere))) {
            putValueInNode(save, *p-save, "dec_octet", pere);
            return true;
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);

    if(DIGIT(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "dec_octet", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int h16(int *p, const char *req, node *pere)
{
    int save = *p;

    int nbr = 0;
    node *fils;
    while(1) {
        if(HEXDIG(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        else {
            break;
        }
    }
    purgeNode(fils);
    if(nbr >= 1 && nbr <= 4) {
        putValueInNode(save, *p-save, "h16", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int ls32(int *p, const char *req, node *pere)
{
    int save = *p;

    if(h16(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(h16(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "ls32", pere);
                return true;
            }
        }
    }
    *p = save;
    purgeFilsAndFrere(pere);

    if(IPv4address(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "ls32", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int reg_name(int *p, const char *req, node *pere)
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
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "reg_name", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return true;
}

int port(int *p, const char *req, node *pere)
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
        putValueInNode(save, *p-save, "port", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return true;
}