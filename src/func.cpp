#include"func.h"

double **new_array(int nArray)
{
	int i;
	double **array;

	array = (double**)malloc(nArray*sizeof(double*));
	for(i=0; i<nArray; i++)
		array[i] = (double*)malloc(3*sizeof(double));

	return array;
}

void del_array(double **array, int nArray)
{
	int i;

	for(i=0; i<nArray; i++)
		free(array[i]);
	free(array);

	return;
}

void cp_array_A2B(double **arrayA, double **arrayB, int nArray)
{
	int i, j;

	for(i=0; i<nArray; i++)
		for(j=0; j<3; j++)
			arrayB[i][j] = arrayA[i][j];

	return;
}

char **new_string(int nString)
{
	int i;
	char **string;

	string = (char**)malloc(nString*sizeof(char*));
	for(i=0; i<nString; i++)
		string[i] = (char*)malloc(5*sizeof(char));

	return string;
}

void del_string(char **string, int nString)
{
	int i;

	for(i=0; i<nString; i++)
		free(string[i]);
	free(string);

	return;
}

void cp_string_A2B(char **stringA, char **stringB, int nString)
{
	int i;
	for(i=0; i<nString; i++)
		strcpy(stringB[i], stringA[i]);

	return;
}

cryStruct *new_CS(parameter *paras)
{
    cryStruct *oneCS;

    oneCS = (cryStruct*)malloc(sizeof(cryStruct));
    oneCS->latt = new_array(3);
	oneCS->charge = (double*)malloc(paras->nType*sizeof(double));
	oneCS->fixPosH = new_array(paras->nFixH);
	oneCS->fixPosL = new_array(paras->nFixL);
    oneCS->buffPosH = new_array(paras->nBuffH);
	oneCS->buffPosL = new_array(paras->nBuffL);
    oneCS->optPos = new_array(paras->nOpt);
	oneCS->fixTpH = new_string(paras->nFixH);
	oneCS->fixTpL = new_string(paras->nFixL);
	oneCS->buffTpH = new_string(paras->nBuffH);
	oneCS->buffTpL = new_string(paras->nBuffL);
	oneCS->optTp = new_string(paras->nOpt);

	return oneCS;
}

void del_CS(cryStruct *oneCS, parameter *paras)
{
	del_array(oneCS->latt, 3);
	free(oneCS->charge);
	del_array(oneCS->fixPosH, paras->nFixH);
	del_array(oneCS->fixPosL, paras->nFixL);
	del_array(oneCS->buffPosH, paras->nBuffH);
	del_array(oneCS->buffPosL, paras->nBuffL);
	del_array(oneCS->optPos, paras->nOpt);
	del_string(oneCS->fixTpH, paras->nFixH);
	del_string(oneCS->fixTpL, paras->nFixL);
	del_string(oneCS->buffTpH, paras->nBuffH);
	del_string(oneCS->buffTpL, paras->nBuffL);
	del_string(oneCS->optTp, paras->nOpt);
	free(oneCS);

	return;
}

void cp_CS_A2B(cryStruct *csA, cryStruct *csB, parameter *paras)
{
	int i;

	cp_array_A2B(csA->latt, csB->latt, 3);
	for(i=0; i < paras->nType; i++)
		csB->charge[i] = csA->charge[i];
	cp_array_A2B(csA->fixPosH, csB->fixPosH, paras->nFixH);
	cp_array_A2B(csA->fixPosL, csB->fixPosL, paras->nFixL);
	cp_array_A2B(csA->buffPosH, csB->buffPosH, paras->nBuffH);
	cp_array_A2B(csA->buffPosL, csB->buffPosL, paras->nBuffL);
	cp_array_A2B(csA->optPos, csB->optPos, paras->nOpt);
	cp_string_A2B(csA->fixTpH, csB->fixTpH, paras->nFixH);
	cp_string_A2B(csA->fixTpL, csB->fixTpL, paras->nFixL);
	cp_string_A2B(csA->buffTpH, csB->buffTpH, paras->nBuffH);
	cp_string_A2B(csA->buffTpL, csB->buffTpL, paras->nBuffL);
	cp_string_A2B(csA->optTp, csB->optTp, paras->nOpt);
	csB->optH = csA->optH;
	csB->transA = csA->transA;
	csB->transB = csA->transB;
	csB->energy = csA->energy;

	return;
}

