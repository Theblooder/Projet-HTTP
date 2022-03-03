#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerHost.h"


#define true 1
#define false 0

int Host_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Host"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = Host(now, req, fils))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = OWS(now, req, fils))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Host_header", pere);
    return now-p;
}

int Host(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = uri_host(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case__AND__port(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Host", pere);
    return now-p;
}

int uri_host(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = host(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "uri_host", pere);
    return now-p;
}

int host(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = IP_literal(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "host", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv4address(p, req, fils)) {
        putValueInNode(p, len, "host", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = reg_name(p, req, fils)) {
        putValueInNode(p, len, "host", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int IP_literal(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '['))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = IPv6address__OR__IPvFuture(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ']'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "IP_literal", pere);
    return now-p;
}

int IPv6address__OR__IPvFuture(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = IPv6address(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPvFuture(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int IPv6address(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = IPv6address__1(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__2(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__3(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__4(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__5(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__6(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__7(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__8(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv6address__9(p, req, fils)) {
        putValueInNode(p, len, "IPv6address", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int IPv6address__1(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = h16(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__3(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = h16(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__4(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 1))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__5(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 2))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;


    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__6(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 3))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__7(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 4))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = ls32(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__8(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 5))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPv6address__9(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __IPv6__optional__special(now, req, fils = createFils(pere), 6))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils, "::"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int __IPv6__optional__special(int p, const char *req, node *pere, int n)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = h16(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = case__AND__h16(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr > n) {
        return false;
    }

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int case__AND__h16(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int IPvFuture(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "v"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = HEXDIG(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    if(nbr == 0) {
        return false;
    }

    if(!(len = case_insensitive_char(now, req, fils, '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    nbr = 0;
    while(len = unreserved__OR__sub_delims__OR__case(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr == 0) {
        return false;
    }

    putValueInNode(p, now-p, "IPvFuture", pere);
    return now-p;
}

int unreserved__OR__sub_delims__OR__case(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = unreserved(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = sub_delims(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_char(p, req, fils, ':')) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int IPv4address(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = dec_octet(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = dec_octet(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = dec_octet(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = dec_octet(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "IPv4address", pere);
    return now-p;
}

int dec_octet(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = dec_octet__1(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "dec_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = dec_octet__2(p, req, fils)) {
        putValueInNode(p, len, "dec_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = dec_octet__3(p, req, fils)) {
        putValueInNode(p, len, "dec_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = dec_octet__4(p, req, fils)) {
        putValueInNode(p, len, "dec_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = DIGIT(p, req, fils)) {
        putValueInNode(p, len, "dec_octet", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int dec_octet__1(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "25"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = range(now, req, fils = createFrere(fils), 0x30, 0x35))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int dec_octet__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "2"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = range(now, req, fils = createFrere(fils), 0x30, 0x34))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int dec_octet__3(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "1"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int dec_octet__4(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = range(now, req, fils = createFils(pere), 0x31, 0x39))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int h16(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = HEXDIG(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr < 1 || nbr > 4) {
        return false;
    }
    
    putValueInNode(p, now-p, "h16", pere);
    return now-p;
}

int ls32(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = h16__AND__case__AND__h16(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "ls32", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = IPv4address(p, req, fils)) {
        putValueInNode(p, len, "ls32", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int h16__AND__case__AND__h16(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = h16(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = h16(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int reg_name(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = unreserved__OR__sub_delims__OR__pct_encoded(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "reg_name", pere);
    return now-p;
}

int unreserved__OR__sub_delims__OR__pct_encoded(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = unreserved(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = pct_encoded(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = sub_delims(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int case__AND__port(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = port(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int port(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = DIGIT(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "port", pere);
    return now-p;
}