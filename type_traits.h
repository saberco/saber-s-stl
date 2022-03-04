//type_traits.h
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H
 
struct __true_type {};
struct __false_type {};
 
template <typename type>
struct __type_traits {
	//不要移除
	typedef __true_type this_dummy_member_must_be_first;
 
	//trivial指无意义的
	typedef __false_type has_trivial_default_constructor;
	typedef __false_type has_trivial_copy_constructor;
	typedef __false_type has_trivial_assignment_constructor;
	typedef __false_type has_trivial_destructor;
	typedef __false_type is_POD_type;
	//POD指的是这样一些数据类型：基本数据类型、指针、union、数组、
	//构造函数是 trivial 的 struct 或者 class
};
 
//特化版本
template <>
struct __type_traits<char> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<signed char> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<unsigned char> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<short> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<unsigned short> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<int> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<unsigned int> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<long> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<unsigned long> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<float> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<double> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本
template <>
struct __type_traits<long double> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
//特化版本(原生指针)
template <class T>
struct __type_traits<T*> {
	typedef __true_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_constructor;
	typedef __true_type has_trivial_destructor;
	typedef __true_type is_POD_type;
};
 
#endif