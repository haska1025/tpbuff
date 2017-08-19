#ifndef _TPB_TPBUFF_H_
#define _TPB_TPBUFF_H_

#include <inttypes.h>
#include <string.h>

#ifndef TPBUFF_DLL_DECL
#   if defined(WIN32)
#       ifndef TPBUFF_EXPORTS
#           define TPBUFF_DLL_DECL __declspec(dllimport)
#       else
#           define TPBUFF_DLL_DECL __declspec(dllexport)
#       endif//TPBUFF_EXPORTS
#   else
#       define TPBUFF_DLL_DECL
#   endif//_WIN32
#endif//TPBUFF_DLL_DECL
/**
 * flags has 32 bits. format:
 * 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *|(0~2)|N|                                                       |
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 * bit0~bit2(0~2): tp data send flags
 * bit3: Whether need to new tm header
 */
enum tp_data_io_flags
{
    TP_DIOF_TCP=1,        //1
    TP_DIOF_UDP,          //2
    TP_DIOF_HTTP,         //3
    TP_DIOF_HTTPS,        //4
    TP_DIOF_REAL_TIME,    //5
    TP_DIOF_FLOW_CONTROL, //6
};
/**
 * ++++++++++++++++++++++++++
 * |  next                  |
 * ++++++++++++++++++++++++++
 * |  channel_hdr           |----------------------------------+
 * ++++++++++++++++++++++++++                                  |
 * |  tm_hdr                |-----------+                      |
 * ++++++++++++++++++++++++++           |                      |
 * |  size                  |           |                      |
 * ++++++++++++++++++++++++++           |                      |
 * |  data                  |           |                      |
 * ++++++++++++++++++++++++++           |                      |
 * |  destructor            |           |                      |
 * ++++++++++++++++++++++++++ <--head   |                      | 
 * ++++++++++++++++++++++++++           |                      |
 * |  padding               |           |                      | 
 * ++++++++++++++++++++++++++ <---------+ (head + tm_hdr)/data | 
 * |  tm header             |                                  |
 * ++++++++++++++++++++++++++ <--------------------------------+ (head + channel_hdr)/data
 * |  channel header        |
 * ++++++++++++++++++++++++++
 * |  payload               |
 * ++++++++++++++++++++++++++
 */
