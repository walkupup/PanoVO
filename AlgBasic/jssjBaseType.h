/************************************************************************
Copyright(C),2000-2008,JSSJ Tech.Co.,Ltd.
FileName: jssjBaseType.h
Author: ����	Date: 2008-6-10
Description:

History:
<author>		<time>		<version>		<desc>
��������������2008-6-10      1.0.0        �������ļ�
************************************************************************/

#ifndef JSSJ_BASECODE_H
#define JSSJ_BASECODE_H


//������������
#define jU8 unsigned char               //8bit�޷�����
#define jU16 unsigned short             //16bit�޷�����
#define jU32 unsigned int				//32bit�޷�����
#define jS8 signed char					//8bit�з�����
#define jCh8 char                       //8bit�ַ�����
#define jS16 short						//16bit�з�����
#define jS32 int						//32bit�з�����
#define jS64 long long					//32bit�з�����
#define jF32 float						//32bit������
#define jF64 double						//64bit������
#define jBool unsigned char				//��������
#define jVoid void						//��������������


//��ά���ݵ�ṹ��jS16��
typedef struct JSSJ_Point2DS{
	jS16 x;
	jS16 y;
} JSSJ_Point2DS;


//��ά���ݵ�ṹ��jS32��
typedef struct JSSJ_Point2DD{
	jS32 x;
	jS32 y;
} JSSJ_Point2DD;












#endif



