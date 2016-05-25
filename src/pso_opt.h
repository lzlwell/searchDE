#ifndef _PSO_OPT_H_
#define _PSO_OPT_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include"conv_pos.h"
#include"func.h"
#include"init_struct.h"
#include"i_o.h"
#include"pair.h"
#include"paras.h"
#include"pso_basic.h"
#include"paras.h"
#include"randomlib.h"
#include"loc_opt.h"
#include"pso.h"
#include"pso_chi.h"
#include"diff_evol.h"

void pso_opt_serial(parameter *paras, cryStruct *oriCS);
void pso_opt(parameter *paras, cryStruct *oriCS);
void pso_opt_adaptive(parameter *paras, cryStruct *oriCS, cryStruct **nCS);

#endif
