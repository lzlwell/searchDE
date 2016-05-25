#ifndef _LAMMPS_H_
#define _LAMMPS_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include"conv_pos.h"
#include"func.h"
#include"init_struct.h"
#include"paras.h"
#include"i_o.h"

void lammps_serial(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);
void lammps_init(cryStruct *oneCS, parameter *paras);
int lammps_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);

#endif
