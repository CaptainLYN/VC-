// nnZhongZhiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcPictureProcessing.h"
#include "nnZhongZhiDlg.h"
#include "afxdialogex.h"


// nnZhongZhiDlg dialog

IMPLEMENT_DYNAMIC(nnZhongZhiDlg, CDialogEx)

nnZhongZhiDlg::nnZhongZhiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(nnZhongZhiDlg::IDD, pParent)
	, size(0)
{
	ifok=false;
}

nnZhongZhiDlg::~nnZhongZhiDlg()
{
}

void nnZhongZhiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, size);
}


BEGIN_MESSAGE_MAP(nnZhongZhiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &nnZhongZhiDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// nnZhongZhiDlg message handlers
int nnZhongZhiDlg::GetSize()
{
	return size;
}

void nnZhongZhiDlg::OnBnClickedOk()//ȷ����ť
{
	UpdateData(true);
	UpdateData(false);
	if(size>=3&&size%2==1)
	{
	ifok=true;
	CDialogEx::OnOK();
	}
	else
	{
		MessageBox(_T("���ڴ�СҪΪ���ڵ���3��������"),_T("��ʾ"),MB_OK);
	}
}
