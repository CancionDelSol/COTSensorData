#line 1 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
#line 39 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
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
#line 40 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
#line 1 "ecdh.h"
#line 44 "ecdh.h"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/stdint.h"
#line 45 "ecdh.h"
#line 94 "ecdh.h"
int ecdh_generate_keys(uint8_t* public_key, uint8_t* private_key);


int ecdh_shared_secret(const uint8_t* private_key, const uint8_t* others_pub, uint8_t* output);



int ecdsa_sign(const uint8_t* private_key, uint8_t* hash, uint8_t* random_k, uint8_t* signature);
int ecdsa_verify(const uint8_t* public_key, uint8_t* hash, const uint8_t* signature);
#line 41 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
#line 58 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
#line 1 "C:/PROGRA~1/NECTOS~1/NECTOS~1/COMPIL~1/PIC32/mikroC/include/assert.h"
#line 59 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
#line 79 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
typedef uint32_t bitvec_t[ (( ( 163 + 3 ) + 31) / 32) ];
typedef bitvec_t gf2elem_t;
typedef bitvec_t scalar_t;
#line 104 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
const gf2elem_t polynomial = { 0x000000c9, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000008 };
const gf2elem_t coeff_b    = { 0x4a3205fd, 0x512f7874, 0x1481eb10, 0xb8c953ca, 0x0a601907, 0x00000002 };
const gf2elem_t base_x     = { 0xe8343e36, 0xd4994637, 0xa0991168, 0x86a2d57e, 0xf0eba162, 0x00000003 };
const gf2elem_t base_y     = { 0x797324f1, 0xb11c5c0c, 0xa2cdd545, 0x71a0094f, 0xd51fbc6c, 0x00000000 };
const scalar_t  base_order = { 0xa4234c33, 0x77e70c12, 0x000292fe, 0x00000000, 0x00000000, 0x00000004 };
#line 208 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static int bitvec_get_bit(const bitvec_t x, const uint32_t idx)
{
  return ((x[idx / 32U] >> (idx & 31U) & 1U));
}

static void bitvec_clr_bit(bitvec_t x, const uint32_t idx)
{
  x[idx / 32U] &= ~(1U << (idx & 31U));
}

static void bitvec_copy(bitvec_t x, const bitvec_t y)
{
  int i;
  for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    x[i] = y[i];
  }
}

static void bitvec_swap(bitvec_t x, bitvec_t y)
{
  bitvec_t tmp;
  bitvec_copy(tmp, x);
  bitvec_copy(x, y);
  bitvec_copy(y, tmp);
}



static int bitvec_equal(const bitvec_t x, const bitvec_t y)
{
  int i;
  for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    if (x[i] != y[i])
    {
      return 0;
    }
  }
  return 1;
}
#line 263 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static void bitvec_set_zero(bitvec_t x)
{
  int i;
  for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    x[i] = 0;
  }
}



static int bitvec_is_zero(const bitvec_t x)
{
  uint32_t i = 0;
  while (i <  (( ( 163 + 3 ) + 31) / 32) )
  {
    if (x[i] != 0)
    {
      break;
    }
    i += 1;
  }
  return (i ==  (( ( 163 + 3 ) + 31) / 32) );
}
#line 302 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static int bitvec_degree(const bitvec_t x)
{
  int i =  (( ( 163 + 3 ) + 31) / 32)  * 32;


  x +=  (( ( 163 + 3 ) + 31) / 32) ;


  while (    (i > 0)
          && (*(--x)) == 0)
  {
    i -= 32;
  }

  if (i != 0)
  {
    uint32_t u32mask = ((uint32_t)1 << 31);
    while (((*x) & u32mask) == 0)
    {
      u32mask >>= 1;
      i -= 1;
    }
  }
  return i;
}


