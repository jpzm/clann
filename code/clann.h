/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
 * Copyright (C) 2010 Joao Paulo de Souza Medeiros
 *
 * Author(s): João Paulo de Souza Medeiros <ignotus21@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef CLANN_H
#define CLANN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define CLANN_S_PRINTF      "%.1Lf"
#define CLANN_PRINTF        "%.10Lf"
#define CLANN_SCANF         "%Lf"
#define CLANN_POW           powl
#define CLANN_SQRT          sqrtl
#define CLANN_EXP           expl
#define CLANN_LOG           logl
#define CLANN_SIN           sinl
#define CLANN_COS           cosl
#define CLANN_ATAN2         atan2l
#define CLANN_FABS          fabsl

#define CLANN_VERBOSE       0
#define CLANN_DEBUG         1

#define FILE_HEADER_MLP     "MLP"
#define FILE_HEADER_SOM     "SOM"
#define FILE_HEADER_TLFN    "TLFN"
#define FILE_HEADER_NARX    "NARX"

#define CLANN_SWAP(a,b)     {(a) += (b); (b) = (a) - (b); (a) -= (b);}
#define CLANN_SCALE(v,a,b)  (2 * (((v) - (b)) / ((a) - (b))) - 1)

typedef unsigned char clann_byte_type;
typedef unsigned char clann_u8_type;
typedef unsigned short int clann_u16_type;
typedef long double clann_real_type;
typedef long int clann_int_type;
typedef unsigned long long int clann_uint_type;
typedef clann_uint_type clann_id_type;
typedef clann_uint_type clann_size_type;
typedef enum {false, true} clann_bool_type;
typedef enum {off, on} clann_key_type;

typedef struct clann_list
{
    void *info;
    struct clann_list *next;
} clann_list_type;


/**
 *
 */
void
clann_list_initialize(clann_list_type *l);

/**
 *
 */
void
clann_list_finalize(clann_list_type *l);

/**
 *
 */
clann_size_type
clann_list_size(clann_list_type *l);

/**
 *
 */
clann_bool_type
clann_list_insert(clann_list_type **l, void *i);

/**
 *
 */
clann_bool_type
clann_list_remove(clann_list_type **l, void *i);

/**
 *
 */
inline void
clann_shuffle(unsigned int *list,
              unsigned int length);

/**
 *
 */
inline void
clann_initialize(void);

/**
 *
 */
inline clann_real_type
clann_nrand(void);

/**
 *
 */
inline clann_real_type
clann_rand(const clann_real_type min,
           const clann_real_type max);

/**
 *
 */
long int
clann_randint(const clann_int_type min,
              const clann_int_type max);

/**
 *
 */
inline clann_real_type
clann_factorial(const clann_uint_type v);

/**
 *
 */
inline clann_real_type
clann_binomial(const clann_uint_type n,
               const clann_uint_type k);

/**
 *
 */
inline clann_uint_type
clann_nextpow2(clann_uint_type n);

#endif
