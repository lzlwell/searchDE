#include"i_o.h"

void r_set(parameter *paras)
{
	FILE *fp;
	int i;

	fp = fopen("paras.in", "r");

	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->interface);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->adaptive);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->run);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->rSeed);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nType);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	paras->type = (char**)malloc(paras->nType*sizeof(char*));
	for(i=0; i < paras->nType; i++)
	{
		paras->type[i] = (char*)malloc(5*sizeof(char));
		fscanf(fp, "%s", paras->type[i]);
	}
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	paras->charge = (double*)malloc(paras->nType*sizeof(double));
	for(i=0; i < paras->nType; i++)
		fscanf(fp, "%lf", &paras->charge[i]);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nFixH);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nFixL);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nBuffH);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nBuffL);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nOpt);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->buffBot);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->buffTop);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->optBot);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->optTop);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->hMin);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->hMax);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->hMix);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->distMin);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->algoGlob);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->algoLoc);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->size);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nGens);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmBuffH);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmBuffL);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmOpt);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmOptH);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->wChgLmp);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->psoProp);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->rmDup);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->devM);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->eDiff);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->vaspNSW);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->keepOri);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->vaspGens);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->lammpsGens);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->autoInitPot);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nFit);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->rigid);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->transAM);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->transBM);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmTransA);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->vmTransB);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->transAB);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->dim2);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->dim2y);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nonDim2type);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->inCD);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->symmetry);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->symMix);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->nRmFile);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	paras->rmFile = (char**)malloc(paras->nRmFile*sizeof(char*));
	for(i=0; i < paras->nRmFile; i++)
	{
		paras->rmFile[i] = (char*)malloc(50*sizeof(char));
		fscanf(fp, "%s", paras->rmFile[i]);
	}
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->dvdOpt);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%d", &paras->dvdA);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->diffEvolF);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '=');
	fscanf(fp, "%lf", &paras->diffEvolCR);

	return;
}

void r_pos(cryStruct *oriCS, parameter *paras)
{
	int i, j;
	FILE *fp;
	double direct[3];

	fp = fopen("struct.in", "r");

	while(fgetc(fp) != '\n');
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->latt[i][j]);
		while(fgetc(fp) != '\n');
	}

	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nFixH; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->fixPosH[i][j]);
		fscanf(fp, "%s", oriCS->fixTpH[i]);
		while(fgetc(fp) != '\n');

		if(paras->inCD == 0)
		{
			car2dir(oriCS->fixPosH[i], direct, oriCS->latt);
			for(j=0; j<3; j++)
				oriCS->fixPosH[i][j] = direct[j];
		}
	}
	
	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nFixL; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->fixPosL[i][j]);
		fscanf(fp, "%s", oriCS->fixTpL[i]);
		while(fgetc(fp) != '\n');

		if(paras->inCD == 0)
		{
			car2dir(oriCS->fixPosL[i], direct, oriCS->latt);
			for(j=0; j<3; j++)
				oriCS->fixPosL[i][j] = direct[j];
		}
	}
	
	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nBuffH; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->buffPosH[i][j]);
		fscanf(fp, "%s", oriCS->buffTpH[i]);
		while(fgetc(fp) != '\n');

		if(paras->inCD == 0)
		{
			car2dir(oriCS->buffPosH[i], direct, oriCS->latt);
			for(j=0; j<3; j++)
				oriCS->buffPosH[i][j] = direct[j];
		}
	}

	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nBuffL; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->buffPosL[i][j]);
		fscanf(fp, "%s", oriCS->buffTpL[i]);
		while(fgetc(fp) != '\n');

		if(paras->inCD == 0)
		{
			car2dir(oriCS->buffPosL[i], direct, oriCS->latt);
			for(j=0; j<3; j++)
				oriCS->buffPosL[i][j] = direct[j];
		}
	}
	
	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nOpt; i++)
	{
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oriCS->optPos[i][j]);
		fscanf(fp, "%s", oriCS->optTp[i]);
		while(fgetc(fp) != '\n');

		if(paras->inCD == 0)
		{
			car2dir(oriCS->optPos[i], direct, oriCS->latt);
			for(j=0; j<3; j++)
				oriCS->optPos[i][j] = direct[j];
		}
	}
	
	fclose(fp);

	return;
}

