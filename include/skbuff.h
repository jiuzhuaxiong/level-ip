#ifndef SKBUFF_H_
#define SKBUFF_H_

#include "netdev.h"
#include "dst.h"
#include "list.h"
#include <pthread.h>

struct sk_buff {
    struct list_head list;
    struct dst_entry *dst;
    struct netdev *netdev;
    uint16_t protocol;
    uint32_t len;
    uint8_t *tail;
    uint8_t *end;
    uint8_t *head;
    uint8_t *data;
};

struct sk_buff_head {
    struct list_head head;

    uint32_t qlen;
    pthread_mutex_t lock;
};

struct sk_buff *alloc_skb(unsigned int size);
void free_skb(struct sk_buff *skb);
uint8_t *skb_push(struct sk_buff *skb, unsigned int len);
uint8_t *skb_head(struct sk_buff *skb);
void *skb_reserve(struct sk_buff *skb, unsigned int len);
void skb_dst_set(struct sk_buff *skb, struct dst_entry *dst);

static inline void skb_queue_init(struct sk_buff_head *list)
{
    list_init(&list->head);
    list->qlen = 0;
    pthread_mutex_init(&list->lock, NULL);
}

#endif
