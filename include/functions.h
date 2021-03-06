double tau_eq(double tempr);
double vv(double tau,double w,double p2);
double f_0(double tau, double w, double p2, double m0);
double f_eq(double tau, double w, double p2, double Tempr);
double Energy_0(double tau,double m0);
double Energy(double tau,double **f);
double Energy_eq(double tau, double tempr);
double Pressure_L(double tau,double **f);
double Pressure_L_0(double tau,double m0);
double Pressure_T(double tau,double **f);
double Tempr(double E);
void calculate_f(double **f,double t,double tempr, double m0);
void calculate_f_0(double **f,double t,double tempr, double m0);
void matrix_init(int d,double **m);
void matrix_print(int d, double **m);

double vv_zero(double tau,double w,double p2);
double f_0_zero(double tau, double w, double p2, double m0);
double Energy_0_zero(double tau,double m0);

