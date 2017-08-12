#include"stdafx.h"
#include"JHBHDib.h"
#include"CDib.h"
#include<WindowsX.h>
#define _USE_MATH_DEFINES
#include<cmath>
JHBHDib::JHBHDib()
{}
JHBHDib::~JHBHDib()
{}
void JHBHDib::GetDib(CDib *cdib)
{
	dib=cdib;
}
void JHBHDib::PingYi(int m_Xmove,int m_Ymove)//ͼ��ƽ��
{
	LPBYTE lpSrc;//ָ��ԭͼ�����ص�ָ��
	LPBYTE p_data;//ָ��ԭͼ������

	LPBYTE lpDst;//ָ��Ҫ���ص�ָ��
	LPBYTE temp;//ָ����ͼ�����ݵ�ָ��
	LONG i;//ѭ������
	LONG wide,height;//ͼ��ĸߺͿ�
	LONG lLineBytes;//ͼ��ÿ�е��ֽ���
	p_data=dib->GetData();
	wide=dib->GetWidth();
	height=dib->GetHeight();
	lLineBytes=((wide*8)+31)/32*4;//����ͼ��ÿ�е��ֽ�����!!!!4�ֽڶ��룬���㲹��
	temp=new BYTE[lLineBytes*height];//��ʱ�����ڴ棬�Ա�����ͼ��
	lpDst=(LPBYTE)temp;
	memset(lpDst,(BYTE)0,lLineBytes*height);//��ʼ���·�����ڴ棬��ʼֵΪ255
	for(i=0;i<wide;i++)//һ����һ���еĸ���
	{
		for(int j=0;j<height;j++)
		{
			lpSrc=(LPBYTE)p_data+lLineBytes*(height-1-j)+i;//�����������ԭdib�е�����
			int i0,j0;
			i0=i+m_Xmove;//�������������dib�е�����
			j0=j+m_Ymove;
			if(i0>=0&&i0<wide&&j0>=0&&j0<height)//�ж��Ƿ�����ͼ��Χ��
			{
				lpDst=(LPBYTE)temp+lLineBytes*(height-1-j0)+i0;
				*lpDst=*lpSrc;//��������
			}
			else
			{
				//lpDst=(LPBYTE)temp+lLineBytes*(height-1+j)+i;
				//���������ȫ����
				//*((unsigned char*)lpDst)=255;//����ԭͼ��û�е�����ֱ�Ӹ�ֵΪ255
			}
		}
	}
	memcpy(p_data,temp,lLineBytes*height);//��ֵƽ�ƺ��ͼ�񣺽�tempָ������ݸ��Ƶ�p_data
	delete []temp;//�ͷ��ڴ�
}
void JHBHDib::JingXiang(bool fangshi)//����任��true��ˮƽ����false�Ǵ�ֱ����
{
	LPBYTE lpSrc;
	LPBYTE p_data;
	LPBYTE lpDst;
	LPBYTE temp;
	LONG i,j;
	long height=dib->GetHeight();
	long width=dib->GetWidth();
	p_data=dib->GetData();
	temp=new BYTE[width*height];
	if(fangshi)
	{
		for(j=0;j<height;j++)
		{
			for(i=0;i<width;i++)
			{
				lpSrc=(LPBYTE)p_data+width*j+i;
				lpDst=(LPBYTE)temp+width*(j+1)-i-1;//һ��Ҫ��һ
				*lpDst=*lpSrc;
			}
		}
	}
	else{
		for(i=0;i<width;i++)
			for(j=0;j<height;j++)
			{
				lpSrc=(LPBYTE)p_data+j*width+i;
				lpDst=(LPBYTE)temp+width*(height-j-1)+i;
				*lpDst=*lpSrc;
			}
	}
	memcpy(p_data,temp,width*height);
	delete []temp;
}

LPBYTE JHBHDib::FangDa(LPBYTE temp,int xzoom,int yzoom,long width,long height,int newwidth,int newheight)//ͼ��ķŴ��������xzoom��yzoom����Ϊ��������Ҫ�õ�Ҳ��int������ֱ�Ӹ�int
{
	LPBYTE p_data;//ָ��ԭͼ��
	p_data=dib->GetData();
	LPBYTE lpSrc;//ָ��ԭ����
	LPBYTE lpDst;
	long i,j,i0,j0;//,height,width;
	int srclinebyte=((width*8+31)/32)*4;
	int dstlinebyte=((newwidth*8+31)/32)*4;
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=(LPBYTE)p_data+srclinebyte*j+i;
			for(j0=0;j0<yzoom;j0++)
				for(i0=0;i0<xzoom;i0++)
				{
					lpDst=(LPBYTE)temp+dstlinebyte*(j*yzoom+j0)+i*xzoom+i0;
					//                          ����           �µ�����
					*lpDst=*lpSrc;
				}
		}
		return temp;
}

