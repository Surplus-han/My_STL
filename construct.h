/**
 * @file construct.h
 * @author han.jr
 * @brief construct �������Ĺ��������
 * @version 0.1
 * @date 2023-07-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MYTINYSTL_CONSTRUCT_H_
#define MYTINYSTL_CONSTRUCT_H_

// ���ͷ�ļ������������� construct��destroy
// construct : �������Ĺ���
// destroy   : ������������
#include <new>  //��ʹ��placement new �������ͷ�ļ�

#include "type_traits.h"
// #include "iterator.h"

#ifdef _MSC_VER
#pragma warning(push) //����һ��������ָ�����ǰ����״̬��ջ��
//����������֮��Ĵ������޸ľ���״̬�����ڴ�������ʱ���Իָ���֮ǰ��״̬��
/*
����һ��������ָ����ڽ����ض����档����������У�
������ 4100 ��ʾ "unused parameter"��
��δʹ�õĲ������档ͨ�����ָ�����������������ض��ľ��档*/
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER

namespace mystl{

    //constuct �������
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

    //destory ���������

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

