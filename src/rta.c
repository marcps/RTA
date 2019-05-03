#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "zer0.h"
#include "functions.h"


int main (int argc, char const *argv[])
{
	double TemperatureTau,Temperature,currT,sn;
	double dT=(T_F-T_0)/((double)TNITER);
	double f[NITER][NITER];
	int i,j;
	double m0;
	double energy[2],deri_E;
	double pressure_L[2],deri_PL;

	//FILE INIT----------------------------------------------------
	if(argc<3)
	{
		printf("[!]ERROR. Please type the names of the outpu .dat files!\n run ./EXEC <1>.dat <2>.dat\n");
		return 1;
	}
	FILE *fp,*fp1;
	fp=fopen(argv[1],"w");
	fp1=fopen(argv[2],"w");
	//-------------------------------------------------------------
	m0= zero_of_m0(); //in the library zer0.h
	/*MATRIX INITIALIZATION*/
        matrix_init(NITER,f);

	/*1st iteration*/
	energy[0]=Energy_0(T_0);
	pressure_L[0]=Pressure_L_0(T_0);
	Temperature=Tempr(energy[0]);

	printf("[*]Iteration 0: Energy= %f; Temperature= %f\n; Pressure_L= %f\n",energy[0],Tempr,pressure_L[0]);
	fprintf(fp,"%.15f %.15f\n",T_0,Temperature*pow(T_0,1/3));

	/*Now we need to return the 1st iteration of f in the form of a matrix*/
	calculate_f(f,T_0,Temperature,m0);

	/*Subsequent iterations*/
	for (i=0;i<=TNITER;i++)
	{
		currT=T_0+(double)i*dT;

		energy[1]=Energy(currT,f);
		deri_E=(energy[1]-energy[0])/dT;

		pressure_L[1]=Pressure_L(currT,f);

		Temperature=Tempr(energy[1]);

		sn=(currT*deri_E/(energy[1]+pressure_L[1]))-1;

		printf("[*]Iteration %d: Energy= %.10f; Temperature=%.10f; Pressure_L= %.10f\n",i+1,energy,Temperature,pressure_L[1]);

		fprintf(fp,"%.15f %.15f\n",currT,Temperature*pow(currT,1/3));
		fprintf(fp1,"%.15f %.15f\n",currT*Temperature,sn);

		calculate_f(f,currT,Temperature,m0);
		energy[0]=energy[1];
		pressure_L[0]=pressure_L[1];
	}
	fclose(fp);
	fclose(fp1);
	return 0;
}

