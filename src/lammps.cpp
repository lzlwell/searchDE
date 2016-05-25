#include"lammps.h"

void lammps_serial(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	FILE *fp;
	char *tmps;
	psoUnit *psoU;
	char file[100];
	psoU = new_psoU(paras);
	tmps = (char*)malloc(100*sizeof(char));

	system("cp -p ../../../lammps_input/* .");
	while(access("runlammps", F_OK) != 0);

	w_lammps(oneCS, paras);

	system("./runlammps");

	do
	{
		system("grep clear log.lammps > .tmp_file");
		fp = fopen(".tmp_file", "r");
		fscanf(fp, "%s", tmps);
		fclose(fp);
		remove(".tmp_file");
	}while(strcmp(tmps, "clear") != 0);

	r_lammps(oneCS, oriCS, paras);

	strcpy(file, "cs");
	w_cs(oneCS, paras, file);
	w_vasp(oneCS, paras);
	remove("INCAR");
	cs2psoU(paras, oneCS, psoU);
	strcpy(file, "psoU");
	w_psoU(psoU, paras, file);

	rm_file(paras);

	del_psoU(psoU, paras);

	free(tmps);

	return;
}

void lammps_init(cryStruct *oneCS, parameter *paras)
{
	system("cp -p ../../../lammps_input/* .");
	while(access("runlammps", F_OK) != 0);

	w_lammps(oneCS, paras);
	system("./runlammps");

	return;
}

int lammps_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	FILE *fp;
	psoUnit *psoU;
	char file[100];
	psoU = new_psoU(paras);
	char tmps[100];

	system("grep clear log.lammps > .tmp_file");
	fp = fopen(".tmp_file", "r");
	fscanf(fp, "%s", tmps);
	fclose(fp);
	remove(".tmp_file");

	if(strcmp(tmps, "clear") == 0)
	{
		r_lammps(oneCS, oriCS, paras);

		strcpy(file, "cs");
		w_cs(oneCS, paras, file);
		w_vasp(oneCS, paras);
		remove("INCAR");
		cs2psoU(paras, oneCS, psoU);
		strcpy(file, "psoU");
		w_psoU(psoU, paras, file);
	
		del_psoU(psoU, paras);
	
		if(paras->adaptive == 1)
			remove("lammps.pot");

		rm_file(paras);

		return 1;
	}
	else
	{
		del_psoU(psoU, paras);
		return 0;
	}
}
