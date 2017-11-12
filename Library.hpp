//
//  Library.hpp
//  movies-library
//
//  Created by Lucas Tan on 11/7/17.
//  Copyright © 2017 Lucas Tan. All rights reserved.
//

#include "Movies.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

vector<Movies> load(vector<Movies> movies) {
    ifstream fis;
    fis.open("/Users/lucastan96/Documents/Computing/Computing Level 8 Year 3/C++/Projects/movies-library/movies-library/movies_2.txt");
    
    if (fis) {
        while (!fis.eof()) {
            Movies m;
            fis >> m;
            movies.push_back(m);
        }
    } else {
        cout << "\nError: Opening data save file failed!" << endl;
    }
    
    fis.close();
    return movies;
}

void save(vector<Movies> movies) {
    int count = 0;
    ofstream fout("/Users/lucastan96/Documents/Computing/Computing Level 8 Year 3/C++/Projects/movies-library/movies-library/movies_2.txt");
    
    if (fout) {
        for (Movies m:movies) {
            if (count != movies.size() - 1) {
                fout << m << endl;
            } else {
                fout << m;
            }
            
            count++;
        }
        fout.close();
    } else {
        cout << "\nError: Something went wrong with saving!" << endl;
    }
}

string beautifyVectorToString(vector<string> v) {
    string s, new_s;
        
    for (int i = 0; i < v.size(); i++) {
        s += v[i];
        s += ", ";
    }
        
    new_s = s.substr(0, s.size() - 2);
    return new_s;
}

void beautify(Movies m) {
    string actors = beautifyVectorToString(m.getActors());
    string genre = beautifyVectorToString(m.getGenre());
    
    cout << "Movie ID:\t\t " << m.getMovieID() << endl << "Title:\t\t\t " << m.getTitle() << endl << "Actors:\t\t\t " << actors << endl << "Genre:\t\t\t " << genre << endl << "Description:\t " << m.getDescription() << endl << "Year:\t\t\t " << m.getYear() << endl << "Rating:\t\t\t " << m.getRating() << "\n" << endl;
}

void minify(Movies m) {
    cout << "Movie ID:\t" << m.getMovieID() << endl << "Title:\t\t" << m.getTitle() << "\n" << endl;
}

void searchify(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

bool sortByTitle(Movies m1, Movies m2) {
    return m1.getTitle() < m2.getTitle();
}

bool sortByYear(Movies m1, Movies m2) {
    return m1.getYear() > m2.getYear();
}

bool sortByRating(Movies m1, Movies m2) {
    return m1.getRating() > m2.getRating();
}

vector<Movies> searchByTitle(vector<Movies> movies, string t) {
    vector<Movies>::iterator iter;
    vector<Movies> results;
    searchify(t);
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        string title = (*iter).getTitle();
        searchify(title);
        
        if (title == t || title.find(t) != string::npos) {
            results.push_back(*iter);
        }
    }

    return results;
}

vector<Movies> searchByActor(vector<Movies> movies, string a) {
    vector<Movies>::iterator iter;
    vector<Movies> results;
    searchify(a);
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        vector<string> actors = (*iter).getActors();
        
        for (int i = 0; i < actors.size(); i++) {
            searchify(actors[i]);
            
            if (actors[i] == a || actors[i].find(a) != string::npos) {
                results.push_back(*iter);
                break;
            }
        }
    }
    
    return results;
}

vector<Movies> searchByGenre(vector<Movies> movies, string g) {
    vector<Movies>::iterator iter;
    vector<Movies> results;
    searchify(g);
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        vector<string> genre = (*iter).getGenre();
        
        for (int i = 0; i < genre.size(); i++) {
            searchify(genre[i]);
            
            if (genre[i] == g || genre[i].find(g) != string::npos) {
                results.push_back(*iter);
                break;
            }
        }
    }
    
    return results;
}

vector<Movies> searchByYear(vector<Movies> movies, int year) {
    vector<Movies>::iterator iter;
    vector<Movies> results;
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        if ((*iter).getYear() == year) {
            results.push_back(*iter);
        }
    }
    
    return results;
}

vector<Movies> searchByRating(vector<Movies> movies, double rating) {
    vector<Movies>::iterator iter;
    vector<Movies> results;
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        if ((*iter).getRating() == rating) {
            results.push_back(*iter);
        }
    }
    
    return results;
}

