#ifndef __SBUF_H__
#define __SBUF_H__


/* $begin sbuft */
typedef struct {
    int *buf;          /* Buffer array */         
    int n;             /* Maximum number of slots */
		int size;
    int front;         /* buf[(front+1)%n] is first item */
    int rear;          /* buf[rear%n] is last item */
    
} sbuf_t;
/* $end sbuft */

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);

#endif /* __SBUF_H__ */
