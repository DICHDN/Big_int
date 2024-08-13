/*
* # Задача 2. Большие числа 

### Описание
Вам нужно реализовать класс для работы с большими числами, которые не помещаются в стандартные типы данных.

Для этого класса нужно определить методы:
- конструктор перемещения;
- перемещающий оператор присваивания;
- оператор сложения двух больших чисел; +
- оператор умножения на число.

Для реализации этого класса можно воспользоваться `std::string` или `std::vector`.

### Пример правильной работы программы
```C++
auto number1 = big_integer("114575");
auto number2 = big_integer("78524");
auto result = number1 + number2;
std::cout << result; // 193099
``` 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <stdlib.h>
#include <iterator>




class big_integer
{
private:
    //std::vector<int> data;
public:
    std::vector<int> data;
    big_integer(std::string A)
    {
        std::vector<int> newString;
        for (auto i : A) newString.push_back(atoi(&i));
        data = newString;
    }
    big_integer() {}
    big_integer(int A)
    {
        std::vector<int> temp;
        do
        {
            temp.push_back(A % 10);
            A = A / 10;
        } while (A > 0);

    }

    big_integer operator+(big_integer& a)
    {
        std::vector<int> c;
        std::vector<int> d = a.data;
        std::vector<int> b = data;
        std::reverse(d.begin(), d.end());
        std::reverse(b.begin(), b.end());
        if (d.size() > b.size())
        {
            int i = 0;
            for (auto j : d)
            {
                if (i < b.size()) c.push_back(j + b[i]);
                else c.push_back(j + 0);
                ++i;
            }
        }
        if (d.size() < b.size())
        {
            int i = 0;
            for (auto j : b)
            {
                if (i < d.size()) c.push_back(j + d[i]);
                else {
                    c.push_back(j + 0);
                    ++i;
                }
                ++i;
            }
        }
        if (d.size() == b.size())
        {
            int i = 0;
            for (auto j : d)
            {
                c.push_back(j + b[i]);
                ++i;
            }
        }
        for (int i = 0; i < c.size(); ++i)//выставление порядков цифр
        {
            if (i < c.size() - 1)
            {
                int a = i + 1;
                int b = c[i] / 10;
                c[a] = c[a] + b;
                c[i] = c[i] % 10;
            }
            else
            {
                if (c[i] / 10 > 0)
                {
                    c.push_back(1);
                    c[i] = c[i] % 10;
                }
                else c[i] = c[i] % 10;
            }
        }
        std::reverse(c.begin(), c.end());
        big_integer A;
        A.data = c;
        return A;
    }

    big_integer operator*(big_integer& a)        
    {
        big_integer A(0);       
        std::reverse(a.data.begin(), a.data.end());
        int j = 0;
        for (auto el : a.data)
        {
            int t = 0;
            std::vector<int> temp(NULL);
            std::reverse(data.begin(), data.end());
            for (auto elem : data)
            {
                int t1 = el * elem+t;
                t = t1 / 10;
                int c = t1 % 10;
                temp.push_back(c);
            }
            std::reverse(data.begin(), data.end());
            std::reverse(temp.begin(), temp.end());
            for (int i=0;i<j;++i) temp.push_back(0);
            big_integer B;
            B.data = temp;
            std::cout << std::endl;
            B.print_big_integer();
            std::cout << std::endl;
            A = A + B;
            
            ++j;
        }
        return A;
    }
    big_integer operator*(int a)
    {
        std::vector<int> c;
        int temp = a;


        big_integer A("0"), B;
        A.data = data;
        B.data = data;
        
        do
        {
            int d = temp % 10;
            c.push_back(d);
            temp = temp / 10;
        } while (temp > 0);
        std::reverse(c.begin(), c.end());
        int i = 1;
        for (auto elem : c)
        {
            for (int j = 0; j < i * elem-1; ++j)
            {
                A = A + B; //простой но очень дорогой способ О(n^2)
                /*существует еще способ бысрого умножения - Умножение длинных чисел методом Карацубы */
            }
            i = i * 10;
        }
        return A;
    }

    void print_big_integer()
    {
        for (auto i : data) std::cout << i;
    };
    ~big_integer()
    {
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    big_integer a("114575");
    std::cout << std::endl;
    a.print_big_integer();
    big_integer b("78524");
    std::cout << std::endl;
    b.print_big_integer();
    big_integer c = a+ b;
    std::cout << std::endl;
    std::cout <<"Сумма первого и второго чисел" << std::endl;
    c.print_big_integer();
    int e = 9;
    std::cout << std::endl << "первое число * "<<e;
    big_integer d = a * e;
    std::cout << std::endl;
    d.print_big_integer(); 
    std::cout << std::endl << "первое число * второе число" ;
    big_integer f = a * b;
    std::cout << std::endl;
    f.print_big_integer();
}

