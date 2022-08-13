#include "Support.h" 
using namespace std;   



void PrintBitBoard(U64 &bitBoard){ 
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

int GetSqaure(int rank,int file){
    return rank*N + file;
}

void PrintBoardDefFormat(){ 
    for(int i =8;i>=1;i--){
        for(int j =0;j<8;j++) cout<<"\""<<aplhabet[j]<<i<<"\", ";
        cout<<'\n';
    }
}

void ClearBit(U64 &bitBoard,int square){
    if(GetBit(bitBoard,square)) ToggleBit(bitBoard,square);
}