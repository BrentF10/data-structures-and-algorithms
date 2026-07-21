#include <iostream>
#include <string>
#include <climits>

using namespace std;

const int MIN_MAIN_CHOICE = 0;
const int MAX_MAIN_CHOICE = 1;

struct TreeNode
{
    char data;
    TreeNode* left;
    TreeNode* right;
};

struct QueueNode
{
    TreeNode* data;
    QueueNode* next;
};

struct TreeQueue
{
    QueueNode* front;
    QueueNode* rear;
};

typedef TreeNode* BinaryTree;


//------------------------------------------------------------------------------------
//Function Prototypes
//------------------------------------------------------------------------------------

string trim(const string& line);
bool parseInteger(const string& line, int& value);
int readIntegerLine(const string& prompt, int minValue, int maxValue);
bool isValidNodeCharacter(char ch);
TreeNode* createTreeNode(char value);
void clearTree(BinaryTree& root);
string removeSpaces(const string& line);
bool buildTreeHelper(const string& treeString, int& index, BinaryTree& root);
bool BuildTree(const string& treeString, BinaryTree& root);
bool isBSTHelper(BinaryTree root, char minValue, char maxValue, bool hasMin, bool hasMax);
bool IsBST(BinaryTree root);
int node_count(BinaryTree root);
int height(BinaryTree root);
bool IsFullBT(BinaryTree root);
void initializeQueue(TreeQueue& q);
bool isEmptyQueue(const TreeQueue& q);
void enqueue(TreeQueue& q, TreeNode* value);
bool dequeue(TreeQueue& q, TreeNode*& value);
void clearQueue(TreeQueue& q);
bool IsCompleteBT(BinaryTree root);
void displayPreorder(BinaryTree root);
void displayInorder(BinaryTree root);
void displayPostorder(BinaryTree root);
void displayLevelOrder(BinaryTree root);
void displayTreeInformation(BinaryTree root);
void processTreeString(const string& treeString);
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

    if (i >= n || line[i] < '0' || line[i] > '9')
    {
        return false;
    }

    while (i < n && line[i] >= '0' && line[i] <= '9')
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
//Determines whether a character can be stored in a tree node
//------------------------------------------------------------------------------------

bool isValidNodeCharacter(char ch)
{
    return (ch != '.' && ch != ' ');
}


//------------------------------------------------------------------------------------
//Creates one binary tree node
//------------------------------------------------------------------------------------

TreeNode* createTreeNode(char value)
{
    TreeNode* nn = new TreeNode;
    nn->data = value;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}


//------------------------------------------------------------------------------------
//Deletes all nodes in a binary tree
//------------------------------------------------------------------------------------

void clearTree(BinaryTree& root)
{
    if (root != NULL)
    {
        clearTree(root->left);
        clearTree(root->right);
        delete root;
        root = NULL;
    }
}


//------------------------------------------------------------------------------------
//Removes spaces from the input string
//------------------------------------------------------------------------------------

string removeSpaces(const string& line)
{
    string result = "";

    for (int i = 0; i < (int)(line.length()); i++)
    {
        if (line[i] != ' ')
        {
            result += line[i];
        }
    }

    return result;
}


//------------------------------------------------------------------------------------
//Builds one subtree from a preorder string with periods for empty subtrees
//------------------------------------------------------------------------------------

