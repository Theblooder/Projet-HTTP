#ifndef __SUBROUTINEPARSEUR_H__
#define __SUBROUTINEPARSEUR_H__

/*Prototype*/

int HTTP_message(int p, const char *req, node *pere);

    

    int header_field__AND__CRLF(int p, const char *req, node *pere);

    int header_field(int p, const char *req, node *pere);

        int Content_Length_Header(int p, const char *req, node *pere);

            int Content_Length(int p, const char *req, node *pere);

        int Content_Type_header(int p, const char *req, node *pere);

            int Content_Type(int p, const char *req, node *pere);

                int media_type(int p, const char *req, node *pere);

                    int type(int p, const char *req, node *pere);

                    int subtype(int p, const char *req, node *pere);

                    int OWS__AND__case__AND__OWS__AND__parameter(int p, const char *req, node *pere);

                    int parameter(int p, const char *req, node *pere);

                        int token__AND__quoted_string(int p, const char *req, node *pere);

                        int quoted_string(int p, const char *req, node *pere);

                            int qdtext__AND__quoted_pair(int p, const char *req, node *pere);

                            int quoted_pair(int p, const char *req, node *pere);

                                int HTAB_SP_VCHAR_obs_text(int p, const char *req, node *pere);

                            int qdtext(int p, const char *req, node *pere);

        int Cookie_header(int p, const char *req, node *pere);

            int cookie_string(int p, const char *req, node *pere);

                int cookie_pair(int p, const char *req, node *pere);

                    int cookie_name(int p, const char *req, node *pere);

                    int cookie_value(int p, const char *req, node *pere);

                        int DQUOTE__AND__cookie_octet__AND__DQUOTE(int p, const char *req, node *pere);

                        int cookie_octet(int p, const char *req, node *pere);

                int case__AND__SP__AND__cookie_pair(int p, const char *req, node *pere);

        int Transfer_Encoding_header(int p, const char *req, node *pere);

            int Transfer_Encoding(int p, const char *req, node *pere);

                int OWS__AND__case__AND__optional_transfert_coding(int p, const char *req, node *pere);

                    int transfer_coding(int p, const char *req, node *pere);

                        int transfer_extension(int p, const char *req, node *pere);

                            int OWS__AND__case__AND__OWS__AND__transfert(int p, const char *req, node *pere);

                            int transfert_parameter(int p, const char *req, node *pere);

                    int OWS__AND__transfert_coding(int p, const char *req, node *pere);

        int Expect_header(int p, const char *req, node *pere);

            int Expect(int p, const char *req, node *pere);

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

        int Unknow_header(int p, const char *req, node *pere);

    /* CRLF */

    int message_body(int p, const char *req, node *pere);


#endif
