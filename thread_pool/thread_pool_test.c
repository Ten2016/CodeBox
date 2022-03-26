/**
 * @file thread_pool_test.c
 * @author tjl
 * @brief  线程池测试
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#include "thread_pool.h"

#define THREAD_NUM_DEF      (5)
#define THREAD_NUM_MIN      (1)
#define THREAD_NUM_MAX      (100)

#define TASK_QUEUE_DEF      (5)
#define TASK_QUEUE_MIN      (1)
#define TASK_QUEUE_MAX      (10)

typedef struct {
    int cnt;
    int time;
} func_arg_t;

void task_func(void *data) {

    curr_time = ()date;
    printf("curr_time:\tthread_id: %x\n",);
    sleep(2);
}


int main(int argc, char **argv) {

    int tn = THREAD_NUM_DEF;
    int qn = TASK_QUEUE_DEF;
    if (argc >= 2) {
        tn = atoi(argv[1]);
        if (tn < THREAD_NUM_MIN || tn > THREAD_NUM_MAX) {
            tn = THREAD_NUM_DEF;
        }
        if (argc >= 3) {
            qn = atoi(argv[2]);
            if (qn < TASK_QUEUE_MIN || qn > TASK_QUEUE_MAX) {
                qn = TASK_QUEUE_DEF;
            }            
        }
    }
    printf("thread num: %d, task queue size: %d\n", tn, qn);

    tp_t *tp = tp_create(tn);
    if (!tp) {
        printf("[error]: %s failed", __FUNCTION__);
        return 1;
    }

    int ret = tp_run(tp);
    if (ret != TP_SUCCESS) {
        printf("[error]: %s failed, msg: %s", __FUNCTION__, tp_get_error(ret));
        return 1;
    }

    for (int i = 0; i < 100; i++) {

        tp_task_t *task = (tp_task_t *)malloc(sizeof(tp_task_t));
        func_arg_t *arg = (func_arg_t *)malloc(sizeof(func_arg_t));

        if (!task || !arg) {
            printf("[error]: malloc failed\n");
            break;
        }

        arg->cnt = i;
        arg->time = time(NULL);

        task->task_arg = (void*)arg;
        task->task_func = task_func;
        task->need_free = 1;

        ret = tp_add_task(tp, task);
        if (ret != TP_SUCCESS) {
            printf("[error]: %s failed, msg: %s", __FUNCTION__, tp_get_error(ret));
            free(arg);
            if (task->need_free) {
                free(task);
            }
        }


        sleep(1);
    }


    (void)tp_destroy(tp);

    return 0;
}
