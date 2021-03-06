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

//             OUTPUT: 3 graphs:
//			1) T*(tau)^(1/3) as a function of tau
//			2) tau*deltaE +E+PL as a function of tau*T
//			3) (tau/T)*deltaT as a function of tau*T
//			4)P_L/P_T as a function of tau

int main (int argc, char **argv)
{
	double currTau,sn,etaEff;
	double tniter=(T_F-T_0)/TSTEP;
	double dTau=TSTEP;
	double **f;
	int i;
	double m0;
	double *Temperature,deri_T;
	double *energy,deri_E;
	double *pressure_L,*pressure_T;//deri_PL;

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
			printf("NOT Enough memory!\n Exitting...\n");
			return 5;
		}
	}
	//Vector initialization
	Temperature=(double *)malloc(3*sizeof(double));
	energy=(double *)malloc(3*sizeof(double));
	pressure_L=(double *)malloc(3*sizeof(double));
	pressure_T=(double *)malloc(3*sizeof(double));
	//-------------------------------------------------------------

	//-----------------------FILE INIT-----------------------------
	if(argc<5)
	{
		printf("\n[!]ERROR. Please type the names of the output");
		printf(".dat files!\n\n[info]run %s ",argv[0]);
		printf("<1>.dat   <2>.dat   <3>.dat   <4>.dat   <5>.dat\n\n\n");
		return 1;
	}
	FILE *fp,*fp1,*fp2,*fp3,*fp4;

	if(strcmp(argv[1],argv[2])==0 || strcmp(argv[2],argv[3])==0 || strcmp(argv[1],argv[3])==0)
	{
		printf("\n[!]ERROR. Filenames must be DIFFERENT!\n\n");
		return 2;
	}
	fp=fopen(argv[1],"w");
	fp1=fopen(argv[2],"w");
	fp2=fopen(argv[3],"w");
	fp3=fopen(argv[4],"w");
	fp4=fopen(argv[5],"w");
	//-------------------------------------------------------------

	m0=1.5000000; //in the library zer0.h

	//MATRIX INITIALIZATION

	//1st iteration
	energy[0] = Energy_0(T_0,m0);
	pressure_L[0] = Pressure_L_0(T_0,m0);
	Temperature[0] = Tempr(energy[0]);

	printf("[*]Iteration %4d: Energy= %.15f; Temperature= %.15f; Pressure_L= %.15f\n",
		0,energy[0],Temperature[0],pressure_L[0]);
	//Now we need to return the 1st iteration of f in the form of a matrix
	calculate_f_0(f,T_0+dTau,Temperature[0],m0);

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//%%%%%%%%%%%%%%%%% Subsequent iterations %%%%%%%%%%%%%%%
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	for (i=1;i<=tniter;i++)
	{
		currTau=T_0+((double)i+0.5)*dTau;
		energy[1]=Energy(currTau,f);
		pressure_L[1]=Pressure_L(currTau,f);
		pressure_T[1]=Pressure_T(currTau,f);
		Temperature[1]=Tempr(energy[1]);
		deri_E=(energy[1]-energy[0])/dTau;
		deri_T=(Temperature[1]-Temperature[0])/dTau;

		//This has to be a very small number. CONSERVATION of ENERGY
		sn=fabs(currTau*deri_E/(energy[1]+pressure_L[1]))-1.0;
		etaEff=9*currTau*currTau/4*(deri_T+Temperature[1]/(3.0*currTau));

		//--------------------------------- PRINTING -----------------------------------------------------------
		printf("[*]Iteration %4d: Energy= %.15f; deriE= %.15f; Temperature=%.15f; Pressure_L= %.15f; Sn= %.10f\n",
			i,energy[1],deri_E,Temperature[1],pressure_L[1],sn);

		fprintf(fp,"%.15f %.15f\n",
			currTau,etaEff);

		fprintf(fp1,"%.15f %.15f\n",
			currTau,sn);

		fprintf(fp2,"%.15f %.15f\n",
			currTau,pressure_L[1]/pressure_T[1]);

		fprintf(fp3,"%.15f %.15f\n",
			currTau/T_0,energy[1]*pow(currTau,3/(double)2)*T_0*T_0*T_0*T_0);

		fprintf(fp4,"%.15f %.15f\n",
			currTau,pressure_L[2]/pressure_T[2]);
		//------------------------------------------------------------------------------------------------------
		//Preparing for the next iteration

		calculate_f(f,currTau+dTau,Temperature[1],m0);
		energy[0]=energy[1];
		Temperature[0]=Temperature[1];
		pressure_L[0]=pressure_L[1];
		pressure_T[0]=pressure_T[1];

	}

	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	free(Temperature);
	free(energy);
	free(pressure_L);
	free(pressure_T);
	free(f);
	return 0;
}