vector<Movies> searchByYearGenre(vector<Movies> movies, int year, string g) {
    vector<Movies>::iterator iter;
    vector<Movies> results, results2;
    searchify(g);
    
    for (iter = movies.begin(); iter != movies.end(); iter++) {
        if ((*iter).getYear() == year) {
            results.push_back(*iter);
        }
    }
    
    if (results.empty()) {
        return results;
    }
    
    for (iter = results.begin(); iter != results.end(); iter++) {
        vector<string> genre = (*iter).getGenre();
        
        for (int i = 0; i < genre.size(); i++) {
            searchify(genre[i]);
            
            if (genre[i] == g || genre[i].find(g) != string::npos) {
                results2.push_back(*iter);
                break;
            }
        }
    }
    
    return results2;
}

int getPosition(vector<Movies> &movies, int movie_id) {
    int position = 0;
    
    for (vector<Movies>::iterator iter = movies.begin(); iter != movies.end(); iter++) {
        if ((*iter).getMovieID() == movie_id) {
            return position;
        }
        position++;
    }
    
    return -1;
}

void menu() {
    cout << "***** Main Menu ***********************************************\n" << endl;
    cout << "1. View All Movies" << endl;
    cout << "2. Search for Movies" << endl;
    cout << "3. Add a New Movie" << endl;
    cout << "4. Check for Movie ID" << endl;
    cout << "5. Edit a Movie" << endl;
    cout << "6. Delete a Movie" << endl;
    cout << "7. Export to HTML" << endl;
    cout << "8. Exit\n" << endl;
    cout << "Please enter your option (1 - 8): ";
}

void option1(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        int option = 0;
        
        while (option != 5) {
            cout << "***** Selected Option: View All Movies ************************\n" << endl;
            cout << "1. View by Movie ID" << endl;
            cout << "2. View by Movie Title (A - Z)" << endl;
            cout << "3. View by Release Year (Newest - Oldest)" << endl;
            cout << "4. View by Rating (Highest - Lowest)" << endl;
            cout << "5. Go Back\n" << endl;
            cout << "Please enter your option (1 - 5): ";
            
            cin >> option;
            
            while (cin.fail()) {
                cout << "\nError: Input should be a integer!\n" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter your option again: ";
                cin >> option;
            }
            
            if (option == 1) {
                cout << "\n***** View by Movie ID ****************************************\n" << endl;
                for (Movies m:movies) {
                    beautify(m);
                }
            } else if (option == 2) {
                cout << "\n***** View by Movie Title (A - Z) *****************************\n" << endl;
                sort(movies.begin(), movies.end(), sortByTitle);
                for (Movies m:movies) {
                    beautify(m);
                }
            } else if (option == 3) {
                cout << "\n***** View by Release Year (Newest - Oldest) ******************\n" << endl;
                sort(movies.begin(), movies.end(), sortByYear);
                for (Movies m:movies) {
                    beautify(m);
                }
            } else if (option == 4) {
                cout << "\n***** View by Rating (Highest - Oldest) ***********************\n" << endl;
                sort(movies.begin(), movies.end(), sortByRating);
                for (Movies m:movies) {
                    beautify(m);
                }
            } else if (option == 5) {
                cout << "" << endl;
            } else {
                cout << "\nError: Please enter a valid option!\n" << endl;
            }
        }
    }
}

