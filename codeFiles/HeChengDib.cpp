#include "StdAfx.h"
#include "HeChengDib.h"
#include<WindowsX.h>
#include"CDib.h"

HeChengDib::HeChengDib(void)
{
}
HeChengDib::~HeChengDib(void)
{
}
void HeChengDib::GetDib(CDib *d)
{
	dib=d;
}
void HeChengDib::Add(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE lpSrc,lpDst,lpSrcBK;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[lbs*height];//��ͼ�񻺳���
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			lpSrcBK=p_dataBK+lbs*j+i;
			//���м�����
			if((*lpSrc+*lpSrcBK)>255)
				*lpDst=255;
			else
				*lpDst=(*lpSrc+*lpSrcBK);
		}
		memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
		delete[]temp;
}
void HeChengDib::Sub(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE lpSrc,lpDst,lpSrcBK;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[lbs*height];//��ͼ�񻺳���
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			lpSrcBK=p_dataBK+lbs*j+i;
			//���м�����
			if((*lpSrc-*lpSrcBK)<0)
				*lpDst=0;
			else
				*lpDst=(*lpSrc-*lpSrcBK);
		}
		memcpy(p_data,temp,sizeof(BYTE)*height*lbs);
		delete[]temp;
}
void HeChengDib::Yu(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp1=new BYTE[lbs*height];
	LPBYTE temp2=new BYTE[lbs*height];
	//��ԭͼ���ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	//�Ա������ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_dataBK[lbs*j+i]>128)
				temp2[lbs*j+i]=255;
			else
				temp2[lbs*j+i]=0;
		}
	//����ÿ�����ص�������
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(temp2[lbs*j+i]==255&&temp1[lbs*j+i]==255)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	memcpy(p_data,temp1,sizeof(BYTE)*lbs*height);
	delete[]temp1;
	delete[]temp2;
}
void HeChengDib::Huo(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp1=new BYTE[lbs*height];
	LPBYTE temp2=new BYTE[lbs*height];
	//��ԭͼ���ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	//�Ա������ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_dataBK[lbs*j+i]>128)
				temp2[lbs*j+i]=255;
			else
				temp2[lbs*j+i]=0;
		}
	//����ÿ�����ص�������
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(temp2[lbs*j+i]==0&&temp1[lbs*j+i]==0)
				temp1[lbs*j+i]=0;
			else
				temp1[lbs*j+i]=255;
		}
	memcpy(p_data,temp1,sizeof(BYTE)*lbs*height);
	delete[]temp1;
	delete[]temp2;
}
void HeChengDib::Fei()
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	//��ԭͼ���ж�ֵ��ȡ������ԭ�醪�µĲ��������˼���
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				p_data[lbs*j+i]=0; 
			else
				p_data[lbs*j+i]=255;
		}
}
void HeChengDib::HuoFei(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp1=new BYTE[lbs*height];
	LPBYTE temp2=new BYTE[lbs*height];
	//��ԭͼ���ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	//�Ա������ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_dataBK[lbs*j+i]>128)
				temp2[lbs*j+i]=255;
			else
				temp2[lbs*j+i]=0;
		}
	//����ÿ�����ص�������
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(temp2[lbs*j+i]==0&&temp1[lbs*j+i]==0)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	memcpy(p_data,temp1,sizeof(BYTE)*lbs*height);
	delete[]temp1;
	delete[]temp2;
}
void HeChengDib::YuFei(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp1=new BYTE[lbs*height];
	LPBYTE temp2=new BYTE[lbs*height];
	//��ԭͼ���ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	//�Ա������ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_dataBK[lbs*j+i]>128)
				temp2[lbs*j+i]=255;
			else
				temp2[lbs*j+i]=0;
		}
	//����ÿ�����ص�������
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(temp2[lbs*j+i]==255&&temp1[lbs*j+i]==255)
				temp1[lbs*j+i]=0;
			else
				temp1[lbs*j+i]=255;
		}
	memcpy(p_data,temp1,sizeof(BYTE)*lbs*height);
	delete[]temp1;
	delete[]temp2;
}
void HeChengDib::YiHuo(LPBYTE p_dataBK)
{
	int i,j;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp1=new BYTE[lbs*height];
	LPBYTE temp2=new BYTE[lbs*height];
	//��ԭͼ���ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>128)
				temp1[lbs*j+i]=255;
			else
				temp1[lbs*j+i]=0;
		}
	//�Ա������ж�ֵ��
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(p_dataBK[lbs*j+i]>128)
				temp2[lbs*j+i]=255;
			else
				temp2[lbs*j+i]=0;
		}
	//����ÿ�����ص�������
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			if(temp2[lbs*j+i]==temp1[lbs*j+i])
				temp1[lbs*j+i]=0;
			else
				temp1[lbs*j+i]=255;
		}
	memcpy(p_data,temp1,sizeof(BYTE)*lbs*height);
	delete[]temp1;
	delete[]temp2;
}