void cp_opt_1D_A2B(cryStruct *csA, cryStruct *csB, parameter *paras, int dim)
{
	int i;
	
	for(i=0; i<paras->nOpt; i++)
		csB->optPos[i][dim] = csA->optPos[i][dim];

	return;
}

psoUnit *new_psoU(parameter *paras)
{
	psoUnit *psoU;

	psoU = (psoUnit*)malloc(sizeof(psoUnit));
	psoU->buffPosH = new_array(paras->nBuffH);
	psoU->buffPosL = new_array(paras->nBuffL);
	psoU->optPos = new_array(paras->nOpt);

	return psoU;
}

void del_psoU(psoUnit *psoU, parameter *paras)
{
	del_array(psoU->buffPosH, paras->nBuffH);
	del_array(psoU->buffPosL, paras->nBuffL);
	del_array(psoU->optPos, paras->nOpt);
	free(psoU);

	return;
}

void cp_psoU_A2B(psoUnit *psoUA, psoUnit *psoUB, parameter *paras)
{
	cp_array_A2B(psoUA->buffPosH, psoUB->buffPosH, paras->nBuffH);
	cp_array_A2B(psoUA->buffPosL, psoUB->buffPosL, paras->nBuffL);
	cp_array_A2B(psoUA->optPos, psoUB->optPos, paras->nOpt);
	psoUB->optH = psoUA->optH;
	psoUB->transA = psoUA->transA;
	psoUB->transB = psoUA->transB;
	psoUB->energy = psoUA->energy;

	return;
}

int get_type(char *type, parameter *paras)
{
	int i;

	for(i=0; i < paras->nType; i++)
		if(strcmp(type, paras->type[i]) == 0)
			return i;
}

void sort(double *array, int nArray)
{
	int i, j;
	double num;

	for(i=0; i<nArray; i++)
	{
		for(j=i+1; j<nArray; j++)
		{
			if(array[i] > array[j])
			{
				num = array[i];
				array[i] = array[j];
				array[j] = num;
			}
		}
	}

	return;
}

void sort_CS_psoU(cryStruct **nCS, psoUnit **swarm, psoUnit **pbest, psoUnit **v, parameter *paras)
{
	cryStruct *oneCS;
	psoUnit *psoU;
	int i, j;

	oneCS = new_CS(paras);
	psoU = new_psoU(paras);

	for(i=0; i < paras->size; i++)
	{
		for(j=i+1; j < paras->size; j++)
		{
			if(nCS[i]->energy > nCS[j]->energy)
			{
				cp_CS_A2B(nCS[i], oneCS, paras);
				cp_CS_A2B(nCS[j], nCS[i], paras);
				cp_CS_A2B(oneCS, nCS[j], paras);

				cp_psoU_A2B(swarm[i], psoU, paras);
				cp_psoU_A2B(swarm[j], swarm[i], paras);
				cp_psoU_A2B(psoU, swarm[j], paras);

				cp_psoU_A2B(pbest[i], psoU, paras);
				cp_psoU_A2B(pbest[j], pbest[i], paras);
				cp_psoU_A2B(psoU, pbest[j], paras);

				cp_psoU_A2B(v[i], psoU, paras);
				cp_psoU_A2B(v[j], v[i], paras);
				cp_psoU_A2B(psoU, v[j], paras);
			}
		}
	}

	del_CS(oneCS, paras);
	del_psoU(psoU, paras);

	return;
}

