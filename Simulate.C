#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "Cache.h"
#include "Simulate.h"

/* Simulate
 * Initializes the hits, misses, evictions, and verbose
 * data members.
 * Create the cache object that will be used in the
 * simulation.
 */
Simulate::Simulate(int32_t associativity, int32_t blockOffsetBits, 
                   int32_t setIndexBits, bool verbose)
{
   //This method is complete
   hits = misses = evictions = 0;
   cacheP = new Cache(associativity, blockOffsetBits, setIndexBits, verbose);
   this->verbose = verbose;
}

/*
 * run
 * Opens the file of addresses and uses each address of a data item
 * to perform a cache access.  The addresses are formatted as follows:
I 0400d7d4,8
 M 0421c7f0,4
 L 04f6b868,8
 S 7ff0005c8,8

Each line denotes one or two memory accesses. The format of each line is

[space]operation address,size

The operation field denotes the type of memory access: 
I denotes an instruction load, L a data load, S a data store, and M a 
data modify (i.e., a data load  followed by a data store, thus two 
sequential accesses to cache). There is never a space before an I. 
There is always a space before each M, L, and S. The address field 
specifies a 64-bit hexadecimal memory address. The size field specifies 
the number of bytes accessed by the operation.  The size
field and instruction (I) addresses can be ignored.

This method will use an address to access the cache
and update the hits, misses, and evictions data members.
*/
void Simulate::run(std::string filename)
{
	std::ifstream a0;
	std::string type;
	std::string addrStr;
	uint64_t addr, tag, index, be0 = 0;
	a0.open(filename);
	//a0 tries to open the file. If the file named by
	//the string filename is not available, error message
	//gets displayed.
	if(!a0)
	{
		std::cout << "File not available..." << std::endl;
	} else {
		//If file is available, while loop reads the type of 
		//cache instruction and address string
		while (a0 >> type)
		{
			a0 >> addrStr;
			
			if(type != "I")
		{
			//If the instruction isn't 'I', code records
			//the address in numerical form from the address String,
			//the tag bits, and the index bits.
			addr = std::stol(addrStr, NULL, 16);
			std::cout << addr << std::endl;
			tag = getBits(addr, (cacheP->getblockOffsetBits() + cacheP->getsetIndexBits()),63);
			index = getBits(addr, cacheP->getblockOffsetBits(), (cacheP->getblockOffsetBits() + cacheP->getsetIndexBits()) - 1);
			if(type == "M")
			{
				be0 = 2;
				
			} else{
				be0 = 1;
			}
			//If the instruction is M, the while loop runs twice.
			//Otherwise, it runs twice.
			while(be0 > 0){
			if(cacheP->voidInset(tag, index))
			{
				//If the tag and index are already in the cache,
				//increase the long hit by one
				hits++;
			} else {
				//If the tag and index are not already in the cache,
				//increase the long misses by one
				misses++;
				if (cacheP-> isSetFull(index))
				{
					//If the set of the cache is full,
				//increase the int evictions by one
					evictions++;
				}
			}
			//print the cache contents
			cacheP->print();
			//update the cache
			cacheP->updateSet(tag, index);
			//Subtract one from the long be0 
			be0--;
			}
		} 
		
		}
		
		
	}
	
	a0.close();
   //You will need to write this.
   //It will call methods in the Cache class that you
   //will also have to write.
}

/*
 * printSummary
 * Prints the number of hits, misses, and evictions both
 * to stdout and to a file to support automatic testing
 */
void Simulate::printSummary()
{
   //This method is complete
   std::fstream fs;
   printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
   fs.open(".csim_results", std::fstream::out);
   assert(fs.is_open());
   fs << hits << " " << misses << " " << evictions <<"\n";;
   fs.close();
}

//Methods retrieves a certain number of bits from a long number
//from the positions between the low and high number
uint64_t Simulate::getBits(uint64_t source, int32_t low, int32_t high)
{
   uint64_t long1 = ((sizeof(source)*8)-1);
	if(low < 0 || high > long1 || low > high) {return 0;}
   uint64_t l2 = (source << (uint64_t)(long1-high)) >> (uint64_t)((long1-high)+low);
	return l2;

}

/* You will need to determine what other methods you need and
 * add them.
 */
