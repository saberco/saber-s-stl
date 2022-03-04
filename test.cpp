#include<new>
#include<iostream>
#include"my_vector.h"
using namespace saberstl;
using namespace std;

void test_vector(){
    int i;
    vector<int> iv(2,9);
    vector<int> arr;
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    iv.push_back(1);
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    iv.push_back(2);
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    iv.push_back(3);
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    iv.push_back(4);
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    for(i=0;i<iv.size();++i){
        cout<< iv[i]<<" ";
    }
    cout<<endl;
    iv.pop_back();
    iv.pop_back();
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
    for(i=0;i<iv.size();++i){
        cout<< iv[i]<<" ";
    }
    cout<<endl;
    iv.erase(iv.begin(),iv.end());
    cout<<"size = " << iv.size()<<endl;
    cout<<"capacity = " <<iv.capacity()<<endl;
}


int main(){
    test_vector();
    return 0;
}