#include "StdAfx.h"
#include "XingTaiDib.h"
#include"CDib.h"
#include<WindowsX.h>
#include"FenGeCeLiangDib.h"

XingTaiDib::XingTaiDib(void)
{
}

XingTaiDib::~XingTaiDib(void)
{
}
void XingTaiDib::GetDib(CDib *d)
{
	dib=d;
}
void XingTaiDib::ShuiPingFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//���ڱ�����ͼ��
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=0;j<height;j++)
		for(int i=1;i<width-1;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//�Ƚ�����㸳ֵΪheise
			for(int n=0;n<3;n++)
				if(*(lpSrc+(n-1))==255)
				{
					*lpDst=255;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ChuiZhiFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//���ڱ�����ͼ��
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=1;j<height-1;j++)
		for(int i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//�Ƚ�����㸳ֵΪheise
			for(int n=0;n<3;n++)
				if(*(p_data+(n-1+j)*lbs+i)==255)
				{
					*lpDst=255;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::QuanFangXiangFuShi()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	int b[9]={1,0,1,0,0,0,1,0,1};//�ṹԪ������
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			*lpDst=0;//�ȸ�ֵΪ��ɫ
			for(int m=0;m<3;m++)
				for(int n=0;n<3;n++)
				{
					if(b[m+n]==1)
						continue;
					if(*(p_data+(m-1+j)*lbs+n-1+i)==255)
						{
							*lpDst=255;
							break;
						}
				}
		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ShuiPingPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//���ڱ�����ͼ��
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);

	for(int j=0;j<height;j++)
		for(int i=1;i<width-1;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=255;//�Ƚ�����㸳ֵΪheise
			for(int n=0;n<3;n++)
				if(*(lpSrc+(n-1))==0)
				{
					*lpDst=0;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::ChuiZhiPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];//���ڱ�����ͼ��
	LPBYTE lpSrc,lpDst;
	memset(temp,255,sizeof(BYTE)*lbs*height);
	
	for(int j=1;j<height-1;j++)
		for(int i=0;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=0;//�Ƚ�����㸳ֵΪheise
			for(int n=0;n<3;n++)
				if(*(p_data+(n-1+j)*lbs+i)==0)
				{
					*lpDst=0;
					break;
				}

		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::QuanFangXiangPengZhang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	int b[9]={1,0,1,0,0,0,1,0,1};//�ṹԪ������
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width;i++)
		{
			lpSrc=p_data+lbs*j+i;
			lpDst=temp+lbs*j+i;
			//*lpDst=0;//�ȸ�ֵΪ��ɫ
			for(int m=0;m<3;m++)
				for(int n=0;n<3;n++)
				{
					if(b[m+n]==1)
						continue;
					if(*(p_data+(m-1+j)*lbs+n-1+i)==0)
						{
							*lpDst=0;
							break;
						}
				}
		}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
		delete[]temp;
}
void XingTaiDib::BiYuanSuan()
{
	QuanFangXiangPengZhang();
	QuanFangXiangFuShi();
}
void XingTaiDib::KaiYunSuan()
{
	QuanFangXiangFuShi();
	QuanFangXiangPengZhang();
}
void XingTaiDib::XiHua()//Ч�������ϲ�̫һ��
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	bool fp=true;//ѭ��������־
	int i,j,m,n;
	unsigned char s[5][5],num;
	while(fp)
	{
		fp=false;
		memset(temp,255,sizeof(BYTE)*lbs*height);
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//�����lbs��С��д��width�ͻ���������鼮�����ഺ
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//���Ϊ��ɫ������
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//�����޸���
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//�ж�����1�Ƿ����
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//����һ������Ͳ���ͬʱ����4�������������õ�
				{
					*lpDst=0;
					continue;
				}
				//�ж�����2�Ƿ����
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//����2������
				}
				//�ж�����3�Ƿ����
				if(s[1][2]*s[2][1]*s[2][3]!=0)
				{
					num=0;
					if(s[0][2]==0&&s[0][1]==1)
						num++;
					if(s[0][1]==0&&s[1][1]==1)
						num++;
					if(s[1][1]==0&&s[2][1]==1)
						num++;
					if(s[2][1]==0&&s[2][2]==1)
						num++;
					if(s[2][2]==0&&s[2][3]==1)
						num++;
					if(s[2][3]==0&&s[1][3]==1)
						num++;
					if(s[1][3]==0&&s[0][3]==1)
						num++;
					if(s[0][3]==0&&s[0][2]==1)
						num++;
					if(num==1)
					{
						*lpDst=0;
						continue;
					}
				}
				/*else
				{
					*lpDst=0;
					continue;
				}*/
				//�ж�����4�Ƿ����
				if(s[1][2]*s[2][1]*s[3][2]/*=*/!=0)
				{
					num=0;
					if(s[1][1]==0&&s[1][0]==1)
						num++;
					if(s[1][0]==0&&s[2][0]==1)
						num++;
					if(s[2][0]==0&&s[3][0]==1)
						num++;
					if(s[3][0]==0&&s[3][1]==1)
						num++;
					if(s[3][1]==0&&s[3][2]==1)
						num++;
					if(s[3][2]==0&&s[2][2]==1)
						num++;
					if(s[2][2]==0&&s[1][2]==1)
						num++;
					if(s[1][2]==0&&s[1][1]==1)
						num++;
					if(num==1)
					{
						*lpDst=0;
						continue;
					}
				}
				/*else
				{
					*lpDst=0;
						continue;
				}*/
				//��������������ɾ���ĵ�
				//*lpDst=255;
				fp=true;
			}
			//����ϸ�����ͼƬ��һ�δ��ظ���ֱ��û�е����ɾ��Ϊֹ
			memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	}
	/*memcpy(p_data,temp,sizeof(BYTE)*lbs*height);*/
	delete[]temp;
}
void XingTaiDib::CuHua()
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(*(p_data+lbs*j+i)==0)
				*(p_data+lbs*j+i)=255;
			else
				*(p_data+lbs*j+i)=0;
		}
	XiHua();
}
void XingTaiDib::ZhongZhou()//Ч�������ϵĲ�һ������������һ���һֱѭ��������
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	//memset(temp,255,sizeof(BYTE)*lbs*height);
	LPBYTE lpSrc,lpDst;
	bool fp=true;//ѭ��������־
	int i,j,m,n;
	unsigned char s[5][5],num;
	while(fp)
	{
		fp=false;
		memset(temp,255,sizeof(BYTE)*lbs*height);
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//�����lbs��С��д��width�ͻ���������鼮�����ഺ
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//���Ϊ��ɫ������
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//�����޸���
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//�ж�����1-1�Ƿ����
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//����һ������Ͳ���ͬʱ����4�������������õ�
				{
					*lpDst=0;
					continue;
				}
				//�ж�����1-2�Ƿ����
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//����2������
				}
				//�ж�����1-3�Ƿ����
				if(s[1][2]*s[2][1]*s[3][2]!=0)
				{
						*lpDst=0;
						continue;
				}
				//�ж�����1-4�Ƿ����
				if(s[2][1]*s[2][3]*s[3][2]!=0)
				{
						*lpDst=0;
						continue;
				}
				//��������������ɾ���ĵ�
				//*lpDst=255;
			}
		memcpy(p_data,temp,sizeof(BYTE)*lbs*height);//��������ͻ�һֱѭ��������������������������������
			//�жϵڶ�������
		for(j=2;j<height-2;j++)
			for(i=2;i<width-2;i++)
			{
				lpSrc=p_data+lbs*j+i;//�����lbs��С��д��width�ͻ���������鼮�����ഺ
				lpDst=temp+lbs*j+i;
				if(*lpSrc==255)//���Ϊ��ɫ������
					continue;
				for(m=0;m<5;m++)
					for(n=0;n<5;n++)
					{
						if(*(lpSrc+(m-2)*lbs+n-2)==255)//�����޸���
							s[m][n]=0;
						else 
							s[m][n]=1;
					}
				//�ж�����2-1�Ƿ����
				num=s[1][1]+s[1][2]+s[1][3]+s[2][1]+s[2][3]+s[3][1]+s[3][2]+s[3][3];
				if(num<2||num>6)//����һ������Ͳ���ͬʱ����4�������������õ�
				{
					*lpDst=0;
					continue;
				}
				//�ж�����2-2�Ƿ����
				num=0;
				if(s[1][2]==0&&s[1][1]==1)
					num++;
				if(s[1][1]==0&&s[2][1]==1)
					num++;
				if(s[2][1]==0&&s[3][1]==1)
					num++;
				if(s[3][1]==0&&s[3][2]==1)
					num++;
				if(s[3][2]==0&&s[3][3]==1)
					num++;
				if(s[3][3]==0&&s[2][3]==1)
					num++;
				if(s[2][3]==0&&s[1][3]==1)
					num++;
				if(s[1][3]==0&&s[1][2]==1)
					num++;
				if(num!=1)
				{
					*lpDst=0;
					continue;//����2������
				}
			   //�ж�2-3�Ƿ����
				if(s[1][2]*s[2][1]*s[2][3]!=0)
				{
					*lpDst=0;
					continue;
				}
				//�ж�2-4�Ƿ����
				if(s[1][2]*s[2][3]*s[3][2]!=0)
				{
					*lpDst=0;
					continue;
				}
				//�����������Ͷ�ɾ��
				//*lpDst=255;
				fp=true;
			}
			//����ϸ�����ͼƬ��һ�δ��ظ���ֱ��û�е����ɾ��Ϊֹ
			memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	}
	/*memcpy(p_data,temp,sizeof(BYTE)*lbs*height);*/
	delete[]temp;
}