//
//  Movies.hpp
//  movies-library
//
//  Created by Lucas Tan on 11/7/17.
//  Copyright © 2017 Lucas Tan. All rights reserved.
//

#ifndef Movies_hpp
#define Movies_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

class Movies {
private:
    int movie_id;
    string title;
    vector<string> actors;
    vector<string> genre;
    string description;
    int year;
    double rating;
    
public:
    Movies();
    Movies(int movie_id, string title, vector<string> actors, vector<string> genre, string description, int year, double rating);
    
    void setTitle(string title);
    void setActors(vector<string> actors);
    void setGenre(vector<string> genre);
    void setDescription(string description);
    void setYear(int year);
    void setRating(double rating);
    
    int getMovieID();
    string getTitle();
    vector<string> getActors();
    vector<string> getGenre();
    string getDescription();
    int getYear();
    double getRating();
    
    ~Movies();
    
    int stringToInt(string s);
    double stringToDouble(string s);
    vector<string> stringToVector(string s);
    string vectorToString(vector<string> v);
    
    friend ostream& operator << (ostream& out, Movies &m);
    friend istream& operator >> (istream& in, Movies &m);
};

#endif /* Movies_hpp */
