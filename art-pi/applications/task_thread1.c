/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-31     44489       the first version
 */



#include <rthw.h>
#include <rtthread.h>
#define THREAD_PRIORITY 20
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5

//ȫ�ֱ���
static int cnt = 0;


//����һ���߳���ں���
void add_number_entry(void * parameter)
{
    rt_uint32_t no;
    rt_uint32_t level;
    no = (rt_uint32_t) parameter;
    while (1)
    {
        /* �ر�ȫ���ж�*/
        //level = rt_hw_interrupt_disable();
        cnt += no;
        /* �ָ�ȫ���ж�*/
        //rt_hw_interrupt_enable(level);
        rt_kprintf("protect thread[%d]'s counter is %d\n", no, cnt);
        rt_thread_mdelay(no * 10);
    }
}

int task_creat_addnumber(void)
{
    rt_thread_t thread;
    thread = rt_thread_create("add number1", add_number_entry, (void *)10, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if(thread != NULL)
    {
        rt_thread_startup(thread);
    }

    thread = rt_thread_create("add number2", add_number_entry, (void *)20, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

    if(thread != NULL)
    {
        rt_thread_startup(thread);
    }
    return 1;
}

/* ������msh �����б���*/
MSH_CMD_EXPORT(task_creat_addnumber, add numbers);
