#ifndef _TP_H_
#define _TP_H_

#ifdef __cplusplus
extern "C" {
#endif

    struct tang_cmd;
    struct protocal;

    //provide the interface for the external call
    extern struct tang_cmd * get_tang_cmd(const char *cmdstr , int len);
    extern int free_tang_cmd(struct tang_cmd *cmd);

    extern char * tang_cmd_get_value(struct tang_cmd *tc , const char *key);
    extern char * tang_cmd_get_name(struct tang_cmd *tc);

    extern int tang_load_cmd_tab(const char *file_name);
    extern struct protocal * tang_get_protocal(struct tang_cmd *tc);
    extern int tang_protocal_get_int16_value(struct protocal *p , const char *key , int *val);
    extern int tang_protocal_get_int32_value(struct protocal *p , const char *key , int *val);
    extern int tang_protocal_get_str_value(struct protocal *p , const char *key , char **val);

#ifdef __cplusplus
}
#endif

#endif//_TP_H_

