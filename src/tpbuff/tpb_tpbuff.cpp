#include "tpb_tpbuff.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_RESERVE_HDR_LEN 20

#ifdef MEMLEAK_DEBUG
struct tp_buff * alloc_tpb_inner(uint32_t len)
#else
struct tp_buff * alloc_tpb(uint32_t len)
#endif
{
    uint32_t size=len;
    size += MAX_RESERVE_HDR_LEN; 
    size += sizeof(struct tp_buff);
    struct tp_buff *tpb = (struct tp_buff*)malloc(size);
    if (!tpb){
        printf("No memory can be allocated\n");
        return NULL;
    }

    tpb->next = tpb;
    tpb->prev = tpb;
    tpb->io_flags = 0;
    tpb->new_tm_hdr = 0;
    tpb->prot_type = 0;
    tpb->reserved2 = 0;
    tpb->reserved3 = 0;
    tpb->sub_prot_type = 0;
    tpb->channel_hdr = 0;
    tpb->tm_hdr = 0;
    tpb->size = size - sizeof(struct tp_buff);
    tpb->truesize = 0;
    tpb->data = tpb->head + tpb->size;
    tpb->extern_data = NULL;
    tpb->unsent_data = NULL;
    return tpb;
}

#ifdef MEMLEAK_DEBUG
void free_tpb_inner(struct tp_buff *tpb)
#else
void free_tpb(struct tp_buff *tpb)
#endif
{
    free((void*)tpb);
}

#ifdef MEMLEAK_DEBUG
void tpb_inc_ref_inner(struct tp_buff *tpb)
#else
void tpb_inc_ref(struct tp_buff *tpb)
#endif
{
}

void tpb_dump(struct tp_buff *tpb, const char *prefix)
{
    printf("(%s) tpb info next(%p) prev(%p) ioflags(%d) new_tmhdr_flags(%d) prottype(%u) subprottype(%u) chanelhdr(%u) tmhdr(%u) size(%u) truesize(%u) data(%p) unsentdata(%p) externdata(%p)\n",
            prefix,
            tpb->next,
            tpb->prev,
            tpb->io_flags,
            tpb->new_tm_hdr,
            tpb->prot_type,
            tpb->sub_prot_type,
            tpb->channel_hdr,
            tpb->tm_hdr,
            tpb->size,
            tpb->truesize,
            tpb->data,
            tpb->unsent_data,
            tpb->extern_data);
}

