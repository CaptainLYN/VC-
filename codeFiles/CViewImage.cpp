#include"stdafx.h"
#include"CDib.h"
#include<WindowsX.h>

#include"CViewImage.h"


void CViewImage::GetDib(CDib *dib2)
{
	dib=dib2;
}

CPalette* CViewImage::CreateBitmapPalette(CDib* pBitmap)
{
	struct mPalette//�����������
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];//PALETTEENTRYָ��һ���߼���ɫ��
	}palette={0x300,256};//version��0x300

	LPRGBQUAD pRGBTable=pBitmap->GetRGB();//LPRGBQUAD�ǵ�ɫ��ָ�룬ֻ��ǰ����LP�Ķ���ָ��
	UINT numberOfColors=pBitmap->GetNumberOfColors();
	for(UINT x=0;x<numberOfColors;++x)
	{
		palette.aEntries[x].peRed=pRGBTable[x].rgbRed;//���ǵڶ�����������Ԫ�غͳ�Ա������������
		palette.aEntries[x].peGreen=pRGBTable[x].rgbGreen;
		palette.aEntries[x].peBlue=pRGBTable[x].rgbBlue;
		palette.aEntries[x].peFlags=0;//ָ����ɫ�����ʹ�ã�PC_EXPLICIT��2��  PC_NOCOLLAPSE��4��  PC_RESERVED��1��	
	}
	hPalette=new CPalette;
	hPalette->CreatePalette((LPLOGPALETTE)&palette);//��ʼ����ɫ�����
	return hPalette;
}

