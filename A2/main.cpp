/*
 NAME : JOENG, SEUNG WON
 STUDENT # : 260735232
 NOTE : To get random numbers with different sequence, please placed this code in the main function before run.
    srand(static_cast<unsigned int>(time(0))); // Set the seed as time
 */


#include <iostream>
#include <cstdlib> // std::srand(), std::rand()
#include <ctime> // std::time()

using namespace std;

struct ticket
{
    unsigned int numbers[6];
    ticket* next;
};

class SuperDraw
{
public:
    //Q1
    SuperDraw()
    {
        // Constructor sets the head and tail of the linked list as NULL.
        ticketListHead = NULL;
        ticketListTail = NULL;
    };
    // Q3 : New constructor that takes an int argument
    SuperDraw(int number)
    {
        ticketListHead = NULL;
        ticketListTail = NULL;
        
        if (number <= 0) return;
        if (number == 1) newTicket(1);
        else
        {
            cout << number << " new tickets were successfully generated." << endl;
            cout << "The numbers are: ";

            for(int i = 0; i < number; i++) {
                newTicket(0);
            }
            ticket *tmp = ticketListHead;
            for (int j = 0; j < number; j++)
            {
                for(int i = 0; i < 6; i++)
                {
                    if(i != 5) cout << tmp -> numbers[i] << ", ";
                    else cout << tmp -> numbers[i];
                }
                if (j < number - 1) cout << " and ";
                tmp = tmp -> next;
            }
            cout << endl;
        }
    }
    
    // Q8 : copy constructor
    SuperDraw(const SuperDraw &sd)
    {
        if(sd.ticketListHead == NULL) return;
        
        // tmp variable since sd doesn't move.
        ticket* tmp = sd.ticketListHead;
        
        // allocate new ticket.
        ticketListHead = new ticket;
        
        // Copy over the numbers
        for(int i = 0; i < 6; i++) ticketListHead -> numbers[i] = tmp -> numbers[i];
        
        // Set the next value to null
        ticketListHead -> next = NULL;
        // Set the tail
        ticket* cur = ticketListHead;
        tmp = tmp -> next;
        
        while (tmp != NULL)
        {
            cur -> next = new ticket;
            cur = cur -> next;
            for(int i =0; i < 6; i++)
            {
                cur -> numbers[i] = tmp -> numbers[i];
            }
            cur -> next = NULL;
            tmp = tmp -> next;
        }
        
        ticketListTail = cur;
    }
    
    //Destructor
    ~SuperDraw()
    {
        // Destructor deletes all lists until the linked list is empty.
        ticket* cur = ticketListHead;
        while(cur != NULL)
        {
            ticketListHead = ticketListHead->next;
            delete cur;
            cur = ticketListHead;
        }
    };
    
    
    //Declaration method newTicket for Q2.
    void newTicket(int verbose);
    //Helper method for newTicket
    int getRandomNumber(int min, int max);
    //Declaration method printAllTicketNumbers for Q4.
    void printAllTicketNumbers();
    //Declaration method verifySequence for Q5.
    void verifySequence(unsigned int myNumbers[]);
    //Declaration method deleteSequence for Q6.
    void deleteSequence(unsigned int myNumbers[]);
    
private:
    ticket* ticketListHead;
    ticket* ticketListTail;
};

// Generate random integer between min and max (both included)
// Helper method for newTicket
int SuperDraw::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max-min+1)*(rand() * fraction));
}


void SuperDraw::newTicket(int verbose)
{
    ticket *current = new ticket;
    
    bool check[49] = {false,};
    
    //Random number 1 to 49 both included
    for(int i = 0; i < 6;) {
        //Generate the number
        int random = getRandomNumber(1, 49);
        //Check the duplicate
        if (check[i] == false)
        {
            check[i] = true;
            current->numbers[i] = random;
            i++;
        }
    }
    
    current -> next = NULL;
    
    //Sorted the array
    int temp;
    int i,j;
    for(i = 1; i < 6; i++)
    {
        temp = current->numbers[i];
        j = i - 1;
        
        while ((j >= 0) && (temp < current->numbers[j]))
        {
            current->numbers[j+1] = current->numbers[j];
            j = j - 1;
        }
        current->numbers[j+1] = temp;
    }
    /*
     ABOVE HERE : Insertion sort
     */
    
    if (verbose == 1)
    {
        cout << "A new ticket was successfully generated. The numbers are: ";
        for(int i =0; i<6; i++)
        {
            if(i != 5) cout << current->numbers[i] << ", ";
            else cout << current->numbers[i];
        }
        cout << endl;
    }
    // If this linked list is empty then
    if (ticketListHead == NULL)
    {
        ticketListHead = current;
        ticketListTail = current;
    }
    
    /* otherwise this linked list is not empty,
     addLast */
    else
    {
        ticketListTail -> next = current;
        ticketListTail = current;
    }
}

void SuperDraw::printAllTicketNumbers()
{
    int length = 0;
    ticket* cur = ticketListHead;
    while (cur != NULL)
    {
        // count the length
        length++;
        cur = cur->next;
    }
    cout << "We found " << length << " generated tickets: " << endl;
    if (length != 0)
    {
        ticket* tmp = ticketListHead;
        // Print each numbers
        while(tmp != NULL)
        {
            for(int i = 0; i < 6; i++)
            {
                if ( i != 5) cout << tmp -> numbers[i] << ", ";
                else cout << tmp -> numbers[i] << endl;
            }
            tmp = tmp -> next;
        }
    }
}

void SuperDraw::verifySequence(unsigned int myNumbers[])
{
    bool check = false;
    ticket *tmp = ticketListHead;
    
    while(tmp != NULL)
    {
        int i;
        for( i = 0; i < 6; i++)
        {
            if (myNumbers[i] != tmp->numbers[i]) break;
        }
        if (i == 6) {
            check = true;
            break;
        }
        else
        tmp = tmp -> next;
    }
    
    if (check) cout << "The provided sequence of numbers was already generated." << endl;
    else cout << "The provided sequence of numbers was never generated before." << endl;
    
    
}

void SuperDraw::deleteSequence(unsigned int myNumbers[])
{
    
    ticket *tmp = ticketListHead;
    
    while(tmp != NULL)
    {
        int i;
        for( i = 0; i < 6; i++)
        {
            if (myNumbers[i] != tmp->numbers[i]) break;
        }
        if (i == 6) break;
        else
            tmp = tmp -> next;
    }
    
    if (tmp == NULL)
    {
        cout << "The provided sequence of numbers was never generated before" << endl;
    }
    else
    {
        ticket* node = ticketListHead;
        //If the node which has same sequence is located on the first
        if (tmp == node)
        {
            ticketListHead = ticketListHead -> next;
            delete tmp;
        }
        else
        {
            // get the previous node
            while(node->next != tmp){
                node = node -> next;
            }
            node -> next = tmp -> next;
            delete tmp;
        }
        
         cout << "The provided sequence of numbers was successfully deleted." << endl;
        
    }
}



int main()
{
    //Set the seed as time from cpu
//   std::srand(static_cast<unsigned int>(time(0)));
    
    SuperDraw sd(3);
    //sd.printAllTicketNumbers();
//    sd.printAllTicketNumbers();
    unsigned int myNumbers[6] = {1, 2, 3, 26, 33, 41};
    sd.verifySequence(myNumbers);
    sd.deleteSequence(myNumbers);
    sd.printAllTicketNumbers();
//
//    SuperDraw sd2(sd);
//    sd2.printAllTicketNumbers();
    
//    SuperDraw sd(2);
    
}
