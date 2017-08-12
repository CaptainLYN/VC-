#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>
#include"FenGeCeLiangDib.h"
#include"HuiDuDib.h"
#include"HuiDuDib.h"
#include<string>
#include"CViewImage.h"
void FenGeCeLiangDib::GetDib(CDib *d)
{
	dib=d;
}
void FenGeCeLiangDib::YuZhiFenGe(int yuzhi)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]>=yuzhi/*abs(p_data[lbs*j+i]-yuzhi)>30*/)
				p_data[lbs*j+i]=255;//ԭ�鸳ֵ�Ǵ���ģ������޸���
			else
				p_data[lbs*j+i]=0;
		}
}
void FenGeCeLiangDib::BanYuZhi(int yuzhi)
{
	int height=dib->GetHeight();
	int width=dib->GetWidth();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			if(p_data[lbs*j+i]<yuzhi)
				p_data[lbs*j+i]=255;//ԭ�鸳ֵ�Ǵ���ģ������޸���
		}
}
void FenGeCeLiangDib::DieDaiYuZhi()
{
	HuiDuDib hui;
	hui.GetDib(dib);
	int j1=hui.PingJunHuiDu();
	float *data=hui.ZhiFangTu(true);
	float t0,t1,t2,t3,j2;
	t0=t1=t2=t3=0;
	while(true)
	{
		for(int i=0;i<j1+1;i++)
		{
			t0+=data[i]*i;//�ܵ��������ԻҶ�
			t1+=data[i];//�ܵ�����
		}
		for(int i=j1+1;i<256;i++)
		{
			t2+=data[i]*i;
			t3+=data[i];
		}
		j2=(t0/t1+t2/t3)/2;
		if(j2==j1)
			break;//�����ֵ���ٷ����仯
		else
			j1=j2;
	}
	//�ҳ������ؾ�ֵ�ͽ��б任
	YuZhiFenGe(j1);
	delete[]data;
}
void FenGeCeLiangDib::LunKuoTiQu()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int a[8];
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	DieDaiYuZhi();
	memset(temp,255,sizeof(byte)*lbs*height);
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			if(p_data[lbs*j+i]==0)
			{
				a[0]=p_data[lbs*(j-1)+i-1];
				a[1]=p_data[lbs*(j-1)+i];
				a[2]=p_data[lbs*(j-1)+i+1];
				a[3]=p_data[lbs*j+i-1];
				a[4]=p_data[lbs*j+i+1];
				a[5]=p_data[lbs*(j+1)+i-1];
				a[6]=p_data[lbs*(j+1)+i];
				a[7]=p_data[lbs*(j+1)+i+1];
				if(a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7]==0)
					temp[lbs*j+i]=255;
				else
					temp[lbs*j+i]=0;
			}
		}
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
}
bool FenGeCeLiangDib::BiHeGenZong()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int i,j;
	bool fs;//�Ƿ��ҵ���ʼ��
	bool fp;//�Ƿ��ҵ���һ���ڵ�
	int cishu=0;
	CPoint sp,cp;//��ʼ��͵�ǰ������
	LPBYTE p_data=dib->GetData();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(byte)*lbs*height);
	int go[8][2]={{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};//�����Ͻǿ�ʼ��˳ʱ��8������
	int sd;//��¼��go�����еķ���
	//��������ֵ��
	DieDaiYuZhi();
	fs=false;
	for(j=0;j<height&&!fs;j++)
		for(i=0;i<width&&!fs;i++)
		{
			if(p_data[lbs*j+i]==0)
			{
				fs=true;//�ҵ��˳�ʼ�ڵ�
				sp.y=j;
				sp.x=i;//��¼��ʼ���λ��
				temp[lbs*j+i]=0;
			}
		}
		//���ڳ�ʼ�������·�������ɨ�������Ϸ���
		sd=0;//���ٱ߽�
		fs=false;
		//�ӳ�ʼ�㿪ʼɨ��
		cp.y=sp.y;
		cp.x=sp.x;
		LPBYTE lpSrc,lpDst;
		while(!fs&&cishu<0x7fffffff)
		{
			cishu++;
			fp=false;
			while(!fp)
			{
				//��ɨ�跽��鿴һ������
				lpSrc=p_data+lbs*(cp.y+go[sd][1])+cp.x+go[sd][0];
				if(*(lpSrc)==0)
				{
					fp=true;//�ҵ�����һ���ڵ�
					cp.y=cp.y+go[sd][1];
					cp.x=cp.x+go[sd][0];
					if(cp.y==sp.y&&cp.x==sp.x)
						fs=true;//�ҵ��˳�ʼ��
					lpDst=temp+lbs*cp.y+cp.x;
					*(lpDst)=0;//д�Ϻڵ�
					//�ҵ��˾���һ�η�����ʱ����ת����
					sd--;
					if(sd==-1)
						sd=7;
					sd--;
					if(sd==-1)
						sd=7;
				}
				else//�����һ�εķ���û�У���˳ʱ����תһ��
				{
					sd++;
					if(sd==8)
						sd=0;
				}
			}
		}
		if(cishu==0x7fffffff)
		{
			MessageBox(NULL,_T("ѭ����0x7fffffff��û�н�����ж�ͼ��û�бպ�Բ"),_T("��ʾ"),MB_OK);
			return false;
		}
		else {
		memcpy(p_data,temp,lbs*height);
		delete[]temp;
		return true;
		}
}
void FenGeCeLiangDib::QuYuZengZhang(CPoint pt)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	int i,j,t;
	LPBYTE p_data=dib->GetData();
	int zhongzi=p_data[pt.y*lbs+pt.x];
	for(j=0;j<height;j++)
		for(i=0;i<width;i++)
		{
			t=p_data[j*lbs+i];
			if(abs(t-zhongzi)>10)//��׼����Ϊ10
			{
				p_data[lbs*j+i]=255;//����һ���������������ɰ�ɫ
			}
		}
}
int FenGeCeLiangDib::ErZhiBiaoJi(LPBYTE temp,int flag[])
{
	//��������ֵ��
	DieDaiYuZhi();
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	/*temp=new BYTE[lbs*height];*///��¼ÿ����ı��
	/*memset(temp,0,sizeof(BYTE)*lbs*height);*/
	BYTE x_temp,y_temp;
	int x_sign=0;
	//memset(flag,0,255*sizeof(int));//ÿ����ǵ�������0���ã�����Ĭ�ϲ�����255��ͼ��
	for(int j=1;j<height-1;j++)
		for(int i=1;i<width-1;i++)
		{
			if(p_data[j*lbs+i]==0)//�����ǰ���Ǻڵ�Ļ�
			{
				if(p_data[(j-1)*lbs+i+1]==0)//������ϵ��Ǻڵ�Ļ�
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i+1];//����ǰ����ֵ����Ϊ�����Ͻ���һ����
					x_temp=temp[j*lbs+i];
					flag[x_temp]+=1;
					if(p_data[j*lbs+i-1]==0&&temp[j*lbs+i-1]!=x_temp)//�����ǰ���Ǻڵ㣬���Ǳ�ǵ�ֵ�͵�ǰ�㲻һ����
					{
						y_temp=temp[j*lbs+i-1];
						for(int m=1;m<height-1;m++)//���������������������
							for(int n=1;n<width-1;n++)
							{
								if(temp[m*lbs+n]==y_temp)
								{
									flag[y_temp]=0;
									flag[x_temp]+=1;
									temp[m*lbs+n]=x_temp;//�޸�ֵ
								}
							}
					}
					if(p_data[(j-1)*lbs+i-1]==0&&temp[(j-1)*lbs+i-1]!=x_temp)//������ϵ��Ǻڵ㣬���Ǹ���ǰ��¼ֵ��һ��
					{
						y_temp=temp[(j-1)*lbs+i-1];
						for(int m=1;m<height;m++)
							for(int n=1;n<width;n++)
							{
								if(temp[m*lbs+n]==y_temp)
								{
									flag[y_temp]=0;
									flag[x_temp]+=1;
									temp[m*lbs+n]=x_temp;//�޸�ֵ
								}
							}
					}
				}
				else if(p_data[(j-1)*lbs+i]==0)//������Ϸ�����0�������Ϸ���0
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else if(p_data[(j-1)*lbs+i-1]==0)//������Ϸ���0
				{
					temp[j*lbs+i]=temp[(j-1)*lbs+i-1];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else if(p_data[j*lbs+i-1]==0)//�����ǰ����0
				{
					temp[j*lbs+i]=temp[j*lbs+i-1];
					y_temp=temp[j*lbs+i];
					flag[y_temp]+=1;
				}
				else
				{
					++x_sign;//��Ǻż�1
					temp[j*lbs+i]=x_sign;
					flag[x_sign]=1;
				}
			}
		}
		//�����˺þ�����֪���ˣ�x_sign��ܴ󣬶��ֳ�����ͼ���ԶС���������Ϊ���м���Щ���ݺ����ݸ��ˣ����Ǽ�ʹ�Ǹ����������ˣ�x_sign���ǻ��������
		/*BYTE t[256*256];
		memcpy(t,temp,256*256);*/
		return x_sign;//��new�����鷵�أ��ǵ�ɾ���ڴ�
}
void  FenGeCeLiangDib::ErZhiZhouChang()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE p_data=dib->GetData();
	int flag[256]={0};
	LPBYTE p_temp=new BYTE[lbs*height];
	memset(p_temp,255,sizeof(BYTE)*lbs*height);
	int x_sign=ErZhiBiaoJi(p_temp,flag);//���ñ�Ƿ������������
	LPBYTE lpSrc,lpDst;
	CPoint sp,cp;//��ʼ�߽��͵�ǰ�߽��
	int dc[8][2]={{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};//8����ʼɨ�跽�򣬴����·���ʼ˳ʱ����ת����������д����
	int bd;//��ʼ�ķ����
	LPBYTE temp=new BYTE[lbs*height];//���ڱ�����ͼ��
	memset(temp,255,sizeof(BYTE)*lbs*height);//��ͼ���ɫ�ǰ�ɫ�����������Ϊ�ڵ�
	bool fsp,fp;//�ҵ���ʼ�㣻�ҵ���һ����
	/*CViewImage ima;
	ima.GetDib(dib);
	ima.OnDraw3(pDC,p_temp,dib->GetWidth(),0);*/
	for(int t=1;t<=x_sign;t++)
	{
		if(flag[t]!=0)//�м�������ͻ��м�������
		{
			fsp=false;
			for(int j=0;j<height&&!fsp;j++)//ɨ��ͼƬ���ҵ���һ���ڵ�
				for(int i=0;i<width&&!fsp;i++)
				{
					lpSrc=p_temp+lbs*j+i;
					if(*lpSrc==t)
					{
						fsp=true;//�ҵ��˳�ʼ��
						sp.y=j;
						sp.x=i;
						temp[lbs*j+i]=t;//����ͼ���аѵ�һ�������
					}
				}
				bd=0;//��ʼ�������·���
				fsp=false;//��ʼʱ��û���ҵ�һ����
				cp.y=sp.y;
				cp.x=sp.x;
				while(!fsp)
				{
					fp=false;
					while(!fp)
					{
						//��ɨ�跽��鿴һ������
						lpSrc=p_temp+lbs*(cp.y+dc[bd][1])+cp.x+dc[bd][0];
						if(*lpSrc==t)//����ҵ���һ���ͳ�ʼ��һ���ĵ�
						{
							fp=true;
							cp.y=cp.y+dc[bd][1];
							cp.x=cp.x+dc[bd][0];//�޸ĵ�ǰ���ֵΪ�·��ֵ�ֵ
							if(cp.x==sp.x&&cp.y==sp.y)
								fsp=true;//�ҵ��˳�ʼ��
							lpDst=temp+lbs*cp.y+cp.x;
							*lpDst=t;//����ͼ�н��ҵ��ĵ��ǳ���
							//�ҵ���һ�������ʱ����ת90�ȣ����ַ���
							bd--;
							if(bd==-1)
								bd=7;
							bd--;
							if(bd==-1)
								bd=7;
						}
						else//���û���ҵ�
						{
							//ɨ��˳ʱ����ת45��
							bd++;
							if(bd==8)
								bd=0;
						}
					}
				}
		}
	}
	
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);//�����ֻ�б�Ե��ͼ�񿽸���ԭͼָ��
	
	//ͳ�Ʊߵĳ���
	int data;
	int fm[256]={0};//��¼�ܳ�
	for(int j=0;j<height;j++)
		for(int i=0;i<width;i++)
		{
			data=p_data[lbs*j+i];
			if(data!=0)
			{
				fm[data]+=1;//�����˳�ʱ��ջ�𻵣�����Խ�磡data��ֵ��0~255����256����һ��ʼfm��fn����255������fm[data]�л�Խ�磡
			}
		}
	//����һ�������¼������ܳ�
	int fn[256]={0};
	int line=0;
	int zhou=0;//�ܳ�
	/*memset(fn,0,256*sizeof(int));*/
	for(int i=1;i<=x_sign;i++)
	{
		if(fm[i]!=0)
		{
			if(fn[line]==0)
			{
				fn[line]=fm[i];
				++line;
			}
			zhou+=fm[i];
		}
	}
	//����ֻ�����һ���ܳ���������ÿ��������ܳ�����û����ʾ���Ժ���Ҫ���Ե���
	CString s;//CString ��MFC����
	s.Format(_T("��ͨ��������%5d,�ܳ�:%10d"),line,zhou);
	MessageBox(NULL,s,_T("�ܳ�"),MB_OK);
	delete[] p_temp;
	delete[]temp;
	//���˺ܳ�ʱ�����˷��������������⣬�����˳�ʱ��fm��ջ��Ҳ�Ѿ������
}
void  FenGeCeLiangDib::XiaoChuXiaoQuYu(int m_value)
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	int lbs=dib->GetDibWidthBytes();
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	int flag[256]={0};
	int x_sign=ErZhiBiaoJi(temp,flag);
	LPBYTE p_data=dib->GetData();
	for(int i=1;i<=x_sign;i++)
	{
		if(flag[i]<m_value)
		{
			for(int m=1;m<height-1;m++)
				for(int n=1;n<width-1;n++)
				{
					if(temp[lbs*m+n]==i)
						temp[lbs*m+n]=255;
				}
		}
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void  FenGeCeLiangDib::ShuiPingTouYing()//���бȽ�������֪��Ϊʲô��Ӧ�����е�����ֵ��
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	DieDaiYuZhi();//�Ƚ��ж�ֵ��
	int num;
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(int j=0;j<height;j++)
	{
		num=0;
		for(int i=0;i<width;i++)
			if(p_data[lbs*j+i]==0)
				num++;
		for(int i=0;i<num;i++)
			temp[lbs*j+i]=0;
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}
void FenGeCeLiangDib::ChuiZhiTouYing()
{
	int width=dib->GetWidth();
	int height=dib->GetHeight();
	LPBYTE p_data=dib->GetData();
	int lbs=dib->GetDibWidthBytes();
	DieDaiYuZhi();//�Ƚ��ж�ֵ��
	int num;
	LPBYTE temp=new BYTE[lbs*height];
	memset(temp,255,sizeof(BYTE)*lbs*height);
	for(int i=0;i<width;i++)
	{
		num=0;
		for(int j=0;j<height;j++)
			if(p_data[lbs*j+i]==0)
				num++;
		for(int j=0;j<num;j++)
			temp[lbs*j+i]=0;//ͼ��Ĵ洢������������棬��������������д����ʾ��ʱ�������ʾ�����棬�����Ǵ�ֱͶӰ
	}
	memcpy(p_data,temp,sizeof(BYTE)*lbs*height);
	delete[]temp;
}