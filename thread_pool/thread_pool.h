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

typedef struct tp_task_s
{
    void (func*)(void *);
    void *arg;
} tp_task_t;


typedef struct tp_s tp_t;

/**
 * @brief 创建线程池
 * 
 * @param thread_num 线程个数
 * @return tp_t* 
 */
tp_t *tp_create(int thread_num);

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