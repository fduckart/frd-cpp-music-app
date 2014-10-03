#include <iostream>
#include <assert.h>
#include "artist.h"
#include <limits>

using std::cout;

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

void testConstructor();  
void testNameSetters();

int main() 
{ 
    cout << "Start  Artist tests...\n";
      
    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
        testNameSetters();
    }
    
    cout << "End of Artist tests.." << '\n';
 
    return 0;
}

void testNameSetters() 
{
    cout << "Running testNameSetters...";
    
    // Test some basic setting.
    Artist a1(1, "Frank Duckart");
    assert( a1.getName() == "Frank Duckart" );

    Artist a2(2, "Sandy Yang");
    assert( a2.getName() == "Sandy Yang" );
    
    Artist a3(3, "Richard Thompson");
    assert( a3.getName() == "Richard Thompson" );

    // No name test.
    Artist a4(4, "");
    assert( a4.getName() == "" );
      
    // Test a long name.
    Artist a5(5, "ReallyLongNameThatShouldn'tTruncate");
    assert(a5.getName() == "ReallyLongNameThatShouldn'tTruncate");
      
    // Try manipulating backing char array, shouldn't be able.
    char bunny[]  = "Bunny Wailer";
    Artist a6(6, bunny);
    bunny[6] = '\0'; 
    assert( a6.getName() == "Bunny Wailer" );

    // Try manipulating a string that's passed in.
    string s1("PJ Harvey");
    Artist a7(7, s1);
    s1[2] = '-';
    assert( s1 == "PJ-Harvey" );
    assert( a7.getName() == "PJ Harvey" );
    
    cout << "OK\n"; 
}

void testConstructor() 
{
    cout << "Running testConstructor...";
    
    // Default artist id is 0 since it 
    // wasn't passed into the constructor.
    // This will be an error as the system
    // goes through further development.
    Artist a(0, "Frank Duckart");
    assert( a.getArtistId() == 0 );
    
    // Need to pass in artist id when making object.
    Artist a1(444, "Sandy Yang");
    assert( a1.getArtistId() == 444 );
    
    cout << "OK\n";
}

