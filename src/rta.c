#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "zer0.h"
#include "functions.h"
/*When executing the binary, you should include 3 arguments when executed
corresponding to the files fp, fp1, fp2*/

/*             OUTPUT: 3 graphs:
			1) T*(tau)^(1/3) as a function of tau
			2) tau*deltaE +E+PL as a function of tau*T
			3) (tau/T)*deltaT as a function of tau*T
*/
int main (int argc, char const *argv[])
{
	printf("%f",PI);
	double currTau,sn;
	double dTau=(T_F-T_0)/((double)TNITER);
	double f[NITER][NITER];
	int i;
	double m0;
	double Temperature[2],deri_T;
	double energy[2],deri_E;
	double pressure_L[2];//deri_PL;

	//-----------------------FILE INIT-----------------------------
	if(argc<4)
	{
		printf("\n[!]ERROR. Please type the names of the output .dat files!\n\n[info]run ./EXEC <1>.dat <2>.dat <3>.dat\n\n\n");
		return 1;
	}
	FILE *fp,*fp1,*fp2;
	if(strcmp(argv[1],argv[2])==0 || strcmp(argv[2],argv[3])==0 || strcmp(argv[1],argv[3])==0)
	{
		printf("\n[!]ERROR. Filenames must be DIFFERENT!\n\n");
		return 2;
	}
	fp=fopen(argv[1],"w");
	fp1=fopen(argv[2],"w");
	fp2=fopen(argv[3],"w");
	//-------------------------------------------------------------

	///////////////////////////m0=zero_of_m0(); //in the library zer0.h
	m0=1;

	/*MATRIX INITIALIZATION*/
        matrix_init(NITER,f);

	/*1st iteration*/
	energy[0]=Energy_0(T_0,m0);
	pressure_L[0]=Pressure_L_0(T_0,0);
	Temperature[0]=Tempr(energy[0]);

	printf("[*]Iteration 0: Energy= %.15f; Temperature= %.15f; Pressure_L= %.15f\n",
		energy[0],Temperature[0],pressure_L[0]);
	fprintf(fp,"%.15f %.15f\n",
		T_0,Temperature[0]*pow(T_0,1/3));

	/*Now we need to return the 1st iteration of f in the form of a matrix*/
	calculate_f_0(f,T_0+dTau,Temperature[0],m0);

	/*Subsequent iterations*/
	for (i=1;i<=TNITER;i++)
	{
		currTau=T_0+(double)i*dTau;

		energy[1]=Energy(currTau,f);
		deri_E=(energy[1]-energy[0])/dTau;

		pressure_L[1]=Pressure_L(currTau,f);

		Temperature[1]=Tempr(energy[1]);
		deri_T=(Temperature[1]-Temperature[0])/dTau;

		//This has to be a very small number
		//sn=fabs(currTau*deri_E/(energy[1]+pressure_L[1]))-1;
		sn=currTau*deri_E+energy[1]+pressure_L[1];

		//--------------------------------- PRINTING -----------------------------------------------------------
		printf("[*]Iteration %d: Energy= %.15f; deriE= %.5f; Temperature=%.15f; Pressure_L= %.15f; Sn= %.10f\n",
			i,energy[1],deri_E,Temperature[1],pressure_L[1],sn);

		/*fprintf(fp,"%.15f %.15f\n",
			currTau,Temperature[1]*pow(currTau,1/3));*///////////////////////////////////////////////////////
		fprintf(fp, "%.15f %.15f\n",currTau,energy[1]);
		fprintf(fp1,"%.15f %.15f\n",
			currTau,sn);
		fprintf(fp2,"%.15f %.15f\n",
			currTau*Temperature[1],currTau*deri_T/Temperature[1]);
		//------------------------------------------------------------------------------------------------------
		//Preparing for the next iteration
		calculate_f(f,currTau+dTau,Temperature[1],m0);
		energy[0]=energy[1];
		Temperature[0]=Temperature[1];
		pressure_L[0]=pressure_L[1];
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

