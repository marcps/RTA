#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "zer0.h"

double vv(double tau,double w,double p2)
{
	return sqrt(w*w+p2*tau*tau);
}

double f_0(double tau, double w, double p2, double m0)
{
        /*f_0 is the initial state density function*/
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
                        E+=PI*dW*dP2*f[i][j]*vv(tau,currW,currP2)/tau/tau; //Check if this expression is c$
                }
        }
        return E;
}

double Pressure_L(double tau,double f[NITER][NITER])
{
        //Calculaters the LONGITUDINAL PRESSURE integrating over a grid of w,p
        double pL,dP2,dW,currW,currP2;
        int i,j;

        pL=0.0;
        dW=(WF-W0)/((double)NITER);
        dP2=(P2_F-P2_0)/((double)NITER);

        for(i=0;i<NITER;i++)
        {
                currW=W0+(double)i*dW;
                for(j=0;j<NITER;j++)
                {
                        currP2=P2_0+(double)j*dP2;
                        pL+=PI*dW*dP2*f[i][j]*(currW*currW/vv(tau,currW,currP2))/tau/tau;
                }
        }
        return pL;
}

double Pressure_L_0(double tau)
{
        double m0=zero_of_m0(); //in the library zer0.h
        /*Calculates the INITIAL ENERGY integrating over a grid of w,p2*/
        double Pr_L, dP2, dW,currW,currP2;
        int i, j;

        Pr_L=0.0;
        dW=(WF-W0)/((double)NITER);
        dP2=(P2_F-P2_0)/((double)NITER);

        /*We integrate */
        for(i=0;i<NITER;i++)
        {
                currW=W0+(double)i*dW;
                for(j=0;j<NITER;j++)
                {
                        currP2=P2_0+(double)j*dP2;
                        Pr_L+=PI*dW*dP2*f_0(tau,currW,currP2,m0)*(currW*currW*vv(tau,currW,currP2))/tau/tau;
                }
        }
        return Pr_L;
}

double Pressure_T(double tau,double f[NITER][NITER])
{
        //Calculaters the TRANSVERSE PRESSURE integrating over a grid of w,p
        double pT,dP2,dW,currW,currP2;
        int i,j;

        pT=0.0;
        dW=(WF-W0)/((double)NITER);
        dP2=(P2_F-P2_0)/((double)NITER);

        for(i=0;i<NITER;i++)
        {
                currW=W0+(double)i*dW;
                for(j=0;j<NITER;j++)
                {
                        currP2=P2_0+(double)j*dP2;
                        pT+=PI*dW*dP2*f[i][j]*(currP2*vv(tau,currW,currP2)); //Check if this expression is c$
                }
        }
        return pT;
}

double Tempr(double E)
{
        /*Returns the TEMPERATURE*/
        return sqrt(PI*sqrt(E/3));
}

void calculate_f(double f[NITER][NITER],double t,double tempr, double m0)
{
	/*given the matrix f, calculates its next iteration of f with its derivative*/
	/*m0 has to be calculated with the function zero_of_m0() in the library zer0.h*/
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
	/*sets a matrix dxd all to zero*/
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
	/*Prints a dxd matrix to std output*/
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
