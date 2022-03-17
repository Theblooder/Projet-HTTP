#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerExpect.h"


#define true 1
#define false 0

int Expect_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Expect")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Expect(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Expect_header", pere);
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

int Expect(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "100-continue")) {
        putValueInNode(save, *p-save, "Expect", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}