#include "Support.h"

class AttackSystem{
public:
    U64 pawn_attack_table[2][64];  
    U64 knight_attack_table[64];                 

    U64 PawanAttackMask(int side,int square, SupportAndUtils &supp_bot){      
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
            pawn_attack_table[white][sq] = this->PawanAttackMask(white,sq,supp_bot);
            pawn_attack_table[black][sq] = this->PawanAttackMask(black,sq,supp_bot); 
            knight_attack_table[sq] = this->KnightAttackMask(sq,supp_bot);
        }
    }  

    U64 KnightAttackMask(int square, SupportAndUtils &supp_bot){
        U64 attacks = 0ULL; 
        U64 pieceBitBoard = 0ULL; 
        supp_bot.SetBit(pieceBitBoard,square);  
        if(not_hg_file & (pieceBitBoard>>10)) attacks|=(pieceBitBoard>>10); 
        if(not_a_file & ((pieceBitBoard>>15))) attacks|=(pieceBitBoard>>15); 
        if(not_h_file & (pieceBitBoard>>17)) attacks|=(pieceBitBoard>>17);
        if(not_ab_file & (pieceBitBoard>>6)) attacks|=(pieceBitBoard>>6);

        if(not_ab_file & (pieceBitBoard<<10)) attacks|=(pieceBitBoard<<10); 
        if(not_h_file & ((pieceBitBoard<<15))) attacks|=(pieceBitBoard<<15); 
        if(not_a_file & (pieceBitBoard<<17)) attacks|=(pieceBitBoard<<17);
        if(not_hg_file & (pieceBitBoard<<6)) attacks|=(pieceBitBoard<<6); 
        return attacks;
    } 
};


int main(){
    U64 board = 0ULL;  
    SupportAndUtils support; 
    AttackSystem attksys; 
    attksys.InitLeaperAttacks(support);
    for(int sq =0;sq<64;sq++){
        support.PrintBitBoard(attksys.knight_attack_table[sq]);
    }
    return 0;
}