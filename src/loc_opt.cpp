#include"loc_opt.h"

void loc_opt_serial(cryStruct *oneCS, cryStruct *oriCS,  parameter *paras)
{
	if(paras->algoLoc == 1)
		lammps_serial(oneCS, oriCS, paras);
	else if(paras->algoLoc == 100)
	{
		psoUnit *psoU;
		double energy;
		int i, j;

		psoU = new_psoU(paras);
		cs2psoU(paras, oneCS, psoU);

		energy = 0;
		for(i=0; i < paras->nOpt; i++)
			for(j=0; j<3; j++)
				energy += pow((psoU->optPos[i][j] - 0.5), 2);
		energy += (psoU->optH - (paras->optTop - paras->optBot)) * (psoU->optH - (paras->optTop - paras->optBot));
		oneCS->energy = energy;

		del_psoU(psoU, paras);
	}

	return;
}

void loc_opt_init(cryStruct *oneCS, parameter *paras)
{
	if(paras->algoLoc == 1)
		lammps_init(oneCS, paras);
	else if(paras->algoLoc == 2)
		vasp_init(oneCS, paras);

	return;
}

int loc_opt_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	if(paras->algoLoc == 1)
		return lammps_final(oneCS, oriCS, paras);
	else if(paras->algoLoc == 2)
		return vasp_final(oneCS, oriCS, paras);
}
