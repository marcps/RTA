#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "zer0.h"
#include "functions.h"

//When executing the binary, you should include 3 arguments when executed
//corresponding to the files fp, fp1, fp2

double t_f=100;
double t_0=1;
double tstep=0.25;
double m0=1;

int main (int argc, char **argv)
{
	double currTau,sn;
	double dTau=tstep;
	double **f;
	int i;
	double *temperature;
	double *energy;
	double energy_eq;
	double tniter=(t_f-t_0)/tstep;


	printf("\n[*]Convergence of TIME EVOLUTION\n");
	printf("\n[params]t_f=%f  ;t_0=%f   ;integration time step=%f   ;m0=%f\n; w_f=%f  ;w_0=%f \np2_f=%f  ;p_0=%f\nNITER=%d\n\n",t_f,t_0,tstep,m0,WF,W0,P2_F,P2_0,NITER);

	//----------------- MATRIX AND VECTOR INIT---------------------
	f = (double **)malloc((NITER+1)*sizeof(double));
	if(f==NULL)
	{
		printf("NOT Enough memory!\n Exitting...\n");
		return 4;
	}
	for(i=0;i<NITER;i++)
	{
		f[i]=(double *)malloc((NITER+1)*sizeof(double));
		if(f[i]==NULL)
		{
			printf("[erro]NOT Enough memory!\n Exitting...\n");
			return 5;
		}
	}
	//Vector initialization
	temperature=(double *)malloc(2*sizeof(double));
	energy=(double *)malloc(2*sizeof(double));
	//-------------------------------------------------------------

	//-----------------------FILE INIT-----------------------------
	if(argc<2)
	{
		printf("\n[!]ERROR. Please type the names of the output .dat files!\n\n[info]run ./EXEC <1>.dat\n\n\n");
		return 1;
	}
	FILE *fp;
	fp=fopen(argv[1],"w");
	//-------------------------------------------------------------
	//MATRIX INITIALIZATION

	//1st iteration
	energy[0]=Energy_0(t_0,m0);
	temperature[0]=Tempr(energy[0]);

	printf("[*]Iteration %4d: Energy= %.15f; Temperature= %.15f\n",
		0,energy[0],temperature[0]);

	//Now we need to return the 1st iteration of f in the form of a matrix
	calculate_f_0(f,t_0+dTau,temperature[0],m0);

	//Subsequent iterations
	for (i=1;i<=tniter;i++)
	{
		currTau=t_0+(double)i*dTau;

		energy[1]=Energy(currTau,f);

		temperature[1]=Tempr(energy[0]);
		energy_eq=Energy_eq(currTau,temperature[1]);
		sn=(energy[1]-energy_eq)/energy[1];
		//--------------------------------- PRINTING -----------------------------------------------------------
		printf("[*]Iteration %4d: Energy= %.15f; Temperature=%.15f; Sn= %.10f\n",
			i,energy[1],temperature[1],sn);

		fprintf(fp,"%.15f %.15f\n",currTau,sn);
		//------------------------------------------------------------------------------------------------------
		//Preparing for the next iteration
		calculate_f(f,currTau+dTau,temperature[1],m0);
		energy[0]=energy[1];
		temperature[0]=temperature[1];
	}
	fclose(fp);
	return 0;
}

