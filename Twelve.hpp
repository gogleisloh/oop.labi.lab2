#ifndef TWELVE
#define TWELVE
#include <stdlib.h>
#include <iostream>
class Twelve
{
public:
Twelve();
Twelve(const size_t & n, unsigned char * t);
Twelve(const std::initializer_list< unsigned char> &t);
Twelve(const std::string &t);
Twelve(const Twelve& other);
Twelve(Twelve&& other) noexcept;
virtual ~Twelve() noexcept;

Twelve plus(Twelve);
Twelve minus(Twelve);
int compare(Twelve);

unsigned char* getline();
private:
unsigned char* data;
size_t size;
int get_digit(unsigned char x);
unsigned char set_digit(int x);
};
#endif
