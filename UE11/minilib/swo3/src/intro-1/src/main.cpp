//       $Id: main.cpp 3367 2023-01-06 08:37:18Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/se/sw/swo3/trunk/Uebungen/minilib/intro-1/src/main.cpp $
// $Revision: 3367 $
//     $Date: 2023-01-06 09:37:18 +0100 (Fr., 06 Jän 2023) $
//   Creator: peter.kulczycki<AT>fh-hagenberg.at
//  Creation: June 1, 2018
//   $Author: p20068 $
// Copyright: (c) 2023 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg. It
//            is distributed under the Boost Software License, Version 1.0 (see
//            http://www.boost.org/LICENSE_1_0.txt).

#include <ml5/ml5.h>

using namespace ml5::literals;

#include <format>

template<typename T> class list_node final : public ml5::object {
private:
    template<typename> friend class list; // ermöglicht, dass list auf private Datenomponenten zugreifen darf (value, p_next)
    template<typename> friend class list_iterator;

    list_node(T v) : value{ v } {
    }

    T value{};
    list_node* p_next{ nullptr };
};

template<typename T> class list : public ml5::container<T> {
public:
    list() = default;

    ~list() {
        clear();
    }

    void add(T value) override {
        (m_p_root ? 
            find_last_node(m_p_root)->p_next // Zuweisungsziel, falls m_p_root vorhanden
            : m_p_root) // Zuweisungsziel, falls Liste leer
            = new list_node<T>{ value };
    }

    void clear() noexcept override {
        while (m_p_root) {
            auto p{ m_p_root }; // p ... list_node<T>*
            m_p_root = m_p_root->p_next;
            delete p;
        }
    }

    bool contains(T const& /*value*/) const noexcept override {
        return {}; // leere geschwungene Klammer = default-Konstruktion dieses Datentyps (bool = false, int = 0, ...)
    }
    
    void remove(T const& /*value*/) noexcept override {
    }
    
    std::size_t size() const noexcept override {
        return ml5::container<T>::size();
    }

    std::unique_ptr <ml5::iterator <T>> make_iterator() override {
        // unique_ptr ... wenn die Pointer-Var. zerstört wird, deleted er auch das Objekt, auf das er zeigt (RAII)
        return std::unique_ptr <ml5::iterator <T>> { new list_iterator<T>{ m_p_root } };
    }

private:
    list_node <T>* m_p_root{ nullptr };

    list_node<T>* find_last_node(list_node<T>* p) { // p = 1. Knoten von dem an gesucht wird
        while (p && p->p_next)
            p = p->p_next;
        
        return p;
    }
};

template<typename T> class list_iterator final : public ml5::iterator<T> {
public:
    list_iterator(list_node<T>* const p = nullptr) : m_p_node{ p } {

    }

    T& get_current() const override {
        if (is_at_end())
            throw std::out_of_range{ "cannot dereference end iterator" };

        return m_p_node->value;
    }
    
    bool is_at_end() const noexcept override {
        return !m_p_node;
    }
    
    void to_next() override {
        if (is_at_end())
            throw std::out_of_range{ "cannot dereference end iterator" };

        m_p_node = m_p_node->p_next;
    }

private:
    list_node<T>* m_p_node{ nullptr };
};

void checked_main () {
    list<ml5::string> l1;

    l1.add("Hansi"_v); // v ... "value" (ml5-value); "Hansi"_v = Literal vom Typ ml5-value
    l1.add("Susi"_v);
    l1.add("Karli"_v);

    for (ml5::string const& e : l1) {
        std::cout << e << ' ';
    }
    std::cout << "\n----------- \n";

    for (std::unique_ptr<ml5::iterator<ml5::string>> itor{ l1.make_iterator() }; itor->not_at_end(); itor->to_next()) {
        std::cout << itor->get_current() << ' ';
    }
    std::cout << "\n----------- \n";
}

int main () {
   // ml5::util:finally erstellt ein finally-Block mit einer Lambda-Expression
   // die Lambda wird am Ende der Programmausführung automatisch ausgeführt (im Destruktor)
   auto const finally {ml5::util::finally ([] {
      std::cout << '\n' << MI5_REGISTRY << '\n'; // Code der im Destruktor ausgeführt wird
   })};

   std::cout << std::format (
      "detected os:       {}\n"
      "detected compiler: {}\n"
      "MiniLib version:   {}\n\n",
   ml5::util::detected_os_as_string (), ml5::util::detected_compiler_as_string (), ml5::version);

   if (!ml5::util::show_console ())
      std::cout << std::format ("console error: {}\n", ml5::util::get_last_error_as_string ());

   try {
      checked_main ();

   } catch (std::exception const & x) {
      std::cerr << std::format ("Exception of type '{}' caught: '{}'\n", ml5::util::type_as_string (x), x.what ());

   } catch (...) {
      std::cerr << "Exception of unknown type caught\n";
   }
}