void w_init(char *file)
{
	FILE *fp;
	fp = fopen(file, "w+");

	fclose(fp);

	return;
}

void w_cs(cryStruct *oneCS, parameter *paras, char *file)
{
	FILE *fp;
	int i;

	fp = fopen(file, "w");

	fprintf(fp, "latt\n");
	for(i=0; i<3; i++)
		fprintf(fp, "%f  %f  %f\n", oneCS->latt[i][0], oneCS->latt[i][1], oneCS->latt[i][2]);
	fprintf(fp, "fixPosH\n");
	for(i=0; i < paras->nFixH; i++)
		fprintf(fp, "%f  %f  %f  %s\n", oneCS->fixPosH[i][0], oneCS->fixPosH[i][1], oneCS->fixPosH[i][2], oneCS->fixTpH[i]);
	fprintf(fp, "fixPosL\n");
	for(i=0; i < paras->nFixL; i++)
		fprintf(fp, "%f  %f  %f  %s\n", oneCS->fixPosL[i][0], oneCS->fixPosL[i][1], oneCS->fixPosL[i][2], oneCS->fixTpL[i]);
	fprintf(fp, "buffPosH\n");
	for(i=0; i < paras->nBuffH; i++)
		fprintf(fp, "%f  %f  %f  %s\n", oneCS->buffPosH[i][0], oneCS->buffPosH[i][1], oneCS->buffPosH[i][2], oneCS->buffTpH[i]);
	fprintf(fp, "buffPosL\n");
	for(i=0; i < paras->nBuffL; i++)
		fprintf(fp, "%f  %f  %f  %s\n", oneCS->buffPosL[i][0], oneCS->buffPosL[i][1], oneCS->buffPosL[i][2], oneCS->buffTpL[i]);
	fprintf(fp, "optPos\n");
	for(i=0; i < paras->nOpt; i++)
		fprintf(fp, "%f  %f  %f  %s\n", oneCS->optPos[i][0], oneCS->optPos[i][1], oneCS->optPos[i][2], oneCS->optTp[i]);
	
	fclose(fp);

	return;
}

void w_psoU(psoUnit *psoU, parameter *paras, char *file)
{
	FILE *fp;
	int i;

	fp = fopen(file, "w");

	fprintf(fp, "buffPosH\n");
	for(i=0; i < paras->nBuffH; i++)
		fprintf(fp, "%f  %f  %f\n", psoU->buffPosH[i][0], psoU->buffPosH[i][1], psoU->buffPosH[i][2]);
	fprintf(fp, "buffPosL\n");
	for(i=0; i < paras->nBuffL; i++)
		fprintf(fp, "%f  %f  %f\n", psoU->buffPosL[i][0], psoU->buffPosL[i][1], psoU->buffPosL[i][2]);
	fprintf(fp, "optPos\n");
	for(i=0; i < paras->nOpt; i++)
		fprintf(fp, "%f  %f  %f\n", psoU->optPos[i][0], psoU->optPos[i][1], psoU->optPos[i][2]);
	fprintf(fp, "optH\n%f\n", psoU->optH);
	fprintf(fp, "transA\n%f\n", psoU->transA);
	fprintf(fp, "transB\n%f\n", psoU->transB);
	
	fclose(fp);

	return;
}

void w_ener(cryStruct *oneCS, char *file)
{
	FILE *fp;
	fp = fopen(file, "a+");
	fprintf(fp, "%f\n", oneCS->energy);

	fclose(fp);

	return;
}

