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
        return pow((1/(2*PI)),3)*exp(-sqrt((1-EPS)*w*w+p2*tau*tau)/(tau*m0));
}

double Energy_0(double tau,double m0,double p2_0,double p2_f, double w_0, double w_f,int niter)
{
        /*Calculates the INITIAL ENERGY integrating over a grid of w,p2*/
        double E, dP2, dW,currW,currP2;
        int i, j;

        E=0.0;
        dW=(w_f-w_0)/((double)niter);
        dP2=(p2_f-p2_0)/((double)niter);

        /*We integrate */
        for(i=0;i<niter;i++)
        {
                currW=w_0+((double)i+0.5)*dW;
                for(j=0;j<niter;j++)
                {
                        currP2=p2_0+((double)j+0.5)*dP2;
                        E+=2*PI*dW*dP2*f_0(tau,currW,currP2,m0)*vv(tau,currW,currP2)/tau/tau;
                }
        }
        return E;
}

double Pressure_L_0(double tau,double m0,double p2_0,double p2_f, double w_0, double w_f,int niter)
{
        /*Calculates the INITIAL ENERGY integrating over a grid of w,p2*/
        double Pr_L, dP2, dW,currW,currP2;
        int i, j;

        Pr_L=0.0;
        dW=(w_f-w_0)/((double)niter);
        dP2=(p2_f-p2_0)/((double)niter);

        /*We integrate */
        for(i=0;i<niter;i++)
        {
                currW=w_0+((double)i+0.5)*dW;
                for(j=0;j<niter;j++)
                {
                        currP2=p2_0+((double)j+0.5)*dP2;
                        Pr_L+=2*PI*dW*dP2*f_0(tau,currW,currP2,m0)*(currW*currW/vv(tau,currW,currP2))/tau/tau;
                }
        }
        return Pr_L;
}


int main1(void){
        double energy1=Energy_0(1,1,0,300,0,30,100);
        double energy2=Energy_0(1,1,0,300,0,30,200);
        double energy3=Energy_0(1,1,0,300,0,30,300);
        double energy4=Energy_0(1,1,0,300,0,30,400);
        double energy5=Energy_0(1,1,0,300,0,30,500);
        double energy6=Energy_0(1,1,0,300,0,30,600);
        double energy7=Energy_0(1,1,0,300,0,30,1000);
        double energy8=Energy_0(1,1,0,300,0,30,1200);
        double energy9=Energy_0(1,1,0,300,0,30,1300);
        double energy10=Energy_0(1,1,0,300,0,30,1400);
        printf("\n\nInitial Energy1= %.15f\n\n",energy1);
        printf("\n\nInitial Energy2= %.15f\n\n",energy2);
        printf("\n\nInitial Energy3= %.15f\n\n",energy3);
        printf("\n\nInitial Energy4= %.15f\n\n",energy4);
        printf("\n\nInitial Energy5= %.15f\n\n",energy5);
        printf("\n\nInitial Energy6= %.15f\n\n",energy6);
        printf("\n\nInitial Energy7= %.15f\n\n",energy7);
        printf("\n\nInitial Energy8= %.15f\n\n",energy8);
        printf("\n\nInitial Energy9= %.15f\n\n",energy9);
        printf("\n\nInitial Energy10= %.15f\n\n",energy10);
        return 0;
}

int main(void){
	double energy1=Pressure_L_0(1,1,0,300,0,10,100);
	double energy2=Pressure_L_0(1,1,0,300,0,10,200);
	double energy3=Pressure_L_0(1,1,0,300,0,10,300);
	double energy4=Pressure_L_0(1,1,0,300,0,10,400);
	double energy5=Pressure_L_0(1,1,0,300,0,10,500);
	double energy6=Pressure_L_0(1,1,0,300,0,10,600);
	double energy7=Pressure_L_0(1,1,0,300,0,10,700);
	double energy8=Pressure_L_0(1,1,0,300,0,10,800);
	double energy9=Pressure_L_0(1,1,0,300,0,10,900);
	double energy10=Pressure_L_0(1,1,0,300,0,10,1000);
	printf("\n\nInitial PL1= %.15f\n\n",energy1);
	printf("\n\nInitial PL2= %.15f\n\n",energy2);
	printf("\n\nInitial PL3= %.15f\n\n",energy3);
	printf("\n\nInitial PL4= %.15f\n\n",energy4);
	printf("\n\nInitial PL5= %.15f\n\n",energy5);
	printf("\n\nInitial PL6= %.15f\n\n",energy6);
	printf("\n\nInitial PL7= %.15f\n\n",energy7);
	printf("\n\nInitial PL8= %.15f\n\n",energy8);
	printf("\n\nInitial PL9= %.15f\n\n",energy9);
	printf("\n\nInitial PL10= %.15f\n\n",energy10);
	return 0;
}



