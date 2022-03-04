#ifndef __COUNSTRUCT_H__
#define __COUNSTRUCT_H__ 1

#include"type_traits.h"
#include"my_iterator.h"

namespace saberstl{


template<class T1, class T2>
inline void construct(T1* p, const T2& value)
{
    ::new (p) T1(value);
}


template<class T1>
inline void construct(T1* p)
{
    ::new (p) T1;
}

template<class T1>
inline void destroy(T1* p)
{
    p->~T1();
}

template<class Forward_iterator, class T>
inline void _destroy_aux(Forward_iterator first, Forward_iterator last, T*)
{
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    _destroy_aux(first, last, trivial_destructor() );
}

//第二个版本，如果析构函数是trivial destructor 那就什么都不做
template<class Forward_iterator>
inline void _destroy_aux(Forward_iterator first, Forward_iterator last, __true_type)  {}

//第三个版本，要一一调用
template<class Forward_iterator>
inline void _destroy_aux(Forward_iterator first, Forward_iterator last, __false_type)
{
    for(; first!=last; ++first)
    {
        destroy(&*first);
    }
}

template<class Forward_iterator>
inline void destroy(Forward_iterator first, Forward_iterator last)
{
    //利用trait 技术，进而求取最合适的析构函数
    //value_type 就是把first 中的实际类型给提取出来
    _destroy_aux(first, last, _value_type(first) );
}


inline void destroy(char*, char* ) {}
inline void destroy(int*, int* ) {}
inline void destroy(long*, long* ) {}
inline void destroy(float*, float* ) {}
inline void destroy(double*, double* ) {}
inline void destroy(wchar_t*, wchar_t* ) {}



}


#endif
