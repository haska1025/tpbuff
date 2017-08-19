#include <stdio.h>
#include <string.h>
#include "tp_symbol_list.h"

int main()
{
    const char *file_name = "test.tpp";
    if ( 0 != tpp_protocol_parse(file_name)){
        fprintf(stderr, "Parse file failed(%s)\n", file_name);
        return -1;
    }

    tpp_display_protocol_table();
    tpp_protocol_tab_destroy();

    if (0 != tp_gen_cxx_code("./", file_name)){
        fprintf(stderr, "Generate code failed(%s)\n", file_name);
        return -1;
    }

    tpp_display_protocol_table();

    return 0;
}

