#ifndef _H_PJSON
#define _H_PJSON
#ifdef __cplusplus
extern "C" {
#endif
#define TYPE_NUM 256
#define STU Student
#define PERSON Person
#define DATA(x) x

typedef struct Stu {
    char name[32];
    int age;
    /* data */
};

typedef struct Stu {
    char name[32];
    int age;
    /* data */
};

typedef struct P_Json {
    void* data;
    char* json_string;
};
int encode_json();  // struct to json
int decode_json();  // json to struct
#ifdef __cplusplus
}
#endif
#endif