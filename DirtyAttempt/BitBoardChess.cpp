#include "BitBoardChess.h"


int main(){
    SupportAndUtils supp; 
    AttackSystem atk(supp);
    supp.GetOccupancyBoardOnGivenBoard({a2,b2,c2,d2,e2,f2,g2,h2},atk.piece_bitboards[P]); 
    supp.GetOccupancyBoardOnGivenBoard({b1,g1},atk.piece_bitboards[N]);
    atk.side = white;
    atk.enpessant = e3; 
    atk.castle|=WK;
    atk.castle|=WQ;
    atk.castle|=BK;
    atk.castle|=BQ;
    supp.PrintBoard(atk.piece_bitboards,atk.side,atk.enpessant,atk.castle); 
    for(int piece = P;piece<=k;piece++){
        supp.PrintBitBoard(atk.piece_bitboards[piece]);
    }
    return 0;
}