int par_done(int *parallel, parameter *paras)
{
	int i;
	int done = 1;
	
	for(i=0; i <  paras->size; i++)
		done *= parallel[i];

	return done;
}

void symmetry(psoUnit *psoU, parameter *paras)
{
	int i, j;
	double symMix;

	symMix = paras->symMix / psoU->optH;

	if(paras->symmetry == 0)
		return;

	for(i=0; i < paras->nOpt - paras->nOpt%2; i++)
	{
		psoU->optPos[i+1][2] = 1.0 - psoU->optPos[i][2];

		if(paras->symmetry == 1)
		{
			psoU->optPos[i+1][0] = 1.0 - psoU->optPos[i][0];
			psoU->optPos[i+1][1] = 1.0 - psoU->optPos[i][1];
		}
		else if(paras->symmetry == 2)
		{
			psoU->optPos[i+1][0] = psoU->optPos[i][0];
			psoU->optPos[i+1][1] = psoU->optPos[i][1];
		}

		if((psoU->optPos[i+1][2] > (1.0 - symMix)/2.0) && (psoU->optPos[i+1][2] < (1.0 - symMix)/2.0 + symMix))
		{
			psoU->optPos[i][2] = 0.5;
			psoU->optPos[i+1][2] = 0.5;
			psoU->optPos[i+1][0] = random;
			psoU->optPos[i+1][1] = random;
		}

		if(paras->dim2 == 1)
			psoU->optPos[i+1][1] = paras->dim2y;

		i++;
	}

	if(paras->nOpt%2 == 1)
	{
		for(j=0; j<3; j++)
			psoU->optPos[paras->nOpt - 1][j] = 0.5;
		if(paras->symmetry == 2)
			for(j=0; j<2; j++)
				 psoU->optPos[paras->nOpt - 1][j] = random;
		if(paras->dim2 == 1)
			psoU->optPos[paras->nOpt - 1][1] = paras->dim2y;
	}

	for(i=0; i < paras->nOpt; i++)
	{
		if(psoU->optPos[i][2] > 0.5)
		{
			psoU->optPos[i][0] += psoU->transA;
			psoU->optPos[i][1] += psoU->transB;
		}
		else if(psoU->optPos[i][2] == 0.5)
		{
			psoU->optPos[i][0] += psoU->transA / 2.0;
			psoU->optPos[i][1] += psoU->transB / 2.0;
		}
	}

	for(i=0; i < paras->nOpt; i++)
		for(j=0; j<2; j++)
			if(psoU->optPos[i][j] > 1.0)
				psoU->optPos[i][j] --;
			else if(psoU->optPos[i][j] < 0.0)
				psoU->optPos[i][j] ++;

	return;
}

void rm_file(parameter *paras)
{
	int i;

	for(i=0; i < paras->nRmFile; i++)
		if(access(paras->rmFile[i], F_OK) == 0)
			remove(paras->rmFile[i]);

	return;
}

