#include "BitBoardChess.h"


int main(){
    SupportAndUtils supp; 
    AttackSystem atk(supp);
    supp.SetBit(atk.piece_bitboards[P],e2);
    supp.PrintBitBoard(atk.piece_bitboards[P]); 
    
    return 0;
}
