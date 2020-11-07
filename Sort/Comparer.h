#ifndef ALGORITHM_SORT_COMPARER_H_H
#define ALGORITHM_SORT_COMPARER_H_H


/*
小于比较器
*/
template<typename T>
struct MyLess
{
	bool operator()(const T &_left, const T &_right) {
		return (_left < _right);
	}
};

/*
大于比较器
*/
template<typename T>
struct MyGreater
{
	bool operator()(const T &_left, const T &_right) {
		return (_left> _right);
	}
};

/*
等于比较器
*/
template<typename T>
struct MyEqual
{
	bool operator()(const T &_left, const T &_right) {
		return (_left== _right);
	}
};

#endif // !ALGORITHM_SORT_COMPARER_H_H

