#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Constants
{
    GPOUPS_MAX = 32,
    LENGTH_MAX = 1022,
    MASKVAL = 7
};

int in_grps (gid_t grp, int grp_cnt);

uid_t uid = 0;
gid_t gid_list[GPOUPS_MAX];
unsigned int operation;

int
main (int argc, char* argv[])
{
    //scan uid
    char line[LENGTH_MAX];
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%u", &uid);

    //scan gid_list
    int grp_cnt = 0;
    fgets(line, sizeof(line), stdin);
    char *tmp;
    tmp = line;
    unsigned int off = 0;
    while (sscanf(tmp, "%u%n", &gid_list[grp_cnt], &off) != EOF){
        tmp += off;
        grp_cnt++;
    }

    //scan operation
    fgets(line, sizeof(line), stdin);


    sscanf(line, "%u", &operation);


    //main cycle
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (line[0] == '\n') {
            continue;
        }

        char *filename;
        uid_t f_uid;
        gid_t f_gid;
        unsigned int perm;
        int i;

        sscanf(line, "%u%u%o%n", &f_uid, &f_gid, &perm, &i);
        filename = line + i;
        while (isspace(filename[0])) {
            filename ++;
        }
        i = 0;
        while (filename[i] != '\0') {
            i++;
        }
        i --;
        if (filename[i] == '\n') {
            i--;


        }
        while(isspace(filename[i])) {
            i--;
        }
        filename[i + 1] = '\n';
        filename[i + 2] = '\0';

        //prov
        if (f_uid == uid) {
            if ( ((perm >> 6) & operation) == operation) {
                printf("%s", filename);
            }
            continue;
        } else if (in_grps(f_gid, grp_cnt)) {
            if ( ((perm >> 3) & MASKVAL & operation) == operation ) {
                printf("%s", filename);
            }
            continue;
        } else {
            if ( (perm & MASKVAL & operation) == operation) {
                printf("%s", filename);
            }


            continue;
        }
    }


}



int
in_grps (gid_t grp, int cnt) 
{
    int fl = 0;
    for (int i = 0; i < cnt; i++) {
        if (gid_list[i] == grp) {
            fl = 1;
            break;
        }
    }

    return fl ? 1 : 0;
}