/*********************************************************************************
  *@Author:  guojiawei
  *@Date:    2019-11-13
  *@Description:  哈希表
        适用于key = key， value = 任意值（万能指针：void *data）
**********************************************************************************/

#ifndef __IOVALHASH_H__
#define __IOVALHASH_H__

#include "uthash.h"


// 哈希表键值：key
typedef struct {
    char  key[16];  /* 键值是字符串 */
    // ...
} hash_key_t;

// 哈希表键值对：<key,value>
typedef struct hash_data {
    hash_key_t  key;           /* key */
    void    *val;              /* value:指向自定义结构体 */
    UT_hash_handle hh;         /* makes this structure hashable */
} hash_data_t;

// 哈希表中键值对个数
int hash_count(hash_data_t *hashlist);

/**
 *  查找键值
 *@param [in]  hashlist     哈希表头
 *@param [in]  key          key
 *@return 查找不到，返回NULL；查找到，返回指针(指向查找到的键值对)
 */
hash_data_t *hash_find(hash_data_t **hashlist, char* key);

/**
 *    设置key的value
 * @detail 若key存在，设置value；若key不存在，则新建<key,value>插入哈希表
 * @param  [in]  hashlist   哈希表头
 * @param  [in]  key        键
 * @param  [in]  val        新的值
 * @return 成功，0；发生错误，-1
 */
int hash_set(hash_data_t **hashlist, char* key, void* val);

/**
 *    删除哈希表中的节点
 * @param  [in]  key    键
 * @return 删除成功，0；失败，-1
 */
int hash_del(hash_data_t **hashlist, char* key);


/**
 *  删除哈希表中所有键值对、释放整个哈希表
 *@param [in]  hashlist     哈希表头
 */
void hash_destroy(hash_data_t **hashlist);


typedef void (*print_val_cbk)(hash_data_t* hd);
/**
 *    遍历打印哈希表
 */
void hash_travel(hash_data_t **hashlist, print_val_cbk cbk);

#endif