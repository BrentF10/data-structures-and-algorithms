#include <iostream>
#include <string>
#include <cctype>
#include <climits>

using namespace std;

const int MIN_MAIN_CHOICE = 0;
const int MAX_MAIN_CHOICE = 2;
const int MIN_SUB_CHOICE = 0;
const int MAX_SUB_CHOICE = 2;

struct CharNode
{
    char data;
    CharNode* next;
};

struct IntNode
{
    int data;
    IntNode* next;
};

struct ExprNode
{
    char data;
    ExprNode* left;
    ExprNode* right;
};

struct TreeStackNode
{
    ExprNode* data;
    TreeStackNode* next;
};


//------------------------------------------------------------------------------------
//Function Prototypes
//------------------------------------------------------------------------------------

string trim(const string& line);
bool parseInteger(const string& line, int& value);
int readIntegerLine(const string& prompt, int minValue, int maxValue);
bool isBase36Operand(char ch);
bool isInfixOperand(char ch);
bool isOperator(char ch);
int precedence(char op);
char toUpperCharacter(char ch);
int base36Value(char ch);
string base36String(int value);
void pushChar(CharNode*& top, char value);
bool popChar(CharNode*& top, char& value);
bool peekChar(const CharNode* top, char& value);
bool isEmptyCharStack(const CharNode* top);
void clearCharStack(CharNode*& top);
void pushInt(IntNode*& top, int value);
bool popInt(IntNode*& top, int& value);
bool isEmptyIntStack(const IntNode* top);
void clearIntStack(IntNode*& top);
ExprNode* createExprNode(char value);
void pushTreeNode(TreeStackNode*& top, ExprNode* value);
bool popTreeNode(TreeStackNode*& top, ExprNode*& value);
bool isEmptyTreeStack(const TreeStackNode* top);
void clearTreeStack(TreeStackNode*& top);
void clearExpressionTree(ExprNode*& root);
bool infixToPostfix(const string& infix, string& postfix);
bool evaluatePostfix(const string& postfix, int& result);
bool buildExpressionTreeFromPostfix(const string& postfix, ExprNode*& root);
void displayPreorder(const ExprNode* root);
void displayInorder(const ExprNode* root);
void displayPostorder(const ExprNode* root);
void displayExpressionValue(int value);
void processInfixExpression(const string& infix, int subChoice);
void processPostfixExpression(const string& postfix, int subChoice);
void infixMenu();
void postfixMenu();
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

    if (i >= n || !isdigit((unsigned char)(line[i])))
    {
        return false;
    }

    while (i < n && isdigit((unsigned char)(line[i])))
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
//Determines whether a character is a base 36 operand
//------------------------------------------------------------------------------------

bool isBase36Operand(char ch)
{
    ch = toUpperCharacter(ch);
    return ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z'));
}


//------------------------------------------------------------------------------------
//Determines whether a character is a valid infix operand
//------------------------------------------------------------------------------------

bool isInfixOperand(char ch)
{
    ch = toUpperCharacter(ch);
    return ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z'));
}


//------------------------------------------------------------------------------------
//Determines whether a character is an arithmetic operator
//------------------------------------------------------------------------------------

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}


//------------------------------------------------------------------------------------
//Returns the precedence of an operator
//------------------------------------------------------------------------------------

int precedence(char op)
{
    if (op == '*' || op == '/')
    {
        return 2;
    }

    if (op == '+' || op == '-')
    {
        return 1;
    }

    return 0;
}


//------------------------------------------------------------------------------------
//Converts a lowercase letter to uppercase
//------------------------------------------------------------------------------------

char toUpperCharacter(char ch)
{
    return (char)(toupper((unsigned char)(ch)));
}


//------------------------------------------------------------------------------------
//Returns the base 36 numeric value of an operand
//------------------------------------------------------------------------------------

int base36Value(char ch)
{
    ch = toUpperCharacter(ch);

    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }

    return 10 + (ch - 'A');
}


//------------------------------------------------------------------------------------
//Converts a base 10 integer to a base 36 string
//------------------------------------------------------------------------------------

