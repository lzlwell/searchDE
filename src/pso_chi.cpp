#include"pso_chi.h"

void pso_chi(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, cryStruct *oriCS)
{
	double r1, r2;
	int i, j, k;
	double chi, phi1, phi2;
	cryStruct *oneCS;

	oneCS = new_CS(paras);

	chi = 0.7298;
	phi1 = 2.05;
	phi2 = 2.05;

	for(i=0; i < (int)(paras->size * paras->psoProp); i++)
	{
		for(j=0; j < paras->nBuffH; j++)
		{
			for(k=0; k<3; k++)
			{
				r1 = random;
				r2 = random;
				v[i]->buffPosH[j][k] = chi  * ( v[i]->buffPosH[j][k] \
									   + phi1 * r1 * (pbest[i]->buffPosH[j][k] - swarm[i]->buffPosH[j][k]) \
									   + phi2 * r2 * (gbest->buffPosH[j][k] - swarm[i]->buffPosH[j][k]) );
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
				v[i]->buffPosL[j][k] = chi  * ( v[i]->buffPosL[j][k] \
									   + phi1 * r1 * (pbest[i]->buffPosL[j][k] - swarm[i]->buffPosL[j][k]) \
									   + phi2 * r2 * (gbest->buffPosL[j][k] - swarm[i]->buffPosL[j][k]) );
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
				v[i]->optPos[j][k] = chi  * ( v[i]->optPos[j][k] \
									   + phi1 * r1 * (pbest[i]->optPos[j][k] - swarm[i]->optPos[j][k]) \
									   + phi2 * r2 * (gbest->optPos[j][k] - swarm[i]->optPos[j][k]) );
				if(v[i]->optPos[j][k] > fabs(vm->optPos[j][k]))
					v[i]->optPos[j][k] = fabs(vm->optPos[j][k]);
				else if(v[i]->optPos[j][k] < -1 * fabs(vm->optPos[j][k]))
					v[i]->optPos[j][k] = -1 * fabs(vm->optPos[j][k]);
				swarm[i]->optPos[j][k] += v[i]->optPos[j][k];
			}
		}

		r1 = random;
		r2 = random;
		v[i]->optH = chi  * ( v[i]->optH \
							 + phi1 * r1 * (pbest[i]->optH - swarm[i]->optH) \
							 + phi2 * r2 * (gbest->optH - swarm[i]->optH) );
		if(v[i]->optH > fabs(vm->optH))
			v[i]->optH = fabs(vm->optH);
		else if(v[i]->optH < -1 * fabs(vm->optH))
			v[i]->optH = -1 * fabs(vm->optH);
		swarm[i]->optH += v[i]->optH;

		r1 = random;
		r2 = random;
		v[i]->transA = chi  * ( v[i]->transA \
							 + phi1 * r1 * (pbest[i]->transA - swarm[i]->transA) \
							 + phi2 * r2 * (gbest->transA - swarm[i]->transA) );
		if(v[i]->transA > fabs(vm->transA))
			v[i]->transA = fabs(vm->transA);
		else if(v[i]->transA < -1 * fabs(vm->transA))
			v[i]->transA = -1 * fabs(vm->transA);
		swarm[i]->transA += v[i]->transA;

		r1 = random;
		r2 = random;
		v[i]->transB = chi  * ( v[i]->transB \
							 + phi1 * r1 * (pbest[i]->transB - swarm[i]->transB) \
							 + phi2 * r2 * (gbest->transB - swarm[i]->transB) );
		if(v[i]->transB > fabs(vm->transB))
			v[i]->transB = fabs(vm->transB);
		else if(v[i]->transB < -1 * fabs(vm->transB))
			v[i]->transB = -1 * fabs(vm->transB);
		swarm[i]->transB += v[i]->transB;


        psoU2cs(paras, oriCS, swarm[i], oneCS);
        if(chk_dist(oneCS, paras) == 1)
			i--;
	}

	del_CS(oneCS, paras);

	return;
}
