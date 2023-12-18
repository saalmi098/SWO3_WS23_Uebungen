//       $Id: main.cpp 47980 2023-12-18 10:20:51Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/Inhalt/CPP/exceptions/src/main.cpp $
// $Revision: 47980 $
//     $Date: 2023-12-18 11:20:51 +0100 (Mo., 18 Dez 2023) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: January 25, 2016
// Copyright: (c) 2021 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#include <format>
#include <iostream>
#include <source_location>
#include <stdexcept>
#include <string>

// -------------------------------------------------------------------------------------------------

std::string to_string (std::string const & msg, std::source_location const & src) noexcept {
   std::string file_name {src.file_name ()};

   if (std::size (file_name) > 25)
      file_name = std::format (
         "{}...{}",
         file_name.substr (0, 10), file_name.substr (std::size (file_name) - 15, 15)
      );

   return std::format (
      "'{}' '{}' {}:{} '{}'",
      msg, file_name, src.line (), src.column (), src.function_name ()
   );
}

// -------------------------------------------------------------------------------------------------

struct severe_error : std::runtime_error {
   explicit severe_error (std::string const & msg, std::source_location const & src = std::source_location::current ())
      : std::runtime_error {to_string (msg, src)} {
   }
};

// -------------------------------------------------------------------------------------------------

struct error {
   explicit error (std::string const & msg, std::source_location const & src = std::source_location::current ())
      : m_msg {msg}
      , m_src {src} {
   }

   std::string          m_msg;
   std::source_location m_src;
};

struct file_error : error {
   explicit file_error (std::string const & msg, std::source_location const & src = std::source_location::current ())
      : error {msg, src} {
   }
};

struct file_not_found_error : file_error {
   explicit file_not_found_error (std::string const & msg, std::source_location const & src = std::source_location::current ())
      : file_error {msg, src} {
   }
};

struct logic_error : error {
   explicit logic_error (std::string const & msg, std::source_location const & src = std::source_location::current ())
      : error {msg, src} {
   }
};

// -------------------------------------------------------------------------------------------------

void foo () {
    std::cout << "vor dem Fehler\n";

    //throw "ein Fehler ist passiert"; // ruft catch (char const * const p) auf
    //throw file_not_found_error {"./input.txt"};
    //throw severe_error {"division by 0"};
    //throw logic_error {"array not sorted"};

    std::cout << "nach dem Fehler\n";
}

int main () {
   std::cout << "vor dem try-catch-Block\n";

   try {
      std::cout << "vor foo\n";
      foo ();
      std::cout << "nach foo\n";

   } catch (file_not_found_error const & e) {
      std::cout << std::format (
         "Error:                File '{}' not found.\n"
         "Info from throw site: {}\n",
         e.m_msg, to_string (e.m_msg, e.m_src)
      );

   } catch (file_error const & e) {
      std::cout << std::format (
         "Error:                Some file error occurred.\n"
         "Info from throw site: {}\n",
         to_string (e.m_msg, e.m_src)
      );

   } catch (logic_error const & e) {
      std::cout << std::format (
         "Error:                Some logic error occurred.\n"
         "Info from throw site: {}\n",
         to_string (e.m_msg, e.m_src)
      );

   } catch (char const * const p) {
      std::cout << std::format ("Error: Some error '{}' caught.\n", p);

   } catch (int const i) {
      std::cout << std::format ("Error: Integer {} caught.\n", i);

   } catch (std::runtime_error const & e) {
      std::cout << "Error: " << e.what () << '\n';

   } catch (...) {
      std::cout << "Error: Unknown error caught.\n";
   }

   std::cout << "nach dem try-catch-Block\n";
}