void w_lammps(cryStruct *oneCS, parameter *paras)
{
	FILE *fp;
	double *car;
	int i, count;
	car = (double*)malloc(3*sizeof(double));

	fp = fopen("struct.lammps", "w");

	fprintf(fp, "search structure\n\n");
	fprintf(fp, "%d atoms\n", paras->nFixH + paras->nFixL + paras->nBuffH + paras->nBuffL + paras->nOpt);
	fprintf(fp, "%d  atom types\n\n", paras->nType);
	fprintf(fp, "0   %f xlo xhi\n0   %f ylo yhi\n0   %f zlo zhi\n\n", oneCS->latt[0][0], oneCS->latt[1][1], oneCS->latt[2][2]);
	fprintf(fp, "Atoms\n\n");
	
	count = 0;
	for(i=0; i < paras->nFixH; i++)
	{
		dir2car(oneCS->fixPosH[i], car, oneCS->latt);
		count++;
		fprintf(fp, "%d %d %f %f %f", count, get_type(oneCS->fixTpH[i], paras)+1, car[0], car[1], car[2]);
		if(paras->wChgLmp == 1)
			fprintf(fp, " %f\n", oneCS->charge[get_type(oneCS->fixTpH[i], paras)]);
		else if(paras->wChgLmp == 0)
			fprintf(fp, "\n");
	}
	for(i=0; i < paras->nFixL; i++)
	{
		dir2car(oneCS->fixPosL[i], car, oneCS->latt);
		count++;
		fprintf(fp, "%d %d %f %f %f", count, get_type(oneCS->fixTpL[i], paras)+1, car[0], car[1], car[2]);
		if(paras->wChgLmp == 1)
			fprintf(fp, " %f\n", oneCS->charge[get_type(oneCS->fixTpL[i], paras)]);
		else if(paras->wChgLmp == 0)
			fprintf(fp, "\n");
	}
	for(i=0; i < paras->nBuffH; i++)
	{
		dir2car(oneCS->buffPosH[i], car, oneCS->latt);
		count++;
		fprintf(fp, "%d %d %f %f %f", count, get_type(oneCS->buffTpH[i], paras)+1, car[0], car[1], car[2]);
		if(paras->wChgLmp == 1)
			fprintf(fp, " %f\n", oneCS->charge[get_type(oneCS->buffTpH[i], paras)]);
		else if(paras->wChgLmp == 0)
			fprintf(fp, "\n");
	}
	for(i=0; i < paras->nBuffL; i++)
	{
		dir2car(oneCS->buffPosL[i], car, oneCS->latt);
		count++;
		fprintf(fp, "%d %d %f %f %f", count, get_type(oneCS->buffTpL[i], paras)+1, car[0], car[1], car[2]);
		if(paras->wChgLmp == 1)
			fprintf(fp, " %f\n", oneCS->charge[get_type(oneCS->buffTpL[i], paras)]);
		else if(paras->wChgLmp == 0)
			fprintf(fp, "\n");
	}
	for(i=0; i < paras->nOpt; i++)
	{
		dir2car(oneCS->optPos[i], car, oneCS->latt);
		count++;
		fprintf(fp, "%d %d %f %f %f", count, get_type(oneCS->optTp[i], paras)+1, car[0], car[1], car[2]);
		if(paras->wChgLmp == 1)
			fprintf(fp, " %f\n", oneCS->charge[get_type(oneCS->optTp[i], paras)]);
		else if(paras->wChgLmp == 0)
			fprintf(fp, "\n");
	}

	free(car);
	fclose(fp);

	return;
}

