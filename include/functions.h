double vv(double tau,double w,double p2);
double f_0(double tau, double w, double p2, double m0);
double f_eq(double tau, double w, double p2, double Tempr);
double Energy_0(double tau);
double Energy(double tau,double f[NITER][NITER]);
double Pressure_L(double tau,double f[NITER][NITER]);
double Pressure_L_0(double tau);
double Pressure_T(double tau,double f[NITER][NITER]);
double Tempr(double E);
void calculate_f(double f[NITER][NITER],double t,double tempr, double m0);
void matrix_init(int d,double m[d][d]);
void matrix_print(int d, double m[d][d]);

