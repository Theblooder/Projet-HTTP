#ifndef __HEADERHOST_H__
#define __HEADERHOST_H__

/*Prototype*/

int Host_header(int p, const char *req, node *pere);

    int Host(int p, const char *req, node *pere);

        int uri_host(int p, const char *req, node *pere);

            int host(int p, const char *req, node *pere);

                int IP_literal(int p, const char *req, node *pere);

                    int IPv6address__OR__IPvFuture(int p, const char *req, node *pere);

                    int IPv6address(int p, const char *req, node *pere);

                        int IPv6address__1(int p, const char *req, node *pere);

                        int IPv6address__2(int p, const char *req, node *pere);

                        int IPv6address__3(int p, const char *req, node *pere);

                        int IPv6address__4(int p, const char *req, node *pere);

                        int IPv6address__5(int p, const char *req, node *pere);

                        int IPv6address__6(int p, const char *req, node *pere);

                        int IPv6address__7(int p, const char *req, node *pere);

                        int IPv6address__8(int p, const char *req, node *pere);

                        int IPv6address__9(int p, const char *req, node *pere);

                        int   __IPv6__optional__special(int p, const char *req, node *pere, int n);

                            int case__AND__h16(int p, const char *req, node *pere);

                    int IPvFuture(int p, const char *req, node *pere);

                        int unreserved__OR__sub_delims__OR__case(int p, const char *req, node *pere);

                int IPv4address(int p, const char *req, node *pere);

                    int dec_octet(int p, const char *req, node *pere);

                        int dec_octet__1(int p, const char *req, node *pere);

                        int dec_octet__2(int p, const char *req, node *pere);

                        int dec_octet__3(int p, const char *req, node *pere);

                        int dec_octet__4(int p, const char *req, node *pere);

                int h16(int p, const char *req, node *pere);

                int ls32(int p, const char *req, node *pere);

                    int h16__AND__case__AND__h16(int p, const char *req, node *pere);

                int reg_name(int p, const char *req, node *pere);

                    int unreserved__OR__sub_delims__OR__pct_encoded(int p, const char *req, node *pere);

        int case__AND__port(int p, const char *req, node *pere);

        int port(int p, const char *req, node *pere);


#endif