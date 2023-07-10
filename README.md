##空间配置器
allocator
包括了 allocator 和 constructor，分别定义在 allocator.h 和 construct.h 中。
allocator 负责空间的配置与回收，定义了一个类 mystl::alloc 用于管理内存，定义在 alloc.h 。
constructor 负责对象的构造与析构，对应两个全局函数： construct 和 destroy。
