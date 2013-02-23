#ifndef _PANO_VO_H_
#define _PANO_VO_H_

#include <stdio.h>
#include <stdlib.h>
#include "AlgBasic.h"
#include "jssjIUD.h"
#include "jssjVSM.h"

typedef struct  
{
	int width;			// ԭͼ���
	int height;
	int gndWidth;		// ����ͼ���
	int gndHeight;



	// IUD(image undistortion) ��ģ��
	JSDJ_IUDHandle iudHdl;
	JSDJ_IUDParam iudParam;
	JSDJ_IUDVar iudVar;

	VehParam par;
	
	int *map[VSM_CAM_NUM];
	int *map_op[VSM_CAM_NUM];
	int *map_opc[VSM_CAM_NUM];
	MapData *mapdata[VSM_CAM_NUM];
	jU8 *label;
	jU8 *frontLabel, *rearLabel;
	jU8 *label2;

	
} PanoVO;

void pvoCreate(PanoVO **pvo);

void pvoProcess(PanoVO *pvo);

void pvoRelease(PanoVO *pvo);

#endif