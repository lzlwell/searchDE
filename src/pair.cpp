#include"pair.h"

double pair_dist(double *posA, double *posB, double **latt)
{
	double carA[3], carB[3], distSqr;
	dir2car(posA, carA, latt);
	dir2car(posB, carB, latt);
	distSqr = (carA[0]-carB[0])*(carA[0]-carB[0]) + (carA[1]-carB[1])*(carA[1]-carB[1]) + (carA[2]-carB[2])*(carA[2]-carB[2]);

	return sqrt(distSqr);
}

void ext_cell(int na, int nb, int nc, cryStruct *oneCS, cryStruct *extCS, parameter *paras)
{
	int i;

	for(i=0; i < paras->nFixH; i++)
	{
		extCS->fixPosH[i][0] = oneCS->fixPosH[i][0] + na;
		extCS->fixPosH[i][1] = oneCS->fixPosH[i][1] + nb;
		extCS->fixPosH[i][2] = oneCS->fixPosH[i][2] + nc;
	}

	for(i=0; i < paras->nFixL; i++)
	{
		extCS->fixPosL[i][0] = oneCS->fixPosL[i][0] + na;
		extCS->fixPosL[i][1] = oneCS->fixPosL[i][1] + nb;
		extCS->fixPosL[i][2] = oneCS->fixPosL[i][2] + nc;
	}

	for(i=0; i < paras->nBuffH; i++)
	{
		extCS->buffPosH[i][0] = oneCS->buffPosH[i][0] + na;
		extCS->buffPosH[i][1] = oneCS->buffPosH[i][1] + nb;
		extCS->buffPosH[i][2] = oneCS->buffPosH[i][2] + nc;
	}

	for(i=0; i < paras->nBuffL; i++)
	{
		extCS->buffPosL[i][0] = oneCS->buffPosL[i][0] + na;
		extCS->buffPosL[i][1] = oneCS->buffPosL[i][1] + nb;
		extCS->buffPosL[i][2] = oneCS->buffPosL[i][2] + nc;
	}

	for(i=0; i < paras->nOpt; i++)
	{
		extCS->optPos[i][0] = oneCS->optPos[i][0] + na;
		extCS->optPos[i][1] = oneCS->optPos[i][1] + nb;
		extCS->optPos[i][2] = oneCS->optPos[i][2] + nc;
	}

	return;
}

int chk_dist(cryStruct *oneCS, parameter *paras)
{
	cryStruct *extCS;
	int i, j, na, nb, nc;

	extCS = new_CS(paras);
	cp_CS_A2B(oneCS, extCS, paras);

	for(na=-1; na<=1; na++)
	{
		for(nb=-1; nb<=1; nb++)
		{
			for(nc=-1; nc<=1; nc++)
			{
				ext_cell(na, nb, nc, oneCS, extCS, paras);
	
				for(i=0; i < paras->nOpt; i++)
				{

					for(j=0; j < paras->nOpt; j++)
						if((pair_dist(oneCS->optPos[i], extCS->optPos[j], oneCS->latt) < paras->distMin) \
								&& (pair_dist(oneCS->optPos[i], extCS->optPos[j], oneCS->latt) > 0))
						{
							del_CS(extCS, paras);
							return 1;
						}
	
					for(j=0; j < paras->nFixH; j++)
						if(pair_dist(oneCS->optPos[i], extCS->fixPosH[j], oneCS->latt) < paras->distMin)
						{
							del_CS(extCS, paras);
							return 1;
						}

					for(j=0; j < paras->nFixL; j++)
						if(pair_dist(oneCS->optPos[i], extCS->fixPosL[j], oneCS->latt) < paras->distMin)
						{
							del_CS(extCS, paras);
							return 1;
						}

					for(j=0; j < paras->nBuffH; j++)
						if(pair_dist(oneCS->optPos[i], extCS->buffPosH[j], oneCS->latt) < paras->distMin)
						{
							del_CS(extCS, paras);
							return 1;
						}

					for(j=0; j < paras->nBuffL; j++)
						if(pair_dist(oneCS->optPos[i], extCS->buffPosL[j], oneCS->latt) < paras->distMin)
						{
							del_CS(extCS, paras);
							return 1;
						}
				}
			}
		}
	}

	del_CS(extCS, paras);

	return 0;
}

void get_bond(cryStruct *oneCS, parameter *paras, double *bond)
{
	cryStruct *extCS;
	int na, nb, nc, i, j, count;

	extCS = new_CS(paras);
	cp_CS_A2B(oneCS, extCS, paras);

	count = 0;
	for(na=-1; na<=1; na++)
	{
		for(nb=-1; nb<=1; nb++)
		{
			for(nc=-1; nc<=1; nc++)
			{
				ext_cell(na, nb, nc, oneCS, extCS, paras);
	
				for(i=0; i < paras->nOpt; i++)
				{

					for(j=0; j < paras->nOpt; j++)
					{
						bond[count] = pair_dist(oneCS->optPos[i], extCS->optPos[j], oneCS->latt);
						count ++;
					}
	
					for(j=0; j < paras->nFixH; j++)
					{
						bond[count] = pair_dist(oneCS->optPos[i], extCS->fixPosH[j], oneCS->latt);
						count ++;
					}

					for(j=0; j < paras->nFixL; j++)
					{
						bond[count] = pair_dist(oneCS->optPos[i], extCS->fixPosL[j], oneCS->latt);
						count ++;
					}

					for(j=0; j < paras->nBuffH; j++)
					{
						bond[count] = pair_dist(oneCS->optPos[i], extCS->buffPosH[j], oneCS->latt);
						count ++;
					}

					for(j=0; j < paras->nBuffL; j++)
					{
						bond[count] = pair_dist(oneCS->optPos[i], extCS->buffPosL[j], oneCS->latt);
						count ++;
					}
				}
			}
		}
	}
	
	del_CS(extCS, paras);

	return;
}

int chk_dup(cryStruct **nCS, parameter *paras, int num)
{
	int i, j, nBond;
	double *bondA, *bondB;
	double devSqr;

	nBond = 3 * 3 * 3 * paras->nOpt * (paras->nOpt + paras->nFixH + paras->nFixL + paras->nBuffH + paras->nBuffL);
	bondA = (double*)malloc(nBond*sizeof(double));
	bondB = (double*)malloc(nBond*sizeof(double));

	for(i=0; i<num; i++)
	{
		if(fabs(nCS[num]->energy - nCS[i]->energy) < paras->eDiff)
		{
			if(paras->rmDup == 1)
			{
				free(bondA);
				free(bondB);
				return 1;
			}
			else if(paras->rmDup == 2)
			{
				get_bond(nCS[num], paras, bondA);
				sort(bondA, nBond);
	
				get_bond(nCS[i], paras, bondB);
				sort(bondB, nBond);
	
				devSqr = 0;
				for(j=0; j<nBond; j++)
					devSqr += (bondA[j] - bondB[j]) * (bondA[j] - bondB[j]);
	
				if(sqrt(devSqr) < paras->devM)
				{
					free(bondA);
					free(bondB);
					return 1;
				}
			}
		}
	}

	free(bondA);
	free(bondB);
	return 0;
}