void r_lammps(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	FILE *fp;
	double *car, tmpd;
	int i, step, tmpi;
	char *tmps;

	car = (double*)malloc(3*sizeof(double));
	tmps = (char*)malloc(100*sizeof(char));

	system("grep Loop log.lammps > .tmp_file");
	fp = fopen(".tmp_file", "r");
	fscanf(fp, "%s %s %s %lf %s %d %s %s %d", tmps, tmps, tmps, &tmpd, tmps, &tmpi, tmps, tmps, &step);
	fclose(fp);

	system("wc -l log.lammps > .tmp_file");
	system("sed -i \"s/log.lammps//g\" .tmp_file");
	system("grep -A $(cat .tmp_file) Step log.lammps > .tmp_file");
	fp = fopen(".tmp_file", "r");
	while(fgetc(fp) != '\n');
	for(i=0; i<step; i++)
		while(fgetc(fp) != '\n');
	fscanf(fp, "%d %lf %lf %lf %lf %lf", &tmpi, &tmpd, &tmpd, &oneCS->latt[0][0], &oneCS->latt[1][1], &oneCS->latt[2][2]);
	fclose(fp);

	system("grep -A 1 Energy log.lammps > .tmp_file");
	fp = fopen(".tmp_file", "r");
	while(fgetc(fp) != '\n');
	fscanf(fp, "%lf %lf %lf", &tmpd, &tmpd, &oneCS->energy);
	fclose(fp);
	remove(".tmp_file");
	
	fp = fopen("dump.atom", "r");
	for(i=0; i < paras->nFixH + paras->nFixL + paras->nBuffH + paras-> nBuffL + paras->nOpt + 4; i++)
		while(fgetc(fp) != '\n');
	for(i=0; i < paras->nFixH; i++)
	{
		fscanf(fp, "%d %lf %lf %lf", &tmpi, &car[0], &car[1], &car[2]);
		car2dir(car, oneCS->fixPosH[i], oneCS->latt);
	}
	for(i=0; i < paras->nFixL; i++)
	{
		fscanf(fp, "%d %lf %lf %lf", &tmpi, &car[0], &car[1], &car[2]);
		car2dir(car, oneCS->fixPosL[i], oneCS->latt);
	}
	for(i=0; i < paras->nBuffH; i++)
	{
		fscanf(fp, "%d %lf %lf %lf", &tmpi, &car[0], &car[1], &car[2]);
		car2dir(car, oneCS->buffPosH[i], oneCS->latt);
	}
	for(i=0; i < paras->nBuffL; i++)
	{
		fscanf(fp, "%d %lf %lf %lf", &tmpi, &car[0], &car[1], &car[2]);
		car2dir(car, oneCS->buffPosL[i], oneCS->latt);
	}
	for(i=0; i < paras->nOpt; i++)
	{
		fscanf(fp, "%d %lf %lf %lf", &tmpi, &car[0], &car[1], &car[2]);
		car2dir(car, oneCS->optPos[i], oneCS->latt);
	}
	fclose(fp);

	if(paras->interface == 1)
		oneCS->optH = oriCS->optH + oneCS->latt[2][2] - oriCS->latt[2][2];
	else if(paras->interface == 2)
		oneCS->optH = oriCS->optH + \
					  (oneCS->fixPosH[0][2] - oneCS->fixPosL[0][2]) * oneCS->latt[2][2] - \
					  (oriCS->fixPosH[0][2] - oriCS->fixPosL[0][2]) * oriCS->latt[2][2];

	if(paras->transAB == 0)
	{
		oneCS->transA = 0.0;
		oneCS->transB = 0.0;
	}
	else if(paras->transAB = 1)
	{
		oneCS->transA = oneCS->fixPosH[0][0] - oriCS->fixPosH[0][0];
		oneCS->transB = oneCS->fixPosH[0][1] - oriCS->fixPosH[0][1];

		if(oneCS->transA > 0.5)
			oneCS->transA --;
		else if(oneCS->transA < -0.5)
			oneCS->transA ++;

		if(oneCS->transB > 0.5)
			oneCS->transB --;
		else if(oneCS->transB < -0.5)
			oneCS->transB ++;

		if(fabs(oneCS->transA) > fabs(paras->transAM))
			paras->transAM = fabs(oneCS->transA);
		if(fabs(oneCS->transB) > fabs(paras->transBM))
			paras->transBM = fabs(oneCS->transB);
	}

	free(car);
	free(tmps);

	return;
}

void r_seed(int *ij, int *kl, char *file)
{
	FILE *fp;

	fp = fopen(file, "r");
	fscanf(fp, "%d %d", ij, kl);
	fclose(fp);

	return;
}

void w_seed(int ij, int kl, char *file)
{
	FILE *fp;

	fp = fopen(file, "w");
	fprintf(fp, "%d %d\n", ij, kl);
	fclose(fp);

	return;
}

