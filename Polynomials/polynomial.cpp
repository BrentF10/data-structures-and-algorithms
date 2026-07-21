#include <iostream>
#include <string>
#include <cctype>
#include <climits>

using namespace std;

const int MIN_POLYNOMIALS = 0;
const int MAX_POLYNOMIALS = 10;

struct ATerm
{
    int coefficient;
    int exponent;
    ATerm* next;
};

typedef ATerm* Polynomial;


//------------------------------------------------------------------------------------
//Function Prototypes
//------------------------------------------------------------------------------------

string trim(const string& line);
bool parseInteger(const string& line, int& value);
int readIntegerLine(const string& prompt, int minValue, int maxValue);
ATerm* createNode(int coefficient, int exponent);
void clearPolynomial(Polynomial& poly);
Polynomial copyPolynomial(const Polynomial poly);
void insertTerm(Polynomial& poly, int coefficient, int exponent);
Polynomial Add(const Polynomial poly1, const Polynomial poly2);
Polynomial Multiply(const Polynomial poly1, const Polynomial poly2);
void skipSpaces(const string& line, int& index);
bool readUnsignedInteger(const string& line, int& index, int& value);
bool parseTerm(const string& line, int& index, int& coefficient, int& exponent);
bool parsePolynomial(const string& line, Polynomial& poly);
void displayTerm(int coefficient, int exponent, bool firstTerm);
void displayPolynomial(const Polynomial poly);
void displayBracketPolynomial(const Polynomial poly);
void displaySum(Polynomial polynomials[], int count);
void displayProduct(Polynomial polynomials[], int count);
void inputPolynomials(Polynomial polynomials[], int count);
void clearPolynomialArray(Polynomial polynomials[], int count);
void runProgram();


//------------------------------------------------------------------------------------
//Starts the program
//------------------------------------------------------------------------------------

int main()
{
    runProgram();
    return 0;
}


//------------------------------------------------------------------------------------
//Removes leading and trailing spaces from a string
//------------------------------------------------------------------------------------

string trim(const string& line)
{
    int start = 0;
    int end = (int)(line.length()) - 1;

    while (start <= end && line[start] == ' ')
    {
        start++;
    }

    while (end >= start && line[end] == ' ')
    {
        end--;
    }

    if (start > end)
    {
        return "";
    }

    string result = "";
    for (int i = start; i <= end; i++)
    {
        result += line[i];
    }

    return result;
}


//------------------------------------------------------------------------------------
//Parses a string as an integer
//------------------------------------------------------------------------------------

bool parseInteger(const string& line, int& value)
{
    value = 0;
    int i = 0;
    int n = (int)(line.length());

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i >= n)
    {
        return false;
    }

    int sign = 1;
    if (line[i] == '+')
    {
        i++;
    }
    else if (line[i] == '-')
    {
        sign = -1;
        i++;
    }

    if (i >= n || !isdigit(line[i]))
    {
        return false;
    }

    while (i < n && isdigit(line[i]))
    {
        int digit = line[i] - '0';

        if (value > (INT_MAX - digit) / 10)
        {
            return false;
        }

        value = value * 10 + digit;
        i++;
    }

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i != n)
    {
        return false;
    }

    value *= sign;
    return true;
}


//------------------------------------------------------------------------------------
//Reads and validates an integer line of input
//------------------------------------------------------------------------------------

int readIntegerLine(const string& prompt, int minValue, int maxValue)
{
    string line;
    int value = 0;
    bool valid = false;

    while (!valid)
    {
        cout << prompt;
        getline(cin, line);

        if (parseInteger(line, value) && value >= minValue && value <= maxValue)
        {
            valid = true;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl << endl;
        }
    }

    return value;
}


//------------------------------------------------------------------------------------
//Creates a new polynomial term node
//------------------------------------------------------------------------------------

ATerm* createNode(int coefficient, int exponent)
{
    ATerm* nn = new ATerm;
    nn->coefficient = coefficient;
    nn->exponent = exponent;
    nn->next = NULL;
    return nn;
}


