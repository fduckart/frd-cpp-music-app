#include <iostream>
#include <string.h>
#include <assert.h>
#include "command.h"
#include <limits>

using std::cout;

const int TEST_RUNS = 1;
// const int TEST_RUNS = numeric_limits<int>::max();

void testConstructor();  

int main() 
{ 
    cout << "Start  Command tests...\n";
    
    for (int i = 0; i < TEST_RUNS; i++) {
        testConstructor();
    }
    
    cout << "End of Command tests.." << '\n';
 
    return 0;
}

void testConstructor() 
{
    cout << "Running testConstructor...";
    
    // Test some basic setting.
    Command c1("search artist Eno");
    assert( c1.getPrimary() == "search" );
    assert( c1.getQualifier() == "artist" );
    assert( c1.getArguments() == "Eno" );
    assert( c1.isEmpty() == false );
    
    // User puts a tab in command.
    Command c2("1search1\tartist Thompson");
    assert( c2.getPrimary() == "1search1" );
    assert( c2.getQualifier() == "artist" );
    assert( c2.getArguments() == "Thompson" );
    assert( c2.isEmpty() == false );
    
    // User puts in extra spaces.
    // Note that trailing spaces are stripped.
    Command c3("  search    3artist3  Brian Eno  ");
    assert( c3.getPrimary() == "search" );
    assert( c3.getQualifier() == "3artist3" );
    assert( c3.getArguments() == "Brian Eno" );
    assert( c3.isEmpty() == false );
    
    // Spaces in middle of argument are preserved.
    Command c4("  search    artist  Richard    Thompson  ");
    assert( c4.getPrimary() == "search" );
    assert( c4.getQualifier() == "artist" );
    assert( c4.getArguments() == "Richard    Thompson" );
    assert( c4.isEmpty() == false );

    // Tabs in middle of argument are preserved.
    Command c5("  search     5artist5  Richard \t   Thompson  ");
    assert( c5.getPrimary() == "search" );
    assert( c5.getQualifier() == "5artist5" );
    assert( c5.getArguments() == "Richard \t   Thompson" );
    assert( c5.isEmpty() == false );
      
    // User puts in extra spaces and tabs.
    Command c6(" \t search  \t   6artist6  Miles Davis");
    assert( c6.getPrimary() == "search" );
    assert( c6.getQualifier() == "6artist6" );
    assert( c6.getArguments() == "Miles Davis" );
    assert( c6.isEmpty() == false );
    
    // User only enters primary command.
    Command c7("add");
    assert( c7.getPrimary() == "add" );
    assert( c7.getQualifier() == "" );
    assert( c7.getArguments() == "" );
    assert( c7.getTokenCount() == 1 );    
    assert( c7.isEmpty() == false );

    // User enters primary and qualifier commands.
    Command c8("delete 10001");
    assert( c8.getPrimary()   == "delete" );
    assert( c8.getQualifier() == "10001" );
    assert( c8.getArguments() == "" );
    assert( c8.getTokenCount() == 2 );
    assert( c8.isEmpty() == false );
    
    // An empty command, but shouldn't happen in epected use.
    // Need to make sure it doesn't through anything, though.
    Command c9("");
    assert( c9.getPrimary()   == "" );
    assert( c9.getQualifier() == "" );
    assert( c9.getArguments() == "" );
    assert( c9.getTokenCount() == 0 );
    assert( c9.isEmpty() == true );
    
    // User entered spaces/tabs.  
    // Should be an empty command.
    Command c10("    ");
    assert( c10.getPrimary()   == "" );
    assert( c10.getQualifier() == "" );
    assert( c10.getArguments() == "" );
    assert( c10.getTokenCount() == 0 );
    assert( c10.isEmpty() == true );
    
    Command c11(" \t   ");
    assert( c11.getPrimary()   == "" );
    assert( c11.getQualifier() == "" );
    assert( c11.getArguments() == "" );
    assert( c11.getTokenCount() == 0 );
    assert( c11.isEmpty() == true );
    
    cout << "OK\n"; 
}
