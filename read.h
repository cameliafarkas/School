#define HMAXL1 4096
#define HMAXL2 16384

#ifndef __READ__H
#define __READ__H
#include <stdlib.h>
#include "hash.h"
#include <fstream>
#include "hashtable.h"
#include <stdio.h>
#include <iostream>

using namespace std;


void read(istream& ram, int address, Hashtable<int, unsigned int>& L1, Hashtable<int, unsigned int>& L2)
{
	unsigned int idx1, idx2, v;
	int a;

	bool cond1 = L1.has_key(address);
	bool cond2 = (L1.has_key(address))&&!(L1.is_dirty(address));
	bool cond3 = (L2.has_key(address));

	if((!cond1)||(cond2))
	{
		if(cond3)
		{
			L1.put(address, L2.get(address), 0);

		}
		else
		{
			while(!ram.eof())
			{
				ram >> a >> v;

				if (a == address)
				{
					L2.put(a, v, 1);
					L1.put(a, v, 0);
					break;
				}
			}
		}
	}

}

#endif