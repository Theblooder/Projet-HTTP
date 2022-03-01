#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"


#define true 1
#define false 0


int token(int p, const char *req, node *pere) /* Multiple times */
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = tchar(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr < 1) {
        return false;
    }
    
    putValueInNode(p, now-p, "token", pere);
    return now-p;
}

int tchar(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(req[p] != '\0') {
        if(req[p] == '!') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '#') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '$') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '%') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '&') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == 0x27) { /* ' */
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '*') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '+') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '-') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '.') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '^') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '_') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '`') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '|') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
        else if(req[p] == '~') {
            putValueInNode(p, 1, "tchar", pere);
            return 1;
        }
    }
    else
        return false;

    if(len = ALPHA(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "tchar", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = DIGIT(p, req, fils)) {
        putValueInNode(p, len, "tchar", pere);
        return len;
    }
    else
        purgeNode(fils);
    
    return false;
}

int segment(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = pchar(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    
    putValueInNode(p, now-p, "segment", pere);
    return now-p;
}

int pchar(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(req[p] != '\0') {
        if(req[p] == ':') {
            putValueInNode(p, 1, "pchar", pere);
            return 1;
        }
        else if(req[p] == '@') {
            putValueInNode(p, 1, "pchar", pere);
            return 1;
        }
    }
    else
        return false;

    if(len = unreserved(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "pchar", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = pct_encoded(p, req, fils)) {
        putValueInNode(p, len, "pchar", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = sub_delims(p, req, fils)) {
        putValueInNode(p, len, "pchar", pere);
        return len;
    }
    else
        purgeNode(fils);
    
    return false;
}

int unreserved(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(req[p] != '\0') {
        if(req[p] == '-') {
            putValueInNode(p, 1, "unreserved", pere);
            return 1;
        }
        else if(req[p] == '.') {
            putValueInNode(p, 1, "unreserved", pere);
            return 1;
        }
        else if(req[p] == '_') {
            putValueInNode(p, 1, "unreserved", pere);
            return 1;
        }
        else if(req[p] == '~') {
            putValueInNode(p, 1, "unreserved", pere);
            return 1;
        }
    }
    else
        return false;

    if(len = ALPHA(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "unreserved", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = DIGIT(p, req, fils)) {
        putValueInNode(p, len, "unreserved", pere);
        return len;
    }
    else
        purgeNode(fils);
    
    return false;
}

int pct_encoded(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '%'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = HEXDIG(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = HEXDIG(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "pct_encoded", pere);
    return now-p;
}

int sub_delims(int p, const char *req, node *pere)
{
    if(req[p] != '\0') {
        if(req[p] == '!') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '$') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '&') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == 0x27) { /* ' */
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '(') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == ')') { /* ' */
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '*') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '+') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == ',') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == ';') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else if(req[p] == '=') {
            putValueInNode(p, 1, "sub_delims", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int obs_text(int p, const char *req, node *pere)
{
    int len;
    node* fils;


    if(len = range(p, req, fils = createFils(pere), 0x80, 0xFF)) {
        putValueInNode(p, len, "obs_text", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, -255, -1)) {
        putValueInNode(p, len, "obs_text", pere);
        return len;
    }
    else
        purgeNode(fils);

    return false;
}

int HEXDIG(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(req[p] != '\0') {
        if(req[p] == 'A') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
        else if(req[p] == 'B') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
        else if(req[p] == 'C') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
        else if(req[p] == 'D') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
        else if(req[p] == 'E') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
        else if(req[p] == 'F') {
            putValueInNode(p, 1, "HEXDIG", pere);
            return 1;
        }
    }
    else
        return false;

    if(len = DIGIT(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "HEXDIG", pere);
        return len;
    }
    else
        purgeNode(fils);
    
    return false;
}

int DQUOTE(int p, const char *req, node *pere)
{
    if(req[p] != '\0') {
        if(req[p] == 0x22) {
            putValueInNode(p, 1, "DQUOTE", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int OWS(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = SP__OR__HTAB(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    
    putValueInNode(p, now-p, "OWS", pere);
    return now-p;
}

int BWS(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "BWS", pere);
    return now-p;
}

int SP__OR__HTAB(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = SP(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = HTAB(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int ALPHA(int p, const char *req, node *pere)
{
    if(req[p] != '\0') {
        if((req[p] >= 65 && req[p] <= 90) || (req[p] >= 97 && req[p] <= 122)) {
            putValueInNode(p, 1, "ALPHA", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int DIGIT(int p, const char *req, node *pere)
{
    if(req[p] != '\0') {
        if(req[p] >= 48 && req[p] <= 57) {
            putValueInNode(p, 1, "DIGIT", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int CRLF(int p, const char *req, node *pere) /* terminal */
{
    if(req[p] != '\0' && req[p+1] != '\0') {
        if(req[p] == 0x0D && req[p+1] == 0x0A) {
            putValueInNode(p, 2, "CRLF", pere);
            return 2;
        }
        else
            return false;
    }
    else
        return false;
}

int SP(int p, const char *req, node *pere) /* terminal */
{
    if(req[p] != '\0') {
        if(req[p] == 0x20) {
            putValueInNode(p, 1, "SP", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int HTAB(int p, const char *req, node *pere) /* terminal */
{
    if(req[p] != '\0') {
        if(req[p] == 0x09) {
            putValueInNode(p, 1, "HTAB", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int VCHAR(int p, const char *req, node *pere) /* terminal */
{
    if(req[p] != '\0') {
        if(req[p] >= 0x21 && req[p] <= 0x7E) {
            putValueInNode(p, 1, "VCHAR", pere);
            return 1;
        }
        else
            return false;
    }
    else
        return false;
}

int range(int p, const char *req, node *pere, int d, int f)
{
    if(req[p] != '\0' && (req[p] >= d && req[p] <= f)) {
        putValueInNode(p, 1, "range", pere);
        return 1;
    }
    else
        return false;
}

int num(int p, const char *req, node *pere, int *v, int n)
{
    for(int i=0; i<n; i++) {
        if(req[p+i] != '\0' && req[p+i] == v[i]) {
            putValueInNode(p, n, "num", pere);
            return n;
        }
        else
            return false;
    }
}

int case_insensitive_char(int p, const char *req, node *pere, char c) /* terminal */
{
    if(req[p] != '\0' && req[p] == c) {
        putValueInNode(p, 1, "case_insensitive_string", pere);
        return 1;
    }
    else
        return false;
}

int case_insensitive_string(int p, const char *req, node *pere, char *c) /* terminal */
{
    int now = p;
    while(*c) {
        if(req[now] && tolower(*c++) == tolower(req[now])) {
            now++;
        }
        else
            return false;
    }
    putValueInNode(p, now-p, "case_insensitive_string", pere);
    return now-p;
}