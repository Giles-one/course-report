#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int i,test_dev;
	char data_write[15]="data from user";
	char *data;
	char buf[15];
	test_dev = open("/dev/test",O_RDWR);
	if(test_dev < 0) {
		perror("can't open /dev/test");
		exit(0);
	}
	read(test_dev, buf, 15);
	for(i=0; i<15; i++) {
		printf("%c", buf[i]);
	}
	printf("\n");
	fflush(stdout);
	data = data_write;
	write(test_dev,data,15);
	close(test_dev);
	return 0;
}
