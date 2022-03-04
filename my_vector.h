#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__

#include"myallocator.h"
#include<memory>
#include<algorithm>
#include"construct.h"

namespace saberstl{

template<class T, class Alloc=alloc>
class vector{
public:
    //型别定义
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;


protected:
    typedef simple_alloc<value_type, Alloc> data_alloctor;
    iterator start; //目标使用空间的头
    iterator finish;//目前使用空间的尾
    iterator end_of_storage;//目前可用空间的尾
    //vector的初始化（构造和析构）
    void insert_aux(iterator position, const T& x);
    void deallocate(){
        if(start){
            data_alloctor::deallocate(start, end_of_storage-start);
        }
    }
    void fill_initialize(size_type n, const T& value){
        start = allocate_and_fill(n,value);
        finish = start + n;
        end_of_storage = finish;
    }
public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size() {return size_type((end()-begin()));}
    size_type capacity() {
        return size_type(end_of_storage-begin());
    }
    bool empty() const {return begin()==end();}
    //重载中括号
    reference operator [](size_type n) {
        return *(begin()+n);
    }
    //构造函数
    vector() : start(0), finish(0), end_of_storage(0){}
    vector(size_type n, const T& value) {fill_initialize(n, value);}
    vector(int n, const T& value) {fill_initialize(n, value);}
    vector(long n, const T& value) {fill_initialize(n, value);}
    //防止隐式转换
    explicit vector(size_type n) {fill_initialize(n, T());}

    //析构函数
    ~vector(){
        destroy(start, finish);
        deallocate();   //vector的成员函数
    }

    reference front(){return *begin();}//第一个元素
    reference back(){return *(end()-1);}//末尾元素
    void push_back(const T& x){//在vector尾部插入元素
        if(finish != end_of_storage){
            construct(finish, x);
            ++finish;
        }
        else {
            insert_aux(end(), x);
        }
    }

    void pop_back(){//取出末尾元素
        --finish;
        destroy(finish);
    }

    iterator erase(iterator position){
        if(position +1 !=end){
            std::copy(position+1, finish, position);
        }
        --finish;
        destroy(finish);
        return position;
    }
    iterator erase(iterator first, iterator last){
        iterator i = std::copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last-first);
        return first;
    }

    // void resize(size_type new_size,const T& x){
    //     if(new_size<size())
    //         erase(begin(),end());
    //     else
    //         insert(end(),new_size-size(),x);
    // }
    // void resize(size_type new_size){resize(new_size,T);}
    void clear(){erase(begin(),end());}
protected:
    iterator allocate_and_fill(size_type n,const T& x){
        iterator result = data_alloctor::allocate(n);
        std::uninitialized_fill_n(result,n,x);
        return result;
    }
};


template<class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T & x){
    if(finish != end_of_storage){   //还有备用空间
    //在备用空间构造一个元素，并以最后一个元素作为初值
        construct(finish, *(finish-1));
        ++finish;
        T x_copy = x;
        std::copy_backward(position, finish - 2, finish - 1);
        *position = x_copy;
    }
    else{//无备用空间
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2*old_size : 1;
        //等于0配置为1，不等于0配置为2倍
        iterator new_start = data_alloctor::allocate(len); //实际配置
        iterator new_finish = new_start;
        try{//将原本vector的内容拷贝到新vector
            new_finish = std::uninitialized_copy(start, position, new_start);
            //为新元素设定初值
            construct(new_finish,x);
            //调整尾部
            ++new_finish;
            //拷贝备用空间（不确定是不是真的没了）
            new_finish = std::uninitialized_copy(position, finish,new_finish);
        }
        catch(...){
            //捕获到异常
            destroy(new_start, new_finish);
            data_alloctor::deallocate(new_start,len);
            throw;
        }
        //析构并释放原vector
        destroy(begin(), end());
        deallocate();

        //调整迭代器指向新vector
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start+len;
    }
}




}






#endif