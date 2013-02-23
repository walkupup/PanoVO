
#ifndef _ALG_BASIC_H_
#define _ALG_BASIC_H_

#include "math.h"

#ifndef PI
#define PI 3.1415926
#endif

#define Clip3(min,max,val) (((val)<(min))?(min):(((val)>(max))?(max):(val)))
#define AB_ABS(x) (((x) > 0) ? (x) : -(x))
#define AB_SWAP(x, y, type) {type t; t = (x); (x) = (y); (y) = t;}


// �������
typedef struct  
{
	int width;
	int height;

	double intrin[9];
	double distort[8];

	double angle[3];
	int camNum;			// 0, 1, 2, 3 ��ʾ��װ�ڳ�����ǰ���ҡ���
	float camOffset[2];	// �Գ�ͷΪ�е㣬x���ң�yָ��β������ϵ���������λ��
	float camHeight;	// ����߶�

	int mirror;			// ԭͼ�Ƿ����Ҿ���ͨ��Ϊ0
} CamParam;


// 4x4 ��������
// m : ԭ����double m[16]
// invOut : �������double invOut[16]
int invertMatrix4x4(const double m[16], double invOut[16]);


// 3x3��������
void inv3x3Mat(double *src, double *in);


// ����ڲξ�������
void invIntrinMat(double *intrin, double *inv);


// �������
void jssjMatMulF(double *src1, double *src2, double *dst, int rows, int mid, int cols);

// �������λ�ã�ǰ�����ң����Ͱ�װ�Ƕȣ������������ԭ����µ���ת����
void jssjRotateMat(double *angle, int camNum, double *R);

// ������Ĺ���x, y���������ۻ���֮���ͼ������u��v
// ����matlab toolbox ������ۻ���ģ��
void fisheyeProj(double x, double y, double *intrin, double *distort, float *u, float *v);


// ��ӡ����
void printMat(double *mat, int width, int height, char *name);

#endif
