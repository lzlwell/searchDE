#ifndef _PAIR_H_
#define _PAIR_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"conv_pos.h"
#include"init_struct.h"
#include"paras.h"

double pair_dist(double *posA, double *posB);
void ext_cell(int na, int nb, int nc, double *oneCS, double *extCS, parameter *paras);
int chk_dist(cryStruct *oneCS, parameter *paras);
void get_bond(cryStruct *oneCS, parameter *paras, double *bond);
int chk_dup(cryStruct **nCS, parameter *paras, int num);

#endif
