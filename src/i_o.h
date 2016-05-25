#ifndef _I_O_H_
#define _I_O_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include"init_struct.h"
#include"paras.h"
#include"pso_basic.h"

void r_set(parameter *paras);
void r_pos(struct cryStruct *oriCS, parameter *paras);
void w_init(char *file);
void w_cs(cryStruct *oneCS, parameter *paras, char *file);
void w_psoU(psoUnit *psoU, parameter *paras, char *file);
void w_ener(cryStruct *oneCS, char *file);
void w_lammps(cryStruct *oneCS, parameter *paras);
void r_lammps(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);
void r_seed(int *ij, int *kl, char *file);
void w_seed(int ij, int kl, char *file);
void w_vasp(cryStruct *oneCS, parameter *paras);
void r_vasp(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);
void w_potfit(parameter *paras, char *config, char *startpot, char *tempfile, char *endpot, char *plotfile, char *flagfile);
void w_init_pot(parameter *paras, char *startpot);
void w_config(cryStruct *oriCS, parameter *paras, char *config);

#endif
