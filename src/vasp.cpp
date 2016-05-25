#include"vasp.h"

void vasp_init(cryStruct *oneCS, parameter *paras)
{
	system("cp -p ../../../vasp_input/* .");
	while(access("runvasp", F_OK) != 0);

	w_vasp(oneCS, paras);
	system("./runvasp");

	return;
}

int vasp_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras)
{
	FILE *fp;
        psoUnit *psoU;
        char file[100];
        psoU = new_psoU(paras);
	char tmps[100];
	int tmpi;

	system("grep Voluntary OUTCAR > .tmp_file");
	fp = fopen(".tmp_file", "r");
	fscanf(fp, "%s", tmps);
	fclose(fp);
	remove(".tmp_file");

	if(strcmp(tmps, "Voluntary") == 0)
	{
		system("tail -1 OSZICAR > .tmp");
		system("grep F .tmp > .tmp_file");
		fp = fopen(".tmp_file", "r");
		fscanf(fp, "%d", &tmpi);
		fclose(fp);
		remove(".tmp_file");
		remove(".tmp");

		if(tmpi == paras->vaspNSW)
		{
			remove("OUTCAR");
			remove("OSZICAR");
			remove("log.out");
			do
			{
				init_struct(oneCS, oriCS, paras);
			}while(chk_dist(oneCS, paras) == 1);
	
			w_vasp(oneCS, paras);
			system("./runvasp");

			del_psoU(psoU, paras);

			return 0;
		}
		else
		{
			r_vasp(oneCS, oriCS, paras);
	        strcpy(file, "cs");
	   	    w_cs(oneCS, paras, file);
       	    cs2psoU(paras, oneCS, psoU);
            strcpy(file, "psoU");
            w_psoU(psoU, paras, file);

            del_psoU(psoU, paras);

			rm_file(paras);
			
			return 1;
		}
	}

	system("tail -1 log.out > .tmp_file");
	fp = fopen(".tmp_file", "r");
	fscanf(fp, "%s", tmps);
	fclose(fp);
	remove(".tmp_file");

	if(strcmp(tmps, "to") == 0)
	{
		remove("log.out");
		remove("OSZICAR");
		remove("OUTCAR");

		system("cp CONTCAR POSCAR");
		system("./runvasp");
	}
	else if((strcmp(tmps, "Error") == 0) || (strcmp(tmps, "LAPACK:") == 0))
	{
		remove("log.out");
		remove("OSZICAR");
		remove("OUTCAR");

		do
		{
			init_struct(oneCS, oriCS, paras);
		}while(chk_dist(oneCS, paras) == 1);
	
		w_vasp(oneCS, paras);
		system("./runvasp");
	}

	del_psoU(psoU, paras);

	return 0;
}
