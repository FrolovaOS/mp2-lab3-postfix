#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  setlocale(LC_ALL, "Russian");
  string expression;
  double res;
  cout << "Введите арифметическое выражение: ";
  getline(cin,expression);
 
  TPostfix postfix(expression);

  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

  double* values;
  int tmp = postfix.CountLetter();
  values = new double[tmp];
  cout << "Введите аргументы" << endl;
  
  for (int i = 0; i < tmp; i++)
  {
	  cin >> values[i];
  }

  res = postfix.Calculate(values);
  cout << res << endl;

  return 0;
}
