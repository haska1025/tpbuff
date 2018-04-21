#include <stdio.h>
#include <string.h>
#include "tp_symbol_list.h"

int g_gen_struct = 0;
int g_reg_cmd = 0;
int g_gen_redis = 0;

void printrefs();
void test_tpp(const char *file_name)
{
    struct generated_file *gfile, *cur_gfile;

    printf("Ready parse file(%s)\n", file_name);
    if ( 0 != tpp_protocol_parse(file_name)){
        fprintf(stderr, "Parse file failed(%s)\n", file_name);
        return;
    }

    printrefs();
    printf("Ready print file(%s)\n", file_name);
    gfile = tpp_gfile_get_list();
    for (cur_gfile = gfile; cur_gfile != NULL; cur_gfile=cur_gfile->next){
        fprintf(stdout, "package name:%s\n", tpp_get_package_name(cur_gfile));
        tpp_display_protocol_table(cur_gfile);
    }
    tpp_gfile_destroy_list();

    printf("Ready generate file(%s)\n", file_name);
    if (0 != tp_gen_cxx_code(".", file_name)){
        fprintf(stderr, "Generate code failed(%s)\n", file_name);
        return;
    }

    printf("Ready generate java file(%s)\n", file_name);
    if (0 != tp_gen_java_code(".", file_name)){
        fprintf(stderr, "Generate java code failed(%s)\n", file_name);
        return;
    }
}
int main()
{
    //test_tpp("common.tpp");
    //test_tpp("test.tpp");
    //test_tpp("test_multi.tpp");
    g_gen_redis = 1;
    test_tpp("okvm.tpp");
    g_gen_redis = 0;
    return 0;
}

