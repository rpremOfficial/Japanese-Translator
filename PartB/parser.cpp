#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include "scanner.cpp"
using namespace std;

//=================================================                                                                                                      
// File parser.cpp written by Group Number: 16                                                                                                           
//=================================================                                                                                                      

// ----- Four Utility Functions and Globals -----------------------------------                                                                          

string saved_lexeme;
tokentype saved_token;
bool token_available = false;
string user_choice;
ofstream errorfile;

enum parser_function {STORY, S, AFTER_SUBJECT, AFTER_NOUN, AFTER_OBJECT, VERB1, TENSE, NOUN, BE};
string parserName[30] = {"story", "s", "afterSubject", "afterNoun", "afterObject", "verb1", "tense", "noun", "be"};

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)                                                                                   
//    to display syntax error messages as specified by me.                                                                                               

// Type of error: Match fails.                                                                                                                           
// Done by: Jeffery Lu                                                                                                                                   
void syntaxerror1(tokentype expected)
{
  cout << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;
}

// Type of error: Switch default                                                                                                                         
// Done by: Jeffer Lu                                                                                                                                    
void syntaxerror2(parser_function function)
{
  cout << "\nSYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parserName[function] << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars                                                                                           
// saved_token and saved_lexeme                                                                                                                          

// Purpose: Checks what token comes next from scanner.                                                                                                   
// Done by: Daniel Martinez                                                                                                                              
tokentype next_token()
{
   if(!token_available)
    {
      scanner(saved_token, saved_lexeme);
      token_available = true;
    }

  return
    saved_token;
}

// Purpose: Checks if expected token is different from next_token()                                                                                      
// Done by: Robert Paud                                                                                                                                  
bool match(tokentype expected)
{
  if(next_token() != expected)
    {
      syntaxerror1(expected);
      if(errorfile.is_open())
        {
          errorfile << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;
        }

      cout << "Skip or replace the token? (s or r)";
      cin >> user_choice;
     if(user_choice == "s")
        {
          token_available = false;
          match(expected);
        }

      else if(user_choice == "r")
        {
          token_available = false;
          cout << "Matched " << tokenName[expected] << endl;
        }
    }

  else
    {
      token_available = false;
      cout << "Matched " << tokenName[expected] << endl;
      return true;
    }
}

// ----- RDP functions - one per non-term -------------------                                                                                            

// ** Make each non-terminal into a function here                                                                                                        
// ** Be sure to put the corresponding grammar rule above each function                                                                                  
// ** Be sure to put the name of the programmer above each function
// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG                                                                                          
// Done by: Sam Cooke                                                                                                                                    
void tense()
{
  cout << "Processing <tense>\n";

  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;

    case VERB:
      match(VERB);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;
        
    default:
      syntaxerror2(TENSE);
    }
}

// Grammar: <be> ::= IS | WAS                                                                                                                            
// Done by: Sam Cooke                                                                                                                                    
void be()
{
  cout << "Processing <be>\n";

  switch(next_token())
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;

    default:
      syntaxerror2(BE);
    }
}

// Grammar: <verb> ::= WORD2                                                                                                                             
// Done by: Sam Cooke                                                                                                                                    
void verb()
{
  cout << "Processing <verb>\n";
  match(WORD2);
}

// Grammar: <noun> ::= WORD1 | PRONOUN                                                                                                                   
// Done by: Sam Cooke                                                                                                                                    
void noun()
{
  cout << "Processing <noun>\n";

  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;

    case PRONOUN:
      match(PRONOUN);
      break;

    default:
      syntaxerror2(NOUN);
    }
}

// Grammar: <afterObject> ::= <noun> DESTINATION <verb> <tense> PERIOD | <verb> <tense> PERIOD                                                           
// Done by: Sam Cooke                                                                                                                                    
void afterObject()
{
  cout << "Processing <afterObject>\n";

  switch(next_token())
    {
    case WORD1:
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    default:
      syntaxerror2(AFTER_OBJECT);
    }
}

// Grammar: <afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterObject>                                                       
// Done by: Sam Cooke                                                                                                                                    
void afterNoun()
{
  cout << "Processing <afterNoun>\n";

  switch(next_token())
    {
    case IS:
    case WAS:
      be();
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      afterObject();
      break;

    default:
      syntaxerror2(AFTER_NOUN);
    }
}

// Grammar: <afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>                                                                                
// Done by: Robert Paud                                                                                                                                  
void afterSubject()
{
  cout << "Processing <afterSubject>\n";

  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      afterNoun();
      break;

    default:
      syntaxerror2(AFTER_SUBJECT);
    }
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <afterSubject>                                                                                            
// Done by: Daniel Martinez                                                                                                                              
void s()
{
  cout << "Processing <s>\n";

  switch(next_token())
    {
    case CONNECTOR:
      match(CONNECTOR);
      noun();
      match(SUBJECT);
      afterSubject();
      break;

    default:
      noun();
      match(SUBJECT);
      afterSubject();
      break;
    }
}

// Grammar: <story> ::= <s> { <s> }                                                                                                                      
// Done by: Jeffrey Lu                                                                                                                                   
void story()
{
  cout << "\nProcessing <story>\n\n";

  s();
  while(true)
    {
      if(next_token() == EOFM)
        {
          cout << "\nSuccessfully parsed <story>.\n";
          break;
        }

      s();
    }
}

//----------- Driver ---------------------------                                                                                                         

string filename;

// The new test driver to start the parser                                                                                                               
// Done by:  Jeffrey Lu/Daniel Martinez 
int main()
{
  cout << "\nGROUP 16\n";
  cout << "---------\n";
  cout << "Jeffery Lu\n";
  cout << "Sam Cooke\n";
  cout << "Daniel B. Martinez\n";
  cout << "Robert Paud\n\n";

  cout << "Enter the input file name ex: partBtest1.txt\n";
  cout << "Enter file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  cout << "Do you want to trace error messages? (y or n)";
  cin >> user_choice;

  if(user_choice == "y")
    {
      errorfile.open("errors.txt");
    }

  //** calls the <story> to start parsing                                                                                                                
  story();
  errorfile.close(); //** closes the error file                                                                                                          
  fin.close(); //** closes the input file                                                                                                                
}
// end                                                                                                                                                   
//** require no other input files!                                                                                                                       
//** syntax error EC requires producing errors.txt of error messages                                                                                     
//** tracing On/Off EC requires sending a flag to trace message output functions