void JHBHDib::SuoXiao(float xzoom,float yzoom)
{
	long width,height,newwidth,newheight,i,j,i0,j0;
	LPBYTE p_data,temp,lpSrc,lpDst;
	
	temp=dib->GetData();
	p_data=temp;
	width=dib->GetWidth();
	height=dib->GetHeight();
	newwidth=(long)(width*xzoom+0.5);
	newheight=(long)(height*yzoom+0.5);
	int newlinebytes,linebytes;
		
	if(dib->GetInfo()->bmiHeader.biBitCount==8)//���ھ���ԻҶ�ͼ��������
	{
		linebytes=((width*8+31)/32)*4;
		newlinebytes=((newwidth*8+31)/32)*4;
	    temp=new BYTE[newlinebytes*newheight];
		for(j=0;j<newheight;j++)
			for(i=0;i<newwidth;i++)
			{
				lpDst=(LPBYTE)temp+newlinebytes*j+i;
				//����õ���ԭͼ�е�λ��
				j0=(LONG)(j/yzoom+0.5);
				i0=(LONG)(i/xzoom+0.5);
				if((i0>=0&&i0<width)&&(j0>=0&&j0<height))//��Ȼ��������жϣ����Ǹо��������ǲ����ܲ���ԭͼ��
				{
					lpSrc=(LPBYTE)p_data+j0*linebytes+i0;
					*lpDst=*lpSrc;
				}
				else
				{
					*lpDst=255;
				}
			}
			
			for(j=0;j<height;j++)
				for(i=0;i<width;i++)
				{
					if(j<newheight&&i<newwidth)
					{
					lpDst=(LPBYTE)temp+newlinebytes*j+i;
					*p_data=*lpDst;
					}
					else *p_data=0;
					p_data++;
				}
				delete[]temp;
		//����Ĵ���ʽ�ͷŴ��ǲ�һ����
				
	}
}
LPBYTE JHBHDib::ZhuanZhi()
{
	long width=dib->GetWidth();
	long height=dib->GetHeight();
	int linebytes=((width*8+31)/32)*4;
	int newlinebytes=(height*8+31)/32*4;
	int i,j;
	LPBYTE lpSrc,lpDst,temp,p_data;
	temp=new BYTE[newlinebytes*width];
	memset(temp,(BYTE)0,newlinebytes*width);
	p_data=dib->GetData();
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			lpSrc=(LPBYTE)p_data+linebytes*j+i;
			lpDst=(LPBYTE)temp+newlinebytes*i+j;
			*lpDst=*lpSrc;
		}
		//����������Щ����Ϊ��ͼ��ת�ú����������ֽڶ��룬���Դ�С���ܻ������ԣ�dib���������ٵ�ʱ���С���ԣ�����ִ���
		dib->GetInfo()->bmiHeader.biHeight=width;
		dib->GetInfo()->bmiHeader.biWidth=height;
		dib->GetInfo()->bmiHeader.biSizeImage=newlinebytes*width;
		//memcpy(p_data,temp,height*width);//��������дlinebytes*newlinebytes,����4�ֽڶ������ݲ�ȫ����ֱ�Ե��ɫ
		//delete(temp);
		return temp;
}
double JHBHDib::RADIAN(double RotateAngle)
{
	return RotateAngle*M_PI/180;//Ҫ���������Ǹ�define����
}

