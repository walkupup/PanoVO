#include "AlgBasic.h"
#include <stdio.h>

// 3x3矩阵求逆
void inv3x3Mat(double *src, double *in)
{
	int i, j;
	double a[3][3];
	double det;

	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
		{
			a[j][i] = src[j * 3 + i];
		}
	}

	det=a[0][0]*(a[1][1]*a[2][2]-a[2][1]*a[1][2])-a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0])+a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);

	in[0]=(a[1][1]*a[2][2]-a[2][1]*a[1][2])/det;
	in[3]=-(a[1][0]*a[2][2]-a[1][2]*a[2][0])/det;
	in[6]=(a[1][0]*a[2][1]-a[2][0]*a[1][1])/det;
	in[1]=-(a[0][1]*a[2][2]-a[0][2]*a[2][1])/det;
	in[4]=(a[0][0]*a[2][2]-a[0][2]*a[2][0])/det;
	in[7]=-(a[0][0]*a[2][1]-a[2][0]*a[0][1])/det;
	in[2]=(a[0][1]*a[1][2]-a[0][2]*a[1][1])/det;
	in[5]=-(a[0][0]*a[1][2]-a[1][0]*a[0][2])/det;
	in[8]=(a[0][0]*a[1][1]-a[1][0]*a[0][1])/det;

	return;
}



// 4x4 矩阵求逆
// m : 原矩阵，double m[16]
// invOut : 输出矩阵，double invOut[16]
int invertMatrix4x4(const double m[16], double invOut[16])
{
	double inv[16], det;
	int i;

	inv[0] = m[5]  * m[10] * m[15] - 
		m[5]  * m[11] * m[14] - 
		m[9]  * m[6]  * m[15] + 
		m[9]  * m[7]  * m[14] +
		m[13] * m[6]  * m[11] - 
		m[13] * m[7]  * m[10];

	inv[4] = -m[4]  * m[10] * m[15] + 
		m[4]  * m[11] * m[14] + 
		m[8]  * m[6]  * m[15] - 
		m[8]  * m[7]  * m[14] - 
		m[12] * m[6]  * m[11] + 
		m[12] * m[7]  * m[10];

	inv[8] = m[4]  * m[9] * m[15] - 
		m[4]  * m[11] * m[13] - 
		m[8]  * m[5] * m[15] + 
		m[8]  * m[7] * m[13] + 
		m[12] * m[5] * m[11] - 
		m[12] * m[7] * m[9];

	inv[12] = -m[4]  * m[9] * m[14] + 
		m[4]  * m[10] * m[13] +
		m[8]  * m[5] * m[14] - 
		m[8]  * m[6] * m[13] - 
		m[12] * m[5] * m[10] + 
		m[12] * m[6] * m[9];

	inv[1] = -m[1]  * m[10] * m[15] + 
		m[1]  * m[11] * m[14] + 
		m[9]  * m[2] * m[15] - 
		m[9]  * m[3] * m[14] - 
		m[13] * m[2] * m[11] + 
		m[13] * m[3] * m[10];

	inv[5] = m[0]  * m[10] * m[15] - 
		m[0]  * m[11] * m[14] - 
		m[8]  * m[2] * m[15] + 
		m[8]  * m[3] * m[14] + 
		m[12] * m[2] * m[11] - 
		m[12] * m[3] * m[10];

	inv[9] = -m[0]  * m[9] * m[15] + 
		m[0]  * m[11] * m[13] + 
		m[8]  * m[1] * m[15] - 
		m[8]  * m[3] * m[13] - 
		m[12] * m[1] * m[11] + 
		m[12] * m[3] * m[9];

	inv[13] = m[0]  * m[9] * m[14] - 
		m[0]  * m[10] * m[13] - 
		m[8]  * m[1] * m[14] + 
		m[8]  * m[2] * m[13] + 
		m[12] * m[1] * m[10] - 
		m[12] * m[2] * m[9];

	inv[2] = m[1]  * m[6] * m[15] - 
		m[1]  * m[7] * m[14] - 
		m[5]  * m[2] * m[15] + 
		m[5]  * m[3] * m[14] + 
		m[13] * m[2] * m[7] - 
		m[13] * m[3] * m[6];

	inv[6] = -m[0]  * m[6] * m[15] + 
		m[0]  * m[7] * m[14] + 
		m[4]  * m[2] * m[15] - 
		m[4]  * m[3] * m[14] - 
		m[12] * m[2] * m[7] + 
		m[12] * m[3] * m[6];

	inv[10] = m[0]  * m[5] * m[15] - 
		m[0]  * m[7] * m[13] - 
		m[4]  * m[1] * m[15] + 
		m[4]  * m[3] * m[13] + 
		m[12] * m[1] * m[7] - 
		m[12] * m[3] * m[5];

	inv[14] = -m[0]  * m[5] * m[14] + 
		m[0]  * m[6] * m[13] + 
		m[4]  * m[1] * m[14] - 
		m[4]  * m[2] * m[13] - 
		m[12] * m[1] * m[6] + 
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] + 
		m[1] * m[7] * m[10] + 
		m[5] * m[2] * m[11] - 
		m[5] * m[3] * m[10] - 
		m[9] * m[2] * m[7] + 
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - 
		m[0] * m[7] * m[10] - 
		m[4] * m[2] * m[11] + 
		m[4] * m[3] * m[10] + 
		m[8] * m[2] * m[7] - 
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] + 
		m[0] * m[7] * m[9] + 
		m[4] * m[1] * m[11] - 
		m[4] * m[3] * m[9] - 
		m[8] * m[1] * m[7] + 
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] - 
		m[0] * m[6] * m[9] - 
		m[4] * m[1] * m[10] + 
		m[4] * m[2] * m[9] + 
		m[8] * m[1] * m[6] - 
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return 0;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return 1;
}



