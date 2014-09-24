// Command.cpp
// This class was created in able to parse apart
// the individual tokens in a given user command.

#include <iostream>
#include <assert.h>
#include "command.h"

using namespace std;

// Standard constructor.
Command::Command(const string& s)
{
    commandStr = trim(s);
    tokens = tokenize(commandStr);
}

// Copy constructor.
Command::Command(const Command& command)
{
    commandStr = command.commandStr;
    tokens = tokenize(commandStr);
}

// Destructor.
Command::~Command()
{
    // Destructor; empty so far.
}

const string Command::getPrimary()
{
    if (getTokenCount() == 0)
        return "";
        
    return tokens[0];
}

const string Command::getQualifier()
{
    if (getTokenCount() < 2)
        return "";
        
    return tokens[1];
}

const string Command::getArguments()
{
    if (getTokenCount() < 2)
        return "";
        
    string::size_type pos = commandStr.find(getQualifier());
    
    int qualifierLen = getQualifier().size();
                
    return string(trim(commandStr.substr(pos + qualifierLen)));
}

int Command::getTokenCount()
{
    return tokens.size();
}

bool Command::isEmpty()
{
    return (tokens.size() == 0);
}

bool Command::hasPrimary() {
    return (getTokenCount() > 0);
}

bool Command::hasQualifier() {
    return (getTokenCount() > 1);
}

bool Command::hasArguments() {
    return (getTokenCount() > 2);
}

vector<string> Command::tokenize(const string &fullCommand)
{    
    // Command argument tokenizing.
    // Break user command into individual tokens.
    string str(fullCommand);
    string delimiters(" \t");
    vector<string> tokens;    
    
    // Skip any delimiters at beginning of string.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        
        // Skip delimiters.
        lastPos = str.find_first_not_of(delimiters, pos);
        
        // Find the next token.
        pos = str.find_first_of(delimiters, lastPos);
    }
        
    return tokens;
}

// Helper function to trim whitespace off ends of a string.
const string Command::trim(const string& s)  
{
    if (s.length() == 0)
        return s;
        
    int f = s.find_first_not_of(" \t");  // Find first char.
    int e = s.find_last_not_of(" \t");   // Find ending char.
    
    if (e == -1)
        return "";  // Didn't find any chars.
        
    return string(s, f, e - f + 1);  // Trim off spaces.
}

// End of Command class.
//===========================================================================
