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

// template instantiation
template class General<int>;
template class General<std::string>;

// h
#pragma once

#include <string>
template <typename T>
class General
{
    T d_t;
  public:
    General(T&& t);
    void print();
};

// main

General<std::string> g{"123"};
