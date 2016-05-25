#ifndef _ADAPTIVE_H_
#define _ADAPTIVE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include"init_struct.h"
#include"paras.h"
#include"func.h"
#include"pair.h"
#include"pso_opt.h"
#include"potfit.h"

void adaptive(parameter *paras, cryStruct *oriCS);

#endif
