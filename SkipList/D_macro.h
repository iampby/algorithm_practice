#ifndef D_MACRO_H_H
#define D_MACRO_H_H

#define SKL_OUTOFLINE inline


#define QLN QuaListNode* 
#define  RVarConst(_X,_XV) *const_cast<_X*>(&_XV) //��������ȥ��
#define Ey(_X,_XV) Entry<_X, _XV> 
#define QQLN_OUT_(_X,_XV) typename QuadList<Ey(_X, _XV)>::QuaListNode //�ⲿ����˵��
#define  QQLN_OUT(_X)  typename QuadList<_X>::QuaListNode //�ⲿ����˵��
#define  List_QEIt(_X,_XV) typename std::list <QuadList <Entry<_X,_XV> >*>::iterator //��������˵��
#define  CallList(_X,_XV)  std::list <QuadList <Entry<_X,_XV> >*> //����list����

#endif // !D_MACRO_H_H

