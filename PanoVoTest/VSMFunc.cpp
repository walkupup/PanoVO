/*****************************************************************
Copyright (C), 2011-2020, iCare Vision Tech. Co., Ltd.
All rights reserved

FileName: VSMFunc.c
Description: Vehicle Surrounding Monitor (VSM) 汽车全景图内部函数

History:
<author>		<time>		<version>		<Abstract>
杨力 　　　	   12-01-15      1.0.0			创建此文件
*****************************************************************/


#include "stdafx.h"
#include "jssjVSM.h"
#include <stdio.h>
#include <string.h>
#include <stdio.h>

// load vehicle parameters
// Parameter:
// fv -- file of vehicle
// fcam -- file of camera
// fcar -- file of car
//
// return:
// -1 if error
// >= 0 if success
int loadVehParam(FILE *fv, FILE *fcam, FILE *fcar, VehParam *par)
{
	int i;
	char buf[300];
	char carType[20];
	int succ;

	fscanf(fv, "Cam ID = %d %d %d %d\n", &par->camID[0], &par->camID[1], &par->camID[2], &par->camID[3]);

	// 载入相机参数
	for (i = 0; i < VSM_CAM_NUM; i++)
	{
		succ = 0;
		while (fgets(buf, 300, fcam) != NULL)
		{
			if (buf[0] == '[')
			{
				if (atoi(&buf[1]) == par->camID[i])
				{
					fscanf(fcam, "%f %f %f\n", &par->intrinParam[i][0], &par->intrinParam[i][1], &par->intrinParam[i][2]);
					fscanf(fcam, "%f %f %f\n", &par->intrinParam[i][3], &par->intrinParam[i][4], &par->intrinParam[i][5]);
					fscanf(fcam, "%f %f %f\n", &par->intrinParam[i][6], &par->intrinParam[i][7], &par->intrinParam[i][8]);
					fscanf(fcam, "%f %f %f %f %f %f %f %f\n", &par->distortParam[i][0], &par->distortParam[i][1], 
						&par->distortParam[i][2], &par->distortParam[i][3], &par->distortParam[i][4], 
						&par->distortParam[i][5], &par->distortParam[i][6], &par->distortParam[i][7]);
					fscanf(fcam, "\n");
					succ = 1;
					break;
				}
			}
		}
		if (!succ)
			return -1;

		rewind(fcam);
	}

	// 载入车辆尺寸参数
	fscanf(fv, "Car Type = %s\n", &par->carType[0]);
	strcpy(&carType[1], par->carType);
	carType[0] = '[';
	strcat(carType, "]\0");
	succ = 0;
	while (fgets(buf, 300, fcar) != NULL)
	{
		if (buf[0] == '[')
		{
			if (strncmp(buf, carType, strlen(carType)) == 0)
			{
				fscanf(fcar, "Vehicle Len = %f\n", &par->vehLen);
				fscanf(fcar, "Vehicle Width = %f\n", &par->vehWidth);
				succ = 1;
				break;
			}
		}
		if (!succ)
			return -1;
	}

	fscanf(fv, "Cam Height 0 = %f\n", &par->camHeight[0]);
	fscanf(fv, "Cam Height 1 = %f\n", &par->camHeight[1]);
	fscanf(fv, "Cam Height 2 = %f\n", &par->camHeight[2]);
	fscanf(fv, "Cam Height 3 = %f\n", &par->camHeight[3]);
	fscanf(fv, "Cam Offset 0 = %f %f\n", &par->camOffset[0][0], &par->camOffset[0][1]);
	fscanf(fv, "Cam Offset 1 = %f %f\n", &par->camOffset[1][0], &par->camOffset[1][1]);
	fscanf(fv, "Cam Offset 2 = %f %f\n", &par->camOffset[2][0], &par->camOffset[2][1]);
	fscanf(fv, "Cam Offset 3 = %f %f\n", &par->camOffset[3][0], &par->camOffset[3][1]);
	fscanf(fv, "Sight 0 = %f\n", &par->sight[0]);
	fscanf(fv, "Sight 1 = %f\n", &par->sight[1]);
	fscanf(fv, "Sight 2 = %f\n", &par->sight[2]);
	fscanf(fv, "Sight 3 = %f\n", &par->sight[3]);
	fscanf(fv, "Cam Pitch 0 = %f\n", &par->pitch[0]);
	fscanf(fv, "Cam Pitch 1 = %f\n", &par->pitch[1]);
	fscanf(fv, "Cam Pitch 2 = %f\n", &par->pitch[2]);
	fscanf(fv, "Cam Pitch 3 = %f\n", &par->pitch[3]);
	fscanf(fv, "Cam Roll 0 = %f\n", &par->roll[0]);
	fscanf(fv, "Cam Roll 1 = %f\n", &par->roll[1]);
	fscanf(fv, "Cam Roll 2 = %f\n", &par->roll[2]);
	fscanf(fv, "Cam Roll 3 = %f\n", &par->roll[3]);
	fscanf(fv, "Cam Yaw 0 = %f\n", &par->yaw[0]);
	fscanf(fv, "Cam Yaw 1 = %f\n", &par->yaw[1]);
	fscanf(fv, "Cam Yaw 2 = %f\n", &par->yaw[2]);
	fscanf(fv, "Cam Yaw 3 = %f\n", &par->yaw[3]);
	fscanf(fv, "Blind Dist 0 = %f\n", &par->blindDist[0]);
	fscanf(fv, "Blind Dist 1 = %f\n", &par->blindDist[1]);
	fscanf(fv, "Blind Dist 2 = %f\n", &par->blindDist[2]);
	fscanf(fv, "Blind Dist 3 = %f\n", &par->blindDist[3]);
	fscanf(fv, "Pattern Size = %f\n", &par->pattern);
	fscanf(fv, "Angle Range = %f %f %f\n", &par->angleRange[0], &par->angleRange[1], &par->angleRange[2]);
	fscanf(fv, "Angle Step = %f %f %f\n", &par->angleStep[0], &par->angleStep[1], &par->angleStep[2]);
	fscanf(fv, "Cam mirror = %d\n", &par->mirror);
	fscanf(fv, "Mid Cam Height = %f\n", &par->midCamHeight);
	fscanf(fv, "Vir Cam Height = %f\n", &par->virCamHeight);
	fscanf(fv, "Vir Cam Offset = %f %f\n", &par->virCamOffset[0], &par->virCamOffset[1]);

	return 1;
}