void option2(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        int option = 0;
        
        while (option != 7) {
            cout << "***** Selected Option: Search for Movies **********************\n" << endl;
            cout << "1. Search by Movie Title" << endl;
            cout << "2. Search by Actor" << endl;
            cout << "3. Search by Genre" << endl;
            cout << "4. Search by Release Year" << endl;
            cout << "5. Search by Rating" << endl;
            cout << "6. Search by Year & Genre" << endl;
            cout << "7. Go Back\n" << endl;
            cout << "Please enter your option (1 - 7): ";
            
            cin >> option;
            
            while (cin.fail()) {
                cout << "\nError: Input should be a integer!\n" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter your option again: ";
                cin >> option;
            }
            
            if (option == 1) {
                string title;
                
                cout << "\n***** Search by Movie Title ***********************************\n" << endl;
                cout << "Please enter the movie title: ";
                cin.ignore(1000, '\n');
                getline(cin, title);
                
                vector<Movies> results = searchByTitle(movies, title);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 2) {
                string actor;
                
                cout << "\n***** Search by Actor *****************************************\n" << endl;
                cout << "Please enter the movie actor: ";
                cin.ignore(1000, '\n');
                getline(cin, actor);
                
                vector<Movies> results = searchByActor(movies, actor);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 3) {
                string genre;
                
                cout << "\n***** Search by Genre *****************************************\n" << endl;
                cout << "Please enter the movie genre: ";
                cin.ignore(1000, '\n');
                getline(cin, genre);
                
                vector<Movies> results = searchByGenre(movies, genre);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 4) {
                int year;
                
                cout << "\n***** Search by Release Year **********************************\n" << endl;
                cout << "Please enter the movie release year: ";
                cin >> year;
                
                while (cin.fail()) {
                    cout << "\nError: Input should be a integer!\n" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter the movie release year again: ";
                    cin >> year;
                }
                
                vector<Movies> results = searchByYear(movies, year);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 5) {
                double rating;
                
                cout << "\n***** Search by Rating ****************************************\n" << endl;
                cout << "Please enter the movie rating: ";
                cin >> rating;
                
                while (cin.fail()) {
                    cout << "\nError: Input should be a intger/double!\n" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter the movie rating again: ";
                    cin >> rating;
                }
                
                vector<Movies> results = searchByRating(movies, rating);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 6) {
                int year;
                string genre;
                
                cout << "\n***** Search by Year & Genre **********************************\n" << endl;
                cout << "Please enter the movie relese year: ";
                cin >> year;
                
                while (cin.fail()) {
                    cout << "\nError: Input should be a integer!\n" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter the movie release year again: ";
                    cin >> year;
                }
                
                cout << "Please enter the movie genre: ";
                cin.ignore(1000, '\n');
                getline(cin, genre);
                
                vector<Movies> results = searchByYearGenre(movies, year, genre);
                
                cout << "\n***** Search Results ******************************************\n" << endl;
                if (!results.empty()) {
                    for (Movies m:results) {
                        beautify(m);
                    }
                } else {
                    cout << "Error: No results found, please try again!\n" << endl;
                }
            } else if (option == 7) {
                cout << "" << endl;
            } else {
                cout << "\nError: Please enter a valid option!\n" << endl;
            }
        }
    }
}

void option3(vector<Movies> &movies) {
    string title, description, actors_s, genre_s;
    vector<string> actors, genre;
    int movie_id, year, actors_i = 1, genre_i = 1, option = 0;
    double rating;
    bool actors_b = false, genre_b = false;
    
    cout << "***** Selected Option: Add a New Movie ************************\n" << endl;
    cout << "Please enter the movie details: " << endl;
    cout << "\nTitle: ";
    cin.ignore(1000, '\n');
    getline(cin, title);
    do {
        cout << "\nActor " << actors_i << ": ";
        getline(cin, actors_s);
        actors.push_back(actors_s);
        cout << "\nDo you want to add an additional actor?:" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No\n" << endl;
        cout << "Please enter your option (1 - 2): ";
        cin >> option;
        
        while (cin.fail()) {
            cout << "\nError: Input should be a integer!\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter your option again: ";
            cin >> option;
        }
        
        if (option == 1) {
            actors_i++;
        } else if (option == 2) {
            actors_b = true;
        } else {
            cout << "\nError: Please enter a valid option!\n" << endl;
        }
        cin.ignore(1000, '\n');
    } while (actors_b == false);
    do {
        cout << "\nGenre " << genre_i << ": ";
        getline(cin, genre_s);
        genre.push_back(genre_s);
        cout << "\nDo you want to add an additional genre?:" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No\n" << endl;
        cout << "Please enter your option (1 - 2): ";
        cin >> option;
        if (option == 1) {
            genre_i++;
        } else if (option == 2) {
            genre_b = true;
        } else {
            cout << "\nError: Please enter a valid option!\n" << endl;
        }
        cin.ignore(1000, '\n');
    } while (genre_b == false);
    cout << "\nDescription: ";
    getline(cin, description);
    cout << "\nYear: ";
    cin >> year;
    while (cin.fail()) {
        cout << "\nError: Input should be a integer!\n" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Year: ";
        cin >> year;
    }
    cout << "\nRating: ";
    cin >> rating;
    while (cin.fail()) {
        cout << "\nError: Input should be a integer/double!\n" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Rating: ";
        cin >> rating;
    }
    cout << "\nNotice: Movie has been added and saved successfully!\n" << endl;
    
    if (movies[0].getMovieID() == 0) {
        movies.clear();
        movie_id = 1;
    } else {
        movie_id = (movies[movies.size() - 1].getMovieID() + 1);
    }
    
    Movies m(movie_id, title, actors, genre, description, year, rating);
    movies.push_back(m);
    
    save(movies);
}

