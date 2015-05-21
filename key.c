#include<stdio.h>
#include<sys/io.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define key_read_reg 0x60
#define key_status_reg 0x64

//Print in binary
char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

//Sets the port permissions to access them
void init(){
    if(ioperm(key_read_reg,1,1)){
		printf("**Could not access port. Try running the program with sudo.**\n");
		exit(0);
	}
	if(ioperm(key_status_reg,1,1)){
		printf("**Could not access port. Try running the program with sudo.**\n");
		exit(0);
	}
	
	printf("**Port permissions set!**\n");
}

//Read status from keyboard controller
uint8_t key_status_read(){
	return inb(key_status_reg);
}

//Read input buffer of keyboard register
uint8_t key_read(){
	return inb(key_read_reg);
}


//Parse the code from keyboard register buffer to key pressed
/*
char parse(char *code){
	char key;

	return 
}
*/

int main(){

	init();

	while(1){
		if( key_status_read() & 1 == 1){						//Checked whether keyboard register input buffer is empty or not. If not empty.
			char *read;
			int readint;
			readint = key_read();
			read=byte_to_binary(readint);
			printf("%d\n",readint);
			if(strcmp(read,"00011100")==0){
				break;
			}
		}
	}

	ioperm(key_read_reg,1,0);
	ioperm(key_status_reg,1,0);

	return 0;
}