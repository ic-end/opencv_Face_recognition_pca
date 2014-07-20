/**
 *@brief ����Э������󣬲����ԣ�M*N��
 *@param[in] Mat& _matX������������ 
 *@param[out]
 *@return    _matX Mat��  CV_32F
 *@pre       �����Mat�����ݱ����ǵ�ͨ��CV_32F�͵�
 *@post      �����Mat�������ǵ�ͨ��CV_32F�͵�
 *@code
   Mat _matX(25, 1000, CV_32F, Scalar(0.0));
   int _M = 5;
   int _N = 5;

   Mat out;
   out=matCov(Mat& _matX, int _M, int _N);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "matCov.h"

Mat matCov(Mat _matX, int _M, int _N)
{
	return _matX * _matX.t() / (_M * _N);

}
