/* $begin sbufc */
#include "usg_common.h"
#include "sbuf.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
/* $begin sbuf_init */
void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf = (int *) calloc(n, sizeof(int)); 
    sp->n = n;                       /* Buffer holds max of n items */
    sp->size = 0;
    sp->front = sp->rear = 0;        /* Empty buffer iff front == rear */

}
/* $end sbuf_init */

/* Clean up buffer sp */
/* $begin sbuf_deinit */
void sbuf_deinit(sbuf_t *sp)
{
    free(sp->buf);
}
/* $end sbuf_deinit */

/* Insert item onto the rear of shared buffer sp */
/* $begin sbuf_insert */
void sbuf_insert(sbuf_t *sp, int item)
{
    sp->buf[(sp->rear++)%(sp->n)] = item;
    sp->size++;
    //sp->buf[(sp->rear)++] = item;   /* Insert the item */
    
}
/* $end sbuf_insert */

/* Remove and return the first item from buffer sp */
/* $begin sbuf_remove */
int sbuf_remove(sbuf_t *sp)
{
    int item;
    item = sp->buf[(sp->front++)%(sp->n)];
    sp->size--;
    // item = sp->buf[(sp->front)++];  /* Remove the item */
    
    return item;
}

int sbuf_getsize(sbuf_t *sp) {
    // printf("get size\n" );
    return  sp->size;
}
/* $end sbuf_remove */
/* $end sbufc */

int main() {
    sbuf_t sbuf;
    int SBUFSIZE = 8;
    sbuf_init(&sbuf, SBUFSIZE);
    sbuf_insert(&sbuf, 1);
    sbuf_insert(&sbuf, 2);

    for(int i = 0; i<sbuf_getsize(&sbuf); i++) {
        printf("%d ", sbuf.buf[i]);
    }
    printf("\n");
}

