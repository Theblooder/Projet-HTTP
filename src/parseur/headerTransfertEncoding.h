#ifndef __HEADERCTRANSFERTENCODING_H__
#define __HEADERCTRANSFERTENCODING_H__

/*Prototype*/
int Transfer_Encoding_header(int p, const char *req, node *pere);

    int Transfer_Encoding(int p, const char *req, node *pere);

        int OWS__AND__case__AND__optional_transfert_coding(int p, const char *req, node *pere);

            int transfer_coding(int p, const char *req, node *pere);

                int transfer_extension(int p, const char *req, node *pere);

                    int OWS__AND__case__AND__OWS__AND__transfert(int p, const char *req, node *pere);

                    int transfert_parameter(int p, const char *req, node *pere);

            int OWS__AND__transfert_coding(int p, const char *req, node *pere);

#endif