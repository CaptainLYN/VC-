
// MfcPictureProcessingDlg.h : ͷ�ļ�
//

#pragma once

class CDib;
class CViewImage;
// CMfcPictureProcessingDlg �Ի���
class CMfcPictureProcessingDlg : public CDialogEx
{
	
	CMenu m_Menu;
	CString filePath;
	CPoint pt;
#pragma region �����涼��ϵͳ�Լ����ɵģ���û��
// ����
public:
	CMfcPictureProcessingDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_MFCPICTUREPROCESSING_DIALOG };
	
	

protected:
virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
#pragma endregion
public:
	void GetFilePath(CString file); 

	afx_msg void On32771();//����ǲ˵����Ĵ��ļ���ť�ĺ���
	afx_msg void On32772();//����ɨ��
	afx_msg void On32773();//����ɨ��
	afx_msg void On32774();//����ɨ��
	afx_msg void On32775();//����ɨ��
	afx_msg void On32776();//ˮƽ����
	afx_msg void On32777();//��ֱ����
	afx_msg void On32778();//�������
	afx_msg void On32779();//�м�����
	afx_msg void On32780();//����
	afx_msg void On32781();//�м�����
	afx_msg void On32782();//ˮƽդ��
	afx_msg void On32783();//��ֱդ��
	afx_msg void On32784();//ͼ����
	afx_msg void On32785();//ˮƽ��Ҷ��
	afx_msg void On32786();//��ֱ��Ҷ��
	afx_msg void On32787();//��������ʾ
	afx_msg void OnUpdate32780(CCmdUI *pCmdUI);//��յ���Ϣ������û������
	afx_msg void On32789();//ͼ��ƽ��
	afx_msg void On32790();//ˮƽ����
	afx_msg void On32791();//��ֱ����
	afx_msg void On32792();//�������
	afx_msg void On32793();//ͼ��Ŵ�
	
	afx_msg void OnBnClickedButton1();//�˳���ť
	afx_msg void On32794();//ͼ����С
	afx_msg void On32795();//ͼ��ת��
	afx_msg void On32796();//ͼ����ת
	afx_msg void On32797();//�Ҷȷ���ȡһ
	afx_msg void On32798();//�Ҷȹ̶���ֵ
	afx_msg void On32799();//�����ļ�
	afx_msg void On32800();//�Ҷ�˫��ֵ
	afx_msg void On32801();//�Ҷȷ�ɫת��
	afx_msg void On32802();//�Ҷȴ��ڱ任
	afx_msg void On32803();//���߱任
	afx_msg void On32804();//�Ҷ�ֱ��ͼ
	afx_msg void On32805();//�Ҷȷֲ����⻯
	afx_msg void On32807();//�ڰ׵������˲�
	afx_msg void On32808();//���������ڵ�4����
	afx_msg void On32809();//���������ڵ�8����
	afx_msg void On32810();//3x3��ֵ�˲�
	afx_msg void On32811();//��������ƽ����
	afx_msg void On32812();//ѡ��ʽ��Ĥƽ��
	afx_msg void On32813();//NxN��ֵ�˲�
	afx_msg void On32814();//ʮ����ֵ�˲�
	afx_msg void On32815();//NxN���ֵ�˲�
	afx_msg void On32816();//�����������
	afx_msg void On32817();//������������
	afx_msg void On32818();//����΢��
	afx_msg void On32819();//����΢��
	afx_msg void On32820();//˫��΢��
	afx_msg void On32821();//������
	afx_msg void On32822();//�̶���
	afx_msg void On32823();//��ֵ��
	afx_msg void On32824();//Robert���ӱ�Ե���
	afx_msg void On32825();//sobel���ӱ�Ե���
	afx_msg void On32826();//prewitt���ӱ�Ե���
	afx_msg void On32827();//Krisch���ӱ�Ե���
	afx_msg void On32828();//��˹-������˹���Ӽ��
	afx_msg void On32829();//��ֵ�ָ�
	afx_msg void On32830();//����ֵ�ָ�
	afx_msg void On32831();//������ֵ�ָ�
	afx_msg void On32832();//������ȡ
	afx_msg void On32833();//�պ���������
	afx_msg void On32834();//����������
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void On32835();//��ֵͼ��������
	afx_msg void On32836();//��ֵͼ����ܳ�����
	afx_msg void On32837();//С�����������
	afx_msg void On32838();//ˮƽͶӰ
	afx_msg void On32839();//��ֱͶӰ
	afx_msg void On32840();//ˮƽ��ʴ
	afx_msg void On32841();//��ֱ��ʴ
	afx_msg void On32842();//ȫ����ʴ
	afx_msg void On32843();//ˮƽ����
	afx_msg void On32844();//��ֱ����
	afx_msg void On32845();//ȫ��������
	afx_msg void On32846();//������
	afx_msg void On32847();//������
	afx_msg void On32848();//ϸ��
	afx_msg void On32849();//�ֻ�
	afx_msg void On32850();//����任
	afx_msg void On32851();//���ٸ���Ҷ�任
	afx_msg void On32852();//��ɢ���ұ任
	afx_msg void On32853();//�����ͨ�˲���
	afx_msg void On32854();//ͼ���
	void GetNextFile(CString *file);//����ͼ��ϳ���ѡ��ڶ���ͼ��
	afx_msg void On32855();//ͼ���
	afx_msg void On32856();//ͼ����
	afx_msg void On32857();//ͼ���
	afx_msg void On32858();//ͼ���
	afx_msg void On32859();//ͼ����
	afx_msg void On32860();//ͼ�����
	afx_msg void On32861();//���
	afx_msg void On32862();//��ɫͼ�����ֵ��Ҷȴ���
	afx_msg void On32863();//��ʽ����Ҷ�
	afx_msg void On32864();//�Ҷȱ��ɫ
	afx_msg void On32865();//���ȵ���
	afx_msg void On32866();//�Աȶȵ���
	afx_msg void On32867();//���ȵ��淴����
	afx_msg void On32868();//�ع⴦��
	afx_msg void On32869();//��ɫͼ�����ɢ����
	afx_msg void On32870();//��ɫͼ��������Ч��
	afx_msg void On32871();//��ɫͼ������ƽ����ƽ��
	afx_msg void On32872();//3x3��ͨ�˲�
	afx_msg void On32873();//5x5��ͨ�˲�
	afx_msg void On32874();//ͼ���ˮƽ��ǿ
	afx_msg void On32875();//ͼ��ֱ��ǿ
	afx_msg void On32876();//��ɫͼ��˫������ǿ
	afx_msg void On32877();//��ɫͼ���ݶ���
	afx_msg void On32878();//��ɫͼ������ͨ
	afx_msg void On32879();//��ɫͼ�еȸ�ͨ�˲�
	afx_msg void On32880();//��ɫͼ�������ͨ�˲�
	afx_msg void On32881();//������
	afx_msg void On32882();//��ɫͼ�޺紦��
};
