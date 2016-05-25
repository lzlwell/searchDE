#ifndef _VASP_H_
#define _VASP_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include"conv_pos.h"
#include"func.h"
#include"init_struct.h"
#include"paras.h"
#include"pair.h"
#include"i_o.h"

void vasp_init(cryStruct *oneCS, parameter *paras);
int vasp_final(cryStruct *oneCS, cryStruct *oriCS, parameter *paras);

#endif