static void bitvec_lshift(bitvec_t x, const bitvec_t y, int nbits)
{
  int nwords = (nbits / 32);


  int i,j;
  for (i = 0; i < nwords; ++i)
  {

    x[i] = 0;
  }
  j = 0;

  while (i <  (( ( 163 + 3 ) + 31) / 32) )
  {
    x[i] = y[j];
    i += 1;
    j += 1;
  }


  nbits &= 31;
  if (nbits != 0)
  {

    int i;
    for (i = ( (( ( 163 + 3 ) + 31) / 32)  - 1); i > 0; --i)
    {
      x[i]  = (x[i] << nbits) | (x[i - 1] >> (32 - nbits));
    }
    x[0] <<= nbits;
  }
}
#line 371 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static void gf2field_set_one(gf2elem_t x)
{

  x[0] = 1;

  int i;
  for (i = 1; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    x[i] = 0;
  }
}



static int gf2field_is_one(const gf2elem_t x)
{

  if (x[0] != 1)
  {
    return 0;
  }

  int i;
  for (i = 1; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    if (x[i] != 0)
    {
      break;
    }
  }
  return (i ==  (( ( 163 + 3 ) + 31) / 32) );
}
#line 425 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static void gf2field_add(gf2elem_t z, const gf2elem_t x, const gf2elem_t y)
{
  int i;
  for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
  {
    z[i] = (x[i] ^ y[i]);
  }
}


static void gf2field_inc(gf2elem_t x)
{
  x[0] ^= 1;
}



static void gf2field_mul(gf2elem_t z, const gf2elem_t x, const gf2elem_t y)
{
  int i;
  gf2elem_t tmp;
#line 450 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
  ((z != y) ? (void)0 : (1 ) ) ;

  bitvec_copy(tmp, x);


  if (bitvec_get_bit(y, 0) != 0)
  {
    bitvec_copy(z, x);
  }
  else
  {
    bitvec_set_zero(z);
  }


  for (i = 1; i <  163 ; ++i)
  {

    bitvec_lshift(tmp, tmp, 1);


    if (bitvec_get_bit(tmp,  163 ))
    {
      gf2field_add(tmp, tmp, polynomial);
    }
#line 483 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
    if (bitvec_get_bit(y, i))
    {
      gf2field_add(z, z, tmp);
    }
#line 493 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
  }
}


static void gf2field_inv(gf2elem_t z, const gf2elem_t x)
{
  gf2elem_t u, v, g, h;
  int i;

  bitvec_copy(u, x);
  bitvec_copy(v, polynomial);
  bitvec_set_zero(g);
  gf2field_set_one(z);

  while (!gf2field_is_one(u))
  {
    i = (bitvec_degree(u) - bitvec_degree(v));

    if (i < 0)
    {
      bitvec_swap(u, v);
      bitvec_swap(g, z);
      i = -i;
    }
#line 524 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
    bitvec_lshift(h, v, i);
    gf2field_add(u, u, h);
    bitvec_lshift(h, g, i);
    gf2field_add(z, z, h);
  }
}
#line 543 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static void gf2point_copy(gf2elem_t x1, gf2elem_t y1, const gf2elem_t x2, const gf2elem_t y2)
{
  bitvec_copy(x1, x2);
  bitvec_copy(y1, y2);
}

static void gf2point_set_zero(gf2elem_t x, gf2elem_t y)
{
  bitvec_set_zero(x);
  bitvec_set_zero(y);
}

static int gf2point_is_zero(const gf2elem_t x, const gf2elem_t y)
{
  return (    bitvec_is_zero(x)
           && bitvec_is_zero(y));
}


static void gf2point_double(gf2elem_t x, gf2elem_t y)
{

  if (bitvec_is_zero(x))
  {
    bitvec_set_zero(y);
  }
  else
  {
    gf2elem_t l;

    gf2field_inv(l, x);
    gf2field_mul(l, l, y);
    gf2field_add(l, l, x);
    gf2field_mul(y, x, x);
    gf2field_mul(x, l, l);

    gf2field_inc(l);

    gf2field_add(x, x, l);
    gf2field_mul(l, l, x);
    gf2field_add(y, y, l);
  }
}



