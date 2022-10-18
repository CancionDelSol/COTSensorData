#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdio.h"
#line 2 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
#line 33 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;


typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 34 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
#line 45 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
typedef struct divstruct
{
    int quot;
    int rem;
} div_t;

typedef struct ldivstruct
{
    long quot;
    long rem;
} ldiv_t;

typedef struct uldivstruct
{
    unsigned long quot;
    unsigned long rem;
} uldiv_t;
#line 81 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
int abs( int num );
#line 94 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
float atof( char * str );
#line 107 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
int atoi( char * str );
#line 120 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
long atol( char * str );
#line 141 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
div_t div( int number, int denom );
#line 159 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
ldiv_t ldiv( long number, long denom );
#line 177 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
uldiv_t uldiv( unsigned long number, unsigned long denom );
#line 190 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
long labs( long num );
#line 201 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
long max( long num1, long num2 );
#line 212 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
long min( long num1, long num2 );
#line 224 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
int rand();
#line 241 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
void srand( unsigned seed );
#line 251 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdlib.h"
int xtoi( char * str );
#line 3 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
#line 32 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 33 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdbool.h"



typedef char _Bool;
#line 34 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
#line 56 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short islower( char character );
#line 65 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isupper( char character );
#line 74 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isalpha( char character );
#line 83 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short iscntrl( char character );
#line 92 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isdigit( char character );
#line 102 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isalnum( char character );
#line 111 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isspace( char character );
#line 120 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short ispunct( char character );
#line 129 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isgraph( char character );
#line 138 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
unsigned short isxdigit( char character );
#line 147 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
char tolower( char character );
#line 156 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/ctype.h"
char toupper( char character );
#line 4 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
#line 33 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 34 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
#line 65 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double fabs( double num );
#line 79 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double floor( double num );
#line 92 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double ceil( double num );
#line 109 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double frexp( double num, int16_t * exp_ptr );
#line 124 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double ldexp( double num, int16_t new_exp );
#line 139 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double modf( double num, double * int_ptr );
#line 151 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double sqrt( double num );
#line 164 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double atan( double num );
#line 177 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double asin( double num );
#line 190 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double acos( double num );
#line 205 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double atan2( double y, double  x );
#line 216 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double sin( double num );
#line 227 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double cos( double num );
#line 238 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double tan( double num );
#line 251 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double exp( double pow );
#line 264 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double log( double num );
#line 277 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double log10( double num );
#line 292 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double pow( double num, double pow );
#line 305 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double sinh( double num );
#line 317 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double cosh( double num );
#line 328 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/math.h"
double tanh( double num );
#line 5 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/time.h"



struct tm
{
    unsigned long tm_sec;
    unsigned long tm_min;
    unsigned long tm_hour;
    unsigned long tm_mday;
    unsigned long tm_mon;
    unsigned long tm_year;
    unsigned long tm_wday;
    unsigned long tm_yday;
    unsigned long tm_isdst;
};









typedef unsigned long size_t;


typedef unsigned long clock_t;
typedef unsigned long time_t;
#line 6 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/DES.c"


const int BUFFER_SIZE = 64;
const int BITTEDNESS = 64;
char decrypted_buffer[BUFFER_SIZE] = { 0 };
char encrypted_buffer[BUFFER_SIZE] = { 0 };
char input[BUFFER_SIZE * 2] = { 0 };
char bits[BUFFER_SIZE * 2] = { 0 };

