#ifndef __HEADERCOOKIE_H__
#define __HEADERCOOKIE_H__

/*Prototype*/

int Cookie_header(int p, const char *req, node *pere);

    int cookie_string(int p, const char *req, node *pere);

        int cookie_pair(int p, const char *req, node *pere);

            int cookie_name(int p, const char *req, node *pere);

            int cookie_value(int p, const char *req, node *pere);

                int DQUOTE__AND__cookie_octet__AND__DQUOTE(int p, const char *req, node *pere);

                int cookie_octet(int p, const char *req, node *pere);

        int case__AND__SP__AND__cookie_pair(int p, const char *req, node *pere);

#endif