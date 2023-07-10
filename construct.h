/**
 * @file construct.h
 * @author han.jr
 * @brief construct 负责对象的构造和析构
 * @version 0.1
 * @date 2023-07-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构
#include <new>  //欲使用placement new 则包含此头文件

#include "type_traits.h"
// #include "iterator.h"

#ifdef _MSC_VER
#pragma warning(push) //这是一个编译器指令，将当前警告状态入栈。
//这样可以在之后的代码中修改警告状态，而在代码块结束时可以恢复到之前的状态。
/*
这是一个编译器指令，用于禁用特定警告。在这个例子中，
警告码 4100 表示 "unused parameter"，
即未使用的参数警告。通过这个指令，编译器将忽略这个特定的警告。*/
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER

namespace mystl{

    //constuct 构造对象
    template <class Ty>
    void construct(Ty* ptr){
        ::new ((void*)ptr) Ty();
    }

    template <class Ty1,class Ty2>
    void construct(Ty1* ptr,const Ty2& value){
        ::new ((void*)ptr) Ty1(value);
    }
    
    template <class Ty,class...Args>
    void construct(Ty* ptr,Args&&... args){
        ::new ((void*)ptr) Ty(mystl::forwards<Args>(args)...);
    }

    //destory 对象的析构

    template <class Ty>
    void destory_one(Ty*,std::true_type){}

    template <class Ty>
    void destory_one(Ty* pointer, std::false_type){
        if(pointer != nullptr){
            pointer->~Ty();
        }
    }


}


#endif

