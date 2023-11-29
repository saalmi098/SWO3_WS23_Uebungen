//       $Id: tetrimino.c 47848 2023-11-22 18:32:07Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/C/Tetris-Shader/intermediate/src/tetris/src/tetrimino.c $
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

#include "./window.h"

// -------------------------------------------------------------------------------------------------

GLfloat normalize_blue (color_type const color) {
   return (GLfloat) (color & color_blue) / color_blue;
}

GLfloat normalize_green (color_type const color) {
   return (GLfloat) (color & color_green) / color_green;
}

GLfloat normalize_red (color_type const color) {
   return (GLfloat) (color & color_red) / color_red;
}
