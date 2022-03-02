#ifndef __MY_TYPE_TRAITS_H__
#define __MY_TYPE_TRAITS_H__

#include<cstddef>

namespace saberstl{
//五种迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//迭代器模板
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator{
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

//类型提取
template<class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category    iterator_category;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
};

//对于原生指针的偏特化模板
template<class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

template<class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

//提取迭代器类型
template<class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category Category;
    return Category();
}

//提取迭代器的容量
template<class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type*> (0);
}

//提取迭代器指向的数据类型
template<class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
}

//distance的input_iterator_tag特化版本
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_Distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first != last){
        ++first;
        ++n;
    }
    return n;
}

//distance的random_access_iterator_tag特化版本
template<class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_Distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    return last-first;
}

//distance函数
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last){
    typedef typename iterator_traits<InputIterator>::iterator_category Category;
    return _Distance(first, last, Category());
}



// 以下函数用于让迭代器前进 n 个距离

// advance 的 input_iterator_tag 的版本
template <class InputIterator, class Distance>
inline void _advance(InputIterator& i, Distance n, input_iterator_tag)
{
  while (n--) 
    ++i;
}

// advance 的 bidirectional_iterator_tag 的版本
template <class BidirectionalIterator, class Distance>
inline void _advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
  if (n >= 0)
    while (n--)  ++i;
  else
    while (n++)  --i;
}

// advance 的 random_access_iterator_tag 的版本
template <class RandomIter, class Distance>
inline void _advance(RandomIter& i, Distance n, random_access_iterator_tag)
{
  i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n)
{
  _advance(i, n, iterator_category(i));
}

}










#endif