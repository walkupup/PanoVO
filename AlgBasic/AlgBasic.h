
#ifndef _ALG_BASIC_H_
#define _ALG_BASIC_H_

#include "math.h"

#ifndef PI
#define PI 3.1415926
#endif

#define Clip3(min,max,val) (((val)<(min))?(min):(((val)>(max))?(max):(val)))
#define AB_ABS(x) (((x) > 0) ? (x) : -(x))
#define AB_SWAP(x, y, type) {type t; t = (x); (x) = (y); (y) = t;}


// 相机参数
typedef struct  
{
	int width;
	int height;

	double intrin[9];
	double distort[8];

	double angle[3];
	int camNum;			// 0, 1, 2, 3 表示安装在车体左、前、右、后
	float camOffset[2];	// 以车头为中点，x向右，y指向车尾的坐标系下相机坐标位置
	float camHeight;	// 相机高度

	int mirror;			// 原图是否左右镜像，通常为0
} CamParam;


// 4x4 矩阵求逆
// m : 原矩阵，double m[16]
// invOut : 输出矩阵，double invOut[16]
int invertMatrix4x4(const double m[16], double invOut[16]);


// 3x3矩阵求逆
void inv3x3Mat(double *src, double *in);


// 相机内参矩阵求逆
void invIntrinMat(double *intrin, double *inv);


// 矩阵相乘
void jssjMatMulF(double *src1, double *src2, double *dst, int rows, int mid, int cols);

// 根据相机位置（前后左右），和安装角度，求虚拟相机在原相机下的旋转矩阵
void jssjRotateMat(double *angle, int camNum, double *R);

// 由输入的光线x, y，计算鱼眼畸变之后的图像坐标u，v
// 采用matlab toolbox 里的鱼眼畸变模型
void fisheyeProj(double x, double y, double *intrin, double *distort, float *u, float *v);


// 打印矩阵
void printMat(double *mat, int width, int height, char *name);

#endif
