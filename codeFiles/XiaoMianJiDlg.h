#pragma once


// XiaoMianJiDlg �Ի���

class XiaoMianJiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(XiaoMianJiDlg)

public:
	XiaoMianJiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XiaoMianJiDlg();
	bool ifok;

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	int mianji;
public:
	afx_msg void OnBnClickedOk();
	int GetMianJi();
};
