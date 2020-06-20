#ifndef _H_CARGS
#define _H_CARGS

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>
/********argument*******/
void args_init();
void args_set_string(char* dst_string, const char* name, const char* value,
                     const char* use);
void args_set_int(int* dst_int, const char* name, int value, const char* use);
void args_use();
void args_parse(int argc, char* argv[]);

/********log api******/
int fprint_null(FILE* stream, char* format, ...);
int fprint(FILE* stream, char* format, ...);
int print_null(char* format, ...);
int print(char* format, ...);
int fprint_uchar_array(FILE* stream, const char* array, int size,
                       const char* prefix);
int print_uchar_array(const char* array, int size, const char* prefix);
int fprint_null_uchar_array(FILE* stream, const char* array, int size,
                            const char* prefix);
int print_null_uchar_array(const char* array, int size, const char* prefix);

/********control log printf*****/
#ifdef DEBUG
#define LOG print  // use or use printf
#define FLOG fprint
#define LOGUCHAR print_uchar_array
#define FLOGUCHAR fprint_uchar_array
#else
#define LOG print_null  // use
#define FLOG fprint_null
#define LOGUCHAR print_null_uchar_array
#define FLOGUCHAR fprint_null_uchar_array
#endif

#ifdef __cplusplus
}
#endif
#endif