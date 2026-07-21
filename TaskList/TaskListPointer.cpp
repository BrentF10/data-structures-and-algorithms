#include <iostream>
#include <string>

using namespace std;

const int MAX_ITEMS = 8;

struct node
{
    string task;
    node* next;
};

void displayMenu();
int performOption(node **head);
int optionValid(node *head);
int countNodes(node *head);
void printTaskCount(node *head);
void printTasksForward(node *head);
void printTasksReverse(node *head);
void printTasksForwardOption(node *head);
void printTasksReverseOption(node *head);
void printReverseHelper(node *head, int &num);
void insertAtStart(node **head, string x);
void insertAtEnd(node **head, string x);
void insertAtPosition(node **head, int position, string x);
void addNewNode(node **head);
bool removeNode(node **head);
int stringSize(string input);
int stringToint(string input);
bool isInterger(string posSTR);
bool parseOneToken(string line, string &tokenOut);
bool parseTwoTokens(string line, string &taskOut, string &posOut);
bool addValidation(node **head, string posSTR);
bool removeValidation(node *head, string posSTR);
bool hasNodeBefore(node *head, int position);
bool hasNodeAt(node *head, int position);

int main()
{
    node *head = NULL;
    int option;

    do
    {
        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << endl;

        displayMenu();
        option = performOption(&head);

    } while (option != 6);

    return 0;
}


// -----------------------------------------------------------------------
// Prints the numbered list of menu options (1-6) for the user to choose.
// -----------------------------------------------------------------------


void displayMenu()
{
    cout << "1. Add task X to the list at a particular position p" << endl;
    cout << "2. Delete task X from the task list at position q" << endl;
    cout << "3. Print the number of tasks in the task list" << endl;
    cout << "4. Print all tasks in the task list in the order of position" << endl;
    cout << "5. Print all tasks in the task list in reverse order of position" << endl;
    cout << "6. Quit" << endl;
    cout << endl;
}


// -----------------------------------------------------------------------
// Reads a validated menu option and executes the corresponding action
// (add, remove, count, print forward, print reverse, or quit).
// Returns the selected option number.
// -----------------------------------------------------------------------


int performOption(node **head)
{
    int option = optionValid(*head);

    switch (option)
    {
        case 1:
            addNewNode(head);
            printTaskCount(*head);
            printTasksForward(*head);
            printTasksReverse(*head);
            cout << endl;
            break;

        case 2:
        {
            bool deleted = removeNode(head);

            printTaskCount(*head);

            if (deleted)
            {
                printTasksForward(*head);
                printTasksReverse(*head);
            }
            cout << endl;
            break;
        }

        case 3:
            printTaskCount(*head);
            cout << endl;
            break;

        case 4:
            printTasksForwardOption(*head);
            cout << endl;
            break;

        case 5:
            printTasksReverseOption(*head);
            cout << endl;
            break;

        case 6:
            cout << "Goodbye." << endl;
            break;
    }

    return option;
}


// -----------------------------------------------------------------------
// Repeatedly prompts the user until a valid menu option (1-6) is entered.
// Rejects empty input, non-integers, out-of-range values, and option 1
// when the list is already full. Returns the valid integer option.
// -----------------------------------------------------------------------


int optionValid(node *head)
{
    string line;
    string token;
    int option;

    while (true)
    {
        cout << "Select an option (1-6): ";
        getline(cin, line);

        if (stringSize(line) == 0)
        {
            cout << "Invalid input: you entered nothing." << endl << endl;
            continue;
        }

        if (!parseOneToken(line, token))
        {
            cout << "Invalid input: enter exactly ONE number (1-6)." << endl << endl;
            continue;
        }

        if (!isInterger(token))
        {
            cout << "Invalid input. Please enter an integer 1-6." << endl << endl;
            continue;
        }

        option = stringToint(token);

        if (option < 1 || option > 6)
        {
            cout << "Invalid input. You must select an option between 1-6." << endl << endl;
            continue;
        }

        if (option == 1 && countNodes(head) >= MAX_ITEMS)
        {
            cout << "The list is full. Delete an item before adding another one." << endl << endl;
            continue;
        }

        return option;
    }
}


// -----------------------------------------------------------------------
// Traverses the list and returns the total number of nodes present.
// -----------------------------------------------------------------------


int countNodes(node *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}


// -----------------------------------------------------------------------
// Prints the current number of tasks in the list to the console.
// -----------------------------------------------------------------------


void printTaskCount(node *head)
{
    cout << "Number of tasks: " << countNodes(head) << endl;
}


// -----------------------------------------------------------------------
// Prints all tasks in forward positional order, each preceded by its
// 1-based index. Prints a blank line if the list is empty.
// -----------------------------------------------------------------------


void printTasksForward(node *head)
{
    if (head == NULL)
    {
        cout << endl;
        return;
    }

    int i = 1;
    node *temp = head;
    while (temp != NULL)
    {
        cout << i << ": " << temp->task << " ";
        temp = temp->next;
        i++;
    }
    cout << endl;
}


