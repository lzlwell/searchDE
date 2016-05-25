#include"pso_opt.h"

void pso_opt_serial(parameter *paras, cryStruct *oriCS)
{
	cryStruct **nCS, *bestCS;
	psoUnit **swarm, **pbest, *gbest, **v, *vm;
	double omega;
	char dirGen[20], dirSize[20];
	char fileEner[20], fileStruct[20], file[20];
	int i, j, k, l;
	FILE *fp;

	fp = fopen("log.pso", "w");
	fprintf(fp, "Starting Particle Swarm Optimization\n");
	fclose(fp);

	strcpy(fileEner, "energy");
	strcpy(fileStruct, "struct.out");

	w_init(fileEner);
	w_init(fileStruct);

	nCS = (cryStruct**)malloc(paras->size * sizeof(cryStruct*));
	bestCS = new_CS(paras);
	swarm = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	pbest = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	gbest = new_psoU(paras);
	v = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	vm = new_psoU(paras);

	for(i=0; i < paras->size; i++)
	{
		nCS[i] = new_CS(paras);
		swarm[i] = new_psoU(paras);
		pbest[i] = new_psoU(paras);
		v[i] = new_psoU(paras);
	}

	mkdir("results", S_IRWXU);
	chdir("results");
	mkdir("_1", S_IRWXU);
	chdir("..");
	fp = fopen("log.pso", "a+");
	fprintf(fp, "Generating new structures...\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		do
		{
			init_struct(nCS[i], oriCS, paras);
		}while(chk_dist(nCS[i], paras) == 1);
	
		if((paras->keepOri == 1) && (i==0))
			cp_CS_A2B(oriCS, nCS[i], paras);

		group_dividing(oriCS, nCS[i], paras);

		chdir("results");
		chdir("_1");
		sprintf(dirSize, "%d", i);
		mkdir(dirSize, S_IRWXU);
		chdir(dirSize);
		loc_opt_serial(nCS[i], oriCS, paras);
		group_dividing(oriCS, nCS[i], paras);
		chdir("../../../");

		cs2psoU(paras, nCS[i], swarm[i]);
		cp_psoU_A2B(swarm[i], pbest[i], paras);
	
		fp = fopen("log.pso", "a+");
		fprintf(fp, "The energy of the %dth structure is: %f\n", i, swarm[i]->energy);
		fclose(fp);

		for(j=0; j < paras->nBuffH; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosH[j][k] = 0;
		for(j=0; j < paras->nBuffL; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosL[j][k] = 0;
		for(j=0; j < paras->nOpt; j++)
			for(k=0; k<3; k++)
				v[i]->optPos[j][k] = 0;
		v[i]->optH = 0;
		v[i]->transA = 0;
		v[i]->transB = 0;
		v[i]->energy = 0;
	}
	fp = fopen("log.pso", "a+");
	fprintf(fp, "End generating new srtuctures.\n");
	fclose(fp);
	cp_psoU_A2B(pbest[0], gbest, paras);

	for(i=0; i < paras->nBuffH; i++)
		for(j=0; j<3; j++)
			vm->buffPosH[i][j] = paras->vmBuffH;
	for(i=0; i < paras->nBuffL; i++)
		for(j=0; j<3; j++)
			vm->buffPosL[i][j] = paras->vmBuffL;
	for(i=0; i < paras->nOpt; i++)
		for(j=0; j<3; j++)
			vm->optPos[i][j] = paras->vmOpt;
	vm->optH = paras->vmOptH;
	vm->transA = paras->vmTransA;
	vm->transB = paras->vmTransB;

	pso_select(swarm, pbest, gbest, paras);
	sort_CS_psoU(nCS, swarm, pbest, v, paras);
	fp = fopen("log.pso", "a+");
	fprintf(fp, "After DE selection\nparticle  energy\n");
	for(j=0; j < paras->size; j++)
		fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
	fprintf(fp, "PSO has selected best for the _1 generation: %f\n", gbest->energy);
	fclose(fp);

	psoU2cs(paras, oriCS, gbest, bestCS);
	w_ener(bestCS, fileEner);

	fp = fopen("log.pso", "a+");
	fprintf(fp, "Starting PSO main loop...\n");
	fclose(fp);

	omega = 0.9;
	for(i=0; i < paras->nGens; i++)
	{
		fp = fopen("log.pso", "a+");
		fprintf(fp, "\ngeneration %d\n", i);
		fclose(fp);
		chdir("results");
		sprintf(dirGen, "%d", i);
		mkdir(dirGen, S_IRWXU);
		chdir("..");

		if(paras->algoGlob == 1 || paras->algoGlob == 2 || paras->algoGlob == 3)
		{
			diff_evol(swarm, pbest, gbest, v, vm, paras, oriCS);
		}
		else if(paras->algoGlob == 10)
		{
			omega = 0.9 - (0.9-0.4) * i / paras->nGens;
			pso(swarm, pbest, gbest, v, vm, paras, omega, oriCS);
		}
		else if(paras->algoGlob == 11)
			pso_chi(swarm, pbest, gbest, v, vm, paras, oriCS);
		
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done PSO!\n");
		fclose(fp);
		for(j=0; j < paras->size; j++)
		{
			if(j < (int)(paras->size * paras->psoProp))
			{
				fp = fopen("log.pso", "a+");
				fprintf(fp, "Constraining and checking distances for the %dth PSO unit\n", j);
				fclose(fp);
				pso_constr(swarm[j], oriCS, paras);
				symmetry(swarm[j], paras);
				psoU2cs(paras, oriCS, swarm[j], nCS[j]);
			//	cp_opt_1D_A2B(oriCS, nCS[j], paras, 1);
				if(chk_dist(nCS[j], paras) == 1)
				{
					fp = fopen("log.pso", "a+");
					fprintf(fp, "New structure generated to substitute the one PSO generated!\n");
					fclose(fp);
				}
				while(chk_dist(nCS[j], paras) == 1)
					init_struct(nCS[j], oriCS, paras);
				fp = fopen("log.pso", "a+");
				fprintf(fp, "End constraining and checking\n");
				fclose(fp);
			}
			else
			{
				fp = fopen("log.pso", "a+");
				fprintf(fp, "Reinitializing for the %dth PSO unit\n", j);
				fclose(fp);
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				fp = fopen("log.pso", "a+");
				fprintf(fp, "End reinitializing\n");
				fclose(fp);
			}			

			fp = fopen("log.pso", "a+");
			fprintf(fp, "Changing directory to start local optimization!\n");
			fclose(fp);
			chdir("results");
			chdir(dirGen);
			sprintf(dirSize, "%d", j);
			mkdir(dirSize, S_IRWXU);
			chdir(dirSize);
			loc_opt_serial(nCS[j], oriCS, paras);
			group_dividing(oriCS, nCS[j], paras);
			if((paras->rmDup > 0) && (chk_dup(nCS, paras, j) == 1))
			{
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				loc_opt_serial(nCS[j], oriCS, paras);
				group_dividing(oriCS, nCS[j], paras);
				cs2psoU(paras, nCS[j], pbest[j]);
				for(k=0; k < paras->nBuffH; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosH[k][l] = 0;
				for(k=0; k < paras->nBuffL; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosL[k][l] = 0;
				for(k=0; k < paras->nOpt; k++)
					for(l=0; l<3; l++)
						v[j]->optPos[k][l] = 0;
				v[j]->optH = 0;
				v[j]->energy = 0;
			}
			chdir("../../..");
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Done local optimization! Return to main directory.\n");
			fclose(fp);

			cs2psoU(paras, nCS[j], swarm[j]);
			fp = fopen("log.pso", "a+");
			fprintf(fp, "The energy of the %dth structure is: %f\n", j, swarm[j]->energy);
			fclose(fp);
		}

		pso_select(swarm, pbest, gbest, paras);
		fp = fopen("log.pso", "a+");
		fprintf(fp, "After DE selection\nparticle  energy\n");
		for(j=0; j < paras->size; j++)
			fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
		fprintf(fp, "PSO has selected the gbest for the %d generation: %f\n", i, gbest->energy);
		fclose(fp);
		sort_CS_psoU(nCS, swarm, pbest, v, paras);
		psoU2cs(paras, oriCS, gbest, bestCS);

		printf("generations: %d    energy: %f \n", i, bestCS->energy);
		w_ener(bestCS, fileEner);
	}

	w_cs(bestCS, paras, fileStruct);
	w_vasp(bestCS, paras);
	remove("INCAR");
	strcpy(file, "psoU");
	cs2psoU(paras, bestCS, gbest);
	w_psoU(gbest, paras, file);

	fp = fopen("log.pso", "a+");
	fprintf(fp, "Finishing Particle Swarm Optimization!\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		del_CS(nCS[i], paras);
		del_psoU(swarm[i], paras);
		del_psoU(pbest[i], paras);
		del_psoU(v[i], paras);
	}
	del_CS(bestCS, paras);
	del_psoU(gbest, paras);
	del_psoU(vm, paras);

	free(nCS);
	free(swarm);
	free(pbest);
	free(v);

	return;
}

void pso_opt(parameter *paras, cryStruct *oriCS)
{
	cryStruct **nCS, *bestCS;
	psoUnit **swarm, **pbest, *gbest, **v, *vm;
	int *parallel;
	double omega;
	char dirGen[20], dirSize[20];
	char fileEner[20], fileStruct[20], file[20];
	int i, j, k, l;
	FILE *fp;

	parallel = (int*)malloc(paras->size*sizeof(int));

	strcpy(fileEner, "energy");
	strcpy(fileStruct, "struct.out");
   
	fp = fopen("log.pso", "w");
	fprintf(fp, "Starting Particle Swarm Optimization\n");
	fclose(fp);

	w_init(fileEner);
	w_init(fileStruct);

	nCS = (cryStruct**)malloc(paras->size * sizeof(cryStruct*));
	bestCS = new_CS(paras);
	swarm = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	pbest = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	gbest = new_psoU(paras);
	v = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	vm = new_psoU(paras);

	for(i=0; i < paras->size; i++)
	{
		nCS[i] = new_CS(paras);
		swarm[i] = new_psoU(paras);
		pbest[i] = new_psoU(paras);
		v[i] = new_psoU(paras);
	}

	mkdir("results", S_IRWXU);
	chdir("results");
	mkdir("_1", S_IRWXU);
	chdir("..");
	fp = fopen("log.pso", "a+");
	fprintf(fp, "Generating new structures...\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		do
		{
			init_struct(nCS[i], oriCS, paras);
		}while(chk_dist(nCS[i], paras) == 1);
	
		if((paras->keepOri == 1) && (i==0))
			cp_CS_A2B(oriCS, nCS[i], paras);
	
		chdir("results");
		chdir("_1");
		sprintf(dirSize, "%d", i);
		mkdir(dirSize, S_IRWXU);
		chdir(dirSize);
		loc_opt_init(nCS[i], paras);
		chdir("../../../");
		parallel[i] = 0;
	
		for(j=0; j < paras->nBuffH; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosH[j][k] = 0;
		for(j=0; j < paras->nBuffL; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosL[j][k] = 0;
		for(j=0; j < paras->nOpt; j++)
			for(k=0; k<3; k++)
				v[i]->optPos[j][k] = 0;
		v[i]->optH = 0;
		v[i]->transA = 0;
		v[i]->transB = 0;
		v[i]->energy = 0;
	}
	fp = fopen("log.pso", "a+");
	fprintf(fp, "End generating new srtuctures.\nStarting local optimization for initial structures\n");
	fclose(fp);
	while(par_done(parallel, paras) == 0)
	{
		for(i=0; i < paras->size; i++)
		{
			if(parallel[i] == 0)
			{
				chdir("results");
				chdir("_1");
				sprintf(dirSize, "%d", i);
				chdir(dirSize);

				parallel[i] = loc_opt_final(nCS[i], oriCS, paras);
				group_dividing(oriCS, nCS[i], paras);

				chdir("../../../");

				if(parallel[i] == 1)
				{
					cs2psoU(paras, nCS[i], swarm[i]);
					cp_psoU_A2B(swarm[i], pbest[i], paras);
					fp = fopen("log.pso", "a+");
					fprintf(fp, "The energy of the %dth structure is: %f\n", i, swarm[i]->energy);
					fclose(fp);
				}
			}
		}
	}
	fp = fopen("log.pso", "a+");
	fprintf(fp, "End local optimization.\n");
	fclose(fp);

	cp_psoU_A2B(pbest[0], gbest, paras);

	for(i=0; i < paras->nBuffH; i++)
		for(j=0; j<3; j++)
			vm->buffPosH[i][j] = paras->vmBuffH;
	for(i=0; i < paras->nBuffL; i++)
		for(j=0; j<3; j++)
			vm->buffPosL[i][j] = paras->vmBuffL;
	for(i=0; i < paras->nOpt; i++)
		for(j=0; j<3; j++)
			vm->optPos[i][j] = paras->vmOpt;
	vm->optH = paras->vmOptH;
	vm->transA = paras->vmTransA;
	vm->transB = paras->vmTransB;

	pso_select(swarm, pbest, gbest, paras);
	sort_CS_psoU(nCS, swarm, pbest, v, paras);
	fp = fopen("log.pso", "a+");
	fprintf(fp, "After DE selection\nparticle  energy\n");
    for(j=0; j < paras->size; j++)
		fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
	fprintf(fp, "PSO has selected best for the _1 generation: %f\n", gbest->energy);
	fclose(fp);

	psoU2cs(paras, oriCS, gbest, bestCS);
	w_ener(bestCS, fileEner);

	fp = fopen("log.pso", "a+");
    fprintf(fp, "Starting PSO main loop...\n");
	fclose(fp);

	omega = 0.9;
	for(i=0; i < paras->nGens; i++)
	{
		fp = fopen("log.pso", "a+");
		fprintf(fp, "\ngeneration %d\n", i);
		fclose(fp);
		chdir("results");
		sprintf(dirGen, "%d", i);
		mkdir(dirGen, S_IRWXU);
		chdir("..");


		if(paras->algoGlob == 1 || paras->algoGlob == 2 || paras->algoGlob == 3)
			diff_evol(swarm, pbest, gbest, v, vm, paras, oriCS);
		else if(paras->algoGlob == 10)
		{
			omega = 0.9 - (0.9-0.4) * i / paras->nGens;
			pso(swarm, pbest, gbest, v, vm, paras, omega, oriCS);
		}
		else if(paras->algoGlob == 11)
			pso_chi(swarm, pbest, gbest, v, vm, paras, oriCS);
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done PSO!\n");
		fclose(fp);
		for(j=0; j < paras->size; j++)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Constraining and checking distances for the %dth PSO unit\n", j);
			fclose(fp);
			if(j < (int)(paras->size * paras->psoProp))
			{
				pso_constr(swarm[j], oriCS, paras);
				symmetry(swarm[j], paras);
				psoU2cs(paras, oriCS, swarm[j], nCS[j]);
			//	cp_opt_1D_A2B(oriCS, nCS[j], paras, 1);
				if(chk_dist(nCS[j], paras) == 1)
				{
					fp = fopen("log.pso", "a+");
					fprintf(fp, "New structure generated to substitute the one PSO generated!\n");
					fclose(fp);
				}
				while(chk_dist(nCS[j], paras) == 1)
					init_struct(nCS[j], oriCS, paras);
			}
			else
			{
				fp = fopen("log.pso", "a+");
				fprintf(fp, "Reinitializing for the %dth PSO unit\n", j);
				fclose(fp);
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				fp = fopen("log.pso", "a+");
				fprintf(fp, "End reinitializing\n");
				fclose(fp);
			}			

			fp = fopen("log.pso", "a+");
			fprintf(fp, "Changing directory to start local optimization!\n");
			fclose(fp);
			chdir("results");
			chdir(dirGen);
			sprintf(dirSize, "%d", j);
			mkdir(dirSize, S_IRWXU);
			chdir(dirSize);
			loc_opt_init(nCS[j], paras);
			chdir("../../../");
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Done starting local optimization! Return to the main directory!\n");
			fclose(fp);
			parallel[j] = 0;
		}

		fp = fopen("log.pso", "a+");
		fprintf(fp, "Monitoring if parallelization has done...\n");
		fclose(fp);
		while(par_done(parallel, paras) == 0)
		{
			for(j=0; j < paras->size; j++)
			{
				if(parallel[j] == 0)
				{
					chdir("results");
					chdir(dirGen);
					sprintf(dirSize, "%d", j);
					chdir(dirSize);

					parallel[j] = loc_opt_final(nCS[j], oriCS, paras);
					group_dividing(oriCS, nCS[j], paras);
					chdir("../../../");
					if(parallel[j] == 1)
					{
						cs2psoU(paras, nCS[j], swarm[j]);
						fp = fopen("log.pso", "a+");
						fprintf(fp, "The energy of the %dth structure is: %f\n", j, swarm[j]->energy);
						fclose(fp);
					}
				}
			}
		}
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done parallel local optimization! Return to main directory.\n");
		fclose(fp);

		if(paras->rmDup > 0)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Starting removing duplicates!\n");
			fclose(fp);
			sort_CS_psoU(nCS, swarm, pbest, v, paras);
		}
		for(j=0; j < paras->size; j++)
		{
			if((paras->rmDup > 0) && (chk_dup(nCS, paras, j) == 1))
			{
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				chdir("results");
				chdir(dirGen);
				sprintf(dirSize, "%d", j);
				chdir(dirSize);
				loc_opt_init(nCS[j], paras);
				cs2psoU(paras, nCS[j], pbest[j]);
				for(k=0; k < paras->nBuffH; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosH[k][l] = 0;
				for(k=0; k < paras->nBuffL; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosL[k][l] = 0;
				for(k=0; k < paras->nOpt; k++)
					for(l=0; l<3; l++)
						v[j]->optPos[k][l] = 0;
				v[j]->optH = 0;
				v[j]->energy = 0;
				parallel[j] = 0;
				chdir("../../../");
			}
		}

		while(par_done(parallel, paras) == 0)
		{
			for(j=0; j < paras->size; j++)
			{
				if(parallel[j] == 0)
				{
					chdir("results");
					chdir(dirGen);
					sprintf(dirSize, "%d", j);
					chdir(dirSize);

					parallel[j] = loc_opt_final(nCS[j], oriCS, paras);
					group_dividing(oriCS, nCS[j], paras);
					chdir("../../../");
					
					if(parallel[j] == 1)
					{
						cs2psoU(paras, nCS[j], swarm[j]);
						fp = fopen("log.pso", "a+");
						fprintf(fp, "The energy of the %dth structure is: %f\n", j, swarm[j]->energy);
						fclose(fp);
					}				
				}
			}
		}
		if(paras->rmDup > 0)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Done removing duplicates!\n");
			fclose(fp);
		}
	
		pso_select(swarm, pbest, gbest, paras);
		fp = fopen("log.pso", "a+");
		fprintf(fp, "After DE selection\nparticle  energy\n");
		for(j=0; j < paras->size; j++)
			fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
		fprintf(fp, "PSO has selected the gbest for the %d generation: %f\n", i, gbest->energy);
		fclose(fp);
		sort_CS_psoU(nCS, swarm, pbest, v, paras);
		psoU2cs(paras, oriCS, gbest, bestCS);

		printf("generations: %d    energy: %f \n", i, bestCS->energy);
		w_ener(bestCS, fileEner);
	}

	w_cs(bestCS, paras, fileStruct);
	w_vasp(bestCS, paras);
	remove("INCAR");
	strcpy(file, "psoU");
	cs2psoU(paras, bestCS, gbest);
	w_psoU(gbest, paras, file);

	fp = fopen("log.pso", "a+");
	fprintf(fp, "Finishing Particle Swarm Optimization!\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		del_CS(nCS[i], paras);
		del_psoU(swarm[i], paras);
		del_psoU(pbest[i], paras);
		del_psoU(v[i], paras);
	}
	del_CS(bestCS, paras);
	del_psoU(gbest, paras);
	del_psoU(vm, paras);

	free(nCS);
	free(swarm);
	free(pbest);
	free(v);
	free(parallel);

	return;
}

void pso_opt_adaptive(parameter *paras, cryStruct *oriCS, cryStruct **nCS)
{
	cryStruct *bestCS;
	psoUnit **swarm, **pbest, *gbest, **v, *vm;
	int *parallel;
	double omega;
	char dirGen[20], dirSize[20];
	char fileEner[20], fileStruct[20], file[20];
	int i, j, k, l;
	FILE *fp;

	parallel = (int*)malloc(paras->size*sizeof(int));

	strcpy(fileEner, "energy");
	strcpy(fileStruct, "struct.out");
   
	fp = fopen("log.pso", "w");
	fprintf(fp, "Starting Particle Swarm Optimization\n");
	fclose(fp);

	w_init(fileEner);
	w_init(fileStruct);

	bestCS = new_CS(paras);
	swarm = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	pbest = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	gbest = new_psoU(paras);
	v = (psoUnit**)malloc(paras->size * sizeof(psoUnit*));
	vm = new_psoU(paras);

	for(i=0; i < paras->size; i++)
	{
		swarm[i] = new_psoU(paras);
		pbest[i] = new_psoU(paras);
		v[i] = new_psoU(paras);
	}

	mkdir("results", S_IRWXU);
	chdir("results");
	mkdir("_1", S_IRWXU);
	chdir("..");
	fp = fopen("log.pso", "a+");
//	fprintf(fp, "Generating new structures...\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		chdir("results");
		chdir("_1");
		sprintf(dirSize, "%d", i);
		mkdir(dirSize, S_IRWXU);
		chdir(dirSize);
		loc_opt_init(nCS[i], paras);
		chdir("../../../");
		parallel[i] = 0;
	
		for(j=0; j < paras->nBuffH; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosH[j][k] = 0;
		for(j=0; j < paras->nBuffL; j++)
			for(k=0; k<3; k++)
				v[i]->buffPosL[j][k] = 0;
		for(j=0; j < paras->nOpt; j++)
			for(k=0; k<3; k++)
				v[i]->optPos[j][k] = 0;
		v[i]->optH = 0;
		v[i]->transA = 0;
		v[i]->transB = 0;
		v[i]->energy = 0;
	}
	fp = fopen("log.pso", "a+");
	fprintf(fp, "Starting local optimization for initial structures\n");
	fclose(fp);
	while(par_done(parallel, paras) == 0)
	{
		for(i=0; i < paras->size; i++)
		{
			if(parallel[i] == 0)
			{
				chdir("results");
				chdir("_1");
				sprintf(dirSize, "%d", i);
				chdir(dirSize);

				parallel[i] = loc_opt_final(nCS[i], oriCS, paras);
				group_dividing(oriCS, nCS[i], paras);

				chdir("../../../");

				if(parallel[i] == 1)
				{
					cs2psoU(paras, nCS[i], swarm[i]);
					cp_psoU_A2B(swarm[i], pbest[i], paras);
					fp = fopen("log.pso", "a+");
					fprintf(fp, "The energy of the %dth structure is: %f\n", i, swarm[i]->energy);
					fclose(fp);
				}
			}
		}
	}
	
	if(paras->rmDup > 0)
	{
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Starting removing duplicates!\n");
		fclose(fp);
		sort_CS_psoU(nCS, swarm, pbest, v, paras);
	}
	for(i=0; i < paras->size; i++)
	{
		if((paras->rmDup > 0) && (chk_dup(nCS, paras, i) == 1))
		{
			do
			{
				init_struct(nCS[i], oriCS, paras);
			}while(chk_dist(nCS[i], paras) == 1);
			chdir("results");
			chdir("_1");
			sprintf(dirSize, "%d", i);
			chdir(dirSize);
			loc_opt_init(nCS[i], paras);
			cs2psoU(paras, nCS[i], pbest[i]);
			for(j=0; j < paras->nBuffH; j++)
				for(k=0; k<3; k++)
					v[i]->buffPosH[j][k] = 0;
			for(j=0; j < paras->nBuffL; j++)
				for(k=0; k<3; k++)
					v[i]->buffPosL[j][k] = 0;
			for(j=0; j < paras->nOpt; j++)
				for(k=0; k<3; k++)
					v[i]->optPos[j][k] = 0;
			v[i]->optH = 0;
			v[i]->energy = 0;
			parallel[i] = 0;
			chdir("../../../");
		}
	}

	while(par_done(parallel, paras) == 0)
	{
		for(i=0; i < paras->size; i++)
		{
			if(parallel[i] == 0)
			{
				chdir("results");
				chdir("_1");
				sprintf(dirSize, "%d", i);
				chdir(dirSize);

				parallel[i] = loc_opt_final(nCS[i], oriCS, paras);
				group_dividing(oriCS, nCS[i], paras);
				chdir("../../../");
				
				if(parallel[i] == 1)
				{
					cs2psoU(paras, nCS[i], swarm[i]);
					fp = fopen("log.pso", "a+");
					fprintf(fp, "The energy of the %dth structure is: %f\n", i, swarm[i]->energy);
					fclose(fp);
				}				
			}
		}
	}
	if(paras->rmDup > 0)
	{
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done removing duplicates!\n");
		fclose(fp);
	}

	fp = fopen("log.pso", "a+");
	fprintf(fp, "End local optimization.\n");
	fclose(fp);

	cp_psoU_A2B(pbest[0], gbest, paras);

	for(i=0; i < paras->nBuffH; i++)
		for(j=0; j<3; j++)
			vm->buffPosH[i][j] = paras->vmBuffH;
	for(i=0; i < paras->nBuffL; i++)
		for(j=0; j<3; j++)
			vm->buffPosL[i][j] = paras->vmBuffL;
	for(i=0; i < paras->nOpt; i++)
		for(j=0; j<3; j++)
			vm->optPos[i][j] = paras->vmOpt;
	vm->optH = paras->vmOptH;
	vm->transA = paras->vmTransA;
	vm->transB = paras->vmTransB;

	pso_select(swarm, pbest, gbest, paras);
	sort_CS_psoU(nCS, swarm, pbest, v, paras);
	fp = fopen("log.pso", "a+");
	fprintf(fp, "After DE selection\nparticle  energy\n");
    for(j=0; j < paras->size; j++)
	   	fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
	fprintf(fp, "PSO has selected best for the _1 generation: %f\n", gbest->energy);
	fclose(fp);

	psoU2cs(paras, oriCS, gbest, bestCS);
	w_ener(bestCS, fileEner);

	fp = fopen("log.pso", "a+");
	fprintf(fp, "Starting PSO main loop...\n");
	fclose(fp);

	omega = 0.9;
	for(i=0; i < paras->nGens; i++)
	{
		fp = fopen("log.pso", "a+");
		fprintf(fp, "\ngeneration %d\n", i);
		fclose(fp);
		chdir("results");
		sprintf(dirGen, "%d", i);
		mkdir(dirGen, S_IRWXU);
		chdir("..");

		if(paras->algoGlob == 1 || paras->algoGlob == 2 || paras->algoGlob == 3)
			diff_evol(swarm, pbest, gbest, v, vm, paras, oriCS);
		else if(paras->algoGlob == 10)
		{
			omega = 0.9 - (0.9-0.4) * i / paras->nGens;
			pso(swarm, pbest, gbest, v, vm, paras, omega, oriCS);
		}
		else if(paras->algoGlob == 11)
			pso_chi(swarm, pbest, gbest, v, vm, paras, oriCS);

		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done PSO!\n");
		fclose(fp);
		for(j=0; j < paras->size; j++)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Constraining and checking distances for the %dth PSO unit\n", j);
			fclose(fp);
			if(j < (int)(paras->size * paras->psoProp))
			{
				pso_constr(swarm[j], oriCS, paras);
				symmetry(swarm[j], paras);
				psoU2cs(paras, oriCS, swarm[j], nCS[j]);
			//	cp_opt_1D_A2B(oriCS, nCS[j], paras, 1);
				if(chk_dist(nCS[j], paras) == 1)
				{
					fp = fopen("log.pso", "a+");
					fprintf(fp, "New structure generated to substitute the one PSO generated!\n");
					fclose(fp);
				}
				while(chk_dist(nCS[j], paras) == 1)
					init_struct(nCS[j], oriCS, paras);
			}
			else
			{
				fp = fopen("log.pso", "a+");
				fprintf(fp, "Reinitializing for the %dth PSO unit\n", j);
				fclose(fp);
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				fp = fopen("log.pso", "a+");
				fprintf(fp, "End reinitializing\n");
				fclose(fp);
			}			

			fp = fopen("log.pso", "a+");
			fprintf(fp, "Changing directory to start local optimization!\n");
			fclose(fp);
			chdir("results");
			chdir(dirGen);
			sprintf(dirSize, "%d", j);
			mkdir(dirSize, S_IRWXU);
			chdir(dirSize);
			loc_opt_init(nCS[j], paras);
			chdir("../../../");
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Done starting local optimization! Return to the main directory!\n");
			fclose(fp);
			parallel[j] = 0;
		}

		fp = fopen("log.pso", "a+");
		fprintf(fp, "Monitoring if parallelization has done...\n");
		fclose(fp);
		while(par_done(parallel, paras) == 0)
		{
			for(j=0; j < paras->size; j++)
			{
				if(parallel[j] == 0)
				{
					chdir("results");
					chdir(dirGen);
					sprintf(dirSize, "%d", j);
					chdir(dirSize);

					parallel[j] = loc_opt_final(nCS[j], oriCS, paras);
					group_dividing(oriCS, nCS[j], paras);
					chdir("../../../");
					if(parallel[j] == 1)
					{
						cs2psoU(paras, nCS[j], swarm[j]);
						fp = fopen("log.pso", "a+");
						fprintf(fp, "The energy of the %dth structure is: %f\n", j, swarm[j]->energy);
						fclose(fp);
					}
				}
			}
		}
		fp = fopen("log.pso", "a+");
		fprintf(fp, "Done parallel local optimization! Return to main directory.\n");
		fclose(fp);

		if(paras->rmDup > 0)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Starting removing duplicates!\n");
			fclose(fp);
			sort_CS_psoU(nCS, swarm, pbest, v, paras);
		}
		for(j=0; j < paras->size; j++)
		{
			if((paras->rmDup > 0) && (chk_dup(nCS, paras, j) == 1))
			{
				do
				{
					init_struct(nCS[j], oriCS, paras);
				}while(chk_dist(nCS[j], paras) == 1);
				chdir("results");
				chdir(dirGen);
				sprintf(dirSize, "%d", j);
				chdir(dirSize);
				loc_opt_init(nCS[j], paras);
				cs2psoU(paras, nCS[j], pbest[j]);
				for(k=0; k < paras->nBuffH; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosH[k][l] = 0;
				for(k=0; k < paras->nBuffL; k++)
					for(l=0; l<3; l++)
						v[j]->buffPosL[k][l] = 0;
				for(k=0; k < paras->nOpt; k++)
					for(l=0; l<3; l++)
						v[j]->optPos[k][l] = 0;
				v[j]->optH = 0;
				v[j]->energy = 0;
				parallel[j] = 0;
				chdir("../../../");
			}
		}

		while(par_done(parallel, paras) == 0)
		{
			for(j=0; j < paras->size; j++)
			{
				if(parallel[j] == 0)
				{
					chdir("results");
					chdir(dirGen);
					sprintf(dirSize, "%d", j);
					chdir(dirSize);

					parallel[j] = loc_opt_final(nCS[j], oriCS, paras);
					group_dividing(oriCS, nCS[j], paras);
					chdir("../../../");
					
					if(parallel[j] == 1)
					{
						cs2psoU(paras, nCS[j], swarm[j]);
						fp = fopen("log.pso", "a+");
						fprintf(fp, "The energy of the %dth structure is: %f\n", j, swarm[j]->energy);
						fclose(fp);
					}				
				}
			}
		}
		if(paras->rmDup > 0)
		{
			fp = fopen("log.pso", "a+");
			fprintf(fp, "Done removing duplicates!\n");
			fclose(fp);
		}
	
		pso_select(swarm, pbest, gbest, paras);
		fp = fopen("log.pso", "a+");
		fprintf(fp, "After DE selection\nparticle  energy\n");
		for(j=0; j < paras->size; j++)
			fprintf(fp, "%d  %f\n", j, swarm[j]->energy);
		fprintf(fp, "PSO has selected the gbest for the %d generation: %f\n", i, gbest->energy);
		fclose(fp);
		sort_CS_psoU(nCS, swarm, pbest, v, paras);
		psoU2cs(paras, oriCS, gbest, bestCS);

		printf("generations: %d    energy: %f \n", i, bestCS->energy);
		w_ener(bestCS, fileEner);
	}

	w_cs(bestCS, paras, fileStruct);
	w_vasp(bestCS, paras);
	remove("INCAR");
	strcpy(file, "psoU");
	cs2psoU(paras, bestCS, gbest);
	w_psoU(gbest, paras, file);

	fp = fopen("log.pso", "a+");
	fprintf(fp, "Finishing Particle Swarm Optimization!\n");
	fclose(fp);
	for(i=0; i < paras->size; i++)
	{
		del_psoU(swarm[i], paras);
		del_psoU(pbest[i], paras);
		del_psoU(v[i], paras);
	}
	del_CS(bestCS, paras);
	del_psoU(gbest, paras);
	del_psoU(vm, paras);

	free(swarm);
	free(pbest);
	free(v);
	free(parallel);

	return;
}
