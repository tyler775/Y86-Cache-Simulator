#include <iostream>
#include <string>
#include <assert.h>
#include "Cache.h"

/*
 * Cache constructor
 * Creates the twoD array of lines and initializes the
 * associativity, numSets, blockOffsetBits, setIndexBits,
 * and verbose data members.
 */
Cache::Cache(int32_t associativity, int32_t blockOffsetBits, 
             int32_t setIndexBits, bool verbose)
{
	
	const int nsets = 1 << setIndexBits; //nsets equals 2^# of set index bits
	const int col = associativity; //col equal to associativity
	lines = new Line*[nsets];
for(int i = 0; i < nsets; i++)
{
    lines[i] = new Line[col];
	//set each segment
}

	
   //Use set methods to set the associativity,
   //setIndexBits, blockOffsetBits, and verbose 
   //variables in the cache.
   setassociativity(associativity);
   setsetIndexBits(setIndexBits);
   setblockOffsetBits(blockOffsetBits);
   setverbose(verbose);
   
}

/*
 * Line constructor
 * Sets the tag to 0 and the valid bit to false (tag not valid)
 */
Cache::Line::Line()
{
   //This constructor is complete.
   tag = 0;
   valid = false;
}

//Sets associativity variable
void Cache::setassociativity(int32_t a)
{
	associativity = a;
}
//Sets setIndexBits variable
void Cache::setsetIndexBits(int32_t a)
{
	setIndexBits = a;
}
//Sets blockOffsetBits variable
void Cache::setblockOffsetBits(int32_t a)
{
	blockOffsetBits = a;
}
//Gets associativity variable
int32_t Cache::getassociativity()
{
	return associativity;
};
//Gets setIndexBits variable
int32_t Cache::getsetIndexBits()
{
		return setIndexBits;  
};
//Gets blockOffsetBits variable
int32_t Cache::getblockOffsetBits(){
		  
		return blockOffsetBits;  
};
//Sets verbose variable true or false
void Cache::setverbose(bool a)
{
	verbose = a;
}
//Checks if a tag is in a set of a certain index
bool Cache::voidInset(int64_t tag, int64_t index)
{
	bool b = false;
	int a = associativity;
	for (int i = 0; i < a; i++)
	{
		if ((tag == (lines[index][i].tag)) && (lines[index][i].valid == true))
		{
			b = true;
		}
	}
	
	return b;
}
//Checks if set is full. Returns false if
//any part of the cache is blank (contains
//a boolean variable valid equal to false)
bool Cache::isSetFull(int64_t index)
{

	int a0 = associativity;
	
	for (int i = 0; i < a0; i++)
	{
		//If any element in cache is not valid, 
		//the set is not full. Thus, return false.
		if (lines[index][i].valid == false)
		{
			return false;
		}
	}
	//If cache full, return true
	return true;
}

//Method updates the set
void Cache::updateSet(int64_t tag, int64_t index)
{
	int a = 0;
	
	//If the set under the chosen index doesn't contain 
	//the tag, move each element in the set forward by one -
	//evicting the last element in the set if the set is full-
	//and insert a new element containing the tag to the front
	//of the set.
	if (voidInset(tag, index) == false)
	{
		for(int i = associativity - 1; i>0; i--)
		{
        lines[index][i]=lines[index][i-1]; //Move each element forward by one
		}
		lines[index][0].tag = tag; //Element at front of set contains new tag
		lines[index][0].valid = true; //Element at front of set now valid


	} //If the set under row index does contain an element with the tag,
//locate the element and move that element to the front on the set
//
	else if (voidInset(tag, index) == true) 
	{
		for (int j = 0; j < associativity; j++)
		{
			//If set index has element containing the tag,
			//make int a equal to the elements column number
			//and break out of the for loop.
			if(tag == lines[index][j].tag)
			{
				a = j;
				break;
			}
			
		}
		
		for (int k = a; k > 0; k--)
		{
			//Move element to the front of the list.
			lines[index][k]=lines[index][k-1];
			
		}
		
		lines[index][0] .tag = tag; //Element at front of set contains the tag you want
		lines[index][0].valid = true; //Element at front set now valid
		
	}
	
}
//Method returns the column number for next 
//available space in the cache 
int Cache::returnsize(int64_t index)
{
	int a = associativity;
	int b = 0;
	for (int i = 0; i < a; i++)
	{
		if(lines[index][i].valid == true)
		{
			b++;
		}
	}
	
	return b;
	
}
//Function prints contents of the cache with each line
//representing a set.
void Cache::print()
{
	int col = associativity;
	for(int i0 = 0; i0 < (1 << setIndexBits); i0++)
{
	for(int i1 = 0; i1 < col; i1++)
	{
		//Print each element of a single set set in a single row
		std::cout << lines[i0][i1].tag;
		
	}
	//New line after each set, before for-loop has cache move to next set or exit for loop.
	std::cout << "\n";
	
}
//Prints End when print of cache is complete
std::cout << "End" << "\n";
	
}