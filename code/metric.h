/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
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

#ifndef METRIC_H
#define METRIC_H

#include <math.h>
#include "clann.h"
#include "matrix.h"
#include <limits.h>


/**
 * Normalize
 */
inline clann_real_type
metric_scale(clann_real_type value,
             clann_real_type *from,
             clann_real_type *to);

/**
 *
 */
inline clann_real_type
metric_euclidean_pow2(const clann_real_type *a,
                      const clann_real_type *b,
                      const unsigned int length);

/**
 *
 */
inline clann_real_type
metric_euclidean(const clann_real_type *a,
                 const clann_real_type *b,
                 const unsigned int length);

/**
 *
 */
inline clann_real_type
metric_norm(const clann_real_type *a,
            const unsigned int length);

/**
 *
 */
inline clann_real_type
metric_dot_product(const clann_real_type *a,
                   const clann_real_type *b,
                   const unsigned int length);

/**
 *
 */
inline clann_real_type
metric_hausdorff(const struct matrix *a,
                 const struct matrix *b);

/**
 *
 */
inline clann_real_type
metric_hausdorff_symmetric(const struct matrix *a,
                           const struct matrix *b);

/**
 *
 */
inline unsigned int
metric_hausdorff_limit(const struct matrix *a,
                       const struct matrix *b,
                       clann_real_type limit);

/**
 *
 */
inline unsigned int
metric_hausdorff_limit_symmetric(const struct matrix *a,
                                 const struct matrix *b,
                                 clann_real_type limit);

/**
 *
 */
inline clann_real_type
metric_hausdorff_mean(const struct matrix *a,
                      const struct matrix *b);

/**
 *
 */
inline clann_real_type
metric_hausdorff_mean_symmetric(const struct matrix *a,
                                const struct matrix *b);

/**
 *
 */
inline unsigned int
metric_hausdorff_angle(const struct matrix *a,
                       const struct matrix *b,
                       clann_real_type limit);

/**
 *
 */
inline unsigned int
metric_hausdorff_angle_symmetric(const struct matrix *a,
                                 const struct matrix *b,
                                 clann_real_type limit);

#endif
