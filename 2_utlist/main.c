

#include "utlistself.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------学生类------------*/

// 链表节点中存放的数据
typedef struct {
    char name[100];
    int age;
} stu_t;

// 打印
void stu_print(void *data)
{
    stu_t *stu_data = (stu_t *)data;
    printf("name = %s, age = %d\n", stu_data->name, stu_data->age);
}

/**
 * @return 相等，1；不等，0
 */
int stu_cmp(void *data1, void *data2)
{
    stu_t *stu_data1 = (stu_t *)data1;
    stu_t *stu_data2 = (stu_t *)data2;

    return (strcmp(stu_data1->name, stu_data2->name) == 0) && (stu_data1->age == stu_data2->age);
}

// 释放
void stu_free(void* data)
{
    stu_t *stu_data = (stu_t *)data;
    if(!stu_data)
        return;

    free(stu_data);
}

/*----------测试------------*/

int main()
{
    dblist *dblist_head = NULL;

    int ret;

    int i = 0;

    printf("1.尾插\n");
    for (i = 0; i < 10; i++) {
        stu_t *stu = malloc(sizeof(stu_t));
        snprintf(stu->name, 100, "%d", i);
        stu->age = i;
        dblist_append(&dblist_head, stu);
    }

    dblist_travel(dblist_head, stu_print);

    printf("2.头插\n");
    for (i = 0; i < 10; i++) {
        stu_t *stu = malloc(sizeof(stu_t));
        snprintf(stu->name, 100, "%d", i);
        stu->age = i;
        dblist_prepend(&dblist_head, stu);
    }

    dblist_travel(dblist_head, stu_print);

    printf("3.删除\n");
    stu_t data1 = {"1", 1};
    ret = dblist_del_data(&dblist_head, stu_cmp, &data1, stu_free); 
    printf("  3.1 删除[%d]个元素\n", ret);  // [2]

    stu_t data2 = {"2", 1};
    ret = dblist_del_data(&dblist_head, stu_cmp, &data2, stu_free);
    printf("  3.2 删除[%d]个元素\n", ret);  // [0]

    dblist_travel(dblist_head, stu_print);


    dblist_free(dblist_head, stu_free);
    
    return 0;
}