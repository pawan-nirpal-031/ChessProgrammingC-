#include "Support.h"

class AttackSystem{
public:
    U64 pawn_attack_table[2][64];                  

    U64 MaskPawanAttacks(int side,int square, SupportAndUtils &supp_bot){      
        U64 attacks = 0ULL;                         
        U64 pawn_bit_board = 0ULL;                  
        supp_bot.SetBit(pawn_bit_board,square);  
        if(side==white){                            
           if(not_a_file & (pawn_bit_board >> 7)) attacks |=(pawn_bit_board >> 7);  
           if(not_h_file & (pawn_bit_board >> 9)) attacks |=(pawn_bit_board >> 9);
        }else{
            if(not_h_file & (pawn_bit_board << 7)) attacks |=(pawn_bit_board << 7);  
            if(not_a_file & (pawn_bit_board << 9)) attacks |=(pawn_bit_board << 9);
        } 
        return attacks;                             
    }  

    U64 GetPawnBitBoard(int side,int sqaure){
        return pawn_attack_table[side][sqaure];
    }

    void InitLeaperAttacks(SupportAndUtils &supp_bot){
        for(int sq =0;sq<64;sq++){
            pawn_attack_table[white][sq] = this->MaskPawanAttacks(white,sq,supp_bot);
            pawn_attack_table[black][sq] = this->MaskPawanAttacks(black,sq,supp_bot);
        }
    } 
};


int main(){
    U64 board = 0ULL;  
    SupportAndUtils support; 
    AttackSystem attksys; 
    attksys.InitLeaperAttacks(support); 
    for(int sq =0;sq<64;sq++){
        support.PrintBitBoard(attksys.pawn_attack_table[black][sq]);
    }
    return 0;
}