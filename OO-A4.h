/* -------------------------- Assignment 3 -- 159.234 ---------------------------- */
/*                 Andrew Creevey 12236284 -- Jonny Jackson 14089365               */
/* ------------------------------------------------------------------------------- */

#include <iostream>
#include <cassert>

using namespace std;

//requirement to display this info on the screen
void displayInfo () {
	cout << "----------------------------------------" << endl;
	cout << "     Assignment 1 -- Semester 2 2015    " << endl;
	cout << " Submitted by: Andrew Creevey, 12236284 " << endl;
	cout << "                 Jonny Jackon, 14089365 " << endl;
	cout << "----------------------------------------" << endl;
}

/* --------------------------- Start of Template Class --------------------------- */
template <class T>
class Vector {
public:
	// Constructors
	Vector();
	Vector(int size);
   Vector(int size, const T &value);
   Vector(int size, const T *data);
   Vector(const Vector<T> &other);
   Vector(Vector<T> &&other);

	// Destructor
   ~Vector();
	
   // Assignment Operators
   const Vector<T>& operator=(const Vector<T> &other);
   Vector<T>& operator=(Vector<T> &&other);

	// Operators
   T& operator[](int i);
   const T& operator[](int i) const;

   // Methods
	void insert(int i, const T& value);
	void assign(int first, int last, const Vector<T> other);
	void erase(int i);
	void erase(int first, int last);
	void clear();
	int length() const;
	int memorySize() const;
	bool isEmpty() const;
	
	void printVector() {
		for (int i = 0; i < mSize; i++) {
			if (i == mSize-1) {
				cout << mData[i] << endl;
			} else { 
				cout << mData[i] << ", ";
			}
		}
	}
private:
	// Data Members
	int mCapacity;
	int mSize;
	T *mData;
};

/* ---------------------------- End of Template Class ---------------------------- */

/* -------------------------------- Constructors --------------------------------- */

// Default constructor to create an empty Vector - mSize and mCapacity should
// be set to zero and no memory should be allocated for the array (make sure 
// that the value of mData is not arbitrary).
template <class T>
Vector<T>::Vector() : mCapacity (0), mSize(0), mData(nullptr) {
	cout << "Vector () called" << endl;
}


// Custom constructor that creates a Vector with size items. Each item is 
// initialised by its default constructor. The constructor should not act 
// as a type conversion.
template <class T>
Vector<T>::Vector(int size) : mCapacity(size), mSize(size), mData(new T[size]) { 
	cout << "Vector (int size) called" << endl;
}

