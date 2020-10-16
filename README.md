# uthash
开源库uthash/utlist使用小案例

# 案例使用
- uthash
1. key, value类型分别为：char [16], void*
- utlist
1. 实际上在开发过程中，最长使用的是Linux内核自带的链表struct list_head
2. 本质上，utlist和struct list_head一样，后者更加通用