void group_dividing(cryStruct *oriCS, cryStruct *oneCS, parameter *paras)
{
	int **typeNum, *types, *countNum;
	int i, j, k, l, m, type;
	int ndvd, dvd, ndvda, dvda, alimit, blimit;
	double coord;

	ndvd = paras->dvdOpt;
	ndvda = paras->dvdA;

	types = (int*)malloc(paras->nType * sizeof(int));
	typeNum = (int**)malloc(paras->nType * sizeof(int));
	countNum = (int*)malloc(paras->nType * sizeof(int));
	for(i=0; i < paras->nType; i++)
	{
		types[i] = 0;
		countNum[i] = -1;
	}
	for(i=0; i < paras->nOpt; i++)
		types[get_type(oriCS->optTp[i], paras)] ++;
	for(i=0; i < paras->nType; i++)
		typeNum[i] = (int*)malloc(types[i] * sizeof(int));
	for(i=0; i < paras->nOpt; i++)
	{
		type = get_type(oriCS->optTp[i], paras);
		countNum[type] ++;
		typeNum[type][countNum[type]] = i;
	}

	for(i=0; i < paras->nType; i++)
	{
		for(j=0; j<types[i]; j++)
			for(k=0; k<j; k++)
			{
				if(oneCS->optPos[typeNum[i][k]][2] > oneCS->optPos[typeNum[i][j]][2])
				{
					coord = oneCS->optPos[typeNum[i][k]][0];
					oneCS->optPos[typeNum[i][k]][0] = oneCS->optPos[typeNum[i][j]][0];
					oneCS->optPos[typeNum[i][j]][0] = coord;
					coord = oneCS->optPos[typeNum[i][k]][1];
					oneCS->optPos[typeNum[i][k]][1] = oneCS->optPos[typeNum[i][j]][1];
					oneCS->optPos[typeNum[i][j]][1] = coord;
					coord = oneCS->optPos[typeNum[i][k]][2];
					oneCS->optPos[typeNum[i][k]][2] = oneCS->optPos[typeNum[i][j]][2];
					oneCS->optPos[typeNum[i][j]][2] = coord;
				}
			}

		dvd = (int)(types[i] / ndvd);
		for(j=0; j<ndvd; j++)
		{
			if(j == ndvd - 1)
				alimit = types[i];
			else
				alimit = (j+1) * dvd;
			for(k = j * dvd; k < alimit; k++)
			{
				for(l = j * dvd; l < k; l++)
				{
					if(oneCS->optPos[typeNum[i][l]][0] > oneCS->optPos[typeNum[i][k]][0])
					{
						coord = oneCS->optPos[typeNum[i][l]][0];
						oneCS->optPos[typeNum[i][l]][0] = oneCS->optPos[typeNum[i][k]][0];
						oneCS->optPos[typeNum[i][k]][0] = coord;
						coord = oneCS->optPos[typeNum[i][l]][1];
						oneCS->optPos[typeNum[i][l]][1] = oneCS->optPos[typeNum[i][k]][1];
						oneCS->optPos[typeNum[i][k]][1] = coord;
						coord = oneCS->optPos[typeNum[i][l]][2];
						oneCS->optPos[typeNum[i][l]][2] = oneCS->optPos[typeNum[i][k]][2];
						oneCS->optPos[typeNum[i][k]][2] = coord;
					}
				}
			}

			dvda = (int)((alimit - j * dvd) / ndvda);
			for(k = 0; k < ndvda; k++)
			{
				if(k == ndvda - 1)
					blimit = (alimit - j * dvd);
				else
					blimit = (k+1) * dvda;
				for(l = k * dvda + j * dvd; l < blimit + j * dvd; l++)
				{
					for(m = k * dvda + j * dvd; m < l; m++)
					{
						if(oneCS->optPos[typeNum[i][m]][1] > oneCS->optPos[typeNum[i][l]][1])
						{
							coord = oneCS->optPos[typeNum[i][m]][0];
							oneCS->optPos[typeNum[i][m]][0] = oneCS->optPos[typeNum[i][l]][0];
							oneCS->optPos[typeNum[i][l]][0] = coord;
							coord = oneCS->optPos[typeNum[i][m]][1];
							oneCS->optPos[typeNum[i][m]][1] = oneCS->optPos[typeNum[i][l]][1];
							oneCS->optPos[typeNum[i][l]][1] = coord;
							coord = oneCS->optPos[typeNum[i][m]][2];
							oneCS->optPos[typeNum[i][m]][2] = oneCS->optPos[typeNum[i][l]][2];
							oneCS->optPos[typeNum[i][l]][2] = coord;
						}
					}
				}
			}
		}
	}

	for(i=0; i < paras->nType; i++)
		free(typeNum[i]);
	free(typeNum);
	free(types);
	free(countNum);

	return;
}
