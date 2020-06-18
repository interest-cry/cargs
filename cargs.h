#ifndef _H_CARGS
#define _H_CARGS

#ifdef __cplusplus
extern "C" {
#endif
#define NAME_LEN 32
#define VALUVE_LEN 64
#define ARG_COUNT 32
typedef struct Argument {
  char type[NAME_LEN];
  char name[NAME_LEN];
  char value_char[VALUVE_LEN];
  int value_int;

} Argument;

typedef struct Arguments {
  Argument arg[ARG_COUNT];
  int num;  //参数个数
  // int (*parse)(const char*, Argument*);
} Arguments;

int parse_args(int argc, char* argv[], Arguments* args);
#ifdef __cplusplus
}
#endif
#endif