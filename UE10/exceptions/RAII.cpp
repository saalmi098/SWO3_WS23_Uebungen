//       $Id: main.cpp 45230 2021-12-19 09:04:31Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/CPP/RAII/src/main.cpp $
// $Revision: 45230 $
//     $Date: 2021-12-19 10:04:31 +0100 (So., 19 Dez 2021) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: January 17, 2017
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#include <iostream>
#include <string>

// -------------------------------------------------------------------------------------------------

class resource_manager {
   public:
      resource_manager () = delete;

      explicit resource_manager (std::string name)
         : m_allocated {!name.empty ()}
         , m_name      {std::move (name)} {

         if (m_allocated)
            std::cout << "acquired resource '" + m_name + "' from the system ...\n";
      }

      resource_manager (resource_manager const &) = delete;   // do not copy the managed resource

      resource_manager (resource_manager && tmp)
         : m_allocated {tmp.m_allocated}
         , m_name      {std::move (tmp.m_name)} {

         tmp.m_allocated = false;

         if (m_allocated)
            std::cout << "moved resource '" + m_name + "' to a new manager object ...\n";
      }

     ~resource_manager () {
         release ();
      }

      resource_manager & operator = (resource_manager const &) = delete;   // do not copy the managed resource

      resource_manager & operator = (resource_manager && tmp) noexcept {
         if (&tmp != this) {
            release ();

            m_allocated = tmp.m_allocated;
            m_name      = std::move (tmp.m_name);

            tmp.m_allocated = false;

            if (m_allocated)
               std::cout << "moved resource '" + m_name + "' to a new manager object ...\n";
         }

         return *this;
      }

      void release () {
         if (m_allocated) {
            std::cout << "released resource '" + m_name + "' (i.e., handed it back to the system) ...\n";

            m_allocated = false;   //
            m_name      = "";      // m_name.clear ()
         }
      }

      void use () {
         if (m_allocated)
            std::cout << "use resource '" + m_name + "' ...\n";
      }

   private:
      bool        m_allocated {false};   //
      std::string m_name      {};        // the managed resource
};

// -------------------------------------------------------------------------------------------------

resource_manager get_resource () {
   resource_manager r {"X"};

   r.use ();

   return r;
}

int main () {
   resource_manager r1 {"A"};
   resource_manager r2 {"B"};
   resource_manager r3 {std::move (r2)};

   r1.use ();

   r1 = std::move (r3);

   r1.use ();

   r1 = get_resource ();

   r1.use ();
}

/*
acquired resource 'A' from the system ...
acquired resource 'B' from the system ...
moved resource 'B' to a new manager object ...
use resource 'A' ...
released resource 'A' (i.e., handed it back to the system) ...
moved resource 'B' to a new manager object ...
use resource 'B' ...
acquired resource 'X' from the system ...
use resource 'X' ...
moved resource 'X' to a new manager object ...
released resource 'B' (i.e., handed it back to the system) ...
moved resource 'X' to a new manager object ...
use resource 'X' ...
released resource 'X' (i.e., handed it back to the system) ...
*/
