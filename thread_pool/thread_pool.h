/**
 * @file thread_pool.h
 * @author tjl
 * @brief  线程池接口
 * @version 0.1
 * @date 2022-03-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H


#include <pthread.h>


#ifdef __cplusplus
extern "C" {
#endif

#define TP_TASK_FREE            (1)
#define TP_TASK_ARG_FREE        (1 << 1)

typedef struct tp_task_s
{
    unsigned int flag;
    void (*func)(void *);
    void *arg;
} tp_task_t;


typedef struct tp_s tp_t;

enum TP_ERROR {
    TP_SUCCESS = 0,
    TP_ERROR_1,
    TP_ERROR_2,
    TP_ERROR_3
};

#define TP_ERROR_UNKNOWN        "errno error"
cosnt char *err_msg[] = {
    "success",
    "input parameter invalid",
    "task queue full",
    "create thread failed"
};


/**
 * @brief 获取错误信息
 * 
 * @param errno 错误码
 * @return const char* 
 */
const char *tp_get_error(int errno) {
    if (errno < 0 || errno > sizeof(err_msg) / sizeof(err_msg[0])) {
        return TP_ERROR_UNKNOWN;
    }
    return err_msg[errno];
}


/**
 * @brief 创建线程池
 * 
 * @param thread_size 线程个数
 * @param queue_size  任务队列最大容量
 * @return tp_t* 
 */
tp_t *tp_create(int thread_size, int queue_size);

/**
 * @brief 运行线程池
 * 
 * @param tp 线程池句柄
 * @return int 0：成功 非0：错误
 */
int tp_run(tp_t *tp);


/**
 * @brief 销毁线程池
 * 
 * @param tp 线程池句柄
 */
void tp_destroy(tp_t *tp);


/**
 * @brief 向任务队列中插入任务
 * 
 * @param tp 线程池句柄
 * @param tp_task 任务句柄
 * @return int 0：成功 非0：错误
 */
int tp_add_task(tp_t *tp, tp_task_t *tp_task);



#ifdef __cplusplus
}
#endif

#endif