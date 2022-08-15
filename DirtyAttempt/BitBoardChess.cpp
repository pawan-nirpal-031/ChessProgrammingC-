#include "Support.h"

class AttackSystem{

    void InitLeaperAttacks(SupportAndUtils &supp_bot){
        for(int sq =0;sq<64;sq++){
            pawn_attack_table[white][sq] = this->PawanAttackMask(white,sq,supp_bot);
            pawn_attack_table[black][sq] = this->PawanAttackMask(black,sq,supp_bot); 
            knight_attack_table[sq] = this->KnightAttackMask(sq,supp_bot);
            king_attack_table[sq] = this->KingAttackMask(sq,supp_bot);
        }
    }  

public:
    U64 pawn_attack_table[2][64];  
    U64 knight_attack_table[64];      
    U64 king_attack_table[64];           

    AttackSystem(SupportAndUtils &supp_bot){
        InitLeaperAttacks(supp_bot);
    }

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

    U64 KingAttackMask(int square,SupportAndUtils &supp_bot){
        U64 attacks = 0ULL; 
        U64 pieceBitBoard = 0ULL; 
        supp_bot.SetBit(pieceBitBoard,square);
        if((pieceBitBoard>>1) & not_h_file) attacks|=(pieceBitBoard>>1);
        if((pieceBitBoard>>7) & (not_a_file)) attacks|=(pieceBitBoard>>7); 
        if((pieceBitBoard>>8)) attacks|=(pieceBitBoard>>8);
        if((pieceBitBoard>>9) & (not_h_file)) attacks|=(pieceBitBoard>>9); 
        if((pieceBitBoard<<1) & not_a_file) attacks|=(pieceBitBoard<<1);
        if((pieceBitBoard<<7) & (not_h_file)) attacks|=(pieceBitBoard<<7); 
        if((pieceBitBoard<<8)) attacks|=(pieceBitBoard<<8);
        if((pieceBitBoard<<9) & (not_a_file)) attacks|=(pieceBitBoard<<9);
        return attacks;
    }

    U64 BishopAttackMask(int square,SupportAndUtils &supp_bot){
        U64 attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_rank = rank+1,tar_file = file+1; (tar_rank<7 and tar_file <7); tar_file++, tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank-1,tar_file = file+1; (tar_rank>=1 and tar_file <7); tar_file++, tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank-1,tar_file = file-1; (tar_rank>=1 and tar_file>=1); tar_file--, tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank+1,tar_file = file-1; (tar_rank<7 and tar_file >=1); tar_file--, tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        return attacks;
    } 

    U64 RookAttackMask(int square,SupportAndUtils &supp_bot){
        U64 attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_file = file+1; (tar_file <7); tar_file++)  attacks|=(1ULL<<supp_bot.GetSqaure(rank,tar_file));
        for(int tar_file = file-1; (tar_file >=1); tar_file--)  attacks|=(1ULL<<supp_bot.GetSqaure(rank,tar_file));
        for(int tar_rank = rank+1; (tar_rank <7); tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,file));
        for(int tar_rank = rank-1; (tar_rank >=1); tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,file));
        return attacks;
    }

};


int main(){
    SupportAndUtils support; 
    AttackSystem attksys(support); 
    for(int sq =0;sq<64;sq++){
       // support.PrintBitBoard(attksys.king_attack_table[sq]); 
       U64 board =  attksys.RookAttackMask(sq,support);
       support.PrintBitBoard(board);
    }
    return 0;
}