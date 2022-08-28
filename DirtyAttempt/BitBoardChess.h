#include "Support.h"


class AttackSystem{ 

    void ConstantInializations(){
        side = -1;
        castle = 0;
        enpessant = no_sq;
        for(int i =0;i<12;i++) piece_bitboards[i] = 0ull;
        occupancy[0] = occupancy[1] = occupancy[2] = 0ull;
    }

    void InitLeaperAttacks(SupportAndUtils &supp_bot){ 
        for(int sq =0;sq<64;sq++){
            pawn_attack_table[white][sq] = this->PawnAttackMask(white,sq,supp_bot);
            pawn_attack_table[black][sq] = this->PawnAttackMask(black,sq,supp_bot); 
            knight_attack_table[sq] = this->KnightAttackMask(sq,supp_bot);
            king_attack_table[sq] = this->KingAttackMask(sq,supp_bot);
        }
    }  

public:

    ull pawn_attack_table[2][64];  
    ull knight_attack_table[64];      
    ull king_attack_table[64];        
    ull bishop_attack_masks[64]; 
    ull rook_attack_masks[64]; 
    ull bishop_attack_tables[64][512]; // [sqaure][occupancies]  
    ull rook_attack_tables[64][4096]; 
    ull piece_bitboards[12]; 
    ull occupancy[3]; // white, black, both
    int side = - 1; // black or white 
    int enpessant = no_sq;
    int castle;

    

    AttackSystem(SupportAndUtils &supp_bot){ 
        ConstantInializations();
        InitLeaperAttacks(supp_bot);
        InitSliderPiecesTables(bishop,supp_bot); 
        InitSliderPiecesTables(rook,supp_bot);
       // InitMagicNumbers(supp_bot);
    }

    ull PawnAttackMask(int side,int square, SupportAndUtils &supp_bot){      
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
        for(int tar_rank = rank-1; (tar_rank >=0); tar_rank--){
            int tar_sq = supp_bot.GetSqaure(tar_rank,file);
            attacks|=(1ULL<<tar_sq);
            if((1ULL<<tar_sq) & blocker) break;
        }
        return attacks;
    } 

    ull SetOccupancy(int indx,int bit_count_mask,ull attack_mask, SupportAndUtils &support){
        ull occupancy_map = 0ull; 
        for(int count =0;count<bit_count_mask;count++){
            int sq = support.LeastSigBitIndex(attack_mask); 
            support.ClearBit(attack_mask,sq);
            if(indx & (1<<count)) occupancy_map|=(1ull<<sq);
        }
        return occupancy_map; 
    } 

    ull FindMagicNumber(int sq,int relevent_bits,int bishop_,SupportAndUtils &supp){
        ull occupancies[4096];
        ull attacks[4096];
        ull used_attacks[4096]; 
        ull attack_mask = (bishop_?BishopAttackMask(sq,supp):RookAttackMask(sq,supp)); 
        int occupancy_indices = (1<<relevent_bits); 
        for(int i =0;i<occupancy_indices;i++){
            occupancies[i] = SetOccupancy(i,relevent_bits,attack_mask,supp);
            attacks[i] = bishop_?InFlightBishopAttackMask(sq,occupancies[i],supp):InFlightRookAttackMask(sq,occupancies[i],supp); 
        } 
        for(int rand_cnt = 0;rand_cnt<100000000;rand_cnt++){
            ull magic_num  = supp.GenerateMagicNumberCandidate(); 
            if(supp.NumberOfSetBits(((attack_mask)*magic_num)  & 0xFF00000000000000) <6) continue; 
            memset(used_attacks,0ull,sizeof(used_attacks));
            int indx,fail; 
            for(indx =0,fail =0;!fail and indx<occupancy_indices;indx++){
                int magic_indx =(int)((occupancies[indx]*magic_num)>>(64-relevent_bits));
                if(used_attacks[magic_indx]==0ull){
                    used_attacks[magic_indx] = attacks[indx];
                }else if(used_attacks[magic_indx]!=attacks[indx]){
                    fail = 1;
                }
            }
            if(not fail) return magic_num;
        }
        return 0ull;
    }

    void InitMagicNumbers(SupportAndUtils &supp){ 
        for(int i =0;i<64;i++){
            printf(" 0x%llxULL,\n",FindMagicNumber(i,rook_relevant_occupancy_bits[i],rook,supp));  
            rook_magic_numbers[i] = FindMagicNumber(i,rook_relevant_occupancy_bits[i],rook,supp);
        } 
        cout<<"\n\n";
        for(int i =0;i<64;i++){ 
            printf(" 0x%llxULL,\n",FindMagicNumber(i,bishop_relevant_occupancy_bits[i],bishop,supp)); 
            bishop_magic_numbers[i] = FindMagicNumber(i,bishop_relevant_occupancy_bits[i],bishop,supp); 
        }
    } 

    void InitSliderPiecesTables(int bishop_,SupportAndUtils &supp){
        for(int sq =0;sq<64;sq++){
            bishop_attack_masks[sq] = BishopAttackMask(sq,supp); 
            rook_attack_masks[sq] = RookAttackMask(sq,supp); 
            ull attack_mask = bishop_?bishop_attack_masks[sq]:rook_attack_masks[sq]; 
            int relevent_bits_count = supp.NumberOfSetBits(attack_mask); 
            int occupancy_indices = (1 << relevent_bits_count);
            for(int indx =0;indx<occupancy_indices;indx++){
                if(bishop_){
                    ull occpancy = SetOccupancy(indx,relevent_bits_count,attack_mask,supp); 
                    int magic_indx = (occpancy*bishop_magic_numbers[sq])>>(64-bishop_relevant_occupancy_bits[sq]);
                    bishop_attack_tables[sq][magic_indx] = InFlightBishopAttackMask(sq,occpancy,supp);
                }else{
                    ull occpancy = SetOccupancy(indx,relevent_bits_count,attack_mask,supp); 
                    int magic_indx = (occpancy*rook_magic_numbers[sq])>>(64-rook_relevant_occupancy_bits[sq]);
                    rook_attack_tables[sq][magic_indx] = InFlightRookAttackMask(sq,occpancy,supp);
                }
            }
        }
    }

    inline ull GetBishopAttacks(int sq,ull occupancy){
        occupancy&=bishop_attack_masks[sq]; 
        occupancy*=bishop_magic_numbers[sq];
        occupancy>>=(64-bishop_relevant_occupancy_bits[sq]);
        return bishop_attack_tables[sq][occupancy];
    }

    inline ull GetRookAttacks(int sq,ull occupancy){
        occupancy&=rook_attack_masks[sq]; 
        occupancy*=rook_magic_numbers[sq];
        occupancy>>=(64-rook_relevant_occupancy_bits[sq]);
        return rook_attack_tables[sq][occupancy];
    }
};

