#pragma once
class CDib;
class JHBHDib:public CObject
{
protected:
	CDib *dib;
public:
	void GetDib(CDib* cdib);
	JHBHDib();
	~JHBHDib();
	void PingYi(int m_Xmove,int m_Ymove);
	void JingXiang(bool fangshi);

	//�ڴ�һ��Ҫ�����������룬�������������ջ���
	LPBYTE FangDa(LPBYTE temp,int xzoom,int yzoom,long width,long height,int newwidth,int newheight);//����ݵķŴ���,���ｵ��һ��Ҫ����int
	void SuoXiao(float xzoom,float yzoom);
	LPBYTE ZhuanZhi();
	LPBYTE XuanZhuan(double RotateAngle);
	double RADIAN(double RotateAngle);

};