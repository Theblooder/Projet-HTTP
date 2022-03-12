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


#define true 1
#define false 0


int HTTP_message(int *p, const char *req, node *pere)
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
                if(message_body(p, req, createFils(pere))) {
                    putValueInNode(save, *p-save, "HTTP_message", pere);
                    return true;
                }
            }
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
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
    // else if(Unknow_header(p, req, fils)) {
    //     putValueInNode(save, *p-save, "header_field", pere);
    //     return true;
    // }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int message_body(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;

        if(OCTET(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "message_body", pere);
        return true;
    }

    *p = save;
    purgeNode(pere);
    return true;
}