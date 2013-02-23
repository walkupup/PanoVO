/*****************************************************************
Copyright (C), 2011-2020, iCare Vision Tech. Co., Ltd.
All rights reserved

FileName: jssjIVSPublic.h
Description: 所有子算法共用的头

History:
<author>		<time>		<version>		<Abstract>
lyhe　　　	  2011-05-23     2.6.0			创建该文件
*****************************************************************/

#ifndef _IVSPUBLIC_H_
#define _IVSPUBLIC_H_

#include "jssjBaseType.h"

//16字节对齐宏
#define IVS_ALIGN_16BYTE(x) ((jU8*)(((jU32)(x) + 15) >> 4 << 4))

#define JSSJ_MIN(x, y)			((x) < (y) ? (x) : (y))
#define JSSJ_MAX(x, y)			((x) > (y) ? (x) : (y))
#define JSSJ_PI					3.1415926

#ifdef _ALG_PC_
#pragma warning(disable:4311 4312 4244 4996 4018)
#endif


#define		VERSION_ALG		"v1.0.0"		//算法版本号
#define		PARAM_VER		(0x01000000)	//参数版本号

#define JSERR_COM_OK		0				//没有错误
#define JSERR_COM_NOBUF		0x80000000		//没有缓存
#define JSERR_COM_LESSBUF	0x80000001		//缓存不够
#define JSERR_COM_NODATA	0x80000002		//没有图像数据
#define JSERR_COM_BADROI	0x80000003		//错误的ROI区域
#define JSERR_COM_BADSIZE	0x80000004		//图像尺寸错误
#define JSERR_COM_BADPRM	0x80000005		//配置参数错误
#define JSERR_COM_BADVER	0x80000006		//参数结构体版本不匹配


//错误类型字符串，同上面的宏一一对应
#define ERRSTR_COM_OK			"OK!"
#define ERRSTR_COM_NOBUF		"No buffer input!"
#define ERRSTR_COM_LESSBUF		"Lack of buffer length!"
#define ERRSTR_COM_NODATA		"No image data!"
#define ERRSTR_COM_BADROI		"The setting ROI is incorrect!"
#define ERRSTR_COM_BADSIZE		"The size of image is incorrect!"
#define ERRSTR_COM_BADPRM		"Parameters are inaccurate!"
#define ERRSTR_COM_BADVER		"The version of parameter is unmatched!"


#endif
