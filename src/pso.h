#ifndef _PSO_H_
#define _PSO_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"pso_basic.h"
#include"randomlib.h"
#include"paras.h"
#include"init_struct.h"
#include"conv_pos.h"
#include"func.h"
#include"pair.h"

void pso(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, double omega, cryStruct *oriCS);
void pso_select(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, parameter *paras);
void pso_constr(psoUnit *psoU, cryStruct *oriCS, parameter *paras);
void pso_chi(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, cryStruct *oriCS);

#endif
