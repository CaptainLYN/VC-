/*
#ifndef _CDIB_H_  //�������ͷ�ļ���ı���ֻ����һ��
#define _CDIB_H_
*/
#pragma once

class CDib:public CObject
{
public:
	RGBQUAD* m_pRGB;//��ɫ��ָ��
	BYTE* m_pData,*m_pData2;//m_pDataָ��ԭ���ݣ�m_pData2ָ��Ҷ�����
	UINT m_numberOfColors;//λͼ��ɫ��Ŀ
	BOOL m_valid;//�Ƿ�������λͼ�ļ�
	BITMAPFILEHEADER bitmapFileHeader;//λͼ�ļ�ͷ
	
	BITMAPINFOHEADER* m_pBitmapInfoHeader;//λͼ��Ϣͷ
	BITMAPINFO* m_pBitmapInfo;//λͼ��Ϣָ��
	int byBitCount;
	DWORD dwWidthBytes;//DWORD ����Double Word,4���ֽڣ�32λ��λͼ�Ŀ���ֽ���
	BYTE* pDib;//�ļ���λͼ������ָ�룬Ҳ���Ƕ����ڴ��������ݵĵ�һ��
	DWORD size;//λͼ�����ݵĳ���

public:
	CDib();
	~CDib();

	char m_fileName[256];//�ļ���
	char* GetFileName();
	BOOL IsValid();//�Ƿ�������λͼ�ļ�
	DWORD GetSize();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetNumberOfColors();
	RGBQUAD* GetRGB();//��ȡ��ɫ��ָ��
	BYTE* GetData();
	BYTE* GetData2();
	DWORD GetDibWidthBytes();
	BITMAPINFO* GetInfo();//��ȡλͼ��Ϣ�ṹ��ָ��
	WORD PaletteSize(LPBYTE IpDIB);//λͼָ��ָ���λͼ��ɫ��Ĵ�С
	WORD DIBNumColors(LPBYTE IpDIB);//��������������ɫ����Ŀ
	void SaveFile(const CString filename);
	//DWORD GetFilesize();
public:
	void GradetoRGB();
	void RGBtoGrade();
	void LoadFile(CString dibFileName);
};

//#endif