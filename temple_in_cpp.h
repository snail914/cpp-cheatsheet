// cpp
#include "general.h"
#include <iostream>
#include <string>

template <typename T>
General<T>::General(T&& t)
  : d_t{t}
{
}

template <typename T>
void General<T>::print()
{
    std::cout << d_t << std::endl;
}


template <typename T>
void test() {
    std::cout << T() << std::endl;
}


// template instantiation
template class General<int>;
template class General<std::string>;

template void test<int>();
template void test<std::string>();

// h
#pragma once

template <typename T>
class General
{
    T d_t;
  public:
    General(T&& t);
    void print();
};

template <typename T>
void test();


// main

#include "general.h"
#include <string>

int main()
{
    General<std::string> g{"hello"};
    g.print();
    test<int>();
    test<std::string>();
}

