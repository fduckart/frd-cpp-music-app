#ifndef TRACK_H
#define TRACK_H

#include <string>

using namespace std;

class Track {
  public:
    Track(const int, const string);
    Track(const Track &);
        
    ~Track();
    
    void print() const;    
    int getNumber() const;
    const string getTitle() const;
    void setTitle(const string t);
    
  private:
    int  number;
    string title;
    
};

#endif
