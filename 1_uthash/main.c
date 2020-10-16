#include "iovalhash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 学生属性 */
typedef struct {
    int age;
    int socre;
} stu_val_t;

/* 学生 */
typedef struct {
    char name[16];  /* 以学生名作为key */
    stu_val_t sv;
} stu_t;

void print_stu(hash_data_t* hd)
{
    stu_val_t* val = (stu_val_t*)(hd->val);

    printf("name = %s, age = %d, socre = %d\n", 
        hd->key.key,
        val->age, val->socre);
}

int main()
{
    hash_data_t *hash_hd = NULL;  // 哈希表头

    char name[16];

    int i;
    
    // 1.
    printf("插入\n");
    for (i = 0; i < 10; i++) 
    {
        sprintf(name, "%d", i);  // key
        stu_val_t* sv = malloc(sizeof(stu_val_t));
        sv->age = i;
        sv->socre = i;
        hash_set(&hash_hd, name, sv);
    }
    hash_travel(&hash_hd, print_stu);

    // 2.
    printf("修改\n");
    for (i = 0; i < 10; i++) 
    {
        sprintf(name, "%d", i);  // key
        stu_val_t* sv = malloc(sizeof(stu_val_t));
        sv->age = i * 2;
        sv->socre = i * 2;
        hash_set(&hash_hd, name, sv); // 修改
    }
    hash_travel(&hash_hd, print_stu);

    // 3.    
    printf("删除：1，4，20\n");
    hash_del(&hash_hd, "1");
    hash_del(&hash_hd, "4");
    hash_del(&hash_hd, "20");
    
    hash_travel(&hash_hd, print_stu);

    // 4.
    printf("释放哈希表\n");
    
    hash_destroy(&hash_hd);
    printf("len = %d\n", hash_count(hash_hd));

    return 0;
}