// 矩阵相乘 dst = src1 * src2
// src1 is rows x mid, src2 is mid x cols
void jssjMatMulF(double *src1, double *src2, double *dst, int rows, int mid, int cols)
{
	int i, j, k;

	for (j = 0; j < rows; j++)
	{
		for (i = 0; i < cols; i++)
		{
			dst[j * cols + i] = 0;
			for (k = 0; k < mid; k++)
			{
				dst[j * cols + i] += src1[j * mid + k] * src2[i + k * cols];
			}
		}
	}
	return;
}


// 计算旋转矩阵
// angle, 三个角度
// camNum, 相机编号, 0, 1, 2, 3 代表安装在车体左，前，右，后
// R, 旋转矩阵
void jssjRotateMat(double *angle, int camNum, double *R)
{
	double pitch, roll, yaw;
	double rollMat[9];
	double tmp2[9];
	double tmp3[9];
	double yawMat[9];

	pitch = angle[0];
	roll = angle[1];
	yaw = angle[2];

	//左
	if (camNum == 0)
	{
		tmp2[0] = 0;
		tmp2[3] = sin(pitch);
		tmp2[6] = -cos(pitch);
		tmp2[1] = -1;
		tmp2[4] = 0;
		tmp2[7] = 0;
		tmp2[2] = 0;
		tmp2[5] = cos(pitch);
		tmp2[8] = sin(pitch);

		rollMat[0] = 1;
		rollMat[3] = 0;
		rollMat[6] = 0;
		rollMat[1] = 0;
		rollMat[4] = cos(roll);
		rollMat[7] = -sin(roll);
		rollMat[2] = 0;
		rollMat[5] = sin(roll);
		rollMat[8] = cos(roll);

	}

	//前
	else if (camNum == 1)
	{
		tmp2[0] = 1;
		tmp2[3] = 0;
		tmp2[6] = 0;
		tmp2[1] = 0;
		tmp2[4] = sin(pitch);
		tmp2[7] = -cos(pitch);
		tmp2[2] = 0;
		tmp2[5] = cos(pitch);
		tmp2[8] = sin(pitch);

		rollMat[0] = cos(roll);
		rollMat[3] = 0;
		rollMat[6] = -sin(roll);
		rollMat[1] = 0;
		rollMat[4] = 1;
		rollMat[7] = 0;
		rollMat[2] = sin(roll);
		rollMat[5] = 0;
		rollMat[8] = cos(roll);
	}

	//右
	else if (camNum == 2)
	{
		tmp2[0] = 0;
		tmp2[3] = -sin(pitch);
		tmp2[6] = cos(pitch);
		tmp2[1] = 1;
		tmp2[4] = 0;
		tmp2[7] = 0;
		tmp2[2] = 0;
		tmp2[5] = cos(pitch);
		tmp2[8] = sin(pitch);

		rollMat[0] = 1;
		rollMat[3] = 0;
		rollMat[6] = 0;
		rollMat[1] = 0;
		rollMat[4] = cos(roll);
		rollMat[7] = -sin(roll);
		rollMat[2] = 0;
		rollMat[5] = sin(roll);
		rollMat[8] = cos(roll);
	}

	//后
	else
	{
		tmp2[0] = -1;
		tmp2[3] = 0;
		tmp2[6] = 0;
		tmp2[1] = 0;
		tmp2[4] = -sin(pitch);
		tmp2[7] = cos(pitch);
		tmp2[2] = 0;
		tmp2[5] = cos(pitch);
		tmp2[8] = sin(pitch);  //pitch

		rollMat[0] = cos(roll);
		rollMat[3] = 0;
		rollMat[6] = -sin(roll);
		rollMat[1] = 0;
		rollMat[4] = 1;
		rollMat[7] = 0;
		rollMat[2] = sin(roll);
		rollMat[5] = 0;
		rollMat[8] = cos(roll);
	}

	yawMat[0] = cos(yaw);
	yawMat[3] = -sin(yaw);
	yawMat[6] = 0;
	yawMat[1] = sin(yaw);
	yawMat[4] = cos(yaw);
	yawMat[7] = 0;
	yawMat[2] = 0;;
	yawMat[5] = 0;
	yawMat[8] = 1; 	

	//R,t
	jssjMatMulF(tmp2, rollMat, tmp3, 3, 3, 3);
	jssjMatMulF(tmp3, yawMat, R, 3, 3, 3);

}

