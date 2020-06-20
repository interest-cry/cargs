#include "cargs.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 32
#define VALUVE_LEN 64
#define ARG_COUNT 32
enum { STRING, INT };

typedef struct Argument {
  int type;             // 8,0:string;1:int
  int* dst_int;         // 8
  char* dst_string;     // 8
  char name[NAME_LEN];  // 32
  char use[NAME_LEN];   // 32

} Argument;

typedef struct Arguments {
  Argument arg[ARG_COUNT];
  int len;  //参数个数
} Arguments;
Arguments Args;
void print_log(const char* pre, const char* param_name) {
  printf("local:%s ,please input (%s) argument, and the value\n", pre,
         param_name);
}
void print_value(const char* pre, Argument a) {
  printf("%stype:%d,name:%s,", pre, a.type, a.name);
  if (a.dst_string != NULL) {
    printf("dst_string:%s,", a.dst_string);
  }

  if (a.dst_int != NULL) {
    printf("dst_int:%d,", *(a.dst_int));
  }
  printf("\n");
}
void print_args(const char* prefix, const Arguments* args) {
  assert(args != NULL);
  printf("%s\nargs->len:%d\n", prefix, args->len);
  for (int i = 0; i < args->len; i++) {
    printf("index:%d\n", i);
    print_value(NULL, args->arg[i]);
  }
}
void args_init() {
  LOG(s
      "sizeof(Arguments)=%ld,sizeof(Argument)=%ld,sizeof(int)=%ld,sizeof(int*)="
      "%ld\n",
      sizeof(Arguments), sizeof(Argument), sizeof(int), sizeof(int*));
  memset(&Args, 0, sizeof(Arguments));
}
void args_set_string(char* dst_string, const char* name, const char* value,
                     const char* use) {
  assert(dst_string != NULL);
  assert(name != NULL);
  // memcpy(args->arg + args->len, &a, 1);
  int index = Args.len;
  Args.arg[index].type = STRING;
  Args.arg[index].dst_string = dst_string;
  strcpy(Args.arg[index].name, name);
  if (value != NULL) {
    strcpy(Args.arg[index].dst_string, value);
  } else {
    strcpy(Args.arg[index].dst_string, "");
  }
  if (use != NULL) {
    strcpy(Args.arg[index].use, use);
  } else {
    strcpy(Args.arg[index].use, "");
  }
  Args.len++;
}

void args_set_int(int* dst_int, const char* name, int value, const char* use) {
  assert(dst_int != NULL);
  assert(name != NULL);
  int index = Args.len;
  Args.arg[index].type = INT;
  Args.arg[index].dst_int = dst_int;
  strcpy(Args.arg[index].name, name);
  *(Args.arg[index].dst_int) = value;
  if (use != NULL) {
    strcpy(Args.arg[index].use, use);
  } else {
    strcpy(Args.arg[index].use, "");
  }
  Args.len++;
}

void args_use() {
  printf("-%-32s,--%-32s (help infomation)\n", "h", "help");
  for (int i = 0; i < Args.len; i++) {
    printf("-%-32s,--%-32s (%s)\n", Args.arg[i].name, Args.arg[i].name,
           Args.arg[i].use);
  }
}

void parse_one_arg(int argc, char* argv[], Argument* arg) {
  LOG(s "\n*******the name of argument:%s*******\n", arg->name);
  for (int i = 1; i < argc; i++) {
    LOG(s "===main function parameter argc, argv[%d]:%s\n", i, argv[i]);
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
        LOG(s "no (=) catch the next argv[i+1] value:%s\n", value);
      } else {
        LOG(s "no (=) the value was not catched,and return\n");
        return;
      }
    } else {  // has '='
      memcpy(name_tmp, argv[i], index - argv[i]);
      strcpy(value, index + 1);
      LOG(s "has (=) catch the value after (=):%s\n", value);
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
      LOG(s "no (--) catch the name :%s\n", name);
    } else {
      strcpy(name, name_tmp + 2);
      LOG(s "has (--) catch the name :%s\n", name);
    }
    // name not equal
    if (strcmp(name, arg->name)) {
      // i += 1;
      // if (i >= argc) {
      //   // todo:打印日志
      //   printf("===========>>>>>>>i:%d\n", i);
      //   print_log("22", arg->name);
      //   return 0;
      // }
      LOG(s "input-name is not equal argument-name\n");
      continue;
    }
    // name equal
    // LOG("========name equal.....\n");
    if (arg->type == STRING) {
      strcpy(arg->dst_string, value);
      LOG(s "input-name is equal argument-name,type(string)\n");
    } else {  // type int
      *arg->dst_int = atoi(value);
      LOG(s "input-name is equal argument-name,type(int)\n");
    }
    break;
  }
}

