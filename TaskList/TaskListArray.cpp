#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int SIZE = 8;

void displayMenu();
string getOption();
int optionValid(string list[SIZE]);
void shift(string list[SIZE], int index);
void addTask(string list[SIZE], string task, int p);
void addValidation(string list[SIZE]);
void deleteTask(string list[SIZE], int q);
void deleteValidation(string list[SIZE]);
void printNumTask(string list[SIZE]);
void printAllTask(string list[SIZE]);
void reversePrint(string list[SIZE]);
int performOption(string list[SIZE]);
int stringToint(string input);
int stringSize(string input);
bool isEmpty(string list[SIZE], int i);


int main()
{
    string list[SIZE];
    int option = 7;

    while (option != 6)
    {
        displayMenu();
        option = performOption(list);
    }

    return 0;
}


//-------------------------------------------------------------------------------
//Converts string variables into integer variables
//-------------------------------------------------------------------------------

int stringToint(string input)
{
    int i = 0;
    for (int c = 0; c < stringSize(input); c++)
    {
        i = i * 10 + (input[c] - '0');

    }
    return i;
}


//Displays the menu options
void displayMenu()
{
    cout << "1. Add task X to the list at a particular position p" << endl;
    cout << "2. Delete task X from the task list at position q" << endl;
    cout << "3. Print the number of tasks in the task list" << endl;
    cout << "4. Print all tasks in the task list in the order of position" << endl;
    cout << "5. Print all tasks in the task list in reverse order of position" << endl;
    cout << "6. Quit" << endl;
}


//Get the uses option for the menu and returns it
string getOption ()
{
    string input;
    cout << "Please select an option and enter the corrosponding number: ";
    getline(cin >> ws, input);
    return input;
}


//Check if the user input is valid for the menu options then executes the menu option
int optionValid(string list[SIZE])
{
    bool validInput = false;
    bool isInteger;
    int option;
    while (!validInput)
    {
        string input;
        input = getOption();
        
        isInteger = true;
        for (int i =0; i < stringSize(input); i++)
        {
            if(!isdigit(input[i]))
            {
                isInteger = false;
                break;
            }
        }
        
        if (!isInteger)
        {
            cout << "Invalid input. Please enter an integer 1-6" << endl; 
        }
        else
        {
            option = stringToint(input); 
            if (option == 1 && !isEmpty(list, SIZE-1))
            {
                cout << "The list is full. You must delete an item before adding another one" << endl;
            }
            else if (option < 1 || option > 6)
            {
                cout << "Invalid input. You must select on option between 1-6" << endl;
            }
            else
            {
                validInput = true;
            }
        }
    }
    return option;
}


//Shifts everything it list over by one at the index to make space for new task
void shift(string list[SIZE], int index)
{
    for(int i = SIZE-2; i >= index; i--)
    {
        list[i+1] = list[i];
    }
}


//adds new task to the list
void addTask(string list[SIZE], string task, int p)
{
    int index = p - 1; 

    if (!isEmpty(list, index))
    {
        shift(list, index);
    }

    list[index] = task;
}


//validates the user input for the task position and calls addTask
void addValidation(string list[SIZE])
{
    bool validInput = false;
    bool isInteger;
    string line;
    string task;
    string input;
    int position;
    
    while(!validInput)
    {
        cout << "Enter task name and its position (seprated by a space): ";
        getline(cin >> ws, line);
        stringstream ss(line);

        if (!(ss >> task >> input) || (ss >> ws && !ss.eof()))
        {
            cout << "Invalid input. Please enter exactly: <task> <position>" <<endl;
            continue;
        }
        isInteger = true;

        for (int i =0; i < stringSize(input); i++)
        {
            if(!isdigit(input[i]))
            {
                isInteger = false;
                break;
            }
        }
        if (!isInteger)
        {
            cout << "Invalid input. Please enter an integer" << endl;
        }
        else 
        {
            position = stringToint(input);
            if (position < 1 || position > SIZE)
            {
                cout << "Invalid input. Position must be between 1-" << SIZE << endl;
            }
            else if (position != 1 && isEmpty(list, position-2)) 
            { 
                cout << "Invalid input. Cannot add a task to a position if there is not preciding task. Please enter a valid position" << endl;
            }
            else{
                validInput = true;
                }
        }
    }

    addTask(list, task, position);
    printNumTask(list);
    printAllTask(list);
    reversePrint(list);
}


