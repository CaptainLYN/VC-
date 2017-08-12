#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)  //��ǰ��һ����������
CDib::CDib()
{
	 
}
CDib::~CDib()
{
	GlobalFreePtr(m_pBitmapInfo);//�ͷ���loadfile�������ڶ����������Դ
}
void CDib::LoadFile(CString m_filename)//��̬�������޸�
{
	//strcpy(m_fileName,dibFileName);
	CFile dibFile(m_filename,CFile::modeRead);//���캯����ʼ�����ƶȴ��ļ�,LPCTSTR����const char*,unicodeͨ���ַ���
	dibFile.Read((void*)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
	if(bitmapFileHeader.bfType==0x4d42)//λͼ�ļ������ͣ�����ʮ����19778
	{
		DWORD fileLength=dibFile.GetLength();
		/*DWORD*/ size=fileLength-sizeof(BITMAPFILEHEADER);//ͼ�����ݵ�ʵ�ʴ�С+��ɫ��+λͼ�ļ���Ϣͷ
		/*BYTE**/ pDib=(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,size);//�Ӷ��з�������ΪGMEM_MOVEABLE��win32ƽ̨��GMEM_FIXED�̶����Ѿ�û�д����𣩡�size��С�Ŀ��ƶ��ڴ�
		dibFile.Read((void*)pDib,size);//�������������ļ��ж�ȡsize��С�����ݷ���ָ�뻺������ÿ��һ�ζ�ȡָ���λ���ƶ�size��С���ļ�ͷ�Ѿ���ȡ���ˣ����ǰ�����Ϣͷ������
		dibFile.Close();

		m_pBitmapInfo=(BITMAPINFO*)pDib;//������ָ��ľ���λͼ��Ϣ��Ҳ��λͼ��Ϣ�ĵ�һ����Ա��λ��
		m_pBitmapInfoHeader=(BITMAPINFOHEADER*)pDib;
		m_pRGB=(RGBQUAD*)(pDib+m_pBitmapInfoHeader->biSize);//ָ����ɫ��
		int m_numberOfColors=GetNumberOfColors();//2��16��256���������ɫ
		if(m_pBitmapInfoHeader->biClrUsed==0)//λͼʵ��ʹ�õ���ɫ���е���ɫ���ǲ��Եģ����޸�
			m_pBitmapInfoHeader->biClrUsed=m_numberOfColors;
		DWORD colorTableSize=m_numberOfColors*sizeof(RGBQUAD);//��ɫ��Ĵ�С
		m_pData=pDib+m_pBitmapInfoHeader->biSize+colorTableSize;//��ɫ���ݵ�������ʼλ��
		if(m_pRGB==(RGBQUAD*)m_pData)//���û�е�ɫ��
			m_pRGB=NULL;
		m_pBitmapInfoHeader->biSizeImage=GetSize();//λͼ�Ĵ�С�����ֽ�Ϊ��λ
		m_valid=TRUE;
	}
	else
	{
		m_valid=FALSE;
		MessageBox(NULL,_T("�ⲻ��λͼ�ļ���"),_T("��ʾ"),MB_OK);//���������޸ģ�������
	}
}

BOOL CDib::IsValid()
{
	return m_valid;
}

char*CDib::GetFileName()
{
	return m_fileName;
}

UINT CDib::GetWidth()
{
	return (UINT)m_pBitmapInfoHeader->biWidth;
}

UINT CDib::GetHeight()
{
	return (UINT)m_pBitmapInfoHeader->biHeight;
}

DWORD CDib::GetSize()
{
	if(m_pBitmapInfoHeader->biSizeImage!=0)//λͼ�Ĵ�С
		return m_pBitmapInfoHeader->biSizeImage;
	else
	{//���Ծ��Լ�����
		DWORD height=(DWORD)GetHeight();
		DWORD width=(DWORD)GetWidth();
		return height*/*width */GetDibWidthBytes();
	}
}


//�������ֽ���
DWORD CDib::GetDibWidthBytes()
{
	byBitCount=m_pBitmapInfoHeader->biBitCount;//ÿ�����������λ����1��4��8�����ɫ
	LONG nWidth=m_pBitmapInfoHeader->biWidth;//λͼ�Ŀ�ȣ�������Ϊ��λ

	dwWidthBytes=(DWORD)m_pBitmapInfoHeader->biWidth;//λͼ�Ŀ���ֽ���
	if(byBitCount==1) dwWidthBytes=(nWidth+7)/8;//һλ���أ��ǰ��ֽڼ����Ӧ�ó�8
	else if(byBitCount==4) dwWidthBytes=(nWidth+1)/2;
	else if(byBitCount==24) dwWidthBytes=nWidth*3;//��Ϊ���ɫÿ��������24λ

	while((dwWidthBytes&3)!=0) dwWidthBytes++;//�Ƿ�Ϊ4�ı�������Ϊλͼÿ��Ϊ4�ı��������㲹0

	return dwWidthBytes;
}

//����λͼ��ɫ��Ŀ
UINT CDib::GetNumberOfColors()
{
	int numberOfColors;

	if((m_pBitmapInfoHeader->biClrUsed==0)&&(m_pBitmapInfoHeader->biBitCount<9))
	{
		switch(m_pBitmapInfoHeader->biBitCount)
		{
		case 1:numberOfColors=2;break;
		case 4:numberOfColors=16;break;
		case 8:numberOfColors=256;
		}
	}
	else
		numberOfColors=(int)m_pBitmapInfoHeader->biClrUsed;//��������ɫ������ʵ��ʹ�õ���ɫ
	return numberOfColors;
}

BYTE* CDib::GetData()
{
	return m_pData;
}

BYTE* CDib::GetData2()
{
	if(GetRGB())
		m_pData2=m_pData;//����ɫ��������������ͬ
	return m_pData2;
}

RGBQUAD* CDib::GetRGB()
{
	return m_pRGB;
}

BITMAPINFO* CDib::GetInfo()
{
	return m_pBitmapInfo;//λͼ��Ϣָ��
}

WORD CDib::PaletteSize(LPBYTE lpDIB)//LPBYTE��BYTEָ��
{
	return (DIBNumColors(lpDIB)*sizeof(RGBQUAD/*RGBTRIPLE*/));//λͼָ��ָ�����ɫ����Ŀ*ÿһ����ɫ�Ĵ�С,��ɫ���λ�ܴ�С
}

//Ӧ���Ƿ�����ɫ���е���������
WORD CDib::DIBNumColors(LPBYTE lpDIB)
{
	WORD wBitCount;//�豸�޹�ͼ��λ��
	//wBitCount=((LPBITMAPCOREHEADER)lpDIB)->bcBitCount;//ÿ����ɫ��λ��
	wBitCount=((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	switch(wBitCount)
	{
	case 1:return 2;
	case 4:return 16;
	case 8:return 256;
	default:return 0;
	}
}

void CDib::SaveFile(const CString filename)
{
	BITMAPFILEHEADER bmfHdr;
	LPBITMAPINFOHEADER lpBI;
	DWORD dwDIBSize;

	bmfHdr.bfType=0x4d42;//"BM"
	lpBI=(LPBITMAPINFOHEADER)m_pBitmapInfoHeader;

	dwDIBSize=*(LPDWORD)lpBI+PaletteSize((LPBYTE)lpBI);//λͼ���ݺ���Ϣͷ+��ɫ���λ��С������ֻ�к�������
	//       ���ṹ��ռ���ֽ���
	if((lpBI->biCompression==BI_RLE8)||(lpBI->biCompression==BI_RLE4))
		dwDIBSize+=lpBI->biSizeImage;//λͼ�Ĵ�С�ֽ�
	else
	{
		DWORD dwBmBitSize;//ֻ��ʾλͼ��λ�Ĵ�С
		dwBmBitSize=WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount))*lpBI->biHeight;//��ȵ��ֽ���*�߶�
		dwDIBSize+=dwBmBitSize;
		lpBI->biSizeImage=dwBmBitSize;//λͼ���ݴ�С���ֽ���
	}
	bmfHdr.bfSize=dwDIBSize+sizeof(BITMAPFILEHEADER);//λͼ�ļ��Ĵ�С��ָ���������ļ�
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;
	bmfHdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+lpBI->biSize+PaletteSize((LPBYTE)lpBI);

	CFile dibFile(filename,CFile::modeWrite|CFile::modeCreate);//|��λ��,CFile::modeWrite|CFile::modeCreate������������
	dibFile.Write(&bmfHdr,sizeof(BITMAPFILEHEADER));//�������Ҫд���Σ����ǲ�֪��Ϊʲô
	dibFile.Write(lpBI,dwDIBSize);
	dibFile.Close();
}

//rgbת�ɻҶ�ͼ
void CDib::RGBtoGrade()
{
	if(GetRGB())//�������ɫ�����������ɫ24λ
		m_pData2=m_pData;//��ɫ��ž�����ɫ��rgb���
	else
	{
		BYTE r,g,b;
		int height,wide,size;
		height=GetHeight();
		wide=GetWidth();
		size=height*wide;
		m_pData2=(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,size);
		LONG lLineBytes=GetDibWidthBytes();
		for(int j=0;j<height;j++)
		{
			for(int i=0;i<wide;i++)
			{
				b=m_pData[j*lLineBytes+3*i];
				g=m_pData[j*lLineBytes+3*i+1];
				r=m_pData[j*lLineBytes+3*i+2];
				m_pData2[j*wide+i]=(BYTE)(0.3*r+0.59*g+0.11*b);//wide�����أ�һ��������24λ����������rgbӳ��һ������ֵ��rgb���費ͬ��Ȩ�أ�һ��ֵ�ʹ�����rgb����ֵ����Ϊ�ǻҶ�ͼ
			}
		}
	}
}

//�Ҷ�ͼתΪrgb
void CDib::GradetoRGB()
{
	if(GetRGB())
		m_pData=m_pData2;//����rgb��Ⱦ�����
	else
	{
		//BYTE r,g,b;
		int height,wide;
		height=GetHeight();
		wide=GetWidth();
		LONG lLineBytes=GetDibWidthBytes();
		for(int j=0;j<height;j++)
		{
			for(int i=0;i<wide;i++)//��һ���Ҷ�ֵ��ֵ������rgb�������һ�п�ʼ����һ��ʼӦ��Ҳ��һ����
			{
				m_pData[(height-j-1)*lLineBytes+3*i]=m_pData2[(height-1-j)*wide+i];
				m_pData[(height-j-1)*lLineBytes+3*i+1]=m_pData2[(height-1-j)*wide+i];
				m_pData[(height-j-1)*lLineBytes+3*i+3]=m_pData2[(height-1-j)*wide+i];
			}
		}
	}
}