int IP[] =
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int E[] =
{
    32,  1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

int P[] =
{
    16,  7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

int FP[] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

int S1[4][16] =
{
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
        0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
        4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

int S2[4][16] =
{
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

int S3[4][16] =
{
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

int S4[4][16] =
{
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

int S5[4][16] =
{
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

int S6[4][16] =
{
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

int S7[4][16]=
{
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

int S8[4][16]=
{
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

int PC1[] =
{
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

int PC2[] =
{
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int LEFT[17][32], RIGHT[17][32];
int IPtext[64];
int EXPtext[48];
int XORtext[48];
int X[8][6];
int X2[32];
int R[32];
int key56bit[56];
int key48bit[17][48];
int CIPHER[64];
int ENCRYPTED[64];

void expansion_function(int pos, int text)
{
    for (int i = 0; i < 48; i++)
    {
        if (E[i] == pos + 1) {
            EXPtext[i] = text;
        }
    }
}

int initialPermutation(int pos, int text)
{
    int i;
    for (i = 0; i < 64; i++)
    {
        if (IP[i] == pos + 1) {
            break;
        }
    }
    IPtext[i] = text;
    return 0;
}

int F1(int i)
{
    int r, c, b[6];

    for (int j = 0; j < 6; j++) {
        b[j] = X[i][j];
    }

    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];

    if (i == 0) {
        return S1[r][c];
    }
    else if (i == 1) {
        return S2[r][c];
    }
    else if (i == 2) {
        return S3[r][c];
    }
    else if (i == 3) {
        return S4[r][c];
    }
    else if (i == 4) {
        return S5[r][c];
    }
    else if (i == 5) {
        return S6[r][c];
    }
    else if (i == 6) {
        return S7[r][c];
    }
    else if (i == 7) {
        return S8[r][c];
    }
}

int XOR(int a, int b) {
    return (a ^ b);
}

void ToBits(int value)
{
    int k, j, m;
    static int i;

    if (i % 32 == 0) {
        i = 0;
    }

    for (j = 3; j >= 0; j--)
    {
        m = 1 << j;
        k = value & m;
        if (k==0) {
            X2[3 - j + i] = '0' - 48;
        }
        else {
            X2[3 - j + i] = '1' - 48;
        }
    }

    i = i + 4;
}

void SBox(int XORtext[])
{
    int k = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++) {
            X[i][j] = XORtext[k++];
        }
    }

    int value;
    for (int i = 0; i < 8; i++)
    {
        value = F1(i);
        ToBits(value);
    }
}

void PBox(int pos, int text)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if (P[i] == pos + 1) {
            break;
        }
    }
    R[i] = text;
}

void cipher(int Round, int mode)
{
    for (int i = 0; i < 32; i++) {
        expansion_function(i, RIGHT[Round - 1][i]);
    }

    for (int i = 0; i < 48; i++)
    {
        if (mode == 0) {
            XORtext[i] = XOR(EXPtext[i], key48bit[Round][i]);
        }
        else {
            XORtext[i] = XOR(EXPtext[i], key48bit[17 - Round][i]);
        }
    }

    SBox(XORtext);

    for (int i = 0; i < 32; i++) {
        PBox(i, X2[i]);
    }

    for (int i = 0; i < 32; i++) {
        RIGHT[Round][i] = XOR(LEFT[Round - 1][i], R[i]);
    }
}

void finalPermutation(int pos, int text)
{
    int i;
    for (i = 0; i < 64; i++)
    {
        if (FP[i] == pos + 1) {
            break;
        }
    }
    ENCRYPTED[i] = text;
}

void convertToBinary(int n)
{
    int k, m;
    for (int i = 7; i >= 0; i--)
    {
        m = 1 << i;
        k = n & m;

        if (k == 0) {


        }
        else {


        }
    }
}

int convertCharToBit(long int n)
{
    char ch;
    int i = n * 8;

    int index = 0;
    while (i)
    {
        ch = input[index];
        if (ch == 0x0) {
            break;
        }
        i--;
        convertToBinary(ch);
    }
}

void Encryption(long int plain[])
{
    for (int i = 0; i < 64; i++) {
        initialPermutation(i, plain[i]);
    }

    for (int i = 0; i < 32; i++) {
        LEFT[0][i] = IPtext[i];
    }

    for (int i = 32; i < 64; i++) {
        RIGHT[0][i - 32] = IPtext[i];
    }

    for (int k = 1; k < 17; k++)
    {
        cipher(k, 0);

        for (int i = 0; i < 32; i++)
            LEFT[k][i] = RIGHT[k - 1][i];

    }

    for (int i = 0; i < 64; i++)
    {
        if (i < 32) {
            CIPHER[i] = RIGHT[16][i];
        }
        else {
            CIPHER[i] = LEFT[16][i - 32];
        }
        finalPermutation(i, CIPHER[i]);
    }

    for (int i = 0; i < 64; i++) {




        encrypted_buffer[i] = ENCRYPTED[i];
    }
}

void Decryption(long int plain[])
{
    for (int i = 0; i < 64; i++) {
        initialPermutation(i, plain[i]);
    }

    for (int i = 0; i < 32; i++) {
        LEFT[0][i] = IPtext[i];
    }

    for (int i = 32; i < 64; i++) {
        RIGHT[0][i - 32] = IPtext[i];
    }

    for (int k = 1; k < 17; k++)
    {
        cipher(k, 1);

        for (int i = 0; i < 32; i++) {
            LEFT[k][i] = RIGHT[k - 1][i];
        }
    }

    for (int i = 0; i < 64; i++)
    {
        if (i < 32) {
            CIPHER[i] = RIGHT[16][i];
        } else {
            CIPHER[i] = LEFT[16][i - 32];
        }
        finalPermutation(i, CIPHER[i]);
    }

    for (int i = 0; i < 64; i++) {




        decrypted_buffer[i] = ENCRYPTED[i];
    }
}

void convertToBits(int ch[], int index)
{
    int value = 0;
    for (int i = 7; i >= 0; i--) {
        value += (int)pow(2, i) * ch[7 - i];
    }

    bits[index] = value;
}

int bittochar()
{
    for (int i = 0; i < 64; i = i + 8) {
        convertToBits(&ENCRYPTED[i], i);
    }
}

void key56to48(int round, int pos, int text)
{
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC2[i] == pos + 1) {
            break;
        }
    }
    key48bit[round][i] = text;
}

int key64to56(int pos, int text)
{
    int i;
    for (i = 0; i < 56; i++)
    {
        if (PC1[i] == pos + 1) {
            break;
        }
    }
    key56bit[i] = text;
}

void key64to48(unsigned int key[])
{
    int k, backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];

    for (int i = 0; i < 64; i++) {
        key64to56(i, key[i]);
    }

    for (int i = 0; i < 56; i++)
    {
        if (i < 28) {
            C[0][i] = key56bit[i];
        }
        else {
            D[0][i - 28] = key56bit[i];
        }
    }

    for (int x = 1; x < 17; x++)
    {
        int shift = SHIFTS[x - 1];

        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = C[x - 1][i];
        }

        for (int i = 0; i < (28 - shift); i++) {

            C[x][i] = C[x - 1][i + shift];
        }

        k = 0;

        for (int i = 28 - shift; i < 28; i++) {

            C[x][i] = backup[x - 1][k++];
        }

        for (int i = 0; i < shift; i++) {

            backup[x - 1][i] = D[x - 1][i];
        }




        for (int i = 0; i < (28 - shift); i++) {
            D[x][i] = D[x - 1][i + shift];
        }

        k = 0;



        for (int i = 28 - shift; i < 28; i++) {
            D[x][i] = backup[x - 1][k++];
        }
    }

    for (int j = 0; j < 17; j++)
    {
        for (int i = 0; i < 28; i++) {
            CD[j][i] = C[j][i];
        }

        for (int i = 28; i < 56; i++) {

            CD[j][i] = D[j][i - 28];
        }
    }

    for (int j = 1; j < 17; j++)
    {
        for (int i = 0; i < 56; i++) {
            key56to48(j, i, CD[j][i]);
        }
    }
}

void decrypt(long int n)
{



    long int plain[BUFFER_SIZE * BITTEDNESS];

    char ch;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        ch = encrypted_buffer[i];
        plain[i] = ch - 48;
    }

    for (int i = 0; i < n; i++)
    {
        Decryption(plain + i * 64);
        bittochar();
    }
}

void encrypt(long int n)
{


    long int plain[BUFFER_SIZE * BITTEDNESS];
    int i = -1;
    char ch;

    while (bits[i + 1] != 0x0)
    {
        ch = bits[i + 1];
        plain[++i] = ch - 48;
    }

    for (int i = 0; i < n; i++) {
        Encryption(plain + 64 * i);
    }
}



const char key_source[BUFFER_SIZE] = { 0 };
void create16Keys()
{


    unsigned int key[BITTEDNESS];
    int i = 0, ch;

    while (              i < BUFFER_SIZE)
    {

        ch = key_source[i];
        key[i++] = ch - 48;
    }

    key64to48(key);
}


long int findInputSize()
{
    int length = -1;
    _Bool  done =  0 ;
    do {
        done = input[++length] == 0x00;
    } while (!done);
    return length;
}
