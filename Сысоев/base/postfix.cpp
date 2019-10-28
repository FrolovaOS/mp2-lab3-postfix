#include "postfix.h"
#include "stack.h"


TPostfix::TPostfix()
{
	{
		infix = "( ( ( a + b ) * c - d ) + h ) * s - n";
		len_infix = GetLen();
	}
}

TPostfix::TPostfix(string s)
{
	{
		infix = s;
		len_infix = GetLen();
	}
}

string TPostfix::ToPostfix()
{
	TStack<char> operation(len_infix);
	
	postfix = "";
	
	for (int i = 0; i < len_infix; i++)
	{
		if (isalpha(infix[i])) postfix += infix[i];
		else if ((infix[i] == '*') || (infix[i] == '/') || (infix[i] == '+') || (infix[i] == '-') || (infix[i] == '(') || (infix[i] == ')'))
		{
			if (operation.IsEmpty())
				operation.Push(infix[i]);
			else
			{
				 if (Priority(infix[i]) == Priority(operation.GetTop()))
					{
					 if (infix[i] == '(') operation.Push(infix[i]);
					 else if (infix[i] == ')')
					 {
						 while (operation.GetTop() != '(')
						 {
							 postfix += operation.Pop();
						 }
						 operation.Pop();
					 }
					 else 
					 {
						 postfix += operation.Pop();
						 operation.Push(infix[i]);
					 }
					}
				 else if (Priority(infix[i]) < Priority(operation.GetTop()))
				 {
					if (infix[i] == '(') operation.Push(infix[i]);
					else if (infix[i] == ')')
					{
						while (operation.GetTop() != '(')
						{
							postfix += operation.Pop();
						}
						operation.Pop();
					}
				    else
					   {
						while ((!operation.IsEmpty()) && (operation.GetTop() != '('))
						{

							postfix += operation.Pop();
						}
						operation.Push(infix[i]);
					   }
				  }
				  else if (Priority(infix[i]) > Priority(operation.GetTop()))
				   {
					operation.Push(infix[i]);
				   }
			}
		}
	}
	while (!operation.IsEmpty())
	{
		postfix += operation.Pop();
	}
	return postfix;
}

double TPostfix::Calculate(double* _values)
{
	TStack<double> values(CountVal());

	int j = 0;
	int val1;
	int val2;

	
	int CV = CountVal();
	
	double* values1;
	values1 = new double[CV]();//массив значений
	if (CV == CountLetter()) //случай, когда нет повторяющихся переменных
		{for (int i = 0; i < CV; i++)
			{
			values1[i] = _values[i];
			}
		}
	else // случай,когда есть повторяющиеся переменные
	{	
		string t = variables();
		int k = 0;
		
		for (int i = 0; i < CV; i++)
		{
			if (isalpha(t[i]))
			values1[i] = _values[k++];
			for (int j = i + 1; j < CV; j++)
			{
				if (isalpha(t[j]))
				{
					if ((t[i] == t[j]) && (t[i] != ' '))
					{
						values1[j] = values1[i];
						t[j] = ' ';
					}
				}
			}
		}
	}


	j = 0;

	for (int i = 0; i < postfix.length(); i++)
	{
		
		if (isalpha(postfix[i]))
		{
			values.Push(values1[j]);
			j++;
		}
	 else if ((postfix[i] == '/')|| (postfix[i] == '*') || (postfix[i] == '+') || (postfix[i] == '-'))
	 {
			val1 = values.GetTop();
			values.Pop();
			val2 = values.GetTop();
			values.Pop();
			if (postfix[i] == '+')
				values.Push(val1 + val2);
			if (postfix[i] == '-')
				values.Push(val2 - val1);
			if (postfix[i] == '/')
				values.Push(val2 / val1);
			if (postfix[i] == '*')
				values.Push(val2 * val1);

		}
	}
	return values.GetTop();
}

int TPostfix::Priority(char tmp)
{
	if (tmp == '/' || tmp == '*')
		return 3;
	else if (tmp == '+' || tmp == '-')
		return 2;
	else if (tmp == ')')
		return 1;
	else if (tmp == '(')
		return 0;
	throw "Error val";
}

int TPostfix::CountLetter()
{
	int res = 0;
	string t = "";
	for (int i = 0; i < len_infix; i++)
	{
		if (isalpha(infix[i]))
		{
			res++;
			t += infix[i];
		}
	}
	for (int i = 0; i < t.length(); i++)
	{
		for (int j = i+1; j < t.length(); j++)
		{
			if ((t[i] == t[j])&&(t[i]!=' '))
			{
				res--;
				t[j] = ' ';
			}
		}
	}
	return res;
}

int TPostfix::CountVal()
{
	int res = 0;
	string t = "";
	for (int i = 0; i < len_infix; i++)
	{
		if (isalpha(infix[i]))
		{
			res++;
		}
	}
	return res;
}

string TPostfix::variables()
{
	string tmp="";
	for (int i = 0; i < len_infix; i++)
	{
		if (isalpha(infix[i])) tmp+= infix[i];
	}
	return tmp;
}
