/**
 *@brief ���������������еĲ�ֵ�Ķ����������������ֵ
 *@param[in] Mat& _Omiga ����������
 *@param[out]
 *@return    float threshold_omiga 
 *@pre       �����Mat�����ݱ����ǵ�ͨ��CV_32F�͵�
 *@post      �����float
 *@code
   Mat X_img(25, 30, CV_32F, Scalar(0.0));
   randu(X_img, Scalar::all(0.0), Scalar::all(1.0));
   float out;
   out=computeThreshold(Mat& _Omiga);
 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "computeThreshold.h"

float computeThreshold(Mat _Omiga)
{
	float threshold_omiga = 0;
	float mid_par = 0;
	Mat colRoi1; // ����ĵ�i��
	Mat colRoi2; // ����ĵ�j��
	Mat colRoi;  // ����ĵ�j��-��i��

	for (int i = 0; i < _Omiga.cols; i ++)
	{
		colRoi1 = _Omiga(Rect(i, 0, 1, _Omiga.rows)); // ȡ��i��
		for (int j = 0; j < _Omiga.cols; j++)
		{
			colRoi2 = _Omiga(Rect(j, 0, 1, _Omiga.rows)); // ȡ��j��
			colRoi = colRoi2 - colRoi1; // i��-j��
			mid_par = norm(colRoi, NORM_L2)/2; //��2����������2
			if(mid_par > threshold_omiga)
			{
				threshold_omiga = mid_par; // �ҵ����ֵ
			}
		}
	}	
	return threshold_omiga;
}
