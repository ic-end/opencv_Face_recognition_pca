/**
 *@brief ���ݲ�������ͼ�񣬲�����ѵ�����õ����ݽ���ʶ��
 *@param[in] 
 *@param[out]
 *@return    
 *@pre       
 *@post      
 *@code

 *@endcode

 *@since 2013.10.22
 *@author lichao
*/
#include "distinguishFaces.h"
int distinguishfaces(Mat _X_img_mean, Mat _eignVectorn, Mat _omiga_mat, float _threshold_omiga, int rows, int cols, int i, int j)
{
	char pathNames[100]; // Ҫʶ���ͼ���·����
	char windowsName[50]; // ��ʾͼ��Ĵ�������
	Mat imagergb(rows, cols, CV_8U, Scalar(0,0,0)); // �����RGBͼ��
	Mat imagergb_dis(rows, cols, CV_8U, Scalar(0,0,0)); // ʶ�����ͼ��

	Mat imagegray(rows, cols, CV_8U, Scalar(0)); // �����RGBͼ��ת�Ҷ�ͼ
	Mat imagegrayt(rows, cols, CV_8U, Scalar(0)); // ͼ��ת�ã���Ϊ�˶�����������matlab����һ�£���ɾȥ
	Mat imagegray_f(rows, cols, CV_32F, Scalar(0.0));// uchar to float
	Mat omiga_matx; // ͶӰ�������ռ�����Ӧ����������
	Mat omiga_matx_mid; // �м����
	Mat _omigaRoi;
	float sigma_x; // ��ʶ���������ѵ�����������������ռ��ŷʽ����
	int ix = 1;
	int iy = 1;
	int flag_Y_N = 0; // ��Ǽ�⵽ͼ��ĸ���
	int mark_k = 0;       // ��Ǽ�⵽�ĸ�����


	sprintf_s(pathNames, "D:\\Document\\vidpic\\����ͼ��\\����\\orl_%d_%d.bmp", i, j);

	imagergb = imread(pathNames); // ����rgbͼ��
	if(!imagergb.data)
	{
		cout << "δ�ҵ�ָ����ͼ��" << endl;
		Sleep(2000);
		exit(0);
	}

	cvtColor(imagergb, imagegray, CV_BGR2GRAY); // rgb2gray
	imagegrayt = imagegray.t(); // ͼ��ת��
	imagegrayt.convertTo(imagegray_f, CV_32F, 1.0, 0.0); // uchar to float
	normalize(imagegray_f, imagegray_f, 1.0, 0.0, NORM_INF); // ��һ��
	imagegray_f = imagegray_f.reshape(1,1); // ��ÿһ��ͼ������һ��
	// ��ʶ���������ƽ�����Ĳ�ֵͶӰ�������ռ�����Ӧ����������
	omiga_matx = _eignVectorn.t() * (imagegray_f - _X_img_mean).t(); 

	for (int k = 0; k < _eignVectorn.cols; k++)
	{
		_omigaRoi = _omiga_mat(Rect(k, 0, 1, _omiga_mat.rows));
		omiga_matx_mid = omiga_matx - _omigaRoi;
		sigma_x = norm(omiga_matx_mid, NORM_L2); // ��ʶ���������ѵ�����������������ռ��ŷʽ����
		if (sigma_x < _threshold_omiga)
		{
			_threshold_omiga = sigma_x;
			mark_k = k + 1;
		}

	}
	if (mark_k != 0)
	{
		ix = int((mark_k - 0.5) / 8); // �ҵ���ѵ�����ж�Ӧ������
		iy = mark_k - ix * 8;
		sprintf_s(pathNames, "D:\\Document\\vidpic\\����ͼ��\\ѵ��\\orl_%d_%d.bmp", ix + 1, iy);
		imagergb_dis = imread(pathNames);

		cout <<"��ʶ��ͼ��:\t" << i << "_" << j << endl;
		cout <<"��⵽��ͼ��:\t" << ix + 1 << "_" << iy << endl;
		if(i == (ix+1))
		{
			cout << "�����ȷ��\n"<<endl;
			flag_Y_N = 1;
		}
		else
		{
			cout << "��ⲻ��ȷ��\n"<<endl;
			flag_Y_N = 2;
		}

		//sprintf_s(windowsName, "ͼ%d_%d�ļ������", i, j);
		//dispManyimgs(windowsName, 2, imagergb, imagergb_dis); // ��һ����������ʾͼ��
	}
	return flag_Y_N;
}
