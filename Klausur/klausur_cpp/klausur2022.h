#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cassert>

class person final {
public:
	person(unsigned long int ss, std::string fn, std::string ln)
		: ssnr{ ss }, first_name{ fn }, last_name{ ln } {
	}

	int const& get_ssnr() const {
		return ssnr;
	}

	std::string const& get_first_name() const {
		return first_name;
	}

	std::string const& get_last_name() const {
		return first_name;
	}

	void set_last_name(std::string const& ln) {
		last_name = ln;
	}

	friend std::ostream& operator << (std::ostream& lhs, person& rhs) {
		return lhs << rhs.first_name << " " << rhs.last_name << " (" << rhs.ssnr << ")";
	}

	friend bool operator == (person& lhs, person& rhs) {
		return lhs.ssnr == rhs.ssnr;
	}

	friend bool operator < (person& lhs, person& rhs) {
		std::string name1{ lhs.last_name + " " + lhs.first_name };
		std::string name2{ rhs.last_name + " " + rhs.first_name };
		return name1 < name2;
	}

	person(person& copy) = delete;
	person& operator = (person& rhs) = delete;

private:
	unsigned long int ssnr;
	std::string first_name;
	std::string last_name;
};

// =====================================================

class element {
};

class element_int : public element {
public:
	element_int(int data) : m_data{data} {}
private:
	int m_data;
};

class element_str : public element {
public:
	element_str(std::string data) : m_data{ data } {}
private:
	std::string m_data;
};

class element_vector final {
public:
	element_vector(int c) : m_capacity{ c } {
		assert(c > 0);
		m_elements = new element[m_capacity];
	}

	~element_vector() {
		delete[] m_elements;
	}

	void add(element const& e) {
		if (m_element_count >= m_capacity)
			throw std::range_error{ "vector full" };

		m_elements[m_element_count++] = e;
	}

	/*friend std::ostream& operator << (std::ostream& lhs, element_vector& v) {
		for (int i{ 0 }; i < v.m_element_count; i++) {
			lhs << v.m_elements[i] << " ";
		}
	}*/

private:
	int m_capacity{ 0 };
	int m_element_count{ 0 };
	element* m_elements;
};

// =====================================================

template <typename T> class vector {
public:
	vector(int c) : m_capacity{ c } {
		assert(c > 0);
		m_elements = new T[m_capacity];
	}

	~vector() {
		delete[] m_elements;
	}

	void add(T const& e) {
		if (m_element_count >= m_capacity)
			throw std::range_error{ "vector full" };

		m_elements[m_element_count++] = e;
	}

private:
	int m_capacity{ 0 };
	int m_element_count{ 0 };
	T* m_elements;
};