// save vehicle parameters
void saveVehParam(FILE *fv, VehParam *vPar)
{
	int i;
	char buf[300];

	fprintf(fv, "Cam ID = %d %d %d %d\n", vPar->camID[0], vPar->camID[1], vPar->camID[2], vPar->camID[3]);
	fprintf(fv, "Car Type = %s\n", vPar->carType);
	fprintf(fv, "\n");

	fprintf(fv, "Cam Height 0 = %f\n", vPar->camHeight[0]);
	fprintf(fv, "Cam Height 1 = %f\n", vPar->camHeight[1]);
	fprintf(fv, "Cam Height 2 = %f\n", vPar->camHeight[2]);
	fprintf(fv, "Cam Height 3 = %f\n", vPar->camHeight[3]);
	fprintf(fv, "\n");

	fprintf(fv, "Cam Offset 0 = %f %f\n", vPar->camOffset[0][0], vPar->camOffset[0][1]);
	fprintf(fv, "Cam Offset 1 = %f %f\n", vPar->camOffset[1][0], vPar->camOffset[1][1]);
	fprintf(fv, "Cam Offset 2 = %f %f\n", vPar->camOffset[2][0], vPar->camOffset[2][1]);
	fprintf(fv, "Cam Offset 3 = %f %f\n", vPar->camOffset[3][0], vPar->camOffset[3][1]);
	fprintf(fv, "\n");

	fprintf(fv, "Sight 0 = %f\n", vPar->sight[0]);
	fprintf(fv, "Sight 1 = %f\n", vPar->sight[1]);
	fprintf(fv, "Sight 2 = %f\n", vPar->sight[2]);
	fprintf(fv, "Sight 3 = %f\n", vPar->sight[3]);
	fprintf(fv, "\n");
	fprintf(fv, "Cam Pitch 0 = %f\n", vPar->pitch[0]);
	fprintf(fv, "Cam Pitch 1 = %f\n", vPar->pitch[1]);
	fprintf(fv, "Cam Pitch 2 = %f\n", vPar->pitch[2]);
	fprintf(fv, "Cam Pitch 3 = %f\n", vPar->pitch[3]);
	fprintf(fv, "\n");
	fprintf(fv, "Cam Roll 0 = %f\n", vPar->roll[0]);
	fprintf(fv, "Cam Roll 1 = %f\n", vPar->roll[1]);
	fprintf(fv, "Cam Roll 2 = %f\n", vPar->roll[2]);
	fprintf(fv, "Cam Roll 3 = %f\n", vPar->roll[3]);
	fprintf(fv, "\n");
	fprintf(fv, "Cam Yaw 0 = %f\n", vPar->yaw[0]);
	fprintf(fv, "Cam Yaw 1 = %f\n", vPar->yaw[1]);
	fprintf(fv, "Cam Yaw 2 = %f\n", vPar->yaw[2]);
	fprintf(fv, "Cam Yaw 3 = %f\n", vPar->yaw[3]);
	fprintf(fv, "\n");
	fprintf(fv, "Blind Dist 0 = %f\n", vPar->blindDist[0]);
	fprintf(fv, "Blind Dist 1 = %f\n", vPar->blindDist[1]);
	fprintf(fv, "Blind Dist 2 = %f\n", vPar->blindDist[2]);
	fprintf(fv, "Blind Dist 3 = %f\n", vPar->blindDist[3]);
	fprintf(fv, "\n");
	fprintf(fv, "Pattern Size = %f\n", vPar->pattern);
	fprintf(fv, "Angle Range = %f %f %f\n", vPar->angleRange[0], vPar->angleRange[1], vPar->angleRange[2]);
	fprintf(fv, "Angle Step = %f %f %f\n", vPar->angleStep[0], vPar->angleStep[1], vPar->angleStep[2]);
	fprintf(fv, "Cam mirror = %d\n", vPar->mirror);

	fprintf(fv, "\n");
	fprintf(fv, "Mid Cam Height = %f\n", vPar->midCamHeight);
	fprintf(fv, "Vir Cam Height = %f\n", vPar->virCamHeight);
	fprintf(fv, "Vir Cam Offset = %f %f\n", vPar->virCamOffset[0], vPar->virCamOffset[1]);

	return;
}
