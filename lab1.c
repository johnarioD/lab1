#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Program written by Diamantaras Ioannis 9387, Mpounarelis Dimosthenis 9431
 * This simple script returns the hypotenuse of a triangle with given sides
 * For simplicity th length of each side is an integer that is given to the program
 * via command line arguments
 */
float main(int argc, char *argv[]){

	/* A simple check to see if the user has provided the
	 * correct amount of command line arguments
	 */
	if(argc!=3){
		printf("Usage: <output_file_name> X Y");
		return(1);
	}


	int x = atoi(argv[1]); // The sides of the triangle are initialized by command line
	int y = atoi(argv[2]);
	double result = (double)(x*x+y*y);
	result = sqrt(result); // A simple usage of the pythagorean theorem
	/* The result is printed out in the command line.
	 * As the result is also returned by the program, it can be piped into a file.
	 */
	printf("The triangle has a hypotenuse of: %f", result);
	printf("\n");
	return(result);
}
