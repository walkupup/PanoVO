

/*****************************************************************
Copyright (C), 2011-2020, iCare Vision Tech. Co., Ltd.
All rights reserved

FileName: jssjVSM.h
Description: Vehicle Surrounding Monitor (VSM) 车辆全景图 头文件

History:
<author>		<time>		<version>		<Abstract>
杨力 　　　	   11-12-08      1.0.0			创建此文件
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

//输入图像分辨率
#define IMAGE_TYPE 0      //0 = cif 1 = HD1
//标定图像分辨率
#define UNDISTORT_IMAGE_TYPE 1 //0 = cif 1 = D1
#define VSM_CALIB_RES_X 704
#define VSM_CALIB_RES_Y 576

// 输入图像格式
#define JSSJ_COLOR_YUV422	1
#define JSSJ_COLOR_BGR24	2

//计算16字节对齐地址，主要是为了保证DSP移植时的兼容性
#define IVS_ALIGN_16BYTE(x) ((jU8*)(((jU32)(x) + 15) >> 4 << 4))
#define VSM_CAM_NUM 4		// 摄像机个数
#define VSM_IMG_CHANNEL 2	// 中间运算的图像通道数
#define VSM_IMG_W_OUT	480	// 输出图像宽度
#define VSM_IMG_H_OUT	480	// 输出图像高度

// 全景图视角
#define VSM_VIEW_TOP	1
#define VSM_VIEW_TOP2	2
#define VSM_VIEW_FRONT	3
#define VSM_VIEW_REAR	4

// 第一次使用时调整相机的方式：不调整、自动调整、手动调整
#define VSM_NO_ADJUST 0
#define VSM_AUTO_ADJUST_CAM 1 
#define VSM_MAN_ADJUST_CAM 2
#define VSM_MAN_ADJUST_CAM_FAST 3
#define VSM_ADJUST_CAM_FINISH 4

// 调整相机角度
#define VSM_ADJ_PITCH	0
#define VSM_ADJ_ROLL	1
#define VSM_ADJ_YAW		2

// vehicle 参数
typedef struct  
{
	float vehLen;							// 车身长度
	float vehWidth;						// 车身宽度
	float sight[VSM_CAM_NUM];
	float frontSight[VSM_CAM_NUM];			// 前视全景图视野范围，单位米，汽车左前右后顺序
	float rearSight[VSM_CAM_NUM];			// 后视全景图视野范围，单位米，汽车左前右后顺序
	float camHeight[VSM_CAM_NUM];
	float pitch[VSM_CAM_NUM];
	float roll[VSM_CAM_NUM];
	float yaw[VSM_CAM_NUM];
	float camOffset[VSM_CAM_NUM][2];		// 俯视图上，向下偏离为正，向右偏离为正。
	float pattern;
	float angleRange[3];
	float angleStep[3];

	float intrinParam[VSM_CAM_NUM][9];	// 3x3 内参矩阵
	float distortParam[VSM_CAM_NUM][8];	// 畸变系数
	int	mirror;

	// other
	int camID[VSM_CAM_NUM];					// 相机编号
	char carType[20];						// 车型号

	//blind dist
	float blindDist[VSM_CAM_NUM];

	// multi view
	float midCamHeight;
	float virCamHeight;
	float virCamOffset[2];
} VehParam;

typedef struct 
{
	jU16 uwWidth;					// 输入图像宽
	jU16 uwHeight;					// 输入图像高
	jU16 uwWidthOut;
	jU16 uwHeightOut;
	jU16 uwWidthOut2;				// 正上方鱼眼图宽高
	jU16 uwHeightOut2;				
	jU16 uwVirWidth;				// 多视角全景图宽高
	jU16 uwVirHeight;
	VehParam *par;					// 汽车参数指针，置为NULL

	//以上成员用于计算内存大小函数
	jU32 udwBufLen;					//缓冲块大小
	jU8  *pubyRAMBuf;				//算法所需的缓冲块
} JSDJ_VSMHandle;

//配置参数结构体
typedef struct 
{
	jU32 udwAlgFlag;				//算法名称标记
	jU32 udwVersion;				//算法版本信息——仅对外算法接口中有用
	jU32 udwResetFlag;				//复位标记，传VehParam参数时须复位
	jU32 udwImgFormat;				// 输入图像格式

	// 相机调整参数
	jU32 udwAdjustCam;				// 自动或手动调整相机
	jU32 udwAdjustCamNum;			// 手动调相机编号
	jU32 udwAdjustCamDirect;		// pitch or roll
	jS32 udwAdjustCamStep;			// 调整大小，单位度

	// 自动调整参数
	jU8 *pubyImg[VSM_CAM_NUM];		//图像数据指针——输入

	jU32 udwSaveParam;				// 调整相机完成，保存数据到ROM
	VehParam vPar;					// 车辆参数

	//汽车图像
	jU16 uwCarWidth;				//汽车图像宽高
	jU16 uwCarHeight;
	jU8 *pubyCar;					//汽车图像

	jU32 udwALGSwitch;				//IUD+MIS/AFI  切换标记 1 MIS 0 AFI 
	jU32 udwALGTip;					//置顶切换
	jU32 udwViewSwitch;				// 视角转换
} JSDJ_VSMParam;	

//输入参数结构体
typedef struct 
{
	jU32 udwN;						//输入图像帧数
	jS32 dwDisplayMode;			//手动调整状态，1 是 0 否
	jS32 dwMarkControl;				//鸟瞰图加入标尺线，1 是 0 否
	jU8 *pubyImg[VSM_CAM_NUM];		//图像数据指针——输入
} JSDJ_VSMVarIn;

//输出参数结构体
typedef struct 
{
	jU32 udwWidthOut;				// 输出图像宽
	jU32 udwHeightOut;				// 输出图像高
	jU8 *pubyImgCombine;			//合并图像数据指针——输出
	jU8 *pubyAlarm;					//AFI触警信号——输出 0 无 1 有
} JSDJ_VSMVarOut;

//////////////////////////////算法接口定义////////////////////////////////////////////

jS32 JSSJ_VSM_Init(JSDJ_VSMHandle *pdjHandle);

jS32 JSSJ_VSM_Process(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMVarIn *pdjVar, JSDJ_VSMVarOut *pdjVarOut);

jS32 JSSJ_VSM_CalcMemSize(JSDJ_VSMHandle *pdjHandle);

jS32 JSSJ_VSM_SetConfig(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMParam *pdjParam);

jS32 JSSJ_VSM_GetConfig(JSDJ_VSMHandle *pdjHandle, JSDJ_VSMParam *pdjParam);

jCh8* JSSJ_VSM_GetVersion(jCh8 *pchVer);

jS32 JSSJ_VSM_Exit(JSDJ_VSMHandle *pdjHandle);

#endif
