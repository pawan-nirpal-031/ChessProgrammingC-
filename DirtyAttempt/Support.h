#ifndef SUPPORT_H
#define SUPPORT_H

#include "SystemUtils.h"
#include "ConstDefns.h"



class SupportAndUtils{
public:
    
    const char *aplhabet;

    SupportAndUtils(){
        aplhabet = "abcdefgh";
    }
    
    
    void ToggleBit(ull &bitBoard,int square){
        (bitBoard^=((1ULL<<square)));
    }

    bool GetBit(ull &bitBoard,int square){
        return (bitBoard&(1ULL<<square));
    }

    void SetBit(ull &bitBoard, int square){
        if((bitBoard)&(1ULL<<square)) return;
        (bitBoard|=(1ULL<<square));
    } 

    void ClearBit(ull &bitBoard,int square){
        if(GetBit(bitBoard,square)) ToggleBit(bitBoard,square);
    }

    void PrintBitBoard(ull &bitBoard){ 
        cout<<"\n\n";
        for(int rank =0;rank<8;rank++){
            for(int file =0;file<8;file++){
                int square = GetSqaure(rank,file);  
                if(not file) cout<<(8-rank)<<"  ";
                cout<<(GetBit(bitBoard,square)?1:0)<<' '; // Print bit state 1/0
            }
            cout<<'\n';
        }
        cout<<"\n   a b c d e f g h\n"; 
        printf("\n   BitBoard : %llud\n\n",bitBoard);
    }   

    unsigned int random_state = 1804289383;

    unsigned int GetRandomU32bitnumber(){
        unsigned int num = random_state; 
        num^=(num<<13); 
        num^=(num>>17);
        num^=(num<<5);  
        random_state = num; 
        return num; 
    } 

    ull GetRandomU64Numbers(){
        ull nums[4]; 
        for(int i=0;i<4;i++) nums[i] = ((ull)(GetRandomU32bitnumber()) & 0xFFFF);
        return (nums[0] | (nums[1]<<16) | (nums[2]<<32) | (nums[3]<<48));
    } 

    ull GenerateMagicNumberCandidate(){
        return (GetRandomU64Numbers() & GetRandomU64Numbers() & GetRandomU64Numbers());
    }

    
    void PrintBitBoardMemoryRepresentation(ull &bitBoard){ 
        cout<<"\n";
        int Bytes = 8; 
        int bitlvl = 8;
        for(int i =0;i<Bytes;i++){
            for(int j =0;j<bitlvl;j++){
                cout<<(GetBit(bitBoard,GetSqaure(i,j))?1:0);
            }
            cout<<" ";
        }
        cout<<"\n\n";
    }

    int GetSqaure(int rank,int file){
        return rank*8 + file;
    }

    void PrintBoardDefFormat(){ 
        for(int i =8;i>=1;i--){
            for(int j =0;j<8;j++) cout<<"\""<<aplhabet[j]<<i<<"\", ";
            cout<<'\n';
        }
    }

    static inline int NumberOfSetBits(ull board){
        int count =0; 
        while(board){
            ++count;
            board &=(board-1);
        }
        return count;
    }

    static inline int LeastSigBitIndex(ull board){
        if(board) return NumberOfSetBits((board & -board)-1);
        return -1;
    }  

    void PrintBoard(ull piece_bitboards[],int side,int &enpassant,int &castle){
        cout<<"\n";
        for(int r =0;r<8;r++){
            for(int f =0;f<8;f++){
                int sq = GetSqaure(r,f); 
                int piece = -1; 
                if(not f) cout<<(8-r)<<"  ";
                for(int bb_piece=P;bb_piece<=k;bb_piece++){
                    if(GetBit(piece_bitboards[bb_piece],sq)) piece = bb_piece;
                }
                cout<<(piece==-1?".":unicode_pieces[piece])<<' ';
            }
            cout<<'\n';
        }
        cout<<"\n   a b c d e f g h\n"; 
        cout<<"\n   Side         : "<<(!side?"white":"black"); 
        cout<<"\n   Enpassant    : "<<(enpassant!=no_sq?PositionToIndexMap[enpassant]:"none");
        printf("\n   Castling     : %c%c%c%c\n\n",((WK&castle)?'K':'-')
                                           ,((WQ&castle)?'Q':'-')
                                           ,((BK&castle)?'k':'-')
                                           ,((BQ&castle)?'q':'-'));
    }

    ull GetOccupancyBoard(vector<int>blocking){
        ull occupancy = 0ull; 
        for(int &x : blocking){
            SetBit(occupancy,x);
        }
        return occupancy;
    } 

    void GetOccupancyBoardOnGivenBoard(vector<int>blocking,ull &board){
        for(int &x : blocking){
            SetBit(board,x);
        }
    } 
};

#endif