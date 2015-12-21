/****************************
AES 128 bit - Author: Mohamed Essam Fathalla
******************************/

#include <iostream>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>

using namespace std;
//TO PRINT HEX
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
//
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
 unsigned char sboxforMulTo2[256] = {
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
	0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
	0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e,
	0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
	0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e,
	0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe,
	0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde,
	0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe,
	0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11, 0x17, 0x15, 0x0b, 0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05,
	0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31, 0x37, 0x35, 0x2b, 0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25,
	0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51, 0x57, 0x55, 0x4b, 0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45,
	0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71, 0x77, 0x75, 0x6b, 0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65,
	0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91, 0x97, 0x95, 0x8b, 0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85,
	0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1, 0xb7, 0xb5, 0xab, 0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5,
	0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1, 0xd7, 0xd5, 0xcb, 0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5,
	0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1, 0xf7, 0xf5, 0xeb, 0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5 };
 unsigned char Rcon1[32] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A,
    0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A,
    0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5, 0x91, 0x39,
 };
 unsigned char Rcon[] = { 0x01, 0x02 , 0x04 , 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };
  unsigned char Rcon3[255] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
  0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
  0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
  0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
  0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
  0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
  0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
  0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
  0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
  0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
  0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
  0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
  0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
  0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
  0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
  0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

unsigned long SubWord(unsigned long sub){
    unsigned char rot1[4];
    rot1[0] = ( (sub & 0xFF000000 )>> 24 ) ;
    rot1[1] = (( sub & 0x00FF0000) >> 16 ) ;
    rot1[2] = ( (sub & 0x0000FF00) >> 8 ) ;
    rot1[3] = ( sub &  0x000000FF  ) ;

    rot1[0] = sbox[rot1[0]];
    rot1[1] = sbox[rot1[1]];
    rot1[2] = sbox[rot1[2]];
    rot1[3] = sbox[rot1[3]];
	 return (rot1[0]<<24) | ( rot1[1] << 16 ) |( rot1[2] << 8)| (rot1[3]);

}
unsigned long  RotWord(unsigned long rot){
    unsigned char temp ,rot1[4];
    rot1[0] = ( (rot & 0xFF000000) >> 24 ) ;
    rot1[1] = ( (rot & 0x00FF0000) >> 16 ) ;
    rot1[2] = ( (rot & 0x0000FF00) >> 8 ) ;
    rot1[3] = ( (rot & 0xFF)  ) ;
    temp = rot1[0];
    rot1[0] = rot1[1];
    rot1[1] = rot1[2];
    rot1[2] = rot1[3];
    rot1[3] = temp;
    return ((rot1[0] <<24) | ( rot1[1] << 16 ) |( rot1[2] << 8)| (rot1[3]));

}


void keyExp(unsigned char* key,unsigned long* w){


    unsigned long temp;
    for (int i = 0; i < 4; i++){

		w[i] =(key[(4*i)]<<24)| ( key[(4*i)+1] << 16)|( key[(4*i)+2] << 8 )| (key[(4*i)+3] ) ;
    }
    for (int i = 4; i < 44; i++)
    {
        temp = w[i-1];
        if ((i % 4) == 0){
           // RotWord(temp);
           // SubWord(temp);
            //temp = temp ^ 0x00000001;//((Rcon[i/4])&0x000000FF);
			temp = SubWord(RotWord(temp)) ^( Rcon1[i/4]<<24);
        }
        w[i] = w[i - 4] ^ temp;
    }
}

