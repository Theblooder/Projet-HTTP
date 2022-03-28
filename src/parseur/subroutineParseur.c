#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"
#include "subroutineFirstLine.h"

#include "headerConnection.h"
#include "headerContentLength.h"
#include "headerContentType.h"
#include "headerCookie.h"
#include "headerTransfertEncoding.h"
#include "headerExpect.h"
#include "headerHost.h"
#include "headerAccept.h"
#include "headerAcceptCharset.h"
#include "headerAcceptEncoding.h"
#include "headerAcceptLanguage.h"
#include "headerUserAgent.h"
#include "headerReferer.h"
#include "headerAuthorization.h"


#define true 1
#define false 0


int HTTP_message(int *p, const char *req, node *pere, int len)
{
    int save = *p;
    node *fils;

    if(start_line(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(header_field(p, req, fils = createFils(pere))) {
                if(CRLF(p, req, createFils(pere))) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            if(CRLF(p, req, createFils(pere))) {
                if(message_body(p, req, createFils(pere), len)) {
                    putValueInNode(save, *p-save, "HTTP_message", pere);
                    return true;
                }
            }
        }
    }
    
    *p = save;
    purgeFils(pere);
    return false;
}

int header_field(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(Connection_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Content_Length_Header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Content_Type_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Cookie_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Transfer_Encoding_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Expect_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Host_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Accept_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Accept_Charset_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Accept_Encoding_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Accept_Language_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(User_Agent_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Referer_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(Authorization_header(p, req, fils)) {
        putValueInNode(save, *p-save, "header_field", pere);
        return true;
    }
    else if(field_name(p, req, fils)) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(field_value(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "header_field", pere);
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

int field_name(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "field_name", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int field_value(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(field_content(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(obs_fold(p, req, fils)) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "field_value", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return true;
}

int field_content(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;

    if(field_vchar(p, req, fils = createFils(pere))) {
        int c = *p;
        int nbr = 0;
        int c2;
        while(1) {
            c2 = *p;
            fils2 = createFils(pere);

            if(SP(p, req, fils2)) {
                nbr++;
                continue;
            }
            else if(HTAB(p, req, fils2)) {
                nbr++;
                continue;
            }
            purgeNodeAndRightFrere(fils2);
            *p = c2;
            break;
        }
        if(nbr >= 1) {
            if(field_vchar(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "field_content", pere);
                return true;
            }
        }
        if(fils->frere != NULL) {
            purgeNodeAndRightFrere(fils->frere);
        }
        *p = c;
        putValueInNode(save, *p-save, "field_content", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int field_vchar(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(VCHAR(p, req, fils)) {
        putValueInNode(save, *p-save, "field_vchar", pere);
        return true;
    }
    else if(obs_text(p, req, fils)) {
        putValueInNode(save, *p-save, "field_vchar", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int obs_fold(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(CRLF(p, req, createFils(pere))) {
        int c;
        int nbr = 0;
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
            putValueInNode(save, *p-save, "obs_fold", pere);
            return true;
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int message_body(int *p, const char *req, node *pere, int len)
{
    int save = *p;
    
    while(*p < len) {
        OCTET(p, req, createFils(pere));
    }
    putValueInNode(save, *p-save, "message_body", pere);
    return true;
}