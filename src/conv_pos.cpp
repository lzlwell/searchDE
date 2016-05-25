#include"conv_pos.h"

void dir2car(double *dir, double *car, double **latt)
{
	car[0] = dir[0]*latt[0][0] + dir[1]*latt[1][0] + dir[2]*latt[2][0];
	car[1] = dir[0]*latt[0][1] + dir[1]*latt[1][1] + dir[2]*latt[2][1];
	car[2] = dir[0]*latt[0][2] + dir[1]*latt[1][2] + dir[2]*latt[2][2];
	return;
}

void inv_latt(double **latt, double **invLatt)
{
	double a11, a12, a13, a21, a22, a23, a31, a32, a33;
	double d11, d12, d13, d21, d22, d23, d31, d32, d33, detA;

	a11 = latt[0][0]; a12 = latt[0][1]; a13 = latt[0][2];
	a21 = latt[1][0]; a22 = latt[1][1]; a23 = latt[1][2];
	a31 = latt[2][0]; a32 = latt[2][1]; a33 = latt[2][2];

	d11 = a22*a33 - a23*a32;
	d21 = a21*a33 - a23*a31;
	d31 = a21*a32 - a22*a31;
	d12 = a12*a33 - a13*a32;
	d22 = a11*a33 - a13*a31;
	d32 = a11*a32 - a12*a31;
	d13 = a12*a23 - a13*a22;
	d23 = a11*a23 - a13*a21;
	d33 = a11*a22 - a12*a21;
	d12 *= -1; d21 *= -1; d23 *= -1; d32 *= -1;
	detA = a11*a22*a33 + a12*a23*a31 + a21*a32*a13 - a13*a22*a31 - a23*a32*a11 - a12*a21*a33;

	invLatt[0][0] = d11/detA; invLatt[0][1] = d12/detA; invLatt[0][2] = d13/detA;
	invLatt[1][0] = d21/detA; invLatt[1][1] = d22/detA; invLatt[1][2] = d23/detA;
	invLatt[2][0] = d31/detA; invLatt[2][1] = d32/detA; invLatt[2][2] = d33/detA;

	return;
}

void car2dir(double *car, double *dir, double **latt)
{
	double **invLatt;
	invLatt = new_array(3);
	
	inv_latt(latt, invLatt);

    dir[0] = car[0]*invLatt[0][0] + car[1]*invLatt[1][0] + car[2]*invLatt[2][0];
    dir[1] = car[0]*invLatt[0][1] + car[1]*invLatt[1][1] + car[2]*invLatt[2][1];
    dir[2] = car[0]*invLatt[0][2] + car[1]*invLatt[1][2] + car[2]*invLatt[2][2];

	del_array(invLatt, 3);

    return;
}

void cs2psoU(parameter *paras, cryStruct *oneCS, psoUnit *psoU)
{
	double **buffCarH, **buffCarL, **optCar, **lattBuffH, **lattBuffL, **lattOpt;
	double buffBot, buffTop, optBot, optTop;
	int i, j;

	buffCarH = new_array(paras->nBuffH);
	buffCarL = new_array(paras->nBuffL);
	optCar = new_array(paras->nOpt);
	lattBuffH = new_array(3);
	lattBuffL = new_array(3);
	lattOpt = new_array(3);
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			lattBuffH[i][j] = oneCS->latt[i][j];
			lattBuffL[i][j] = oneCS->latt[i][j];
			lattOpt[i][j] = oneCS->latt[i][j];
		}
	}
	lattBuffH[2][2] = paras->buffTop - paras->optTop;
	lattBuffL[2][2] = paras->optBot - paras->buffBot;
	lattOpt[2][2] = oneCS->optH;
	
	buffBot = paras->buffBot;
	optBot = paras->optBot;
	buffTop = optBot + lattOpt[2][2] + lattBuffH[2][2];
	optTop = optBot + lattOpt[2][2];

	for(i=0; i < paras->nBuffH; i++)
	{
		dir2car(oneCS->buffPosH[i], buffCarH[i], oneCS->latt);
		buffCarH[i][2] -= optTop;
		car2dir(buffCarH[i], psoU->buffPosH[i], lattBuffH);
		psoU->buffPosH[i][0] -= oneCS->transA;
		psoU->buffPosH[i][1] -= oneCS->transB;
		if(psoU->buffPosH[i][0] >= 1.0)
			psoU->buffPosH[i][0] --;
		else if(psoU->buffPosH[i][0] <= 0.0)
			psoU->buffPosH[i][0] ++;
		if(psoU->buffPosH[i][1] >= 1.0)
			psoU->buffPosH[i][1] --;
		else if(psoU->buffPosH[i][1] <= 0.0)
			psoU->buffPosH[i][1] ++;
	}
	for(i=0; i < paras->nBuffL; i++)
	{
		dir2car(oneCS->buffPosL[i], buffCarL[i], oneCS->latt);
		buffCarL[i][2] -= buffBot;
		car2dir(buffCarL[i], psoU->buffPosL[i], lattBuffL);
	}
	for(i=0; i < paras->nOpt; i++)
	{
		dir2car(oneCS->optPos[i], optCar[i], oneCS->latt);
		optCar[i][2] -= optBot;
		car2dir(optCar[i], psoU->optPos[i], lattOpt);
	}

	psoU->optH = oneCS->optH;
	psoU->transA = oneCS->transA;
	psoU->transB = oneCS->transB;
	psoU->energy = oneCS->energy;

	del_array(buffCarH, paras->nBuffH);
	del_array(buffCarL, paras->nBuffL);
	del_array(optCar, paras->nOpt);
	del_array(lattBuffH, 3);
	del_array(lattBuffL, 3);
	del_array(lattOpt, 3);
	
	return;
}

