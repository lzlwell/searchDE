#ifndef _INIT_STRUCT_H_
#define _INIT_STRUCT_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"paras.h"
#include"randomlib.h"
#include"i_o.h"
#include"pso_basic.h"
#include"conv_pos.h"

struct cryStruct
{
	double **latt;
	double *charge;
	double **fixPosH;
	double **fixPosL;
	double **buffPosH;
	double **buffPosL;
	double **optPos;
	char   **fixTpH;
	char   **fixTpL;
	char   **buffTpH;
	char   **buffTpL;
	char   **optTp;
	double optH;
	double transA;
	double transB;
	double energy;
};

void init_oriCS(cryStruct *oriCS, parameter *paras);
void init_struct(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);

#endif
