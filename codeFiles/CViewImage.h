#pragma once
class CDib;
class CViewImage:public CView
{
protected:
	CPalette *hPalette;//��������������ָ�룬Ϊʲô����ʵ�����أ��������һ������ֻ��һ���ļ������ǿ��Եģ���δ򿪻�����ڴ���󣨴�ҿ�����һ�£���ָ��Ļ���û��һ�ζ����½�һ���࣬�����˼�û�ˣ��ʺ���ָ��
	CDib *dib;
	
public:

	void GetDib(CDib *dib2);//CObject�ǲ���ֱ����Ϊ�������ݵģ���Ϊ���ܱ����ƣ���˽�к���

	void virtual OnDraw(CDC *pDC);//CDC�����豸�������࣬���ڻ�ͼ�����,ʵ���麯��
	void OnDraw2(CDC *pC,int x_move,int y_move);//ԭͼ����ʾλ�ÿ����ƶ��Ļ�ͼ����
	void OnDraw3(CDC *pDC,LPBYTE temp,int x_move,int y_move);
	void OnDraw4(CDC *pC,int x_move,int y_move,int need_width,int need_height);//������ԭͼ������Ҫ�Ĵ�С,��û���޸�ԭͼ��info

    CPalette* CreateBitmapPalette(CDib *pBitmap);
	void OnXiangxia(CDC *pDC);//�ĳ����в����ģ�CDC�ڶԻ����л�ȡ����������������ȡ���ж����⣬û���Ϊʲô
	void OnXiangshang(CDC *pDC);//����ɨ��
	void OnXiangyou(CDC *pDC);//����ɨ��
	void OnXiangzuo(CDC *pDC);//����ɨ��
	void ToShuiPingYouYi(CDC *pDC);//ˮƽ����
	void ToChuiZhiShangYi(CDC *pDC);//��ֱ����
	void ToJiaoChaFeiRu(CDC *pDC);//�������
	void ToSiZhouKuoZhang(CDC *pDC);//��������
	void ToZhongJianShouSuo(CDC *pDC);//�м�����
	void ToShuiPingShanTiao(CDC *pDC);//ˮƽդ��
	void TOShuZhiShanTiao(CDC *pDC);//��ֱդ��
	void ToTuXiangJianXian(CDC *pDC);//ͼ����
	void ToShuiPingBaiYeChuang(CDC* pDC);//ˮƽ��Ҷ��
	void ToShuZhiBaiYeChuang(CDC* pDC);//��ֱ��Ҷ��
	void ToMaSaiKeXianShi(CDC *pDC);//��������ʾ

};//�����һ���ֺžͶ���20����������Ϊinclude����û�зֺ