#ifndef __MY_LIST_H__
#define __MY_LIST_H__ 1

#include"myallocator.h"
#include<memory>
#include<algorithm>
#include"construct.h"
/*****************未完成**********/
namespace saberstl{

//list节点设计
template<class T>
struct __list_node
{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

//list迭代器设计
template<class T, class Ref, class Ptr>
struct __list_iterator
{
    typedef __list_iterator<T, T&, T*>   iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag   iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node;//指向当前节点的指针

    //初始化,构造函数
    __list_iterator(link_type x) : node(x){}
    __list_iterator(){}
    __list_iterator(const iterator& x) : node(x.node){}

    //重载运算符
    bool operator==(const self& x) const {return node == x.node;}
    bool operator!=(const self& x) const {return node != x.node;}

    //取节点数据值
    reference operator*() const {return (*node).data;}

    //存取运算子
    pointer operator->() const {return &(operator*());}

    //对迭代器加一就是前进一个节点,前置++
    self& operator++(){
        node = (link_type) ((*node).next);
        return *this;
    }
    //后置++
    self& operator++(int){
        self tmp = *this;
        ++*this;
        return tmp;
    }
    //对迭代器减一就是后退一个节点,前置--
    self& operator--(){
        node = (link_type) ((*node).prev);
        return *this;
    }
    //后置--
    self& operator--(int){
        self tmp = *this;
        --*this;
        return tmp;
    }
};

//list的数据结构
template<class T, class Alloc = alloc>
class list{
protected:
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
    //型别定义
    typedef list_node* link_type;
    typedef T           value_type;
    typedef list_node* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

protected:
    link_type node;//只需要一个指针就可以表示整个list

public:
    iterator begin(){return (link_type)((*node).next);}
    iterator end(){return node;}
    bool empty() const {
        return node->next == node;
    }
    size_type size() {
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
    }

    reference front(){return *begin();}
    reference back(){return *(--end());}
    //构造
    list(){empty_initialize();}//产生一个空链表

    //push
    void push_back(const T&x){
        insert(end(),x);
    }
    void push_front(const T&x){
        insert(begin(),x);
    }
    //在指定位置插入节点
    iterator insert(iterator position, const T&x){
        link_type tmp = create_node(x);//产生一个节点并传回
        tmp -> next = position.node;
        tmp -> prev = position.node->prev;
        (link_type(position.node->prev))->nrext = tmp;
        position.node->prev = tmp;
        return tmp;
    }
    //移除迭代器position所指节点
    iterator erase(iterator position){
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    //pop
    void pop_back(){
        iterator tmp = end();
        erase(--tmp);
    }
    void pop_front(){
        erase(begin());
    }
protected:
    
    //配置一个节点并传回
    link_type get_node(){return list_node_allocator::allocate();}
    //释放一个节点
    void put_node(link_type p){list_node_allocator::deallocate(p);}

    //产生一个带元素值的节点
    link_type create_node(const T& x){
        link_type p = get_node();
        construct(&p->data,x);
        return p;
    }

    //析构并释放一个节点
    void destroy_node(link_type p){
        destroy(&p->data);
        put_node(p);
    }

    //
    void empty_initialize(){
        node = get_node();//配置一个节点，使node指向它
        node->next = node;//令尾部节点指向自己
        node->prev = node;
    }
};






}








#endif