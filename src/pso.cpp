#include"pso.h"

void pso(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, double omega, cryStruct *oriCS)
{
	double r1, r2;
	int i, j, k;
	cryStruct *oneCS;
	oneCS = new_CS(paras);

	for(i=0; i < (int)(paras->size * paras->psoProp); i++)
	{
		for(j=0; j < paras->nBuffH; j++)
		{
			for(k=0; k<3; k++)
			{
				r1 = random;
				r2 = random;
				v[i]->buffPosH[j][k] = omega * v[i]->buffPosH[j][k] \
									   + 2.0 * r1 * (pbest[i]->buffPosH[j][k] - swarm[i]->buffPosH[j][k]) \
									   + 2.0 * r2 * (gbest->buffPosH[j][k] - swarm[i]->buffPosH[j][k]);
				if(v[i]->buffPosH[j][k] > fabs(vm->buffPosH[j][k]))
					v[i]->buffPosH[j][k] = fabs(vm->buffPosH[j][k]);
				else if(v[i]->buffPosH[j][k] < -1 * fabs(vm->buffPosH[j][k]))
					v[i]->buffPosH[j][k] = -1 * fabs(vm->buffPosH[j][k]);
				swarm[i]->buffPosH[j][k] += v[i]->buffPosH[j][k];
			}
		}

		for(j=0; j < paras->nBuffL; j++)
		{
			for(k=0; k<3; k++)
			{
				r1 = random;
				r2 = random;
				v[i]->buffPosL[j][k] = omega * v[i]->buffPosL[j][k] \
									   + 2.0 * r1 * (pbest[i]->buffPosL[j][k] - swarm[i]->buffPosL[j][k]) \
									   + 2.0 * r2 * (gbest->buffPosL[j][k] - swarm[i]->buffPosL[j][k]);
				if(v[i]->buffPosL[j][k] > fabs(vm->buffPosL[j][k]))
					v[i]->buffPosL[j][k] = fabs(vm->buffPosL[j][k]);
				else if(v[i]->buffPosL[j][k] < -1 * fabs(vm->buffPosL[j][k]))
					v[i]->buffPosL[j][k] = -1 * fabs(vm->buffPosL[j][k]);
				swarm[i]->buffPosL[j][k] += v[i]->buffPosL[j][k];
			}
		}

		for(j=0; j < paras->nOpt; j++)
		{
			for(k=0; k<3; k++)
			{
				r1 = random;
				r2 = random;
				v[i]->optPos[j][k] = omega * v[i]->optPos[j][k] \
									   + 2.0 * r1 * (pbest[i]->optPos[j][k] - swarm[i]->optPos[j][k]) \
									   + 2.0 * r2 * (gbest->optPos[j][k] - swarm[i]->optPos[j][k]);
				if(v[i]->optPos[j][k] > fabs(vm->optPos[j][k]))
					v[i]->optPos[j][k] = fabs(vm->optPos[j][k]);
				else if(v[i]->optPos[j][k] < -1 * fabs(vm->optPos[j][k]))
					v[i]->optPos[j][k] = -1 * fabs(vm->optPos[j][k]);
				swarm[i]->optPos[j][k] += v[i]->optPos[j][k];
			}
		}

		r1 = random;
		r2 = random;
		v[i]->optH = omega * v[i]->optH \
							 + 2.0 * r1 * (pbest[i]->optH - swarm[i]->optH) \
							 + 2.0 * r2 * (gbest->optH - swarm[i]->optH);
		if(v[i]->optH > fabs(vm->optH))
			v[i]->optH = fabs(vm->optH);
		else if(v[i]->optH < -1 * fabs(vm->optH))
			v[i]->optH = -1 * fabs(vm->optH);
		swarm[i]->optH += v[i]->optH;

		r1 = random;
		r2 = random;
		v[i]->transA = omega * v[i]->transA \
							 + 2.0 * r1 * (pbest[i]->transA - swarm[i]->transA) \
							 + 2.0 * r2 * (gbest->transA - swarm[i]->transA);
		if(v[i]->transA > fabs(vm->transA))
			v[i]->transA = fabs(vm->transA);
		else if(v[i]->transA < -1 * fabs(vm->transA))
			v[i]->transA = -1 * fabs(vm->transA);
		swarm[i]->transA += v[i]->transA;

		r1 = random;
		r2 = random;
		v[i]->transB = omega * v[i]->transB \
							 + 2.0 * r1 * (pbest[i]->transB - swarm[i]->transB) \
							 + 2.0 * r2 * (gbest->transB - swarm[i]->transB);
		if(v[i]->transB > fabs(vm->transB))
			v[i]->transB = fabs(vm->transB);
		else if(v[i]->transB < -1 * fabs(vm->transB))
			v[i]->transB = -1 * fabs(vm->transB);
		swarm[i]->transB += v[i]->transB;


		psoU2cs(paras, oriCS, swarm[i], oneCS);
		if(paras->dim2 == 2)
			cp_opt_1D_A2B(oriCS, oneCS, paras, 1);
		if(chk_dist(oneCS, paras) == 1)
			i--;
	}

	del_CS(oneCS, paras);

	return;
}