string base36String(int value)
{
    if (value == 0)
    {
        return "0";
    }

    bool negative = false;
    if (value < 0)
    {
        negative = true;
        value = -value;
    }

    string result = "";

    while (value > 0)
    {
        int digit = value % 36;

        if (digit < 10)
        {
            result = (char)('0' + digit) + result;
        }
        else
        {
            result = (char)('A' + (digit - 10)) + result;
        }

        value /= 36;
    }

    if (negative)
    {
        result = "-" + result;
    }

    return result;
}


//------------------------------------------------------------------------------------
//Pushes one character onto the character stack
//------------------------------------------------------------------------------------

void pushChar(CharNode*& top, char value)
{
    CharNode* nn = new CharNode;
    nn->data = value;
    nn->next = top;
    top = nn;
}


//------------------------------------------------------------------------------------
//Pops one character from the character stack
//------------------------------------------------------------------------------------

bool popChar(CharNode*& top, char& value)
{
    if (top == NULL)
    {
        return false;
    }

    CharNode* temp = top;
    value = top->data;
    top = top->next;
    delete temp;
    return true;
}


//------------------------------------------------------------------------------------
//Reads the top character from the character stack
//------------------------------------------------------------------------------------

bool peekChar(const CharNode* top, char& value)
{
    if (top == NULL)
    {
        return false;
    }

    value = top->data;
    return true;
}


//------------------------------------------------------------------------------------
//Determines whether the character stack is empty
//------------------------------------------------------------------------------------

bool isEmptyCharStack(const CharNode* top)
{
    return (top == NULL);
}


//------------------------------------------------------------------------------------
//Deletes all nodes in the character stack
//------------------------------------------------------------------------------------

void clearCharStack(CharNode*& top)
{
    while (top != NULL)
    {
        CharNode* temp = top;
        top = top->next;
        delete temp;
    }
}


//------------------------------------------------------------------------------------
//Pushes one integer onto the integer stack
//------------------------------------------------------------------------------------

void pushInt(IntNode*& top, int value)
{
    IntNode* nn = new IntNode;
    nn->data = value;
    nn->next = top;
    top = nn;
}


//------------------------------------------------------------------------------------
//Pops one integer from the integer stack
//------------------------------------------------------------------------------------

bool popInt(IntNode*& top, int& value)
{
    if (top == NULL)
    {
        return false;
    }

    IntNode* temp = top;
    value = top->data;
    top = top->next;
    delete temp;
    return true;
}


//------------------------------------------------------------------------------------
//Determines whether the integer stack is empty
//------------------------------------------------------------------------------------

bool isEmptyIntStack(const IntNode* top)
{
    return (top == NULL);
}


//------------------------------------------------------------------------------------
//Deletes all nodes in the integer stack
//------------------------------------------------------------------------------------

void clearIntStack(IntNode*& top)
{
    while (top != NULL)
    {
        IntNode* temp = top;
        top = top->next;
        delete temp;
    }
}


//------------------------------------------------------------------------------------
//Creates one expression tree node
//------------------------------------------------------------------------------------

ExprNode* createExprNode(char value)
{
    ExprNode* nn = new ExprNode;
    nn->data = value;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}


//------------------------------------------------------------------------------------
//Pushes one tree node pointer onto the tree stack
//------------------------------------------------------------------------------------

void pushTreeNode(TreeStackNode*& top, ExprNode* value)
{
    TreeStackNode* nn = new TreeStackNode;
    nn->data = value;
    nn->next = top;
    top = nn;
}


//------------------------------------------------------------------------------------
//Pops one tree node pointer from the tree stack
//------------------------------------------------------------------------------------

bool popTreeNode(TreeStackNode*& top, ExprNode*& value)
{
    if (top == NULL)
    {
        return false;
    }

    TreeStackNode* temp = top;
    value = top->data;
    top = top->next;
    delete temp;
    return true;
}


//------------------------------------------------------------------------------------
//Determines whether the tree stack is empty
//------------------------------------------------------------------------------------

bool isEmptyTreeStack(const TreeStackNode* top)
{
    return (top == NULL);
}


//------------------------------------------------------------------------------------
//Deletes all nodes in the tree stack
//------------------------------------------------------------------------------------