void psoU2cs(parameter *paras, cryStruct *oriCS, psoUnit *psoU, cryStruct *oneCS)
{
	double **fixCarH, **fixCarL, **buffCarH, **buffCarL, **optCar, **lattBuffH, **lattBuffL, **lattOpt, **latt;
	double buffBot, buffTop, optBot, optTop;
	int i, j;

	fixCarH = new_array(paras->nFixH);
	fixCarL = new_array(paras->nFixL);
	buffCarH = new_array(paras->nBuffH);
	buffCarL = new_array(paras->nBuffL);
	optCar = new_array(paras->nOpt);
	lattBuffH = new_array(3);
	lattBuffL = new_array(3);
	lattOpt = new_array(3);
	latt = new_array(3);
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			lattBuffH[i][j] = oriCS->latt[i][j];
			lattBuffL[i][j] = oriCS->latt[i][j];
			lattOpt[i][j] = oriCS->latt[i][j];
			latt[i][j] = oriCS->latt[i][j];
		}
	}
	lattBuffH[2][2] = paras->buffTop - paras->optTop;
	lattBuffL[2][2] = paras->optBot - paras->buffBot;
	lattOpt[2][2] = psoU->optH;
	if(paras->interface == 1)
		latt[2][2] = latt[2][2] - (paras->optTop - paras->optBot) + psoU->optH;
	else if(paras->interface == 2)
		latt[2][2] = oriCS->latt[2][2];

	buffBot = paras->buffBot;
	optBot = paras->optBot;
	buffTop = optBot + lattOpt[2][2] + lattBuffH[2][2];
	optTop = optBot + lattOpt[2][2];

	for(i=0; i < paras->nFixH; i++)
	{
		dir2car(oriCS->fixPosH[i], fixCarH[i], oriCS->latt);
		fixCarH[i][2] = fixCarH[i][2] - paras->buffTop + buffTop;
		car2dir(fixCarH[i], oneCS->fixPosH[i], latt);
		oneCS->fixPosH[i][0] += psoU->transA;
		oneCS->fixPosH[i][1] += psoU->transB;
		if(oneCS->fixPosH[i][0] >= 1.0)
			oneCS->fixPosH[i][0] --;
		else if(oneCS->fixPosH[i][0] <= 0.0)
			oneCS->fixPosH[i][0] ++;
		if(oneCS->fixPosH[i][1] >= 1.0)
			oneCS->fixPosH[i][1] --;
		else if(oneCS->fixPosH[i][1] <= 0.0)
			oneCS->fixPosH[i][1] ++;
	}
	for(i=0; i < paras->nFixL; i++)
	{
		dir2car(oriCS->fixPosL[i], fixCarL[i], oriCS->latt);
		car2dir(fixCarL[i], oneCS->fixPosL[i], latt);
	}
	for(i=0; i < paras->nBuffH; i++)
	{
		dir2car(psoU->buffPosH[i], buffCarH[i], lattBuffH);
		buffCarH[i][2] += optTop;
		car2dir(buffCarH[i], oneCS->buffPosH[i], latt);
		oneCS->buffPosH[i][0] += psoU->transA;
		oneCS->buffPosH[i][1] += psoU->transB;
		if(oneCS->buffPosH[i][0] >= 1.0)
			oneCS->buffPosH[i][0] --;
		else if(oneCS->buffPosH[i][0] <= 0.0)
			oneCS->buffPosH[i][0] ++;
		if(oneCS->buffPosH[i][1] >= 1.0)
			oneCS->buffPosH[i][1] --;
		else if(oneCS->buffPosH[i][1] <= 0.0)
			oneCS->buffPosH[i][1] ++;
	}
	for(i=0; i < paras->nBuffL; i++)
	{
		dir2car(psoU->buffPosL[i], buffCarL[i], lattBuffL);
		buffCarL[i][2] += buffBot;
		car2dir(buffCarL[i], oneCS->buffPosL[i], latt);
	}
	for(i=0; i < paras->nOpt; i++)
	{
		dir2car(psoU->optPos[i], optCar[i], lattOpt);
		optCar[i][2] += optBot;
		car2dir(optCar[i], oneCS->optPos[i], latt);
	}

	cp_string_A2B(oriCS->fixTpH, oneCS->fixTpH, paras->nFixH);
	cp_string_A2B(oriCS->fixTpL, oneCS->fixTpL, paras->nFixL);
	cp_string_A2B(oriCS->buffTpH, oneCS->buffTpH, paras->nBuffH);
	cp_string_A2B(oriCS->buffTpL, oneCS->buffTpL, paras->nBuffL);
	cp_string_A2B(oriCS->optTp, oneCS->optTp, paras->nOpt);

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			oneCS->latt[i][j] = latt[i][j];
	oneCS->optH = psoU->optH;
	oneCS->transA = psoU->transA;
	oneCS->transB = psoU->transB;
	oneCS->energy = psoU->energy;

	del_array(fixCarH, paras->nFixH);
	del_array(fixCarL, paras->nFixL);
	del_array(buffCarH, paras->nBuffH);
	del_array(buffCarL, paras->nBuffL);
	del_array(optCar, paras->nOpt);
	del_array(lattBuffH, 3);
	del_array(lattBuffL, 3);
	del_array(lattOpt, 3);
	del_array(latt, 3);
	
	return;
}
