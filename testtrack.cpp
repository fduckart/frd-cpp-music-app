#include <assert.h>
#include <iostream>
#include <limits>
#include <string>

#include "track.h"

using std::cout;

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

// Prototypes.
void testConstructor();
void testCopyConstructor();
void testTitleSetter();

// Main driver.
int main() 
{ 
    cout << "Start Track tests...\n";
    
    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
        testCopyConstructor();
        testTitleSetter();
    }
          
    cout << "End   Track test.\n";
   
    return 0;
}

void testConstructor() 
{
    cout << "Running testConstructor...";
  
    // Test some basic setting.
    Track t1(1, "Beat on the Brat");
    assert( t1.getNumber() == 1 );
    assert( "Beat on the Brat" == t1.getTitle() );

    Track t2(2, "What's Going On?");
    assert( t2.getNumber() == 2 );
    assert( "What's Going On?" == t2.getTitle() );
  
    Track t3(3, "Superstition");
    assert( t3.getNumber() == 3 );
    assert( "Superstition" == t3.getTitle() );
    
    cout << "OK\n";
}

void testCopyConstructor() 
{
    cout << "Running testCopyConstuctor...";
  
    // Make a track and test values.
    Track t1(1, "");
    t1.setTitle("Einstein on the Beach");
    assert( t1.getNumber() == 1 );
    assert( t1.getTitle() == "Einstein on the Beach" );
  
    // Use the copy constructor and test values.
    Track t2(t1);
    assert( t2.getNumber() == 1 );
    assert( t2.getTitle() == "Einstein on the Beach" );
  
    // Try it with a pointer.
    Track * t3 = new Track(3, "");
    assert( t3 != 0);
    t3->setTitle("Blonde on Blonde");
    Track t4(*t3);
    
    // Now delete the pointer and make sure 
    // the record made from it is still okay.
    delete t3;
    t3 = 0;
    assert( t4.getNumber() == 3 );
    assert( t4.getTitle() == "Blonde on Blonde" ); 
    
    cout << "OK\n";
}

void testTitleSetter() 
{
    cout << "Running testTitleSetter...";
  
    Track t1(1, "");
    t1.setTitle("Shoot out the Lights");
    assert( t1.getTitle() == "Shoot out the Lights" );
  
    Track t2(2, "");
    t2.setTitle("ReallyLongTitleThatWontTruncate");
    assert( t2.getTitle() == "ReallyLongTitleThatWontTruncate" );
 
    cout << "OK\n";
}

