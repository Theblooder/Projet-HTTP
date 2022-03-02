#ifndef __HEADERACCEPT_H__
#define __HEADERACCEPT_H__

/*Prototype*/

int Accept_header(int p, const char *req, node *pere);

    int Accept(int p, const char *req, node *pere);

    int __accept__1(int p, const char *req, node *pere);

        int media_range__AND__accept_params(int p, const char *req, node *pere);

        int media_range(int p, const char *req, node *pere);

            int __media_range__1(int p, const char *req, node *pere);

                int type__AND__case__AND__subtype(int p, const char *req, node *pere);

                int type__AND__case(int p, const char *req, node *pere);

        int accept_params(int p, const char *req, node *pere);

            int weight(int p, const char *req, node *pere);

                int qvalue(int p, const char *req, node *pere);

                    int qvalue__1(int p, const char *req, node *pere);

                        int optional__case__AND__3DIGITS(int p, const char *req, node *pere);

                    int qvalue__2(int p, const char *req, node *pere);

                        int optional__case__AND__3ZERO(int p, const char *req, node *pere);

            int accept_ext(int p, const char *req, node *pere);

                int optional__case__AND__token__AND__case__quoted_string(int p, const char *req, node *pere);

    int __accept__2(int p, const char *req, node *pere);

        int optional__accept__2(int p, const char *req, node *pere);

#endif