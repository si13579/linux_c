#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<shadow.h>


int main(int argc,char **argv)
{
	
	char *crypted_pass;
	char *input_pass;
	struct spwd *shadowline;

	if(argc < 2){
		fprintf(stderr,"Usage...\n");
		exit(1);
	}


	input_pass = getpass("PassWord:");
	
	shadowline = getspnam(argv[1]);

	crypted_pass = crypt(input_pass,shadowline->sp_pwdp); 
	
	if(strcmp(shadowline->sp_pwdp,crypted_pass) == 0 )
		puts("ok!");
	else
		puts("faile!");
	exit(0);
}
