

/*****************************************************************
Copyright (C), 2011-2020, iCare Vision Tech. Co., Ltd.
All rights reserved

FileName: jssjVSM.h
Description: Vehicle Surrounding Monitor (VSM) ����ȫ��ͼ ͷ�ļ�

History:
<author>		<time>		<version>		<Abstract>
���� ������	   11-12-08      1.0.0			�������ļ�
*****************************************************************/

#ifndef _JSSJ_VSM_H_
#define _JSSJ_VSM_H_


#include "jssjPublic.h"
#ifndef _ALG_PC_
#include "jssjCV.h"
#define CV_SHOW_IMG(w, h, data, channels, winname)	
#else
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#define CV_SHOW_IMG(w, h, data, channels, winname)					\
{																\
	CvSize size;												\
	IplImage * img_;												\
	size.width = w;												\
	size.height = h;											\
	img_ = cvCreateImageHeader(size, IPL_DEPTH_8U, channels);					\
	img_->imageData = (char *)data;										\
	cvNamedWindow(winname, CV_WINDOW_AUTOSIZE);				\
	cvShowImage(winname, img_);								\
	cvReleaseImageHeader(&img_);									\
}
#endif

//����ͼ��ֱ���
#define IMAGE_TYPE 0      //0 = cif 1 = HD1
//�궨ͼ��ֱ���
#define UNDISTORT_IMAGE_TYPE 1 //0 = cif 1 = D1
#define VSM_CALIB_RES_X 704
#define VSM_CALIB_RES_Y 576

// ����ͼ���ʽ
#define JSSJ_COLOR_YUV422	1
#define JSSJ_COLOR_BGR24	2

//����16�ֽڶ����ַ����Ҫ��Ϊ�˱�֤DSP��ֲʱ�ļ�����
#define IVS_ALIGN_16BYTE(x) ((jU8*)(((jU32)(x) + 15) >> 4 << 4))
#define VSM_CAM_NUM 4		// ���������
#define VSM_IMG_CHANNEL 2	// �м������ͼ��ͨ����
#define VSM_IMG_W_OUT	480	// ���ͼ����
#define VSM_IMG_H_OUT	480	// ���ͼ��߶�

// ȫ��ͼ�ӽ�
#define VSM_VIEW_TOP	1
#define VSM_VIEW_TOP2	2
#define VSM_VIEW_FRONT	3
#define VSM_VIEW_REAR	4

// ��һ��ʹ��ʱ��������ķ�ʽ�����������Զ��������ֶ�����
#define VSM_NO_ADJUST 0
#define VSM_AUTO_ADJUST_CAM 1 
#define VSM_MAN_ADJUST_CAM 2
#define VSM_MAN_ADJUST_CAM_FAST 3
#define VSM_ADJUST_CAM_FINISH 4

// ��������Ƕ�
#define VSM_ADJ_PITCH	0
#define VSM_ADJ_ROLL	1
#define VSM_ADJ_YAW		2

// vehicle ����
typedef struct  
{
	float vehLen;							// ������
	float vehWidth;						// ������
	float sight[VSM_CAM_NUM];
	float frontSight[VSM_CAM_NUM];			// ǰ��ȫ��ͼ��Ұ��Χ����λ�ף�������ǰ�Һ�˳��
	float rearSight[VSM_CAM_NUM];			// ����ȫ��ͼ��Ұ��Χ����λ�ף�������ǰ�Һ�˳��
	float camHeight[VSM_CAM_NUM];
	float pitch[VSM_CAM_NUM];
	float roll[VSM_CAM_NUM];
	float yaw[VSM_CAM_NUM];
	float camOffset[VSM_CAM_NUM][2];		// ����ͼ�ϣ�����ƫ��Ϊ��������ƫ��Ϊ����
	float pattern;
	float angleRange[3];
	float angleStep[3];

	float intrinParam[VSM_CAM_NUM][9];	// 3x3 �ڲξ���
	float distortParam[VSM_CAM_NUM][8];	// ����ϵ��
	int	mirror;

	// other
	int camID[VSM_CAM_NUM];					// ������
	char carType[20];						// ���ͺ�

	//blind dist
	float blindDist[VSM_CAM_NUM];

	// multi view
	float midCamHeight;
	float virCamHeight;
	float virCamOffset[2];
} VehParam;

