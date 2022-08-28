#include "BitBoardChess.h"

class TestingInfrastructre{

};

int main(){
    SupportAndUtils supp; 
    AttackSystem atk(supp);
    supp.SetBit(atk.piece_bitboards[P],e2);
    cout<<unicode_pieces[P]<<" "<<unicode_pieces[char_piece_encoding['K']]<<'\n';
}