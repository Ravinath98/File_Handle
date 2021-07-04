///////////////////////////////////////////////////////////////////////////////////////////////////
/// *****************   I USED VISUAL STUDIO TO CODE THIS.. *****************************************************************************************


#include <iostream>
#include <fstream> //library for crreate,reads and writes to files
#include <iomanip> //to get the precision
#include <cmath>   //for mathematical functions (abs)
#include <stdio.h>
#include <stack>   //library for stack
#include <string>  //string library
#define size 300  //define the size of the stack(I got 300 because with the spaces it's larger than 100)

using namespace std;


int top;   //stack top
char stack1[size];  //define the char stack

void push(char symbol, int& top)  //stack push function
{
	if (top < size - 1)
	{
		if (top < 0)
		{
			stack1[0] = symbol;
			top = 0;
		}
		else
		{
			top = top + 1;
			stack1[top] = symbol;
		}
	}
	else //if stack is full....
	{
		cout << " E" << endl;

	}
}

int pop(int& top) //stack pop function..
{
	if (top >= 0)
	{
		char item = stack1[top];
		top = top - 1;
		return item;
	}
}

int checkParentheses(char formulaLine[], char stack1[100], int top)  //function for check parentheses..
{

	for (int i = 0; i < 100; i++)
	{
		if (formulaLine[i] == '(' || formulaLine[i] == '{' || formulaLine[i] == '[')
		{
			push(formulaLine[i], top);
			continue;
		}

		else if (formulaLine[i] == ')' || formulaLine[i] == '}' || formulaLine[i] == ']')
		{
			if (top != -1)
			{
				if (formulaLine[i] == ')')
				{
					if (stack1[top] == '(')
					{
						pop(top);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (formulaLine[i] == '}')
				{
					if (stack1[top] == '{')
					{
						pop(top);
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					if (stack1[top] == '[')
					{
						pop(top);
						continue;
					}
					else
					{
						break;
					}
				}
			}
		}


	}
	if (top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int operatorsWeight(char op)  //function for get the weight of the operators....
{
	switch (op)
	{

	case'/':return 2;
	case'*':return 2;
	case'+':return 1;
	case'-':return 1;
	default:return 0;

	}
}

void infixToPostfix(char modified[], char postfix[], char stack1[], int top) //function for convert infix to postfix
{
	int count = 0;
	int check1 = 0;
	int num = 0;
	int symbolWeight;
	char symbol = modified[check1];
	while (symbol != '=')
	{
		symbol = modified[check1];
		if (symbol == '(')
		{

			push(symbol, top);

			check1++;
			continue;
		}
		if (symbol == '=')
		{
			continue;
		}

		if (symbol == ')')
		{
			while (top != -1 && stack1[top] != '(')
			{
				postfix[num++] = stack1[top];
				pop(top);
			}
			if (top != -1)
			{
				pop(top);
			}
			check1++;
			continue;
		}
		symbolWeight = operatorsWeight(symbol);

		if (symbolWeight == 0) //there is a operand
		{
			count = count + 1;

			postfix[num++] = symbol;

		}
		else  //there is a operator...
		{

			if (count > 1) //give a space to identify multi digit numbers....
			{
				postfix[num++] = ' ';
			}
			if (count == 1)
			{
				postfix[num++] = ' ';
			}

			count = 0;


			if (top == -1)
			{
				push(symbol, top);
			}
			else
			{
				while (top != -1 && stack1[top] != '(' && symbolWeight <= operatorsWeight(stack1[top]))
				{
					postfix[num++] = ' ';  //give spaces
					postfix[num++] = stack1[top];
					postfix[num++] = ' ';  //give spaces
					pop(top);
				}

				push(symbol, top);

			}
		}
		check1++;

	}

	while (top != -1)
	{
		postfix[num++] = ' ';   //give spaces
		postfix[num++] = stack1[top];
		pop(top);

	}
	postfix[num] = 0;
}


float EvaluatePostfix(char postfix[], int& error) //function for evaluate the Postfix expression
{

	stack<float> S; //define stack S

	for (int i = 0; i < 300; i++)
	{
		if (postfix[i] == ' ') //if there is a space in the postfix formula...
		{
			continue;
		}
		else if (postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-') //if there is a operator in the postfix formula
		{
			float op2 = S.top();
			S.pop();
			if (S.empty()) //if stack will empty...
			{
				return op2;
			}
			float op1 = S.top();
			S.pop();

			switch (postfix[i])  //mathematical operations
			{
			case '+':S.push(op1 + op2); break;
			case '-':S.push(op1 - op2); break;
			case '*':S.push(op1 * op2); break;
			case '/':

				if (op2 == 0)  //if there is state that divide by zero..
				{

					error = 1;


				}
				else if (op1 == 0 && op2 == 0)  //if bothe operands are zeros...
				{

					error = 1;

				}
				else  //dividing
				{

					S.push((float)op1 / (float)op2);
					break;
				}


			default:
				return 0;
			}


		}
		else if (postfix[i] >= '0' && postfix[i] <= '9')  //if there is a operand...
		{
			float op = 0;
			while (i < 300 && (postfix[i] >= '0' && postfix[i] <= '9'))
			{
				op = (op * 10) + (postfix[i] - '0');
				i++;
			}
			i--;
			S.push(op);
		}
	}
	if (error != 1)
	{
		return S.top();
	}


}



int main()  //main function.
{
	ifstream textFile;  //read the text file(variable)
	ofstream resultFile("result.txt");  //to creates and writes the text file(in here it will create a text file with the results on this name in the cpp file path)
	textFile.open("formulas.txt");    //open the first text file
	if (!textFile)    //if file cannot open....
	{
		cout << "Unable to open the text file!!!!" << endl;
		return 0;
	}

	//in here "resultFile<<" statement represent the output to the text file
	char formulaLine[100];   //to store formulas (line by line)
	textFile >> formulaLine;
	while (textFile.good())  //this loop will execute until end of the text file
	{
		cout << formulaLine;  //formula output to the console
		resultFile << formulaLine;  //formula output to the newly created text file

		top = -1;
		int t = 0;
		int z = 0;
		int c = 0;
		if (checkParentheses(formulaLine, stack1, top) == 1) //check the balanced parentheses
		{
			z = 1;

			for (int i = 0; i < 100; i++)
			{
				if (formulaLine[i] == '=')
				{
					t = 1;
				}
			}

		}
		else
		{
			c = 1;
			cout << " E" << endl;
			resultFile << " E" << endl;
			
		}
		

		if (z == 1 && t == 1 && c==0)
		{
			char modified[100];
			for (int i = 0; i < 100; i++)
			{
				modified[i] = formulaLine[i];
			}

			for (int i = 0; i < 100; i++)
			{
				if (modified[i] == '[')
				{
					modified[i] = '(';
				}
				else if (modified[i] == ']')
				{
					modified[i] = ')';
				}
				else if (modified[i] == '{')
				{
					modified[i] = '(';
				}
				else if (modified[i] == '}')
				{
					modified[i] = ')';
				}
				else
				{
					continue;
				}
			}
			//infix to postfix and the execution of expression//////////////////////////////////////////////////////
			char postfix[300];  //postfix expression....
			top = -1;
			infixToPostfix(modified, postfix, stack1, -1); //infix to postfix function.....

			int error = 0;
			float result = EvaluatePostfix(postfix, error);
			cout << " ";
			resultFile << " "; //output to the textfile
			if (abs(result - int(result)) != 0) //check if result has a decimal point...
			{
				cout << fixed;
				resultFile << fixed;
				cout << setprecision(2);  //set precision up to 2 decimal points...
				resultFile << setprecision(2);
				cout << result << endl;
				resultFile << result << endl;

			}
			else
			{
				if (error == 0)  //this is for check mathematical error (divide by 0 or 0 divide by 0)
				{
					cout << int(result) << endl;
					resultFile << int(result) << endl;
				}
				else if (error == 1)
				{
					cout << " E" << endl;
					resultFile << " E" << endl;
				}
			}



		}
		else
		{
			if (c == 0)
			{
				cout << " E" << endl;
				resultFile << " E" << endl;
			}
		}


		textFile >> formulaLine;
	}

	return 0;
}