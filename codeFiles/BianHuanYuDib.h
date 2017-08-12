#pragma once
#include "afx.h"
#include<complex>

class CDib;

class BianHuanYuDib :
	public CObject
{
private:
	CDib *dib;
public:
	BianHuanYuDib(void);
	~BianHuanYuDib(void);
	void GetDib(CDib *dib);
	void QFC(std::complex<double>  *t,std::complex<double> *f,int r);//��ȫ���������ٸ���Ҷ�任,t��f�ֱ���ָ��ʱ���Ƶ���ָ�룬r��2������
	void FirstQuickFourier();//ͼ��ĸ���Ҷ�任��û�жԴ�������ʾ�������ƽ�ƣ������ε��ÿ��ٸ���Ҷ�任QFC()ʵ�ֶ�ά����Ҷ�任
	void LiSan(double *t,double *f,int r);//ʵ�ֿ�����ɢ���ұ任���ú�������2N��Ŀ��ٸ���Ҷ�任
	void DIBLiSanYuXian();//�ı���ԭ�������Ĳ�����������LiSan��������ʵ��ͼ�����ɢ�������ұ任
	void PerfectFilterL(int u,int v);//�����ͨ�˲�����u��v�ֱ��ǽ�ֹƵ�ʵ�x��y����ֵ�����û�����
	void TLFilter(int u,int v,int vl);//���ε�ͨ�˲�����u��v�ֱ��ǽ�ֹƵ�ʵ�x��y����ֵ�����û�ָ��
};