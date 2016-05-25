#ifndef _CONV_POS_H_
#define _CONV_POS_H_

#include<stdio.h>
#include<stdlib.h>
#include"init_struct.h"
#include"func.h"
#include"paras.h"
#include"pso_basic.h"

void dir2car(double *dir, double *car, double **latt);
void inv_latt(double **latt, double **invLatt);
void car2dir(double *car, double *dir, double **latt);
void cs2psoU(parameter *paras, cryStruct *oneCS, psoUnit *psoU);
void psoU2cs(parameter *paras, cryStruct *oriCS, psoUnit *psoU, cryStruct *oneCS);

#endif
