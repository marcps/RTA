#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "zer0.h"
#include "functions.h"

/*             OUTPUT: 3 graphs:
			1) T*(tau)^(1/3) as a function of tau
			2) tau*deltaE +E+PL as a function of tau*T
			3) (tau/T)*deltaT as a function of tau*T
*/
int main (int argc, char const *argv[])
{
	double TemperatureTau,currTau,sn;
	double dTau=(T_F-T_0)/((double)TNITER);
	double f[NITER][NITER];
	int i,j;
	double m0;
	double Temperature[2],deri_T;
	double energy[2],deri_E;
	double pressure_L[2],deri_PL;

	//FILE INIT----------------------------------------------------
	if(argc<4)
	{
		printf("[!]ERROR. Please type the names of the output .dat files!\n\n[info]run ./EXEC <1>.dat <2>.dat <3>.dat\n\n\n");
		return 1;
	}
	FILE *fp,*fp1,*fp2;
	fp=fopen(argv[1],"w");
	fp1=fopen(argv[2],"w");
	fp2=fopen(argv[3],"w");
	//-------------------------------------------------------------
	m0=zero_of_m0(); //in the library zer0.h

	/*MATRIX INITIALIZATION*/
        matrix_init(NITER,f);

	/*1st iteration*/
	energy[0]=Energy_0(T_0);
	pressure_L[0]=Pressure_L_0(T_0);
	Temperature[0]=Tempr(energy[0]);

	printf("[*]Iteration 0: Energy= %f; Temperature= %f; Pressure_L= %f\n",energy[0],Temperature[0],pressure_L[0]);
	fprintf(fp,"%.15f %.15f\n",T_0,Temperature[0]*pow(T_0,1/3));

	/*Now we need to return the 1st iteration of f in the form of a matrix*/
	calculate_f(f,T_0,Temperature[0],m0);

	/*Subsequent iterations*/
	for (i=1;i<=TNITER;i++)
	{
		currTau=T_0+(double)i*dTau;

		energy[1]=Energy(currTau,f);
		deri_E=(energy[1]-energy[0])/dTau;

		pressure_L[1]=Pressure_L(currTau,f);

		Temperature[1]=Tempr(energy[1]);
		deri_T=(Temperature[1]-Temperature[0])/dTau;

		sn=currTau*deri_E+energy[1]+pressure_L[1]; //This has to be a very small number

		printf("[*]Iteration %d: Energy= %.10f; Temperature=%.10f; Pressure_L= %.10f\n",i,energy[1],Temperature,pressure_L[1]);

		fprintf(fp,"%.15f %.15f\n",currTau,Temperature[1]*pow(currTau,1/3));
		fprintf(fp1,"%.15f %.15f\n",currTau*Temperature[1],sn);
		fprintf(fp2,"%.15f %.15f\n",currTau*Temperature[1],currTau*deri_T/Temperature[1]);

		calculate_f(f,currTau,Temperature[1],m0);
		energy[0]=energy[1];
		Temperature[0]=Temperature[1];
		pressure_L[0]=pressure_L[1];
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