void CViewImage::OnDraw(CDC* pDC)//���������һ������Ҫʵ�ֵ��麯�������Լ�ʹ����ʵ��ҲҪʵ��
{
	int m_scale=1;//�������ű���
	BYTE* pBitmapData=dib->GetData();//CDib���ָ����������ݻ�û����ø�ֵ
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//����CPlalette���󲢳�ʼ����ɫ�����
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//Ϊtrue��ʾ��̨��ɫ�壬���Ѵ����ĵ�ɫ����õ��豸��������,���ҷ��ؾɵĵ�ɫ��
		//�������SelectPalette���صľ����ϵĵ�ɫ��
		pDC->RealizePalette();//ʹ��ɫ����Ч
		//ǰ���::������õ���win api����ȫ�ֺ��������Ǿֲ��̳еĺ���
		::StretchDIBits(pDC->GetSafeHdc(),0,0,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //�豸�����ľ��
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//�ͷŹ���hPalette��ɫ���һ����Դ���߼��ʡ����ʡ����塢λͼ��������ɫ�壩
	}
	else//24λ���ɫ
	{
		::StretchDIBits(pDC->GetSafeHdc(),0,0,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw2(CDC* pDC,int x_move,int y_move)//�������������Ҫ�õĻ��ƺ���
{
	int m_scale=1;//�������ű���
	BYTE* pBitmapData=dib->GetData();//CDib���ָ�����
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//����CPlalette���󲢳�ʼ����ɫ�����
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//Ϊtrue��ʾ��̨��ɫ�壬���Ѵ����ĵ�ɫ����õ��豸��������,���ҷ��ؾɵĵ�ɫ��
		//�������SelectPalette���صľ����ϵĵ�ɫ��
		pDC->RealizePalette();//ʹ��ɫ����Ч
		//ǰ���::������õ���win api����ȫ�ֺ��������Ǿֲ��̳еĺ���
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //�豸�����ľ��
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//�ͷŹ���hPalette��ɫ���һ����Դ���߼��ʡ����ʡ����塢λͼ��������ɫ�壩
	}
	else//24λ���ɫ
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw3(CDC *pDC,LPBYTE temp,int x_move,int y_move)
{
	int m_scale=1;//�������ű���
	//BYTE* pBitmapData=dib->GetData();//CDib���ָ�����
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	int scaledWidth=(int)(bitmapWidth* m_scale);
	int scaledHeight=(int)(bitmapHeight* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//����CPlalette���󲢳�ʼ����ɫ�����
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//Ϊtrue��ʾ��̨��ɫ�壬���Ѵ����ĵ�ɫ����õ��豸��������,���ҷ��ؾɵĵ�ɫ��
		//�������SelectPalette���صľ����ϵĵ�ɫ��
		pDC->RealizePalette();//ʹ��ɫ����Ч
		//ǰ���::������õ���win api����ȫ�ֺ��������Ǿֲ��̳еĺ���
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //�豸�����ľ��
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//�ͷŹ���hPalette��ɫ���һ����Դ���߼��ʡ����ʡ����塢λͼ��������ɫ�壩
	}
	else//24λ���ɫ
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnDraw4(CDC *pDC,int x_move,int y_move,int need_width,int need_height)
{
	int m_scale=1;//�������ű���
	//BYTE* pBitmapData=dib->GetData();//CDib���ָ�����
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	/*int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();*/
	int scaledWidth=(int)(need_width* m_scale);
	int scaledHeight=(int)(need_height* m_scale);
	if(dib->GetRGB())
	{
		CPalette* hPalette=CreateBitmapPalette(dib);//����CPlalette���󲢳�ʼ����ɫ�����
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);//Ϊtrue��ʾ��̨��ɫ�壬���Ѵ����ĵ�ɫ����õ��豸��������,���ҷ��ؾɵĵ�ɫ��
		//�������SelectPalette���صľ����ϵĵ�ɫ��
		pDC->RealizePalette();//ʹ��ɫ����Ч
		//ǰ���::������õ���win api����ȫ�ֺ��������Ǿֲ��̳еĺ���
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,need_width,need_height,dib->GetData(),pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		              //�豸�����ľ��
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);//�ͷŹ���hPalette��ɫ���һ����Դ���߼��ʡ����ʡ����塢λͼ��������ɫ�壩
	}
	else//24λ���ɫ
	{
		::StretchDIBits(pDC->GetSafeHdc(),0+x_move,0+y_move,scaledWidth,scaledHeight,0,0,need_width,need_height,dib->GetData(),pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
	}

}

void CViewImage::OnXiangxia(CDC *pDC)//����ɨ��
{
	//CDC *pDC=GetDC();
	
//	clearmem();//����ͼ�����ݣ�ȡ��ԭʼͼ��Ŀ����ļ��������Ҳ���
	CDocument *pDoc=GetDocument();//�����뱾��ͼ���ӵ��ĵ������ָ��,��߸���

	//ASSERT_VALID(pDoc);//�ж�ָ��Ķ����Ƿ�Ϊ�գ�debug����Ч
	//if(!pDoc->stateddoc&&state2==1)//???????????
	//{
		BYTE* pBitmapData=dib->GetData();//�����е�α�����������Լ����
		LPBITMAPINFO pBitmapInfo=dib->GetInfo();
		int bitmapHeight=dib->GetHeight();
		int bitmapWidth=dib->GetWidth();

		if(dib->GetRGB())//�����ɫ��ָ�벻Ϊ��
		{
			CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);//һ��������
			CBrush brush(RGB(255,255,255));
			pDC->FillRect(&rect,&brush);//�����������ð�ɫ������ͼ��������ǲ������ұߺ��±�

			CPalette* hPalette=CreateBitmapPalette(dib);
			CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
			pDC->RealizePalette();
			for(int j=0;j<bitmapHeight;j++)
			{
				//�޸��˵�7����������ԭ��-1���������ǲ��Ե�
				//ͼ�������x�ᣬ����������y��
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,bitmapWidth,1,0,bitmapHeight-j-1,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				//1���豸�����ľ����2��3�����ǻ���ͼ�����Ͻ����꣬4��5�ǻ���ͼ��Ŀ�Ⱥ͸߶ȣ�6��7��Ҫ���Ƶ�ԭͼ�����½����꣨--�������곬���ˣ�����ͼ����Ӧ������԰�ɫ����--����ע�⣬λͼ�еĴ洢�ǵߵ��ģ������ǵ��Ÿ��ƣ���8��9��ԭͼ��Ⱥ͸߶ȣ�10��ָ��ͼ�����ݵ�ָ�룬11��ָ��ͼ��BITMAPINFO�ṹ��ָ�룬12��bmiColors������ʵ��RGBֵ���ǵ�ɫ���е�����ֵ��13ָ��Ҫ���еĹ�դ����
				//���Ŀ��������Ҫ���Ƶ�ԭͼ����ͽ����к��е����죬��֮���ù�դ��������ѹ��
				Sleep(5);//��ʱ5����
			}
			pDC->SelectPalette(hOldPalette,true);
			::DeleteObject(hPalette);
		}
//	}
	//Invalidate();//ˢ�£����û�����ж�
}
void CViewImage::OnXiangshang(CDC *pDC)//����ɨ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,bitmapWidth*2+5,bitmapHeight);//һ��������
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);//�����������ð�ɫ����������ֻ������������ϱ߽磬���������±߽�

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int j=0;j<bitmapHeight;j++)
		{
			
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,1,0,j,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::OnXiangyou(CDC *pDC)//����ɨ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{

		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int i=0;i<bitmapWidth;i++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),i+bitmapWidth+5,0,1,bitmapHeight,i,0,1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::OnXiangzuo(CDC *pDC)//����ɨ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		for(int i=0;i<bitmapWidth;i++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),2*bitmapWidth-i+4,0,1,bitmapHeight,bitmapWidth-i-1,0,1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuiPingYouYi(CDC *pDC)//ˮƽ����
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		for(int i=0;i<bitmapWidth;i++)
		{
			//ԭ����������Ǵ���ģ�ͼ���²���û�и��Ƶ�����Ϊ��jС��bitmapHeight���־���С��8ʱ����һ�ξͲ��ܸ�����
			/*for(int j=0;j<bitmapHeight;j=j+8)
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j-8,i+1,8,bitmapWidth-i,bitmapHeight-j,i+1,8,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			}*/
			//�����Լ����д�ģ�����ʵ��
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,i+1,bitmapHeight,bitmapWidth-i-1,0,i+1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(3);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToChuiZhiShangYi(CDC *pDC)//��ֱ����
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		for(int j=0;j<bitmapHeight;j++)
		{
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,j+1,0,bitmapHeight-1-j,bitmapWidth,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(4);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToJiaoChaFeiRu(CDC *pDC)//�������
{
	//CDocument *pDoc=GetDocument();

	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette *hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		for(int i=0;i<bitmapWidth;i++)
		{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,i+1,bitmapHeight/2,bitmapWidth-i-1,bitmapHeight/2,i+1,bitmapHeight/2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth*2+4-i,bitmapHeight/2,i+1,bitmapHeight-bitmapHeight/2,0,0,i+1,bitmapHeight-bitmapHeight/2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(3);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToSiZhouKuoZhang(CDC *pDC)//�м�����
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		//for(int i=1;i<=bitmapWidth/2;i++)//ֱ�Ӵ�1��ʼ
		//{
		//	//��һ����ȫ���࣬���Һ����Ǵ���ģ������͵�ͼƬ�ǲ�����չ��ȫ��
		//	//::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+bitmapWidth/2-i,bitmapHeight/2-i,i*2,i,bitmapWidth/2-i,bitmapHeight/2-i,i*2,i,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//	::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+bitmapWidth/2-i,bitmapHeight/2-i,i*2,i*2,bitmapWidth/2-i,bitmapHeight/2-i,i*2,i*2,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//	Sleep(30);
		//}
		int u,d,l,r;//�ϡ��¡����ұ߽�ֵ
		if(bitmapHeight%2)
		{
			u=bitmapHeight/2+1;
			d=bitmapHeight/2-1;
		}
		else
		{
			u=bitmapHeight/2;
			d=bitmapHeight/2-1;
		}
		if(bitmapWidth%2)
		{
			l=bitmapWidth/2+1;
			r=bitmapWidth/2-1;
		}
		else
		{
			l=bitmapWidth/2;
			r=bitmapWidth/2-1;
		}
		do
		{	
			u=u-1>=0?u-1:0;
			d=d+1<bitmapHeight?d+1:bitmapHeight-1;
			l=l-1>=0?l-1:0;
			r=r+1<bitmapWidth?r+1:bitmapWidth-1;
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+l,u,r-l+1,d-u+1,l,u,r-l+1,d-u+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(10);
		}while(!(u==0&&l==0&&d==bitmapHeight-1&&r==bitmapWidth-1));

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToZhongJianShouSuo(CDC *pDC)
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		for(int j=0;j<bitmapHeight/2+bitmapHeight%2;j++)//���������ʱ���м䲻��д������
		{
			//���Ǹ�����ȫ��ȷ��ʾ���롣���������޸�
			//�ֱ���������м临��
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,bitmapWidth,1,0,bitmapHeight-j-1,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,bitmapHeight-j-1,bitmapWidth,1,0,j,bitmapWidth,1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			Sleep(10);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuiPingShanTiao(CDC *pDC)//ˮƽդ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette* hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();

		int scanline=5;//ÿ��դ���Ŀ��
		int k=0;
		for(int i=0;i<bitmapWidth;i++)
		{
			for(int j=0;j<bitmapHeight;j+=2*scanline)
			{
				//���մ����ʵ��Ч����������Ȼ�Ҳ�û�мӱ߽��ж�����������������ֻ�Ḵ�Ƶ������ݵĵط��������жϱ߽�
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,j,i+1,scanline,bitmapWidth-i-1,bitmapHeight-j-scanline,i+1,scanline,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				k=j+scanline;//�Ҳ�դ����ʼ��
				::StretchDIBits(pDC->GetSafeHdc(),2*bitmapWidth+4-i,k,i+1,scanline,0,bitmapHeight-k-scanline,i+1,scanline,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);				
			}
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hOldPalette);
	}
}
void CViewImage::TOShuZhiShanTiao(CDC *pDC)//��ֱդ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		int scanline=5;
		int k=0;
		for(int j=0;j<bitmapHeight;j++)
		{
			for(int i=0;i<bitmapWidth;i+=2*scanline)
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+i,0,scanline,j+1,i,0,scanline,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				k=i+scanline;
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+k,bitmapHeight-1-j,scanline,j+1,k,bitmapHeight-1-j,scanline,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			
			}
			Sleep(5);
		}
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToTuXiangJianXian(CDC *pDC)//ͼ����
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		
		LPBYTE temp,temp1,temp2;//tempָ����ͼ�����ԭʼָ��
		temp=new BYTE[bitmapHeight*bitmapWidth];
		memset(temp,0,bitmapHeight*bitmapWidth);
		for(int n=0;n<=256;n++)
		{
			temp1=temp;
			temp2=pBitmapData;
			for(int i=0;i<bitmapWidth;i++)
				for(int j=0;j<bitmapHeight;j++)
				{
					*temp1=(*temp2)*n/256;//����д���һ��ǵ�һ��
					temp2++;
					temp1++;
				}
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,0,bitmapWidth,bitmapHeight,0,0,bitmapWidth,bitmapHeight,temp,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(6);
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
		delete[]temp;
	}
}
void CViewImage::ToShuiPingBaiYeChuang(CDC* pDC)//ˮƽ��Ҷ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//����ԭ��ĸ����Ͳ�����ȫ�γɣ����ѷ�,���޸�
		for(int i=0;i<bitmapWidth/10;i++)
			for(int j=0;j<=10;j++)//��=������Ǹ�����10�ݵĲ�������
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+j*(bitmapWidth/10),0,i+1,bitmapHeight,j*(bitmapWidth/10),0,i+1,bitmapHeight,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(1);
			}
	
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToShuZhiBaiYeChuang(CDC* pDC)//��ֱ��Ҷ��
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//����ԭ��ĸ����Ͳ�����ȫ�γɣ����ѷ�,���޸�,ע�����������
		for(int j=0;j<bitmapHeight/10;j++)
			for(int i=0;i<=10;i++)//��=������Ǹ�����10�ݵĲ�������
			{
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5,i*(bitmapHeight/10),bitmapWidth,j+1,0,bitmapHeight-(i+1)*(bitmapHeight/10),bitmapWidth,j+1,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
				Sleep(1);
			}
	
		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
	}
}
void CViewImage::ToMaSaiKeXianShi(CDC *pDC)//��������ʾ
{
	//CDocument *pDoc=GetDocument();
	BYTE* pBitmapData=dib->GetData();
	LPBITMAPINFO pBitmapInfo=dib->GetInfo();
	int bitmapHeight=dib->GetHeight();
	int bitmapWidth=dib->GetWidth();
	long mx=0;
	long my=0;
	//int scanline=8;//������ʾ��λ��
	int k=0;
	int nrw=0;
	int nrh=0;
	if((bitmapWidth%12)!=0) nrw=1;//�������12��������Ĳ���12������Ϊһ��������ʾ
	if((bitmapHeight%12)!=0) nrh=1;
	long ltilenum=(bitmapWidth/12+nrw)*(bitmapHeight/12+nrh);
	POINT *point=new POINT[ltilenum];

	if(dib->GetRGB())
	{
		CRect rect(bitmapWidth+5,0,2*bitmapWidth+5,bitmapHeight);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);

		CPalette *hPalette=CreateBitmapPalette(dib);
		CPalette* hOldPalette=pDC->SelectPalette(hPalette,true);
		pDC->RealizePalette();
		//
		for(int mi=0;mi<ltilenum;mi++)//��������
		{
			point[mi].x=mx;
			point[mi].y=my;
			mx=mx+12;
			if(mx>=bitmapWidth)//�޸���
			{
				mx=0;my=my+12;
			}
		}
		//srand((unsigned)time(NULL));//�趨���������
		//���벻����ȫ��ʾ�����޸�
		//for(int i=0;i<=2;i++)
		//{
		//	//
		//	for(int mi=ltilenum-1;mi>=0;mi--)
		//	{
		//		int n=(int)((double)ltilenum*rand()/RAND_MAX);
		//		mx=point[n].x;
		//		my=point[n].y;
		//		::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+mx,my,12,12,mx,bitmapHeight-my-12,12,12,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
		//		point[n].x=point[mi].x;//ʹ�Ѿ���ʾ����ָ����ܻ�û��ʾ��
		//		point[n].y=point[mi].y;
		//		Sleep(1);
		//	}
		//}
		//�������ҵĽⷨ����¼����ʾ�����������ظ��ͱ���û����ʾ��ȫͼ��
	    int xianshi=0;
		int *t=new int[ltilenum];
		memset(t,0,ltilenum*sizeof(int));//0��ʾû�з��ʹ�
		srand((unsigned)time(NULL));//�������������������
		while(xianshi<ltilenum)
		{
				int n=(int)((double)ltilenum*rand()/RAND_MAX);
				n=n==ltilenum?ltilenum-1:n;
			    if(t[n]==0)
				{
				mx=point[n].x;
				my=point[n].y;
				::StretchDIBits(pDC->GetSafeHdc(),bitmapWidth+5+mx,my,12,12,mx,bitmapHeight-my-12,12,12,pBitmapData,pBitmapInfo,DIB_RGB_COLORS,SRCCOPY);
			    t[n]=1;
				xianshi++;
				Sleep(1);
				}
		}

		pDC->SelectPalette(hOldPalette,true);
		::DeleteObject(hPalette);
		delete[]point;
	}
}
