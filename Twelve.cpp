#include <stdlib.h>
#include <iostream>
#include <string>
#include "Twelve.hpp"
	Twelve::Twelve()
	{
	size = 0;
	data = nullptr;	
	}
	
	Twelve::Twelve(const size_t & n, unsigned char * t)
	{
		size = n;
		data = new unsigned char[size];
		if (data!=nullptr) {for(size_t i=0;i<size;i++){data[size-1-i]=t[i];}}
	}
	
	Twelve::Twelve(const std::initializer_list< unsigned char> &t)
	{
		size = t.size();
		data = new unsigned char[size];
		for(size_t i=0;i<size;i++){data[i]=*(t.end()-i-1);}
	}
	
	Twelve::Twelve(const std::string &t)
	{
		size = t.size();
		data = new unsigned char[size];
		for(size_t i=0;i<size;i++){data[size-1-i]=t[i];}
	}
	
	Twelve::Twelve( Twelve&& other) noexcept
	{
		data = other.data;
		size = other.size;
		other.data=nullptr;
		other.size=0;
	}
	
	Twelve::Twelve(const Twelve& other)
	{
		size = other.size;
		data = new unsigned char[size];
		for(size_t i=0;i<size;i++){data[i]=other.data[i];}
	}
	
	Twelve::~Twelve() noexcept
	{
		delete[] data;
		data = nullptr;
	}

	Twelve Twelve::plus(Twelve sec)
	{
		int v_ume{0};
		size_t indexer{0};
		int first_digit{0};
		int second_digit{0};
		while((indexer<size)||(indexer<sec.size))
		{ try{
			if(indexer<size){first_digit =  get_digit(data[indexer]);}
			else{first_digit=0;}
			if(indexer<sec.size){second_digit = get_digit(sec.data[indexer]);}
			else{second_digit=0;}
			}catch(std::invalid_argument  & e){ throw (e);};

			v_ume = (first_digit+second_digit+v_ume)/12;
			++indexer;
		}

		
		Twelve result{};
		result.size = v_ume==0?	indexer:indexer+1;
		indexer = 0;
		result.data = new unsigned char [result.size];
		v_ume=0;		
		while(indexer<result.size)
			{
				if(indexer<size){first_digit =  get_digit(data[indexer]);}
				else{first_digit=0;}
				if(indexer<sec.size){second_digit = get_digit(sec.data[indexer]);}
				else{second_digit=0;}

							
			result.data[indexer]=(first_digit+second_digit+v_ume)%12<10?(first_digit+second_digit+v_ume)%12+'0':(first_digit+second_digit+v_ume)%12-10+'A';
			v_ume = (first_digit+second_digit+v_ume)/12;
			++indexer;
			}
		return result;
	}
	/*
	Twelve Twelve::minus(Twelve sec)
	{
		
		int v_ume{0};
		size_t indexer{0};
		int first_digit{0};
		int second_digit{0};

		int is_loss_size{0};
		while((indexer<size)||(indexer<sec.size))
		{
			try{
				if(indexer<size){first_digit =  get_digit(data[indexer]);}
				else{first_digit=0;}
				if(indexer<sec.size){second_digit = get_digit(sec.data[indexer]);}
				else{second_digit=0;}
				}
			catch(std::invalid_argument  & e){ throw (e);};


			if ((first_digit)<(second_digit+v_ume))
			{size_t j=indexer+1; 	while(data[j]=='0')
				{j++;  if(j>size-1)
					{throw std::invalid_argument("nelza vichest");}
				}

				v_ume=1;	
			}
			else
			{
				if(first_digit-second_digit==0+v_ume){is_loss_size = 1;}else{is_loss_size=0;}
				v_ume=0;
			}
			++indexer;	
		}
		
		Twelve result{};
		result.size = indexer-is_loss_size;
		result.data = new unsigned char [result.size];


		indexer =0;
		v_ume = 0;
		while(indexer<result.size)
				{

						if(indexer<size){first_digit =  get_digit(data[indexer]);}
						else{first_digit=0;}
						if(indexer<sec.size){second_digit = get_digit(sec.data[indexer]);}
						else{second_digit=0;}
						
		
					if ((first_digit)<(second_digit+v_ume))
					{
						result.data[indexer]=set_digit( first_digit+12-second_digit-v_ume);
						v_ume=1;	
					}
					else
					{
						result.data[indexer]=set_digit( first_digit-second_digit-v_ume);

						v_ume=0;
					}
					
				++indexer;	
				}
		
		return result;


	} */
	Twelve Twelve::minus(Twelve sec)
{
    // Проверяем, что уменьшаемое >= вычитаемого
    if (compare(sec) < 0) {
        throw std::invalid_argument("nelza vichest");
    }
    
    // Если числа равны, возвращаем ноль
    if (compare(sec) == 0) {
        Twelve result;
        result.size = 1;
        result.data = new unsigned char[1];
        result.data[0] = '0';
        return result;
    }
    
    size_t max_size = (size > sec.size) ? size : sec.size;
    int* temp_result = new int[max_size];
    
    // Инициализируем временный массив цифрами уменьшаемого
    for (size_t i = 0; i < max_size; ++i) {
        if (i < size) {
            temp_result[i] = get_digit(data[i]);
        } else {
            temp_result[i] = 0;
        }
    }
    
    // Вычитаем цифры вычитаемого
    for (size_t i = 0; i < sec.size; ++i) {
        if (temp_result[i] < get_digit(sec.data[i])) {
            // Занимаем из старшего разряда
            size_t j = i + 1;
            while (j < max_size && temp_result[j] == 0) {
                j++;
            }
            
            if (j >= max_size) {
                delete[] temp_result;
                throw std::invalid_argument("nelza vichest");
            }
            
            // Занимаем
            temp_result[j]--;
            for (size_t k = i + 1; k < j; k++) {
                temp_result[k] = 11; // B в 12-ричной (максимальная цифра)
            }
            temp_result[i] += 12;
        }
        
        temp_result[i] -= get_digit(sec.data[i]);
    }
    
    // Определяем фактический размер результата (без ведущих нулей)
    size_t result_size = max_size;
    while (result_size > 1 && temp_result[result_size - 1] == 0) {
        result_size--;
    }
    
    // Создаем результат
    Twelve result;
    result.size = result_size;
    result.data = new unsigned char[result_size];
    
    // Преобразуем цифры обратно в символы
    for (size_t i = 0; i < result_size; ++i) {
        result.data[i] = set_digit(temp_result[i]);
    }
    
    delete[] temp_result;
    return result;
}
	int Twelve::compare(Twelve sec)
	{
		size_t size1=size-1;
		while(data[size1]=='0'){--size1;}
		size_t size2 = sec.size-1;
		while(sec.data[size2]=='0'){--size2;}

		if (size1>size2){return 1;}
		if (size1<size2){return -1;}
		for(int i = size1; i>=0;--i)
		{
			if(get_digit(data[i])>get_digit(sec.data[i])){return 1;}
			if(get_digit(data[i])<get_digit(sec.data[i])){return -1;}
		}
		return 0;
		
		
	}

	unsigned char* Twelve::getline()
	{
		unsigned char* result = new unsigned char [size+1];
		for(size_t i = 0;i<size;++i)
		{
			result[i]=data[size-i-1];
		}
		result[size]='\0';
		return result;
	}
	int Twelve::get_digit(unsigned char x) 
	{
		int result;
		if((x>='0')&&(x<='9'))          {result = x-'0';}
		else if((x<='B')&&(x>='A'))			{result = (x-'A')+10;} else{ throw(std::invalid_argument("strannie bukvi"));}
	return result;
	}
	unsigned char  Twelve::set_digit(int x)
	{
		return ((x>=0)&&(x<=9))? '0'+x:'A'+(x-10);
	}
	