void pso_select(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, parameter *paras)
{
	int i;

	for(i=0; i < paras->size; i++)
	{
		if(swarm[i]->energy < pbest[i]->energy)
			cp_psoU_A2B(swarm[i], pbest[i], paras);
		else if(paras->algoGlob == 1 || paras->algoGlob == 2 || paras->algoGlob == 3)
			cp_psoU_A2B(pbest[i], swarm[i], paras);
		if(pbest[i]->energy < gbest->energy)
			cp_psoU_A2B(pbest[i], gbest, paras);
	}


	if(paras->algoGlob == 2)   // Actually useless, because after above loop, all particles become pbest
	{
		cp_psoU_A2B(swarm[0], gbest, paras);
		for(i=0; i < paras->size; i++)
			if(swarm[i]->energy < gbest->energy)
				cp_psoU_A2B(swarm[i], gbest, paras);
	}

	return;
}

void pso_constr(psoUnit *psoU, cryStruct *oriCS, parameter *paras)
{
	double hMix;
	int i, j;
	
	hMix = paras->hMix / oriCS->optH / 2.0;  // reduce hMix to fractional form

	for(i=0; i < paras->nBuffH; i++)
	{
		for(j=0; j<3; j++)
		{
			if(j<2)
			{
				while(psoU->buffPosH[i][j] >= 1)
					psoU->buffPosH[i][j]--;
				while(psoU->buffPosH[i][j] < 0)
					psoU->buffPosH[i][j]++;
			}
			else
			{
				if(psoU->buffPosH[i][j] < -hMix)
					psoU->buffPosH[i][j] = -hMix;
			}
		}
	}

	for(i=0; i < paras->nBuffL; i++)
	{
		for(j=0; j<3; j++)
		{
			if(j<2)
			{
				while(psoU->buffPosL[i][j] >= 1)
					psoU->buffPosL[i][j]--;
				while(psoU->buffPosL[i][j] < 0)
					psoU->buffPosL[i][j]++;
			}
			else
			{
				if(psoU->buffPosL[i][j] > 1+hMix)
					psoU->buffPosL[i][j] = 1+hMix;
			}
		}
	}

	for(i=0; i < paras->nOpt; i++)
	{
		for(j=0; j<3; j++)
		{
			if(j<2)
			{
				while(psoU->optPos[i][j] >= 1)
					psoU->optPos[i][j]--;
				while(psoU->optPos[i][j] < 0)
					psoU->optPos[i][j]++;
			}
			else
			{
				if(psoU->optPos[i][j] > 1+hMix)
					psoU->optPos[i][j] = 1+hMix;
				if(psoU->optPos[i][j] < -hMix)
					psoU->optPos[i][j] = -hMix;
			}
		}
	}

	if(psoU->optH > paras->hMax)
		psoU->optH = paras->hMax;
	if(psoU->optH < paras->hMin)
		psoU->optH = paras->hMin;
	if(psoU->transA > paras->transAM)
		psoU->transA = paras->transAM;
	if(psoU->transA < -1 * paras->transAM)
		psoU->transA = -1 * paras->transAM;
	if(psoU->transB > paras->transBM)
		psoU->transB = paras->transBM;
	if(psoU->transB < -1 * paras->transBM)
		psoU->transB = -1 * paras->transBM;

	return;
}

