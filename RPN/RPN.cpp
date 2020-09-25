#include"RPN.h"
#include<iostream>
int constexpr OPERATOR_NUMBER=10;
//匿名空间隐藏类 类内定义枚举常量避免重复定义枚举而且保持常量性质
namespace {
	class Operator
	{
	public:
		Operator()=default;
		~Operator()=default;
		typedef  enum {
			Add, Sub, Mul, Div, Pow, Fac, L_Par, R_Par, EofC,Undefined
		};
	};
}
constexpr char optrPriority[OPERATOR_NUMBER][OPERATOR_NUMBER] = {
	'>','>','<','<','<','<','<','>','>',' ',//+
	'>','>','<','<','<','<','<','>','>',' ',//-
	'>','>','>','>','<','<','<','>','>',' ',//*
	'>','>','>','>','<','<','<','>','>',' ',///
	'>','>','>','>','>','<','<','>','>',' ',//^
	'>','>','>','>','>','>',' ','>','>',' ',//!
	'<','<','<','<','<','<','<','=',' ',' ',//(
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',//)
	'<','<','<','<','<','<','<',' ','=',' ',//\0
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',//undefined
};
const int optrRank(const char& op) { //由运算符转译出编号
	switch (op) {
	case '+': return Operator::Add; //加
	case '-': return Operator::Sub; //减
	case '*': return Operator::Mul; //乘
	case '/': return Operator::Div; //除
	case '^': return Operator::Pow; //乘方
	case '!': return Operator::Fac; //阶乘
	case '(': return Operator::L_Par; //左括号
	case ')': return Operator::R_Par; //右括号
	case '\0': return Operator::EofC; //起始符与终止符
	default: return Operator::Undefined; //未知运算符
	}
}
 char optrPriorityCompare(const char& optr1,const char& optr2) {
	return optrPriority[optrRank(optr1)][optrRank(optr2)];
}

void parseExpression(std::string& s, std::queue<std::string>&exp) {
	int length = s.size() - 1;
	std::string mid;
	for (int i = 0; i < length; i++)
	{
		std::string t;
		t.push_back(s.at(i));
		try {
			int v = stoi(t);
			mid.append(t);
		}
		catch (std::invalid_argument&e) {
			if (*t.c_str() == '.') {
				mid.append(t.c_str());
			}
			else {
				int b = optrRank(*t.c_str());
				if (-1==b) {
					std::cout << "expressions is error！" << std::endl;
					goto label;
				}
				if (!mid.empty()) {
					try {
						double v = stod(mid);
						exp.push(mid);
						mid.clear();
					}
					catch (...) {
						std::cout << "occured error!" << std::endl;
						goto label;
						}
				}
				exp.push(t);
			}
		}
		catch (std::out_of_range&e) {
			std::cout << e.what() << std::endl;
			goto label;
		}
		catch (...) {
			std::cout << "a unknow error!" << std::endl;
			goto label;
		}
	}
	{
		std::string t;
		t.push_back(s.at(length));
		try {
			int v = stoi(t);
			mid.append(t);
			try {
				exp.push(mid);
			}
			catch (...) {
				std::cout << "expressions is error！" << std::endl;
				goto label;
			}
		}
		catch (std::invalid_argument&e) {
			int b = optrRank(*t.c_str());
			if (-1==b) {
				std::cout << "expressions is error！" << std::endl;
				goto label;
			}
			try {
				double v = stod(mid);
				exp.push(mid);
				mid.clear();
			}
			catch (...) {
				std::cout << "occured error!" << std::endl;
				goto label;
			}
			exp.push(t);
		}
		catch (std::out_of_range&e) {
			std::cout << e.what() << std::endl;
			goto label;
		}
		catch (...) {
			std::cout << "a unknow error!" << std::endl;
			goto label;
		}
	}
	return;//返回
	//如果发生错误 清空表达式解析内容
label: {
	while (!exp.empty())
	{
		exp.pop();
	}
	return;
	}
}

bool isOperands(std::string&value,double&operands) {
try
	{
	operands = std::stod(value);//操作数
}
	catch (const std::exception&e)
	{
		return false;
	}
	catch (...) {
		return false;
	}
	return true;
}
//二元操作符
double calculate(double& optr1,char&op,double& optr2) {
	switch (op) {
	case '+': return optr1+optr2; //加
	case '-': return optr1-optr2; //减
	case '*': return optr1*optr2; //乘
	case '/': return optr1/optr2; //除
	case '^': return std::pow(optr1,optr2); //乘方
	}
}
//1元操作符
double calculate(char&op, double& optr) {
	switch (op) {
	case '!':{
		int opint = optr;
		if (opint == 0)return 1.0;
		double result = 1;
		for (int i = 1; i <= opint; ++i) {
			result *= i;
		}
		return result;
	}
	}
}
std::queue<std::string> evaluate(std::queue<std::string> &exp,double&result)
{
	std::queue<std::string>rpn;//逆波兰栈
	std::stack<double>operands; std::stack<std::string>optr;//运算数栈 操作符栈
	optr.push(std::string("\0"));
	while (!optr.empty())
	{
		std::string value;
		if (!exp.empty()) {
			 value = exp.front();//string不能直接引用声明,否则一旦容器删除，丢失内容  这和string的内存机制有关
			}
		else {//如果遍历完表达式 则取终止符来比较计算结果
			value.assign("\0");
		}
		double opnd;//操作数
		if (isOperands(value, opnd)) {
			operands.push(opnd); rpn.push(value);//如果数字就入栈同时添加到逆波兰表达式队列中
			exp.pop();
		}

		else {
			switch (optrPriorityCompare(*optr.top().c_str(),*value.c_str()))
			{
			case '<'://计算推迟，操作符入栈 表达式前进1
			{
				optr.push(value); 
				exp.pop();
}
			break;
			case '=':
			{
				optr.pop();//圆括号或者终止符时 脱括号  表达式前进1
				if(!exp.empty())//当为辅助计算终止符时不要删除
				exp.pop();
}
			break;
			case '>':
			{
				rpn.push(optr.top());//入栈操作符
				char op = *optr.top().c_str();
				optr.pop();
				if (op == '!') {//一元操作符处理
					double& optr1 = operands.top();
					operands.pop();
					operands.push(calculate(op,optr1));
				}
				else {//二元操作符处理
					double& optr2 = operands.top();
					operands.pop();
					double& optr1 = operands.top();
					operands.pop();
					if (op == '/'&&optr2 == 0.0) {//被除数不能为0
						std::cout << "dividend can't is zero "<<std::endl;
						goto label;
					}
					operands.push(calculate(optr1,op,optr2));//计算结果入栈
				}

			}
			break;
			default:
				goto label;//错误表达式

			}
		}
	}
	if (operands.empty()) {
		std::cout << "计算结果不存在！" << std::endl;
		}else
result = operands.top();//最终结果
	return rpn;
	//发送错误执行
label:	 {
	std::cout << "label：" <<std::endl;
	while (!rpn.empty())
	{
		rpn.pop();
		return rpn;
	}
	};
}
