#include "Movie.h"
#include "iostream"

void Movie::setTitle(std::string _title) {
	if (_title.length() < 101)
	{
		title = _title;
	}
	else {
		throw::std::length_error("Title is too long!");
	}
}
void Movie::setDirectorName(std::string _dirName) {
	if(_dirName.length()<101)
	{
		directorName = _dirName;
	}
	else {
		throw std::length_error("Name is too long!");
	}
}

Movie::Movie() 
{
	title = "";
	directorName = "";
	publishedYear = 0;
	startTime.hours = 0;
	startTime.minutes = 0;
	duration = 0;
}
Movie::Movie(const std::string& t, const std::string& dirN, int pYear, Time& sT, int dur) {
	setTitle(t);
	setDirectorName(dirN);
	publishedYear = pYear;
	startTime = sT;
	duration = dur;
}

const std::string Movie::getTitle()const {
	return title;
}
const std::string Movie::getDirName()const {
	return directorName;
}
const int Movie::getYearOfPub()const {
	return publishedYear;
}
const Time Movie::getStartTime()const {
	return startTime;
}
const int Movie::getDuration()const {
	return duration;
}
std::ostream& operator <<(std::ostream& os, const Time& obj) {
	os << obj.hours << ":" << obj.minutes;
	return os;
}
std::ostream& operator <<(std::ostream& os, const Movie& obj) {
	os << "Title: " << obj.title << "\n";
	os << "Director: " << obj.directorName << "\n";
	os << "Year of publishing: " << obj.publishedYear << "\n";
	os << "It starts at: " << obj.startTime.hours << ":" << obj.startTime.minutes << "\n";
	os << "Duration of movie: " << obj.duration << "\n";

	return os;
}
std::istream& operator >>(std::istream& in, Time& time) {
	in >> time.hours;
	in >> time.minutes;
	
	return in;
}
std::istream& operator >>(std::istream& in, Movie& obj) {
	in >> obj.title;
	in >> obj.directorName;
	in >> obj.startTime;
	in >> obj.publishedYear;
	in >> obj.duration;

	return in;
}

const void Movie::serialize(std::ofstream& file)const 
{
	if (file.is_open())
	{
		file << "Title: " << title << "\n";
		file << "Director Name: " << directorName << "\n";
		file << "Year of publishing: " << publishedYear << "\n";
		file << "Movie starts at: " << startTime << "\n";
		file << "Movie duration: " << duration << " minutes" << "\n";
	}
	else 
	{
		throw std::runtime_error("File is not opened!");
	}
}
const void Movie::deserialize(std::ifstream& file) {
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		title = line.substr(line.find(':') + 2);

		std::getline(file, line);
		directorName = line.substr(line.find(':') + 2);

		std::getline(file, line);
		publishedYear = std::stoi(line.substr(line.find(':') + 2));

		std::getline(file, line);
		std::string startOfTimeStr = line.substr(line.find(':') + 2);
		std::size_t colonPos = startOfTimeStr.find(':');
		startTime.hours = std::stoi(startOfTimeStr.substr(0, colonPos));
		startTime.minutes = std::stoi(startOfTimeStr.substr(colonPos +1));

		std::getline(file, line);
		duration = std::stoi(line.substr(line.find(':') + 2));

		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else {
		throw std::runtime_error("File is not opened!");
	}
}


