#include "BitBoardChess.h"


int main(){
    SupportAndUtils supp; 
    AttackSystem atk(supp);
    string somepos = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1 ";
    atk.ParseFENString(somepos,supp);
    supp.PrintBoard(atk.piece_bitboards,atk.side,atk.enpessant,atk.castle);
    return 0;
}