//Deletes task at index q
void deleteTask(string list[SIZE], int q)
{
    int index = q-1;
    cout << list[index] << " has been deleted" << endl;
    for (int i = index; i < SIZE-1; i++)
    {
        list[i] = list[i+1];
    }
    list[SIZE - 1] = "";
}


//Print the total number of tasks
void printNumTask(string list[SIZE])
{
    int numTask = 0;
    for (int i=0; i < SIZE; i++)
    {
        if (!isEmpty(list, i))
        {
            numTask++;
        }
    }
    cout << "Number of tasks = " << numTask << endl;
}


//Prints each task in the list
void printAllTask(string list[SIZE])
{
    for (int i = 0; i < SIZE; i++)
    { 
        if (!isEmpty(list, i))
        { 
            cout << i+1 << ":" << list[i] << " ";
        }
    }
    cout << endl;
}


//Pirnts each task in the list in revese order
void reversePrint(string list[SIZE])
{
    for (int i = SIZE-1; i >= 0; i--)
    { 
        if (!isEmpty(list, i))
        { 
            cout << i+1 << ":" << list[i] << " ";
        }
    }
    cout << endl;
}


//Input validation of the deleteTask function. Also calls this function
void deleteValidation(string list[SIZE])
{
    bool validInput = false;
    bool isInteger;
    string line;
    string input;
    int position;
             
    if (!isEmpty(list, 0))
    {     
        while(!validInput)
        {
            cout << "Please enter the position of the task you would like to delete: ";
            getline(cin >> ws, line);
            stringstream ss(line);
            if (!(ss >> input) || (ss >> ws && !ss.eof())) 
            {
                cout << "Invalid input. Please enter exactly one integer." << endl;
                continue;
            }
            isInteger = true;
            for (int i =0; i < stringSize(input); i++)
            {
                if(!isdigit(input[i]))
                {
                    isInteger = false;
                    break;
                }
            }
            if (!isInteger)
            {
                cout << "Invalid input. Please enter an integer" << endl;
            }
            else 
            {
                position = stringToint(input);
                if (position < 1 || position > SIZE)
                {
                    cout << "Invalid input. Position must be between 1-" << SIZE << endl;
                }
                else if (isEmpty(list, position-1))
                {
                    cout << "The position you entered does not have a task. Please enter a valid position" << endl;
                }
                else
                {
                    deleteTask(list, position);
                    printNumTask(list);
                    printAllTask(list);
                    reversePrint(list);
                    validInput =true;
                }
            }
        }
            
    } 
    else
    { 
        cout << "The list is empty. You can not delete items from an empty list" << endl;
    }
}

//Call optionValid() to make sure option input is valid them excutes the users option
int performOption(string list[SIZE])
{
    int option;
    option = optionValid(list);

    switch(option)
    {
        case 1:
        {
            addValidation(list);
            cout <<endl;
            break;
        }

        case 2:
            deleteValidation(list);
            cout << endl;
            break;

        case 3:
            printNumTask(list);
            cout << endl;
            break;
        
        case 4:
            if (isEmpty(list, 0))
            {
                cout << "List is empty" << endl;
            }
            else
            {
                printAllTask(list); 
            }
            cout << endl;
            break;
            
        case 5:
        if (isEmpty(list, 0))
        {
            cout << "List is empty" << endl;
        }
        else
        {
            reversePrint(list); 
        }
        cout << endl;
        break;

        case 6:
        {
            cout << "Exiting program..." << endl;
            break;
        }

    }

    return option;
}


//Gets the size of a string
int stringSize(string input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        i++;
    }
return i;
}


//Checks if a index in an array is empty
bool isEmpty(string list[SIZE], int i)
{
    return list[i] == "";
}