
#include "stdio.h"
#include "PanoVO.h"

main()
{
	FILE *fv, *fcam, *fcar;
	if ((fv = fopen("vehicle.txt", "rt")) == NULL)
	{
		MessageBox("参数文件不存在，程序无法运行！\n");
		return TRUE;
	}
	if ((fcam = fopen("cam.txt", "rt")) == NULL)
	{
		MessageBox("摄像头文件不存在，程序无法运行！\n");
		return TRUE;
	}
	if ((fcar = fopen("car.txt", "rt")) == NULL)
	{
		MessageBox("汽车文件不存在，程序无法运行！\n");
		return TRUE;
	}

	if (loadVehParam(fv, fcam, fcar, &vsmParam.vPar) < 0)
	{
		MessageBox("参数文件有错误，程序无法运行！\n");
		return TRUE;
	}
	fclose(fv);
	fclose(fcar);
	fclose(fcam);

}
