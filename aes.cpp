#include <iostream>
#include <iomanip>

//for our standard Nb = 4
const unsigned int Nb = 4;

//num rounds and key size
unsigned int Nr = 10;
unsigned int Nk = 4;


//lookup table for sbox
unsigned char box[256] =
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

//lookup table for inverse sbox
const unsigned char invbox[256] =
{ 
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, 
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, 
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, 
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, 
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, 
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, 
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, 
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, 
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, 
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, 
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, 
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, 
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, 
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, 
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  
};

//rcon lookup table
unsigned char rcon[256] = {
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
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};


//helper function I made to print every bit in a byte
void bitcheck(unsigned char test){
    for (int i = 7; i >=0 ; i--){
        std::cout << ((test >> i) & 0x01);
    }
    std::cout << std::endl;
}

//helper function for checking hex value of bytes
void bigcheck(unsigned char* test, int len){
    for(int i = 0; i < len; i++){
        std::cout << std::hex << static_cast<unsigned int>(test[i]) << " ";
    }
    std::cout << std::endl;
}

//helper funtion to print out a state in proper format
void statecheck(unsigned char state[4][Nb]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << std::hex << static_cast<unsigned int>(state[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

//print function for states, takes in a phrase arg and round number
void print(unsigned char state[4][Nb], const char* phrase, int r){

    std::cout  << "round[" << std::setw(2) << std::setfill(' ') << std::dec << r << "]" << phrase;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(state[j][i]);
        }
    }

    std::cout << std::endl;
}

//print function for char arrays, takes a length, phrase and round number arg
void printline(unsigned char* test, int len, const char* phrase, int r){
    std::cout  << "round[" << std::setw(2)  << std::setfill(' ') << std::dec << r << "]" << phrase;
    for(int i = 0; i < len; i++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(test[i]);
    }
    std::cout << std::endl;
}

//add two finite fields
unsigned char ffadd(unsigned char a, unsigned char b){
    return a ^ b;
}

//muiltiply a finit field by 1
unsigned char xtime(unsigned char x){
    return (x << 1) ^ (x & 0x80 ? 0x1b : 0);
}

//multiply two finite fields using method demonstrated in class
unsigned char ffmultiply(unsigned char a, unsigned char b){
    unsigned char sum = 0;
    
    while(a){
        if ((a & 0x01) == 1){
            sum ^= b;
        }

        b = xtime(b);
        a >>=1;
    }
    return sum;
}

//sub all bytes in a word with appropriate sbox values
void subWord(unsigned char* x){
    for(int i = 0; i < 4; i++){
        x[i] = box[x[i]];
    }
}

//cyclic permutation of a word
void rotWord(unsigned char* x){
    //make temp var
    unsigned char tmp = x[0];
    for (int i = 0; i < 4; i++){
        if(i == 3){
            //check to prevent indexing out of bounds
            x[i] = tmp;
        }
        else{
            x[i] = x[i+1];
        }
    }
}

//key expansion function based on given psuedo code
void KeyExpansion(const unsigned char* key, unsigned char* w){
    unsigned char temp[4];

    unsigned int i = 0;
    
    //first key section is just key
    while(i < 4 * Nk){
        w[i * 4] = key[i * 4];
        w[i * 4 + 1] = key[i * 4 + 1];
        w[i * 4 + 2] = key[i * 4 + 2];
        w[i * 4 + 3] = key[i * 4 + 3];
        i++;
    }

    i = Nk;

    while(i < Nb * (Nr+1)){
        for (int j = 0; j < 4; j++){
            //get previous 4byte section of w
            temp[j] = w[(i-1) * 4 + j];
        }

        if (i % Nk == 0){
            //perform rotation and sbox substitution 
            rotWord(temp);
            subWord(temp);

            //xor with rcon value
            temp[0] = temp[0] ^ rcon[i/Nk];
        }
        else if (Nk > 6 && i % Nk == 4){
            //conditional for larger key values
            subWord(temp);
        }

        //fill key secdule value
        w[i * 4 + 0] = w[(i - Nk) * 4 + 0] ^ temp[0];
        w[i * 4 + 1] = w[(i - Nk) * 4 + 1] ^ temp[1];
        w[i * 4 + 2] = w[(i - Nk) * 4 + 2] ^ temp[2];
        w[i * 4 + 3] = w[(i - Nk) * 4 + 3] ^ temp[3];

        i++;
    }
}

//substitute each byte in state with appropriate sbox value
void subBytes(unsigned char state[4][Nb]){
    for (unsigned int i = 0; i < 4; i++){
        for (unsigned int j = 0; j < Nb; j++){
            state[i][j] = box[state[i][j]];
        }
    }
}

//perform incremental cyclic permutation on state
void shiftRows(unsigned char state[4][Nb]){
    
    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < i; j++){
            //above loop runs the 4byte word loop incrementally based on postion in state
            unsigned char tmpch = state[i][0];
            for (int k = 0; k < 4; k++){
                if(k == 3){
                    state[i][k] = tmpch;
                }
                else{
                    state[i][k] = state[i][k + 1];
                }
            }

        }
    }

}

