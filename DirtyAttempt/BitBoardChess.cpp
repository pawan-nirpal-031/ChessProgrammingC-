#include "SystemUtils.h"
#include "ConstDefns.h"

class SupportAndUtils{
public:
    
    const int N = 8; 
    const char *aplhabet;

    SupportAndUtils(){
        aplhabet = "abcdefgh";
    }
    
    
    void ToggleBit(U64 &bitBoard,int square){
        (bitBoard^=((1ULL<<square)));
    }

    bool GetBit(U64 &bitBoard,int square){
        return (bitBoard&(1ULL<<square));
    }

    void SetBit(U64 &bitBoard, int square){
        if((bitBoard)&(1ULL<<square)) return;
        (bitBoard|=(1ULL<<square));
    } 

    void ClearBit(U64 &bitBoard,int square){
        if(GetBit(bitBoard,square)) ToggleBit(bitBoard,square);
    }

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

    
    void PrintBitBoardMemoryRepresentation(U64 &bitBoard){ 
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

};

class AttackSystem{
    U64 pawn_attack_table[2][64];                   // [side to move][attck avail on current sqaure] 

public:
    U64 MaskPawanAttacks(int square,int side, SupportAndUtils &supp_bot){      // side is (white/black) to move
        U64 attacks = 0ULL;                         // result attack bit board 
        U64 pawn_bit_board = 0ULL;                  // define piece bit board 
        supp_bot.SetBit(pawn_bit_board,square);  
        if(side==white){                            // side = 1 is black, =0 is white 
            attacks |=(pawn_bit_board >> 7); 
            attacks |=(pawn_bit_board >> 9); 
        }else{

        } 
        //supp_bot.PrintBitBoard(attacks);
        return attacks;                             // return attack map
    }
};


int main(){
    U64 board = 0ULL;  
    SupportAndUtils support; 
    AttackSystem attksys; 
    U64 pwn_brd = attksys.MaskPawanAttacks(h4,white,support);  
    
    return 0;
}