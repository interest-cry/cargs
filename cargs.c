#include "cargs.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_log(const char* pre, const char* param_name) {
  printf("local:%s ,please input (%s) argument, and the value\n", pre,
         param_name);
}
int parse_one_arg(int argc, char* argv[], Argument* arg) {
  for (int i = 1; i < argc;) {
    // args->arg[i].
    int status = 0;
    char name_tmp[NAME_LEN] = {0};
    memset(name_tmp, 0, sizeof(name_tmp));
    char value[VALUVE_LEN] = {0};
    memset(value, 0, sizeof(value));
    char* index = strchr(argv[i], '=');
    // no "="
    if (index == NULL) {
      strcpy(name_tmp, argv[i]);
      if (i + 1 < argc) {
        strcpy(value, argv[i + 1]);
      } else {
        print_log("11", argv[i]);
        return -1;
      }
    } else {  // has '='
      status = 1;
      memcpy(name_tmp, argv[i], index - argv[i]);
      strcpy(value, index + 1);
    }
    // name
    char name[NAME_LEN] = {0};
    memset(name, 0, sizeof(name));

    if (!strstr(name_tmp, "--")) {  // no "--"
      if (name_tmp[0] == '-') {
        strcpy(name, name_tmp + 1);
      } else {
        strcpy(name, name_tmp);
      }

    } else {
      strcpy(name, name_tmp + 2);
    }
    // name not equal
    if (strcmp(name, arg->name)) {
      //   if (status) {  // has '='
      //     i += 1;
      //   } else {  // no "="
      //     i += 2;
      //   }
      i += 1;
      if (i >= argc) {
        // todo:打印日志
        printf("===========>>>>>>>i:%d\n", i);
        print_log("22", arg->name);
        return -1;
      }
      continue;
    }
    // name equal
    if (strcmp(arg->type, "int")) {
      strcpy(arg->value_char, value);
      return 0;

    } else {  // type int
      arg->value_int = atoi(value);
      return 0;
    }
  }
}
int parse_args(int argc, char* argv[], Arguments* args) {
  int flag = 0;
  for (int i = 1; i < args->num; i++) {
    flag = parse_one_arg(argc, argv, &args->arg[i]);
    printf("#############i:%d\n", i);
    if (flag) {
      printf("================\n");
      return flag;
    }
  }
  return 0;
}
void print_args(const char* prefix, Arguments args) {
  printf("********%s********\n", prefix);
  for (int i = 1; i < args.num; i++) {
    printf("\nindex:%d\n", i);
    printf("===type:%s, %ld\n", args.arg[i].type, strlen(args.arg[i].type));
    printf("===name:%s\n", args.arg[i].name);
    if (!strcmp(args.arg[i].type, "char")) {
      printf("===value_char:%s\n", args.arg[i].value_char);
    } else {
      printf("===value_int>>:%d\n", args.arg[i].value_int);
    }
  }
}
#if 1
int main(int argc, char* argv[]) {
  Arguments args = {{{"", "", "", 0},
                     {"char", "fn", "", 0},
                     {"char", "tm", "", 0},
                     {"char", "nt", "", 0},
                     {"char", "num", "", 0},
                     {"char", "level", "", 0}},
                    6};
  print_args("before parse", args);
  int fg = parse_args(argc, argv, &args);
  if (fg) {
    printf("parse argument error...\n");
    return fg;
  }
  print_args("after parse", args);
}
#endif