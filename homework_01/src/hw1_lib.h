/*
** hw1_io.h:
**
** The header file declaring library functions.
**
** Author: Burak Kocausta
** 
*/

double third_degree_pol(double coeffs[], double x); /* calculates the P(x).(coefficients, x) */ 

double fourth_degree_pol(double coeffs[], double x); /* calculates the P(x).(coefficients, x) */

double find_pot_root(double xs, double ys, double xe, double ye); /* calculates the potential root between (xs,xe) */

double tpzd_area(double xs, double ys, double xe, double ye); /* calculates trapezoid's area.(xstart,f(xstart),xend,f(xend)) */

double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta);


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta);


double root3(double a0, double a1, double a2, double a3, double xs, double xe);


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe);

double third_degree_pol(double coeffs[], double x); /* calculates the P(x).(coefficients, x) */ 

double fourth_degree_pol(double coeffs[], double x); /* calculates the P(x).(coefficients, x) */

double find_pot_root(double xs, double ys, double xe, double ye); /* calculates the potential root between (xs,xe) */

double tpzd_area(double xs, double ys, double xe, double ye); /* calculates trapezoid's area.(xstart,f(xstart),xend,f(xend)) */
