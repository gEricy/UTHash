# uthash
开源库uthash/utlist使用小案例

# 简单介绍
- uthash

uthash对key为简单类型，如int等使用起来是比较方便的，但是对于key为复杂类型使用起来有些繁琐，因此，在实践中，写了个小demo：key, value类型分别为：char [16], void*。当然，uthash源码库中也有很多案例，可供参考。

- utlist
实际上在开发过程中，最长使用的是Linux内核自带的链表struct list_head。本质上，utlist和struct list_head一样，后者更加通用
