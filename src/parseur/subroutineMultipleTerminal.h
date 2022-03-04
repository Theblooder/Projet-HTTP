#ifndef __SUBROUTINEMULTIPLETERMINAL_H__
#define __SUBROUTINEMULTIPLETERMINAL_H__

/*Prototype*/

/* Can be multiple times */

    int token(int p, const char *req, node *pere);
    int tchar(int p, const char *req, node *pere); /* half terminal */

    int segment(int p, const char *req, node *pere); /* half terminal */
    int pchar(int p, const char *req, node *pere);

    int obs_text(int p, const char *req, node *pere);
    

    /* Terminal */

    int unreserved(int p, const char *req, node *pere);
    int pct_encoded(int p, const char *req, node *pere);
    int sub_delims(int p, const char *req, node *pere);
    int HEXDIG(int p, const char *req, node *pere);
    int OCTET(int p, const unsigned char *req, node *pere);
    int DQUOTE(int p, const char *req, node *pere);
    int OWS(int p, const char *req, node *pere);
    int BWS(int p, const char *req, node *pere);
    int SP__OR__HTAB(int p, const char *req, node *pere);
    int ALPHA(int p, const unsigned char *req, node *pere);
    int DIGIT(int p, const char *req, node *pere);
    int CRLF(int p, const char *req, node *pere);
    int SP(int p, const char *req, node *pere);
    int HTAB(int p, const char *req, node *pere);
    int VCHAR(int p, const unsigned char *req, node *pere);
    int range(int p, const unsigned char *req, node *pere, int d, int f);
    int num(int p, const char *req, node *pere, int *v, int n);
    int case_insensitive_char(int p, const char *req, node *pere, char c);
    int case_insensitive_string(int p, const char *req, node *pere, char *c);

    int case__AND__OWS(int p, const char *req, node *pere);
    
    int token__AND__quoted_string(int p, const char *req, node *pere);

        int quoted_string(int p, const char *req, node *pere);

            int qdtext__AND__quoted_pair(int p, const char *req, node *pere);

            int quoted_pair(int p, const char *req, node *pere);

                int HTAB_SP_VCHAR_obs_text(int p, const char *req, node *pere);

            int qdtext(int p, const char *req, node *pere);


#endif