void option4(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        string title;
        
        cout << "***** Selected Option: Check for Movie ID *********************\n" << endl;
        cout << "Please enter the movie title to confirm movie ID: ";
        cin.ignore(1000, '\n');
        getline(cin, title);
        
        vector<Movies> results = searchByTitle(movies, title);
        
        cout << "\n***** Search Results ******************************************\n" << endl;
        if (!results.empty()) {
            for (Movies m:results) {
                minify(m);
            }
            cout << "Notice: Please note down the movie ID for editing or deleting purposes!\n" << endl;
        } else {
            cout << "Error: No results found, please try again!\n" << endl;
        }
    }
}

void option5(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        string title;
        int movie_id;
        
        cout << "***** Selected Option: Edit a Movie ***************************\n" << endl;
        cout << "Please enter the movie ID you want to edit: ";
        cin >> movie_id;
        
        while (cin.fail()) {
            cout << "\nError: Input should be a integer!\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter the movie ID again: ";
            cin >> movie_id;
        }
        
        int position = getPosition(movies, movie_id);
        
        if (position == -1) {
            cout << "\nError: Invalid movie ID, please try again!\n" << endl;
        } else {
            Movies &m = movies[position];
            int option = 0;
            
            while (option != 7) {
                cout << "\nSelected Movie for Editing: " << m.getTitle() << endl;
                cout << "\n1. Edit Title" << endl;
                cout << "2. Edit Actors" << endl;
                cout << "3. Edit Genre" << endl;
                cout << "4. Edit Description" << endl;
                cout << "5. Edit Release Year" << endl;
                cout << "6. Edit Rating" << endl;
                cout << "7. Go Back\n" << endl;
                cout << "Please enter your option (1 - 7): ";
                
                cin >> option;
                
                while (cin.fail()) {
                    cout << "\nError: Input should be a integer!\n" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Please enter your option again: ";
                    cin >> option;
                }
                
                if (option == 1) {
                    string title;
                    
                    cout << "\nCurrent Movie Title: " << m.getTitle() << endl;
                    cout << "\nPlease enter new title: ";
                    cin.ignore(1000, '\n');
                    getline(cin, title);
                    m.setTitle(title);
                    save(movies);
                    cout << "\nNotice: Title has been updated and saved successfully!" << endl;
                } else if (option == 2) {
                    string actors_s;
                    int count = 1, option_2 = 0;
                    bool actors_b = false;
                    
                    vector<string> actors = m.getActors();
                    
                    while (option_2 != 4) {
                        string display;
                        if (actors.empty()) {
                            display = "N/A";
                        } else {
                            display = beautifyVectorToString(actors);
                        }
                        
                        cout << "\nCurrent Movie Actors: " << display << endl;
                        cout << "\n1. Add Actors" << endl;
                        cout << "2. Edit Actors" << endl;
                        cout << "3. Delete Actors" << endl;
                        cout << "4. Go Back\n" << endl;
                        cout << "Please enter your option (1 - 4): ";
                        
                        cin >> option_2;
                        
                        while (cin.fail()) {
                            cout << "\nError: Input should be a integer!\n" << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter your option again: ";
                            cin >> option_2;
                        }
                        
                        if (option_2 == 1) {
                            cin.ignore(1000, '\n');
                            do {
                                cout << "\nNew Actor " << count << ": ";
                                getline(cin, actors_s);
                                actors.push_back(actors_s);
                                cout << "\nDo you want to add an additional actor?:" << endl;
                                cout << "1. Yes" << endl;
                                cout << "2. No\n" << endl;
                                cout << "Please enter your option (1 - 2): ";
                                cin >> option;
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option;
                                }
                                if (option == 1) {
                                    count++;
                                } else if (option == 2) {
                                    actors_b = true;
                                } else {
                                    cout << "\nError: Please enter a valid option!\n" << endl;
                                }
                                cin.ignore(1000, '\n');
                            } while (actors_b == false);
                            
                            m.setActors(actors);
                            save(movies);
                            cout << "\nNotice: Actors has been added and saved successfully!" << endl;
                        } else if (option_2 == 2) {
                            if (actors.empty()) {
                                cout << "\nNotice: No actors has been added yet!" << endl;
                            } else {
                                int option_3 = 0, count = 1;
                                string name;
                                
                                cout << "\nWhich actor do you want to edit?:" << endl;
                                for (int i = 0; i < actors.size(); i++) {
                                    cout << count << ". " << actors[i] << endl;
                                    count++;
                                }
                                count--;
                                
                                if (count != 1) {
                                    cout << "\nPlease enter your option (1 - " << count << "): ";
                                } else {
                                    cout << "\nPlease enter your option: ";
                                }
                                cin >> option_3;
                                
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option_3;
                                }
                                
                                if (actors.size() >= option_3) {
                                    cout << "\nPlease enter new name: ";
                                    cin.ignore(1000, '\n');
                                    getline(cin, name);
                                    actors[option_3 - 1] = name;
                                    m.setActors(actors);
                                    save(movies);
                                    cout << "\nNotice: Actor has been updated and saved successfully!" << endl;
                                } else {
                                    cout << "\nError: Please enter a valid option!" << endl;
                                }
                            }
                        } else if (option_2 == 3) {
                            if (actors.empty()) {
                                cout << "\nNotice: No actors has been added yet!" << endl;
                            } else {
                                int option_3 = 0, count = 1, option_4 = 0;
                                
                                cout << "\nWhich actor do you want to delete?:" << endl;
                                for (int i = 0; i < actors.size(); i++) {
                                    cout << count << ". " << actors[i] << endl;
                                    count++;
                                }
                                count--;
                                
                                if (count != 1) {
                                    cout << "\nPlease enter your option (1 - " << count << "): ";
                                } else {
                                    cout << "\nPlease enter your option: ";
                                }
                                cin >> option_3;
                                
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option_3;
                                }
                                
                                if (actors.size() >= option_3) {
                                    cout << "\nAre you sure you want to delete the actor '" << actors[option_3 - 1] << "'?" << endl;
                                    cout << "1. Yes" << endl;
                                    cout << "2. No\n" << endl;
                                    cout << "Please enter your option (1 - 2): ";
                                    cin >> option_4;
                                    
                                    while (cin.fail()) {
                                        cout << "\nError: Input should be a integer!\n" << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Please enter your option again: ";
                                        cin >> option_4;
                                    }
                                    
                                    if (option_4 == 1) {
                                        actors.erase(actors.begin() + (option_3 - 1));
                                        save(movies);
                                        cout << "\nNotice: Actor has been deleted successfully!" << endl;
                                    } else if (option_4 == 2) {
                                        cout << "\nNotice: Process has been cancelled!" << endl;
                                    } else {
                                        cout << "\nError: Please enter a valid option!" << endl;
                                    }
                                } else {
                                    cout << "\nError: Please enter a valid option!" << endl;
                                }
                            }
                        } else if (option_2 == 4) {
                            cout << "" << endl;
                        } else {
                            cout << "\nError: Please enter a valid option!\n" << endl;
                        }
                    }
                } else if (option == 3) {
                    string genre_s;
                    int count = 1, option_2 = 0;
                    bool genre_b = false;
                    
                    vector<string> genre = m.getGenre();
                    
                    while (option_2 != 4) {
                        string display;
                        if (genre.empty()) {
                            display = "N/A";
                        } else {
                            display = beautifyVectorToString(genre);
                        }
                        
                        cout << "\nCurrent Movie Genre: " << display << endl;
                        cout << "\n1. Add Genre" << endl;
                        cout << "2. Edit Genre" << endl;
                        cout << "3. Delete Genre" << endl;
                        cout << "4. Go Back\n" << endl;
                        cout << "Please enter your option (1 - 4): ";
                        
                        cin >> option_2;
                        
                        while (cin.fail()) {
                            cout << "\nError: Input should be a integer!\n" << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter your option again: ";
                            cin >> option_2;
                        }
                        
                        if (option_2 == 1) {
                            cin.ignore(1000, '\n');
                            do {
                                cout << "\nNew Genre " << count << ": ";
                                getline(cin, genre_s);
                                genre.push_back(genre_s);
                                cout << "\nDo you want to add an additional genre?:" << endl;
                                cout << "1. Yes" << endl;
                                cout << "2. No\n" << endl;
                                cout << "Please enter your option (1 - 2): ";
                                cin >> option;
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option;
                                }
                                if (option == 1) {
                                    count++;
                                } else if (option == 2) {
                                    genre_b = true;
                                } else {
                                    cout << "\nError: Please enter a valid option!\n" << endl;
                                }
                                cin.ignore(1000, '\n');
                            } while (genre_b == false);
                            
                            m.setGenre(genre);
                            save(movies);
                            cout << "\nNotice: Genre has been added and saved successfully!" << endl;
                        } else if (option_2 == 2) {
                            if (genre.empty()) {
                                cout << "\nNotice: No genre has been added yet!" << endl;
                            } else {
                                int option_3 = 0, count = 1;
                                string name;
                                
                                cout << "\nWhich genre do you want to edit?:" << endl;
                                for (int i = 0; i < genre.size(); i++) {
                                    cout << count << ". " << genre[i] << endl;
                                    count++;
                                }
                                count--;
                                
                                if (count != 1) {
                                    cout << "\nPlease enter your option (1 - " << count << "): ";
                                } else {
                                    cout << "\nPlease enter your option: ";
                                }
                                cin >> option_3;
                                
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option_3;
                                }
                                
                                if (genre.size() >= option_3) {
                                    cout << "\nPlease enter new genre: ";
                                    cin.ignore(1000, '\n');
                                    getline(cin, name);
                                    genre[option_3 - 1] = name;
                                    m.setGenre(genre);
                                    save(movies);
                                    cout << "\nNotice: Genre has been updated and saved successfully!" << endl;
                                } else {
                                    cout << "\nError: Please enter a valid option!" << endl;
                                }
                            }
                        } else if (option_2 == 3) {
                            if (genre.empty()) {
                                cout << "\nNotice: No genre has been added yet!" << endl;
                            } else {
                                int option_3 = 0, count = 1, option_4 = 0;
                                
                                cout << "\nWhich genre do you want to delete?:" << endl;
                                for (int i = 0; i < genre.size(); i++) {
                                    cout << count << ". " << genre[i] << endl;
                                    count++;
                                }
                                count--;
                                
                                if (count != 1) {
                                    cout << "\nPlease enter your option (1 - " << count << "): ";
                                } else {
                                    cout << "\nPlease enter your option: ";
                                }
                                cin >> option_3;
                                
                                while (cin.fail()) {
                                    cout << "\nError: Input should be a integer!\n" << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cout << "Please enter your option again: ";
                                    cin >> option_3;
                                }
                                
                                if (genre.size() >= option_3) {
                                    cout << "\nAre you sure you want to delete the genre '" << genre[option_3 - 1] << "'?" << endl;
                                    cout << "1. Yes" << endl;
                                    cout << "2. No\n" << endl;
                                    cout << "Please enter your option (1 - 2): ";
                                    cin >> option_4;
                                    
                                    while (cin.fail()) {
                                        cout << "\nError: Input should be a integer!\n" << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Please enter your option again: ";
                                        cin >> option_4;
                                    }
                                    
                                    if (option_4 == 1) {
                                        genre.erase(genre.begin() + (option_3 - 1));
                                        save(movies);
                                        cout << "\nNotice: Genre has been deleted successfully!" << endl;
                                    } else if (option_4 == 2) {
                                        cout << "\nNotice: Process has been cancelled!" << endl;
                                    } else {
                                        cout << "\nError: Please enter a valid option!" << endl;
                                    }
                                } else {
                                    cout << "\nError: Please enter a valid option!" << endl;
                                }
                            }
                        } else if (option_2 == 4) {
                            cout << "" << endl;
                        } else {
                            cout << "\nError: Please enter a valid option!\n" << endl;
                        }
                    }
                } else if (option == 4) {
                    string description;
                    
                    cout << "\nCurrent Movie Description: " << m.getDescription() << endl;
                    cout << "Please enter new description: ";
                    cin.ignore(1000, '\n');
                    getline(cin, description);
                    m.setDescription(description);
                    save(movies);
                    cout << "\nNotice: Description has been updated and saved successfully!" << endl;
                } else if (option == 5) {
                    int year;
                    
                    cout << "\nCurrent Movie Release Year: " << m.getYear() << endl;
                    cout << "Please enter new release year: ";
                    cin >> year;
                    while (cin.fail()) {
                        cout << "\nError: Input should be a integer!\n" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Please enter new release year again: ";
                        cin >> year;
                    }
                    m.setYear(year);
                    save(movies);
                    cout << "\nNotice: Release year has been updated and saved successfully!" << endl;
                } else if (option == 6) {
                    double rating;
                    
                    cout << "\nCurrent Movie Rating: " << m.getRating() << endl;
                    cout << "Please enter new rating: ";
                    cin >> rating;
                    while (cin.fail()) {
                        cout << "\nError: Input should be a integer/double!\n" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Please enter new ratinf again: ";
                        cin >> rating;
                    }
                    m.setRating(rating);
                    save(movies);
                    cout << "\nNotice: Rating has been updated and saved successfully!" << endl;
                } else if (option == 7) {
                    cout << "" << endl;
                } else {
                    cout << "\nError: Please enter a valid option!\n" << endl;
                }
            }
        }
    }
}

