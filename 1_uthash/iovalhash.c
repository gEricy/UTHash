#include "iovalhash.h"

// 哈希表中键值对个数
int hash_count(hash_data_t *hashlist)
{
    return  HASH_COUNT(hashlist);
}

/**
 *  查找键值
 *@param [in]  hashlist     哈希表头
 *@param [in]  key          key
 *@return 查找不到，返回NULL；查找到，返回指针(指向查找到的键值对)
 */
hash_data_t *hash_find(hash_data_t **hashlist, char* key)
{
    hash_data_t *hd = NULL;

    hash_key_t h_key;
    strncpy(h_key.key, key, 16);

    HASH_FIND(hh, *hashlist, &h_key, sizeof(hash_key_t), hd);

    return hd;
}

/**
 *    设置key的value
 * @detail 若key存在，设置value；若key不存在，则新建<key,value>插入哈希表
 * @param  [in]  hashlist   哈希表头
 * @param  [in]  key        键
 * @param  [in]  val        新的值
 * @return 成功，0；发生错误，-1
 */
int hash_set(hash_data_t **hashlist, char* key, void* val)
{
    hash_data_t *hd = NULL;

    hd = hash_find(hashlist, key);
    if(hd != NULL)  // 查找到，修改val
    {
        free(hd->val); // 释放旧的val
        hd->val = val;  // 更改val指向新val

        return 0;
    }

    // 没查找到，新建<key, value>，添加到hash表中
    hash_data_t* new_hd = malloc(sizeof(hash_data_t));
    if(!new_hd)
        return -1;
    
    // 1. key赋值
    strncpy(new_hd->key.key, key, 16);
    // 2. value赋值
    new_hd->val = val;
    // 3. 插入到哈希表
    HASH_ADD(hh, *hashlist, key, sizeof(hash_key_t), new_hd);
   
    return 0;
}


/**
 *    删除哈希表中的节点
 * @param  [in]  key    键
 * @return 删除成功，0；失败，-1
 */
int hash_del(hash_data_t **hashlist, char* key)
{
    hash_data_t *hd = NULL;

    hd = hash_find(hashlist, key);
    if(hd == NULL)  // 没查找到
        return -1;

    HASH_DEL(*hashlist, hd);
    if(hd->val != NULL)  // 先释放val指向的内存
        free(hd->val);
    free(hd);
    
    return 0;
}

/**
 *  删除哈希表中所有键值对、释放整个哈希表
 *@param [in]  hashlist     哈希表头
 */
void hash_destroy(hash_data_t **hashlist)
{
    hash_data_t *hd, *tmp;

    if (hashlist != NULL && *hashlist != NULL)
    {
        HASH_ITER(hh, *hashlist, hd, tmp) {
            HASH_DEL(*hashlist, hd);
            if (hd->val != NULL) 
                free(hd->val);  // 释放value
            free(hd);
        }

        // free(*hashlist);  // 哈希表，不用释放！
        *hashlist = NULL;
    }
}


/**
 *    遍历打印哈希表
 */
void hash_travel(hash_data_t **hashlist, print_val_cbk cbk)
{
    hash_data_t *hd, *tmp;

    HASH_ITER(hh, *hashlist, hd, tmp) {
        cbk(hd);
    }
}