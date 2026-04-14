#pragma once

// велике число зображено послідовністю цифр
struct LargeNumber
{
	static const int length = 302;
	char m_digits[length];           // масив цифр
	int last;                      // номер останньої цифри
};

// процедура подвоєння великого числа
void MultByTwo(LargeNumber& x);

// процедура домноження великого числа на інше велике
void MultBy(LargeNumber& x, const LargeNumber& y);

// процедура виведення великого числа
void Print(const LargeNumber& x);

// програма піднесення 2 до степеня n, 1<=n<=1000
void PowerLast();

// програма швидкого піднесення 2 до степеня n, 1<=n<=1000
void PowerFast();