void w_vasp(cryStruct *oneCS, parameter *paras)
{
	FILE *fp, *fp2;
	int i, j, count;
	int *types;

	types = (int*)malloc(paras->nType * sizeof(int));
	for(i=0; i < paras->nType; i++)
		types[i] = 0;
	for(i=0; i < paras->nFixH; i++)
		types[get_type(oneCS->fixTpH[i], paras)] ++;
	for(i=0; i < paras->nFixL; i++)
		types[get_type(oneCS->fixTpL[i], paras)] ++;
	for(i=0; i < paras->nBuffH; i++)
		types[get_type(oneCS->buffTpH[i], paras)] ++;
	for(i=0; i < paras->nBuffL; i++)
		types[get_type(oneCS->buffTpL[i], paras)] ++;
	for(i=0; i < paras->nOpt; i++)
		types[get_type(oneCS->optTp[i], paras)] ++;

	fp = fopen("POSCAR", "w");
	fp2 = fopen("INCAR", "a+");

	fprintf(fp, "search\n");
	fprintf(fp, "1.0\n");
	for(i=0; i<3; i++)
		fprintf(fp, "%f %f %f\n", oneCS->latt[i][0], oneCS->latt[i][1], oneCS->latt[i][2]);
	for(i=0; i < paras->nType; i++)
		fprintf(fp, "%s ", paras->type[i]);
	fprintf(fp, "\n");
	for(i=0; i < paras->nType; i++)
		fprintf(fp, "%d ", types[i]);
	fprintf(fp, "\nSelective dynamics\n");
	fprintf(fp, "Direct\n");
	if(paras->rigid == 1)
		fprintf(fp2, "\n\n\nRIGID =");
	count = 0;
	for(i=0; i < paras->nType; i++)
	{
		for(j=0; j < paras->nFixH; j++)
			if(get_type(oneCS->fixTpH[j], paras) == i)
			{
				count ++;
				if(paras->rigid == 0)
					fprintf(fp, "%f %f %f F F F\n", oneCS->fixPosH[j][0], oneCS->fixPosH[j][1], oneCS->fixPosH[j][2]);
				else if(paras->rigid == 1)
				{
					if(paras->transAB == 0)
						fprintf(fp, "%f %f %f F F T\n", oneCS->fixPosH[j][0], oneCS->fixPosH[j][1], oneCS->fixPosH[j][2]);
					else if(paras->transAB == 1)
					{
						if((paras->dim2 == 1) && (paras->nonDim2type != i))
							fprintf(fp, "%f %f %f T F T\n", oneCS->fixPosH[j][0], oneCS->fixPosH[j][1], oneCS->fixPosH[j][2]);
						else
							fprintf(fp, "%f %f %f T T T\n", oneCS->fixPosH[j][0], oneCS->fixPosH[j][1], oneCS->fixPosH[j][2]);
					}
					fprintf(fp2, " %d", count);
				}
			}
		for(j=0; j < paras->nFixL; j++)
			if(get_type(oneCS->fixTpL[j], paras) == i)
			{
				count ++;
				fprintf(fp, "%f %f %f F F F\n", oneCS->fixPosL[j][0], oneCS->fixPosL[j][1], oneCS->fixPosL[j][2]);
			}
		for(j=0; j < paras->nBuffH; j++)
			if(get_type(oneCS->buffTpH[j], paras) == i)
			{
				count ++;
				if((paras->dim2 == 1) && (paras->nonDim2type != i))
					fprintf(fp, "%f %f %f T F T\n", oneCS->buffPosH[j][0], oneCS->buffPosH[j][1], oneCS->buffPosH[j][2]);
				else
					fprintf(fp, "%f %f %f T T T\n", oneCS->buffPosH[j][0], oneCS->buffPosH[j][1], oneCS->buffPosH[j][2]);
			}
		for(j=0; j < paras->nBuffL; j++)
			if(get_type(oneCS->buffTpL[j], paras) == i)
			{
				count ++;
				if((paras->dim2 == 1) && (paras->nonDim2type != i))
					fprintf(fp, "%f %f %f T F T\n", oneCS->buffPosL[j][0], oneCS->buffPosL[j][1], oneCS->buffPosL[j][2]);
				else
					fprintf(fp, "%f %f %f T T T\n", oneCS->buffPosL[j][0], oneCS->buffPosL[j][1], oneCS->buffPosL[j][2]);
			}
		for(j=0; j < paras->nOpt; j++)
			if(get_type(oneCS->optTp[j], paras) == i)
			{
				count ++;
				if((paras->dim2 == 1) && (paras->nonDim2type != i))
					fprintf(fp, "%f %f %f T F T\n", oneCS->optPos[j][0], oneCS->optPos[j][1], oneCS->optPos[j][2]);
				else
					fprintf(fp, "%f %f %f T T T\n", oneCS->optPos[j][0], oneCS->optPos[j][1], oneCS->optPos[j][2]);
			}
	}
	fprintf(fp2, "\n\n");

	fclose(fp);
	fclose(fp2);
	free(types);

	return;
}

