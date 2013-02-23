#include "PanoVO.h"

void pvoCreate(PanoVO **hdl, VehParam *par)
{
	int i;
	PanoVO *pvo;

	pvo = (PanoVO *)malloc(sizeof(PanoVO));

	pvo->width = 704;
	pvo->height = 576;
	pvo->gndWidth = 352;
	pvo->gndHeight = 480;


	pvo->iudHdl.uwWidth = pvo->width;
	pvo->iudHdl.uwHeight = pvo->height;
	pvo->iudHdl.uwWidthOut = pvo->gndWidth;
	pvo->iudHdl.uwHeightOut = pvo->gndHeight;
	pvo->iudHdl.uwVirWidth = 640;
	pvo->iudHdl.uwVirHeight = 480;
	pvo->iudHdl.uwWidthOut2 = 640;
	pvo->iudHdl.uwHeightOut2 = 480;

	pvo->iudHdl.par = par;
	pvo->iudHdl.pubyRAMBuf = (jU8 *)malloc(JSSJ_IUD_CalcMemSize(&pvo->iudHdl) + 100);

	if (JSSJ_IUD_Init(&pvo->iudHdl) < 0)
	{
		printf("iud initialization failed\n");
		return;
	}

	for (i = 0; i < VSM_CAM_NUM; i++)
	{
		pvo->map[i] = (int *)malloc(pvo->gndWidth * pvo->gndHeight);
		pvo->map[i] = (int *)malloc(pvo->gndWidth * pvo->gndHeight);
		pvo->map[i] = (int *)malloc(pvo->gndWidth * pvo->gndHeight);

	}




	// ¹«¹²»º´æ
	pvo->iudParam.udwBufLen = 10000;
	pvo->iudParam.pubyBuf = (jU8 *)malloc(pvo->iudParam.udwBufLen);
	pvo->iudParam.vPar = *par;
	for (i = 0; i < VSM_CAM_NUM; i++)
	{
		pvo->iudParam.map[i] = vsm->map[i];
		pvo->iudParam.map_op[i] = vsm->map_op[i];
		pvo->iudParam.map_opc[i] = vsm->map_opc[i];
		pvo->iudParam.mapdata[i] = vsm->mapdata[i];
	}
	pvo->iudParam.label = vsm->label;
	pvo->iudParam.frontLabel = vsm->frontLabel;
	pvo->iudParam.rearLabel = vsm->rearLabel;
	pvo->iudParam.label2 = vsm->label2;
	pvo->iudParam.udwViewSwitch = vsm->udwViewSwitch;
	pvo->iudParam.udwResetFlag = 0;
	pvo->iudParam.udwAdjustCam = pdjParam->udwAdjustCam;
	if (pdjParam->udwAdjustCam == VSM_MAN_ADJUST_CAM || pdjParam->udwAdjustCam == VSM_MAN_ADJUST_CAM_FAST)
	{
		pvo->iudParam.udwAdjustCamNum = pdjParam->udwAdjustCamNum;
		pvo->iudParam.udwAdjustCamDirect = pdjParam->udwAdjustCamDirect;
		pvo->iudParam.udwAdjustCamStep = pdjParam->udwAdjustCamStep;
	}
	else if (pdjParam->udwAdjustCam == VSM_AUTO_ADJUST_CAM)
	{
		for (i = 0; i < VSM_CAM_NUM; i++)
			pvo->iudParam.pubyImg[i] = pvo->pdjParam->pubyImg[i];		
	}
	JSSJ_IUD_SetConfig(&pvo->iudHdl, &pvo->iudParam);


	*hdl = pvo;
}

void pvoProcess(PanoVO *pvo)
{
	int i;
	/*
	for (i = 0; i < pdjVar->udwN; i++)
	{
		iudVar->pubyImg[i] = pdjVar->pubyImg[i];
	}
	iudVar->udwN = pdjVar->udwN;
	t0 = clock();
	JSSJ_IUD_Process(&vsm->iudHdl, &vsm->iudVar);
	t1 = clock();
	tx = (t1-t0)/594;
	printf("IUD is %d\n",tx);
*/
}

void pvoRelease(PanoVO *pvo)
{
	free(pvo->iudHdl.pubyRAMBuf);
}
