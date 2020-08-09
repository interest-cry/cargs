#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cJSON.h"
#define RAW_LEN 1024 * 10
enum { BOTTOM_INFO, UNIQUE_INFO, ACCESS_INFO };
typedef struct BottomInfo {
    char engine_type[30];
    char device_info[512];
    char project_id[30];
    char engine_version[30];
    char region[30];
    char company[30];
    int expiration;
} BottomInfo;
typedef struct UniqueInfo {
    /* data */
    char cpu_serial[256];
    char mac_info[256];
    char imei_info[256];
} UniqueInfo;

typedef struct AccessInfo {
    /* data */
    char raw_access[RAW_LEN];
    int start_time;
    int end_time;
    int expiration;
    int active_time;
    int max_thread_num;
} AccessInfo;

/****************json_to_struct*******************/
int json_to_struct(void *s, const char *json_text, int type) {
    if ((s == NULL) || (type < 0 || type > 2)) {
        /* code */
        return -1;
    }
    cJSON *jper = NULL;
    // BottomInfo
    BottomInfo *bi = NULL;
    cJSON *jengine_type = NULL, *jdevice_info = NULL, *jproject_id = NULL,
          *jengine_version = NULL, *jregion = NULL, *jcompany = NULL;
    // UniqueInfo
    UniqueInfo *uqi = NULL;
    cJSON *jcpu_serial = NULL, *jmac_info = NULL, *jimei_info = NULL;
    // AccessInfo
    AccessInfo *aci = NULL;
    cJSON *jraw_access = NULL, *jstart_time = NULL, *jend_time = NULL,
          *jexpiration = NULL, *jactive_time = NULL, *jmax_thread_num = NULL;
    switch (type) {
        case BOTTOM_INFO:
            /* code */
            bi = (BottomInfo *)s;
            jper = cJSON_Parse(json_text);
            if (jper == NULL) {
                return -1;
            }
            // engine_type
            jengine_type = cJSON_GetObjectItem(jper, "engine_type");
            memset(bi->engine_type, 0, sizeof(bi->engine_type));
            if (jengine_type != NULL) {
                strcpy(bi->engine_type, jengine_type->valuestring);
            }
            // device_info
            jdevice_info = cJSON_GetObjectItem(jper, "device_info");
            memset(bi->device_info, 0, sizeof(bi->device_info));
            if (jdevice_info != NULL) {
                strcpy(bi->device_info, jdevice_info->valuestring);
            }
            // project_id
            jproject_id = cJSON_GetObjectItem(jper, "project_id");
            memset(bi->project_id, 0, sizeof(bi->project_id));
            if (jproject_id != NULL) {
                // per->age = jage->valueint;
                strcpy(bi->project_id, jproject_id->valuestring);
            }
            // engine_version
            jengine_version = cJSON_GetObjectItem(jper, "engine_version");
            memset(bi->engine_version, 0, sizeof(bi->engine_version));
            if (jengine_version != NULL) {
                strcpy(bi->engine_version, jengine_version->valuestring);
            }
            // region
            jregion = cJSON_GetObjectItem(jper, "region");
            memset(bi->region, 0, sizeof(bi->region));
            if (jregion != NULL) {
                /* code */
                strcpy(bi->region, jregion->valuestring);
            }
            // company
            jcompany = cJSON_GetObjectItem(jper, "company");
            memset(bi->company, 0, sizeof(bi->company));
            if (jcompany != NULL) {
                /* code */
                strcpy(bi->company, jcompany->valuestring);
            }
            break;

        case UNIQUE_INFO:
            uqi = (UniqueInfo *)s;
            jper = cJSON_Parse(json_text);
            if (jper == NULL) {
                return -1;
            }
            // cpu_serial
            jcpu_serial = cJSON_GetObjectItem(jper, "cpu_serial");
            memset(uqi->cpu_serial, 0, sizeof(uqi->cpu_serial));
            if (jcpu_serial != NULL) {
                strcpy(uqi->cpu_serial, jcpu_serial->valuestring);
            }
            // mac_info
            jmac_info = cJSON_GetObjectItem(jper, "mac_info");
            memset(uqi->mac_info, 0, sizeof(uqi->mac_info));
            if (jmac_info != NULL) {
                strcpy(uqi->mac_info, jmac_info->valuestring);
            }
            // imei_info
            jimei_info = cJSON_GetObjectItem(jper, "imei_info");
            memset(uqi->imei_info, 0, sizeof(uqi->imei_info));
            if (jimei_info != NULL) {
                // per->age = jage->valueint;
                strcpy(uqi->imei_info, jimei_info->valuestring);
            }
            break;
        case ACCESS_INFO:
            aci = (AccessInfo *)s;
            jper = cJSON_Parse(json_text);
            if (jper == NULL) {
                return -1;
            }
            // raw_access
            jraw_access = cJSON_GetObjectItem(jper, "raw_access");
            memset(aci->raw_access, 0, sizeof(aci->raw_access));
            if (jraw_access != NULL) {
                strcpy(aci->raw_access, jraw_access->valuestring);
            }
            // start_time
            jstart_time = cJSON_GetObjectItem(jper, "start_time");
            aci->start_time = 0;
            if (jstart_time != NULL) {
                aci->start_time = jstart_time->valueint;
            }
            // end_time
            jend_time = cJSON_GetObjectItem(jper, "end_time");
            aci->end_time = 0;
            if (jend_time != NULL) {
                aci->end_time = jend_time->valueint;
            }
            // expiration
            jexpiration = cJSON_GetObjectItem(jper, "expiration");
            aci->expiration = 0;
            if (jexpiration != NULL) {
                aci->expiration = jexpiration->valueint;
            }
            // active_time
            jactive_time = cJSON_GetObjectItem(jper, "active_time");
            aci->active_time = 0;
            if (jactive_time != NULL) {
                /* code */
                aci->active_time = jactive_time->valueint;
            }
            // max_thread_num
            jmax_thread_num = cJSON_GetObjectItem(jper, "max_thread_num");
            aci->max_thread_num = 0;
            if (jmax_thread_num != NULL) {
                /* code */
                aci->max_thread_num = jmax_thread_num->valueint;
            }
            break;
        default:
            return -1;
    }
    cJSON_Delete(jper);
    return 0;
}
/****************struct_to_json*******************/
int struct_to_json(char *json_string, void *s, int type) {
    cJSON *jper = cJSON_CreateObject();
    if (jper == NULL || json_string == NULL) {
        return -1;
    }
    // BottomInfo
    BottomInfo *bi = NULL;
    cJSON *jengine_type = NULL, *jdevice_info = NULL, *jproject_id = NULL,
          *jengine_version = NULL, *jregion = NULL, *jcompany = NULL;
    // UniqueInfo
    UniqueInfo *uqi = NULL;
    cJSON *jcpu_serial = NULL, *jmac_info = NULL, *jimei_info = NULL;
    // AccessInfo
    AccessInfo *aci = NULL;
    cJSON *jraw_access = NULL, *jstart_time = NULL, *jend_time = NULL,
          *jexpiration = NULL, *jactive_time = NULL, *jmax_thread_num = NULL;
    switch (type) {
        case BOTTOM_INFO:
            /* code */
            // engine_type
            bi = (BottomInfo *)s;
            jengine_type = cJSON_CreateString(bi->engine_type);
            if (jengine_type == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "engine_type", jengine_type);
            // device_info
            jdevice_info = cJSON_CreateString(bi->device_info);
            if (jdevice_info == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "device_info", jdevice_info);
            // project_id
            jproject_id = cJSON_CreateString(bi->project_id);
            if (jproject_id == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "project_id", jproject_id);
            // engine_version
            jengine_version = cJSON_CreateString(bi->engine_version);
            if (jengine_version == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "engine_version", jengine_version);
            // region
            jregion = cJSON_CreateString(bi->region);
            if (jregion == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "region", jregion);
            // company
            jcompany = cJSON_CreateString(bi->company);
            if (jcompany == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "company", jcompany);
            break;
        case UNIQUE_INFO:
            // cpu_serial
            uqi = (UniqueInfo *)s;
            jcpu_serial = cJSON_CreateString(uqi->cpu_serial);
            if (jcpu_serial == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "cpu_serial", jcpu_serial);
            // mac_info
            jmac_info = cJSON_CreateString(uqi->mac_info);
            if (jmac_info == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "mac_info", jmac_info);
            // imei_info
            jimei_info = cJSON_CreateString(uqi->imei_info);
            if (jimei_info == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "imei_info", jimei_info);
            break;
        case ACCESS_INFO:
            /* code */
            // raw_access
            aci = (AccessInfo *)s;
            jraw_access = cJSON_CreateString(aci->raw_access);
            if (jraw_access == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "raw_access", jraw_access);
            // start_time
            jstart_time = cJSON_CreateNumber(aci->start_time);
            if (jstart_time == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "start_time", jstart_time);
            // end_time
            jend_time = cJSON_CreateNumber(aci->end_time);
            if (jend_time == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "end_time", jend_time);
            // expiration
            jexpiration = cJSON_CreateNumber(aci->expiration);
            if (jexpiration == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "expiration", jexpiration);
            // active_time
            jactive_time = cJSON_CreateNumber(aci->active_time);
            if (jactive_time == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "active_time", jactive_time);
            // max_thread_num
            jmax_thread_num = cJSON_CreateNumber(aci->max_thread_num);
            if (jmax_thread_num == NULL) {
                cJSON_Delete(jper);
                return -1;
            }
            cJSON_AddItemToObject(jper, "max_thread_num", jmax_thread_num);
            break;
        default:
            break;
    }
    char *json_str = cJSON_PrintUnformatted(jper);
    strcpy(json_string, json_str);
    cJSON_Delete(jper);
    free(json_str);
    return 0;
}
/****************encode test*******************/
#if 1
/********json*********/
void output(void *s, int type) {
    BottomInfo *p = NULL;
    UniqueInfo *p1 = NULL;
    AccessInfo *p2 = NULL;
    switch (type) {
        case BOTTOM_INFO:
            /* code */
            printf("struct BottomInfo>>:\n");
            p = (BottomInfo *)s;
            printf(
                "engine_type:%s, device_info:%s, project_id:%s, "
                "engine_version:%s,region:%s,company:%s\n",
                p->engine_type, p->device_info, p->project_id,
                p->engine_version, p->region, p->company);
            break;
        case UNIQUE_INFO:
            printf("struct UniqueInfo>>:\n");
            p1 = (UniqueInfo *)s;
            printf("cpu_serial:%s,mac_info:%s,imei_info:%s\n", p1->cpu_serial,
                   p1->mac_info, p1->imei_info);
            break;
        case ACCESS_INFO:
            printf("struct AccessInfo>>:\n");
            p2 = (AccessInfo *)s;
            printf(
                "raw_access:%s,start_time:%d,end_time:%d,expiration:%d,active_"
                "time:%"
                "d,max_thread_num:%d\n",
                p2->raw_access, p2->start_time, p2->end_time, p2->expiration,
                p2->active_time, p2->max_thread_num);
            break;
        default:
            printf("type is error\n");
            break;
    }
}