void args_parse(int argc, char* argv[]) {
  assert(Args.len > 0);
  int eq1 = strcmp(argv[argc - 1], "-h");
  int eq2 = strcmp(argv[argc - 1], "--help");
  if (argc == 1 || eq1 == 0 || eq2 == 0) {
    args_use();
    exit(0);
  }
  // int flag = 0;
  for (int i = 0; i < Args.len; i++) {
    parse_one_arg(argc, argv, &Args.arg[i]);
  }
}
/*******************log api**********************/
// static int N = 3;
int fprint(FILE* stream, char* format, ...) {
  va_list args;
  va_start(args, format);
  int fg = vfprintf(stream, format, args);
  va_end(args);
  // N = N + 7;
  // printf("N=%d\n", N);
  return fg;
}
int fprint_null(FILE* stream, char* format, ...) { return 0; }

int print(char* format, ...) {
  va_list args;
  va_start(args, format);
  int fg = vprintf(format, args);
  va_end(args);
  return fg;
}

int print_null(char* format, ...) {}

int fprint_uchar_array(FILE* stream, const char* array, int size,
                       const char* prefix) {
  if (stream == NULL || array == NULL || size < 1) {
    // return NULL
    return -1;
  }
  // string fmt = "%s: {";

  if (strlen(prefix) == 0) {
    // fmt = "%s{";
    fprint(stream, (char*)"%s{", prefix);
  } else {
    fprint(stream, (char*)"%s: {", prefix);
  }

  for (int i = 0; i < size; i++) {
    /* code */
    if ((unsigned char)array[i] < 0x10) {
      if (i == size - 1) {
        fprint(stream, (char*)"0x0%x", (unsigned char)array[i]);
        break;
      }
      fprint(stream, (char*)"0x0%x, ", (unsigned char)array[i]);
    } else {
      if (i == size - 1) {
        fprint(stream, (char*)"0x%x", (unsigned char)array[i]);
        break;
      }
      fprint(stream, (char*)"0x%x, ", (unsigned char)array[i]);
    }
    // if (i == size - 1) {
    //     fprint(stream, (char*)"0x%x", (unsigned char)array[i]);
    //     break;
    // }
    // fprint(stream, (char*)"0x%x, ", (unsigned char)array[i]);
  }
  fprint(stream, (char*)"}, length=%d\n", size);
  return 0;

  //     fprint() va_list args;
  // va_start(args, format);
  // vfprintf(stream, format, args);
  // va_end(args);
}
int print_uchar_array(const char* array, int size, const char* prefix) {
  if (array == NULL || size < 1) {
    // return NULL
    return -1;
  }
  // string fmt = "%s: {";

  if (strlen(prefix) == 0) {
    // fmt = "%s{";
    print((char*)"%s{", prefix);
  } else {
    print((char*)"%s: {", prefix);
  }

  for (int i = 0; i < size; i++) {
    /* code */
    if ((unsigned char)array[i] < 0x10) {
      if (i == size - 1) {
        print((char*)"0x0%x", (unsigned char)array[i]);
        break;
      }
      print((char*)"0x0%x, ", (unsigned char)array[i]);
    } else {
      if (i == size - 1) {
        print((char*)"0x%x", (unsigned char)array[i]);
        break;
      }
      print((char*)"0x%x, ", (unsigned char)array[i]);
    }
  }
  print((char*)"}, lengrh=%d\n", size);

  return 0;
}
int fprint_null_uchar_array(FILE* stream, const char* array, int size,
                            const char* prefix) {
  return 0;
}
int print_null_uchar_array(const char* array, int size, const char* prefix) {
  return 0;
}
#if 0
int main(int argc, char* argv[]) {
  Arguments aa;
  char fname[32] = {0}, time[32] = {0};
  int num = 0, nt = 0;
  args_init();
  args_set_string(fname, "fn", "1111", "file name");
  args_set_string(time, "tm", "11119999", "tmie name");
  args_set_int(&num, "num", 77777, "number");
  args_set_int(&nt, "nt", 1, "thread number");
  print_args(NULL, &Args);
  args_parse(argc, argv);
  printf("fname:%s,time:%s,num:%d,nt:%d\n", fname, time, num, nt);
}
#endif
#if 0
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