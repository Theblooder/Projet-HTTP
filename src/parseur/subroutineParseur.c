#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"
#include "subroutineFirstLine.h"

#include "headerConnection.h"
#include "headerContentLength.h"


#define true 1
#define false 0


int HTTP_message(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = start_line(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = header_field__AND__CRLF(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);

    purgeNode(fils);
    putValueInNode(p, now-p, "HTTP_message", pere);
    return now-p;

    if(!(len = CRLF(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = message_body(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "HTTP_message", pere);
    return now-p;
}

int header_field__AND__CRLF(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = header_field(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = CRLF(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int header_field(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = Connection_header(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Content_Length_Header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Content_Type_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Cookie_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Transfer_Encoding_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Expect_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Host_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    return false;

    if(len = Unknow_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}


int Content_Type_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Content-Type"))) {
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

    if(!(len = Content_Type(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Content_Type_header", pere);
    return now-p;
}

int Content_Type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = media_type(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "Content_Type", pere);
    return now-p;
}

int media_type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = type(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '/'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = subtype(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = OWS__AND__case__AND__OWS__AND__parameter(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "media_type", pere);
    return now-p;
}

int type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "type", pere);
    return now-p;
}

int subtype(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "subtype", pere);
    return now-p;
}

int OWS__AND__case__AND__OWS__AND__parameter(int p, const char *req, node *pere)
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

    if(!(len = parameter(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int parameter(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = token__AND__quoted_string(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "parameter", pere);
    return now-p;
}

int token__AND__quoted_string(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = token(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = quoted_string(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int quoted_string(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = DQUOTE(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = qdtext__AND__quoted_pair(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);

    if(!(len = DQUOTE(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "quoted_string", pere);
    return now-p;
}

int qdtext__AND__quoted_pair(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = qdtext(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = quoted_pair(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int qdtext(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = HTAB(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = SP(p, req, fils)) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_char(p, req, fils, '!')) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x23, 0x5B)) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = obs_text(p, req, fils)) {
        putValueInNode(p, len, "qdtext", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int quoted_pair(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '\\'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = HTAB_SP_VCHAR_obs_text(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "quoted_pair", pere);
    return now-p;
}

int HTAB_SP_VCHAR_obs_text(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = HTAB(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = SP(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = VCHAR(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = obs_text(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int Cookie_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Cookie:"))) {
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

    if(!(len = cookie_string(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Cookie_header", pere);
    return now-p;
}

int cookie_string(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = cookie_pair(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = case__AND__SP__AND__cookie_pair(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "cookie_string", pere);
    return now-p;
}

int cookie_pair(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = cookie_name(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = cookie_value(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "cookie_pair", pere);
    return now-p;
}

int cookie_name(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "cookie_name", pere);
    return now-p;
}

int cookie_value(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(len = DQUOTE__AND__cookie_octet__AND__DQUOTE(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "cookie_value", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    int nbr = 0;
    while(len = cookie_octet(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    if(now-p != 0)
        putValueInNode(p, len, "cookie_value", pere);
    return now-p;
}

int DQUOTE__AND__cookie_octet__AND__DQUOTE(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = DQUOTE(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = cookie_octet(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);

    if(!(len = DQUOTE(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int cookie_octet(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    int v[1] = {0x21};
    if(len = num(p, req, fils = createFils(pere), v, 1)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x23, 0x2B)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x2D, 0x3A)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x3C, 0x5B)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int case__AND__SP__AND__cookie_pair(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), ';'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = cookie_pair(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

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

int Expect_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Expect"))) {
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

    if(!(len = Expect(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Expect_header", pere);
    return now-p;
}

int Expect(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "100-continue"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "Expect", pere);
    return now-p;
}

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

int message_body(int p, const char *req, node *pere)
{

}





/*==============================================================*/

/*
int message(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = debut(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    int nbr = 0;
    while(len = corps(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    if(nbr < 2) {
        return false;
    }

    if(!(len = ponctuation(now, req, fils))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }

    now += len;

    if(!(len = fin(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    
    now += len;

    if(!(len = caseInsensitive(now, req, '\n', fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }


    now += len;

    putValueInNode(p, now-p, "message", pere);

    return now-p;
}

int debut(int p, const char *req, node *pere)
{
    int now = p;
    if(req[now] == 's' || req[now] == 'S') {
        now++;
        if(req[now] == 't' || req[now] == 'T') {
            now++;
            if(req[now] == 'a' || req[now] == 'A') {
                now++;
                if(req[now] == 'r' || req[now] == 'R') {
                    now++;
                    if(req[now] == 't' || req[now] == 'T') {
                        putValueInNode(p, 5, "debut", pere);
                        return 5;
                    }
                }
            }
        }
    }
    return false;
}

int corps(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = corps1(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "corps", pere);
        return len;
    }
    else
        purgeNode(fils);

    if(len = corps2(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "corps", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int corps1(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(!(len = mot(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    if(!(len = ponctuation(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "corps1", pere);
    return now-p;
}

int corps2(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(!(len = nombre(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    if(!(len = separateur(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "corps2", pere);
    return now-p;
}

int mot(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = alpha(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    if(nbr == 0) {
        return false;
    }

    if(!(len = separateur(now, req, fils))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "mot", pere);
    return now-p;
}

int nombre(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = digit(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr == 0) {
        return false;
    }
    
    putValueInNode(p, now-p, "nombre", pere);
    return now-p;
}

int alpha(int p, const char *req, node *pere)
{
    if((req[p] >= 65 && req[p] <= 90) || (req[p] >= 97 && req[p] <= 122)) {
        putValueInNode(p, 1, "alpha", pere);
        return 1;
    }
    else
        return false;
}

int digit(int p, const char *req, node *pere)
{
    if(req[p] >= 48 && req[p] <= 57) {
        putValueInNode(p, 1, "digit", pere);
        return 1;
    }
    else
        return false;
}

int ponctuation(int p, const char *req, node *pere)
{
    if(req[p] == ',') {
        putValueInNode(p, 1, "ponctuation", pere);
        return 1;
    }
    else if(req[p] == '.') {
        putValueInNode(p, 1, "ponctuation", pere);
        return 1;
    }
    else if(req[p] == '!') {
        putValueInNode(p, 1, "ponctuation", pere);
        return 1;
    }
    else if(req[p] == '?') {
        putValueInNode(p, 1, "ponctuation", pere);
        return 1;
    }
    else if(req[p] == ':') {
        putValueInNode(p, 1, "ponctuation", pere);
        return 1;
    }
    else
        return false;
}

int separateur(int p, const char *req, node *pere)
{
    if(req[p] == ' ') {
        putValueInNode(p, 1, "separateur", pere);
        return 1;
    }
    else if(req[p] == '\t') {
        putValueInNode(p, 1, "separateur", pere);
        return 1;
    }
    else if(req[p] == '-') {
        putValueInNode(p, 1, "separateur", pere);
        return 1;
    }
    else if(req[p] == '_') {
        putValueInNode(p, 1, "separateur", pere);
        return 1;
    }
    else
        return false;
}

int fin(int p, const char *req, node *pere)
{
    int now = p;
    if(req[now] == 'f' || req[now] == 'F') {
        now++;
        if(req[now] == 'i' || req[now] == 'I') {
            now++;
            if(req[now] == 'n' || req[now] == 'N') {
                putValueInNode(p, 3, "fin", pere);
                return 3;
            }
        }
    }
    return false;
}

int caseInsensitive(int p, const char *req, char c, node *pere)
{
    if(req[p] == c) {
        putValueInNode(p, 1, "caseInsensitive", pere);
        return 1;
    }
    else
        return false;
}

*/