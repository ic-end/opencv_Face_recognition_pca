/**
 *@brief ����һ���������������������ɸ�����ע���������Ѿ����Ӵ�С����
 *@param[in] Mat& _eignValues����������������� float _percent�����ļ������İٷֱ�
 *@param[out]
 *@return    _eignValues Mat��  CV_32F
 *@pre       �����Mat�����ݱ����ǵ�ͨ��CV_32F�͵�
 *@post      �����int�ͣ�����
 *@code
   Mat X_img(100, 1, CV_32F, Scalar(0.0));
   X_img = ������;
   int out;
   out=findMaxnums(Mat& _eignValues, float _percent);
 *@endcode

 *@since 2013.10.20
 *@author lichao
*/
#include "findMaxnums.h"

int findMaxnums(Mat _eignValues, float _percent)
{
	if(_eignValues.depth() != 5)
	{
		cout << "��������ȷ��Mat��ֵ���ͣ�" << endl;
		Sleep(2000);
		exit(-1);
	}

	Mat sumEignvalueall; // ��������ֵ�ĺ�
	Mat _eignValues_mid; // �м����
	float sumEignvaluen = 0; // ǰ���ɸ�����ֵ�ĺ�
	int maxNumsn = 0; // ����_percent������ֵ�ĸ���

	// _eignValues_mid = _eignValues.mul(_eignValues); // _eignValues��������ֵ�����ź��ֵ���˴����
	reduce(_eignValues, sumEignvalueall, 0, CV_REDUCE_SUM); // �������
	for (int i=0; i<_eignValues.rows; i++)
	{
		maxNumsn += 1;
		sumEignvaluen += _eignValues.at<float>(i);
		if(sumEignvaluen >= sumEignvalueall.at<float>(0) * _percent)
		{
			i = _eignValues.rows;
		}
	}
	//cout << sumEignvalueall << endl;
	//cout << sumEignvaluen << endl;
	return maxNumsn;
}
