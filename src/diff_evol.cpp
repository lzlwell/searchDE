#include"diff_evol.h"

void diff_evol(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, cryStruct *oriCS)
{
	int a, b, c, d;
	int i, j, k;
	double F;
	double CR;
	double r;
	int NP, D, iD, R;

	NP = paras->size;
	D = 3 * paras->nBuffH + 3 * paras->nBuffL + 3 * paras->nOpt + 3;
	F = paras->diffEvolF;
	CR = paras->diffEvolCR;

	cryStruct *oneCS;

	oneCS = new_CS(paras);

	for(i=0; i < (int)(paras->size * paras->psoProp); i++)
	{
		do{ a = (int)(random * NP);} while (a == i);
		do{ b = (int)(random * NP);} while (b == i || b == a);
		do{ c = (int)(random * NP);} while (c == i || c == a || c == b);
		do{ d = (int)(random * NP);} while (d == i || d == a || d == b || d == c);
		R = (int)(random * D);
		iD = 0;

		for(j=0; j < paras->nBuffH; j++)
		{
			for(k=0; k<3; k++)
			{
				r = random;
				if(r < CR || iD == R)
				{
					if(paras->algoGlob == 1)
						v[i]->buffPosH[j][k] = swarm[c]->buffPosH[j][k] + F * (swarm[a]->buffPosH[j][k] - swarm[b]->buffPosH[j][k]);
					else if(paras->algoGlob == 2 || paras->algoGlob == 3)
						v[i]->buffPosH[j][k] = gbest->buffPosH[j][k] + F * (swarm[a]->buffPosH[j][k] + swarm[b]->buffPosH[j][k] \
							                                              - swarm[c]->buffPosH[j][k] - swarm[d]->buffPosH[j][k] );
				}
				else
					v[i]->buffPosH[j][k] = swarm[i]->buffPosH[j][k];
				iD++;
			}
		}

		for(j=0; j < paras->nBuffL; j++)
		{
			for(k=0; k<3; k++)
			{
				r = random;
				if(r < CR || iD == R)
				{
					if(paras->algoGlob == 1)
						v[i]->buffPosL[j][k] = swarm[c]->buffPosL[j][k] + F * (swarm[a]->buffPosL[j][k] - swarm[b]->buffPosL[j][k]);
					else if(paras->algoGlob == 2 || paras->algoGlob == 3)
						v[i]->buffPosL[j][k] = gbest->buffPosL[j][k] + F * (swarm[a]->buffPosL[j][k] + swarm[b]->buffPosL[j][k] \
								                                          - swarm[c]->buffPosL[j][k] - swarm[d]->buffPosL[j][k] );
				}
				else
					v[i]->buffPosL[j][k] = swarm[i]->buffPosL[j][k];
				iD++;
			}
		}

		for(j=0; j < paras->nOpt; j++)
		{
			for(k=0; k<3; k++)
			{
				r = random;
				if(r < CR || iD == R)
				{
					if(paras->algoGlob == 1)
						v[i]->optPos[j][k] = swarm[c]->optPos[j][k] + F * (swarm[a]->optPos[j][k] - swarm[b]->optPos[j][k]);
					else if(paras->algoGlob == 2 || paras->algoGlob == 3)
						v[i]->optPos[j][k] = gbest->optPos[j][k] + F * (swarm[a]->optPos[j][k] + swarm[b]->optPos[j][k] \
	                                                                  - swarm[c]->optPos[j][k] - swarm[d]->optPos[j][k] );
				}
				else
					v[i]->optPos[j][k] = swarm[i]->optPos[j][k];
				iD++;
			}
		}

		r = random;
		if(r < CR || iD == R)
		{
			if(paras->algoGlob == 1)
				v[i]->optH = swarm[c]->optH + F * (swarm[a]->optH - swarm[b]->optH);
			else if(paras->algoGlob == 2 || paras->algoGlob == 3)
				v[i]->optH = gbest->optH + F * (swarm[a]->optH + swarm[b]->optH \
                                              - swarm[c]->optH - swarm[d]->optH );
		}
		else
			v[i]->optH = swarm[i]->optH;
		iD++;

		r = random;
		if(r < CR || iD == R)
		{
			if(paras->algoGlob == 1)
				v[i]->transA = swarm[c]->transA + F * (swarm[a]->transA - swarm[b]->transA);
			else if(paras->algoGlob == 2 || paras->algoGlob == 3)
				v[i]->transA = gbest->transA + F * (swarm[a]->transA + swarm[b]->transA \
						                          - swarm[c]->transA - swarm[d]->transA );
		}
		else
			v[i]->transA = swarm[i]->transA;
		iD++;

		r = random;
		if(r < CR || iD == R)
		{
			if(paras->algoGlob == 1)
				v[i]->transB = swarm[c]->transB + F * (swarm[a]->transB - swarm[b]->transB);
			else if(paras->algoGlob == 2 || paras->algoGlob == 3)
				v[i]->transB = gbest->transB + F * (swarm[a]->transB + swarm[b]->transB \
						                          - swarm[c]->transB - swarm[d]->transB );
		}
		else
			v[i]->transB = swarm[i]->transB;
		iD++;


        psoU2cs(paras, oriCS, swarm[i], oneCS);
	if(paras->dim2 == 2)
		cp_opt_1D_A2B(oriCS, oneCS, paras, 1);
        if(chk_dist(oneCS, paras) == 1)
			i--;
	}

	for(i=0; i < (int)(paras->size * paras->psoProp); i++)
		cp_psoU_A2B(v[i], swarm[i], paras);

	del_CS(oneCS, paras);

	return;
}
