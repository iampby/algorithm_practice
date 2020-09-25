#include"RPN.h"
#include<iostream>
int constexpr OPERATOR_NUMBER=10;
//�����ռ������� ���ڶ���ö�ٳ��������ظ�����ö�ٶ��ұ��ֳ�������
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
const int optrRank(const char& op) { //�������ת������
	switch (op) {
	case '+': return Operator::Add; //��
	case '-': return Operator::Sub; //��
	case '*': return Operator::Mul; //��
	case '/': return Operator::Div; //��
	case '^': return Operator::Pow; //�˷�
	case '!': return Operator::Fac; //�׳�
	case '(': return Operator::L_Par; //������
	case ')': return Operator::R_Par; //������
	case '\0': return Operator::EofC; //��ʼ������ֹ��
	default: return Operator::Undefined; //δ֪�����
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
					std::cout << "expressions is error��" << std::endl;
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
				std::cout << "expressions is error��" << std::endl;
				goto label;
			}
		}
		catch (std::invalid_argument&e) {
			int b = optrRank(*t.c_str());
			if (-1==b) {
				std::cout << "expressions is error��" << std::endl;
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
	return;//����
	//����������� ��ձ��ʽ��������
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
	operands = std::stod(value);//������
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
//��Ԫ������
double calculate(double& optr1,char&op,double& optr2) {
	switch (op) {
	case '+': return optr1+optr2; //��
	case '-': return optr1-optr2; //��
	case '*': return optr1*optr2; //��
	case '/': return optr1/optr2; //��
	case '^': return std::pow(optr1,optr2); //�˷�
	}
}
//1Ԫ������
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
	std::queue<std::string>rpn;//�沨��ջ
	std::stack<double>operands; std::stack<std::string>optr;//������ջ ������ջ
	optr.push(std::string("\0"));
	while (!optr.empty())
	{
		std::string value;
		if (!exp.empty()) {
			 value = exp.front();//string����ֱ����������,����һ������ɾ������ʧ����  ���string���ڴ�����й�
			}
		else {//�����������ʽ ��ȡ��ֹ�����Ƚϼ�����
			value.assign("\0");
		}
		double opnd;//������
		if (isOperands(value, opnd)) {
			operands.push(opnd); rpn.push(value);//������־���ջͬʱ��ӵ��沨�����ʽ������
			exp.pop();
		}

		else {
			switch (optrPriorityCompare(*optr.top().c_str(),*value.c_str()))
			{
			case '<'://�����Ƴ٣���������ջ ���ʽǰ��1
			{
				optr.push(value); 
				exp.pop();
}
			break;
			case '=':
			{
				optr.pop();//Բ���Ż�����ֹ��ʱ ������  ���ʽǰ��1
				if(!exp.empty())//��Ϊ����������ֹ��ʱ��Ҫɾ��
				exp.pop();
}
			break;
			case '>':
			{
				rpn.push(optr.top());//��ջ������
				char op = *optr.top().c_str();
				optr.pop();
				if (op == '!') {//һԪ����������
					double& optr1 = operands.top();
					operands.pop();
					operands.push(calculate(op,optr1));
				}
				else {//��Ԫ����������
					double& optr2 = operands.top();
					operands.pop();
					double& optr1 = operands.top();
					operands.pop();
					if (op == '/'&&optr2 == 0.0) {//����������Ϊ0
						std::cout << "dividend can't is zero "<<std::endl;
						goto label;
					}
					operands.push(calculate(optr1,op,optr2));//��������ջ
				}

			}
			break;
			default:
				goto label;//������ʽ

			}
		}
	}
	if (operands.empty()) {
		std::cout << "�����������ڣ�" << std::endl;
		}else
result = operands.top();//���ս��
	return rpn;
	//���ʹ���ִ��
label:	 {
	std::cout << "label��" <<std::endl;
	while (!rpn.empty())
	{
		rpn.pop();
		return rpn;
	}
	};
}
