#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include "record.h"
#include <limits>

using std::cout;

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

// Prototypes.
string itos(int i);
void testArtistSetter();
void testConstructor();
void testCopyConstructor();
void testTitleSetter();
void testGenreSetters();

// Main driver.
int main() 
{
    cout << "Start Record tests...\n";

    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
        testCopyConstructor();
        testTitleSetter();
        testArtistSetter();
        testGenreSetters();
    }
    
    cout << "End   Record test.\n";
   
    return 0;
}

void testArtistSetter() 
{
    cout << "Running testConstructor...";
   
    Artist a1(12, "Joe Jackson");
    Record r1("1", a1);
    Artist * ap = r1.getArtist();
    assert(a1.getArtistId() == 12);
    assert( "Joe Jackson" == ap->getName() );
   
    // Loop and check a few times...
    for (int i = 0; i < 10; i++) {
        Artist a(32 + i, "Richard Thompson");
        Record r(itos(i), a);
        Artist * aptr = r.getArtist();
        assert((32 + i) == aptr->getArtistId());
        assert( "Richard Thompson" == aptr->getName() );
    }
    
    cout << "OK\n";
}

void testConstructor() 
{
    cout << "Running testConstructor...";
  
    // Test some basic setting.
    Record r1("1", 11);
    assert( r1.getRecordId() == "1" );

    Record r2("2", 22);
    assert( r2.getRecordId() == "2" );
  
    Record r3("3", 33);
    assert( r3.getRecordId() == "3" );
  
    cout << "OK\n";
}

void testCopyConstructor() 
{
    cout << "Running testCopyConstuctor...";
  
    // Make a record and test values.
    Record r1("1", 11);
    r1.setTitle("Einstein on the Beach");
    assert( r1.getRecordId() == "1" );
    assert( r1.getTitle() == "Einstein on the Beach" );
  
    // Use the copy constructor and test values.
    Record r2(r1);
    assert( r2.getRecordId() == "1" );
    assert( r2.getTitle() == "Einstein on the Beach" );
  
    // Try it with a pointer.
    Record * r3 = new Record("3", 33);
    assert( r3 != 0 );
    r3->setTitle("Blonde on Blonde");
    Record r4(*r3);
    
    // Now delete the pointer and make sure 
    // the record made from it is still okay.
    delete r3;
    r3 = 0;
    assert( r4.getRecordId() == "3" );
    assert( r4.getTitle() == "Blonde on Blonde" ); 
    
    cout << "OK\n";
}

void testTitleSetter() 
{
    cout << "Running testTitleSetter...";
  
    Record r1("1", 11);
    r1.setTitle("Shoot out the Lights");
    assert( r1.getTitle() == "Shoot out the Lights" );
  
    Record r2("2", 22);
    r2.setTitle("ReallyLongTitleThatWontTruncateSomewhere");
    assert( r2.getTitle() == "ReallyLongTitleThatWontTruncateSomewhere" );
  
    cout << "OK\n";
}

void testGenreSetters()
{
    cout << "Running testGenreSetters...";
    
    // Test some basic setting.    
    Record r1("1", 111);
    r1.setGenre("Rock");
    assert( r1.getGenre() == "Rock" );

    // Use a string.
    string genre = "Reggae";
    r1.setGenre(genre);
    assert( r1.getGenre() == "Reggae" );
    
    // Change the string, record
    // genre should be unchanged.
    genre = "Punk";
    assert( r1.getGenre() == "Reggae" );
        
    cout << "OK\n"; 
}

// Convert an int to a string.
// Copied from Bjarne Stroustrup's C++ FAQ.
// http://public.research.att.com/~bs
string itos(int i)
{
    stringstream s;
    s << i;
    
    return s.str();
}

