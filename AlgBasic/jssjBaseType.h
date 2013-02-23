/************************************************************************
Copyright(C),2000-2008,JSSJ Tech.Co.,Ltd.
FileName: jssjBaseType.h
Author: 张明	Date: 2008-6-10
Description:

History:
<author>		<time>		<version>		<desc>
张明　　　　　2008-6-10      1.0.0        创建此文件
************************************************************************/

#ifndef JSSJ_BASECODE_H
#define JSSJ_BASECODE_H


//基本数据类型
#define jU8 unsigned char               //8bit无符号数
#define jU16 unsigned short             //16bit无符号数
#define jU32 unsigned int				//32bit无符号数
#define jS8 signed char					//8bit有符号数
#define jCh8 char                       //8bit字符类型
#define jS16 short						//16bit有符号数
#define jS32 int						//32bit有符号数
#define jS64 long long					//32bit有符号数
#define jF32 float						//32bit浮点数
#define jF64 double						//64bit浮点数
#define jBool unsigned char				//布尔变量
#define jVoid void						//无意义数据类型


//二维数据点结构，jS16型
typedef struct JSSJ_Point2DS{
	jS16 x;
	jS16 y;
} JSSJ_Point2DS;


//二维数据点结构，jS32型
typedef struct JSSJ_Point2DD{
	jS32 x;
	jS32 y;
} JSSJ_Point2DD;












#endif



