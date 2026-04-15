#include "LargeInteger.h"
#include <iostream>

// процедура подвоєння великого числа
void MultByTwo(LargeNumber& x)
{
	char calc;                        // результат проміжних обчислень
	char transfer = 0;                // перенесення до старшого розряду
	for (int i = 0; i <= x.last; ++i) // переглядаємо всі цифри великого числа
	{
		calc = x.m_digits[i] * 2 + transfer;
		x.m_digits[i] = calc % 10;    // молодшу цифру добутку записуємо
		transfer = calc / 10;         // старшу - переносимо
	}
	if (transfer > 0)                 // запис числа стає довшим
		x.m_digits[++x.last] = transfer;
}

// процедура домноження великого числа на інше велике
void MultBy(LargeNumber& x, const LargeNumber& y)
{
	//std::cout << " >>> MultBy: " << x.last + 1 << ' ' << y.last + 1 << '\n';
	// зміння prod накопичує результати обчислень - добуток x*y
	LargeNumber prod = { { 0 }, x.last };
	for (int j = 0; j <= y.last; ++j) // перебір цифр другого множника
	{
		char a = y.m_digits[j];
		if (a == 0) continue; // множення на 0 пропускаємо
		char calc;            // результат проміжних обчислень
		char transfer = 0;    // перенесення до старшого розряду
		for (int i = 0; i <= x.last; ++i) // перебір цифр першого множника
		{
			int k = i + j; // місце чергової цифри
			// множення в стовпчик багатоцифрових чисел мусить враховувати
			//  результати множень на попередні цифри
			calc = x.m_digits[i] * a + transfer + prod.m_digits[k];
			if (k > prod.last) prod.last = k;
			prod.m_digits[k] = calc % 10; // молодшу цифру добутку записуємо
			transfer = calc / 10;         // старшу - переносимо
		}
		if (transfer > 0)                 // запис числа стає довшим
			prod.m_digits[++prod.last] += transfer;
	}
	x = prod;      // обчислений добуток потрапляє в перший множник
}

// процедура виведення великого числа
void Print(const LargeNumber& x)
{
	for (int i = x.last; i >= 0; --i) std::cout << (int)x.m_digits[i];
	std::cout << '\n';
}

// програма піднесення 2 до степеня n, 1<=n<=1000
void PowerLast()
{
	std::cout << "* Обчислення великого степеня числа 2 *\n\n";
	int n;
	std::cout << "Введіть n (n<=1000): "; std::cin >> n;
	LargeNumber x; // велике число х
	// обчислити 2^n в змінній x
	//     велике_число_x = 1;
	x.last = 0;
	x.m_digits[0] = 1;  // x = 2^0

	for (int k = 1; k <= n; ++k)
	{
		// подвоїти_велике_число(x);
		MultByTwo(x); // x = 2^k
	}
	// x = 2^n
	std::cout << "2 в степені " << n << " = ";
	//надрукувати_велике_число(x);
	Print(x);
}

// програма швидкого піднесення 2 до степеня n, 1<=n<=1000
void PowerFast()
{
	std::cout << "* Обчислення великого степеня числа 2 швидким алгоритмом *\n\n";
	int n;
	std::cout << "Введіть n (n<=1000): "; std::cin >> n;
	int m = n;     // робоча копія показника степеня
	LargeNumber d = { { 2 }, 0 }; // допоміжний множник; спочатку d = 2
	// обчислити 2^n в змінній x
	//     велике_число_x = 1;
	LargeNumber x = { { 1 }, 0 }; // велике число х = 2^0
	while (m > 0)
	{
		// піднесення до квадрата, поки показник степеня парний
		while (m % 2 == 0)
		{
			MultBy(d, d);
			m /= 2;
		}
		// врахування квадратів у загальному добутку
		MultBy(x, d);
		--m;
	}
	std::cout << "2 в степені " << n << " = ";
	//надрукувати_велике_число(x);
	Print(x);
}
