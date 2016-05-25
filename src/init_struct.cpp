#include"init_struct.h"
#include"func.h"

void init_oriCS(cryStruct *oriCS, parameter *paras)
{
	int i;

	r_pos(oriCS, paras);
	for(i=0; i < paras->nType; i++)
		oriCS->charge[i] = paras->charge[i];
	oriCS->optH = paras->optTop - paras->optBot;  // make sure the structure of oneCS itself is self-consistent
	oriCS->transA = 0.0;
	oriCS->transB = 0.0;
	oriCS->energy = 1.0E6;

	return;
}

void init_struct(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	psoUnit *psoU;
	int i, j;

	psoU = new_psoU(paras);

	cp_CS_A2B(oriCS, oneCS, paras);
	cs2psoU(paras, oneCS, psoU);

	for(i=0; i < paras->nOpt; i++)
	{
		for(j=0; j<3; j++)
				psoU->optPos[i][j] = random;  // generate random structure
	}
	psoU->optH = paras->hMin + (paras->hMax - paras->hMin) * random;  // give optH a random range
	psoU->transA = paras->transAM * (random - 0.5);
	psoU->transB = paras->transBM * (random - 0.5);

	symmetry(psoU, paras);

	psoU2cs(paras, oriCS, psoU, oneCS);
	if(paras->dim2 == 2)
		cp_opt_1D_A2B(oriCS, oneCS, paras, 1);

	del_psoU(psoU, paras);

	return;
}
