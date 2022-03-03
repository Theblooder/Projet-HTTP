#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerTransfertEncoding.h"


#define true 1
#define false 0


int Transfer_Encoding_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Transfer-Encoding"))) {
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

    if(!(len = Transfer_Encoding(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Transfer_Encoding_header", pere);
    return now-p;
}

int Transfer_Encoding(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = case__AND__OWS(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);

    if(!(len = transfer_coding(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    nbr = 0;
    while(len = OWS__AND__case__AND__optional_transfert_coding(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    
    putValueInNode(p, now-p, "Transfer_Encoding", pere);
    return now-p;
}

int transfer_coding(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = case_insensitive_string(p, req, fils = createFils(pere), "chunked")) {
        putValueInNode(p, len, "transfer_coding", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_string(p, req, fils, "compress")) {
        putValueInNode(p, len, "transfer_coding", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_string(p, req, fils, "deflate")) {
        putValueInNode(p, len, "transfer_coding", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_string(p, req, fils, "gzip")) {
        putValueInNode(p, len, "transfer_coding", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = transfer_extension(p, req, fils)) {
        putValueInNode(p, len, "transfer_coding", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int transfer_extension(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = OWS__AND__case__AND__OWS__AND__transfert(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "transfer_extension", pere);
    return now-p;
}

int OWS__AND__case__AND__OWS__AND__transfert(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils, ';'))) {
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

    if(!(len = transfert_parameter(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int transfert_parameter(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = BWS(now, req, fils = createFrere(fils)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils, '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = BWS(now, req, fils = createFrere(fils)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = token__AND__quoted_string(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "transfert_parameter", pere);
    return now-p;
}

int OWS__AND__case__AND__optional_transfert_coding(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils, ','))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS__AND__transfert_coding(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int OWS__AND__transfert_coding(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = transfer_coding(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}