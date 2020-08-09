#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "cargs.h"
#if 1
int main(int argc, char* argv[]) {
    char fname[32] = {0}, time[32] = {0};
    int num = 0, nt = 0;
    args_init();
    args_set_string(fname, "fn", "1111", "file name");
    args_set_string(time, "tm", "11119999", "tmie name");
    args_set_int(&num, "num", 77777, "number");
    args_set_int(&nt, "nt", 1, "thread number");
    // print_args(NULL, &Args);

    args_parse(argc, argv);
    printf("fname:%s,time:%s,num:%d,nt:%d\n", fname, time, num, nt);
}
#endif