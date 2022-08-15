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
    ull pawn_attack_table[2][64];  
    ull knight_attack_table[64];      
    ull king_attack_table[64];           

    AttackSystem(SupportAndUtils &supp_bot){
        InitLeaperAttacks(supp_bot);
    }

    ull PawanAttackMask(int side,int square, SupportAndUtils &supp_bot){      
        ull attacks = 0ULL;                         
        ull pawn_bit_board = 0ULL;                  
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

    ull KnightAttackMask(int square, SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        ull pieceBitBoard = 0ULL; 
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

    ull KingAttackMask(int square,SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        ull pieceBitBoard = 0ULL; 
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

    ull BishopAttackMask(int square,SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_rank = rank+1,tar_file = file+1; (tar_rank<7 and tar_file <7); tar_file++, tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank-1,tar_file = file+1; (tar_rank>=1 and tar_file <7); tar_file++, tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank-1,tar_file = file-1; (tar_rank>=1 and tar_file>=1); tar_file--, tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        for(int tar_rank = rank+1,tar_file = file-1; (tar_rank<7 and tar_file >=1); tar_file--, tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,tar_file));
        return attacks;
    } 

    ull RookAttackMask(int square,SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_file = file+1; (tar_file <7); tar_file++)  attacks|=(1ULL<<supp_bot.GetSqaure(rank,tar_file));
        for(int tar_file = file-1; (tar_file >=1); tar_file--)  attacks|=(1ULL<<supp_bot.GetSqaure(rank,tar_file));
        for(int tar_rank = rank+1; (tar_rank <7); tar_rank++)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,file));
        for(int tar_rank = rank-1; (tar_rank >=1); tar_rank--)  attacks|=(1ULL<<supp_bot.GetSqaure(tar_rank,file));
        return attacks;
    }

    ull InFlightBishopAttackMask(int square,ull blocker,SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_rank = rank+1,tar_file = file+1; (tar_rank<=7 and tar_file <=7); tar_file++, tar_rank++){
            int tar_sq = supp_bot.GetSqaure(tar_rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_rank = rank-1,tar_file = file+1; (tar_rank>=0 and tar_file <=7); tar_file++, tar_rank--){
            int tar_sq = supp_bot.GetSqaure(tar_rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_rank = rank-1,tar_file = file-1; (tar_rank>=0 and tar_file>=0); tar_file--, tar_rank--){
            int tar_sq = supp_bot.GetSqaure(tar_rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_rank = rank+1,tar_file = file-1; (tar_rank<=7 and tar_file >=0); tar_file--, tar_rank++){
            int tar_sq = supp_bot.GetSqaure(tar_rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        return attacks;
    }  

    ull InFlightRookAttackMask(int square,ull blocker,SupportAndUtils &supp_bot){
        ull attacks = 0ULL; 
        int rank = square / 8,file = square % 8; 
        for(int tar_file = file+1; (tar_file <=7); tar_file++){
            int tar_sq = supp_bot.GetSqaure(rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_file = file-1; (tar_file >=0); tar_file--){
            int tar_sq = supp_bot.GetSqaure(rank,tar_file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_rank = rank+1; (tar_rank <=7); tar_rank++){
            int tar_sq = supp_bot.GetSqaure(tar_rank,file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        for(int tar_rank = rank-1; (tar_rank >=0); tar_rank--) {
            int tar_sq = supp_bot.GetSqaure(tar_rank,file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        return attacks;
    }
};


int main(){
    SupportAndUtils support; 
    AttackSystem attksys(support);  
    ull block = 0ull;  
    support.SetBit(block,d7); 
    support.SetBit(block,d1);
    support.SetBit(block,d2);
    support.SetBit(block,b4); 
    support.SetBit(block,g4);  
    support.PrintBitBoard(block);

    ull inflight =  attksys.InFlightRookAttackMask(d4,block,support); 
    support.PrintBitBoard(inflight);

    for(int sq =0;sq<64;sq++){
       // support.PrintBitBoard(attksys.king_attack_table[sq]); 
      // ull board =  attksys.InFlightBishopAttackMask(sq,support);
     //  support.PrintBitBoard(board);
    }
    return 0;
}