LPBYTE JHBHDib::XuanZhuan(double RotateAngle)//ԭ�����ˣ��Ժ󲻶��Ļ���pdf��ľͿ�����
{
	DWORD DstBufSize;
	LPBYTE lpTempPtr,lpPtr,lpSrc,lpTemp;
	double SrcX1,SrcY1,SrcX2,SrcY2,SrcX3,SrcY3,SrcX4,SrcY4;
	double DstX1,DstY1,DstX2,DstY2,DstX3,DstY3,DstX4,DstY4;
	DWORD Wold,Hold,Wnew,Hnew;
	DWORD x0,y0,x1,y1;
	double cosa,sina;//cos(a),sin(a)
	double num1,num2;
	
	//�Ƕȵ����ȵı仯
	RotateAngle=(double)RADIAN(RotateAngle);
	cosa=(double)cos((double)RotateAngle);
	sina=(double)sin((double)RotateAngle);

	//CString s;
	//s.Format(_T("%lf"),RotateAngle);//��RotateAngleת��Ϊ�ַ���
	//MessageBox(NULL,s,_T("��ʾ"),MB_OK);//�������ԶԲ���

	lpSrc=dib->GetData();
	Wold=dib->GetWidth();
	Hold=dib->GetHeight();
	//ԭͼ��4���ǵ�����
	SrcX1=(double)(-0.5*Wold);
	SrcY1=(double)(0.5*Hold);
	SrcX2=(double)(0.5*Wold);
	SrcY2=(double)(0.5*Hold);
	SrcX3=(double)(-0.5*Wold);
	SrcY3=(double)(-0.5*Hold);
	SrcX4=(double)(0.5*Wold);
	SrcY4=(double)(-0.5*Hold);
	//��ͼ���ĸ�������
	DstX1=cosa*SrcX1+sina*SrcY1;
	DstY1=-sina*SrcX1+cosa*SrcY1;
	DstX2=cosa*SrcX2+sina*SrcY2;
	DstY2=-sina*SrcX2+cosa*SrcY2;
	DstX3=cosa*SrcX3+sina*SrcY3;
	DstY3=-sina*SrcX3+cosa*SrcY3;
	DstX4=cosa*SrcX4+sina*SrcY4;
	DstY4=-sina*SrcX4+cosa*SrcY4;
	//��ͼ�Ŀ�Ⱥ͸߶�
	Wnew=(DWORD)(max(fabs(DstX4-DstX1),fabs(DstX3-DstX2))+0.5);
	Hnew=(DWORD)(max(fabs(DstY4-DstY1),fabs(DstY3-DstY2))+0.5);
	//��������е�������������������ÿ�ζ���
	num1=(double)(-0.5*Wnew*cosa-0.5*Hnew*sina+0.5*Wold);
	num2=(double)(0.5*Wnew*sina-0.5*Hnew*cosa+0.5*Hold);
	
	//������ѡ��linebytes�����ϲ���
	int newlinebytes=((Wnew*8+31)/32)*4;
	int linebytes=((Wold*8+31)/32)*4;

	DstBufSize=newlinebytes*Hnew;
	//DstBufSize=Wnew*Hnew;
	//ԭ��������ǰ�ɫ����Ȼ����ΪҪ���ɫ������Ϊ����ʾЧ��������������ѡ���ɫ
	//���ڻ���������ʱ��������linebytes����ʱ�����Ǽ򵥵ĸߺͿ�ĳ˻�����
	lpTempPtr=new BYTE[DstBufSize];
	memset(lpTempPtr,(BYTE)255,DstBufSize);
	lpTemp=lpTempPtr;//����ס�����
	for(y1=0;y1<Hnew;y1++)
	{
		for(x1=0;x1<Wnew;x1++)
		{
			//x0,y0�Ǹõ���ԭͼ�ϵ�����
			x0=(DWORD)(x1*cosa+y1*sina+num1);
			y0=(DWORD)(-1.0f*x1*sina+y1*cosa+num2);
			if(x0>=0&&x0<Wold&&y0>=0&&y0<Hold)//��ԭͼ��Χ��
			{
				lpPtr=lpSrc+y0*linebytes+x0;
				//lpPtr=lpSrc+y0*Wold+x0;//��ԭ�������ǲ��Ե�
				lpTempPtr=lpTemp+y1*newlinebytes+x1;
				//lpTempPtr=lpTemp+y1*Wnew+x1;
				*lpTempPtr=*lpPtr;
				
				//lpTempPtr=lpTemp;

			}
		}
	}
	dib->GetInfo()->bmiHeader.biHeight=Hnew;
	dib->GetInfo()->bmiHeader.biWidth=Wnew;
	dib->GetInfo()->bmiHeader.biSizeImage=newlinebytes*Hnew;

	return lpTemp;
}