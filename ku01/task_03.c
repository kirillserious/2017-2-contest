Егоров Кирилл [205 группа, 3 семестр, 2017-2018]: Source for run 1706
Settings
Registration
Info
Summary
Submissions
User standings
Submit clar
Clars
Logout [s02160055]

00:48:41 / 1 unread message(s) / RUNNING
Source code 
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

int
is_dot (char *buf, int i)
{
    if ((i > 1) &&
            (buf[i-1] == '.') &&
            (buf[i-2] == '/')) {
        return 1;
    } else {
        return 0;
    }
}

int
is_two_dots (char *buf, int i)
{
    if ((i > 2) &&
            (buf[i-1] == '.') &&
            (buf[i-2] == '.') &&
            (buf[i-3] == '/')) {
        return 1;
    } else {
        return 0;
    }
}

void move_on(char *ptr, int num)
{

    while (*ptr != '\0') {
        *(ptr - num) = *ptr;
        ptr++;
    }
    *(ptr - num) = '\0';
}

int
find_slash(char *ptr)
{
    ptr--;
    int two_fl = 0, res = 0;
    while (two_fl != 2) {
        if (*(ptr - res) == '/') {
            two_fl++;
        }
        res++;
    }
    return res;
}

void
normalize_path (char *buf)
{
    int i = 0;
    while (1) {
        
        int zero_fl;
        zero_fl = (buf[i] == '\0') ? 1 : 0;

        if ((buf[i] =='/') || (buf[i] == '\0')) {
            
            if (is_dot(buf, i)) {
                move_on(buf + i, 2);
                i -= 2;
            } else if (is_two_dots(buf, i)) {
                if (i == 3) {
                    move_on(buf + i, 3);
                    i -= 3;
                } else {
                    int j = find_slash(buf + i);
                    move_on(buf + i, j);
                    i = i - j;
                }
            }
        }

        if (zero_fl) {
            break;
        }

        i++;
    }

    if (!i) {
        buf[0] = '/';
        buf[1] = '\0';
    } else if ((i != 1) && (buf[i - 1] == '/')) {
        
        buf[i - 1] = '\0';
    }


}