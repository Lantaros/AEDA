#ifndef __Date__
#define __Date__

#include "Libraries.h"
#include <sstream>
#include <iostream>
#include <ctime>

class Date
{
public:
	//Constructors
	Date();
	Date(string date);
	Date(unsigned int day, unsigned int month, unsigned int year);
	//Sets 'n gets
	void setYear(unsigned int year);
	void setMonth(unsigned int month);
	void setDay(unsigned int day);
	void setDate(unsigned int day, unsigned int month, unsigned int year);
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	string getDate() const; // returns the date in format "dd/mm/yyyy"
	void show() const; // shows the date on the screen in format "dd/mm/yyyy"
	bool isLeap() const;


//Operators
	ostream & operator<< (ostream &out) const;

	//Comparison operator's overloading
	bool operator< (Date &date) const;
	bool operator> (Date &date) const;
	bool operator== (Date &date) const;



protected:
	void checkLeap();

private:
	unsigned int day, month, year;
	bool leap;
};


#endif
