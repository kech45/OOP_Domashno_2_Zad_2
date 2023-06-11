#include <iostream>
#include "MovieCatalogue.h"

bool MovieCatalogue::fileExists(std::string fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}
int MovieCatalogue::toMinsConverter(const Time& time) {
	return time.hours * 60 + time.minutes;
}

const std::string MovieCatalogue::getCinemaName()const {
	return cinemaName;
}
const Date MovieCatalogue::getProjDate()const {
	return projectionDate;
}
const std::vector<Movie> MovieCatalogue::getMovies()const {
	return movies;
}

MovieCatalogue::MovieCatalogue(const std::string& fileName) {
	if (fileExists(fileName)) {
		std::ifstream file(fileName);
		file.open(fileName);
		deserialize(file);
		file.close();
	}
	else {
		cinemaName = fileName.substr(0, fileName.find("."));
		time_t now = time(nullptr);
		tm* current = localtime(&now);
		projectionDate.day = current->tm_mday;
		projectionDate.month = current->tm_mon + 1;
		projectionDate.year = current->tm_year + 1900;
	}
}
MovieCatalogue::~MovieCatalogue() {
	std::ofstream file(cinemaName + ".bin");
	if (file.is_open()) {
		serialize(file);
		file.close();
	}
}

void MovieCatalogue::addMovie(const Movie& obj) {
	movies.push_back(obj);
}
void MovieCatalogue::removeMovie(const std::string& title) {
	for (int i = 0; i < movies.size(); i++)
	{
		if (movies[i].getTitle() == title) {
			movies.erase(movies.begin()+i);
		}
	}
}
Movie* MovieCatalogue::findMovie(const std::string& title) {
	for (int i = 0; i < movies.size(); i++) {
		if (movies.at(i).getTitle() == title)
		{
			return &movies.at(i);
		}
	}
	return nullptr;
}
int MovieCatalogue::numOfMoviesInInterval(const Time& startTime, const Time& endTime) {
	int count = 0;
	
	
	for (const Movie& movie : movies)
	{
		int movieEndTime = toMinsConverter(movie.getStartTime()) + movie.getDuration();
		if ((toMinsConverter(movie.getStartTime()) >= toMinsConverter(startTime)) && (movieEndTime <= toMinsConverter(endTime))) {
			count++;
		}
	}

	return count;
}

std::ostream& operator <<(std::ostream& os, const Date& obj) {
	os << obj.day << "/" << obj.month << "/" << obj.year;
	
	return os;
}
std::istream& operator >>(std::istream& in, Date& obj) {
	in >> obj.day >> obj.month >> obj.year;
	return in;
}

const void MovieCatalogue::serialize(std::ofstream& file)const {
	if (file.is_open()) {
		size_t numMovies = movies.size();
		file << "Name of cinema: " <<  cinemaName << "\n";
		file << "Date of projection: " << projectionDate << "\n";
		file << "Amount of movies on date: " << numMovies << "\n";
		file << "\n";
		for (const Movie& movie : movies)
		{
			movie.serialize(file);
			file << "\n";
		}
	}
	else {
		throw std::runtime_error("File is not opened!");
	}
}
const void MovieCatalogue::deserialize(std::ifstream& file) 
{
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		cinemaName = line.substr(line.find(':') + 2);

		std::getline(file, line);
		std::string startOfTimeStr = line.substr(line.find(':') + 2);
		std::string startOfMonthStr = line.substr(line.find('/') + 1);
		std::string startOfYearStr = line.substr(line.find('/') + 3);
		std::size_t firstSlash = startOfTimeStr.find('/');
		std::size_t secondSlash = startOfMonthStr.find('/');
		projectionDate.day = std::stoi(startOfTimeStr.substr(0, firstSlash));
		projectionDate.month = std::stoi(startOfMonthStr.substr(0, secondSlash));
		projectionDate.year = std::stoi(startOfYearStr);

		size_t numMovies;
		std::getline(file, line);
		numMovies = std::stoi(line.substr(line.find(':') + 2));
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (size_t i = 0; i < numMovies; i++)
		{
			if (line.empty()) {
				file.ignore('\n');
			}
			Movie movie;
			movie.deserialize(file);
			movies.push_back(movie);
		}
	}
	else {
		throw std::runtime_error("File could not open!");
	}
}