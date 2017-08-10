#include "tp.h"
#include <stdio.h>
#include <string.h>

int main()
{
    struct tang_cmd *cmd;
    struct key_val *kv;

    load_cmd_tab("../../cmd/cmd_tab.txt");

    cmd = NULL;
    const char *s = "join_conf:a='1',b='2',c='ddfdf';";
    const char *s1 ="add:a='1',b='2';\021";
    cmd = get_tang_cmd(s1 , 16 );
    if (!cmd){
        printf("get tang cmd failed!\n");
        return -1;
    }

    /*
    printf("cmd name = %s\n",cmd->name);

    for (kv = cmd->kv_head; kv != NULL; kv = kv->next){
         printf("key=%s,val=%s\n",kv->key , kv->val);
    }

    */
    free_tang_cmd(cmd);

    return 0;
}