//------------------------------------------------------------------------------------
//Deletes all nodes in a polynomial
//------------------------------------------------------------------------------------

void clearPolynomial(Polynomial& poly)
{
    while (poly != NULL)
    {
        ATerm* temp = poly;
        poly = poly->next;
        delete temp;
    }
}


//------------------------------------------------------------------------------------
//Creates and returns a deep copy of a polynomial
//------------------------------------------------------------------------------------

Polynomial copyPolynomial(const Polynomial poly)
{
    Polynomial result = NULL;
    ATerm* tail = NULL;
    ATerm* current = poly;

    while (current != NULL)
    {
        ATerm* nn = createNode(current->coefficient, current->exponent);

        if (result == NULL)
        {
            result = nn;
            tail = nn;
        }
        else
        {
            tail->next = nn;
            tail = nn;
        }

        current = current->next;
    }

    return result;
}


//------------------------------------------------------------------------------------
//Inserts a term into the polynomial in decreasing exponent order
//------------------------------------------------------------------------------------

void insertTerm(Polynomial& poly, int coefficient, int exponent)
{
    if (coefficient == 0)
    {
        return;
    }

    ATerm* previous = NULL;
    ATerm* current = poly;

    while (current != NULL && current->exponent > exponent)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->exponent == exponent)
    {
        current->coefficient += coefficient;

        if (current->coefficient == 0)
        {
            if (previous == NULL)
            {
                poly = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
        }
        return;
    }

    ATerm* nn = createNode(coefficient, exponent);

    if (previous == NULL)
    {
        nn->next = poly;
        poly = nn;
    }
    else
    {
        nn->next = current;
        previous->next = nn;
    }
}


//------------------------------------------------------------------------------------
//Adds two polynomials and returns the result polynomial
//------------------------------------------------------------------------------------

Polynomial Add(const Polynomial poly1, const Polynomial poly2)
{
    Polynomial result = NULL;
    ATerm* p = poly1;
    ATerm* q = poly2;

    while (p != NULL && q != NULL)
    {
        if (p->exponent > q->exponent)
        {
            insertTerm(result, p->coefficient, p->exponent);
            p = p->next;
        }
        else if (p->exponent < q->exponent)
        {
            insertTerm(result, q->coefficient, q->exponent);
            q = q->next;
        }
        else
        {
            insertTerm(result, p->coefficient + q->coefficient, p->exponent);
            p = p->next;
            q = q->next;
        }
    }

    while (p != NULL)
    {
        insertTerm(result, p->coefficient, p->exponent);
        p = p->next;
    }

    while (q != NULL)
    {
        insertTerm(result, q->coefficient, q->exponent);
        q = q->next;
    }

    return result;
}


//------------------------------------------------------------------------------------
//Multiplies two polynomials and returns the result polynomial
//------------------------------------------------------------------------------------

Polynomial Multiply(const Polynomial poly1, const Polynomial poly2)
{
    Polynomial result = NULL;
    ATerm* p = poly1;

    while (p != NULL)
    {
        ATerm* q = poly2;
        while (q != NULL)
        {
            insertTerm(result,
                       p->coefficient * q->coefficient,
                       p->exponent + q->exponent);
            q = q->next;
        }
        p = p->next;
    }

    return result;
}


//------------------------------------------------------------------------------------
//Skips spaces while scanning a polynomial string
//------------------------------------------------------------------------------------

void skipSpaces(const string& line, int& index)
{
    while (index < (int)(line.length()) && line[index] == ' ')
    {
        index++;
    }
}


//------------------------------------------------------------------------------------
//Reads an integer from a polynomial string starting at the given index
//------------------------------------------------------------------------------------

