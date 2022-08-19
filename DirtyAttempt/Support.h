#ifndef SUPPORT_H
#define SUPPORT_H

#include "SystemUtils.h"
#include "ConstDefns.h"



class SupportAndUtils{
public:
    
    const int N = 8; 
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
        for(int rank =0;rank<N;rank++){
            for(int file =0;file<N;file++){
                int square = GetSqaure(rank,file);  
                if(not file) cout<<(8-rank)<<"  ";
                cout<<(GetBit(bitBoard,square)?1:0)<<' '; // Print bit state 1/0
            }
            cout<<'\n';
        }
        cout<<"\n   a b c d e f g h\n"; 
        printf("\n   BitBoard : %llud\n\n",bitBoard);
    }   

    unsigned int state = 1804289383;

    unsigned int GetRandomU32bitnumber(){
        unsigned int num = state; 
        num^=(num<<13); 
        num^=(num>>17);
        num^=(num<<5);  
        state = num; 
        return num; 
    } 

    ull GetRandomU64Numbers(){
        ull nums[4]; 
        for(int i=0;i<4;i++) nums[i] = (ull)(GetRandomU32bitnumber() & 0xFFFF);
        return (nums[0] | (nums[1]<<16) | (nums[2]<<32) | (nums[4]<<48));
    } 

    ull GenerateMagicNumberCandidate(int depth=3){
        assert(depth>=1);
        ull candidate = 0xFFFFFFFFFFFFFFFF; 
        ull magicgen[depth]; 
        for(int i =0;i<depth;i++){
            magicgen[i] = GetRandomU64Numbers(); 
            candidate&=(magicgen[i]);
        }
        return candidate;
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
        return rank*N + file;
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
};

#endif