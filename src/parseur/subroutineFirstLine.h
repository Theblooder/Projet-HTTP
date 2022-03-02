#ifndef __SUBROUTINEFIRSTLINE_H__
#define __SUBROUTINEFIRSTLINE_H__

/*Prototype*/

int start_line(int p, const char *req, node *pere);

    int request_line(int p, const char *req, node *pere);

        int method(int p, const char *req, node *pere);

            /* Token */

        /* SP */

        int request_target(int p, const char *req, node *pere);

            int origin_form(int p, const char *req, node *pere);

                int absolute_path(int p, const char *req, node *pere);

                    int case__AND__segment(int p, const char *req, node *pere);

                    /* case */

                    /* segment */

                int case__AND__query(int p, const char *req, node *pere);

                /* case */

                int query(int p, const char *req, node *pere);

                    int pchar__AND__cases(int p, const char *req, node *pere);

        /* SP */

        int HTTP_version(int p, const char *req, node *pere);

/* terminal */  int HTTP_name(int p, const char *req, node *pere);

            /* case */

            /* DIGIT */

            /* case */

            /* DIGIT */

        /* CRLF */

    int status_line(int p, const char *req, node *pere);

        /* HTTP_version */

        /* SP */

        int status_code(int p, const char *req, node *pere);

        /* SP */

        int reason_phrase(int p, const char *req, node *pere);

            int __reason_phrase__(int p, const char *req, node *pere);

        /* CRLF */

#endif