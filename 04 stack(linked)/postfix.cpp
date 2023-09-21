#include "stacklnk.cpp"
#include <string>

double evaulate(string& postExpression)
{
	Stack<double> testStack;          
	double a, b, c; // a,b�� �ǿ�����, c�� ���
	for (int i = 0; i < postExpression.length(); i++)
	{
		if (postExpression[i] == '+' || postExpression[i] == '-' || postExpression[i] == '*' || postExpression[i] == '/')
		{
			b = testStack.pop();
			a = testStack.pop();
			switch (postExpression[i])
			{
			case'+':
				c = a + b;
				testStack.push(c);
				break;
			case'-':
				c = a - b;
				testStack.push(c);
				break;
			case'*':
				c = a * b;
				testStack.push(c);
				break;
			case'/':
				c = a / b;
				testStack.push(c);
				break;
			}
		}
		else if ((postExpression[i] - '0') >= 0 && (postExpression[i] - '0') <= 9)
		{ 
			testStack.push(postExpression[i] - '0');          // char���� postExrpession[i] �� double������ ��ȯ�Ͽ� push��
		}
	}
	return testStack.pop();
}

int main(void)
{
	while (cin)
	{
		string postExpression;
		cout << "Input postfix expression: ";
		cin >> postExpression;

		if (!cin)              // Reached EOF: stop processing
			break;

		cout << "result: " << evaulate(postExpression) << endl << endl;
	}

	return 0;
}