void r_vasp(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	FILE *fp;
	int i, j, *types, tmpi;
	int a=0, b=0, c=0, d=0, e=0;
	double lattC, tmpd;

	types = (int*)malloc(paras->nType * sizeof(int));
	fp = fopen("CONTCAR", "r");

	while(fgetc(fp) != '\n');
	fscanf(fp, "%lf", &lattC);
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			fscanf(fp, "%lf", &oneCS->latt[i][j]);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nType; i++)
		fscanf(fp, "%d", &types[i]);
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '\n');
	while(fgetc(fp) != '\n');
	for(i=0; i < paras->nType; i++)
	{
		for(j=0; j<types[i]; j++)
		{
			if((a < paras->nFixH) && (get_type(oriCS->fixTpH[a], paras) == i))
			{
				fscanf(fp, "%lf %lf %lf", &oneCS->fixPosH[a][0], &oneCS->fixPosH[a][1], &oneCS->fixPosH[a][2]);
				while(fgetc(fp) != '\n');
				a++;
			}
			else if((b < paras->nFixL) && (get_type(oriCS->fixTpL[b], paras) == i))
			{
				fscanf(fp, "%lf %lf %lf", &oneCS->fixPosL[b][0], &oneCS->fixPosL[b][1], &oneCS->fixPosL[b][2]);
				while(fgetc(fp) != '\n');
				b++;
			}
			else if((c < paras->nBuffH) && (get_type(oriCS->buffTpH[c], paras) == i))
			{
				fscanf(fp, "%lf %lf %lf", &oneCS->buffPosH[c][0], &oneCS->buffPosH[c][1], &oneCS->buffPosH[c][2]);
				while(fgetc(fp) != '\n');
				c++;
			}
			else if((d < paras->nBuffL) && (get_type(oriCS->buffTpL[d], paras) == i))
			{
				fscanf(fp, "%lf %lf %lf", &oneCS->buffPosL[d][0], &oneCS->buffPosL[d][1], &oneCS->buffPosL[d][2]);
				while(fgetc(fp) != '\n');
				d++;
			}
			else if((e < paras->nOpt) && (get_type(oriCS->optTp[e], paras) == i))
			{
				fscanf(fp, "%lf %lf %lf", &oneCS->optPos[e][0], &oneCS->optPos[e][1], &oneCS->optPos[e][2]);
				while(fgetc(fp) != '\n');
				e++;
			}
		}
	}

	fclose(fp);

	if(paras->interface == 1)
		oneCS->optH = oriCS->optH + oneCS->latt[2][2] - oriCS->latt[2][2];
	else if(paras->interface == 2)
		oneCS->optH = oriCS->optH + \
					  (oneCS->fixPosH[0][2] - oneCS->fixPosL[0][2]) * oneCS->latt[2][2] - \
					  (oriCS->fixPosH[0][2] - oriCS->fixPosL[0][2]) * oriCS->latt[2][2];

	if(paras->transAB == 0)
	{
		oneCS->transA = 0.0;
		oneCS->transB = 0.0;
	}
	else if(paras->transAB = 1)
	{
		oneCS->transA = oneCS->fixPosH[0][0] - oriCS->fixPosH[0][0];
		oneCS->transB = oneCS->fixPosH[0][1] - oriCS->fixPosH[0][1];

		if(oneCS->transA > 0.5)
			oneCS->transA --;
		else if(oneCS->transA < -0.5)
			oneCS->transA ++;

		if(oneCS->transB > 0.5)
			oneCS->transB --;
		else if(oneCS->transB < -0.5)
			oneCS->transB ++;

		if(fabs(oneCS->transA) > fabs(paras->transAM))
			paras->transAM = fabs(oneCS->transA);
		if(fabs(oneCS->transB) > fabs(paras->transBM))
			paras->transBM = fabs(oneCS->transB);
	}

	system("tail -1 OSZICAR > .tmp_file");
	system("sed -i \"s/F=//g\" .tmp_file");
	system("sed -i \"s/E0=//g\" .tmp_file");
	fp = fopen(".tmp_file", "r");
	fscanf(fp, "%d %lf %lf", &tmpi, &tmpd, &oneCS->energy);
	fclose(fp);
	remove(".tmp_file");

	free(types);

	return;
}

