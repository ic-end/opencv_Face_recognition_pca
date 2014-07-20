/**
 *@brief ����Э����������������
		 C = A*A'/(m*n);
		 [S, U, VT]=svd(C);
		 S:����ֵ�Ŀ�ƽ��
		 ��������=1/Si*A*Vi
 *@param[in] Mat& _A_mat��A����  Mat& _VT_mat��V�����ת�� 
			 Mat& _eignValues������ֵ�Ŀ�����  int _nums��Ҫȡ�����������ĸ���
 *@param[out]
 *@return    eignVector_mat Mat��  CV_32F  ������������
 *@pre       �����Mat�����ݱ����ǵ�ͨ��CV_32F�͵�
 *@post      �����Mat�������ǵ�ͨ��CV_32F�͵�
 *@code
	int _nums=10;
	A = ...;
	C_mat = matCov(A, M, N); // ����Э�������
	SVDecomp(C, S, U, VT,SVD::FULL_UV);  //SVD�ֽ� �������FULL_UV��ʾ��U��VT����Ƶ�λ��������;
	Mat out;
	out = pickUpeignvectorn(Mat& A, Mat& VT, Mat& S, int _nums);
 *@endcode

 *@since 2013.10.21
 *@author lichao
*/
#include "pickUpeignvectorn.h"

Mat pickUpeignvectorn(Mat _A_mat, Mat _VT_mat, Mat _eignValues, int _nums)
{
	Mat eignVector_mat(_A_mat.cols, _nums, CV_32F, Scalar(0.0));
	Mat eignVectorRoi;
	Mat vtRoi;
	for (int i = 0; i < _nums; i++)
	{
		eignVectorRoi = eignVector_mat(Rect(i, 0, 1, _A_mat.cols)); // ����ĵ�i�У���i����������
		vtRoi =_VT_mat.t()(Rect(i, 0, 1, _VT_mat.cols)); // VT_mat�ĵ�i�У���i����������
		//cout << _eignValues.at<float>(i,0) << endl;
		eignVectorRoi = (1/sqrt(_eignValues.at<float>(i,0))) * _A_mat.t() * vtRoi;
	}
	return eignVector_mat;
}
