

class Cache
{
   class Line         
   {
      public:
         int64_t tag;  //address tag
         bool valid;   //is tag valid
         Line();
   };
   private:
      Line ** lines;           //cache is a 2D array of lines
      int32_t numSets;         //number of cache sets (number of rows)
      int32_t associativity;   //set associativity (number of columns)
      int32_t blockOffsetBits; //number of bits of the address for block offset
      int32_t setIndexBits;    //number of bits of the address for set index
      bool verbose;            //verbose mode of execution
   public:
      Cache(int32_t associativity, int32_t blockOffsetBits, 
            int32_t setIndexBits, bool verbose);
	  
	  void setassociativity(int32_t a);
	  void setsetIndexBits(int32_t a);
	  void setblockOffsetBits(int32_t a);
	  int32_t getassociativity();
	  int32_t getsetIndexBits();
	  int32_t getblockOffsetBits();
	  void setverbose(bool a);
	  bool voidInset(int64_t tag, int64_t index);
	  bool isSetFull(int64_t index);
	  void updateSet(int64_t tag, int64_t index);
	  int returnsize(int64_t index);
	  void print();
	  
};
