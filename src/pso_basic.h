#ifndef _PSO_BASIC_H_
#define _PSO_BASIC_H_

struct psoUnit
{
	double **buffPosH;
	double **buffPosL;
	double **optPos;
	double optH;
	double transA;
	double transB;
	double energy;
};

#endif
