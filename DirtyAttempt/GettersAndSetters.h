#define GetBit(bitBoard,square) (bitBoard&(1ULL<<square)) 
#define SetBit(bitBoard,square) (bitBoard|=(1ULL<<square)) 
#define ToggleBit(bitBoard,square) (bitBoard^=((1ULL<<square))) 
