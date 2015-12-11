/****************************
AES 128 bit - Author: Mohamed Essam Fathalla
******************************/

#include <iostream>
#include <iomanip>
using namespace std;
 unsigned char sbox[256] =
 {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
 };
 unsigned char Rcon[32] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A,
    0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A,
    0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39,
 };
void RotWord(unsigned long rot){
    unsigned char temp ,rot1[4];
    rot1[0] = ( rot >> 24 ) & 0xFF;
    rot1[1] = ( rot >> 16 ) & 0xFF;
    rot1[2] = ( rot >> 8 ) & 0xFF;
    rot1[3] = ( rot  ) & 0xFF;
    temp = rot1[0];
    rot1[0] = rot1[1];
    rot1[1] = rot1[2];
    rot1[2] = rot1[3];
    rot1[3] = temp;
    rot = (rot1[0] << 24) & ( rot1[1] << 16 ) &( rot1[2] << 8)& rot1[3];
}

void SubWord(unsigned long sub){
    unsigned char rot1[4];
    rot1[0] = ( sub >> 24 ) & 0xFF;
    rot1[1] = ( sub >> 16 ) & 0xFF;
    rot1[2] = ( sub >> 8 ) & 0xFF;
    rot1[3] = ( sub  ) & 0xFF;

    rot1[0] = sbox[rot1[0]];
    rot1[1] = sbox[rot1[1]];
    rot1[2] = sbox[rot1[2]];
    rot1[3] = sbox[rot1[3]];
    sub = (rot1[0] << 24) & ( rot1[1] << 16 ) &( rot1[2] << 8)& rot1[3];
}
void keyExp(unsigned char* key,unsigned long* w){

    //key length 16
    //n rounds 10
    //n words = (10+1)*4 = 44

    unsigned long temp;
    for (int i = 0; i < 4; i++){
        w[i] = (key[4*i] << 24);
        w[i] = w[i] & ( key[4*i+1] << 16 );
        w[i] = w[i] &( key[4*i+2] << 8);
        w[i] = w[i]& key[4*i+3];
    }
    for (int i = 4; i < 44; i++)
    {
        temp = w[i-1];
        if (i % 4 == 0){
            RotWord(temp);
            SubWord(temp);
            temp = temp ^ Rcon[i/4];
        }
        w[i] = w[i - 4] ^ temp;
    }
}

//Main Blocks : 1. substit bytes .. 2. shift rows  .. 3. mix col .. 4. Add rounds keys
void substitute_bytes(unsigned char* S[4]){
    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j < 4 ;j++)
            S[i][j] = sbox[S[i][j]];
}
void shift_rows(unsigned char* S[4]){
    for(int col = 1; col < 4;col++)
        for(int row = 0; row < 4;row++){
            S[col][row] = S[col][(row+col)%4];
        }
   /* unsigned char temp;
    temp = S[1][0];
    S[1][0] = S[1][3];
    S[1][1] = temp;
    temp = S[1][2];
    S[1][2] = S[1][1];
    S[1][3] = temp;

    temp = S[2][0];
    S[2][0] = S[2][2];
    S[2][2] = temp;
    temp = S[2][1];
    S[2][1] = S[2][3];
    S[2][3] = temp;

    temp =S[3][0];
    S[3][0]=S[3][3];
    S[3][3]=S[3][2];
    S[3][2]=S[3][1];
    S[3][1]=temp; */
}

void mix_columns(unsigned char* S[4]){
     for (int col = 0; col < 4; col++ ) {
        for (int j = 0; j < 4; j++) {
            //S[(4*j) + i] = (0x02 * S[(4*j) + i]) ^ (0x03 * S[(4*(j+1)) + i]) ^ S[(4*(j+2)) + i]
             //^ S[(4*(j+3)) + i];
             S[col][j] = (0x02 * S[col][j] ) ^ (0x03 * S[col][j+1]) ^ S[col][j+2] ^ S[col][j+3];
        }
    }
}
void add_round_key(unsigned char** S ,unsigned long* key){
    for(int row = 0 ; row < 4 ; row++){
        S[4][row] ^= (key[row] & 0xFF) ;
        S[3][row] ^= (key[row] & 0xFF00) ;
        S[2][row] ^= (key[row] & 0xFF0000) ;
        S[0][row] ^= (key[row] & 0xFF000000) ;
    }

}
void encrypt(unsigned char** plaintext ,unsigned char* key){
    unsigned long *expendedkey[44];
    keyExp(key,expendedkey[44]);
    add_round_key(&plaintext[4],expendedkey[0,4]);
    for(int i = 0 ; i < 9;i++){
        substitute_bytes(&plaintext[4]);
        shift_rows(&plaintext[4]);
        mix_columns(&plaintext[4]);
        add_round_key(&plaintext[4],expendedkey[i * 4,(i+1)*4 -1]);
    }
    substitute_bytes(&plaintext[4]);
    shift_rows(&plaintext[4]);
    add_round_key(&plaintext[4],expendedkey[40,43]);

}
struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

int main()
{
    unsigned char* plaintext[4];
    for (int i=0; i < 4; i++)
        plaintext[i] = new unsigned char[4];
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            plaintext[i][j] = 'b';
        }
    }
    unsigned char keyy[16] ;
    for(int k = 0 ; k < 16 ; k++)
        keyy[k] = 'a';
    encrypt(&plaintext[4],keyy);
    cout << "AES" << endl;

    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j<4 ;j++)
            cout<< hex(plaintext[i][j]);
    cout<<endl;

    return 0;
}
