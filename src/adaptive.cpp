#include"adaptive.h"

void adaptive(parameter *paras, cryStruct *oriCS)
{
	cryStruct **nCS, **nFitCS;
    char adaptDir[20], vaspDir[20], lammpsDir[20];
	char config[50], startpot[50], tempfile[50], endpot[50], plotfile[50], flagfile[50];
	char command[100], file[50];
	int size, rmDup;
	double devM, eDiff;
	int i, j;
	FILE *fp;

	fp = fopen("adaptive.out", "w");
	fclose(fp);

	size = paras->size;
	rmDup = paras->rmDup;
	devM = paras->devM;
	eDiff = paras->eDiff;

	sprintf(config, "config");
	sprintf(startpot, "startpot");
	sprintf(tempfile, "tempfile");
	sprintf(endpot, "endpot");
	sprintf(plotfile, "plotfile");
	sprintf(flagfile, "STOP");

	nCS = (cryStruct**)malloc(paras->size * sizeof(cryStruct*));
	nFitCS = (cryStruct**)malloc(paras->nFit * sizeof(cryStruct*));

	for(i=0; i < paras->size; i++)
	{
		nCS[i] = new_CS(paras);
		do
        {
            init_struct(nCS[i], oriCS, paras);
        }while(chk_dist(nCS[i], paras) == 1);

        if((paras->keepOri == 1) && (i==0))
			cp_CS_A2B(oriCS, nCS[i], paras);

		if(i < paras->nFit)
			nFitCS[i] = new_CS(paras);
	}

	for(i=0; i < paras->vaspGens; i++)
	{
		sprintf(adaptDir, "adaptive%d", i);
		mkdir(adaptDir, S_IRWXU);
		chdir(adaptDir);
		mkdir("vasp_static", S_IRWXU);
		chdir("vasp_static");
		mkdir("vasp_input", S_IRWXU);
		system("cp ../../vasp_input/* vasp_input/");
		while(access("vasp_input/runvasp", F_OK) != 0);
		for(j=0; j < paras->nFit; j++)
			cp_CS_A2B(nCS[j], nFitCS[j], paras);
		paras->size = paras->nFit;
		paras->nGens = 0;
		paras->algoLoc = 2;
		paras->rmDup = 1;
		paras->devM = 0.0;
		paras->eDiff = 0.5;
		pso_opt_adaptive(paras, oriCS, nFitCS);
		chdir("..");

		if(i == 0)
		{
			if(paras->autoInitPot == 1)
				w_init_pot(paras, startpot);
			else
			{
				system("cp ../potfit_input/startpot .");
				while(access("startpot", F_OK) != 0);
			}
		}
		else
		{
			sprintf(adaptDir, "adaptive%d", i-1);
			sprintf(command, "cp ../%s/endpot startpot", adaptDir);
			system(command);
			while(access(startpot, F_OK) != 0);
		}

		w_init(config);
		sprintf(config, "../../../../config");
		for(j=0; j < paras->nFit; j++)
		{
			sprintf(vaspDir, "vasp_static/results/_1/%d", j);
			chdir(vaspDir);
			w_config(oriCS, paras, config);
//			system("echo here_I_am > markfile");
			chdir("../../../..");
		}
		sprintf(config, "config");
		system("echo here_I_am > markfile");
//			sprintf(command, "cp vasp_static/results/_1/%d/OUTCAR OUTCAR%d", j, j);
//			system(command);
//			sprintf(file, "OUTCAR%d", j);
//			while(access(file, F_OK) != 0);
//		system("cp ../potfit_input/vasp2force .");
//		while(access("vasp2force", F_OK) != 0);
		system("cp ../potfit_input/runpotfit .");
		while(access("runpotfit", F_OK) != 0);

		potfit(paras, config, startpot, tempfile, endpot, plotfile, flagfile);

		mkdir("lammps_opt", S_IRWXU);
		chdir("lammps_opt");
		mkdir("lammps_input", S_IRWXU);
		system("cp ../../lammps_input/* lammps_input/");
		while(access("lammps_input/runlammps", F_OK) != 0);
		system("cp ../lammps.pot lammps_input/");
		while(access("lammps_input/lammps.pot", F_OK) != 0);
		paras->size = size;
		paras->nGens = (int)(i * paras->lammpsGens / paras->vaspGens);
		paras->algoLoc = 1;
		paras->rmDup = rmDup;
		paras->devM = devM;
		paras->eDiff = eDiff;
		pso_opt_adaptive(paras, oriCS, nCS);
		chdir("..");

		chdir("..");

		fp = fopen("adaptive.out", "a+");
		fprintf(fp, "adaptive generation %d: LAMMPS: %f, VASP: %f\n", i, nCS[0]->energy, nFitCS[0]->energy);
		fclose(fp);
	}

	for(i=0; i < paras->size; i++)
	{
		del_CS(nCS[i], paras);
		if(i < paras->nFit)
			del_CS(nFitCS[i], paras);
	}
	free(nCS);
	free(nFitCS);

	return;
}
