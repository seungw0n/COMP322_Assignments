#include <iostream>
using namespace std;
/*
 Question 1. Research smart pointers provided by the standard library (since C++11). List them and explain the difference between them.
 
    Allocated memory with using "new" operator must be used "delete" operator to dellocate the memory allocated in C++.
    To prevent the memory leak, C++ provides the smart pointer. The smart pointer is a class that wraps a 'raw' C++ pointer, to manage the lifetime of the object being pointed to.
 
    Before C++11, auto_ptr, a type of smart pointer, was used, and since C++11, unique_ptr, shared_ptr, and weak_ptr are provided. (Not auto_ptr).
 
    The problem of using auto_ptr is that if two (or more) objects point to same address then the runtime error exists.
    So to figure it out, C++ provides the unique_ptr. (Both auto_ptr and unique_ptr have the ability of taking ownership of a pointer. So two or more objects cannot point same address.)
 
    1) unique_ptr
        The "unique_ptr" objects have the ability of taking ownership of a pointer, it means that once they take ownership they manage the pointed object by becoming responsible for its deletion at some point. It also prevents the run-time error when user tries to point two or more objects to same address. (Show on Line Error)
 
    2) Shared_ptr
        Unlike "unique_ptr", the "shared_ptr" objects have the ability of taking ownership of a pointer and share that ownership. Once they take ownership, the group of owners of a pointer become reponsible for its deletion when the last one of them releases that ownership. If the reference count becomes 0, then it uses "delete" keyword automatically to dellocate the memory allcoated.
 
    3) Weak_ptr
        The "weak_ptr" provides sharing semantics and not owning semantics. It means that "weak_ptr" can access to object of "shared_ptr" but it does not affect to "reference count".
        The purpose of "weak_ptr" is that to prevent the "circular reference in shared_ptr".
 */

