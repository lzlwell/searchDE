#ifndef _POTFIT_H_
#define _POTFIT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"init_struct.h"
#include"paras.h"
#include"i_o.h"

void potfit(parameter *paras, char *config, char *startpot, char *tempfile, char *endpot, char *plotfile, char *flagfile);

#endif