bool readUnsignedInteger(const string& line, int& index, int& value)
{
    value = 0;
    int n = (line.length());

    if (index >= n || !isdigit(line[index]))
    {
        return false;
    }

    while (index < n && isdigit(line[index]))
    {
        int digit = line[index] - '0';

        if (value > (INT_MAX - digit) / 10)
        {
            return false;
        }

        value = value * 10 + digit;
        index++;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Parses one term from a polynomial string
//------------------------------------------------------------------------------------

bool parseTerm(const string& line, int& index, int& coefficient, int& exponent)
{
    int n = (line.length());
    skipSpaces(line, index);

    int sign = 1;
    if (index < n && line[index] == '+')
    {
        sign = 1;
        index++;
    }
    else if (index < n && line[index] == '-')
    {
        sign = -1;
        index++;
    }

    skipSpaces(line, index);

    bool hasCoefficientDigits = false;
    int numericValue = 0;
    int tempIndex = index;

    if (tempIndex < n && isdigit(line[tempIndex]))
    {
        hasCoefficientDigits = true;
        if (!readUnsignedInteger(line, tempIndex, numericValue))
        {
            return false;
        }
    }

    skipSpaces(line, tempIndex);

    if (tempIndex < n && (line[tempIndex] == 'x' || line[tempIndex] == 'X'))
    {
        if (hasCoefficientDigits)
        {
            coefficient = sign * numericValue;
        }
        else
        {
            coefficient = sign;
        }

        exponent = 1;
        tempIndex++;
        skipSpaces(line, tempIndex);

        if (tempIndex < n && line[tempIndex] == '^')
        {
            tempIndex++;
            skipSpaces(line, tempIndex);

            int exponentSign = 1;
            if (tempIndex < n && line[tempIndex] == '+')
            {
                exponentSign = 1;
                tempIndex++;
            }
            else if (tempIndex < n && line[tempIndex] == '-')
            {
                exponentSign = -1;
                tempIndex++;
            }

            skipSpaces(line, tempIndex);

            int exponentValue = 0;
            if (!readUnsignedInteger(line, tempIndex, exponentValue))
            {
                return false;
            }

            exponent = exponentSign * exponentValue;
        }

        index = tempIndex;
        return true;
    }

    if (hasCoefficientDigits)
    {
        coefficient = sign * numericValue;
        exponent = 0;
        index = tempIndex;
        return true;
    }

    return false;
}


//------------------------------------------------------------------------------------
//Parses a polynomial string into a linked list polynomial
//------------------------------------------------------------------------------------

bool parsePolynomial(const string& line, Polynomial& poly)
{
    poly = NULL;
    string cleaned = trim(line);

    if (cleaned.length() == 0)
    {
        return false;
    }

    int index = 0;
    int n = (cleaned.length());
    bool foundAtLeastOneTerm = false;

    while (index < n)
    {
        int coefficient = 0;
        int exponent = 0;

        if (!parseTerm(cleaned, index, coefficient, exponent))
        {
            clearPolynomial(poly);
            return false;
        }

        insertTerm(poly, coefficient, exponent);
        foundAtLeastOneTerm = true;

        skipSpaces(cleaned, index);
        if (index < n && cleaned[index] != '+' && cleaned[index] != '-')
        {
            clearPolynomial(poly);
            return false;
        }
    }

    if (!foundAtLeastOneTerm)
    {
        return false;
    }

    if (poly == NULL)
    {
        poly = createNode(0, 0);
    }

    return true;
}


//------------------------------------------------------------------------------------
//Outputs one term in polynomial format
//------------------------------------------------------------------------------------

void displayTerm(int coefficient, int exponent, bool firstTerm)
{
    if (!firstTerm)
    {
        if (coefficient > 0)
        {
            cout << " + ";
        }
        else
        {
            cout << " - ";
        }
    }
    else if (coefficient < 0)
    {
        cout << "-";
    }

    int absoluteCoefficient = coefficient;
    if (absoluteCoefficient < 0)
    {
        absoluteCoefficient = -absoluteCoefficient;
    }

    if (exponent == 0)
    {
        cout << absoluteCoefficient;
    }
    else
    {
        if (absoluteCoefficient != 1)
        {
            cout << absoluteCoefficient;
        }

        cout << "x";

        if (exponent != 1)
        {
            cout << "^" << exponent;
        }
    }
}


//------------------------------------------------------------------------------------
//Displays a polynomial without enclosing brackets
//------------------------------------------------------------------------------------

void displayPolynomial(const Polynomial poly)
{
    if (poly == NULL)
    {
        cout << "0";
        return;
    }

    ATerm* current = poly;
    bool firstTerm = true;

    while (current != NULL)
    {
        displayTerm(current->coefficient, current->exponent, firstTerm);
        firstTerm = false;
        current = current->next;
    }
}


//------------------------------------------------------------------------------------
//Displays a polynomial enclosed in square brackets
//------------------------------------------------------------------------------------

void displayBracketPolynomial(const Polynomial poly)
{
    cout << "[";
    displayPolynomial(poly);
    cout << "]";
}


//------------------------------------------------------------------------------------
//Displays the full sum expression and result
//------------------------------------------------------------------------------------

void displaySum(Polynomial polynomials[], int count)
{
    Polynomial runningSum = copyPolynomial(polynomials[0]);

    cout << endl;
    cout << "Sum = ";
    displayBracketPolynomial(polynomials[0]);

    for (int i = 1; i < count; i++)
    {
        cout << " + ";
        displayBracketPolynomial(polynomials[i]);

        Polynomial newSum = Add(runningSum, polynomials[i]);
        clearPolynomial(runningSum);
        runningSum = newSum;
    }

    cout << endl;
    cout << "    = ";
    displayPolynomial(runningSum);
    cout << endl << endl;

    clearPolynomial(runningSum);
}


//------------------------------------------------------------------------------------
//Displays the full product expression and result
//------------------------------------------------------------------------------------

void displayProduct(Polynomial polynomials[], int count)
{
    Polynomial runningProduct = copyPolynomial(polynomials[0]);

    cout << "Product = ";
    displayBracketPolynomial(polynomials[0]);

    for (int i = 1; i < count; i++)
    {
        cout << " * ";
        displayBracketPolynomial(polynomials[i]);

        Polynomial newProduct = Multiply(runningProduct, polynomials[i]);
        clearPolynomial(runningProduct);
        runningProduct = newProduct;
    }

    cout << endl;
    cout << "        = ";
    displayPolynomial(runningProduct);
    cout << endl << endl;

    clearPolynomial(runningProduct);
}


//------------------------------------------------------------------------------------
//Reads all polynomials from the user
//------------------------------------------------------------------------------------

void inputPolynomials(Polynomial polynomials[], int count)
{
    for (int i = 0; i < count; i++)
    {
        bool valid = false;
        string line;

        while (!valid)
        {
            cout << "Input polynomial " << (i + 1) << " -> ";
            getline(cin, line);

            if (parsePolynomial(line, polynomials[i]))
            {
                valid = true;
            }
            else
            {
                cout << "Invalid input. Please try again." << endl << endl;
            }
        }
    }
}


//------------------------------------------------------------------------------------
//Deletes all stored polynomials in the array
//------------------------------------------------------------------------------------

void clearPolynomialArray(Polynomial polynomials[], int count)
{
    for (int i = 0; i < count; i++)
    {
        clearPolynomial(polynomials[i]);
    }
}


//------------------------------------------------------------------------------------
//Runs the polynomial program
//------------------------------------------------------------------------------------

void runProgram()
{
    int polynomialCount = -1;

    while (polynomialCount != 0)
    {
        cout << endl;
        polynomialCount = readIntegerLine("Number of polynomials -> ", MIN_POLYNOMIALS, MAX_POLYNOMIALS);

        if (polynomialCount != 0)
        {
            Polynomial polynomials[MAX_POLYNOMIALS];
            for (int i = 0; i < MAX_POLYNOMIALS; i++)
            {
                polynomials[i] = NULL;
            }

            cout << endl;
            inputPolynomials(polynomials, polynomialCount);

            displaySum(polynomials, polynomialCount);
            displayProduct(polynomials, polynomialCount);

            clearPolynomialArray(polynomials, polynomialCount);
            cout << "----------------------------------------" << endl;
        }
    }
}