void w_potfit(parameter *paras, char *config, char *startpot, char *tempfile, char *endpot, char *plotfile, char *flagfile)
{
	FILE *fp;
	fp = fopen("potfit.in", "w");

	fprintf(fp, "ntypes\t\t\t%d\n", paras->nType);
	fprintf(fp, "config\t\t\t%s\n", config);
	fprintf(fp, "startpot\t\t\t%s\n", startpot);
	fprintf(fp, "tempfile\t\t\t%s\n", tempfile);
	fprintf(fp, "endpot\t\t\t%s\n", endpot);
	fprintf(fp, "plotfile\t\t\t%s\n", plotfile);
	fprintf(fp, "flagfile\t\t\t%s\n", flagfile);
	fprintf(fp, "# general options\n");
	fprintf(fp, "plotpointfile sampling\n");
	fprintf(fp, "opt \t\t\t1\n");
	fprintf(fp, "anneal_temp\t\t\t1.0\n");
	fprintf(fp, "plotmin\t\t\t0.0\n");
	fprintf(fp, "eng_weight\t\t\t100.\n");
	fprintf(fp, "stress_weight\t\t\t200.\n");
	fprintf(fp, "d_eps\t\t\t0.01\n");

	fclose(fp);

	return;
}

void w_init_pot(parameter *paras, char *startpot)
{
	FILE *fp;
	int i, j;

	fp = fopen(startpot, "w");

	fprintf(fp, "#F 0 %d\n", paras->nType * (paras->nType + 1) / 2 + 2 * paras->nType);
	fprintf(fp, "#T EAM\n");
	fprintf(fp, "#C");
	for(i=0; i < paras->nType; i++)
		fprintf(fp, " %s", paras->type[i]);
	fprintf(fp, "\n##");
	for(i=0; i < paras->nType; i++)
		for(j=i; j < paras->nType; j++)
			fprintf(fp, " %s-%s", paras->type[i], paras->type[j]);
	for(i=0; i < paras->nType; i++)
		fprintf(fp, " %s", paras->type[i]);
	for(i=0; i < paras->nType; i++)
		fprintf(fp, " %s", paras->type[i]);
	fprintf(fp, "\n#E\n");

	for(i=0; i < paras->nType * (paras->nType + 1) / 2; i++)
	{
		fprintf(fp, "\ntype lj\n");
		fprintf(fp, "cutoff 5.000000\n");
		fprintf(fp, "# rmin 1.726198\n");
		fprintf(fp, "a_0 .00144765600000000000 0.00 10.00\n");
		fprintf(fp, "a_1 1.98 1.00 24.68\n");
	}
	for(i=0; i < paras->nType; i++)
	{
		fprintf(fp, "\ntype mexp_decay\n");
		fprintf(fp, "cutoff 5.000000\n");
		fprintf(fp, "# rmin 0.000100\n");
		fprintf(fp, "o_0 1.0000000000e+00 1.00 1.00\n");
		fprintf(fp, "o_1 5.4508974179e-03 0.00 20.01\n");
		fprintf(fp, "o_2 1.0000000000e+00 1.00 1.00\n");
	}
	for(i=0; i < paras->nType; i++)
	{
//		fprintf(fp, "\ntype pohlong\n");
		fprintf(fp, "\ntype bjs\n");
		fprintf(fp, "cutoff 100.00000\n");
		fprintf(fp, "# rmin 1.653518\n");
		fprintf(fp, "m_0 0.00000 -100.00 0.00\n");
		fprintf(fp, "m_1 1.0000000000e+00 1.00 1.00\n");
		fprintf(fp, "m_2 0.0000000000e+00 0.00 0.00\n");
	}

	fclose(fp);

	return;
}

