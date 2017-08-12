#include"stdafx.h"
#include"CViewImage.h"
#include"CDib.h"
#include<WindowsX.h>
#include"ZhiFangDlg.h"
#include"HuiDuDib.h"

void HuiDuDib::Fei0()//Luna��ͼƬȫ�ǰ�ɫ
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();//��ʵ���Ѿ�д����ÿ���ֽڵĻ�ȡ������һֱû��
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;//���ϵ�д�ıȽ�����
			if(*t>0)
				*t=255;
		}
}
void HuiDuDib::GetDib(CDib *d)
{
	dib=d;
}
void HuiDuDib::GuDing(int YuZhi)
{
	LPBYTE p_data,p;
	p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			p=p_data+j*linebytes+i;
			if(*p<YuZhi)
				*p=0;
			else
				*p=255;
		}
}
void HuiDuDib::ShuangYu(int low,int high,int mode)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	switch(mode)
	{
	case 0://0-255-0
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<=low||*t>=high)
				*t=0;
			else
				*t=255;
		}
		break;
		case 1://255-0-255
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<=low||*t>=high)
				*t=255;
			else
				*t=0;
		}
		break;
	}
	
}
void HuiDuDib::FanSe()
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+linebytes*j+i;
			*t=255-*t;
		}
}
void HuiDuDib::ChuangKou(BYTE low,BYTE high)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*t<low)
				*t=0;
			else if(*t>high)
				*t=255;
		}
}
void HuiDuDib::ZheXian(BYTE X1,BYTE Y1,BYTE X2,BYTE Y2)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			t=p_data+linebytes*j+i;
			if(*t>0&&*t<=X1)
			{
				*t=*t*(Y1/X1);
			}
			else if(*t<X1&&*t<X2)
			{
				*t=Y1+(Y2-Y1)/(X2-X1)*(*t-X1);
			}
			else if(X2!=255)
			{
				*t=Y2+(255-Y2)/(255-X2)*(*t-X2);
			}
		}
}
float* HuiDuDib::ZhiFangTu(bool moshi)
{
	float *tongji=new float[256];//Ҫ�ǵ�����
	
	memset(tongji,0,sizeof(float)*256);
	BYTE* p_data=dib->GetData();
	BYTE *temp;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	int i,j;
	for(j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			temp=p_data+j*linebytes+i;
			tongji[*temp]++;
		}
	}
	if(moshi==true)
	{
	for(i=0;i<256;i++)
		tongji[i]=tongji[i]/(height*width);
	}
	return tongji;
}
void HuiDuDib::FenBuJunHengHua()
{
	int i,j;
	//�Ҷȷֲ��ܶ�
	float *fPs_R;
	//�м����
	float temp_r[256];//����S[]�ۼƺ���
	int nNs_R[256];//����L[]��r��Ӧ��������ֵ
	//��ʼ��
	memset(temp_r,0,sizeof(temp_r));
	LPBYTE p_data=dib->GetData();
	fPs_R=ZhiFangTu(true);//�����Ǹ��鴦��һ����
	//���о��⻯����
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp_r[0]=fPs_R[0];
		else
			temp_r[i]=temp_r[i-1]+fPs_R[i];
		nNs_R[i]=(int)(255.0f*temp_r[i]+0.5f);//+0.5fΪ�˼��پ��ȵ�ȱʧ��������������
	}
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	unsigned char temp;
	int linebytes=dib->GetDibWidthBytes();
	//�Ը����ؽ��лҶ�ת��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			temp=*((unsigned char*)p_data+linebytes*j+i);//8λ����
			*((unsigned char*)p_data+linebytes*j+i)=nNs_R[temp];
		}
	delete []fPs_R;
}
void HuiDuDib::PiPeiBianHuan(BYTE jishu,int* huidu,float *shuju)
{
	long i,j;
	int daiti[256];//��¼ÿ�����ر�����Ϊ��һ������
	float *gailv;//�Ҷȷֲ�����
	float temp[256];
	LPBYTE p_data=dib->GetData();
	long width=dib->GetWidth();
	long height=dib->GetHeight();
	gailv=ZhiFangTu(true);
	//����ԭʼ�ۼ�ֱ��ͼ
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp[0]=gailv[0];
		else
			temp[i]=temp[i-1]+gailv[i];
		gailv[i]=temp[i];
	}
	//����涨���ۻ�ֱ��ͼ
	for(i=0;i<256;i++)
	{
		if(i==0)
			temp[0]=shuju[0];
		else
			temp[i]=temp[i-1]+shuju[i];
		shuju[i]=temp[i];
	}
	for(i=0;i<256;i++)
	{
		//��ӽ��Ĺ涨ֱ��ͼ�Ҷȵȼ����ù涨��ֱ��ͼ�ȼ�������ʲ��ĵȼ�
		//��ԭ����ֱ��ͼ����״����ӽ��涨��ֱ��ͼ
		int m_r=0;
		//��С��ֵ
		float min_value_r=1;
		for(j=0;j<jishu;j++)
		{
			//��ǰ��ֵ
			float now_value=0;
			//�����ֵ
			if(gailv[i]-shuju[j]>=0)
				now_value=gailv[i]-shuju[j];
			else
				now_value=shuju[j]-gailv[i];
			//Ѱ����ӽ��Ĺ涨ֱ��ͼ�Ҷȼ�
			if(now_value<min_value_r)
			{
				m_r=j;
				min_value_r=now_value;
			}
		}
		//�����Ҷ�ӳ������ù涨ֱ��ͼ����һ��ֵ���浱ǰ�Ҷ�ֵ
		daiti[i]=huidu[m_r];
	}
	//�Ը����ؽ��д���
	int linebytes=dib->GetDibWidthBytes();
	unsigned char t;
	for(j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			t=*((unsigned char*)p_data+linebytes*j+i);
			*((unsigned char*)p_data+linebytes*j+i)=daiti[t];
		}
	}
}
int HuiDuDib::PingJunHuiDu()
{
	float* data=ZhiFangTu(true);
	float shu=0;
	for(int i=0;i<256;i++)
		shu+=data[i]*i;
	return (int)(shu+0.5);
}