static void gf2point_add(gf2elem_t x1, gf2elem_t y1, const gf2elem_t x2, const gf2elem_t y2)
{
  if (!gf2point_is_zero(x2, y2))
  {
    if (gf2point_is_zero(x1, y1))
    {
      gf2point_copy(x1, y1, x2, y2);
    }
    else
    {
      if (bitvec_equal(x1, x2))
      {
        if (bitvec_equal(y1, y2))
        {
          gf2point_double(x1, y1);
        }
        else
        {
          gf2point_set_zero(x1, y1);
        }
      }
      else
      {

        gf2elem_t a, b, c, d;

        gf2field_add(a, y1, y2);
        gf2field_add(b, x1, x2);
        gf2field_inv(c, b);
        gf2field_mul(c, c, a);
        gf2field_mul(d, c, c);
        gf2field_add(d, d, c);
        gf2field_add(d, d, b);

        gf2field_inc(d);

        gf2field_add(x1, x1, d);
        gf2field_mul(a, x1, c);
        gf2field_add(a, a, d);
        gf2field_add(y1, y1, a);
        bitvec_copy(x1, d);
      }
    }
  }
}





static void gf2point_mul(gf2elem_t x, gf2elem_t y, const scalar_t exp)
{
  gf2elem_t tmpx, tmpy;
  int i;
  int nbits = bitvec_degree(exp);

  gf2point_set_zero(tmpx, tmpy);

  for (i = (nbits - 1); i >= 0; --i)
  {
    gf2point_double(tmpx, tmpy);
    if (bitvec_get_bit(exp, i))
    {
      gf2point_add(tmpx, tmpy, x, y);
    }
  }
  gf2point_copy(x, y, tmpx, tmpy);
}
#line 691 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
static int gf2point_on_curve(const gf2elem_t x, const gf2elem_t y)
{
  gf2elem_t a, b;

  if (gf2point_is_zero(x, y))
  {
    return 1;
  }
  else
  {
    gf2field_mul(a, x, x);



    gf2field_mul(b, a, x);
    gf2field_add(a, a, b);

    gf2field_add(a, a, coeff_b);
    gf2field_mul(b, y, y);
    gf2field_add(a, a, b);
    gf2field_mul(b, x, y);

    return bitvec_equal(a, b);
  }
}
#line 727 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
int ecdh_generate_keys(uint8_t* public_key, uint8_t* private_key)
{

  gf2point_copy((uint32_t*)public_key, (uint32_t*)(public_key +  (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) ) ), base_x, base_y);


  if (bitvec_degree((uint32_t*)private_key) < ( 163  / 2))
  {
    return 0;
  }
  else
  {

    int nbits = bitvec_degree(base_order);
    int i;

    for (i = (nbits - 1); i < ( (( ( 163 + 3 ) + 31) / 32)  * 32); ++i)
    {
      bitvec_clr_bit((uint32_t*)private_key, i);
    }


    gf2point_mul((uint32_t*)public_key, (uint32_t*)(public_key +  (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) ) ), (uint32_t*)private_key);

    return 1;
  }
}



int ecdh_shared_secret(const uint8_t* private_key, const uint8_t* others_pub, uint8_t* output)
{

  if (    !gf2point_is_zero ((uint32_t*)others_pub, (uint32_t*)(others_pub +  (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) ) ))
       &&  gf2point_on_curve((uint32_t*)others_pub, (uint32_t*)(others_pub +  (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) ) )) )
  {

    unsigned int i;
    for (i = 0; i < ( (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) )  * 2); ++i)
    {
      output[i] = others_pub[i];
    }


    gf2point_mul((uint32_t*)output,(uint32_t*)(output +  (sizeof(uint32_t) * (( ( 163 + 3 ) + 31) / 32) ) ), (const uint32_t*)private_key);
#line 783 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
    return 1;
  }
  else
  {
    return 0;
  }
}



