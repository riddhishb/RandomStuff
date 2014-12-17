#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Global Variables
int N;
int *stack;
int a;
int b;
int c;
int size0;
int size1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int push(int sn,int element){			// the push function for each stack
	int ans=-1;
	int j;
	if(size1+size0 == N) {ans = -1;}
	else if(sn == 0){
		
		for(j = 0; j<size0;j++){

			stack[j+1] = stack[j];
		}
		//printf("%d\n",element );
		stack[0] = element;
		size0++;
		ans = 1;
	}
	else if(sn == 1){
//		printf("%s\n", "bitch" );
		for(j = 0; j<size1;j++){

			stack[N-2-j] = stack[N-1-j];
		}
		stack[N-1] = element;
		size1++;
		ans = 1;
	}
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pop(int sn){				// the pop function for each stack

	int ans=-1;
	int j;
	if(sn == 0){
		if(size0 == 0){ans = -1;}
		else{
			ans = stack[0];
			size0--;
			for(j = 0;j<size0;j++){
				stack[j] = stack[j+1];
			}
		}
	}
	if(sn == 1){
		if(size1 == 0){ans = -1;}
		else{
			ans = stack[N-1];
			size1--;
			for(j = 0;j<size1;j++){
				stack[N-1-j] = stack[N-2-j];
			}
		}
	}
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int peek(int sn){					// the peak function

	int ans=-1;
	if(sn==0 && size0 !=0) ans = stack[0];
	if(sn==1 && size1 !=0) ans = stack[N-1];  
	return ans;
}

int isEmpty(int sn){				// the isEmpty function for both stacks
	int ans=0;
	if(sn==0 && size0 == 0) ans = 1;
	if(sn==1 && size1 == 0) ans = 1;
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read data from inputfile, perform Stack operations and output the corrosponding result

void stack_implementation(char *inputfile){
	
	int ret = -1;
	int i=0; 
	FILE *file = fopen (inputfile, "r" );
	if ( file != NULL )
	{
		char line [128];
		int aa[3];
		
		while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
		{
			
			if(i==0){ N =atoi(line);
				stack=malloc(N*sizeof(int));  //memory allocated using malloc	
				int k;
				for(k=0;k<N;k++) stack[k] = 0;
			}

			if(i>0){
				int k; 
				sscanf(line,"%d %d %d",&a,&b,&c);
			
				if(b == 1 || b == 0){
				if(a == 0){
					ret =  push(b,c);
				}
				if(a == 1){
					ret = pop(b);
				}
				if(a == 2){
					ret =  peek(b);
				}
				if(a == 3){
					ret = isEmpty(b);
				}
				printf("%d\n",ret );
			}
			}
			// display ret value

				i++;
		}
		fclose ( file );
	}
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	size0 = size1 = 0;
	stack_implementation(argv[1]);
	return 0;
}