//Main Blocks : 1. substit bytes .. 2. shift rows  .. 3. mix col .. 4. Add rounds keys
void substitute_bytes(unsigned char** S){
    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j < 4 ;j++)
            S[i][j] = sbox[S[i][j]];
}
void shift_rows(unsigned char** S){
	unsigned char Sdashh[4][4];
   for(int row = 1; row < 4;row++){
	for(int col = 0; col < 4;col++)
        {
            Sdashh[row][col] = S[row][(row+col)%4];
        }
	}
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			S[i][j] = Sdashh[i][j];
		}
	}

}
//
unsigned char Multiply(unsigned char x1, unsigned char coff){
	if(coff==0x02){
		if( (x1 & 0x80)==0x80){
			x1 = x1 << 1;
			x1 = x1 ^ 0x1B;
		}
		else{
			x1 = x1 << 1;
		}

	}else if(coff==0x03){
		if((x1 & 0x80)==0x80){
			unsigned char temp = x1;
			x1 = x1 <<1;
			x1 = x1 ^ 0x1B;
			x1 = x1 ^ temp;
		}else{
			x1 = (x1<<1) ^ (x1);
		}
	}
	return x1;
}
//
void mix_columns(unsigned char** S){
	unsigned char Sdash[4][4];
     for (int col = 0; col < 4; col++ ) {
       // for (int row = 0; row < 4; row++) {
            //S[(4*j) + i] = (0x02 * S[(4*j) + i]) ^ (0x03 * S[(4*(j+1)) + i]) ^ S[(4*(j+2)) + i]
             //^ S[(4*(j+3)) + i];
			//Sdash[0][col] = (Multiply( S[0][col],0x02) ) ^ (Multiply( S[1][col],0x03 )) ^ S[2][col] ^ S[3][col];
			//Sdash[1][col] = ( S[0][col] ) ^ (Multiply(  S[1][col],0x02 )) ^ (Multiply(  S[2][col],0x03)) ^ S[3][col];
			//Sdash[2][col] = ( S[0][col] ) ^ (S[1][col]) ^ (Multiply(S[2][col],0x02 )) ^ (Multiply(S[3][col],0x03));
             //Sdash[3][col] = (Multiply(  S[0][col],0x03 )) ^ ( S[1][col]) ^ S[2][col] ^ (Multiply( S[3][col],0x02));
			 Sdash[0][col] = (sboxforMulTo2[ S[0][col]] ) ^ (sboxforMulTo2[ S[1][col]])^S[1][col] ^ S[2][col] ^ S[3][col];
			Sdash[1][col] = ( S[0][col] ) ^ (sboxforMulTo2[S[1][col]]) ^ (sboxforMulTo2[S[2][col]])^ S[2][col] ^ S[3][col];
			Sdash[2][col] = ( S[0][col] ) ^ (S[1][col]) ^ (sboxforMulTo2[S[2][col]]) ^ (sboxforMulTo2[S[3][col]])^S[3][col];
             Sdash[3][col] = (sboxforMulTo2[S[0][col]])^ S[0][col] ^ ( S[1][col]) ^ S[2][col] ^ (sboxforMulTo2[ S[3][col]]);
       // }
    }
	 for (int i = 0; i < 4; i++)
	 {
		 for (int j = 0; j < 4; j++)
		 {
			 S[i][j] = Sdash[i][j];
		 }
	 }
}
void add_round_key(int round,unsigned char** S ,unsigned long* expendedkeyAtround){
    for(int col = 0 ; col < 4 ; col++){
        S[3][col] ^= ((expendedkeyAtround[(round*4)+col] & (0xFF))) ;
        S[2][col] ^= ((expendedkeyAtround[(round*4)+col] & 0x00FF00))>>8 ;
        S[1][col] ^= ((expendedkeyAtround[(round*4)+col] & 0x00FF0000))>>16;
        S[0][col] ^= ((expendedkeyAtround[(round*4)+col] & 0xFF000000))>>24 ;
    }

}
void encrypt(unsigned char** plaintext ,unsigned char* key){
    unsigned long expendedkey[44];
    keyExp(key,expendedkey);
    add_round_key(0,plaintext,expendedkey); //0-3
    for(int i = 1 ; i < 10;i++){
        substitute_bytes(plaintext);
        shift_rows(plaintext);
        mix_columns(plaintext);
       add_round_key(i,plaintext,expendedkey);//[i * 4,(i+1)*4 -1]
    }
    substitute_bytes(plaintext);
    shift_rows(plaintext);
   add_round_key(10,plaintext,expendedkey);//40-43
}


int main()
{
	unsigned char plaintexttt[16]  ;
	unsigned char keyy[16] ;
	int numOfenc =0,numOfCases=0;
	string inputPlainText ;
	string inputKey;
	cin>>numOfCases;
	cin>>inputPlainText;

	//sscanf(arrstr,"%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",&plaintexttt[0],&plaintexttt[1],&plaintexttt[2],&plaintexttt[3],&plaintexttt[4],&plaintexttt[5],&plaintexttt[6],&plaintexttt[7],&plaintexttt[8],&plaintexttt[9],&plaintexttt[10],&plaintexttt[11],&plaintexttt[12],&plaintexttt[13],&plaintexttt[14],&plaintexttt[15]);
	cin>>inputKey;
	cin>>numOfenc;
	for (int i = 0 , j = 0; i < 32; i+=2)
	{
		//stringstream converter(inputPlainText.substr(i,2));
		//converter>>hex>>(unsigned char)plaintexttt[j];
		plaintexttt[j] = (unsigned char) strtoul(inputPlainText.substr(i,2).c_str(),NULL,16);
		keyy[j] = (unsigned char) strtoul(inputKey.substr(i,2).c_str(),nullptr,16);

		if(j==15)
			break;
		j++;
	}

	unsigned char* plaintextt[4];
    for (int i=0; i < 4; i++){
        plaintextt[i] = new unsigned char[4];
	}

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
			plaintextt[i][j] =plaintexttt[j*4 + i];
        }
    }
	double tStart = 0,tEnd = 0 ;
	 tStart = clock();
	 for(int i = 0 ; i < numOfenc; i++)
		encrypt(plaintextt,keyy);
	 tEnd = clock();
	double EndTime = (tEnd - tStart)*1000.0/ CLOCKS_PER_SEC;

    for(int i = 0 ; i < 4;i++)
        for(int j = 0 ; j<4 ;j++)
			//cout<<hex(plaintextt[j][i])<<endl;
				if((plaintextt[j][i] & 0xFF)>> 4 | (plaintextt[j][i] & 0xFF)>> 5 | (plaintextt[j][i] & 0xFF)>> 6 | (plaintextt[j][i] & 0xFF)>> 7  )
					printf("%x",plaintextt[j][i]);
				else
					printf("0%x",plaintextt[j][i]);

	cout<<endl<<"Time taken: "<<EndTime / numOfenc <<" ms\n";
	 system("pause");
    return 0;
}