typedef struct 
{
	jU16 uwWidth;					// ����ͼ���
	jU16 uwHeight;					// ����ͼ���
	jU16 uwWidthOut;
	jU16 uwHeightOut;
	jU16 uwWidthOut2;				// ���Ϸ�����ͼ���
	jU16 uwHeightOut2;				
	jU16 uwVirWidth;				// ���ӽ�ȫ��ͼ���
	jU16 uwVirHeight;
	VehParam *par;					// ��������ָ�룬��ΪNULL

	//���ϳ�Ա���ڼ����ڴ��С����
	jU32 udwBufLen;					//������С
	jU8  *pubyRAMBuf;				//�㷨����Ļ����
} JSDJ_VSMHandle;

//���ò����ṹ��
typedef struct 
{
	jU32 udwAlgFlag;				//�㷨���Ʊ��
	jU32 udwVersion;				//�㷨�汾��Ϣ�����������㷨�ӿ�������
	jU32 udwResetFlag;				//��λ��ǣ���VehParam����ʱ�븴λ
	jU32 udwImgFormat;				// ����ͼ���ʽ

	// �����������
	jU32 udwAdjustCam;				// �Զ����ֶ��������
	jU32 udwAdjustCamNum;			// �ֶ���������
	jU32 udwAdjustCamDirect;		// pitch or roll
	jS32 udwAdjustCamStep;			// ������С����λ��

	// �Զ���������
	jU8 *pubyImg[VSM_CAM_NUM];		//ͼ������ָ�롪������

	jU32 udwSaveParam;				// ���������ɣ��������ݵ�ROM
	VehParam vPar;					// ��������

	//����ͼ��
	jU16 uwCarWidth;				//����ͼ����
	jU16 uwCarHeight;
	jU8 *pubyCar;					//����ͼ��

	jU32 udwALGSwitch;				//IUD+MIS/AFI  �л���� 1 MIS 0 AFI 
	jU32 udwALGTip;					//�ö��л�
	jU32 udwViewSwitch;				// �ӽ�ת��
} JSDJ_VSMParam;	

//��������ṹ��
typedef struct 
{
	jU32 udwN;						//����ͼ��֡��
	jS32 dwDisplayMode;			//�ֶ�����״̬��1 �� 0 ��
	jS32 dwMarkControl;				//���ͼ�������ߣ�1 �� 0 ��
	jU8 *pubyImg[VSM_CAM_NUM];		//ͼ������ָ�롪������
} JSDJ_VSMVarIn;

//��������ṹ��
typedef struct 
{
	jU32 udwWidthOut;				// ���ͼ���
	jU32 udwHeightOut;				// ���ͼ���
	jU8 *pubyImgCombine;			//�ϲ�ͼ������ָ�롪�����
	jU8 *pubyAlarm;					//AFI�����źš������ 0 �� 1 ��
} JSDJ_VSMVarOut;

//////////////////////////////�㷨�ӿڶ���////////////////////////////////////////////

jS32 JSSJ_VSM_Init(JSDJ_VSMHandle *pdjHandle);

jS32 JSSJ_VSM_Process(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMVarIn *pdjVar, JSDJ_VSMVarOut *pdjVarOut);

jS32 JSSJ_VSM_CalcMemSize(JSDJ_VSMHandle *pdjHandle);

jS32 JSSJ_VSM_SetConfig(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMParam *pdjParam);

jS32 JSSJ_VSM_GetConfig(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMParam *pdjParam);

jCh8* JSSJ_VSM_GetVersion(jCh8 *pchVer);

jS32 JSSJ_VSM_Exit(JSDJ_VSMHandle *pdjHandle);

#endif
