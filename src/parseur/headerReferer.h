#ifndef __HEADERREFERER_H__
#define __HEADERREFERER_H__

/*Prototype*/
int Referer_header(int *p, const char *req, node *pere);

    int Referer(int *p, const char *req, node *pere);

        int absolute_URI(int *p, const char *req, node *pere);

            int scheme(int *p, const char *req, node *pere);

            int hier_part(int *p, const char *req, node *pere);

                int authority(int *p, const char *req, node *pere);

                    int userinfo(int *p, const char *req, node *pere);

                int path_abempty(int *p, const char *req, node *pere);

                int path_absolute(int *p, const char *req, node *pere);

                    int segment_nz(int *p, const char *req, node *pere);

                int path_rootless(int *p, const char *req, node *pere);

                int path_empty(int *p, const char *req, node *pere);

        int partial_URI(int *p, const char *req, node *pere);

            int relative_part(int *p, const char *req, node *pere);

                int path_noscheme(int *p, const char *req, node *pere);

                    int segment_nz_nc(int *p, const char *req, node *pere);

#endif