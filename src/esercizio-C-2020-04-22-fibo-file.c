#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


unsigned long * fibonacci_array(unsigned int n);
unsigned int num_digits(unsigned long number);
char * itoa_printf(unsigned long number);
unsigned num_digits(unsigned long n);

int main(){

	int fibonacci_result_length = 40;
	unsigned long * fibonacci_result = fibonacci_array( fibonacci_result_length - 1 );

	// open a file for writing
	int fd = open("fibonacci.txt",
				  O_CREAT | O_TRUNC | O_WRONLY,
				  S_IRUSR | S_IWUSR // l'utente proprietario del file avrà i permessi di lettura e scrittura sul nuovo file
				 );

	if (fd == -1) { // errore!
		perror("open()");
		exit(EXIT_FAILURE);
	}


	for(int i=0 ; i<fibonacci_result_length ; i++){
		char * str = itoa_printf(fibonacci_result[i]);
		int str_len = num_digits(fibonacci_result[i]);
		int res = write(fd, strcat(str, "\n"), str_len);
		if(res == -1){
			perror("write()");
		}
	}

	// close file
	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	exit(0);
}


// return an array where at index i there is the Fibonacci number i
unsigned long * fibonacci_array(unsigned int n){
	unsigned long *arrayResult;
	arrayResult = calloc( n+1, sizeof(unsigned long));

	// check calloc invocation
	if(arrayResult == NULL){
		perror("calloc error!");
		exit(EXIT_FAILURE);
	}

	if( n+1 >= 1){
		arrayResult[0] = 0;
	}
	if( n+1 >= 2){
		arrayResult[1] = 1;
	}
	for(int i = 2 ; i < n+1 ; i++){
		arrayResult[i] = (arrayResult[i-1] + arrayResult[i-2]);
	}
	return arrayResult;
}


// return the number of digits of a number +1 for the total length of a string
unsigned int num_digits(unsigned long number) {
    if (number < 10) return 2;
    return 1 + num_digits(number / 10);
}


// retun the string rappresentation of a number
char * itoa_printf(unsigned long number) {
	char * result;

	result = calloc(num_digits(number), sizeof(char));

	snprintf(
			result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			num_digits(number), // dimensione della zona di memoria
			"%lu", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}

