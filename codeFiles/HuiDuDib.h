#pragma once
class HuiDuDib:public CObject
{
protected:
	CDib* dib;
public:
	void Fei0();
	void GetDib(CDib *d);
	void GuDing(int YuZhi);
	void ShuangYu(int low,int high,int mode);
	void FanSe();
	void ChuangKou(BYTE low,BYTE high);
	void ZheXian(BYTE X1,BYTE y1,BYTE X2,BYTE Y2);//�ŵ��Ǹ����û���Ҫ���������Ȥ������ϸ�ڣ�������Ʋ�����Ȥ�ĻҶȼ�
	float* ZhiFangTu(bool i);//���ԭ�飬�ı��˽ӿ�,Ϊtrue����С���ģ�Ϊfalse����������
	void FenBuJunHengHua();//�������ظ����ٵĻҶȼ���չ��Ҷȼ�������ģ��Ӷ��ﵽ����ͼ���Ŀ��
	void PiPeiBianHuan(BYTE jishu,int* huidu,float *shuju);//jishu��ʾҪƥ��ĻҶ�ͼ�ж��ټ���huidu�����μ�¼�˴�С����ÿһ���Ҷ�ֵ��shuju��¼��ÿһ���Ҷ�ֵ��gailv����ԭͼ��Ŀ��Ҷ�ֱ��ͼ���лҶ�ֱ��ͼ���⻯��Ȼ�����ԭͼ��ÿһ���Ҷȼ��ҵ���Ŀ��Ҷ�ͼ�еĻҶȸ���������ĻҶȣ����е�ӳ��任��Ȼ���ԭͼ���лҶ��滻
	int PingJunHuiDu();//����ͼ���ƽ���Ҷ�
};