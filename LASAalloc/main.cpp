
/*
 * LALLOC Main test
 * 
 * Choose test by using macro SIMPLETEST1 or SIMPLETEST2
 * 
 * Do not change anything else in this file
 */ 
#define SIMPLETEST2



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include"LASAalloc.h"



#ifdef SIMPLETEST1
int main(int argc, char *argv[])
{
	
	LASAalloc	lasa;

	
	char *array;
	int i;

	array = (char *)lasa.lalloc(10);
	if(array == NULL)
	{
		fprintf(stderr,"call to lasa.lalloc() failed\n");
		fflush(stderr);
		exit(1);
	}

	for(i=0; i < 9; i++)
	{
		array[i] = 'a' + i;
	}
	array[9] = 0;

	printf("here is my nifty new string: %s\n",array);

	lasa.lfree(array);

  cout << "TEST 1 SUCCESS" << endl;

	return(0);
}

	
#endif //SIMPLETEST1

#ifdef SIMPLETEST2

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "LASAalloc.h"

int main(int argc, char *argv[])
{
    char *a1;
    char *a2;
    char *a3;
    char *a4;

    LASAalloc lasa;

    a1 = (char *)lasa.lalloc(128);
    cout << "error 1" << endl;
    if (a1 == NULL)
    {
        fprintf(stderr, "call to lasa.lalloc(128) failed\n");
        fflush(stderr);
        exit(1);
    }

    a2 = (char *)lasa.lalloc(32);
    if (a2 == NULL)
    {
        fprintf(stderr, "first call to lasa.lalloc(32) failed\n");
        fflush(stderr);
        exit(1);
    }

    lasa.lfree(a1);

    a3 = (char *)lasa.lalloc(104);
    if (a3 == NULL)
    {
        fprintf(stderr, "call to lasa.lalloc(104) failed\n");
        fflush(stderr);
        exit(1);
    }

    a4 = (char *)lasa.lalloc(8);
    if (a4 == NULL)
    {
        fprintf(stderr, "call to lasa.lalloc(8) failed\n");
        fflush(stderr);
        exit(1);
    }

    lasa.lfree(a2);
    lasa.lfree(a3);
    lasa.lfree(a4);

    return 0;
}

#endif
