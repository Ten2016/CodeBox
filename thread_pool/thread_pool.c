/**
 * @file thread_pool.c
 * @author tjl
 * @brief 
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "thread_pool.h"


#define SAFE_FREE(_point) \
if (_point) { \
    free(_point); \
    _point = NULL; \
}

// 任务节点
typedef struct task_node_s {
    tp_task_t *task;
    struct task_node_s *next;
} task_node_t;


// 任务队列
typedef struct task_queue_s {
    int size;
    task_node_t *pre_head;
    task_node_t *pre_tail;
} task_queue_t;

// 线程池句柄
typedef struct tp_s {
    int ts;                     // 线程数
    int qs;                     // 任务队列长度

    pthread_t *tfd;             // 线程句柄数组
    task_queue_t *tq;           // 任务队列

    pthread_cond_t  cond;       // 条件变量
    pthread_mutex_t lock;       // 互斥锁

} tp_t;



/**
 * @brief 创建任务队列
 * 
 * @return task_queue_t* 
 */
task_queue_t *tp_tq_create() {
    task_queue_t *tq = (task_queue_t*)malloc(sizeof(task_queue_t));
    task_node_t *tn = (task_node_t*)malloc(sizeof(task_node_t));
    if (!tq || !tn) {
        goto L_failed;
    }

    tn->task = NULL;
    tn->next = NULL;

    tq->size = 0;
    tq->pre_head = tn;
    tq->pre_tail = tn;

    return tq;

L_failed:
    SAFE_FREE(tq);
    SAFE_FREE(tn);
    return NULL;
}

/**
 * @brief 释放任务队列
 * 
 * @param tq 任务队列
 */
void tp_tq_destroy(task_queue_t *tq) {
    if (!tq) {
        return ;
    }

    task_node_t *tn = tq->pre_head;
    while(tn) {
        tp_task_t *task = tn->task;
        if (task) {
            if (task->flag | TP_TASK_ARG_FREE) {
                SAFE_FREE(task->arg);
            }
            if (task->flag | TP_TASK_FREE) {
                SAFE_FREE(task);
            }
        }

        task_node_t *tmp = tn->next;
        SAFE_FREE(tn);
        tn = tmp;
    }
    SAFE_FREE(tq);

    return ;
}

int tp_tq_add_task(int)


/**
 * @brief 创建线程池
 * 
 * @param thread_size 线程个数
 * @param queue_size  任务队列最大容量
 * @return tp_t* 
 */
tp_t *tp_create(int thread_size, int queue_size) {
    tp_t *tp = (tp_t *)malloc(sizeof(tp_t));
    pthread_t *tfd = (pthread_t *)malloc(sizeof(pthread_t) * thread_size);
    if (!tp || !tfd) {
        goto L_failed;
    }

    task_queue_t *tq = tp_tq_create();
    if (!tq) {
        goto L_failed;
    }

    tp->ts = thread_size;
    tp->qs = queue_size;
    tp->tq = tq;
    tp->tfd = tfd;
    tp->cond = PTHREAD_COND_INITIALIZER;
    tp->lock = PTHREAD_MUTEX_INITIALIZER;

    return tp;

L_failed:
    tp_tq_destroy(tq);
    SAFE_FREE(tfd);
    SAFE_FREE(tp);
    return NULL;
}


/**
 * @brief 运行线程池
 * 
 * @param tp 线程池句柄
 * @return int 0：成功 非0：错误
 */
int tp_run(tp_t *tp) {
    if (!tp) {
        return TP_ERROR_1;
    }

    for (int i = 0; i < tp->ts; i++) {
        int ret = pthread_create(&(tp->tfd[i]), NULL, thread_func, NULL);
        if (ret != 0) {
            return TP_ERROR_3;
        }
        printf("create thread: %d\n", i);
    }

    return TP_SUCCESS;
}