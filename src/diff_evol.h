#ifndef _DIFF_EVOL_H_
#define _DIFF_EVOL_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"pso_basic.h"
#include"randomlib.h"
#include"paras.h"
#include"init_struct.h"
#include"func.h"
#include"conv_pos.h"
#include"pair.h"
#include"pso.h"

void diff_evol(psoUnit **swarm, psoUnit **pbest, psoUnit *gbest, psoUnit **v, psoUnit *vm, parameter *paras, cryStruct *oriCS);

#endif
