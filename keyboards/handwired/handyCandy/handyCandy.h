/* Copyright 2020 Jack Lance
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00, k41, k01, k42, k02, k43, k03, k44, k04, k45, k05, k46, k06, k47, k07, k48, k08, \
     k10,  k51, k11, k52, k12, k53, k13, k54, k14, k55, k15,   k16,  k57, k17, k58, k18, \
      k20,   k21, k62, k22, k63, k23, k64, k24, k65, k25, k66,  k26, k67, k27, k68, k28, \
     k30,   k31,   k32,     k33,       k34,    k75,  k35,  k76, k36, k77, k37, k78, k38 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { KC_NO, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { KC_NO, k51, k52, k53, k54, k55, KC_NO, k57, k58 }, \
    { KC_NO, KC_NO, k62, k63, k64, k65, k66, k67, k68 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k75, k76, k77, k78 } \
}