void option6(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        int movie_id, option = 0;
        
        cout << "***** Selected Option: Delete a Movie *************************\n" << endl;
        cout << "Please enter the movie ID you want to delete: ";
        cin >> movie_id;
        
        while (cin.fail()) {
            cout << "\nError: Input should be a integer!\n" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter the movie ID again: ";
            cin >> movie_id;
        }
        
        int position = getPosition(movies, movie_id);
        
        if (position == -1) {
            cout << "\nError: Invalid movie ID, please try again!\n" << endl;
        } else {
            Movies &m = movies[position];
            
            cout << "\nAre you sure you want to delete the movie '" << m.getTitle() << "'?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No\n" << endl;
            cout << "Please enter your option (1 - 2): ";
            cin >> option;
            
            while (cin.fail()) {
                cout << "\nError: Input should be a integer!\n" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter your option again: ";
                cin >> option;
            }
            
            if (option == 1) {
                movies.erase(movies.begin() + position);
                save(movies);
                cout << "\nNotice: Movie has been deleted successfully!\n" << endl;
            } else if (option == 2) {
                cout << "\nNotice: Process has been cancelled!\n" << endl;
            } else {
                cout << "\nError: Please enter a valid option!\n" << endl;
            }
        }
    }
}

void option7(vector<Movies> &movies) {
    if (movies[0].getMovieID() == 0) {
        cout << "Notice: No movies has been added yet!\n" << endl;
    } else {
        sort(movies.begin(), movies.end(), sortByTitle);
        
        ofstream html;
        html.open ("/Users/lucastan96/Documents/Computing/Computing Level 8 Year 3/C++/Projects/movies-library/movies-library/movies.html");
        html << "<!DOCTYPE html><html><head><title>Movies Library</title>";
        html << "<style>html {width: 100%; text-align: center; color: #263C4E;} table, th, td {border: 1px solid #263C4E; border-collapse: collapse;} th, td {padding: 5px;} table tr:nth-child(even) {background-color: white;} table tr:nth-child(odd) {background-color: #f2f2f2;} table th {background-color: #263C4E; color: white;}</style>";
        html << "</head><body><h1>Movies Library</h1><table><tr>";
        html << "<th>Movie ID</th>";
        html << "<th>Title</th>";
        html << "<th>Actors</th>";
        html << "<th>Genre</th>";
        html << "<th>Description</th>";
        html << "<th>Year</th>";
        html << "<th>Rating</th>";
        html << "</tr>";
        
        for (int i = 0; i < movies.size(); i++) {
            string actors = beautifyVectorToString(movies[i].getActors());
            string genre = beautifyVectorToString(movies[i].getGenre());
            
            html << "<tr>";
            html << "<td>" << movies[i].getMovieID() << "</td>";
            html << "<td>" << movies[i].getTitle() << "</td>";
            html << "<td>" << actors << "</td>";
            html << "<td>" << genre << "</td>";
            html << "<td>" << movies[i].getDescription() << "</td>";
            html << "<td>" << movies[i].getYear() << "</td>";
            html << "<td>" << movies[i].getRating() << "</td>";
            html << "</tr>";
        }
        
        html << "</table></body></html>";
        html.close();
        
        cout << "Notice: Your data has been exported to an HTML file. You can now view your data in a tidy table format!\n" << endl;
    }
}
