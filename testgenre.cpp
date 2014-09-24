#include <assert.h>
#include "genre.h"
#include <limits>

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

void testConstructor();  

int main() 
{ 
    cout << "Start  Genre tests...\n";
      
    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
    }
    
    cout << "End of Genre tests.." << '\n';
 
    return 0;
}

void testConstructor() 
{
    cout << "Running testConstructor...";
    
    // Test some basic setting.
    Genre g1("Rock");
    assert( g1.getName() == "Rock" );

    Genre g2("Jazz");
    assert( g2.getName() == "Jazz" );
    
    Genre g3("Folk-Rock");
    assert( g3.getName() == "Folk-Rock" );

    // No name test.
    Genre g4("");
    assert( g4.getName() == "" );
      
    // Test the size limit on the names.
    Genre g5("ReallyLongGenreThatWontTruncate");
    assert( g5.getName() == "ReallyLongGenreThatWontTruncate" );
      
    // Try manipulating backing char array, shouldn't be able.
    char punk[]  = "Punk Rock";
    Genre g6(punk);
    punk[6] = '\4'; 
    assert( g6.getName() == "Punk Rock" );

    cout << "OK\n"; 
}

