#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Serializeable.h"

struct Time 
{
	int hours;
	int minutes;
};

class Movie : public Serializeable {
private:
	std::string title;
	std::string directorName;
	int publishedYear;
	Time startTime;
	int duration;
	void setTitle(std::string _title);
	void setDirectorName(std::string _dirName);
public:
	Movie();
	Movie(const std::string& t, const std::string& dirN, int pYear, Time& sT, int dur);

	const std::string getTitle()const;
	const std::string getDirName()const;
	const int getYearOfPub()const;
	const Time getStartTime()const;
	const int getDuration()const;

	friend std::ostream& operator <<(std::ostream& os, const Time& obj);
	friend std::ostream& operator <<(std::ostream& os, const Movie& obj);
	friend std::istream& operator >>(std::istream& in, Time& time);
	friend std::istream& operator >>(std::istream& in, Movie& obj);

	const void serialize(std::ofstream& file)const override;
	const void deserialize(std::ifstream& file)override;
};
