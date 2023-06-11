#include <iostream>
#include "Movie.h"
#include "MovieCatalogue.h"
#include "Serializeable.h"
#include <fstream>

int main()
{
    Time time1{ 12, 50 };
    Time time2{ 4, 30 };
    Time time3{ 16, 55 };
    Movie movie1("The Man", "John Henderson ", 2009, time1, 90);
    Movie movie2("The Woman", "John Pork ", 2013, time2, 150);
    Movie movie3("The Woman-Man", "Darius Henderson-Pork ", 2009, time3, 180);
    std::ofstream outputFile1("Movies.txt", std::ios::binary);
    movie1.serialize(outputFile1);
    outputFile1.close();

    Movie newMovie;
    std::ifstream inputFile1("Movies.txt", std::ios::binary);
    newMovie.deserialize(inputFile1);

    std::ofstream outputFile2("Cinema.txt", std::ios::binary);
    MovieCatalogue Cinema1("CinemaCity");
    Cinema1.addMovie(movie1);
    Cinema1.addMovie(movie2);
    Cinema1.addMovie(movie3);
    Cinema1.serialize(outputFile2);
    outputFile2.close();

    MovieCatalogue newCinema;
    std::ifstream inputFile2("Cinema.txt", std::ios::binary);
    newCinema.deserialize(inputFile2);
    std::cout << newCinema.getCinemaName() << std::endl;
    std::cout << newCinema.getProjDate().day << "/" << newCinema.getProjDate().month << "/" << newCinema.getProjDate().year << std::endl;
    std::cout << std::endl;
    std::cout << newCinema.getMovies().at(0) << std::endl;
    std::cout << newCinema.getMovies().at(1) << std::endl;
    std::cout << newCinema.getMovies().at(2) << std::endl;
}
