#include"stdafx.h"
#include<WindowsX.h>
#include"CDib.h"
#include"PingHuaDib.h"//Ҫ���·�

void PingHuaDib::GetDib(CDib *sdib)
{
	dib=sdib;
}

void PingHuaDib::ErZhiHua(int yuzhi)
{
	LPBYTE p_data=dib->GetData();
	LPBYTE t;
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	int i,j;
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			t=p_data+j*linebytes+i;
			if(*(t)>=yuzhi)
				*(t)=255;
			else
				*(t)=0;
		}

}

void PingHuaDib::HeiBaiZaoSheng()
{
	int averg;//��Χͼ���ƽ��ֵ
	BYTE* p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	/*ErZhiHua(100);*///�����������������ʾ
	BYTE* p_temp=new BYTE[linebytes*height];
	memcpy(p_temp,p_data,linebytes*height);
	//3x3�����˲�
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			averg=0;
			//����Χ8���ھ�ֵ
			averg=(int)((*(p_data+(j-1)*linebytes+i-1)+*(p_data+(j-1)*linebytes+i)+*(p_data+(j-1)*linebytes+i+1)+*(p_data+j*linebytes+i-1)+*(p_data+j*linebytes+i+1)+*(p_data+j*linebytes+i+1)+*(p_data+(j+1)*linebytes+i-1)+*(p_data+(j+1)*linebytes+i)+*(p_data+(j+1)*linebytes+i+1))/8);
			if(abs(averg-*(p_temp+j*linebytes+i))>127)
				*(p_temp+j*linebytes+i)=averg;
		}
		memcpy(p_data,p_temp,linebytes*height);
		delete []p_temp;
}
void PingHuaDib::GuLiHei(int connect)//Ϊ4��8����Ӧ4���Ӻ�8����
{
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	/*LPBYTE temp=new BYTE[linebytes*height];*/
	//memcpy(temp,p_data,linebytes*height);//�����ڵ�Ҫô�����������������Ҫô�෴
	switch(connect)
	{
	case 4:
		for(int j=1;j<height-1;j++)
			for(int i=1;i<width-1;i++)
			{
				if(p_data[linebytes*j+i]==255)
					continue;
				else
				{
					if(p_data[linebytes*(j-1)+i]+p_data[linebytes*j+i-1]+p_data[linebytes*j+i+1]+p_data[linebytes*(j+1)+i]==255*4)
						p_data[linebytes*j+i]=255;
				}
			}
		break;
	case 8:
		for(int j=1;j<height-1;j++)
			for(int i=1;i<width-1;i++)
			{
				if(p_data[linebytes*j+i]==255)
					continue;
				else
				{
					if(p_data[linebytes*(j-1)+i-1]+p_data[linebytes*(j-1)+i+1]+p_data[linebytes*(j+1)+i-1]+p_data[linebytes*(j+1)+i+1]+p_data[linebytes*(j-1)+i]+p_data[linebytes*j+i-1]+p_data[linebytes*j+i+1]+p_data[linebytes*(j+1)+i]==255*8)
						p_data[linebytes*j+i]=255;
				}
			}
		break;
	}
}
void PingHuaDib::ThreeThree()
{
	int avrg;
	LPBYTE p_data=dib->GetData();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[linebytes*height];
	memcpy(temp,p_data,linebytes*height);
	int i,j;
	for(j=1;j<height-1;j++)
		for(i=1;i<width-1;i++)
		{
			avrg=(p_data[linebytes*(j-1)+i-1]+p_data[linebytes*(j-1)+i+1]+p_data[linebytes*(j+1)+i-1]+p_data[linebytes*(j+1)+i+1]+p_data[linebytes*(j-1)+i]+p_data[linebytes*j+i-1]+p_data[linebytes*j+i+1]+p_data[linebytes*(j+1)+i])/8;
			temp[linebytes*j+i]=avrg;//�������Ľ��о�ֵ��ֵ���϶���ģ����
		}
		memcpy(p_data,temp,linebytes*height);
		delete []temp;
}
void PingHuaDib::ChaoXian(int yuzhi)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	LPBYTE p_data=dib->GetData();
	int linebytes=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[linebytes*height];
	memcpy(temp,p_data,linebytes*height);
	int avrg;
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			avrg=(p_data[linebytes*(j-1)+i-1]+p_data[linebytes*(j-1)+i+1]+p_data[linebytes*(j+1)+i-1]+p_data[linebytes*(j+1)+i+1]+p_data[linebytes*(j-1)+i]+p_data[linebytes*j+i-1]+p_data[linebytes*j+i+1]+p_data[linebytes*(j+1)+i])/8;
			if(abs(p_data[linebytes*j+i]-avrg)>yuzhi)
				temp[linebytes*j+i]=avrg;
		}
		memcpy(p_data,temp,linebytes*height);
		delete []temp;
}
void PingHuaDib::JuBuPingJun()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int linebytes=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[linebytes*height];
	memcpy(temp,p_data,linebytes*height);
	float mean[9];
	float fangcha[9];
	int shuzhi[9];
	int i,j,n;
	//����5x5�Ĵ���
	for(j=2;j<height-2;j++)
		for(i=2;i<width-2;i++)
		{
			//9x9,��Ҫ�����Լ�
			shuzhi[0]=p_data[linebytes*(j-1)+i-1];
			shuzhi[1]=p_data[linebytes*(j-1)+i];
			shuzhi[2]=p_data[linebytes*(j-1)+i+1];
			shuzhi[3]=p_data[linebytes*j+i-1];
			shuzhi[4]=p_data[linebytes*j+i];
			shuzhi[5]=p_data[linebytes*j+i+1];
			shuzhi[6]=p_data[linebytes*(j+1)+i-1];
			shuzhi[7]=p_data[linebytes*(j+1)+i];
			shuzhi[8]=p_data[linebytes*(j+1)+i+1];
			mean[0]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6]+shuzhi[7]+shuzhi[8])*1.0/9;
			fangcha[0]=0;
			for(n=0;n<9;n++)
				fangcha[0]+=shuzhi[n]*shuzhi[n]-mean[0]*mean[0];
			//��7�ڽ�
			shuzhi[0]=p_data[linebytes*(j-1)+i-2];
			shuzhi[1]=p_data[linebytes*(j-1)+i-1];
			shuzhi[2]=p_data[linebytes*j+i-2];
			shuzhi[3]=p_data[linebytes*j+i-1];
			shuzhi[4]=p_data[linebytes*(j+1)+i-2];
			shuzhi[5]=p_data[linebytes*(j+1)+i-1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[1]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[1]=0;
			for(n=0;n<7;n++)
				fangcha[1]+=shuzhi[n]*shuzhi[n]-mean[1]*mean[1];
			//��7�ٽ�
			shuzhi[0]=p_data[linebytes*(j-2)+i-1];
			shuzhi[1]=p_data[linebytes*(j-2)+i];
			shuzhi[2]=p_data[linebytes*(j-2)+i+1];
			shuzhi[3]=p_data[linebytes*(j-1)+i-1];
			shuzhi[4]=p_data[linebytes*(j-1)+i];
			shuzhi[5]=p_data[linebytes*(j-1)+i+1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[2]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[2]=0;
			for(n=0;n<7;n++)
				fangcha[2]+=shuzhi[n]*shuzhi[n]-mean[2]*mean[2];
			//��7�ٽ�
			shuzhi[0]=p_data[linebytes*(j-1)+i+1];
			shuzhi[1]=p_data[linebytes*(j-1)+i+2];
			shuzhi[2]=p_data[linebytes*j+i+1];
			shuzhi[3]=p_data[linebytes*j+i+2];
			shuzhi[4]=p_data[linebytes*(j+1)+i+1];
			shuzhi[5]=p_data[linebytes*(j+1)+i+2];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[3]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[3]=0;
			for(n=0;n<7;n++)
				fangcha[3]+=shuzhi[n]*shuzhi[n]-mean[3]*mean[3];
			//��7�ٽ�
			shuzhi[0]=p_data[linebytes*(j+1)+i-1];
			shuzhi[1]=p_data[linebytes*(j+1)+i];
			shuzhi[2]=p_data[linebytes*(j+1)+i+1];
			shuzhi[3]=p_data[linebytes*(j+2)+i-1];
			shuzhi[4]=p_data[linebytes*(j+2)+i];
			shuzhi[5]=p_data[linebytes*(j+2)+i+1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[4]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[4]=0;
			for(n=0;n<7;n++)
				fangcha[4]+=shuzhi[n]*shuzhi[n]-mean[4]*mean[4];
			//����7�ٽ�
			shuzhi[0]=p_data[linebytes*(j-1)+i-2];
			shuzhi[1]=p_data[linebytes*(j-1)+i-1];
			shuzhi[2]=p_data[linebytes*j+i-2];
			shuzhi[3]=p_data[linebytes*j+i-1];
			shuzhi[4]=p_data[linebytes*(j+2)+i-1];
			shuzhi[5]=p_data[linebytes*(j+2)+i];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[5]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[5]=0;
			for(n=0;n<7;n++)
				fangcha[5]+=shuzhi[n]*shuzhi[n]-mean[5]*mean[5];
			//����7�ٽ�
			shuzhi[0]=p_data[linebytes*(j+2)+i+1];
			shuzhi[1]=p_data[linebytes*(j+2)+i+2];
			shuzhi[2]=p_data[linebytes*(j+1)+i];
			shuzhi[3]=p_data[linebytes*(j+1)+i+1];
			shuzhi[4]=p_data[linebytes*(j+1)+i+2];
			shuzhi[5]=p_data[linebytes*j+i+1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[6]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[6]=0;
			for(n=0;n<7;n++)
				fangcha[6]+=shuzhi[n]*shuzhi[n]-mean[6]*mean[6];
			//����7�ٽ�
			shuzhi[0]=p_data[linebytes*(j+2)+i+1];
			shuzhi[1]=p_data[linebytes*(j+2)+i+2];
			shuzhi[2]=p_data[linebytes*(j+1)+i];
			shuzhi[3]=p_data[linebytes*(j+1)+i+1];
			shuzhi[4]=p_data[linebytes*(j+1)+i+2];
			shuzhi[5]=p_data[linebytes*j+i+1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[7]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[7]=0;
			for(n=0;n<7;n++)
				fangcha[7]+=shuzhi[n]*shuzhi[n]-mean[7]*mean[7];
			//����7�ٽ�
			shuzhi[0]=p_data[linebytes*(j+2)+i-2];
			shuzhi[1]=p_data[linebytes*(j+2)+i-1];
			shuzhi[2]=p_data[linebytes*(j+1)+i-2];
			shuzhi[3]=p_data[linebytes*(j+1)+i-1];
			shuzhi[4]=p_data[linebytes*(j+1)+i];
			shuzhi[5]=p_data[linebytes*j+i-1];
			shuzhi[6]=p_data[linebytes*j+i];
			mean[8]=(shuzhi[0]+shuzhi[1]+shuzhi[2]+shuzhi[3]+shuzhi[4]+shuzhi[5]+shuzhi[6])*1.0/7;
			fangcha[8]=0;
			for(n=0;n<7;n++)
				fangcha[8]+=shuzhi[n]*shuzhi[n]-mean[8]*mean[8];
			//�󷽲���С�ģ������Լ��仯����ҵ�
			float min=fangcha[0];
			int num=0;
			for(n=1;n<9;n++)
			{
				if(min>fangcha[n])
				{
					min=fangcha[n];
					num=n;
				}
			}
			temp[j*linebytes+i]=(int)(mean[num]+0.5);
		}
		memcpy(p_data,temp,linebytes*height);
		delete []temp;
}
void PingHuaDib::nnZhongZhi(int n)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	int medium;//��ֵλ��
	BYTE t;//��ʱ����
	LPBYTE windows=new BYTE[100];//�洢�����ڵ����ݣ���������
	memcpy(temp,p_data,lbs*height);
	int n1=(n-1)/2;//�м�ֵ
	for(int j=n1;j<height-n1;j++)
		for(int i=n1;i<width-n1;i++)
		{
			int m=0;
			int k,h;
			for(k=j-n1;k<=j+n1;k++)
				for(h=i-n1;h<=i+n1;h++)
				{
					windows[m]=p_data[lbs*k+h];
					m++;
				}
				//ԭ����ð�ݣ�����Ϊ��ѡ��������ã�������n+1��/2
				int cishi=0;
				int l;
				
				while(cishi<((n+1)/2))
				{
					l=windows[cishi];
					h=cishi;
					for(k=cishi+1;k<m;k++)
					{
						if(l>windows[k])
						{
							l=windows[k];//��¼��ֵ
							h=k;//��¼λ��
						}
					}
					//����
					if(cishi!=h)
					{
						t=windows[cishi];
						windows[cishi]=l;
						windows[h]=t;
					}
					cishi++;
				}
				medium=windows[cishi-1];//ȡ����ֵ
				temp[lbs*j+i]=medium;
		}
		memcpy(p_data,temp,lbs*height);
		delete []temp;//Ҫ����[]���������ղ�����
		delete[]windows;
}
void PingHuaDib::shizi(int n)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	int medium;//��ֵλ��
	BYTE t;//��ʱ����
	LPBYTE windows=new BYTE[100];//�洢�����ڵ����ݣ���������
	memcpy(temp,p_data,lbs*height);
	int n1=(n-1)/2;//�м�ֵ
	for(int j=n1;j<height-n1;j++)
		for(int i=n1;i<width-n1;i++)
		{
			int m=0;
			int k,h;
			//��ֱ����
			for(k=j-n1;k<=j+n1;k++)
			{
				windows[m]=p_data[k*lbs+i];
				m++;
			}
			for(k=i-n1;k<=i+n1;k++)
			{
				windows[m]=p_data[j*lbs+k];
				m++;
			}
			//ԭ����ð�ݣ�����Ϊ��ѡ��������ã�������n+1��/2
				int cishi=0;
				int l;
				
				while(cishi<((n+1)/2))
				{
					l=windows[cishi];
					h=cishi;
					for(k=cishi+1;k<m;k++)
					{
						if(l>windows[k])
						{
							l=windows[k];//��¼��ֵ
							h=k;//��¼λ��
						}
					}
					//����
					if(cishi!=h)
					{
						t=windows[cishi];
						windows[cishi]=l;
						windows[h]=t;
					}
					cishi++;
				}
				medium=windows[cishi-1];//ȡ����ֵ
				temp[lbs*j+i]=medium;
		}
		memcpy(p_data,temp,lbs*height);
		delete []temp;//Ҫ����[]���������ղ�����
		delete[]windows;
}
void PingHuaDib::nnZuiDa(int n)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	int medium;//��ֵλ��
	BYTE t;//��ʱ����
	//LPBYTE windows=new BYTE[100];//�洢�����ڵ����ݣ���������
	memcpy(temp,p_data,lbs*height);
	int n1=(n-1)/2;//�м�ֵ
	for(int j=n1;j<height-n1;j++)
		for(int i=n1;i<width-n1;i++)
		{
			int m=0,max=-1;
			int k,h;
			for(k=j-n1;k<=j+n1;k++)
				for(h=i-n1;h<=i+n1;h++)
				{
					if(p_data[lbs*k+h]>max)
						max=p_data[lbs*k+h];//��ԭ�鲻ͬ����������ֱ������󼴿�
				}
				temp[lbs*j+i]=max;
		}
		memcpy(p_data,temp,lbs*height);
		delete []temp;//Ҫ����[]���������ղ�����
}
void PingHuaDib::SuiJiZaoSheng()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	srand(time(NULL));//�Ե�ǰʱ��Ϊ���ӣ�time(NULL)�ǵ�ǰʱ��
	float noise;
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			noise=rand()*1.0/1024;
			temp[lbs*j+i]=p_data[lbs*j+i]*(224*1.0/256)+noise;
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
void PingHuaDib::JiaoYanZaoSheng()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	srand(time(NULL));//�Ե�ǰʱ��Ϊ���ӣ�time(NULL)�ǵ�ǰʱ��
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(rand()>31500)
				p_data[lbs*j+i]=255;
		}
}