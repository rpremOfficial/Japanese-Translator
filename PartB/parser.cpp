#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();
void gen();
void getEword();

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 16
//=================================================
string tokens[15] = { "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR" };

tokentype  saved_token;     // global buffer for the scanner token

bool exitFlag = false, parserTraceFlag = true;
string saved_lexeme;// global buffer for the saved lexeme
string saved_E_word;           //global input file
ofstream fileOutput;		//global ouput file for translation


// global flag indicating whether
// we have saved a token to eat up or not
bool   token_available;
// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: **
// Done by: Jeffrey Lu
void syntaxerror1(tokentype token, string str ) {  
   cout << "\nSYNTAX ERROR: expected " << token << " but found " << str << endl;
   }

// Type of error: **
// Done by: ** 
void syntaxerror2(  ) {    }

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks to see what token comes next from the scanner.
// Done by: Sam
token_type next_token(){
    string lexeme;

    if (!token_available)   // if there is no saved token from previous lookahead
    {
        if (exitFlag)
            exit(0);
        scan(saved_token, lexeme, fin);
        cout << "Scanner called using word: " << lexeme << endl;
        if (saved_token == ERROR) {
            cout << "Lexical Error: " << lexeme << " is not a valid token" << endl;
        }
        token_available = true;                  // mark that fact that you have saved it
        saved_lexeme = lexeme;

    }
    return saved_token;    // return the saved token
}