//mix columns based on example in class and pseudo code from the homework
void MixColumns(unsigned char state[4][Nb]){
    
    //use temp var to hold new state
    unsigned char tmp[4][Nb];
    for (unsigned int i = 0; i < Nb; i++){
        tmp[0][i] = (xtime(state[0][i]) ^ (xtime(state[1][i]) ^ state[1][i]) ^ state[2][i] ^ state[3][i]);
        tmp[1][i] = (state[0][i] ^ xtime(state[1][i]) ^ (xtime(state[2][i]) ^ state[2][i]) ^ state[3][i]);
        tmp[2][i] = (state[0][i] ^ state[1][i] ^ xtime(state[2][i]) ^ (xtime(state[3][i]) ^ state[3][i]));
        tmp[3][i] = ((xtime(state[0][i]) ^ state[0][i]) ^ state[1][i] ^ state[2][i] ^ xtime(state[3][i]));
    }

    //reassign values to state from tmp
    for (unsigned int i = 0; i < Nb; i++){
        for(unsigned int j = 0; j < 4; j++){
            state[i][j] = tmp[i][j];
        }
    }

}

//xor each state value with the appropraite round key value
void addRoundKey(unsigned char state[0][Nb], unsigned char* w){
    for (unsigned int i = 0; i < Nb; i++){
        for (unsigned int j = 0; j < 4; j++){
            state[j][i] ^= w[i * 4 + j];
        }
    }
}

//inverse of subBytes, retrieve appropriate inverse sbox value for each value in the state
void InvSubBytes(unsigned char state[4][Nb]){
    for (unsigned int i = 0; i < 4; i++){
        for (unsigned int j = 0; j < Nb; j++){
            state[i][j] = invbox[state[i][j]];
        }
    }
}

//inverse of shift rows, same shift method but reversed
void InvShiftRows(unsigned char state[4][Nb]){
    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < i; j++){
            
            unsigned char tmpch = state[i][3];
            for (int k = 3; k >= 0; k--){
            
                if(k == 0){
                    state[i][k] = tmpch;
                }
                else{
                    state[i][k] = state[i][k - 1];
                    
                }
            }

        }
    }
}


//Inverse mix columns, uses ffmultiply function and hard coded values given in the spec
void InvMixColumns(unsigned char state[4][Nb]) {
    unsigned char tmp[4][Nb];

    for(unsigned int i = 0; i < Nb; i++){
        tmp[0][i] = (ffmultiply(0x0e, state[0][i]) ^ ffmultiply(0x0b, state[1][i]) ^ ffmultiply(0x0d, state[2][i]) ^ ffmultiply(0x09, state[3][i]));
        tmp[1][i] = (ffmultiply(0x09, state[0][i]) ^ ffmultiply(0x0e, state[1][i]) ^ ffmultiply(0x0b, state[2][i]) ^ ffmultiply(0x0d, state[3][i]));
        tmp[2][i] = (ffmultiply(0x0d, state[0][i]) ^ ffmultiply(0x09, state[1][i]) ^ ffmultiply(0x0e, state[2][i]) ^ ffmultiply(0x0b, state[3][i]));
        tmp[3][i] = (ffmultiply(0x0b, state[0][i]) ^ ffmultiply(0x0d, state[1][i]) ^ ffmultiply(0x09, state[2][i]) ^ ffmultiply(0x0e, state[3][i]));
    }

    //retrieve new state from tmp
    for (unsigned int i = 0; i < Nb; i++){
        for(unsigned int j = 0; j < 4; j++){
            state[i][j] = tmp[i][j];
        }
    }
}


//main ciper function, based on pseudo code in spec
void Cipher(unsigned char in[4*Nb], unsigned char out[4*Nb], unsigned char* w){
    unsigned char state[4][Nb];
    
    //fill state from input
    for(unsigned int i = 0; i < Nb; i++){
        for (unsigned int j = 0; j < 4; j++){
            state[j][i] = in[i * 4 + j];
        }
    }

    printline(in, 16, ".input     ", 0);
    printline(w, 16, ".k_sch     ", 0);

    //add initial roundkey
    addRoundKey(state, w);


    // for round = 1 step 1 to Nr-1
    for (unsigned int i = 1; i < Nr; i++){
        print(state, ".start     ", i);
        subBytes(state);
        print(state, ".s_box     ", i);
        shiftRows(state);
        print(state,".s_row     ", i);
        MixColumns(state);
        print(state,".m_col     ",i);

        addRoundKey(state, w + (i * 4 * Nb));
        printline(w + (i * 4 * Nb), 16, ".k_sch     ", i);
    }


    //perform final round
    print(state, ".start     ", Nr);

    subBytes(state);
    print(state, ".s_box     ", Nr);
    shiftRows(state);
    print(state,".s_row     ", Nr);

    addRoundKey(state, w + (Nr * 4 * Nb));
    printline(w + (Nr * 4 * Nb), 16, ".k_sch     ", Nr);

    
    //retrieve output from state
    for(unsigned int i = 0; i < Nb; i++){
        for (unsigned int j = 0; j < 4; j++){
            out[i * 4 + j] = state[j][i];
        }
    }

    printline(out, 16, ".output    ", Nr);


}

