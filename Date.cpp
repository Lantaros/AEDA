#include "Date.h"

//Constructors

/**
 * Date default constructor,
 * instatiates an object with current time
 */
Date::Date()
{
	time_t now;
	now = time(0); //Number os secs since 1st of January 1970

	tm ltm;  //local time struct
	tm *ltmP = &ltm;

	localtime_s(&ltm, &now); //Initialises the struct

	day = ltmP->tm_mday;
	month = 1 + ltmP->tm_mon;
	year = 1900 + ltmP->tm_year;

	//Check if it's a leap year
	this->checkLeap();
}

/**
* This constructs a date from a string
* @param date A string formated like this (dd/mm/yyyy)
*/
Date::Date(string date)
{
	istringstream iss(date);
	string extract;

	getline(iss, extract, '/');
	day = stoi(extract);

	getline(iss, extract, '/');
	month = stoi(extract);

	getline(iss, extract, '/');
	year = stoi(extract);

	//Check if it's a leap year
	this->checkLeap();

    if(!this->isValid())
        throw InvalidDate(date);

}

/**
* A Date constructor from three uIntegers ( day, month, year)
* @param day
* @param month
* @param year
*/
Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;

	//Check if it's a leap year
	this->checkLeap();
}

//Sets 'n gets
/**
* This sets the date's year attribute
* @param year
*/
void Date::setYear(unsigned int year)
{
	Date::year = year;
}

/**
*Sets the month attribute to argument value, if valid
* @param month
*/
void Date::setMonth(unsigned int month)
{
	Date::month = month;
}

/**
 * Sets the day attribute to argument value, if valid
 * @param day
 */
void Date::setDay(unsigned int day)
{
	Date::day = day;
}

/**
 *Sets all of the date attributes, if all of them are valid
 * @param day
 * @param month
 * @param year
 */
void Date::setDate(unsigned int day, unsigned int month, unsigned int year)
{
	Date::day = day;
	Date::month = month;
	Date::year = year;
}

/**
*
* @return class's day atribute
*/
unsigned int Date::getDay() const
{
	return day;
}

/**
 *
 * @return class's month atribute
 */
unsigned int Date::getMonth() const
{
	return month;
}
/**
 *
 * @return class's year atribute
 */
unsigned int Date::getYear() const
{
	return year;
}


/**
 *
 * @return all the attributes in a string (dd/mm/yyyy)
 */
string Date::getDate() const // returns the date in format "dd/mm/yyyy"
{
	ostringstream oss;
	oss << day << "/" << month << "/" << year;

	return  oss.str();
}


/**
 * Checks wether a year is a leap one
 */
void Date::checkLeap()
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		leap = true;
	else
		leap = false;
}


bool Date::isValid() const
{
    if (month >= 1 && month <= 12)
    {
        if (day >= 1 && day <= nDays())
            return true;
        else
            return false;
    }
    else
        return false;
}

unsigned int Date::nDays() const
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
    if (month == 2)
    {
        if (leap)
            return 29;
        else
            return 28;
    }
    else
        return 31;
}

string InvalidDate::getDate() const
{
    return std::__cxx11::string();
}


//Operators overloading

/**
* Operator<< overloading for class Date
* @param out out stream
* @return output stream
*/
ostream & Date::operator<< (ostream &out) const
{
	out << day << "/" << month << "/" << year;

	return out;
}

//Comparison operator's overloading
/**
*
* @param date a Date object
* @return a bool
*/
bool Date::operator< (const Date &date) const
{
	if (Date::year < date.year)
		return true;

	if (date.year == Date::year)
	{
		if (Date::month < date.month)
		{
			return true;
		}
		else
			if (date.month == Date::month)
			{
				if (Date::day <  date.day)
					return true;
				else
					return false;

			}
			else
				return false;
	}
	else
		return	false;
}

/**
 *
 * @param date
 * @return ! operator<
 */
bool Date::operator> (const Date &date) const
{
	return !this->operator <(date);
}

/**
 *
 * @param date
 * @returnv
 */
bool Date::operator== (const Date &date) const
{
	if (Date::day == date.day && Date::month == date.month && Date::year == date.year)
		return true;
	else
		return false;
}
