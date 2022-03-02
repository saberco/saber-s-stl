#include<new>
#include<iostream>

template<int inst>
class _Mytest
{
    private:
        static void *  _test(size_t n);
};
template<int inst>
void * _Mytest<inst>::_test(size_t n){
     std::cout << "test" << std::endl;
     void * res = 0;
     return res;
 }








int main(){

    std::cout<< "hello world" << std::endl;

    return 0;
}