void w_config(cryStruct *oriCS, parameter *paras, char *config)
{
	int i, j, k;
	int natom;
	FILE *fp, *fp2;
	char command[100], tmps[30];
	double data[6], energy;
	int *types;

	types = (int*)malloc(paras->nType * sizeof(int));
	for(i=0; i < paras->nType; i++)
		types[i] = 0;
	for(i=0; i < paras->nFixH; i++)
		types[get_type(oriCS->fixTpH[i], paras)] ++;
	for(i=0; i < paras->nFixL; i++)
		types[get_type(oriCS->fixTpL[i], paras)] ++;
	for(i=0; i < paras->nBuffH; i++)
		types[get_type(oriCS->buffTpH[i], paras)] ++;
	for(i=0; i < paras->nBuffL; i++)
		types[get_type(oriCS->buffTpL[i], paras)] ++;
	for(i=0; i < paras->nOpt; i++)
		types[get_type(oriCS->optTp[i], paras)] ++;

	natom = paras->nFixH + paras->nFixL + paras->nBuffH + paras->nBuffL + paras->nOpt;

	fp = fopen(config, "a+");

	fprintf(fp, "#N %d %d\n", natom, 1);
	fprintf(fp, "#C");
	for(j=0; j < paras->nType; j++)
		fprintf(fp, " %s", paras->type[j]);
	fprintf(fp, "\n");
	fprintf(fp, "## force and energy file generated from ./OUTCAR\n");
	do
	{
		sprintf(command, "grep \"direct lattice vectors\" OUTCAR -A 3 | tail -4 > .tmp1");
		system(command);
		fp2 = fopen(".tmp1", "r");
		fscanf(fp2, "%s", tmps);
		fclose(fp2);
		sleep(1);
	}while(strcmp(tmps, "direct") != 0);
	fp2 = fopen(".tmp1", "r");
	while(fgetc(fp2) != '\n');
	fscanf(fp2, "%lf %lf %lf %lf %lf %lf", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
	fprintf(fp, "#X    %f    %f    %f\n", data[0], data[1], data[2]);
	fscanf(fp2, "%lf %lf %lf %lf %lf %lf", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
	fprintf(fp, "#Y    %f    %f    %f\n", data[0], data[1], data[2]);
	fscanf(fp2, "%lf %lf %lf %lf %lf %lf", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
	fprintf(fp, "#Z    %f    %f    %f\n", data[0], data[1], data[2]);
	fclose(fp2);
	remove(".tmp1");
	fprintf(fp, "#W 1.000000\n");
	do
	{
		sprintf(command, "grep \"energy  without entropy\" OUTCAR > .tmp2");
		system(command);
		fp2 = fopen(".tmp2", "r");
		fscanf(fp2, "%s", tmps);
		fclose(fp2);
		sleep(1);
	}while(strcmp(tmps, "energy") != 0);
	fp2 = fopen(".tmp2", "r");
	while(fgetc(fp2) != '=');
	while(fgetc(fp2) != '=');
	fscanf(fp2, "%lf", &energy);
	fclose(fp2);
	remove(".tmp2");
	fprintf(fp, "#E %f\n", energy/natom);
	fprintf(fp, "#F\n");
	do
	{
		sprintf(command, "grep TOTAL-FORCE OUTCAR -A %d > .tmp3", natom+1);
		system(command);
		fp2 = fopen(".tmp3", "r");
		fscanf(fp2, "%s", tmps);
		fclose(fp2);
		sleep(1);
	}while(strcmp(tmps, "POSITION") != 0);
	fp2 = fopen(".tmp3", "r");
	while(fgetc(fp2) != '\n');
	while(fgetc(fp2) != '\n');
	for(j=0; j < paras->nType; j++)
	{
		for(k=0; k < types[j]; k++)
		{
			fscanf(fp2, "%lf %lf %lf %lf %lf %lf", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
			fprintf(fp, "%d  %f  %f  %f  %f  %f  %f\n", j, data[0], data[1], data[2], data[3], data[4], data[5]);
		}
	}
	fclose(fp2);
	remove(".tmp3");
	fclose(fp);
	free(types);

	return;
}