int main() {
    int tnow = (int)(time(NULL));
    printf("===sizeof:%ld, tnow:%d\n", sizeof(int), tnow);
    BottomInfo bi = {"face", "", "3377", "v2", "shanghai", "yzs"}, bi_2;
    printf("----------cJSON %s----------\n", cJSON_Version());
    output(&bi, BOTTOM_INFO);
    char json_txt[1000] = {0};
    memset(json_txt, 0, sizeof(json_txt));
    int fg = struct_to_json(json_txt, &bi, BOTTOM_INFO);
    if (fg != 0) {
        /* code */
        printf("json to struct error\n");
        return 1;
    }
    printf("fg=%d\n", fg);
    printf("bottom info to json:%s,%ld\n", json_txt, strlen(json_txt));
    // char json_text[] = "{\"name\":\" qxf\",\"gender\":\"female\"}";
    // char json_text[] = "{\"gender\":\"female\"}";
    fg = json_to_struct(&bi_2, json_txt, BOTTOM_INFO);
    printf("fg=%d,len=%d\n", fg, (int)strlen(json_txt));
    output(&bi_2, BOTTOM_INFO);
    ////////////////
    UniqueInfo uqi = {"777", "333", ""}, uqi_2;
    memset(json_txt, 0, sizeof(json_txt));
    fg = struct_to_json(json_txt, &uqi, UNIQUE_INFO);
    if (fg != 0) {
        /* code */
        printf("json to struct error\n");
        return 1;
    }
    printf("unique info to json:%s,%ld\n", json_txt, strlen(json_txt));
    fg = json_to_struct(&uqi_2, json_txt, UNIQUE_INFO);
    printf("fg=%d,len=%d\n", fg, (int)strlen(json_txt));
    output(&uqi_2, UNIQUE_INFO);
    //////////////////
    AccessInfo aci = {"7777777",  1582010522, 1582010523,
                      1582010524, 1582010525, 1582010526},
               aci_2;
    memset(json_txt, 0, sizeof(json_txt));
    fg = struct_to_json(json_txt, &aci, ACCESS_INFO);
    if (fg != 0) {
        /* code */
        printf("access info to struct error\n");
        return 1;
    }
    printf("access info to json:%s,%ld\n", json_txt, strlen(json_txt));
    fg = json_to_struct(&aci_2, json_txt, ACCESS_INFO);
    printf("fg=%d,len=%d\n", fg, (int)strlen(json_txt));
    output(&aci_2, ACCESS_INFO);

    return 0;
}
#endif
