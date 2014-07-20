/**
 *@brief ����ÿһ������ƽ��ֵ�Ĳ�ֵ
 *@param[in] Mat& _X_img������������ Mat& _X_img_mean����������ƽ��
 *@param[out]
 *@return    avgMat Mat��  CV_32F
 *@pre       �����Mat�����ݱ����ǵ�ͨ��CV_32F�͵�
 *@post      �����Mat�������ǵ�ͨ��CV_32F�͵�
 *@code
   Mat X_img(25, 1000, CV_32F, Scalar(0.0));
   Mat X_img_mean;
   randu(X_img, Scalar::all(0.0), Scalar::all(1.0));
   reduce(X_img, X_img_mean, 0, CV_REDUCE_AVG); // ����ƽ��������Ϊһ��
   Mat out;
   out=avgFacemat(X_img, X_img_mean);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "avgFacemat.h"

Mat avgFacemat(Mat _X_img, Mat _X_img_mean)
{
	// _X_img ÿһ�ж�Ӧһ������
	Mat avgMat(_X_img.rows, _X_img.cols, CV_32F, Scalar(0.0));
	Mat imgRoi;
	Mat midMat;
	for (int i=0; i<_X_img.rows; i++)
	{
		imgRoi = _X_img(Rect(0, i, _X_img.cols, 1)); // ��ȡһ��
		avgMat(Rect(0, i, _X_img.cols, 1)) = imgRoi - _X_img_mean;// ÿһ�м�ȥ��ƽ��ֵ
		//cout<<imgRoi.at<float>(i,0)<<endl;
		//cout<<imgRoi.at<float>(i,1)<<endl;
	}
	return avgMat;
}
