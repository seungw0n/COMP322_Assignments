//  A1
//  NAME : JOENG, SEUNG WON
//  STUDENT # :

#include <iostream>
using namespace std;

// Functin countLetter declaration
void countLetter();

// Function convertPhonetic declaration
void convertPhonetic();

// Functions for Q4 declaration
void factorial();
int aux(int num, int tail);

// Function for Q5 declaration
void enhancedFactorial();
int helperEnhancedVer(int num,int tail);

// main function
int main() {
    //countLetter();
    convertPhonetic();
    //factorial();
    //enhancedFactorial();
    return 0;
}

// function countLetter definition : Q1
void countLetter() {
    // delcare two string variables
    string strOne;
    string strTwo;
    // print the message
    cout << "Please enter a sentence: ";
    // using getline function to get the input values(sentence).
    getline(cin,strOne);
    // convert user's sentence to lower case
    for(int i =0; i < strOne.size(); i++) strOne[i] = tolower(strOne[i]);
    
    //cin.ignore();
    cout << "Please enter a letter: ";
    // using cin stream to get a input value.
    cin >> strTwo;
    // convert user's letter to lower case
    strTwo[0] = tolower(strTwo[0]);
    
    int count = 0;
    for (int i = 0; i < strOne.size(); i++) {
        // comparing both, if two letters are same, increase count by 1.
        if (strTwo[0]==strOne[i]) count++;
    }
    cout << "The letter " << strTwo << " is repeated " << count << " times in your sentence" << endl;
}

//function converPhonetic definition : Q2
void convertPhonetic() {
    string input;
    cout << "Please enter a word: ";
    cin >> input;
    
    string storage;
    
    // store upper case of input at variable storage
    for (int i =0; i < input.size(); i++) {
        storage[i] = toupper(input[i]);
        
        switch(storage[i])
        {
            case 'A': cout << "Alfa";
                break;
            case 'B': cout << "Bravo";
                break;
            case 'C': cout << "Charlie";
                break;
            case 'D': cout << "Delta";
                break;
            case 'E': cout << "Echo";
                break;
            case 'F': cout << "Foxtrot";
                break;
            case 'G': cout << "Golf";
                break;
            case 'H': cout << "Hotel";
                break;
            case 'I': cout << "India";
                break;
            case 'J': cout << "Juliett";
                break;
            case 'K': cout << "Kilo";
                break;
            case 'L': cout << "Lima";
                break;
            case 'M': cout << "Mike";
                break;
            case 'N': cout << "November";
                break;
            case 'O': cout << "Oscar";
                break;
            case 'P': cout << "Papa";
                break;
            case 'Q': cout << "Quebec";
                break;
            case 'R': cout << "Romeo";
                break;
            case 'S': cout << "Sierra";
                break;
            case 'T': cout << "Tango";
                break;
            case 'U': cout << "Uniform";
                break;
            case 'V': cout << "Victor";
                break;
            case 'W': cout << "Whiskey";
                break;
            case 'X': cout << "X-ray";
                break;
            case 'Y': cout << "Yankee";
                break;
            case 'Z': cout << "Zulu";
                break;
            //If non-alphabetical char,
            default: cout << storage[i];
                break;
        }
        
        cout << " ";
        
    }
    cout << endl;
}

/* Question 3 :
a) Research tail recursivity and explain in your own words why it is better to design your recursive function this way.
 
    A tail recursive is a one of types of recursive algorithm. Recursive algorithm can be defined as a self-referencing algorithm. Recursive algorithm has an advantage, easy to understand and to solve that algorithm, and also it is easy to use divide and conquer.
    A program has a recursive function, we call tail-recursive function when recursive call is the last thing executed by the function.
    In computer system, if a function is called, the computer saves the return address, so after the call is complete, computer can return to that location, and this is actually saved on the stack. Using tail-recursive function is more efficient on this information. Because, tail-recursion can be optimized by compiler, since the this type recursive call is the last statement, so the computer does not have to save current function on the stack.
 
 
b) Can any recursive function be designed to be tail recursive? Please develop your answer by providing clear explanation
 
    I can say yes for if a recursive function is solved on LIFO (opposite of FIFO). Tail recursive is a efficient on using stack, and stack is based on LIFO.
    However, if the recursive function is keeped as functions, then it cannot be designed to be a tail-recursive. For example, mergesort, quicksort cannot be designed to use tail-recursive.
 
 
*/

// function factorial() definition : Q4
void factorial() {
    int num;
    cout << "Please enter a number: ";
    // Get the number which user enters
    cin >> num;
    // If user enters non-positive number, display a error message
    if (num <= 0) cout <<"Invalid input, please enter a positive number only!" << endl;
    else {
        // Call the helper function and store it to variable fac
        int fac = aux(num, 1);
        cout << "The factorial of " << num << " is " << fac << endl;
    }
}
// Helper : function aux is using tail recursive to get the factorial of user's input.
int aux(int num, int tail) {
    if (num == 0) return tail;
    else return aux(num-1, tail * num);
}


// function enhancedFactorial definition : Q5
void enhancedFactorial() {
    int num;
    int arr[] = {1,2,6,24,120,720};
    
    cout << "Please enter a number: ";
    cin >> num;
    if (num <= 0) {
        // If user input non-positive number, display error message with return statement with nothing
        cout <<"Invalid input, please enter a positive number only!" << endl;
        return;
    }
    // If the user input is less or equal than 6,
    if (num <= 6)
        cout << "The factorial of " << num << " is " << arr[num-1] << endl;
    else {
        // If user input is more than 6, using helper method to calculate multiplying until 6,
        int val = helperEnhancedVer(num,1);
        // Multiply with 720
        val = val * arr[5];
        cout << "The factorial of " << num << " is " << val << endl;
    }
}

int helperEnhancedVer(int num, int tail) {
    // Using tail-recursive until the input is 6.
    if (num == 6) return tail;
    else return helperEnhancedVer(num-1, tail*num);
}
