#ifndef MYTINYSTL_ALLOCATOR_H_
#define MYTINYSTL_ALLOCATOR_H_

// 这个头文件包含一个模板类 allocator，用于管理内存的分配、释放，对象的构造、析构
// #include "construct.h"
// #include "util.h"
namespace mystl
{

    // 模板类 :allocator
    // 模板函数代表数据类型

    template <class T>
    class allocator
    {
    public:
        typedef T              value_type;
        typedef T*             pointer;
        typedef const T*       const_pointer;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef size_t         size_type;
        typedef ptrdiff_t      difference_type;

    public:
        //分配内存函数allocate声明
        static T* allocate();
        static T* allocate(size_type n);
        
        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_type n);

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr,T&& value);

        template<class... Args>//可变参数模板
        static void construct(T* ptr, Args&&... args);

        static void destroy(T* ptr);
        static void destroy(T* first,T* last);
    };
    template<class T>
    T* allocator<T>::allocate(){
        return static_cast<T*>(::operator new(sizeof(T)));
        //使用 ::operator new 而不是 new，可以确保调用的是全局的内存分配操作符，
        //而不是某个特定命名空间或类中重载的版本。
    }
    
    template <class T>
    T* allocator<T>::allocate(size_type n){
        if(n == 0){
            return nullptr;
        }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr){
        if(ptr == nullptr){
            return;
        }
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr, size_type){
        if(ptr == nullptr){
            return;
        }
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr){
        mystl::construct(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr, const T& value){
        mystl::construct(ptr, value);
    }

    template  <class T>
    void allocator<T>::construct(T* ptr,T&& value){
        mystl::construct(ptr, mystl::move(value));
    }

    template <class T>
    template <class ...Args>
    void allocator<T>::construct(T* ptr,Args&& ... args){
        /*
        mystl::forward 是一个用于完美转发（perfect forwarding）
        的函数模板，它用于保持传递的参数类型和值类别不变。
        */
        mystl::construct(ptr, mystl::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T* ptr){
        mystl::destroy(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T* first,T* last){
        mystl::destroy(first,last);
    }
}  // namespace mystl
#endif