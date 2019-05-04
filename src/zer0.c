#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constants.h"
#include "functions.h"

double zero_of_m0()
{
/*Returns the root of the function foo*/
	int i,n_max;
	double a,b,a1,b1,p,tol;

	//Can this intervals be calculated?
	a=0.1;
	b=100;

	tol=0.000001;
	if(Energy_0_zero(T_0,a)*Energy_0_zero(T_0,b)>0)
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
		if((Energy_0_zero(T_0,a1)*Energy_0_zero(T_0,p))<=0.)
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
