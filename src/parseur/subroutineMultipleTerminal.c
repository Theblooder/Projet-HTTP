#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../main/tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"


#define true 1
#define false 0


int token(int *p, const char *req, node *pere) /* Multiple times */
{
    int save = *p;

    int nbr = 0;
    node *fils;
    while(1) {
        if(tchar(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        else {
            break;
        }
    }
    purgeNode(fils);
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "token", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int tchar(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_char(p, req, fils, '!')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '#')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '$')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '%')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '&')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '\'')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '*')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '+')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '-')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '.')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '^')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '_')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '`')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '|')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '~')) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(DIGIT(p, req, fils)) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }
    else if(ALPHA(p, req, fils)) {
        putValueInNode(save, *p-save, "tchar", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int segment(int *p, const char *req, node *pere)
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
        putValueInNode(save, *p-save, "segment", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    putValueInNode(save, *p-save, "segment", pere);
    return true;
}

int pchar(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_char(p, req, fils, ':')) {
        putValueInNode(save, *p-save, "pchar", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '@')) {
        putValueInNode(save, *p-save, "pchar", pere);
        return true;
    }
    else if(unreserved(p, req, fils)) {
        putValueInNode(save, *p-save, "pchar", pere);
        return true;
    }
    else if(pct_encoded(p, req, fils)) {
        putValueInNode(save, *p-save, "pchar", pere);
        return true;
    }
    else if(sub_delims(p, req, fils)) {
        putValueInNode(save, *p-save, "pchar", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int unreserved(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_char(p, req, fils, '-')) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '.')) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '_')) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '~')) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }
    else if(ALPHA(p, req, fils)) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }
    else if(DIGIT(p, req, fils)) {
        putValueInNode(save, *p-save, "unreserved", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int pct_encoded(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_char(p, req, createFils(pere), '%')) {
        if(HEXDIG(p, req, createFils(pere))) {
            if(HEXDIG(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "pct_encoded", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int sub_delims(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_char(p, req, fils, '!')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '$')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '&')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '\'')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '(')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, ')')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '*')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '+')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, ',')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, ';')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '=')) {
        putValueInNode(save, *p-save, "sub_delims", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int obs_text(int *p, const char *req, node *pere)
{
    int save = *p;

    if(range(p, req, createFils(pere), 0x80, 0xFF)) {
        putValueInNode(save, *p-save, "obs_text", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int HEXDIG(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(case_insensitive_char(p, req, fils, 'A')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, 'B')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, 'C')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, 'D')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, 'E')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, 'F')) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }
    else if(DIGIT(p, req, fils)) {
        purgeNode(fils);
        putValueInNode(save, *p-save, "__hexdig", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int OCTET(int *p, const unsigned char *req, node *pere)
{
    int save = *p;

    if(req[*p] && req[*p] >= 0x00 && req[*p] <= 0xFF) {
        *p += 1;
        putValueInNode(save, *p-save, "__octet", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int DQUOTE(int *p, const char *req, node *pere)
{
    int save = *p;

    if(req[*p] && req[*p] == 0x22) {
        *p += 1;
        putValueInNode(save, *p-save, "__dquote", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int OWS(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(SP(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(HTAB(p, req, fils)) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "OWS", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    putValueInNode(save, *p-save, "OWS", pere);
    return true;
}

int BWS(int *p, const char *req, node *pere)
{
    int save = *p;

    if(OWS(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "BWS", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int RWS(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(SP(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(HTAB(p, req, fils)) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "RWS", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int ALPHA(int *p, const unsigned char *req, node *pere)
{
    int save = *p;

    if(req[*p] && ((req[*p] >= 65 && req[*p] <= 90) || (req[*p] >= 97 && req[*p] <= 122))) {
        *p += 1;
        putValueInNode(save, *p-save, "__alpha", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int DIGIT(int *p, const char *req, node *pere)
{
    int save = *p;

    if(req[*p] && req[*p] >= 48 && req[*p] <= 57) {
        *p += 1;
        putValueInNode(save, *p-save, "__digit", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int CRLF(int *p, const char *req, node *pere) /* terminal */
{
    int save = *p;

    if(req[*p] && req[(*p)+1] && req[*p] == 0x0D && req[(*p)+1] ==0x0A) {
        *p += 2;
        putValueInNode(save, *p-save, "__crlf", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int SP(int *p, const char *req, node *pere) /* terminal */
{
    int save = *p;

    if(req[*p] && req[*p] == 0x20) {
        *p += 1;
        putValueInNode(save, *p-save, "__sp", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int HTAB(int *p, const char *req, node *pere) /* terminal */
{
    int save = *p;

    if(req[*p] && req[*p] == 0x09) {
        *p += 1;
        putValueInNode(save, *p-save, "__htab", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int VCHAR(int *p, const unsigned char *req, node *pere) /* terminal */
{    
    int save = *p;

    if(req[*p] && req[*p] >= 0x21 && req[*p] <= 0X7E) {
        *p += 1;
        putValueInNode(save, *p-save, "__vchar", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int range(int *p, const unsigned char *req, node *pere, int d, int f)
{
    int save = *p;

    if(req[*p] && req[*p] >= d && req[*p] <= f) {
        *p += 1;
        putValueInNode(save, *p-save, "__range", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int num(int *p, const char *req, node *pere, int *v, int n)
{
    int save = *p;

    for(int i=0; i<n; i++) {
        if(req[(*p)+i] && req[(*p)+i] == v[i]) {
            continue;
        }
        else {
            purgeFilsAndFrere(pere);
            return false;
        }
    }
    *p += n;
    putValueInNode(save, *p-save, "__num", pere);
    return true;
}

int case_insensitive_char(int *p, const char *req, node *pere, char c) /* terminal */
{
    int save = *p;

    if(req[*p] == c) {
        *p += 1;
        putValueInNode(save, *p-save, "case_insensitive_string", pere);
        return true;
    }
    else {
        purgeFilsAndFrere(pere);
        return false;
    }
}

int case_insensitive_string(int *p, const char *req, node *pere, char *c) /* terminal */
{
    int save = *p;

    while(*c) {
        if(req[*p] && tolower(*c++) == tolower(req[*p])) {
            *p += 1;
        }
        else {
            *p = save;
            purgeFilsAndFrere(pere);
            return false;
        }
    }
    putValueInNode(save, *p-save, "case_insensitive_string", pere);
    return true;
}


int quoted_string(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(DQUOTE(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;
            fils = createFils(pere);

            if(qdtext(p, req, fils)) {
                nbr++;
                continue;
            }
            else if(quoted_pair(p, req, fils)) {
                nbr++;
                continue;
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            if(DQUOTE(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "quoted_string", pere);
                return true;
            }
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int qdtext(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(HTAB(p, req, fils)) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }
    else if(SP(p, req, fils)) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '!')) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }
    else if(range(p, req, fils, 0x23, 0x5B)) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }
    else if(range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }
    else if(obs_text(p, req, fils)) {
        putValueInNode(save, *p-save, "qdtext", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int quoted_pair(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(case_insensitive_char(p, req, createFils(pere), '\\')) {
        fils = createFils(pere);
        if(HTAB(p, req, fils)) {
            putValueInNode(save, *p-save, "quoted_pair", pere);
            return true;
        }
        else if(SP(p, req, fils)) {
            putValueInNode(save, *p-save, "quoted_pair", pere);
            return true;
        }
        else if(VCHAR(p, req, fils)) {
            putValueInNode(save, *p-save, "quoted_pair", pere);
            return true;
        }
        else if(obs_text(p, req, fils)) {
            putValueInNode(save, *p-save, "quoted_pair", pere);
            return true;
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}