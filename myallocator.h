#ifndef __MYALLOCATOR_H__
#define __MYALLOCATOR_H__
#include<new>
#include<iostream>

typedef void(*MALLOCALLOC)();           //将void (*)()   重命名成MALLOCALLOC
template<int inst>
class _MallocAllocTemplate
{
private:
       static void* _OomMalloc(size_t);       //malloc失败的时候调用的函数
       static MALLOCALLOC _MallocAllocOomHandler;         //函数指针，内存不足的时候的处理机制
public:
       static void* _Allocate(size_t n)                        //分配空间n个字节的空间
       {
              void *result=0;
              result = malloc(n);
              if (0 == result)                    //若果malloc失败，则就调OOM_malloc
                     _OomMalloc(n);
              return result;
       }
       static void _DeAllocate(void *p)                //释放这块空间
       {
              free(p);
       }
       static MALLOCALLOC _SetMallocHandler(MALLOCALLOC f)    //这是一个函数，参数是一个函数指针，返回值也是一个函数指针
       {
              MALLOCALLOC old = _MallocAllocOomHandler;
              _MallocAllocOomHandler = f;              //将内存分配失败的句柄设置为f(让它指向一个内存失败了，让系统去释放其他地方空间的函数)
              return old;
       }
};
template<int inst>
void(* _MallocAllocTemplate<inst>::_MallocAllocOomHandler)()=0;    //默认不设置内存不足处理机制
template<int inst>
void* _MallocAllocTemplate<inst>::_OomMalloc(size_t n)
{
       MALLOCALLOC _MyMallocHandler;     //定义一个函数指针
       void *result;               
       while (1)
       {
              _MyMallocHandler = _MallocAllocOomHandler;
              if (0 == _MyMallocHandler)                  //没有设置内存不足处理机制
                     throw std::bad_alloc();                  //则抛出异常
              (*_MyMallocHandler)();                 //调用内存不足处理的函数，申请释放其他地方的内存
              if (result = malloc(n))                //重新申请内存
                     break;
       }
       return result;                              //申请成功时，则返回这块内存的地址
}
typedef _MallocAllocTemplate<0> malloc_alloc;

#endif