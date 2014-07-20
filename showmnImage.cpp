/**
 *@brief ��_DispImage�ģ�_m, _n��λ�ÿ�ʼ��ʾ_Image
 *@param[in] int _m,int _n����ʼ����  Mat _Image������ʾͼ��
			 Mat& _DispImage ����ͼ������
 *@param[out]
 *@return    _DispImage �޸Ĺ�������ͼ��
 *@pre       �����Mat������
 *@post      �����Mat������
 *@code
   Mat _DispImage(500, 500, CV_8UC3, Scalar(0, 0, 0));
   Mat _Image(100, 100, CV_8UC3, Scalar(255, 0, 0));
   int _m = 100;
   int _n = 100;
   _DispImage = showmnImage(int _m,int _n,Mat& _Image, Mat& _DispImage) ;

 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "showmnImage.h"

Mat showmnImage(int _m,int _n,Mat& _Image, Mat& _DispImage) 
{
	Mat imageROI;
	if((_m < 0) || (_m > _DispImage.cols - _Image.cols) || (_n < 0) || (_n > _DispImage.rows - _Image.rows))
	{
		cout << "�����������" << endl;
		_m = 0;
		_n = 0;
	}
	imageROI=_DispImage(Rect(_m,_n,_Image.cols,_Image.rows));
	_Image.copyTo(imageROI,_Image);
	return _DispImage;
}