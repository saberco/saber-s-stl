# saber-s-stl
## STL六大组件
名称|功能
---|---：
容器（containers）|类似于一种class template，适用于各种数据结构，如vector,list,deque,set,map等
算法（algorithms）|各种常用算法sort,search,copy等，是一种function template
迭代器（iterators）|所谓“泛型指针”，是容器和算法的胶合剂
仿函数（funtors）|行为类似函数，可作为算法的某种策略
配接器（adapters）|用来修饰容器，仿函数，迭代器接口的东西
配置器（allocators）|负责空间配置和管理，实现了一个动态的空间配置
---
## 空间配置器
空间配置器是STL的基础，他可以向任何存在连续空间的对象申请存储空间。