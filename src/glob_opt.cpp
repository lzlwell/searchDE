#include"glob_opt.h"

void glob_opt()
{
	parameter *paras;
	cryStruct *oriCS;
	int i;

	paras = (parameter*)malloc(sizeof(parameter));
	r_set(paras);

	init_rand(paras);

	oriCS = new_CS(paras);
	init_oriCS(oriCS, paras);

	if(paras->adaptive == 1)
		adaptive(paras, oriCS);
	else if((paras->algoGlob >= 1) && (paras->algoGlob <= 19))
	{
		if(paras->run == 1)
			pso_opt_serial(paras, oriCS);
		else if(paras->run == 11)
			pso_opt(paras, oriCS);
	}

	del_CS(oriCS, paras);
	for(i=0; i < paras->nType; i++)
		free(paras->type[i]);
	for(i=0; i < paras->nRmFile; i++)
		free(paras->rmFile[i]);
	free(paras->type);
	free(paras->charge);
	free(paras->rmFile);
	free(paras);

	return;
}
