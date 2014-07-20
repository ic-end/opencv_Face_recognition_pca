#include <iostream>
#include <highgui.h>
#include <algorithm>
#include "inPutimgs.h"
#include "matCov.h"
#include "avgFacemat.h"
#include "findMaxnums.h"
#include "pickUpeignvectorn.h"
#include "computeThreshold.h"
#include "distinguishFaces.h"

using namespace std;
using namespace cv;
// ע��matlab�о����ǰ������ȴ洢����c�о��������ȴ洢
// ���matlab��opencv��reshape�᲻��ͬ
int main()
{
	int N = 40; // 40����
	int M = 8; // ÿ���˶�Ӧ8��ͼ
	int rows = 112; // ͼ�����
	int cols = 92; // ͼ�����
	int numRight = 0; // ׼ȷʶ����
	int numWrong = 0; // ����ʶ����
	Mat X_img(N*M, rows*cols, CV_32F, Scalar(0.0));
	Mat X_img_mean(1, rows*cols, CV_32F, Scalar(0.0));
	Mat A_mat; // ��ֵ��
	Mat C_mat; // Э�������
	Mat S; // ����ֵ25*1 U*S*VT=
	Mat U; //svd�ֽ��U
	Mat VT; //svd�ֽ��v��ת��
	int maxeignValuenums = 0; // ����x%������ֵ�ĸ���
	float eignValuepercent = 0.99f; // ���ļ�������ֵ�İٷֱ�
	Mat eignVectorn; // ����������ɸ���������
	Mat omiga_mat; // ��ѵ����������ƽ�����Ĳ�ֵͶӰ�������ռ�
	float threshold_omiga = 0.0f;
	int flag_Y_N = 0; // ��Ǽ������������ĸ���

	double duration;
	duration = static_cast<double>(getTickCount());

	X_img = inPutimgs(N, M, rows, cols); //ÿһ�ж�Ӧһ���˵�һ��ͼ
	reduce(X_img, X_img_mean, 0, CV_REDUCE_AVG); // ����ƽ��������Ϊһ��
	A_mat = avgFacemat(X_img, X_img_mean); // ���ֵ�� 
	C_mat = matCov(A_mat, M, N); // ����Э�������
	SVDecomp(C_mat, S, U, VT,SVD::FULL_UV);  //SVD�ֽ� �������FULL_UV��ʾ��U��VT����Ƶ�λ��������;

	maxeignValuenums = findMaxnums(S, eignValuepercent); // ���������ɸ�����ֵ�ĸ���
	cout << "maxeignValuenums=" << maxeignValuenums << endl;

	eignVectorn = pickUpeignvectorn(A_mat, VT, S, maxeignValuenums); // �������ļ�������ֵ��Ӧ����������

	omiga_mat = eignVectorn.t() * A_mat.t(); // ��ѵ����������ƽ�����Ĳ�ֵͶӰ�������ռ�

	threshold_omiga = computeThreshold(omiga_mat); // ������ֵ
	// cout << "threshold_omiga=" << threshold_omiga << endl;

	for (int i = 9; i <= 10; i++)
	{
		for (int j = 1; j <= 40; j++)
		{
			flag_Y_N=distinguishfaces(X_img_mean, eignVectorn, omiga_mat, threshold_omiga, rows, cols, j, i); // ʶ����
			if (1 == flag_Y_N)
			{
				numRight++;
			}
			else if (2 == flag_Y_N)
			{
				numWrong++;
			}

		}
	}
	cout << "׼ȷʶ��Ч��Ϊ��" << numRight / 80.0 << endl;
	cout << "����ʶ��Ч��Ϊ��" << numWrong / 80.0 << endl;

	duration = static_cast<double>(getTickCount())-duration;
	duration = duration / getTickFrequency();
	cout << "����ʱ��Ϊ��" << duration << "s" <<endl;

	Sleep(20000);
	waitKey(0);
}