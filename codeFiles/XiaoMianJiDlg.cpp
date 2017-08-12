// XiaoMianJiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "XiaoMianJiDlg.h"
#include "afxdialogex.h"



// XiaoMianJiDlg �Ի���

IMPLEMENT_DYNAMIC(XiaoMianJiDlg, CDialogEx)

XiaoMianJiDlg::XiaoMianJiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(XiaoMianJiDlg::IDD, pParent)
	, mianji(0)
{
	ifok=false;
}

XiaoMianJiDlg::~XiaoMianJiDlg()
{
}

void XiaoMianJiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mianji);
}


BEGIN_MESSAGE_MAP(XiaoMianJiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &XiaoMianJiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// XiaoMianJiDlg ��Ϣ�������

int XiaoMianJiDlg::GetMianJi()
{
	return mianji;
}
void XiaoMianJiDlg::OnBnClickedOk()
{
	ifok=true;
	UpdateData(true);
	UpdateData(false);
	CDialogEx::OnOK();
}
