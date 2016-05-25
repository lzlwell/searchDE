#include"potfit.h"

void potfit(parameter *paras, char *config, char *startpot, char *tempfile, char *endpot, char *plotfile, char *flagfile)
{
	FILE *fp;
	char command[200], tmps[100];
	int i;

//	sprintf(command, "./vasp2force > %s", config);
//	system(command);
//	while(access(config, F_OK) != 0);

//	w_config(oriCS, paras, config);

	w_potfit(paras, config, startpot, tempfile, endpot, plotfile, flagfile);

	system("./runpotfit");

	do
	{
		system("grep stress potfit.out > .tmp");
		system("tail -1 .tmp > .tmp_file");
		fp = fopen(".tmp_file", "r");
		fscanf(fp, "%s", tmps);
		fclose(fp);
		remove(".tmp");
		remove(".tmp_file");
	}while(strcmp(tmps, "stress") != 0);

//	while(access("adaptive.alloy", F_OK) != 0);
//	system("mv adaptive.alloy lammps.pot");
	while(access("lammps.pot", F_OK) != 0);

	for(i=0; i < paras->nType; i++)
	{
		sprintf(command, "sed -i \"s/type%d/%s/g\" lammps.pot", i, paras->type[i]);
		system(command);
	}

	return;
}
