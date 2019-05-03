#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"
#include "zer0.h"


double vv(double tau, double w, double p2)
{
	return (sqrt(w*w+p2*tau*tau))/tau;
}

double f_0(double tau, double w, double p2, double m0)
{
	/*Here we have to read some parameters*/
	return pow((1/(2*PI)),3)*exp(-sqrt((1-EPS)*w*w+p2*tau*tau)/(TAU0*m0));
}
double f_eq(double tau, double w, double p2, double Tempr)
{
	return pow((1/(2*PI)),3)*exp(-sqrt(w*w+p2*tau*tau)/(tau*Tempr));
}

double Energy_0(double tau)
{
	double m0=zero_of_m0(); //in the library zer0.h
	/*Calculates the INITIAL ENERGY integrating over a grid of w,p2*/
	double E, dP2, dW,currW,currP2;
	int i, j;

	E=0.0;
	dW=(WF-W0)/((double)NITER);
	dP2=(P2_F-P2_0)/((double)NITER);

	/*We integrate */
	for(i=0;i<NITER;i++)
	{
		currW=W0+(double)i*dW;
		for(j=0;j<NITER;j++)
		{
			currP2=P2_0+(double)j*dP2;
			E+=PI*dW*dP2*f_0(tau,currW,currP2,m0)*vv(tau,currW,currP2)/tau/tau;
		}
	}
	return E;
}

double Energy(double tau,double f[NITER][NITER])
{
	//Calculaters the ENERGY integrating over a grid of w,p
	double E,dP2,dW,currW,currP2;
	int i,j;

	E=0.0;
	dW=(WF-W0)/((double)NITER);
	dP2=(P2_F-P2_0)/((double)NITER);

	for(i=0;i<NITER;i++)
	{
		currW=W0+(double)i*dW;
		for(j=0;j<NITER;j++)
		{
			currP2=P2_0+(double)j*dP2;
			E+=PI*dW*dP2*f[i][j]*vv(tau,currW,currP2)/tau/tau; //Check if this expression is correct.
		}
	}
	return E;
}

double Tempr(double E)
{
	/*Returns the TEMPERATURE*/
	return sqrt(sqrt((6/PI)*E));
}

double TemprTau(double E, double tau)
{
	return sqrt(sqrt((6/PI)*E))*pow(tau,(1/3));
}

void calculate_f(double f[NITER][NITER],double t,double tempr, double m0)
{
	double dW,dP2,currW,currP2;
	int i,j;
	dW=(WF-W0)/((double)NITER);
	dP2=(P2_F-P2_0)/((double)NITER);

	for(i=0;i<NITER;i++)
	{
		currW=W0+(double)i*dW;
		for(j=0;j<NITER;j++)
		{
			currP2=P2_0+(double)j*dP2;
			f[i][j]=f[i][j]+(f_0(t,currW,currP2,m0)-(f_eq(t,currW,currP2,tempr)))/t;
		}
	}
}

void matrix_init(int d,double m[d][d])
{
	int i,j;
        for(i=0;i<d;i++)
	{
		for(j=0;j<d;j++)
		{
			m[i][j]=0.0;
		}
	}
}

void matrix_print(int d, double m[d][d])
{
	int i,j;
	for(i=0;i<d;i++)
	{
		printf("\n");
		for(j=0;j<d;j++)
		{
			printf("%f ",m[i][j]);
		}
	}
	printf("\n");
}



int main ()
{
	double energy,TemperatureTau,Temperature,x,y,currT;
	double dT=(T_F-T_0)/((double)TNITER);
	double f[NITER][NITER],tempr_matrix[2],deriTau_Tempr;
	int i,j;
	double m0= zero_of_m0(); //in the library zer0.h

	/*FILE INIT*/
	FILE *fp;
	fp=fopen("temp.dat","w");

	/*MATRIX INITIALIZATION*/
        matrix_init(NITER,f); 

	/*1st iteration*/
	energy=Energy_0(T_0);
	TemperatureTau=TemprTau(energy,T_0);
	Temperature=Tempr(energy);
	tempr_matrix[0]=Temperature;

	printf("[*]Iteration 0: Energy= %f; Temperature= %f\n",energy,Tempr);	
	fprintf(fp,"%.10f %.10f\n",T_0,TemperatureTau);
	/*Now we need to return the 1st iteration of f in the form of a matrix*/
	calculate_f(f,T_0,Temperature,m0);

	/*Subsequent iterations*/
	for (i=0;i<=TNITER;i++)
	{
		currT=T_0+(double)i*dT;
		energy=Energy(currT,f);

		Temperature=Tempr(energy);
		//Derivative of Temperature
		tempr_matrix[1]=Temperature;
		deriTau_Tempr=(tempr_matrix[1]-tempr_matrix[0])/dT;

		TemperatureTau=TemprTau(energy,currT);
		//We now define the x,y axis
		x=currT*Temperature;
		y=(currT/Temperature)*deriTau_Tempr;
		printf("[*]Iteration %d: Energy= %.10f; Temperature=%.10f\n",i+1,energy,Temperature);
		fprintf(fp,"%.15f %.15f\n",x,y);

		calculate_f(f,currT,Temperature,m0);
	}
	fclose(fp);
	return 0;
}