// Purpose: Checks to see if expected token is the same as next token.
// Done by: Sam
boolean match(tokentype expected) {
    if (exitFlag)
        return false;
    if (next_token() != expected)  // mismatch has occurred with the next token
    { // generate a syntax error message here
        // do error handling here if any
        syntaxerror1(expected, saved_lexeme);
        return false;
    }
    else  // match has occurred
    {
        if (parserTraceFlag)
            cout << "Match found for " << tokens[expected] << endl;
        token_available = false;  // eat up the token
        return true;              // say there was a match
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: 1 <story> ::= <s> { <s> }
// Done by: Sam
void story()
{
    if (exitFlag)
        return;
    cout << "Processing <story>" << endl;
    s();
    while (true)
    {
        if (exitFlag)
            return;
        switch (next_token()) // look ahead to see if the valid start is there
        {
            case CONNECTOR: s();// found another beginning
                // so do it
                break;
            case WORD1:s();// found another beginning
                // so do it
                break;
            case PRONOUN:s();// found another beginning
                // so do it
                break;
            default:
                return;  // loop stops
        }//end switch
    }//end loop
}


// 2 <s>  ::=  [CONNECTOR #getEword# #gen#] <noun> #getEword# SUBJECT #gen# <afterSubject>
// Done by: Sam
void s()
{
    if (exitFlag)
        return;
    cout << "Processing <afterSubject>" << endl;
    if (next_token() == CONNECTOR) {   // start of what is in [ ] is found
        match(saved_token);// do it
        getEword();
        gen();
    }

    noun();
    getEword();
    match(SUBJECT);
    gen();
    afterSubject();
}

// 3 <afterSubject> ::=  <verb> #getEword# #gen# <tense> #gen# PERIOD | <noun> #getEword# <afterNoun>
// Done by: Sam
void afterSubject()
{
    if (exitFlag)
        return;
    cout << "Processing <afterSubject>" << endl;
    switch (next_token())
    {
        case WORD2:
            verb();
            getEword();
            gen();
            tense();
            gen();
            match(PERIOD);
            break;

        case WORD1:
        case PRONOUN:
            noun();
            getEword();
            afterNoun();
            break;

        default:
            syntaxerror2(saved_lexeme, "afterSubject");
    }

}

// 4 <afterNoun> ::=  <be> #gen# PERIOD | DESTINATION #gen# <verb> #getEword# #gen# <tense> #gen# PERIOD | OBJECT #gen# <afterObject>
// Done by: Sam
void afterNoun()
{
    if (exitFlag)
        return;
    cout << "Processing <afterNoun>" << endl;
    switch (next_token())
    {
        case IS:
        case WAS:
            be();
            gen();
            match(PERIOD);
            break;

        case DESTINATION:
            match(DESTINATION);
            gen();
            verb();
            getEword();
            gen();
            tense();
            gen();
            match(PERIOD);
            break;

        case OBJECT:
            match(OBJECT);
            gen();
            afterObject();
            break;

        default:
            syntaxerror2(saved_lexeme, "afterNoun");
    }
}

// 5 <afterObject> ::=  <verb> #getEword# #gen# <tense> #gen# PERIOD | <noun> #getEword# DESTINATION #gen# <verb> #getEword# #gen# <tense> #gen# PERIOD
// Done by: Sam
void afterObject()
{
    if (exitFlag)
        return;
    cout << "Processing <afterObject>" << endl;
    switch (next_token())
    {
        case WORD2:
            verb();
            getEword();
            gen();
            tense();
            gen();
            match(PERIOD);
            break;

        case WORD1:
        case PRONOUN:
            noun();
            getEword();
            match(DESTINATION);
            gen();
            verb();
            getEword();
            gen();
            tense();
            gen();
            match(PERIOD);
            break;

        default:
            syntaxerror2(saved_lexeme, "afterObject");
    }
}

// 6 <noun> :: = WORD1 | PRONOUN
// Done by: Sam
void noun()
{
    if (exitFlag)
        return;
    cout << "Processing <noun>" << endl;
    switch (next_token())
    {
        case WORD1:
            match(WORD1);
            break;

        case PRONOUN:
            match(PRONOUN);
            break;

        default:
            syntaxerror2(saved_lexeme, "noun");
    }
}

// 7 <verb> ::= WORD2
// Done by: Sam
void verb()
{
    if (exitFlag)
        return;
    cout << "Processing <verb>" << endl;
    match(WORD2);
}

// 8 <be> :: = IS | WAS
// Done by: Sam
void be()
{
    if (exitFlag)
        return;
    cout << "Processing <be>" << endl;
    switch (next_token())
    {
        case IS:
            match(IS);
            break;

        case WAS:
            match(WAS);
            break;

        default:
            syntaxerror2(saved_lexeme, "be");
    }
}

// 9 <tense> : = VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Sam
void tense()
{
    if (exitFlag)
        return;
    cout << "Processing <tense>" << endl;
    switch (next_token())
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
            syntaxerror2(saved_lexeme, "tense");
    }
}

//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result
//Done by: Sam
void getEword() {
    if (exitFlag)
        return;

    if (saved_lexeme == "watashi")
        saved_E_word = "I/me";
    else if (saved_lexeme == "anata")
        saved_E_word = "you";
    else if (saved_lexeme == "kare")
        saved_E_word = "he/him";
    else if (saved_lexeme == "kanojo")
        saved_E_word = "she/her";
    else if (saved_lexeme == "sore")
        saved_E_word = "it";
    else if (saved_lexeme == "mata")
        saved_E_word = "also";
    else if (saved_lexeme == "soshite")
        saved_E_word = "then";
    else if (saved_lexeme == "shikashi")
        saved_E_word = "however";
    else if (saved_lexeme == "dakara")
        saved_E_word = "therefore";
    else
        saved_E_word = saved_lexeme;
}

//    gen()			- uses the saved_token to know what line to produce,
//                     display a line of an IR (saved_E_word or saved_token
//                     is used)
//Done by: Sam
void gen() {
    if (exitFlag)
        return;

    switch (saved_token) {

        case CONNECTOR:
            fileOutput << "CONNECTOR:   " << saved_E_word << endl;
            break;
        case SUBJECT:
            fileOutput << "ACTOR:       " << saved_E_word << endl;
            break;
        case IS:
        case WAS:
            fileOutput << "DESCRIPTION: " << saved_E_word << endl;
            fileOutput << "TENSE:       " << tokens[saved_token] << endl;
            break;
        case OBJECT:
            fileOutput << "OBJECT:      " << saved_E_word << endl;
            break;
        case DESTINATION:
            fileOutput << "TO:          " << saved_E_word << endl;
            break;
        case WORD2:
            fileOutput << "ACTION:      " << saved_E_word << endl;
            break;
        case VERBPAST:
        case VERBPASTNEG:
        case VERB:
        case VERBNEG:
            fileOutput << "TENSE:       " << tokens[saved_token] << endl;
            break;

        default:
            return;
    }

}
string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Jeffery Lu
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 
  story();
  fin.close();
   
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
