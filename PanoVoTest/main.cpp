
#include "stdio.h"
#include "PanoVO.h"

main()
{
	FILE *fv, *fcam, *fcar;
	if ((fv = fopen("vehicle.txt", "rt")) == NULL)
	{
		MessageBox("�����ļ������ڣ������޷����У�\n");
		return TRUE;
	}
	if ((fcam = fopen("cam.txt", "rt")) == NULL)
	{
		MessageBox("����ͷ�ļ������ڣ������޷����У�\n");
		return TRUE;
	}
	if ((fcar = fopen("car.txt", "rt")) == NULL)
	{
		MessageBox("�����ļ������ڣ������޷����У�\n");
		return TRUE;
	}

	if (loadVehParam(fv, fcam, fcar, &vsmParam.vPar) < 0)
	{
		MessageBox("�����ļ��д��󣬳����޷����У�\n");
		return TRUE;
	}
	fclose(fv);
	fclose(fcar);
	fclose(fcam);

}
