#ifndef COMPARER_H_H_H
#define COMPARER_H_H_H

//小于比较器
template <typename T>
struct  myLess
{
	constexpr bool operator()(const T&_left,const T&_right) {
		return (_left) < (_right);
}
};

//大于比较器
template <typename T>
struct  myGreater
{
	constexpr bool operator()(const T&_left, const T&_right) {
		return (_left) > (_right);
	}
};
#endif // !COMPARER_H_H_H

