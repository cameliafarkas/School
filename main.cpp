#define HMAXL1 4096
#define HMAXL2 16384

#include "hashtable.h"
#include "hash.h"
#include "read.h"
#include "write.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>
using namespace std;

void scriere_fisier(ostream& cache, Hashtable<int, unsigned int>& L, unsigned int HMAXL)
{
	for(int i = 0; i < HMAXL; ++i)
	{
		if(L.get_key(i, 0) != -1)
		{
			cache << i << " " << 0 << " " << L.get_key(i, 0) << " " << L.get(L.get_key(i,0));

			//cout << L.get_key(i, 0) << endl;

			//cout << L.get(L.get_key(i,0)) << endl;

			if(L.is_dirty(L.get_key(i,0)))
			{
				cache << " *";
			}
			cache << endl;
		}
		if(L.get_key(i, 1) != -1)
		{
			cache << i << " " << 1 << " " << L.get_key(i, 1) << " " << L.get(L.get_key(i,1));

			//cout << L.get_key(i, 1) << endl;
			//cout << L.get(L.get_key(i,1)) << endl;
			if(L.is_dirty(L.get_key(i,1)))
			{
				cache << " *";
			}
			cache << endl;
		}
	}
}

int main()
{
	string op;
	unsigned int newdata;
	int address;
	bool core;
	int i;

	ifstream ram("ram.in");
	ifstream operation("operations.in");

	ofstream cache("cache.out");
	ofstream ram0("ram.out");

	Hashtable<int, unsigned int> L1_1(HMAXL1, hash1);
	Hashtable<int, unsigned int> L1_2(HMAXL1, hash1);
	Hashtable<int, unsigned int> L2(HMAXL2, hash2);


	while(!operation.eof())
	{
		operation >> core >> op >> address;

		if(op == "w")
		{
			operation >> newdata;

			if(core)
			{
				write(ram, ram0, address, newdata, L1_2, L1_1, L2);
			}
			else
			{
				write(ram, ram0, address, newdata, L1_1, L1_2, L2);
			}

			
		}
		else
		{
			if(core)
			{
				read(ram, address, L1_2, L2);
			}
			else	
			{
				read(ram, address, L1_1, L2);
			}
			
		}
	}

	scriere_fisier(cache, L1_1, HMAXL1);
	cache << endl;
	scriere_fisier(cache, L1_2, HMAXL1);
	cache << endl;	
	scriere_fisier(cache, L2, HMAXL2);


	return 0;
}
