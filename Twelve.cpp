#include <stdlib.h>
#include <iostream>
#include <string>
class Twelve
{
public:
Twelve()
{
size = 0;
data = nullptr;	
}
Twelve(const size_t & n, unsigned char * t)
{
	size = n;
	data = new unsigned char[size];
	if (data!=nullptr) {for(size_t i=0;i<size;i++){data[size-1-i]=t[i];}}
	
}
Twelve(const std::initializer_list< unsigned char> &t)
{
	size = t.size();
	data = new unsigned char[size];
	for(size_t i=0;i<size;i++){data[i]=*(t.end()+i);}
}
Twelve(const std::string &t)
{
	size = t.size();
	for(size_t i=0;i<size;i++){data[size-1-i]=t[i];}
}
Twelve(const Twelve& other)
{
	data = other.data;
	size = other.size;
}
Twelve(Twelve&& other) noexcept
{
	size = other.size;
	for(size_t i=0;i<size;i++){data[i]=other.data[i];}
	delete[] other.data;
}
virtual ~Twelve() noexcept
{
	delete[] data;
}

Twelve plus(Twelve);
Twelve minus(Twelve);
Twelve copy();
int compare(Twelve);

unsigned char* getline();
private:
unsigned char* data;
size_t size;
};
