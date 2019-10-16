#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix; // инфиксная форма
  string postfix; // постфиксная форма
  int len_infix; // длина инфиксной формы
public:
  TPostfix();
  TPostfix(string s);
  string GetInfix() { return infix; } //получение инфиксной формы
  string GetPostfix() { return postfix; } // получение постфиксной формы
  string ToPostfix(); // перевод в постфиксную форму
  double Calculate(double* _values); // Ввод переменных, вычисление по постфиксной форме
  int Priority(char tmp); // сравнение приоритета элементов
  int GetLen() { return infix.length(); } // получение длины инфиксной формы
  int CountValue(); // подсчет количества значений 
};

#endif
