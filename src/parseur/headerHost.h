#ifndef __HEADERHOST_H__
#define __HEADERHOST_H__

/*Prototype*/

int Host_header(int *p, const char *req, node *pere);

    int Host(int *p, const char *req, node *pere);

        int uri_host(int *p, const char *req, node *pere);

            int host(int *p, const char *req, node *pere);

                int IP_literal(int *p, const char *req, node *pere);

                    int IPv6address(int *p, const char *req, node *pere);

                    int IPvFuture(int *p, const char *req, node *pere);

                int IPv4address(int *p, const char *req, node *pere);

                    int dec_octet(int *p, const char *req, node *pere);

                int h16(int *p, const char *req, node *pere);

                int ls32(int *p, const char *req, node *pere);

                int reg_name(int *p, const char *req, node *pere);

        int port(int *p, const char *req, node *pere);


#endif