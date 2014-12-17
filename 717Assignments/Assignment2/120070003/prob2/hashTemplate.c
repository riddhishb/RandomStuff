/*Start of prefix code. DO NOT EDIT PREFIX CODE*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int M=0, N=0;
#define EMPTY -2
#define FREE -1


struct tuple{
	char value[20];
};

struct tuple *valTable = NULL; //used to store the actual strings
uint32_t *hashTable = NULL; //used to store the keys alone


uint32_t jenkins_one_at_a_time_hash(char *key)
{
    uint32_t hash, i;

    int len = strlen(key);
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void init()
{
	int i;
	valTable = (struct tuple *) malloc(sizeof(struct tuple)*M);
	hashTable = (uint32_t *) malloc(sizeof(uint32_t)*M);

	for(i=0; i<M; i++){
		hashTable[i] = EMPTY;
	}
	N = 0;
}

void cleanup()
{
	free(valTable); valTable = NULL;
	free(hashTable); hashTable = NULL;
}

int search(char *a)
{
	uint32_t hash = jenkins_one_at_a_time_hash(a);
	uint32_t pos = hash%M;
	int i;

/*End of prefix code. Do not edit code above this line*/
	
	//Complete rest of the code for search()
}

int insert(char *a)
{
	//Write code for insert()
}

int delete(char *a)
{
	//Write code for delete()
}

/*Start of suffix code. DO NOT EDIT CODE BELOW THIS LINE TILL THE END OF FILE*/

void printTable(FILE *fp)
{
	int i;
	for(i=0; i<M; i++){
		fprintf(fp,"Pos %d : Key %lu ",i,(unsigned long)hashTable[i]);
		if(hashTable[i] != EMPTY && hashTable[i] != FREE){
			fprintf(fp,"Value %s", valTable[i].value);
		}
		fprintf(fp,"\n");
	}
}

int main(int argc, char **argv)
{
	char str[20];
	int i;

	char line[80];
	int op;

	int status;


	if(argc != 3){
		printf("Pass <input file> <outputfile> as arguments when you run the executable\n");
		printf("Example: ./hash input.txt ouptut.txt\n");
		exit(-1);
	}
		


	

	FILE *fp = fopen(argv[1],"r");
	FILE *fp1 = fopen(argv[2],"w");

	if(fp == NULL){
		printf("Input file %s not present\n",argv[1]);
	}

	fgets(line, 80, fp); 
	sscanf(line,"%d %s",&M,str);
	init();

	while(fgets(line, 80, fp) != NULL){
		sscanf(line,"%d %s",&op,str);
		switch(op){
			case 0: status=search(str); fprintf(fp1,"%d\n",status);break;
			case 1: status=insert(str); fprintf(fp1,"%d\n",status);break;
			case 2: status=delete(str); fprintf(fp1,"%d\n",status);break;
			case 3: printTable(fp1); break;
		}
	}	
	fclose(fp);
	fclose(fp1);
	
	cleanup();
	return 0;
}
/*End of suffix code. DO NOT EDIT THE SUFFIX CODE*/
