#pragma once
#include "afx.h"
class CDib;
class HeChengDib :
	public CObject
{
private:
	CDib *dib;
public:
	HeChengDib(void);
	~HeChengDib(void);
	void GetDib(CDib *dib);
	void Add(LPBYTE p_dataBK);//ͼ�񱳾�;��ԭ���������ı���;����ͼ���С����һ��(��Ȼ��һ��Ҳ����)
	void Sub(LPBYTE p_dataBK);//�������������ʶ���������ض�������˶����
	void Yu(LPBYTE p_dataBK);//������
	void Huo(LPBYTE p_dataBK);//������
	void Fei();//������
	void HuoFei(LPBYTE p_dataBK);//������㣬�����ص�ͬʱΪ0��1��255����������0
	void YuFei(LPBYTE p_dataBK);//������㣬�����ص�ͬʱΪ1��0������Ϊ0
	void YiHuo(LPBYTE p_dataBK);//������㣬�����ص���ͬ��0��������1��255��
};

