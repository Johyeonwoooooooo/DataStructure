//--------------------------------------------------------------------
//
//  Laboratory 5 (In-lab 3 shell)                          delim.cs
//
//  Program validates delimiter pairing.
//
//--------------------------------------------------------------------

#include <string>
#include "stackarr.cpp"

//--------------------------------------------------------------------
//
//  Function prototype

bool delimitersOk(const string &expression);

//--------------------------------------------------------------------

int main(void)
{
    string inputLine;            // Input line
    char ch;                     // Holding pen for input chars

    cout << "This program checks for properly matched delimiters."
         << endl;

    while(cin)
    {
        cout << "Enter delimited expression (<EOF> to quit) : ";

        // Read in one line
        inputLine = "";
        cin.get(ch);
        while(cin && ch != '\n')
        {
            inputLine = inputLine + ch;
            cin.get(ch);
        }
    
        if(!cin)              // Reached EOF: stop processing
            break;

        if (delimitersOk(inputLine))
            cout << "Valid" << endl << endl;
        else
            cout << "Invalid" << endl << endl;
    }

    return 0;
}


bool delimitersOk(const string& expression)
{
    int length = expression.size();
    Stack <char> items(length);
    char popitem = NULL;
    for (int i = 0; i < length; i++)
    {
        if (expression[i] == '(')
        {
            items.push('(');
        }
        else if (expression[i] == '[')
        {
            items.push('[');
        }
        else if (expression[i] == ')')
        {
            popitem = items.pop();

            if (popitem != '(')
                return false;
        } 
        else if (expression[i] == ']')
        {
            popitem = items.pop();

            if (popitem != '[')
                return false;
        }
    }
    if (items.isEmpty() == true)
          return true;
    else
          return false;
}