// -----------------------------------------------------------------------
// Recursive helper for printTasksReverse. Walks to the end of the list,
// then prints each task with a descending position number on the way back.
// -----------------------------------------------------------------------


void printReverseHelper(node *head, int &num)
{
    if (head == NULL)
    {
        return;
    }

    printReverseHelper(head->next, num);
    cout << num << ": " << head->task << " ";
    num--;
}


// -----------------------------------------------------------------------
// Prints all tasks in reverse positional order using a recursive helper.
// Prints a blank line if the list is empty.
// -----------------------------------------------------------------------


void printTasksReverse(node *head)
{
    if (head == NULL)
    {
        cout << endl;
        return;
    }

    int num = countNodes(head);
    printReverseHelper(head, num);
    cout << endl;
}


// -----------------------------------------------------------------------
// Menu option 4 wrapper for printTasksForward. Displays an "empty list"
// message instead of a blank line when no tasks exist.
// -----------------------------------------------------------------------


void printTasksForwardOption(node *head)
{
    if (head == NULL)
    {
        cout << "The list is empty." << endl;
        return;
    }
    printTasksForward(head);
}


// -----------------------------------------------------------------------
// Menu option 5 wrapper for printTasksReverse. Displays an "empty list"
// message instead of a blank line when no tasks exist.
// -----------------------------------------------------------------------


void printTasksReverseOption(node *head)
{
    if (head == NULL)
    {
        cout << "The list is empty." << endl;
        return;
    }
    printTasksReverse(head);
}


// -----------------------------------------------------------------------
// Creates a new node with task x and inserts it at the front of the list,
// updating the head pointer accordingly.
// -----------------------------------------------------------------------


void insertAtStart(node **head, string x)
{
    node *newNode = new node();
    newNode->task = x;
    newNode->next = *head;
    *head = newNode;
}


// -----------------------------------------------------------------------
// Creates a new node with task x and appends it to the end of the list.
// If the list is empty, the new node becomes the head.
// -----------------------------------------------------------------------


void insertAtEnd(node **head, string x)
{
    node *newNode = new node();
    newNode->task = x;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    node *last = *head;
    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = newNode;
}


// -----------------------------------------------------------------------
// Creates a new node with task x and splices it into the list at the
// given 1-based position, shifting later nodes forward by one.
// -----------------------------------------------------------------------


void insertAtPosition(node **head, int position, string x)
{
    node *newNode = new node();
    newNode->task = x;

    node *previous = *head;
    for (int i = 0; i < position - 2; i++)
    {
        previous = previous->next;
    }

    newNode->next = previous->next;
    previous->next = newNode;
}


// -----------------------------------------------------------------------
// Prompts the user for a task name and position, validates both, then
// inserts the new task node at the specified position in the list.
// -----------------------------------------------------------------------


void addNewNode(node **head)
{
    string task;
    string posSTR;
    int position;
    string line;

    while (true)
    {
        cout << "Please enter task and position: ";
        getline(cin, line);

        if (stringSize(line) == 0)
        {
            cout << "Invalid input: you entered nothing." << endl << endl;
            continue;
        }

        if (!parseTwoTokens(line, task, posSTR))
        {
            cout << "Invalid input: enter exactly TWO items." << endl << endl;
            continue;
        }

        if (!addValidation(head, posSTR))
        {
            cout << "Invalid position." << endl << endl;
            continue;
        }

        break;
    }

    position = stringToint(posSTR);

    if (position == 1)
    {
        insertAtStart(head, task);
    }
    else
    {
        insertAtPosition(head, position, task);
    }
}


// -----------------------------------------------------------------------
// Prompts the user for a position, validates it, then removes and frees
// the node at that position. Prints the deleted task name. Returns true
// if a node was deleted, or false if the list was empty.
// -----------------------------------------------------------------------


bool removeNode(node **head)
{
    string line;
    string posSTR;
    int position;

    if (*head == NULL)
    {
        cout << "Cannot delete from an empty list." << endl;
        return false;
    }

    while (true)
    {
        cout << "Enter position to remove: ";
        getline(cin, line);

        if (stringSize(line) == 0)
        {
            cout << "Invalid input: you entered nothing." << endl << endl;
            continue;
        }

        if (!parseOneToken(line, posSTR))
        {
            cout << "Invalid input: enter exactly ONE item." << endl << endl;
            continue;
        }

        if (!removeValidation(*head, posSTR))
        {
            cout << "Invalid position." << endl << endl;
            continue;
        }

        break;
    }

    position = stringToint(posSTR);

    if (position == 1)
    {
        node *toDelete = *head;
        string deletedTask = toDelete->task;

        *head = (*head)->next;
        delete toDelete;

        cout << endl;
        cout << deletedTask << " was deleted." << endl;
        return true;
    }

    node *current = *head;
    for (int i = 0; i < position - 2; i++)
    {
        current = current->next;
    }

    node *toDelete = current->next;
    string deletedTask = toDelete->task;

    current->next = toDelete->next;
    delete toDelete;

    cout << endl;
    cout << deletedTask << " was deleted." << endl;
    return true;
}