struct tp_buff;
struct tp_buff_head
{
    struct tp_buff *next;
    struct tp_buff *prev;
    uint32_t nums;
};
struct tp_buff
{
    struct tp_buff *next;  /**<The pointer to the next tp buff.It must be first */
    struct tp_buff *prev;  /**<The pointer to the prev tp buff.It must be first */
    uint32_t io_flags:3;   /**<The send flags */
    uint32_t new_tm_hdr:1; /**<Whether need to new tm header */
    uint32_t prot_type:4;  /**<The control flags */
    uint8_t sub_prot_type; /**<The control flags */
    uint8_t reserved2;     /**<The reserved flags */
    uint8_t reserved3;     /**<The reserved flags */
    uint16_t channel_hdr;  /**<The channel header offset*/
    uint16_t tm_hdr;       /**<The tm header offset*/
    uint32_t size;         /**<The total size of the head pointer to the memory */
    uint32_t truesize;     /**<The real size of the data */
    uint8_t *data;         /**<The pointer to the data */
    uint8_t *unsent_data;  /**<The pointer to unsent data */
    struct tp_buff *extern_data;  /**<The pointer to the external data which has its own memory */
    uint8_t head[1];       /**<It must be last */
};
/************** macros ***********************************/
#define INIT_TPB_HEAD(tpb) \
{\
    (tpb)->next = (struct tp_buff *)(tpb);\
    (tpb)->prev = (struct tp_buff *)(tpb);\
    (tpb)->nums = 0;\
}
/************** extern functions *************************/
#ifdef MEMLEAK_DEBUG
TPBUFF_DLL_DECL extern struct tp_buff * alloc_tpb_inner(uint32_t len);
TPBUFF_DLL_DECL extern void free_tpb_inner(struct tp_buff *tpb);
TPBUFF_DLL_DECL extern void tpb_inc_ref_inner(struct tp_buff *tpb);
#define alloc_tpb(len) ({\
    struct tp_buff *buff = alloc_tpb_inner(len);\
    TRANS_LOG_INFO("tmbuff malloc %s %s:%d (%p) ", __FUNCTION__, __FILE__, __LINE__, buff);\
    buff;\
})
#define free_tpb(tpb) ({\
    TRANS_LOG_INFO("tmbuff tm_free %s %s:%d (%p) ", __FUNCTION__, __FILE__, __LINE__, tpb);\
    free_tpb_inner(tpb);\
})
#define tpb_inc_ref(tpb) ({\
    TRANS_LOG_INFO("tmbuff tm_ref %s %s:%d (%p) ", __FUNCTION__, __FILE__, __LINE__, tpb);\
    tpb_inc_ref_inner(tpb);\
})
#else
TPBUFF_DLL_DECL extern struct tp_buff * alloc_tpb(uint32_t len);
TPBUFF_DLL_DECL extern void free_tpb(struct tp_buff *tpb);
TPBUFF_DLL_DECL extern void tpb_inc_ref(struct tp_buff *tpb);
#endif
TPBUFF_DLL_DECL extern void tpb_dump(struct tp_buff *tpb, const char *prefix);
/************* inline functions **************************/
static inline int tpb_list_empty(struct tp_buff *tpb)
{
    return (tpb == tpb->next);
}
static inline void tpb_list_insert(struct tp_buff *prev, struct tp_buff *next, struct tp_buff *tpb_new)
{
    tpb_new->prev->next = next;
    next->prev = tpb_new->prev;

    tpb_new->prev = prev;
    prev->next = tpb_new;
}
static inline void tpb_list_push_back(struct tp_buff *tpb_head, struct tp_buff *tpb_new)
{
    tpb_list_insert(tpb_head->prev, tpb_head, tpb_new);
}
static inline tp_buff *tpb_list_pop_front(struct tp_buff *tpb_head)
{
    if (tpb_list_empty(tpb_head))return NULL;
    struct tp_buff *tpb = tpb_head->next;
    tpb_head->next = tpb->next;
    tpb->next->prev = tpb_head;

    // pointer to myself
    tpb->next = tpb;
    tpb->prev = tpb;

    return tpb;
}
static inline uint8_t * tpb_push(struct tp_buff *tpb, uint32_t len)
{
    tpb->data -= len;
    tpb->truesize += len;
    return tpb->data;
}
static inline uint8_t * tpb_pull(struct tp_buff *tpb, uint32_t len)
{
    tpb->data += len;
    tpb->truesize -= len;
    return tpb->data;
}
static inline uint8_t * tpb_set_unsent(struct tp_buff *tpb, uint32_t sentbytes)
{
    tpb->unsent_data = tpb->data + sentbytes;
    return tpb->unsent_data;
}
static inline uint8_t * tpb_pull_unsent(struct tp_buff *tpb, uint32_t sentbytes)
{
    tpb->unsent_data += sentbytes;
    return tpb->unsent_data;
}
static inline uint32_t tpb_get_size(struct tp_buff *tpb)
{
    return tpb->size;
}
static inline uint8_t * tpb_get_unsent_data_pointer(struct tp_buff *tpb)
{
    return tpb->unsent_data;
}
static inline uint32_t tpb_get_unsent_data_size(struct tp_buff *tpb)
{
    return (tpb->truesize - (tpb->unsent_data - tpb->data));
}
static inline uint8_t * tpb_get_data_pointer(struct tp_buff *tpb)
{
    return tpb->data;
}
// Set the true size of the data
static inline void tpb_set_data_size(struct tp_buff *tpb, uint32_t len)
{
    tpb->truesize = len;
}
// Get the true size of the data
static inline uint32_t tpb_get_data_size(struct tp_buff *tpb)
{
    return tpb->truesize;
}
// Get the size of the tm data
static inline uint32_t tpb_get_tm_data_size(struct tp_buff *tpb)
{
    return (tpb->data - tpb->head)+tpb->truesize-tpb->tm_hdr;
}
// Get the size of the channelmgr data
static inline uint32_t tpb_get_channel_data_size(struct tp_buff *tpb)
{
    return (tpb->data - tpb->head)+tpb->truesize-tpb->channel_hdr;
}
static inline void tpb_reset_channel_hdr(struct tp_buff *tpb)
{
    tpb->channel_hdr = (uint16_t)(tpb->data - tpb->head);
}
static inline void tpb_reset_tm_hdr(struct tp_buff *tpb)
{
    tpb->tm_hdr = (uint16_t)(tpb->data - tpb->head);
}
static inline uint8_t * tpb_channel_hdr(struct tp_buff *tpb)
{
    return (tpb->head + tpb->channel_hdr);
}
static inline uint8_t * tpb_tm_hdr(struct tp_buff *tpb)
{
    return (tpb->head + tpb->tm_hdr);
}
static inline uint32_t tpb_get_new_tm_hdr_flag(struct tp_buff *tpb)
{
    return tpb->new_tm_hdr;
}
static inline void tpb_set_new_tm_hdr_flag(struct tp_buff *tpb, uint32_t flag)
{
    tpb->new_tm_hdr = (0x1 & flag);
}
static inline uint8_t tpb_get_sub_prot_type(struct tp_buff *tpb)
{
    return tpb->sub_prot_type;
}
static inline void tpb_set_sub_prot_type(struct tp_buff *tpb, uint8_t spt)
{
    tpb->sub_prot_type = spt;
}
static inline uint32_t tpb_get_prot_type(struct tp_buff *tpb)
{
    return tpb->prot_type;
}
static inline void tpb_set_prot_type(struct tp_buff *tpb, uint32_t pt)
{
    tpb->prot_type = 0xF&pt;
}
static inline void tpb_reset(struct tp_buff *tpb)
{
    tpb->next = tpb;
    tpb->prev = tpb;
    tpb->io_flags = 0;
    tpb->new_tm_hdr = 0;
    tpb->channel_hdr = 0;
    tpb->tm_hdr = 0;   
    tpb->truesize = 0;
    tpb->extern_data = NULL;
    tpb->unsent_data = NULL;
    tpb->data = tpb->head + tpb->size;
}
#endif//_TPB_TPBUFF_H_

