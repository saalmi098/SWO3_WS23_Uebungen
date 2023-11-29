//       $Id: board.h 47848 2023-11-22 18:32:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/C/Tetris-Shader/intermediate/src/tetris/src/board.h $
// $Revision: 47848 $
//     $Date: 2023-11-22 19:32:07 +0100 (Mi., 22 Nov 2023) $
//   $Author: p20068 $
//   Creator: Michael Hava
//  Creation: October 24, 2023
// Copyright: (c) 2023 Michael Hava (michael.hava<AT>risc-software.at)
//            (c) 2023 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#pragma once

#include "./primitives.h"

// -------------------------------------------------------------------------------------------------

#define N_COLS 11
#define N_ROWS 22

// -------------------------------------------------------------------------------------------------

bool is_valid_position (position_type position);
