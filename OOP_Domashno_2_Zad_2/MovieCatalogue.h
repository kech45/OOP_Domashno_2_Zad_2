#pragma once
#include <iostream>
#include <vector>
#include "Movie.h"

struct Date {
	int year;
	int month;
	int day;
};

class MovieCatalogue : public Serializeable 
{
private:
	std::vector<Movie> movies;
	std::string cinemaName;
	Date projectionDate;
	bool fileExists(std::string fileName);
	int toMinsConverter(const Time& time);
public:
	const std::string getCinemaName()const;
	const Date getProjDate()const;
	const std::vector<Movie> getMovies()const;

	MovieCatalogue() = default;
	MovieCatalogue(const std::string& fileName);
	~MovieCatalogue();

	void addMovie(const Movie& obj);
	void removeMovie(const std::string& title);
	Movie* findMovie(const std::string& title);
	int numOfMoviesInInterval(const Time& startTime, const Time& endTime);

	friend std::ostream& operator <<(std::ostream& os, const Date& obj);
	friend std::istream& operator >>(std::istream& in, Date& obj);

	const void serialize(std::ofstream& file)const override;
	const void deserialize(std::ifstream& file)override;


};