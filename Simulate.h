
class Simulate
{
   private:
      Cache * cacheP;      //pointer to the cache object
      int32_t hits;        //number of hits
      int32_t misses;      //number of misses
      int32_t evictions;   //number of evictions
      bool verbose;        //for verbose output
   public:
      Simulate(int32_t associativity, int32_t blockOffsetBits, 
               int32_t setIndexBits, bool verbose);
			 //prints summary of hits, misses, and evictions
      void printSummary();
	  //runs the code
      void run(std::string filename);
	  //function for getting bits from a larger number
	  uint64_t getBits(uint64_t source, int32_t low, int32_t high);
	  

};
