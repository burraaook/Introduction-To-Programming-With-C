/*
** hw5_lib.h:
**
** The header file declaring library functions.
**
** Author: Burak Kocausta
** 
*/


void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op);


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N);


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance);


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats);


void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3);


void number_encrypt (unsigned char* number);


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0);


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0);


/*------------------------HELPER FUNCTIONS DECLARED------------------------*/
void scan_3polynomial(double *a3, double *a2, double *a1, double *a0);
void scan_coefficient(double *a);
void scan_operator(char *op);
void discard();
void multiply_polynomials(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double b0);
void scan_4d_vectors(double* n0, double* n1, double* n2, double* n3);
void scan_double_num(double *x, int i, int j);
void scan_5_votes(int *a, int *b, int *c, int *d, int *e, int *seat);
void scan_positive_int(int *num);
int find_max(int a, int b, int c, int d, int e);
void order_2_point(double *x1,double *y1, double *x2, double *y2);
int find_region(double x, double y);
void swap_points(double *x1, double *y1, double *x2, double *y2);
void order_w_slope(double *x1, double *y1, double *x2, double *y2, int reg);
void scan_uchar(unsigned char *number);
void assign_bits(char* b, unsigned char* num);
/*------------------------HELPER FUNCTIONS DECLARED------------------------*/

/* Helper Functions which are used in test_operate_polynomials() function. */
void scan_3polynomial(double *a3, double *a2, double *a1, double *a0);

void scan_operator(char *op);
/* Helper Functions which are used in test_operate_polynomials() function. */