bool buildTreeHelper(const string& treeString, int& index, BinaryTree& root)
{
    if (index >= (int)(treeString.length()))
    {
        root = NULL;
        return false;
    }

    char ch = treeString[index];
    index++;

    if (ch == '.')
    {
        root = NULL;
        return true;
    }

    if (!isValidNodeCharacter(ch))
    {
        root = NULL;
        return false;
    }

    root = createTreeNode(ch);

    if (!buildTreeHelper(treeString, index, root->left))
    {
        clearTree(root);
        return false;
    }

    if (!buildTreeHelper(treeString, index, root->right))
    {
        clearTree(root);
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Builds a binary tree from a preorder string
//------------------------------------------------------------------------------------

bool BuildTree(const string& treeString, BinaryTree& root)
{
    clearTree(root);

    string cleaned = removeSpaces(trim(treeString));

    if (cleaned.length() == 0)
    {
        return false;
    }

    int index = 0;

    if (!buildTreeHelper(cleaned, index, root))
    {
        clearTree(root);
        return false;
    }

    if (index != (int)(cleaned.length()))
    {
        clearTree(root);
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------------
//Determines whether a binary tree is a binary search tree using value limits
//------------------------------------------------------------------------------------

bool isBSTHelper(BinaryTree root, char minValue, char maxValue, bool hasMin, bool hasMax)
{
    if (root == NULL)
    {
        return true;
    }

    if (hasMin && root->data <= minValue)
    {
        return false;
    }

    if (hasMax && root->data >= maxValue)
    {
        return false;
    }

    return isBSTHelper(root->left, minValue, root->data, hasMin, true) &&
           isBSTHelper(root->right, root->data, maxValue, true, hasMax);
}


//------------------------------------------------------------------------------------
//Determines whether a binary tree is a binary search tree
//------------------------------------------------------------------------------------

bool IsBST(BinaryTree root)
{
    return isBSTHelper(root, '\0', '\0', false, false);
}


//------------------------------------------------------------------------------------
//Counts the number of nodes in a binary tree
//------------------------------------------------------------------------------------

int node_count(BinaryTree root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1 + node_count(root->left) + node_count(root->right);
}


//------------------------------------------------------------------------------------
//Returns the height of a binary tree
//------------------------------------------------------------------------------------

int height(BinaryTree root)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
    {
        return 1 + leftHeight;
    }
    else
    {
        return 1 + rightHeight;
    }
}


//------------------------------------------------------------------------------------
//Determines whether a binary tree is full
//------------------------------------------------------------------------------------

bool IsFullBT(BinaryTree root)
{
    if (root == NULL)
    {
        return true;
    }

    if (root->left == NULL && root->right == NULL)
    {
        return true;
    }

    if (root->left != NULL && root->right != NULL)
    {
        return IsFullBT(root->left) && IsFullBT(root->right);
    }

    return false;
}


//------------------------------------------------------------------------------------
//Initializes a tree pointer queue
//------------------------------------------------------------------------------------

void initializeQueue(TreeQueue& q)
{
    q.front = NULL;
    q.rear = NULL;
}


//------------------------------------------------------------------------------------
//Determines whether the queue is empty
//------------------------------------------------------------------------------------

bool isEmptyQueue(const TreeQueue& q)
{
    return (q.front == NULL);
}


//------------------------------------------------------------------------------------
//Adds one tree pointer to the rear of the queue
//------------------------------------------------------------------------------------

void enqueue(TreeQueue& q, TreeNode* value)
{
    QueueNode* nn = new QueueNode;
    nn->data = value;
    nn->next = NULL;

    if (q.rear == NULL)
    {
        q.front = nn;
        q.rear = nn;
    }
    else
    {
        q.rear->next = nn;
        q.rear = nn;
    }
}


//------------------------------------------------------------------------------------
//Removes one tree pointer from the front of the queue
//------------------------------------------------------------------------------------

bool dequeue(TreeQueue& q, TreeNode*& value)
{
    if (q.front == NULL)
    {
        return false;
    }

    QueueNode* temp = q.front;
    value = q.front->data;
    q.front = q.front->next;

    if (q.front == NULL)
    {
        q.rear = NULL;
    }

    delete temp;
    return true;
}


//------------------------------------------------------------------------------------
//Deletes all nodes in the queue
//------------------------------------------------------------------------------------

void clearQueue(TreeQueue& q)
{
    TreeNode* tempValue = NULL;

    while (dequeue(q, tempValue))
    {
    }
}


//------------------------------------------------------------------------------------
//Determines whether a binary tree is complete
//------------------------------------------------------------------------------------

bool IsCompleteBT(BinaryTree root)
{
    if (root == NULL)
    {
        return true;
    }

    TreeQueue q;
    initializeQueue(q);
    enqueue(q, root);

    bool foundMissingChild = false;
    TreeNode* current = NULL;

    while (dequeue(q, current))
    {
        if (current->left != NULL)
        {
            if (foundMissingChild)
            {
                clearQueue(q);
                return false;
            }

            enqueue(q, current->left);
        }
        else
        {
            foundMissingChild = true;
        }

        if (current->right != NULL)
        {
            if (foundMissingChild)
            {
                clearQueue(q);
                return false;
            }

            enqueue(q, current->right);
        }
        else
        {
            foundMissingChild = true;
        }
    }

    return true;
}


//------------------------------------------------------------------------------------
//Displays a binary tree in preorder
//------------------------------------------------------------------------------------

void displayPreorder(BinaryTree root)
{
    if (root != NULL)
    {
        cout << root->data;
        displayPreorder(root->left);
        displayPreorder(root->right);
    }
}


//------------------------------------------------------------------------------------
//Displays a binary tree in inorder
//------------------------------------------------------------------------------------

void displayInorder(BinaryTree root)
{
    if (root != NULL)
    {
        displayInorder(root->left);
        cout << root->data;
        displayInorder(root->right);
    }
}


//------------------------------------------------------------------------------------
//Displays a binary tree in postorder
//------------------------------------------------------------------------------------

void displayPostorder(BinaryTree root)
{
    if (root != NULL)
    {
        displayPostorder(root->left);
        displayPostorder(root->right);
        cout << root->data;
    }
}


//------------------------------------------------------------------------------------
//Displays a binary tree in level order
//------------------------------------------------------------------------------------

void displayLevelOrder(BinaryTree root)
{
    if (root == NULL)
    {
        return;
    }

    TreeQueue q;
    initializeQueue(q);
    enqueue(q, root);

    TreeNode* current = NULL;

    while (dequeue(q, current))
    {
        cout << current->data;

        if (current->left != NULL)
        {
            enqueue(q, current->left);
        }

        if (current->right != NULL)
        {
            enqueue(q, current->right);
        }
    }
}


//------------------------------------------------------------------------------------
//Displays the traversals and properties of a binary tree
//------------------------------------------------------------------------------------

void displayTreeInformation(BinaryTree root)
{
    cout << endl;

    cout << "Preorder    = ";
    displayPreorder(root);
    cout << endl;

    cout << "Inorder     = ";
    displayInorder(root);
    cout << endl;

    cout << "Postorder   = ";
    displayPostorder(root);
    cout << endl;

    cout << "Level-order = ";
    displayLevelOrder(root);
    cout << endl << endl;

    cout << "Node count  = " << node_count(root) << endl;
    cout << "Height      = " << height(root) << endl;

    if (IsBST(root))
    {
        cout << "Is BST      = TRUE" << endl;
    }
    else
    {
        cout << "Is BST      = FALSE" << endl;
    }

    if (IsFullBT(root))
    {
        cout << "Is Full     = TRUE" << endl;
    }
    else
    {
        cout << "Is Full     = FALSE" << endl;
    }

    if (IsCompleteBT(root))
    {
        cout << "Is Complete = TRUE" << endl;
    }
    else
    {
        cout << "Is Complete = FALSE" << endl;
    }

    cout << endl;
}


//------------------------------------------------------------------------------------
//Processes one preorder tree string
//------------------------------------------------------------------------------------

void processTreeString(const string& treeString)
{
    BinaryTree root = NULL;

    if (!BuildTree(treeString, root))
    {
        cout << endl;
        cout << "Invalid tree representation." << endl << endl;
        return;
    }

    displayTreeInformation(root);
    clearTree(root);
}


//------------------------------------------------------------------------------------
//Runs the binary tree program
//------------------------------------------------------------------------------------

void runProgram()
{
    int mainChoice = -1;

    while (mainChoice != 0)
    {
        cout << endl;
        cout << "Main Menu" << endl;
        cout << "0. Quit" << endl;
        cout << "1. Build a binary tree from preorder input" << endl;

        mainChoice = readIntegerLine("Enter choice -> ", MIN_MAIN_CHOICE, MAX_MAIN_CHOICE);

        if (mainChoice == 1)
        {
            string treeString = "";
            cout << endl;
            cout << "Use a period for an empty subtree." << endl;
            cout << "Example: AB..C.." << endl;
            cout << "Input preorder tree string -> ";
            getline(cin, treeString);

            processTreeString(treeString);
        }
    }
}
