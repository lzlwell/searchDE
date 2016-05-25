#ifndef _LOC_OPT_H_
#define _LOC_OPT_H_

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include"init_struct.h"
#include"i_o.h"
#include"paras.h"
#include"pso_basic.h"
#include"func.h"
#include"conv_pos.h"
#include"lammps.h"
#include"vasp.h"

void loc_opt_serial(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);
void loc_opt_init(cryStruct *oneCS, parameter *paras);
int loc_opt_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);

#endif
