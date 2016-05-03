/* --------------------------- Assignment 3 -- 159.234 --------------------------- */
/*                             Andrew Creevey 12236284                             */
/* ------------------------------------------------------------------------------- */
/* You have to write a program to be used by the Massey University Library. There  */
/* are three types of items that can be borrowed from the library – Books, Journal */ 
/* articles and Movies. All of these items are a type of Media item. You will need */
/*  to create a simple inheritance hierarchy for items that the library lends out  */
/*   Create a Media base class with Book, Movie and Journal as derived classes as  */
/*                                 specified below                                 */
/* ------------------------------------------------------------------------------- */

#include <iostream> 	
#include <string> 	
#include <iomanip>

using namespace std;

//requirement to display this info on the screen
void displayInfo () {
	cout << " ----------------------------------------" << endl;
	cout << "      Assignment 1 -- Semester 2 2015    " << endl;
	cout << "  Submitted by: Andrew Creevey, 12236284 " << endl;
	cout << " ----------------------------------------" << endl;
}

/* ----------------------- Start of Media class functions ------------------------ */

//base class Media
class Media {
private: 
	int id;
	string title;
	int year;
	int rating;
	int numReviews;
public:
	//default constructor
	Media (int _id = 0, string _title = "", int _year = 0, int _rating = 0, int _numReviews = 0) 
   /**/: id(_id), title(_title), year(_year), rating(_rating), numReviews(_numReviews) { }

	//~destructor
	virtual ~Media() { }

	//functions
	void rate (int mRating);
	virtual void print (ostream &out);
	void printRating (ostream &out);
	friend ostream &operator << (ostream &out, Media &MediaOb);
};

//rate function
void Media::rate (int mRating) {
	this->rating += mRating; //add the rating to whats already in rating
	numReviews++; //increment number of reviews
}

void Media::print (ostream &out) {
	out << id << ", "; //print out the id
	out << title << ", "; //print out the title
	out << "(" << year << "), "; //print out the year
}

void Media::printRating (ostream &out) {
	if (rating == 0) { 	//if rating is zero
		out << " (no rating)"; //display no rating
	} else {
		out << " ("; 
		for (int i = 0; i < (rating/(numReviews)); i++) out << "*"; //print a * for every number
		cout << ")"; 
	}
}

ostream &operator << (ostream &out, Media &MediaOb) {
	MediaOb.print(out); 	//call the print function 
	return out;				//return out
}

/* ----------------------- Start of Movie class functions ------------------------ */

class Movie : public Media {
private:	
	string director;
public:
	//default constructor
	Movie (int _id, string _title, int _year, string _director = "unknown")
	/**/ : Media(_id, _title, _year), director(_director) { }
	
	//default destructor
	virtual ~Movie() { }
	
	//print function
	void print (ostream &out) {
		out << " Movie: "; //type
		Media::print(out); //call this so id/title/year is displayed
		out << "Directed by " << director; //display director
		Media::printRating(out); //display rating
	}
};

/* ----------------------- Start of Book class functions ------------------------ */

class Book : public Media {
private: 
	string author;
	int numPages;
public:
	//Constructor
	Book (int _id, string _title, int _year, string _author, int _numPages)
	/**/ : Media(_id, _title, _year), author(_author), numPages(_numPages) { }
	
	//destructor
	virtual ~Book() { }
	
	//print
	void print (ostream &out) {
		out << " Book: "; //type
		Media::print(out); //call this so id/title/year is displayed
		out << "By " << author << ", ";
		out << numPages; //
		Media::printRating(out); //display rating
	}
};

/* ---------------------- Start of Journal class functions ----------------------- */

class Journal : public Media {
private: 
	int volume;
	int number;
public:
	public:
	//Constructor
	Journal(int _id, string _title, int _year, int _volume, int _number) 
	/**/: Media(_id, _title, _year), volume(_volume), number(_number) { }
	
	//destructor
	virtual ~Journal () { }
	
	//print
	void print (ostream &out) {
		out << " Journal: "; //print type
		Media::print(out); //call this so id/title/year is displayed
		out << "Volume: " << volume << ", "; //print volume
		out << "Number: " << number; //print number
		Media::printRating(out); //print out the rating
	}
};

/* -------------------------- Main --------------------------- */

int main() {
	displayInfo();
	
	/*** The below code was given as a requirement from the assignment brief ***/
	Media *ptr[10];
	
	ptr[0] = new Movie(352, "Remember The Alamo", 1945, "George Smith");
	ptr[1] = new Movie(831, "High School Blues", 1984);
	ptr[2] = new Movie(194, "Going for the Touchdown", 1984, "Frank Madden");
	ptr[3] = new Movie(576, "Martian Hairdresser", 1992, "Debbie Gold");
	ptr[4] = new Book(608, "How to Make Money",1987, "Phil Barton", 324);
	ptr[5] = new Book(442, "Garden Projects At Home", 1998, "Mary Freeman", 164);
	ptr[6] = new Book(185, "The Haunted House Mystery", 1996, "Bert Morgan", 53);
	ptr[7] = new Journal(294, "ACM", 2009, 6, 8);
	ptr[8] = new Journal(521, "J of Logic", 2008, 23, 14);
	ptr[9] = new Journal(630, "J of AI", 2009, 35, 11);
	
	cout << " Printing 10 items..." << endl << endl;
	
	for (int i = 0; i < 10; ++i) {
		cout << *ptr[i] << endl;
	}
	
	ptr[0]->rate(3);
	ptr[0]->rate(1);
	
	ptr[2]->rate(4);
	ptr[2]->rate(2);
	
	ptr[3]->rate(1);
	ptr[3]->rate(1);
	
	cout << endl << " Printing again..." << endl << endl;
	
	for (int i = 0; i < 10; ++i) {
		cout << *ptr[i] << endl;
		delete ptr[i];
	}
}
