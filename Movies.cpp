//
//  Movies.cpp
//  movies-library
//
//  Created by Lucas Tan on 11/7/17.
//  Copyright © 2017 Lucas Tan. All rights reserved.
//

#include "Movies.hpp"

Movies::Movies() {
    movie_id = 0;
    title = "";
    actors = {};
    genre = {};
    description = "";
    year = 0;
    rating = 0.0;
}

Movies::Movies(int id, string t, vector<string> a, vector<string> g, string d, int y, double r) {
    movie_id = id;
    title = t;
    actors = a;
    genre = g;
    description = d;
    year = y;
    rating = r;
}

void Movies::setTitle(string t) {
    title = t;
}

void Movies::setActors(vector<string> a) {
    actors = a;
}

void Movies::setGenre(vector<string> g) {
    genre = g;
}

void Movies::setDescription(string d) {
    description = d;
}

void Movies::setYear(int y) {
    year = y;
}

void Movies::setRating(double r) {
    rating = r;
}

int Movies::getMovieID() {
    return movie_id;
}

string Movies::getTitle() {
    return title;
}

vector<string> Movies::getActors() {
    return actors;
}

vector<string> Movies::getGenre() {
    return genre;
}

string Movies::getDescription() {
    return description;
}

int Movies::getYear() {
    return year;
}

double Movies::getRating() {
    return rating;
}

Movies::~Movies() {
    
}

int Movies::stringToInt(string s) {
    int i = atoi(s.c_str());
    return i;
}

double Movies::stringToDouble(string s) {
    double d = atof(s.c_str());
    return d;
}

vector<string> Movies::stringToVector(string s) {
    istringstream ss(s);
    string token;
    vector<string> v;

    while(getline(ss, token, ',')) {
        v.push_back(token);
    }
    
    return v;
}

string Movies::vectorToString(vector<string> v) {
    string s, new_s;
    
    for (int i = 0; i < v.size(); i++) {
        s += v[i];
        s += ",";
    }
    
    new_s = s.substr(0, s.size() - 1);
    return new_s;
}

ostream& operator << (ostream& out, Movies &m) {
    string actors = m.vectorToString(m.getActors());
    string genre = m.vectorToString(m.getGenre());
    
    out << m.movie_id << endl << m.title << endl << actors << endl << genre << endl << m.description << endl << m.year << endl << m.rating;
    
    return out;
}

istream& operator >> (istream& in, Movies &m) {
    string movie_id, actors, genre, year, rating;
    
    getline(in, movie_id);
    m.movie_id = m.stringToInt(movie_id);
    getline(in, m.title);
    getline(in, actors);
    m.actors = m.stringToVector(actors);
    getline(in, genre);
    m.genre = m.stringToVector(genre);
    getline(in, m.description);
    getline(in, year);
    m.year = m.stringToInt(year);
    getline(in, rating);
    m.rating = m.stringToDouble(rating);
    
    return in;
}
