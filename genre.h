#ifndef GENRE_H
#define GENRE_H

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Genre {
  public:
    Genre(const string);
    Genre(const Genre &);

    ~Genre();

    void print() const;
    const string getName() const;

  private:
    void setName(const string);
    string name;
};

#endif