// Custom constructor that creates a Vector with size items. Each item is 
// initialised to value.
template <class T>
Vector<T>::Vector(int size, const T &value) {
	cout << "Vector (int size, const T &value) called" << endl;
	mSize = mCapacity = size;
	mData = new T[size];
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int test = 0; //used for testing, comment out
	for (int i = 0; i < size; i++) {
		mData[i] = test; //value;
		test++;
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}

// Custom constructor that creates Vector of size items. Each item is initialised
// by the value of the corresponding item in the array data
template <class T>
Vector<T>::Vector(int size, const T *data){
	cout << "Vector (int size, const T *data) called" << endl;
	mSize = mCapacity = size;
	mData = new T[size];
	for (int i = 0; i < size; i++) {
		mData[i] = data[i]; //value;
	}
}

// Copy constructor – create a deep copy of the other Vector.
template <class T>
Vector<T>::Vector(const Vector<T> &other) {
	cout << "Called copy constructor" << endl;
	mSize = other.mSize;
	mCapacity = other.mCapacity;
	mData = new int[mSize];
	for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
}

// Move constructor – steal the data from the other Vector
template <class T>
Vector<T>::Vector(Vector<T> &&other) : mCapacity(0), mSize(0), mData(nullptr) {
	cout << "Called move constructor" << endl;
	
	//copy the data from the source object
	mCapacity = other.mCapacity;
	mSize = other.size;
	for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
	
	//release the data from the source object
	other.mCapacity = 0;
	other.mSize = 0;
	other.mData = nullptr;
}

/* --------------------------------- Destructors --------------------------------- */

template <class T>
Vector<T>::~Vector () {
	cout << "Destructor called" << endl;
	delete[] mData; 
	mData = nullptr;
	mSize = 0;
	mCapacity = 0;
}

/* ----------------------------- Assignment Operators ---------------------------- */

//copy assignment operator
template <class T>
const Vector<T>& Vector<T>::operator = (const Vector<T> &other) {
	cout << "Copy assignment operator called" << endl;
	if (this != &other) {
		delete[] mData; //free whats there already
		mSize = other.mSize;
		mCapacity = other.mCapacity;
		mData = new T[mSize];
		for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
	}
	return *this;
}

//move assignment operator
template <class T>
Vector<T>& Vector<T>::operator = (Vector<T> &&other) {
	cout << "Move assignment operator called" << endl;
	
	if (this != &other) {
		//free existing data
		delete[] mData;
		
		//copy the data from the source object
		mCapacity = other.mCapacity;
		mSize = other.mSize;
		for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
		
		//release the data from the source object
		other.mCapacity = 0;
		other.mSize = 0;
		other.mData = nullptr;
	}
	return *this;
}

/* ---------------------------------- Operators ---------------------------------- */

template <class T>
T& Vector<T>::operator[](int i) {
	if (0 < i && i < mSize) { //if in range
		return mData[i]; //return data at position i
	} 
	throw "Error: Out of Range"; //if not in range, throw an error
}

template <class T>
const T& Vector<T>::operator[](int i) const {
	if (0 < i && i < mSize) { //if in range
		return mData[i]; //return data at position i
	} 
	throw "Error: Out of range"; //if not in range, throw an error
}

/* ----------------------------------- Methods ----------------------------------- */

template <class T>
void Vector<T>::insert(int i, const T& value) { 
	//have assumed that the insert
	if (i == 0) { //want to insert at the first element
		//e.g. array[4] = 0,1,2,3 and want to put in at position [0]
		T* tempArray = new T[mSize+1];
		for (int j = mSize; j > -1; j--) { //work backwards
			tempArray[j] = mData[j-1];
		}
		tempArray[0] = value; //insert variable
		delete[] mData; 
		mData = tempArray;
		mSize += 1;
	}
	else if (0 < i && i < mSize) { //want to insert at position in range
		//e.g. array[4] = 0,1,2,3 and want to put in at position [1], [2] or [3]
		T* tempArray = new T[mSize+1];
		for (int j = 0; j < i; j++) { //initialise variables before i
			tempArray[j] = mData[j];
		}
		for (int j = mSize; j > i; j--) { //shift variables backwards to make room
			tempArray[j] = mData[j-1];
		}
		tempArray[i] = value; //insert variable
		delete[] mData; 
		mData = tempArray;
		mSize += 1;
	}
	else if (i == mSize) { //want to insert after the current element
		//e.g. array[4] = 0,1,2,3 and want to put in at position [4]
		T* tempArray = new T[mSize+1];
		for (int j = 0; j < mSize; j++) { //initialise variables before i
			tempArray[j] = mData[j];
		}
		tempArray[i] = value; //insert variable
		delete[] mData;
		mData = tempArray;
		mSize += 1;
	}
	else { //if out of range, throw error
		cout << "Error: Cannot insert values, out of range" << endl;
	}
}

template <class T>
void Vector<T>::assign(int first, int last, const Vector<T> other) {
	if (last > other.mSize-1) {
		cout << "Error: Second argument is out of bounds. " << endl;
		return;
	}
	else if(last > this->mSize) { 
		T temp;
		T* tempArray = new T[(mSize+(last-mSize))];
		for(int i=0; i < mSize; i++) {
			temp = mData[i];
			tempArray[i] = temp;
		}
		for(int i = first; i<last+1; i++) {
			tempArray[i] = other[i];
		}
		delete[] mData; //we forgot to put the [], edited 6/11/15
		mData = tempArray;
		mSize+=(last-mSize)+1;
	} else {
		for(int i = first; i<last+1; i++) {
			mData[i] = other[i];
		}
	}
}

template <class T>
void Vector<T>::erase(int i) {
	if (0 < i && i < mSize) { //checks if it is in range
		for (int index = i; index < mSize; i++) {
			mData[i] = mData[i+1]; //put the next data variable into the current index
		}
	} else { cout << "Error: Out of range" << endl; } //if not in range, display error
}

template <class T>
void Vector <T>:: erase(int first, int last){
	if (0 <= first && last < mSize) {
		mSize -= ((last - first) + 1); 			//remove extra numbers from the size value
		if (first + 1 != last) { 					//if there's 2 or more numbers to be removed
			for (int i = first; i < mSize; i++)  {
				mData[i] = mData[++last];		//shift the elements down the array
			}  
		}
		else if (first + 1 == last) {				//if less than 2 numbers to be removed
			for (int i = first; i < mSize; i++) {
				mData[i] = mData[i + 2];			//
			}
		}
	} else { cout << "Error: Out of range" << endl; } //if numbers are out of bounds
}

template <class T>
void Vector<T>::clear() {
	for (int i = 0; i < mSize; i++) mData[i] = nullptr; //change all variables to null
	mCapacity = 0; 	//reset to 0
	mSize = 0; 			//reset to 0
}

template <class T>
int Vector<T>::length() const {
	cout << "Called length(). Size is: " << mSize << endl; 
	return mSize; //return the size
}

//Returns the size of the memory space allocated for the Vector.
template <class T>
int Vector<T>::memorySize() const {
	return mSize*sizeof(mData);
}

//Returns true if the Vector has no items and false otherwise
template <class T>
bool Vector<T>::isEmpty() const {
	if (mSize == 0) return true;
	else return false;
}