int ecdsa_sign(const uint8_t* private_key, uint8_t* hash, uint8_t* random_k, uint8_t* signature)
{
#line 804 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
  ((private_key != 0) ? (void)0 : (1 ) ) ;
  ((hash != 0) ? (void)0 : (1 ) ) ;
  ((random_k != 0) ? (void)0 : (1 ) ) ;
  ((signature != 0) ? (void)0 : (1 ) ) ;

  int success = 0;

  if (    (bitvec_degree((uint32_t*)private_key) >= ( 163  / 2))
       && !bitvec_is_zero((uint32_t*)random_k) )
  {
    gf2elem_t r, s, z, k;

    bitvec_set_zero(r);
    bitvec_set_zero(s);
    bitvec_copy(z, (uint32_t*)hash);


    int nbits = bitvec_degree(base_order);
    int i;
    for (i = (nbits - 1); i <  ( 163 + 3 ) ; ++i)
    {
      bitvec_clr_bit(z, i);
    }


    bitvec_copy(k, (uint32_t*)random_k);


    gf2point_copy(r, s, base_x, base_y);
    gf2point_mul(r, s, k);


    if (!bitvec_is_zero(r))
    {

      gf2field_inv(s, k);
      gf2field_mul(r, r, (uint32_t*)private_key);
      gf2field_add(r, r, z);

      nbits = bitvec_degree(r);
      for (i = (nbits - 1); i <  ( 163 + 3 ) ; ++i)
      {

        bitvec_clr_bit(r, i);
      }

      gf2field_mul(s, s, r);

      nbits = bitvec_degree(s);
      for (i = (nbits - 1); i <  ( 163 + 3 ) ; ++i)
      {

        bitvec_clr_bit(s, i);
      }

      if (!bitvec_is_zero(s))
      {
        bitvec_copy((uint32_t*)signature, r);
        bitvec_copy((uint32_t*)(signature +  24 ), s);
        success = 1;
      }
    }
  }
  return success;
}


int ecdsa_verify(const uint8_t* public_key, uint8_t* hash, const uint8_t* signature)
{
#line 883 "C:/Users/roger/Documents/MIKROE/Projects/SandboxLegacy/ecc.c"
  ((public_key != 0) ? (void)0 : (1 ) ) ;
  ((hash != 0) ? (void)0 : (1 ) ) ;
  ((signature != 0) ? (void)0 : (1 ) ) ;

  int success = 0;

  gf2elem_t r, s;
  bitvec_copy(r, (uint32_t*)(signature));
  bitvec_copy(s, (uint32_t*)(signature +  24 ));

  if (    !bitvec_is_zero(s)
       && !bitvec_is_zero(r))
  {
    gf2elem_t x1, y1, u1, u2, w, z;


    bitvec_copy(z, (uint32_t*)hash);
    uint32_t nbits = bitvec_degree(base_order);
    uint32_t i;
    for (i = (nbits - 1); i <  ( 163 + 3 ) ; ++i)
    {
      bitvec_clr_bit(z, i);
    }


    gf2field_inv(w, s);

    if (bitvec_get_bit(w,  163 ))
    {

      gf2field_add(w, w, polynomial);
    }


    gf2field_mul(u1, z, w);

    if (bitvec_get_bit(u1,  163 ))
    {

      gf2field_add(u1, u1, polynomial);
    }
    gf2field_mul(u2, r, w);

    if (bitvec_get_bit(u2,  163 ))
    {

      gf2field_add(u2, u2, polynomial);
    }


    bitvec_copy(x1, base_x);
    bitvec_copy(y1, base_y);
    gf2field_mul(u1, x1, y1);

    bitvec_copy(w, (uint32_t*)(public_key));
    bitvec_copy(z, (uint32_t*)(public_key +  24 ));
    gf2field_mul(u2, w, z);


    gf2point_add(x1, y1, w, z);
    if (bitvec_get_bit(x1,  163 ))
    {

      gf2field_add(x1, x1, polynomial);
    }

    success = bitvec_equal(r, x1);

    if (!success)
    {

      for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
      {

      }


      for (i = 0; i <  (( ( 163 + 3 ) + 31) / 32) ; ++i)
      {

      }

    }
  }
  else
  {

  }

  return success;
}
