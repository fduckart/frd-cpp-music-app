#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Command {
  public:
    Command(const string &);
    Command(const Command &);

    ~Command();

    const string getPrimary();
    const string getQualifier();
    const string getArguments();

    bool hasPrimary();
    bool hasQualifier();
    bool hasArguments();

    int  getTokenCount();
    bool isEmpty();

  private:
    string commandStr;      // Given command string.
    vector<string> tokens;  // Tokens of command.

    // Helper functions.
    const string trim(const string& s);
    vector<string> tokenize(const string &);
};

#endif
