//
// Created by matan on 12/18/19.
//

#include "lexer.h"
using namespace std;

/*
 * this method execute the main lexer functionality
 * it takes the text file and parses it into tokens:
 */
list<string> lexer::execute() {
  ifstream inputFile(lexer::fileName);
  string line;
  bool apos = false;
  //running through all the lines:
  while (getline(inputFile, line))
  {
    line = (lexer::removeSpaces)(line);
    unsigned int currLocation = 0;
    bool doc = false;
    bool equalSign = false;
    //runing through the current line:
    while (currLocation < line.size() && !doc)
    {
      stringstream stringBuilder;
      string result = "notSpecial";
      //handeling "...", =:
      if(!apos && !equalSign)
      {
        result = isSpecialCharacter(line, currLocation);
      }
      //the basic case of reading the line:
      while((apos || equalSign || result == "notSpecial") && currLocation < line.size() && !doc)
      {
        //handeling '....":
        if(line[currLocation] == '\"')
        {
          apos = ! apos;
        }
        //handeling documentations:
        if(line[currLocation] == '/' && line[currLocation+1] == '/')
        {
          doc = true;
        }
        else
        {
          stringBuilder<<line[currLocation];
          currLocation++;
        }
        if(!apos & !equalSign)
        {
          result = isSpecialCharacter(line, currLocation);
        }
      }

      //handeling //,=:
      if(result == "=")
      {
        equalSign = true;
      }
      if(result == "//")
      {
        doc = true;
      }
      if(stringBuilder.str() != "" && result != "//")
      {
        (lexer::tokensList).push_back(stringBuilder.str());
      }
      if("special" != result && "notSpecial" != result && "//" != result)
      {
        (lexer::tokensList).push_back(result);
      }
    }
  }
  //returning the list of tokens after we applied the lexer:
  return lexer::tokensList;
}

lexer::lexer(string file) {
  lexer::fileName = file;
}

/*
 * this method removes the spaces in the file smartly.
 * meaning - in some condition where we are sure that
 * there will be a space - we wont remove it.
 */
string lexer::removeSpaces(string line) {
  stringstream stringBuilder;
  bool apos = false;
  unsigned int currLoc = 0;
  for(currLoc = 0; currLoc < line.size(); currLoc++)
  {
    //handeling "..." :
    if(line[currLoc] == '\"')
    {
      apos = !apos;
      stringBuilder<<line[currLoc];
    }
    //removving the spaces and tabs:
    else if(line[currLoc] == ' ' || line[currLoc] == '\t')
    {
      //handeling special cases: (var, while. if)
      if((currLoc >= 3 && line[currLoc-3] == 'v' && line[currLoc-2] == 'a' && line[currLoc-1] == 'r') || apos)
      {
        stringBuilder<<line[currLoc];
      }
      if((currLoc >= 5 && line[currLoc-5] == 'w' && line[currLoc-4] == 'h' && line[currLoc-3] == 'i' && line[currLoc-2] == 'l' && line[currLoc-1] == 'e'))
      {
        stringBuilder<<line[currLoc];
      }
      if(currLoc >= 2 && line[currLoc-2] == 'i' && line[currLoc-1] == 'f')
      {
        stringBuilder<<line[currLoc];
      }
    }
    else
    {
      //adding the string to the string builder;
      stringBuilder<<line[currLoc];
    }
  }
  return stringBuilder.str();
}

/*
 * a method to check if we are reading a special character right now:
 */
string lexer::isSpecialCharacter(string line,unsigned int& currLocation) {
  switch(line[currLocation])
  {
    case ' ':
      currLocation++;
      return "special";
    case '=':

      currLocation++;
      switch(line[currLocation])
      {
        case '=':
          currLocation++;
          return "==";
        case '<':
          currLocation++;
          return "=<";
        case '>':
          currLocation++;
          return "=>";
        default:
          return "=";
      }
    case '!':

      currLocation++;
      if(line[currLocation] == '=')
      {
        currLocation++;
        return "!=";
      }
      break;
    case '<':

      currLocation++;
      if(line[currLocation] == '=')
      {
        currLocation++;
        return "<=";
      }
      else if(line[currLocation] == '-')
      {
        currLocation++;
        return "<-";
      }
      else
      {
        return "<";
      }
    case '>':
      currLocation++;
      if(line[currLocation] == '=')
      {
        currLocation++;
        return ">=";
      }
      else
      {
        return ">";
      }
    case '-':
      if(line[currLocation+1] == '>')
      {
        currLocation++;
        currLocation++;
        return "->";
      }
      break;
    case ')':
      currLocation++;
      return "special";
    case '(':
      currLocation++;
      return "special";
    case ',':
      currLocation++;
      return "special";
    case '{':
      currLocation++;
      return "{";
    case '}':
      currLocation++;
      return "}";
    case '/':
      if(line[currLocation+1] == '/')
        {
          currLocation++;
          currLocation++;
          return "//";
        }
    default:
      break;
  }
  return "notSpecial";
}