// 由输入的光线x, y，计算鱼眼畸变之后的图像坐标u，v
// 采用matlab toolbox 里的鱼眼畸变模型
void fisheyeProj(double x, double y, double *intrin, double *distort, float *u, float *v)
{
	double s;
	double distx;
	double disty;
	double r = sqrt(x * x + y * y);

	if (r < 0.1)
	{
		distx = x;
		disty = y;
	}
	else
	{
		double t = atan(r);
		double t2 = t * t;
		double t4 = t2 * t2;
		double t6 = t4 * t2;
		double t8 = t4 * t4;
		double kr = 1 + distort[0] * t2 + distort[1] * t4 + distort[2] * t6 + distort[3] * t8;
		double td = t * kr;
		s = td / r;
		distx = x * s;
		disty = y * s;
	}
	*u = (intrin[0] * distx + intrin[2]);
	*v = (intrin[4] * disty + intrin[5]);
	return;
}

// 打印矩阵
void printMat(double *mat, int width, int height, char *name)
{
	int i, j;

	printf("%s\n", name);
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			printf("%f, ", mat[j * width + i]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

// 相机内参矩阵求逆
void invIntrinMat(double *intrin, double *inv)
{
	inv[0] = 1.0f / intrin[0];
	inv[1] = 0;
	inv[2] = -intrin[2] / intrin[0];
	inv[3] = 0;
	inv[4] = 1.0f / intrin[4];
	inv[5] = -intrin[5] / intrin[4];
	inv[6] = 0;
	inv[7] = 0;
	inv[8] = 1;
	return;
}

// 由相机内参求fov
double fovFromIntrin(double *intrin, int width, int height)
{
	double fx = intrin[0];
	double fy = intrin[4];
	double u0 = intrin[2];
	double theta1, theta2;

	theta1 = atan2(u0, fx);
	theta2 = atan2(width - u0, fx);

	return theta1 + theta2;
}
