
// MfcPictureProcessing.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMfcPictureProcessingApp:
// �йش����ʵ�֣������ MfcPictureProcessing.cpp
//

class CMfcPictureProcessingApp : public CWinApp
{
public:
	CMfcPictureProcessingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMfcPictureProcessingApp theApp;