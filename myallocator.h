#ifndef __MYALLOCATOR_H__
#define __MYALLOCATOR_H__
#include<new>
#include<iostream>

//第一级配置器
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

//第二级配置器
enum {_ALIGN = 8};                              //按照8的基准倍数进行内存操作
enum {_MAXBYTES = 128};                         //自由链表最大的块大小为128
enum {_NFREELISTS = 16};                        //自由链表的长度等于_MAXBYTES/_ALIGN
template <bool threads, int inst>
class _DefaultAllocTemplate
{
private:
    union _Obj                                  //自由链表的结点类型
    {
        _Obj * _freeListLink;                   //指向自由链表的结点指针
        char _clientData[1];
    };
private:
    static char * _startFree;                   //内存池头指针
    static char * _endFree;                     //内存池尾指针
    static size_t _heapSize;                    //内存池已申请的内存大小
    static _Obj * volatile _freeList[_NFREELISTS];  // 16个自由链表的头指针

private:
    //根据区块大小，决定使用第几号自由链表,n>0
    static size_t _GetFreeListIndex(size_t bytes){
        return (bytes + (size_t) _ALIGN - 1) / (size_t) _ALIGN - 1;
    }

    //将bytes上调至8的倍数
    static size_t _GetRoundUp(size_t bytes){
        return (bytes + (size_t) _ALIGN -1) & (~(_ALIGN-1));
    }
    static void * _Refill(size_t n);            //在自由链表中申请内存，n表示需要的内存大小
    static void * _chunkAlloc(size_t, int & nobjs); //在内存池中申请nobjs个对象，每个对象size个大小

public:
    static void * Allocate(size_t n);       //n大于0
    static void * DeAllocate(void *p, size_t n); 
};
//类外初始化静态成员变量和定义静态成员函数





#endif