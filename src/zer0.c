#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"

double vv_zero(double tau, double w, double p2)
{
        return (sqrt(w*w+p2*tau*tau))/tau;
}

double f_0_zero(double tau, double w, double p2,double m0)
{
        /*Here we have to read some parameters*/
        return pow((1/(2*PI)),3)*exp(-sqrt((1-EPS)*w*w+p2*tau*tau)/(TAU0*m0));
}

double Energy_foo(double tau, double m0)
{
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
			//We only calculate this for the initial time!
                        E+=PI*dW*dP2*f_0_zero(T_0,currW,currP2,m0)*vv_zero(T_0,currW,currP2)/tau/tau;
                }
        }
	//This will ensure that the fixed energy is 1 (when the root is found).
        return E-1;
}




double zero_of_m0()
{
/*Returns the root of the function foo*/
	int i,n_max;
	double a,b,a1,b1,p,tol;

	a=0.1;
	b=10;
	tol=0.0001;
	if(Energy_foo(T_0,a)*Energy_foo(T_0,b)>0)
	{
		printf("[!]Error when calculating the root of the initial energy\n");
		return 1;
	}

	//We ESTIMATE the number of times needed
	n_max=(int)log((b-a)/tol)/(log(2.)) + 1;
	a1=a;
	b1=b;
	for(i=0;i<n_max;i++)
	{
		p=(a1+b1)/2.;
		if((Energy_foo(T_0,a1)*Energy_foo(T_0,p))<=0.)
		{
			b1=p;
		}
		else
		{
			a1=p;
		}

	}
	return p;
}