// -----------------------------------------------------------------------
// Returns the number of characters in the given string by counting until
// the null terminator is reached.
// -----------------------------------------------------------------------


int stringSize(string input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        i++;
    }
    return i;
}


// -----------------------------------------------------------------------
// Returns true if every character in posSTR is a digit (0-9), indicating
// the string represents a non-negative integer. Returns false otherwise.
// -----------------------------------------------------------------------


bool isInterger(string posSTR)
{
    if (stringSize(posSTR) == 0)
    {
        return false;
    }

    for (int i = 0; i < stringSize(posSTR); i++)
    {
        if (posSTR[i] < '0' || posSTR[i] > '9')
        {
            return false;
        }
    }
    return true;
}


// -----------------------------------------------------------------------
// Converts a string of digit characters to its integer equivalent and
// returns the result.
// -----------------------------------------------------------------------


int stringToint(string input)
{
    int value = 0;
    for (int c = 0; c < stringSize(input); c++)
    {
        value = value * 10 + (input[c] - '0');
    }
    return value;
}


// -----------------------------------------------------------------------
// Parses a line and extracts exactly one whitespace-delimited token into
// tokenOut. Returns true on success, or false if the line is empty,
// blank, or contains more than one token.
// -----------------------------------------------------------------------


bool parseOneToken(string line, string &tokenOut)
{
    int n = stringSize(line);
    int i = 0;

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i >= n)
    {
        return false;
    }

    tokenOut = "";
    while (i < n && line[i] != ' ')
    {
        tokenOut += line[i];
        i++;
    }

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i < n)
    {
        return false;
    }

    return true;
}


// -----------------------------------------------------------------------
// Parses a line and extracts exactly two whitespace-delimited tokens into
// taskOut and posOut. Returns true on success, or false if the line does
// not contain exactly two tokens.
// -----------------------------------------------------------------------


bool parseTwoTokens(string line, string &taskOut, string &posOut)
{
    int n = stringSize(line);
    int i = 0;

    while (i < n && line[i] == ' ')
    {
        i++;
    }
    if (i >= n) return false;

    taskOut = "";
    while (i < n && line[i] != ' ')
    {
        taskOut += line[i];
        i++;
    }

    while (i < n && line[i] == ' ')
    {
        i++;
    }
    if (i >= n) return false;

    posOut = "";
    while (i < n && line[i] != ' ')
    {
        posOut += line[i];
        i++;
    }

    while (i < n && line[i] == ' ')
    {
        i++;
    }

    if (i < n) return false;

    return true;
}


// -----------------------------------------------------------------------
// Returns true if a node exists at position - 1 (i.e., there is a valid
// predecessor for an insertion at the given position). Position 1 always
// returns true since no predecessor is needed.
// -----------------------------------------------------------------------


bool hasNodeBefore(node *head, int position)
{
    if (position == 1)
    {
        return true;
    }

    node *temp = head;
    for (int i = 0; i < position - 2; i++)
    {
        if (temp == NULL)
        {
            return false;
        }
        temp = temp->next;
    }

    return temp != NULL;
}


// -----------------------------------------------------------------------
// Validates a position string for an add operation. Returns false if the
// value is not an integer, is out of range, the list is full, or there is
// no existing node before the target position.
// -----------------------------------------------------------------------


bool addValidation(node **head, string posSTR)
{
    int position;

    if (!isInterger(posSTR))
    {
        return false;
    }

    position = stringToint(posSTR);

    if (position < 1 || position > MAX_ITEMS)
    {
        return false;
    }

    if (countNodes(*head) >= MAX_ITEMS)
    {
        return false;
    }

    if (!hasNodeBefore(*head, position))
    {
        return false;
    }

    return true;
}


// -----------------------------------------------------------------------
// Returns true if a node actually exists at the given 1-based position
// in the list, or false if the position is beyond the last node.
// -----------------------------------------------------------------------


bool hasNodeAt(node *head, int position)
{
    node *temp = head;

    for (int i = 0; i < position - 1; i++)
    {
        if (temp == NULL)
        {
            return false;
        }
        temp = temp->next;
    }

    return temp != NULL;
}


// -----------------------------------------------------------------------
// Validates a position string for a remove operation. Returns false if
// the value is not an integer, is out of range, or no node exists at
// that position.
// -----------------------------------------------------------------------


bool removeValidation(node *head, string posSTR)
{
    int position;

    if (!isInterger(posSTR))
    {
        return false;
    }

    position = stringToint(posSTR);

    if (position < 1 || position > MAX_ITEMS)
    {
        return false;
    }

    if (!hasNodeAt(head, position))
    {
        return false;
    }

    return true;
}