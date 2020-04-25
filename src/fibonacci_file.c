#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIB_INDEX	39

unsigned long fibonacci(unsigned int n)
{
	if (n < 2)
		return n;

	unsigned long nums[3] = {0, 1, 1};
	for (unsigned int i = 3; i <= n; i++) {
		nums[0] = nums[1];
		nums[1] = nums[2];
		nums[2] = nums[0] + nums[1];
	}

	return nums[2];
}

unsigned long *fibonacci_array(unsigned int n)
{
	unsigned long* ret = calloc(n + 1, sizeof(unsigned long));
	if (ret == NULL) {
		perror("calloc() error\n");
		exit(EXIT_FAILURE);
	}

	for (unsigned int i = 0; i <= n; i++)
		ret[i] = fibonacci(i);

	return ret;
}

int min_string_len(unsigned long number)
{
	if (number == 0)
		return 2;
	int result = (int) (floor(log10(labs(number))) + 2);
	if (number < 0)
		result++;
	return result;
}

char *itoa_printf(unsigned long number)
{
	int len = min_string_len(number);
	char *result = calloc(len, sizeof(char));
	snprintf(result, len, "%lu", number);
	return result;
}

int main()
{
	unsigned long *fibonacci_result = fibonacci_array(FIB_INDEX);
	int fd = open("/home/tfonda/fibonacci.txt", O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1) {
		perror("open() error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i <= FIB_INDEX; i++) {
		char *str = itoa_printf(fibonacci_result[i]);
		if (write(fd, strcat(str, "\n"), strlen(str) + 1) == -1) {
			perror("write() error");
			exit(EXIT_FAILURE);
		}
		free(str);
	}

	free(fibonacci_result);
	close(fd);
	return 0;
}
