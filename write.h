#define HMAXL1 4096
#define HMAXL2 16384

#ifndef __WRITE__H
#define __WRITE__H
#include <stdlib.h>
#include "hash.h"
#include <fstream>
#include "hashtable.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void write_ram(ostream& ram0, int address, unsigned int way)
{
	unsigned int nrcifre, nrcifre2, aux1, aux2, i;

						aux2 = way;
						nrcifre = 0;
						nrcifre2 = 0;

						do
						{
							++nrcifre;
							aux1 = aux1/10;
						}
						while(aux1 != 0);

						do
						{
							++nrcifre2;
							aux2 = aux2/10;
						}
						while(aux2 != 0);
					

						for(i = 0; i < 10 - nrcifre; ++i)
						{
							ram0 << "0";
						}

						ram0 << address << " ";

						for(i = 0; i < 10 - nrcifre2; ++i)
						{
							ram0 << "0";
						}

						ram0 << way << endl;

					
}

bool write(istream& ram, ostream& ram0, int address, unsigned int newdata, Hashtable<int, unsigned int>& L1_1, Hashtable<int, unsigned int>& L1_2, Hashtable<int, unsigned int>& L2)
{
	unsigned int idx1, idx2, v, way;
	int a;

	idx1 = hash1(address);
	idx2 = hash2(address);

	if((L1_1.has_key(address))&&(!L1_1.is_dirty(address)))
	{
		L1_1.put(address, newdata, 0);
		L2.put(address, newdata, 1);

		if(L1_2.has_key(address))
		{
			L1_2.make_dirty(address);
		}
		return 1;
	}

	if(L2.has_key(address))
		{ 
			L1_1.put(address, newdata, 0);
			
			way = L2.put(address, newdata, 1);

			if(way >= 0)
					{
						write_ram(ram0, address, way);
					}
				
		}
		else
		{ 
			while(!ram.eof())
			{
				ram >> a >> v;

				if(a == address)
				{
					L1_1.put(address, newdata, 0);

					way = L2.put(address, newdata, 1);

					if(way >= 0)
					{
						write_ram(ram0, address, way);
					}
					break;
				}
			}
		}
	
	
}


#endif