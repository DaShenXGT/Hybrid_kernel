#include <stdio.h>
#include <stdint.h>

#ifndef H_KERNEL_H
#define H_KERNEL_H

/* 在任务运行期间的任意时刻允许的任务最大数目,任务增加的时候，（（必须））进行修改 */
#define SCH_MAX_TASKS (3)

typedef struct // 定义在data区只有一个目的：快速存取
{
    void (*pTask)(void); // 指向任务的指针
    uint32_t Delay;      // 任务初始延迟
    uint16_t Period;     // 连续运行之间的间隔
    uint8_t RunMe;       // 当任务需要运行时(由调度器)+1
    //如果是任务式合作式的，设置为1
    //如果是抢占式合作式的，设置为0
    uint8_t Co_op;       // 合作式和抢占式内核的标志
} Task_t;

/***********************************************************************************************************************
* @param hook:指定的钩子函数
***********************************************************************************************************************/
void SCH_Idle_Sethook(void (*hook)(void));

/***********************************************************************************************************************
 * @brief 此功能放入定时器里面进行更新,刷新任务队列
 ***********************************************************************************************************************/
void SCH_Update(void);

/***********************************************************************************************************************
 * @brief    清空第Index个任务块
 * @param Index: 任务的节点号
 ***********************************************************************************************************************/
void SCH_Clear_Task(const uint8_t Index);

/***********************************************************************************************************************
 * @brief    调度任务初始化，用于准备调度器
 ***********************************************************************************************************************/
void SCH_Init(void);

/***********************************************************************************************************************
 * @brief    向调度器增加任务函数
 * @param pTask:指向任务的指针
 * @param Delay:任务初始延迟
 * @param Period:连续运行之间的间隔
 * @param Co_op:合作式和抢占式内核的标志,如果是任务式合作式的，设置为1,如果是抢占式合作式的，设置为0
 * @return uint8_t: >=SCH_MAX_TASKS时, 说明任务队列已满，出现了错误
***********************************************************************************************************************/
uint8_t SCH_Add_Task(void (*pTask)(void), const uint32_t Delay, const uint16_t Period,const uint8_t Co_op);

/***********************************************************************************************************************
 * @brief    删除节点处的任务
 * @param Index:任务的节点
 * @return uint8_t: 0xFF-fail
 ***********************************************************************************************************************/
uint8_t SCH_Delete_Task(const uint8_t Index);

/***********************************************************************************************************************
 * @brief    任务运行，此任务一旦运行永不回头
 ***********************************************************************************************************************/
void SCH_Dispatch_Tasks(void);

#endif
