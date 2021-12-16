#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iterator> 
#include<map>
#include<sstream>
#include "scanner.cpp"
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 16
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

string saved_lexeme;
string saved_E_word;
tokentype saved_token;
bool token_available = false;
string user_choice;
ofstream errorfile;
ofstream translatedfile;

enum parser_function {STORY, S, AFTER_SUBJECT, AFTER_NOUN, AFTER_OBJECT, VERB1, TENSE, NOUN, BE};
string parserName[30] = {"story", "s", "after_subject", "after_noun", "after_object", "verb1", "tense", "noun", "be"};

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: Match fails.
// Done by: William Cerros 
void syntaxerror1(tokentype expected){
    cout << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;
}
// Type of error: Switch default
// Done by: William Cerros 
void syntaxerror2(parser_function function) {
    cout << "\nSYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parserName[function] << endl;
    exit(1);
}

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: William Cerros

//Map will serve as our look up table
map<string, string> lexicon_dictionary;

void build_dictionary() {
    // input streamt to read from text file
    std::ifstream input_stream("lexicon.txt", std::ifstream::in);
    string word;
    
    int i;
    int j = 0;
    // for loop will iterate through each line in lexicon.txt
    for (string line; getline(input_stream, line); )
    {
         
        // istringstream object will help us parse the input
        istringstream ss(line);

        // This will be our dictionary pair
        string key;
        string value;

        // Counter to let us know if we are reading the fist or second word
        i = 0;

        // while a word exists in the line we are currently reading from text file
        while (ss >> word)
        {
            if (i == 0) {
                key = word;
            }

            if (i == 1) {
                value = word;

                // Once we have read in the value we can insert to our map
                lexicon_dictionary.insert(pair<string, string>(key, value));
            }

            i++;
        }
    }

    // printing out map to verify
    // for (map<string, string>::const_iterator it = lexicon_dictionary.begin();
    //     it != lexicon_dictionary.end(); ++it)
    // {
    //         std::cout << "Key: "<< it->first << " Value: " << it->second << " ""\n";
    // }
    input_stream.close(); 

}

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Peter Sharp 
void getEword() {

    for (map<string, string>::const_iterator it = lexicon_dictionary.begin();it != lexicon_dictionary.end(); ++it)
    {
        if (saved_lexeme == it->first) {
            saved_E_word = it->second;
            return;
        }
    }
    saved_E_word = saved_lexeme;
    return;
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Howard Tep
void gen(string token) {

    if (token == "TENSE") {
        translatedfile << "TENSE:" << tokenName[saved_token] << endl;
    } else {
        translatedfile << token << ": " << saved_E_word << endl;
    }
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Checks what token comes next from scanner.
// Done by: Howard Tep
tokentype next_token() {

    if (!token_available) {
        scanner(saved_token, saved_lexeme);
        token_available = true;
    }
    return saved_token;
}

// Purpose: Checks if expected token is different from next_token()
// Done by: Howard Tep
bool match(tokentype expected) {

    if (next_token() != expected) {
        syntaxerror1(expected);
        if (errorfile.is_open()) {
            errorfile << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;
        }
        cout << "Skip or replace the token? (s or r)";
        cin >> user_choice;
        if (user_choice == "s") {
            token_available = false;
            match(expected);
        } else if (user_choice == "r") {
            token_available = false;
            cout << "Matched " << tokenName[expected] << endl;
        }
    } else {
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
// Done by: Peter Sharp
void tense() {

    cout << "Processing <tense>\n";

    switch (next_token()) {
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
// Done by: Peter Sharp
void be() {

    cout << "Processing <be>\n";

    switch (next_token()) {
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
// Done by: Howard Tep
void verb() {

    cout << "Processing <verb>\n";
    match(WORD2);
}

// Grammar: <noun> ::= WORD1 | PRONOUN 
// Done by: Howard Tep
void noun() {

    cout << "Processing <noun>\n";

    switch (next_token()) {
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

// Grammar: <afterObject> ::= <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword#
//                            #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <verb> 
//                            #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD 
// Done by: William Cerros
void after_object() {

    cout << "Processing <afterObject>\n";

    switch (next_token()) {
        case WORD1: case PRONOUN:
            noun();
            getEword();
            match(DESTINATION);
            gen("TO");
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
            break;
        case WORD2:
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
            break;
        default:
            syntaxerror2(AFTER_OBJECT);
    }
}

// Grammar: <afterNoun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE") PERIOD | DESTINATION #gen("TO") 
//                          <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | OBJECT
//                          #gen("OBJECT")# <afterObject>
// Done by: William Cerros
void after_noun() {

    cout << "Processing <afterNoun>\n";

    switch (next_token()) {
        case IS: case WAS:
            be();
            gen("DESCRIPTION");
            gen("TENSE");
            match(PERIOD);
            break;
        case DESTINATION:
            match(DESTINATION);
            gen("TO");
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
            break;
        case OBJECT:
            match(OBJECT);
            gen("OBJECT");
            after_object();
            break;
        default:
            syntaxerror2(AFTER_NOUN);
    }
}

// Grammar: <afterSubject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# 
//                             PERIOD | <noun> #getEword# <afterNoun> 
// Done by: Howard Tep
void after_subject() {

    cout << "Processing <afterSubject>\n";

    switch (next_token()) {
        case WORD2:
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
            break;
        case WORD1: case PRONOUN:
            noun();
            getEword();
            after_noun();
            break;
        default:
            syntaxerror2(AFTER_SUBJECT);
    }

}

// Grammar: <s> ::= [CONNECTOR] #getEword# #gen("CONNECTOR")# <noun> #getEword# 
//                   SUBJECT #gen("ACTOR")# <afterSubject>
// Done by: Peter Sharp
void s() {

    cout << "Processing <s>\n";

    switch (next_token()) {
        case CONNECTOR:
            match(CONNECTOR);
            getEword();
            gen("CONNECTOR");
            noun();
            getEword();
            match(SUBJECT);
            gen("ACTOR");
            after_subject();
            break;
        default:
            noun();
            getEword();
            match(SUBJECT);
            gen("ACTOR");
            after_subject();
            break;
    }
}

// Grammar: <story> ::= <s> { <s> }
// Done by: William Cerros
void story() {

    cout << "Processing <story>\n";

    s();
    while (true) {
        if (next_token() == EOFM) {
            cout << "\nSuccessfully parsed <story>.\n";
            break;
        }
        s();
    }
}

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  **
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  build_dictionary();

  //** opens the output file translated.txt
  translatedfile.open("translated.txt");
  
  //** opens the output file translated.txt
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing

  //** closes the input file 
  //** closes traslated.txt
  cout << "Do you want to trace error messages? (y or n)";
  cin >> user_choice;
    
  if(user_choice == "y")
  {
    errorfile.open("errors.txt");
  } 

  //** calls the <story> to start parsing
  story();

  //** closes the input file 
  //** closes traslated.txt
  errorfile.close();
  fin.close();
  translatedfile.close();
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
