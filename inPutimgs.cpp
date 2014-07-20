/**
*@brief �������ɷ�RGBͼ��Ȼ��ת��Ϊ�Ҷ�ͼ�񣬲����棬ÿ��ͼ�񱣴�Ϊһ��
*@param[in] int N�� int M��ȷ������ͼ������� int rows��int cols��ȷ������ͼ���С
*@param[out]
*@return    float_img Mat��  CV_32FC3
*@pre       �����Mat�����ݱ�������ͨ��CV_8U�͵�
*@post      �����Mat�������ǵ�ͨ��CV_32F�͵�
*@code
Mat test_img(25, 10000, CV_8U, Scalar(0));
test_img=inPutimgs(5, 5, 100, 100);
*@endcode

*@since 2013.10.20
*@author lichao
*/
#include "inPutimgs.h"

Mat inPutimgs(int _N, int _M, int _rows, int _cols)
{
	char pathNames[100]; // �������ͼ���·��
	Mat imagergb(_rows, _cols, CV_8U, Scalar(0, 0, 0)); // �����RGBͼ
	Mat imagegray(_rows, _cols, CV_8U, Scalar(0)); // �����RGBͼת��Ϊ�Ҷ�ͼ
	Mat imagegrayt(_rows, _cols, CV_8U, Scalar(0)); // ͼ��ת����Ϊ�˶�����������matlab����һ�£���ɾȥ
	Mat imagegray_f(_rows, _cols, CV_32F, Scalar(0.0)); // ucharͼ����Ϊfloatͼ�����ּ��㾫��
	Mat outImg(_N * _M, _rows * _cols, CV_32F, Scalar(0.0)); // �����ͼ�����
	Mat imgROI; // ���ͼ��ĸ���Ȥ����

	for (int i = 1; i <= _N; i++)
	{
		for (int j = 1; j <= _M; j++)
		{
			sprintf_s(pathNames, "D:\\Document\\vidpic\\����ͼ��\\ѵ��\\orl_%d_%d.bmp", i, j);
			imagergb = imread(pathNames); // ����rgbͼ��
			if(!imagergb.data)
			{
				cout << "δ�ҵ�ָ����ͼ��" << endl;
				Sleep(2000);
				exit(0);
			}
			cvtColor(imagergb, imagegray, CV_BGR2GRAY); //rgb2gray
			imagegrayt = imagegray.t(); // ͼ��ת����Ϊ�˶�����������matlab����һ�£���ɾȥ
			imagegrayt.convertTo(imagegray_f, CV_32F, 1.0, 0.0); // uchar to float
			normalize(imagegray_f, imagegray_f, 1.0, 0.0, NORM_INF); // �����ֵ��һ��

			//��ÿһ��ͼ������һ�У����δ洢��outImg��
			imgROI = outImg(Rect(0, (i - 1) * _M + j - 1, _rows * _cols, 1)); // ѡ�����Ȥ����
			imagegray_f.reshape(1, 1).copyTo(imgROI); // ͼ������һ�У��������ڸ���Ȥ����

			//cout << i << "_" << j << endl;
			//namedWindow("test");
			//imshow("test",imagegray);
			//waitKey(10);
		}
	}
	return outImg;
}
