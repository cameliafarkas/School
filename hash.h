#ifndef __HASH__H
#define __HASH__H
#include <stdlib.h>
#include <cmath>

using namespace std;

int hash1(int key)
{
	int *v = new int[32];
	int *w = new int[12];
	int i = 0, j;
	int nr = 0;

	while(key > 0)
	{
		v[i] = key % 2;
		key /= 2;
		++i;
	}

	if(i>=12)
	{
		for(j = 2; j <=12; ++ j)
		{
			w[j-2] = v[j];

		}
	}
	else
	{
		for(j = 2; j <i; ++j)
		{
			w[j-2] = v[j];

		}
	}

	for(j = 0; j < i-2; ++j)
	{
		nr += w[j]*pow(2,j);
	}
	delete[] v;
	delete[] w;
	return nr;
}

int hash2(int key)
{
	int *v = new int[32];
	int *w = new int[14];
	int i = 0, j;
	int nr = 0;

	while(key > 0)
	{
		v[i] = key % 2;
		key /= 2;
		++i;
	}

	if(i>=14)
	{
		for(j = 2; j <=14; ++ j)
		{
			w[j-2] = v[j];

		}
	}
	else
	{
		for(j = 2; j <i; ++j)
		{
			w[j-2] = v[j];

		}
	}

	for(j = 0; j < i-2; ++j)
	{
		nr += w[j]*pow(2,j);
	}
	delete[] v;
	delete[] w;
	return nr;
}


    #endif //__HASH__H
