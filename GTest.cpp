#include "Twelve.hpp"
#include <string>
#include <gtest/gtest.h>
#include <cstring>

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    unsigned char* str = num.getline();
    EXPECT_EQ(std::strlen((char*)str), 0);
    delete[] str;
}

TEST(TwelveTest, StringConstructor) {
    Twelve num1("123");
    unsigned char* str1 = num1.getline();
    EXPECT_STREQ((char*)str1, "123");
    delete[] str1;
    
    Twelve num2("A1B");
    unsigned char* str2 = num2.getline();
    EXPECT_STREQ((char*)str2, "A1B");
    delete[] str2;
    
    Twelve num3("5");
    unsigned char* str3 = num3.getline();
    EXPECT_STREQ((char*)str3, "5");
    delete[] str3;
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num1 = {'1', '2', '3'};  
    unsigned char* str1 = num1.getline();
    EXPECT_STREQ((char*)str1, "123");
    delete[] str1;
    
    Twelve num2 = {'A', 'B', '0'}; 
    unsigned char* str2 = num2.getline();
    EXPECT_STREQ((char*)str2, "AB0");
    delete[] str2;
}

TEST(TwelveTest, CopyConstructor) {
    Twelve num1("A1B");
    Twelve num2(num1);  
    
    unsigned char* str1 = num1.getline();
    unsigned char* str2 = num2.getline();
    
    EXPECT_STREQ((char*)str1, (char*)str2);
    
    delete[] str1;
    delete[] str2;
}

TEST(TwelveTest, MoveConstructor) {
    Twelve num1("123AB");
    Twelve num2(std::move(num1));
    
    unsigned char* str = num2.getline();
    EXPECT_STREQ((char*)str, "123AB");
    
    unsigned char* str1 = num1.getline();
    EXPECT_EQ(std::strlen((char*)str1), 0);
    
    delete[] str;
    delete[] str1;
}

TEST(TwelveTest, Addition) {
    Twelve num1("123");
    Twelve num2("456");
    Twelve result1 = num1.plus(num2);
    unsigned char* str1 = result1.getline();
    EXPECT_STREQ((char*)str1, "579");
    delete[] str1;
    
    Twelve num3("A");  
    Twelve num4("3");
    Twelve result2 = num3.plus(num4);
    unsigned char* str2 = result2.getline();
    EXPECT_STREQ((char*)str2, "11");
	    delete[] str2;
    
    Twelve num5("A"); 
    Twelve num6("B");  
    Twelve result3 = num5.plus(num6);
    unsigned char* str3 = result3.getline();
    EXPECT_STREQ((char*)str3, "19");  
    delete[] str3;

    Twelve num7("BA9");
    Twelve num8("123");
    Twelve result4 = num7.plus(num8);
    unsigned char* str4 = result4.getline();
    EXPECT_STREQ((char*)str4, "1110");
    delete[] str4;
    
    
    Twelve num9("0");
    Twelve num10("A1B");
    Twelve result5 = num9.plus(num10);
    unsigned char* str5 = result5.getline();
    EXPECT_STREQ((char*)str5, "A1B");
    delete[] str5;
}


TEST(TwelveTest, Subtraction) {
    Twelve num1("579");
    Twelve num2("456");
    Twelve result1 = num1.minus(num2);
    unsigned char* str1 = result1.getline();
    EXPECT_STREQ((char*)str1, "123");
    delete[] str1;
    
    Twelve num3("11");  
    Twelve num4("3");
    Twelve result2 = num3.minus(num4);
    unsigned char* str2 = result2.getline();
	EXPECT_STREQ((char*)str2, "A");  
	    delete[] str2;
	    
	    
	    Twelve num5("19");  
	    Twelve num6("B");   
	    Twelve result3 = num5.minus(num6);
	    unsigned char* str3 = result3.getline();
	    EXPECT_STREQ((char*)str3, "A");  
	    delete[] str3;
	    
	    Twelve num7("A1B");
	    Twelve num8("A1B");
	    Twelve result4 = num7.minus(num8);
	    unsigned char* str4 = result4.getline();
	    EXPECT_STREQ((char*)str4, "0");
	    delete[] str4;
	}
	
	TEST(TwelveTest, SubtractionException) {
	    Twelve num1("123");
	    Twelve num2("456");
	    
	    try {
	        Twelve result = num1.minus(num2);
	        FAIL() << "Ожидалось исключение std::invalid_argument";
	    } catch (const std::invalid_argument& e) {
	        EXPECT_STREQ(e.what(), "nelza vichest");
	    } catch (...) {
	        FAIL() << "Ожидалось исключение std::invalid_argument";
	    }
	}
	
	TEST(TwelveTest, Comparison) {
	    Twelve num1("123");
	    Twelve num2("456");
	    Twelve num3("123");
	    Twelve num4("12");
	    Twelve num5("1234");
	    
	    EXPECT_EQ(num1.compare(num2), -1);  
	    EXPECT_EQ(num2.compare(num1), 1);   
	    EXPECT_EQ(num1.compare(num3), 0);   
	    EXPECT_EQ(num1.compare(num4), 1);   
	    EXPECT_EQ(num1.compare(num5), -1);  
	    
	    Twelve num6("A");   
	    Twelve num7("9");
	    Twelve num8("B");   
	    Twelve num9("10");  
	    
	    EXPECT_EQ(num6.compare(num7), 1);   
	    EXPECT_EQ(num6.compare(num8), -1);  
	    EXPECT_EQ(num6.compare(num9), -1);  
	}
	
	TEST(TwelveTest, GetLine) {
	    Twelve num("A1B23");
	    unsigned char* str = num.getline();
	    
	    EXPECT_EQ(std::strlen((char*)str), 5);
	    
	    EXPECT_STREQ((char*)str, "A1B23");
	    
	    EXPECT_EQ(str[5], '\0');
	    
	    delete[] str;
	}
	
	TEST(TwelveTest, InvalidCharacters) {
	    Twelve num("12G3");  
	    
	    try {
	        Twelve num2("45");
	        num.plus(num2);
	        FAIL() << "Ожидалось исключение для некорректного символа";
	    } catch (const std::invalid_argument& e) {
	        EXPECT_STREQ(e.what(), "strannie bukvi");
	    }
	}
	
	TEST(TwelveTest, ComplexOperations) {
	    Twelve a("BA9");     
	    Twelve b("123");     
	    Twelve c("45");      
	    
	    Twelve sum = a.plus(b);      
	    Twelve result = sum.minus(c); 
	    
	    unsigned char* str = result.getline();
	    EXPECT_STREQ((char*)str, "1087");
	    delete[] str;
	}
	
	
	TEST(TwelveTest, LeadingZeros) {
	    Twelve num1("00123");
	    Twelve num2("123");
	    
	    unsigned char* str1 = num1.getline();
	    unsigned char* str2 = num2.getline();
	    
	    EXPECT_STREQ((char*)str1, "00123");
	    EXPECT_STREQ((char*)str2, "123");
	    
	    
	    EXPECT_EQ(num1.compare(num2), 0);
	    
	    delete[] str1;
	    delete[] str2;
	}
	
	int main(int argc, char **argv) {
	    ::testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
	} 
	
	
