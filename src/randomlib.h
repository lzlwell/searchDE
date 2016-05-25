#ifndef _RANDOMLIB_H_
#define _RANDOMLIB_H_

#include<string.h>
#include<time.h>
#include"paras.h"
#include"i_o.h"

void   RandomInitialise(int,int);
double RandomUniform(void);
double RandomGaussian(double,double);
int    RandomInt(int,int);
double RandomDouble(double,double);

void init_rand(parameter *paras);
#define random RandomDouble(0.0, 1.0)

#endif
