#ifndef _FUNC_H_
#define _FUNC_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"init_struct.h"
#include"paras.h"
#include"pso_basic.h"

double** new_array(int nArray);
void del_array(double **array, int nArray);
void cp_array_A2B(double **arrayA, double **arrayB, int nArray);
char **new_string(int nString);
void del_string(char **string, int nString);
void cp_string_A2B(char **stringA, char **stringB, int nString);
cryStruct *new_CS(parameter *paras);
void del_CS(cryStruct *oneCS, parameter *paras);
void cp_CS_A2B(cryStruct *csA, cryStruct *csB, parameter *paras);
void cp_opt_1D_A2B(cryStruct *csA, cryStruct *csB, parameter *paras, int dim);
psoUnit *new_psoU(parameter *paras);
void del_psoU(psoUnit *psoU, parameter *paras);
void cp_psoU_A2B(psoUnit *psoUA, psoUnit *psoUB, parameter *paras);
int get_type(char *type, parameter *paras);
void sort(double *array, int nArray);
void sort_CS_psoU(cryStruct **nCS, psoUnit **swarm, psoUnit **pbest, psoUnit **v, parameter *paras);
int par_done(int *parallel, parameter *paras);
void symmetry(psoUnit *psoU, parameter *paras);
void rm_file(parameter *paras);
void group_dividing(cryStruct *oriCS, cryStruct *oneCS, parameter *paras);

#endif
