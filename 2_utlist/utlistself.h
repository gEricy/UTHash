/* A doubly-linked list */

/*********************************************************************************
  *Author:  guojiawei
  *Date:    2019-11-14
  *Description:  自己封装的双线链表
**********************************************************************************/

#ifndef  __UTLISTSELF_H__
#define  __UTLISTSELF_H__

#include "utlist.h"


// 链表中的每个元素
typedef struct dblist {
    void *data;    // (万能指针) 链表中存放的元素
    struct dblist *next, *prev;
} dblist;


/*-------------- 插入 --------------*/

/**
 * 新建链表节点
 * @param [in] data  链表节点中存放的元素
 * @return 成功，new_node；失败，NULL
 */
dblist* dblist_new_node(void* data);

/**
 *    头插
 * @param [in]  p_list  链表头
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_prepend(dblist** p_list, void* data);

/**
 *    尾插
 * @param [in]  p_list  链表头
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_append(dblist** p_list, void* data);

/**
 *    在任意元素位置（而不是链表头部）前面进行插入
 * @param [in]  p_list  链表头
 * @param [in]  ref     任意元素(非链表头部)
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_prepend_elem(dblist** p_list, dblist* ref, void* data);

/**
 *    在任意元素位置（而不是链表尾部）后面进行插入
 * @param [in]  p_list  链表头
 * @param [in]  ref     任意元素(非链表尾部)
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_append_elem(dblist** p_list, dblist* ref, void* data);

/*-------------- 查找 --------------*/

typedef int(*data_cmp_cbk)(void* data1, void* data2);

/**
 *   查找
 * @param [in] p_list  链表头
 * @param [in] cmp     用户自定义比较准则
 * @param [in] data    待查找的元素
 * @return  成功，返回指向元素的指针；失败，NULL
 */
dblist* dl_search(dblist* p_list, data_cmp_cbk cmp, void* data);

/*-------------- 删除 --------------*/

// 释放链表节点中data的回调函数
typedef void(*data_free_cbk)(void* data);

/**
 *   删除值为data的元素
 * @param [in] p_list    链表头
 * @param [in] cmp_cbk   比较大小的规则
 * @param [in] data      待删元素
 * @param [in] free_cbk  data元素释放的回调函数
 * @return  实际删除的元素个数
 */
int dblist_del_data(dblist** p_list, data_cmp_cbk cmp_cbk, void* data, data_free_cbk free_cbk);

/**
 *   删除dblist中的所有的元素
 * @param [in] p_list    链表头
 * @param [in] free_cbk  data元素释放的回调函数
 */
void dblist_free(dblist** p_list, data_free_cbk cbk);

/*-------------- 替换 --------------*/



/*-------------- 遍历 --------------*/

typedef void (*data_print_cbk)(void* data);

/**
 * 遍历打印
 * @param [in] p_list  链表头
 * @param [in] cbk     (用户自定义)打印data的回调函数
 */
void dblist_travel(dblist* p_list, data_print_cbk cbk);


#endif