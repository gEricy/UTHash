#include "utlistself.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <errno.h>

/*-------------- 插入 --------------*/

/**
 * 新建链表节点
 * @param [in] data  链表节点中存放的元素
 * @return 成功，new_node；失败，NULL
 */
dblist* dblist_new_node(void* data)
{
    dblist* new_node = malloc(sizeof(dblist));
    if(!new_node)
        return NULL;
    new_node->data = data;

    return new_node;
}

/**
 *    头插
 * @param [in]  p_list  链表头
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_prepend(dblist** p_list, void* data)
{
    dblist* new_node = dblist_new_node(data);
    if(new_node == NULL)
        return -1;
    
    DL_PREPEND(*p_list, new_node);
    return 0;
}

/**
 *    尾插
 * @param [in]  p_list  链表头
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_append(dblist** p_list, void* data)
{
    dblist* new_node = dblist_new_node(data);
    if(new_node == NULL)
        return -1;
    
    DL_APPEND(*p_list, new_node);
    return 0;
}

/**
 *    在任意元素位置（而不是链表头部）前面进行插入
 * @param [in]  p_list  链表头
 * @param [in]  ref     任意元素(非链表头部)
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_prepend_elem(dblist** p_list, dblist* ref, void* data)
{
    dblist* new_node = dblist_new_node(data);
    if(new_node == NULL)
        return -1;

    DL_PREPEND_ELEM(*p_list, ref, new_node);
    return 0;
}

/**
 *    在任意元素位置（而不是链表尾部）后面进行插入
 * @param [in]  p_list  链表头
 * @param [in]  ref     任意元素(非链表尾部)
 * @param [in]  data    链表节点中存放的元素
 * @return 成功，0；失败，-1
 */
int dblist_append_elem(dblist** p_list, dblist* ref, void* data)
{
    dblist* new_node = dblist_new_node(data);
    if(new_node == NULL)
        return -1;

    DL_APPEND_ELEM(*p_list, ref, new_node);
    return 0;
}


/*-------------- 查找 --------------*/

/**
 *   查找
 * @param [in] p_list  链表头
 * @param [in] cmp     用户自定义比较准则
 * @param [in] data    待查找的元素
 * @return  成功，返回指向元素的指针；失败，NULL
 */
dblist* dl_search(dblist* p_list, data_cmp_cbk cmp, void* data)
{
    dblist* elt, etmp;
    
    etmp.data = data;

    DL_SEARCH(p_list, elt, &etmp, cmp);

    return elt == NULL ? NULL : elt;
}


/*-------------- 删除 --------------*/

/**
 *   删除dblist中的元素elt
 * @param [in] p_list    链表头
 * @param [in] elt       指向待删除的元素
 * @param [in] free_cbk  data元素释放的回调函数
 */
static void dblist_del(dblist** p_list, dblist* elt, data_free_cbk cbk)
{
    assert(p_list && elt);
    
    DL_DELETE(*p_list, elt);
    
    cbk(elt->data);  // 记得：先释放elt成员指向的内存
    free(elt);  // 再释放elt
}


/**
 *   删除值为data的元素
 * @param [in] p_list    链表头
 * @param [in] cmp_cbk   比较大小的规则
 * @param [in] data      待删元素
 * @param [in] free_cbk  data元素释放的回调函数
 * @return  实际删除的元素个数
 */
int dblist_del_data(dblist** p_list, data_cmp_cbk cmp, void* data, data_free_cbk cbk)
{
    int ret = 0;

    dblist *elt, *tmp;

    /* now delete each element, use the safe iterator */
    DL_FOREACH_SAFE(*p_list, elt, tmp) {
        if(cmp(elt->data, data) == 1)
        {
            dblist_del(p_list, elt, cbk);  // 删除一个元素
            ret++;
        }
    }

    return ret;
}

/**
 *   删除dblist中的所有的元素
 * @param [in] p_list    链表头
 * @param [in] free_cbk  data元素释放的回调函数
 */
void dblist_free(dblist** p_list, data_free_cbk cbk)
{
    dblist *elt, *tmp;

    /* now delete each element, use the safe iterator */
    DL_FOREACH_SAFE(*p_list, elt, tmp) {
        dblist_del(p_list, elt, cbk);  // 删除一个元素
    }
    *p_list = NULL;
}

/*-------------- 替换 --------------*/



/*-------------- 遍历 --------------*/

/**
 * 遍历打印
 * @param [in] p_list  链表头
 * @param [in] cbk     (用户自定义)打印data的回调函数
 */
void dblist_travel(dblist* p_list, data_print_cbk cbk)
{
    dblist *elt, *tmp;
    DL_FOREACH_SAFE(p_list, elt, tmp) {
        cbk(elt->data);
    }
}