void clearTreeStack(TreeStackNode*& top)
{
    while (top != NULL)
    {
        TreeStackNode* temp = top;
        top = top->next;
        delete temp;
    }
}


//------------------------------------------------------------------------------------
//Deletes all nodes in an expression tree
//------------------------------------------------------------------------------------

void clearExpressionTree(ExprNode*& root)
{
    if (root != NULL)
    {
        clearExpressionTree(root->left);
        clearExpressionTree(root->right);
        delete root;
        root = NULL;
    }
}


//------------------------------------------------------------------------------------
//Converts a valid infix expression into postfix form
//------------------------------------------------------------------------------------

bool infixToPostfix(const string& infix, string& postfix)
{
    postfix = "";
    string cleaned = trim(infix);

    if (cleaned.length() == 0)
    {
        return false;
    }

    CharNode* operatorStack = NULL;
    bool expectOperand = true;
    int openParenthesisCount = 0;

    for (int i = 0; i < (int)(cleaned.length()); i++)
    {
        char ch = cleaned[i];

        if (ch == ' ')
        {
            continue;
        }

        ch = toUpperCharacter(ch);

        if (isInfixOperand(ch))
        {
            if (!expectOperand)
            {
                clearCharStack(operatorStack);
                postfix = "";
                return false;
            }

            postfix += ch;
            expectOperand = false;
        }
        else if (ch == '(')
        {
            if (!expectOperand)
            {
                clearCharStack(operatorStack);
                postfix = "";
                return false;
            }

            pushChar(operatorStack, ch);
            openParenthesisCount++;
        }
        else if (ch == ')')
        {
            if (expectOperand || openParenthesisCount == 0)
            {
                clearCharStack(operatorStack);
                postfix = "";
                return false;
            }

            char topOperator = '\0';
            while (peekChar(operatorStack, topOperator) && topOperator != '(')
            {
                popChar(operatorStack, topOperator);
                postfix += topOperator;
            }

            if (!popChar(operatorStack, topOperator) || topOperator != '(')
            {
                clearCharStack(operatorStack);
                postfix = "";
                return false;
            }

            openParenthesisCount--;
            expectOperand = false;
        }
        else if (isOperator(ch))
        {
            if (expectOperand)
            {
                clearCharStack(operatorStack);
                postfix = "";
                return false;
            }

            char topOperator = '\0';
            while (peekChar(operatorStack, topOperator) && topOperator != '(' &&
                   precedence(topOperator) >= precedence(ch))
            {
                popChar(operatorStack, topOperator);
                postfix += topOperator;
            }

            pushChar(operatorStack, ch);
            expectOperand = true;
        }
        else
        {
            clearCharStack(operatorStack);
            postfix = "";
            return false;
        }
    }

    if (expectOperand || openParenthesisCount != 0)
    {
        clearCharStack(operatorStack);
        postfix = "";
        return false;
    }

    char topOperator = '\0';
    while (popChar(operatorStack, topOperator))
    {
        if (topOperator == '(')
        {
            postfix = "";
            return false;
        }

        postfix += topOperator;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Evaluates a postfix expression in base 36
//------------------------------------------------------------------------------------

bool evaluatePostfix(const string& postfix, int& result)
{
    string cleaned = trim(postfix);

    if (cleaned.length() == 0)
    {
        return false;
    }

    IntNode* valueStack = NULL;
    int operandCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < (int)(cleaned.length()); i++)
    {
        char ch = cleaned[i];

        if (ch == ' ')
        {
            continue;
        }

        ch = toUpperCharacter(ch);

        if (isBase36Operand(ch))
        {
            pushInt(valueStack, base36Value(ch));
            operandCount++;
        }
        else if (isOperator(ch))
        {
            int rightValue = 0;
            int leftValue = 0;

            if (!popInt(valueStack, rightValue) || !popInt(valueStack, leftValue))
            {
                clearIntStack(valueStack);
                return false;
            }

            int newValue = 0;

            if (ch == '+')
            {
                newValue = leftValue + rightValue;
            }
            else if (ch == '-')
            {
                newValue = leftValue - rightValue;
            }
            else if (ch == '*')
            {
                newValue = leftValue * rightValue;
            }
            else
            {
                if (rightValue == 0)
                {
                    clearIntStack(valueStack);
                    return false;
                }

                newValue = leftValue / rightValue;
            }

            pushInt(valueStack, newValue);
            operatorCount++;
        }
        else
        {
            clearIntStack(valueStack);
            return false;
        }
    }

    if (operandCount == 0 || operatorCount != operandCount - 1)
    {
        clearIntStack(valueStack);
        return false;
    }

    if (!popInt(valueStack, result) || !isEmptyIntStack(valueStack))
    {
        clearIntStack(valueStack);
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Builds an expression tree from a postfix expression
//------------------------------------------------------------------------------------

bool buildExpressionTreeFromPostfix(const string& postfix, ExprNode*& root)
{
    root = NULL;
    string cleaned = trim(postfix);

    if (cleaned.length() == 0)
    {
        return false;
    }

    TreeStackNode* treeStack = NULL;
    int operandCount = 0;
    int operatorCount = 0;

    for (int i = 0; i < (int)(cleaned.length()); i++)
    {
        char ch = cleaned[i];

        if (ch == ' ')
        {
            continue;
        }

        ch = toUpperCharacter(ch);

        if (isBase36Operand(ch))
        {
            pushTreeNode(treeStack, createExprNode(ch));
            operandCount++;
        }
        else if (isOperator(ch))
        {
            ExprNode* rightNode = NULL;
            ExprNode* leftNode = NULL;

            if (!popTreeNode(treeStack, rightNode) || !popTreeNode(treeStack, leftNode))
            {
                if (rightNode != NULL)
                {
                    clearExpressionTree(rightNode);
                }
                clearTreeStack(treeStack);
                return false;
            }

            ExprNode* operatorNode = createExprNode(ch);
            operatorNode->left = leftNode;
            operatorNode->right = rightNode;
            pushTreeNode(treeStack, operatorNode);
            operatorCount++;
        }
        else
        {
            clearTreeStack(treeStack);
            return false;
        }
    }

    if (operandCount == 0 || operatorCount != operandCount - 1)
    {
        ExprNode* tempRoot = NULL;
        while (popTreeNode(treeStack, tempRoot))
        {
            clearExpressionTree(tempRoot);
        }
        return false;
    }

    if (!popTreeNode(treeStack, root) || !isEmptyTreeStack(treeStack))
    {
        clearExpressionTree(root);
        ExprNode* tempRoot = NULL;
        while (popTreeNode(treeStack, tempRoot))
        {
            clearExpressionTree(tempRoot);
        }
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Displays an expression tree in preorder
//------------------------------------------------------------------------------------

void displayPreorder(const ExprNode* root)
{
    if (root != NULL)
    {
        cout << root->data;
        displayPreorder(root->left);
        displayPreorder(root->right);
    }
}


//------------------------------------------------------------------------------------
//Displays an expression tree in inorder
//------------------------------------------------------------------------------------

void displayInorder(const ExprNode* root)
{
    if (root != NULL)
    {
        bool currentIsOperator = isOperator(root->data);

        if (currentIsOperator)
        {
            cout << "(";
        }

        displayInorder(root->left);
        cout << root->data;
        displayInorder(root->right);

        if (currentIsOperator)
        {
            cout << ")";
        }
    }
}


//------------------------------------------------------------------------------------
//Displays an expression tree in postorder
//------------------------------------------------------------------------------------

void displayPostorder(const ExprNode* root)
{
    if (root != NULL)
    {
        displayPostorder(root->left);
        displayPostorder(root->right);
        cout << root->data;
    }
}


//------------------------------------------------------------------------------------
//Displays the expression value in base 10 and base 36
//------------------------------------------------------------------------------------

void displayExpressionValue(int value)
{
    cout << "Value (base 10) = " << value << endl;
    cout << "Value (base 36) = " << base36String(value) << endl;
}


//------------------------------------------------------------------------------------
//Processes one infix expression request
//------------------------------------------------------------------------------------

void processInfixExpression(const string& infix, int subChoice)
{
    string postfix = "";

    if (!infixToPostfix(infix, postfix))
    {
        cout << endl;
        cout << "Invalid infix expression." << endl << endl;
        return;
    }

    cout << endl;
    cout << "Postfix expression = " << postfix << endl;

    if (subChoice == 2)
    {
        ExprNode* root = NULL;
        int value = 0;

        if (!buildExpressionTreeFromPostfix(postfix, root) || !evaluatePostfix(postfix, value))
        {
            clearExpressionTree(root);
            cout << "Unable to build the expression tree or evaluate the expression." << endl << endl;
            return;
        }

        cout << "Preorder  = ";
        displayPreorder(root);
        cout << endl;

        cout << "Inorder   = ";
        displayInorder(root);
        cout << endl;

        cout << "Postorder = ";
        displayPostorder(root);
        cout << endl;

        displayExpressionValue(value);
        cout << endl;

        clearExpressionTree(root);
    }
    else
    {
        cout << endl;
    }
}


//------------------------------------------------------------------------------------
//Processes one postfix expression request
//------------------------------------------------------------------------------------

void processPostfixExpression(const string& postfix, int subChoice)
{
    int value = 0;

    if (!evaluatePostfix(postfix, value))
    {
        cout << endl;
        cout << "Invalid postfix expression." << endl << endl;
        return;
    }

    cout << endl;

    if (subChoice == 1)
    {
        displayExpressionValue(value);
        cout << endl;
    }
    else
    {
        ExprNode* root = NULL;

        if (!buildExpressionTreeFromPostfix(postfix, root))
        {
            cout << "Invalid postfix expression." << endl << endl;
            return;
        }

        cout << "Preorder  = ";
        displayPreorder(root);
        cout << endl;

        cout << "Inorder   = ";
        displayInorder(root);
        cout << endl;

        cout << "Postorder = ";
        displayPostorder(root);
        cout << endl;

        displayExpressionValue(value);
        cout << endl;

        clearExpressionTree(root);
    }
}


//------------------------------------------------------------------------------------
//Displays the infix sub menu and processes the user's request
//------------------------------------------------------------------------------------

void infixMenu()
{
    int subChoice = -1;

    while (subChoice != 0)
    {
        cout << endl;
        cout << "Infix Menu" << endl;
        cout << "0. Return to previous menu" << endl;
        cout << "1. Print postfix expression only" << endl;
        cout << "2. Print postfix expression, traversals, and expression value" << endl;

        subChoice = readIntegerLine("Enter choice -> ", MIN_SUB_CHOICE, MAX_SUB_CHOICE);

        if (subChoice != 0)
        {
            string infix = "";
            cout << endl;
            cout << "Input infix expression -> ";
            getline(cin, infix);
            processInfixExpression(infix, subChoice);
        }
    }
}


//------------------------------------------------------------------------------------
//Displays the postfix sub menu and processes the user's request
//------------------------------------------------------------------------------------

void postfixMenu()
{
    int subChoice = -1;

    while (subChoice != 0)
    {
        cout << endl;
        cout << "Postfix Menu" << endl;
        cout << "0. Return to previous menu" << endl;
        cout << "1. Print expression value only" << endl;
        cout << "2. Print traversals and expression value" << endl;

        subChoice = readIntegerLine("Enter choice -> ", MIN_SUB_CHOICE, MAX_SUB_CHOICE);

        if (subChoice != 0)
        {
            string postfix = "";
            cout << endl;
            cout << "Input postfix expression -> ";
            getline(cin, postfix);
            processPostfixExpression(postfix, subChoice);
        }
    }
}


//------------------------------------------------------------------------------------
//Runs the infix and postfix expression program
//------------------------------------------------------------------------------------

void runProgram()
{
    int mainChoice = -1;

    while (mainChoice != 0)
    {
        cout << endl;
        cout << "Main Menu" << endl;
        cout << "0. Quit" << endl;
        cout << "1. Input an infix expression" << endl;
        cout << "2. Input a postfix expression" << endl;

        mainChoice = readIntegerLine("Enter choice -> ", MIN_MAIN_CHOICE, MAX_MAIN_CHOICE);

        if (mainChoice == 1)
        {
            infixMenu();
        }
        else if (mainChoice == 2)
        {
            postfixMenu();
        }
    }
}
