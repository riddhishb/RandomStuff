#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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

int main(){
	char *key = "competant";
	uint32_t m;
	uint32_t pos = m%401;
	printf("%d\n", pos );
	m = jenkins_one_at_a_time_hash(key);
	printf("%d",m);
	return 0;
}
