#ifndef COMPARER_H_H_H
#define COMPARER_H_H_H

//С�ڱȽ���
template <typename T>
struct  myLess
{
	constexpr bool operator()(const T&_left,const T&_right) {
		return (_left) < (_right);
}
};

//���ڱȽ���
template <typename T>
struct  myGreater
{
	constexpr bool operator()(const T&_left, const T&_right) {
		return (_left) > (_right);
	}
};
#endif // !COMPARER_H_H_H