//Q4 : generic using templates(built-in type)
template <typename T> class SmartPointer
{
private:
    T* ptr;
    // Additional field for allocated array size
    int size = 0;
public:
    
    //Constructor with no parameter sets to 0
    SmartPointer() {
        ptr = new T(0.0);
    }
    //Constructor with parameter
    SmartPointer(T val)
    {
        setValue(val);
    };
    
    //Constructor for carrying array case
    SmartPointer(T arr[], int size)
    {
        try
        {
            if(size < 0)
            {
                throw invalid_argument("Array size cannot be a negative!");
            }
            else
            {
                this->size = size;
                
                ptr = new T[size];
                for(int i = 0; i < size; i++)
                    *(ptr + i) = arr[i];
            }
        }
        catch (const bad_alloc& e)
        {
            cout << "Fail to allocate variable" << e.what() << endl;
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << endl;
        }
        
    }
    
    
    T getValue()
    {
         return *ptr;
    }
    
    
    void setValue(T val)
    {
        try
        {
            if(val < 0) throw "Negative Number";
            ptr = new T(val);
        }
        // 3.1 : catch out of memory exception
        catch(const bad_alloc& e)
        {
            cout << e.what() << endl;
        }
        // 3.2 : catch if input is negative
        catch(const char* eMsg){
            cout << "Error: " << eMsg << endl;
        }
    }
    
    
    //Q5 : operators overloading, use friend functions
    friend SmartPointer operator+ (SmartPointer<T> &first, SmartPointer<T> &second)
    {
        if (first.size == 0 && second.size == 0)
        {
            return SmartPointer<T>(*first.ptr + *second.ptr);
        }
        
        try
        {
            if(first.size != second.size) throw "Different Size";
            T arr[first.size];
            for(int i = 0; i < first.size; i++) arr[i] = *(first.ptr + i) + *(second.ptr + i);
            return SmartPointer<T>(arr, first.size);
            
        }catch(const char* eMsg){
            cout << "Error: " << eMsg << endl;
            return NULL;
        }
        
    }
    friend SmartPointer operator- (SmartPointer<T> &first, SmartPointer<T> &second)
    {
        if(first.size == 0 && second.size)
            return SmartPointer<T>(*first.ptr - *second.ptr);
        try
        {
            if(first.size != second.size) throw "Different Size";
            T arr[first.size];
            for(int i = 0; i < first.size; i++) arr[i] = *(first.ptr + i) - *(second.ptr + i);
            return SmartPointer<T>(arr, first.size);
            
        }catch(const char* eMsg){
            cout << "Error: " << eMsg << endl;
            return NULL;
        }
        
    }
    friend SmartPointer operator* (SmartPointer<T> &first, SmartPointer<T> &second)
    {
        if(first.size == 0 && second.size)
            return SmartPointer<T>(*first.ptr * *second.ptr);
        try
        {
            if(first.size != second.size) throw "Different Size";
            T arr[first.size];
            for(int i = 0; i < first.size; i++) arr[i] = *(first.ptr + i) * *(second.ptr + i);
            return SmartPointer<T>(arr, first.size);
            
        }catch(const char* eMsg){
            cout << "Error: " << eMsg << endl;
            return NULL;
        }
    }
    
    //Overloading getValue for case of array
    T getValue(int pos)
    {
        try {
            if (pos >= size) throw out_of_range("Index Out of Bound.");
            return *(ptr + pos);
        } catch (out_of_range& e) {
            cout << e.what() << endl;
            return NULL;
        }
    }
    
    void printAllValues()
    {
        for(int i = 0; i < size; i++)
        {
            cout << *(ptr + i);
            if (i != size-1) cout << ", ";
            else cout << endl;
        }
    }
    
    // Overloading setValue for case of array
    void setValue(T ptr, int pos)
    {
        try {
            if (pos >= size) throw out_of_range("Index Out of Bound.");
            if (pos < 0) throw invalid_argument("Array size cannot be a negative.");
             *(this->ptr + pos) = ptr;
        } catch(const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    // Overloading operators for case of array
    
    
    //Destructor
    ~SmartPointer()
    {
        if (size == 0) delete ptr;
        // Delete an allocated array
        else delete[] ptr;
    };
};

int main() {
    
    // For SmartPointer class
    cout << "Testing SmartPointer class" << endl;

    // Testing Constructors
    cout << "Creating a SmartPointer of type int with value 11" << endl;
    SmartPointer<int> SmartIntPointer1(11);
    cout << "SmartIntPointer1 = " << SmartIntPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type int with value -1" << endl;
    SmartPointer<int> SmartIntPointer(-1);

    cout << "Creating a SmartPointer of type int with no value provided" << endl;
    SmartPointer<int> SmartIntPointer2;
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    // Testing Setter & Getter
    cout << "Setting value of SmartIntPointer2 to 5" << endl;
    SmartIntPointer2.setValue(5);
    cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer1;
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Setting value of SmartFloatPointer1 to 1.5" << endl;
    SmartFloatPointer1.setValue(1.5);
    cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

    cout << "Creating a SmartPointer of type float with no value provided" << endl;
    SmartPointer<float> SmartFloatPointer2;
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    cout << "Setting value of SmartFloatPointer2 to 2.5" << endl;
    SmartFloatPointer2.setValue(2.5);
    cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

    SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
    cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

    SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
    cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

    SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
    cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;
    
    // For handling arrays
    cout << "Testing arrays" << endl;
    
    
    // add the needed code that shows how you use your class to create an array of multiple elements of a certain type.
    // provide all the necessary test code that shows the different use cases of your code
    
    // Index of Array starts with 0
    // Testing Constructors
    cout << "Creating a SmartPointer of type int array with value [11,12,13]" << endl;
    int a[] = {11,12,13};
    SmartPointer<int> SmartArrPointer1(a, 4);
    cout << "SmartArrPointer1.getValue(0) = " << SmartArrPointer1.getValue(0) << endl;
    cout << "SmartArrPointer1.getValue(1) = " << SmartArrPointer1.getValue(1) << endl;
    cout << "SmartArrPointer1.getValue(2) = " << SmartArrPointer1.getValue(2) << endl;
    cout << "SmartArrPointer1.getValue(9) : Exception " << endl
    << SmartArrPointer1.getValue(9) << endl;
    
    cout << "SmartArrPointer1.setValue(3,14) " << endl;
    SmartArrPointer1.setValue(14,3);
    cout << "SmartArrPointer1.getValue(3) = " << SmartArrPointer1.getValue(3) << endl;
    
    int b[] = {11,12,13,3,12};
    SmartPointer<int> SmartArrPointer2(b,5);
    cout << "SmartArrPointer3 = SmartArrPointer1 + SmartArrPointer2 : Exception " << endl;
    SmartPointer<int> SmartArrPointer3 = SmartArrPointer1 + SmartArrPointer2; // Error Different Size
    
    
    cout << endl;
    int c[] = {11,12,13,14};
    cout << "Creating a new SmartPointer of type int array with value [11,12,13,14]" << endl;
    SmartPointer<int> SmartArrPointer4(c,4);
    
    cout << endl;
    cout << "SmartArrPointer5 = SmartArrPointer1 + SmartArrPointer4 = [22,24,26,28]" << endl;
    
    SmartPointer<int> SmartArrPointer5 = SmartArrPointer1 + SmartArrPointer4;
    cout << "SmartArrPointer5.getValue(0) = " << SmartArrPointer5.getValue(0) << endl;
    cout << "SmartArrPointer5.getValue(1) = " << SmartArrPointer5.getValue(1) << endl;
    cout << "SmartArrPointer5.getValue(2) = " << SmartArrPointer5.getValue(2) << endl;
    cout << "SmartArrPointer5.getValue(3) = " << SmartArrPointer5.getValue(3) << endl;
    
    SmartArrPointer5.setValue(2, 2);
    cout << "SmartArrPointer5.setValue(2,2)\nSmartArrPointer5.getValue(2) = " << SmartArrPointer5.getValue(2) << endl;
    
    cout << endl;
    cout << "SmartArrPointer6 = SmartArrPointer1 - SmartArrPointer4 = [0,0,0,0]" << endl;
    SmartPointer<int> SmartArrPointer6 = SmartArrPointer1 - SmartArrPointer4;
    cout << "SmartArrPointer6.getValue(0) = " << SmartArrPointer6.getValue(0) << endl;
    cout << "SmartArrPointer6.getValue(1) = " << SmartArrPointer6.getValue(1) << endl;
    cout << "SmartArrPointer6.getValue(2) = " << SmartArrPointer6.getValue(2) << endl;
    cout << "SmartArrPointer6.getValue(3) = " << SmartArrPointer6.getValue(3) << endl;
    
    cout << endl;
    cout << "SmartArrPointer7 = SmartArrPointer1 * SmartArrPointer4 = [121,144,169,196]" << endl;
    SmartPointer<int> SmartArrPointer7 = SmartArrPointer1 * SmartArrPointer4;
    cout << "SmartArrPointer7.getValue(0) = " << SmartArrPointer7.getValue(0) << endl;
    cout << "SmartArrPointer7.getValue(1) = " << SmartArrPointer7.getValue(1) << endl;
    cout << "SmartArrPointer7.getValue(2) = " << SmartArrPointer7.getValue(2) << endl;
    cout << "SmartArrPointer7.getValue(3) = " << SmartArrPointer7.getValue(3) << endl;
    
    cout<<endl;
    cout << "Function printAllValues" << endl;
    cout << "SmartArrPointer1.printAllValues : ";
    SmartArrPointer1.printAllValues();
    cout << "SmartArrPointer2.printAllValues : ";
    SmartArrPointer2.printAllValues();
    cout << "SmartArrPointer4.printAllValues : ";
    SmartArrPointer5.printAllValues();
    cout << "SmartArrPointer6.printAllValues : ";
    SmartArrPointer6.printAllValues();
    cout << "SmartArrPointer7.printAllValues : ";
    SmartArrPointer7.printAllValues();
    
}

