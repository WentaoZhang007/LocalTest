#include "sv_common.h"

int main ()
{

    unsigned char uc_status ;
    uc_status = '\xBC';
    printf("uc_status:%x.",uc_status);
    uc_status = '\x02';
    printf("uc_status:%x.",uc_status);
    uc_status = '\x2';
    printf("uc_status:%x.",uc_status);

    return 0;
}