//inverse ciper, based upon given pseudo code in spec
//mostly the same as cipher but in reverse order
void InvCipher(unsigned char in[4*Nb], unsigned char out[4*Nb], unsigned char* w){
    unsigned char state[4][Nb];
    
    //fill state form input
    for(unsigned int i = 0; i < Nb; i++){
        for (unsigned int j = 0; j < 4; j++){
            state[j][i] = in[i * 4 + j];
        }
    }

    printline(in, 16, ".iinput    ", 0);
    printline(w + (Nr * 4 * Nb), 16, ".ik_sch    ", 0);

    //start from the end of the key schedule
    addRoundKey(state, w + (Nr * 4 * Nb));

    //decrement from Nr to 1
    for (unsigned int i = Nr-1; i > 0; i--){
        print(state, ".istart    ", Nr - i);

        InvShiftRows(state);
        print(state,".is_row    ", Nr - i);

        InvSubBytes(state);
        print(state, ".is_box    ", Nr - i);

        addRoundKey(state, w + (i * 4 * Nb));
        printline(w + (i * 4 * Nb), 16, ".ik_sch    ", Nr - i);

        print(state, ".ik_add    ", Nr - i);

        InvMixColumns(state);
        //print(state, ".im_col    ", Nr - i);

    }

    print(state, ".istart    ", Nr);

    //perform final shift
    InvShiftRows(state);
    print(state,".is_row    ", Nr);

    InvSubBytes(state);
    print(state, ".is_box    ", Nr);

    addRoundKey(state, w);
    printline(w, 16, ".ik_sch    ", Nr);

    //retrieve decrypted values
    for(unsigned int i = 0; i < Nb; i++){
        for (unsigned int j = 0; j < 4; j++){
            out[i * 4 + j] = state[j][i];
        }
    }

    printline(out, 16, ".ioutput   ", Nr);


}


int main(){


    //generate inputs and print proper headings
    unsigned char input[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    unsigned char output[16];
    unsigned char decrypt[16];

    int klen = 4 * Nb * (Nr + 1);
    unsigned char w [klen];
    unsigned char Key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    std::cout << "C.1   AES-128 (Nk=4, Nr=10)\n\n";
    std::cout << "PLAINTEXT:          00112233445566778899aabbccddeeff\n";
    std::cout << "KEY:                000102030405060708090a0b0c0d0e0f\n\n";
    std::cout << "CIPHER (ENCRYPT):\n";

    //expand key
    KeyExpansion(Key, w);

    Cipher(input, output, w);
    std::cout << "\nINVERSE CIPHER (DECRYPT):\n";
    InvCipher(output, decrypt, w);

    //set key and round sizes
    Nr = 12;
    Nk = 6;

    klen = 4 * Nb * (Nr + 1);
    unsigned char w24[klen];

    //establishg new key
    unsigned char Key6[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

    //print pretty headers
    std::cout << "\nC.2   AES-192 (Nk=6, Nr=12)\n\n";
    std::cout << "PLAINTEXT:          00112233445566778899aabbccddeeff\n";
    std::cout << "KEY:                000102030405060708090a0b0c0d0e0f1011121314151617\n\n";
    std::cout << "CIPHER (ENCRYPT):\n";

    //expand key
    KeyExpansion(Key6, w24);

    Cipher(input, output, w24);
    std::cout << "\nINVERSE CIPHER (DECRYPT):\n";
    InvCipher(output, decrypt, w24);

    //set key and round sizes
    Nr = 14;
    Nk = 8;

    klen = 4 * Nb * (Nr + 1);
    unsigned char w32[klen];

    unsigned char Key8[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

    //print pretty headers
    std::cout << "\nC.3   AES-256 (Nk=8, Nr=14)\n\n";
    std::cout << "PLAINTEXT:          00112233445566778899aabbccddeeff\n";
    std::cout << "KEY:                000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f\n\n";
    std::cout << "CIPHER (ENCRYPT):\n";

    //expand key
    KeyExpansion(Key8, w32);

    Cipher(input, output, w32);
    
    std::cout << "\nINVERSE CIPHER (DECRYPT):\n";
    InvCipher(output, decrypt, w32);

    

}

