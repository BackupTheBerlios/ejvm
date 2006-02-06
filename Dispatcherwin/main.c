#include"ejvm.h"

 int PC;
int main(int argc ,char** args){
	
	int f2 (char* x,...){return 0;}
	int f1 (char* x,...){return 0;}
	int ((*f[3]) (char*,...)) ;
	
	f[0]=f1;
	f[0]("hj");
	f[1]= f2;
	{
	register int i;
	for(i=0; i< argc ;i++)
		printf("\n %s",args[i]);
	}
	fflush(stdout);
	
	return 0;
}
