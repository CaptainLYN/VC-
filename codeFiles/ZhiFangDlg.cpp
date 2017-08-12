// ZhiFangDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "ZhiFangDlg.h"
#include "afxdialogex.h"


// ZhiFangDlg dialog

IMPLEMENT_DYNAMIC(ZhiFangDlg, CDialogEx)

ZhiFangDlg::ZhiFangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZhiFangDlg::IDD, pParent)
{
	data=NULL;
}

ZhiFangDlg::~ZhiFangDlg()
{
}

void ZhiFangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZhiFangDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ZhiFangDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ZhiFangDlg message handlers
void ZhiFangDlg::SetData(float *d)
{
	data=d;
}
void ZhiFangDlg::OnPaint()
{
	//
	//CPaintDC dc(this);//�������������
	CDC *dc=GetDC();
	CPen* pPen=new CPen;//��������
	pPen->CreatePen(PS_SOLID,1,RGB(0,0,0));//����һ֧�ڱ�
	CGdiObject *pOldPen=dc->SelectObject(pPen);//ѡ���»��ʣ�����ɻ���
	int i=0;
	CString str;
	CPoint OPos(14,188),NowPos;//��������ϵ
	//����X������
	dc->MoveTo(OPos);
	NowPos.x=284;
	NowPos.y=188;
	dc->LineTo(NowPos);
	//���Ƽ�ͷ
	dc->LineTo(279,183);
	dc->MoveTo(NowPos);
	dc->LineTo(279,193);
	//����x������ϵ��
	//���浥����������Ϊ�˺ÿ�
	i=0;
	dc->MoveTo(OPos.x+i,OPos.y);
	dc->LineTo(CPoint(OPos.x+i,OPos.y+5));
	str.Format(_T("%d"),i);
	dc->TextOutW(OPos.x+i-5,OPos.y+7,str);
	for(i=10;i<256;i+=10)//�������޸�
	{
		if(i%10==0)//��������
		{
			dc->MoveTo(OPos.x+i,OPos.y);
			dc->LineTo(CPoint(OPos.x+i,OPos.y+5));
		}
		if(i%40==0)//������
		{
			str.Format(_T("%d"),i);
			dc->TextOutW(OPos.x+i-10,OPos.y+7,str);
		}
	}
	//����y������ϵ��
	dc->MoveTo(OPos);
	NowPos.x=OPos.x;
	NowPos.y=4;
	dc->LineTo(NowPos);
	//���Ƽ�ͷ
	dc->LineTo(NowPos.x-5,NowPos.y+5);//�������ͣ��������Ƶ����ľ�������
	dc->MoveTo(NowPos);
	dc->LineTo(NowPos.x+5,NowPos.y+5);
	//Ѱ��������������
	float max=0;
	for(i=0;i<256;i++)
	{
		if(max<data[i])
			max=data[i];
	}
	//y������ϵ�������ݲ���
	//float Tstep=max/10;
	//y������ϵ���Ŀ̶Ȳ���
	float Ystep=174/20;
	//��ʾy����Ŀ̶Ⱥ�����
	i=20;
	dc->MoveTo(OPos.x,OPos.y-Ystep*i);
	dc->LineTo(OPos.x+5,OPos.y-Ystep*i);
	str.Format(_T("%f"),max);//�����޸���
	dc->TextOutW(20,OPos.y-Ystep*i-20,str);	
	
	//���ƻҶ�ֱ��ͼ
	for(i=0;i<256;i++)
	{
		NowPos.x=OPos.x+i;
		NowPos.y=OPos.y;
		dc->MoveTo(NowPos);
		NowPos.y=187-20*Ystep*data[i]/max;//�����������20*Ystep��������175����Ϊ�м侫��ȱʧ��̫��
		dc->LineTo(NowPos);
	}
	dc->SelectObject(pOldPen);

	delete pPen;
	//Invalidate();
}

void ZhiFangDlg::OnBnClickedButton1()
{
	if(data!=NULL)
		OnPaint();
}
