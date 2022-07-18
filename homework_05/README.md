<h1>Functions</h1>

1- Operates given polynomials with coefficients, and operator type.  
- void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op);  
  
2- Reads N number of 4D vectors from command prompt, and calculates euclidian distance between two consecutive vectors. Returns the longest distance from parameter.   
- void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N);  
- void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance);  
  
3- Allocates seats with Dhont Method. Reads every parameter from command prompt.  
- void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats);  

4- Reads 3 points from user, and orders them in counter clockwise. Returns the ordered version.  
- void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3);  

5- Encrypts the number by with given algorithm in the pdf.  
- void number_encrypt (unsigned char* number);  
- void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0);  
- void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0);  