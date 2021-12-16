#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================                                                                                                  
// File scanner.cpp written by: Group Number: 16                                                                                                         
//=====================================================                                                                                                  

// --------- Two DFAs ---------------------------------                                                                                                  

// WORD DFA                                                                                                                                              
// Done by: Robert Paud, Sam Cooke                                                                                                                       
/* RE:(vowel | vowel n | consonant vowel | consonant vowel n |                                                                                           
consonant-pair vowel | consonant-pair vowel n)^+ */
bool word(string s)
{
  int state = 0;
  int charpos = 0;
  /* replace the following todo the word dfa  */
  while(s[charpos] != '\0')
    {
      if(state == 0)
        {
          char ch = s[charpos];

          //vowels, qoq1                                                                                                                                 
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch == 'd' || ch == 'w' || ch == 'z' || ch == 'y' || ch == 'j')
            {
              state = 2;
            }

          //qy                                                                                                                                           
          else if(ch == 'b' || ch == 'm' || ch == 'k' || ch == 'n' || ch == 'h' || ch == 'p' || ch == 'r' || ch == 'g')
            {
              state = 3;
            }

          //qt                                                                                                                                           
          else if(ch == 't')
            {
              state = 4;
            }
          
          //qs                                                                                                                                           
          else if(ch == 's')
            {
              state = 5;
            }

          //qc                                                                                                                                           
          else if(ch == 'c')
            {
              state = 6;
            }

          else
            return false;
        }
      
      //qoq1                                                                                                                                             
      else if(state == 1)
        {
          char ch = s[charpos];

          //q0q1                                                                                                                                         
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch == 'd' || ch == 'w' || ch == 'z' || ch == 'y' || ch == 'j')
            {
              state = 2;
            }

          //qy                                                                                                                                           
          else if(ch == 'b' || ch == 'g' || ch == 'h' || ch == 'k' || ch == 'm' || ch == 'p' || ch == 'r')
            {
              state = 3;
            }

          else if(ch == 't')
            {
              state = 4;
            }

          else if(ch == 's')
            {
              state = 5;
            }
          
          //qc                                                                                                                                           
          else if(ch == 'c')
            {
              state = 6;
            }

          //q0qy                                                                                                                                         
          else if(ch == 'n')
            {
              state = 7;
            }

          else
            return false;
        }
      
      //qsa                                                                                                                                              
      else if(state == 2)
        {
          char ch = s[charpos];

          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          else
            return false;
        }
      
      //qy                                                                                                                                               
      else if(state == 3)
        {
          char ch = s[charpos];

          //q0q1                                                                                                                                         
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch = 'y')
            {
              state = 2;
            }

          else
            return false;
        }
      
      //qt                                                                                                                                               
      else if(state == 4)
        {
          char ch = s[charpos];

          //q0q1                                                                                                                                         
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch == 's')
            {
              state = 2;
            }

          else
            return false;
        }
      
      //qs                                                                                                                                               
      else if(state == 5)
        {
          char ch = s[charpos];

          //q0q1                                                                                                                                         
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch == 'h')
            {
              state == 2;
            }

          else
            return false;
        }
      
      //qc                                                                                                                                               
      else if(state == 6)
        {
          char ch = s[charpos];

          if(ch == 'h')
            {
              state == 2;
            }
        }
      
      //q0qy                                                                                                                                             
      else if(state == 7)
        {
          char ch = s[charpos];

          //q0q1                                                                                                                                         
          if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'I' || ch == 'E')
            {
              state = 1;
            }

          //qsa                                                                                                                                          
          else if(ch == 'd' || ch == 'w' || ch == 'z' || ch == 'y' || ch == 'j')
            {
              state = 2;
            }

          //qy                                                                                                                                           
          else if(ch == 'b' || ch == 'g' || ch == 'h' || ch == 'k' || ch == 'm' || ch == 'p' || ch == 'r')
            {
              state = 3;
            }

          else if(ch == 't')
            {
              state = 4;
            }

          else if(ch == 's')
            {
              state = 5;
            }

          else if(ch == 'c')
            {
              state = 6;
            }

          else
            return false;
        }

      charpos++;
    }//end of while 
    
    // where did I end up????                                                                                                                              
  if(state == 0 || state == 1 || state == 7)
    return(true);  // end in a final state                                                                                                               

  else
    return(false);
}

// PERIOD DFA                                                                                                                                            
// Done by: Jeffrey Lu                                                                                                                                   
bool period(string s)
{
    if(s[0] == '.')
      {
        return true;
      }

    else
      {
        return false;
      }
}

// ------ Three  Tables -------------------------------------                                                                                            
// TABLES Done by: Jeffrey Lu, Sam Cooke                                                                                                                 
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.                                                                                 
enum tokentype {WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG,
                 IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM, ERROR };

// ** For the display names of tokens - must be in the same order as the tokentype.                                                                      
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST",
                        "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION",
                        "PRONOUN", "CONNECTOR", "EOFM", "ERROR" };

// ** Need the reservedwords table to be set up here.                                                                                                    
// ** Do not require any file input for this. Hard code the table.                                                                                       
// ** a.out should work without any additional files.                                                                                                    
string reservedwords[20][2] = {{"masu", "VERB"}, {"masen", "VERBNEG"}, {"mashita", "VERBPAST"},
{"masendeshita", "VERBPASTNEG"}, {"desu", "IS"}, {"deshita", "WAS"}, {"o", "OBJECT"}, {"wa", "SUBJECT"},
{"ni", "DESTINATION"}, {"watashi", "PRONOUN"}, {"anata", "PRONOUN"}, {"kare", "PRONOUN"},
{"kanojo", "PRONOUN"}, {"sore", "PRONOUN"}, {"mata", "CONNECTOR"}, {"soshite", "CONNECTOR"},
{"shikashi", "CONNECTOR"}, {"dakara", "CONNECTOR"}, {"eofm", "EOFM"} };

// ------------ Scanner and Driver -----------------------                                                                                               

ifstream fin;  // global stream for reading from the input file                                                                                          

// Scanner processes only one word each time it is called                                                                                                
// Gives back the token type and the word itself                                                                                                         
// ** Done by: Daniel B. Martinez
int scanner(tokentype& tt, string& w)
{
  // variables                                                                                                                                           
  bool reserve = false;

  // ** Grab the next word from the file via fin                                                                                                         
  fin >> w;
  cout << "\nScanner called using word: " << w << endl;

  // 1. If it is eofm, return right now.                                                                                                                 
  if(w == "eofm")
    {
      return EOFM;
    }

  // call the period function, check to see if period after the word                                                                                     
  if(period(w))
    {
      tt = PERIOD;
    }
    
  // call the token funcion word to test cases                                                                                                           
  else if(word(w))
    {
      /*                                                                                                                                                 
        loop through the words that was hardcoded in the above                                                                                           
        string reservewords table that was written. Loop through                                                                                         
        all nineteen words.                                                                                                                              
      */
      for(int i = 0; i < 20; i++)
        {
          if(w == reservedwords[i][0])
            {
              // w was found to be reserved, assign the correct token type                                                                               
              if(reservedwords[i][1] == "VERB")
                {
                  tt = VERB;
                }

              else if(reservedwords[i][1] == "VERBNEG")
                {
                  tt = VERBNEG;
                }

              else if(reservedwords[i][1] == "VERBPAST")
                {
                  tt = VERBPAST;
                }

              else if(reservedwords[i][1] == "VERBPASTNEG")
                {
                  tt = VERBPASTNEG;
                }

              else if(reservedwords[i][1] == "IS")
                {
                  tt = IS;
                }

              else if(reservedwords[i][1] == "WAS")
                {
                  tt = WAS;
                }

              else if(reservedwords[i][1] == "OBJECT")
                {
                  tt = OBJECT;
                }

              else if(reservedwords[i][1] == "SUBJECT")
                {
                  tt = SUBJECT;
                }

              else if(reservedwords[i][1] == "DESTINATION")
                {
                  tt = DESTINATION;
                }
              else if(reservedwords[i][1] == "PRONOUN")
                {
                  tt = PRONOUN;
                }

              else if(reservedwords[i][1] == "CONNECTOR")
                {
                  tt = CONNECTOR;
                }

              else if(reservedwords[i][1] == "EOFM")
                {
                  tt = EOFM;
                }

              reserve = true;
              break;

            }//endif                                                                                                                                     
        }//endloop
      
      // check the words, if not found in reservedwords table.                                                                                           
      // words must be WORD1 or WORD2                                                                                                                    
      if(!reserve)
        {
          // test cases                                                                                                                                  
          if(w[w.size() - 1] == 'I' || w[w.size() - 1] == 'E')
            {
              // E ending will be WORD2                                                                                                                  
              tt = WORD2;
            }

          else
            {
              // I ending will be WORD1                                                                                                                  
              tt = WORD1;
            }
        }
    }

  // no token type has been found so throw a lexical error,                                                                                              
  // both DFA's fail. tokentype is to be an ERROR.                                                                                                       
  else
    {
      cout << "\nLexical error: " << w << " is not a valid token\n";
      tt = ERROR;
    }
    
    /*  **                                                                                                                                                 
  2. Call the token functions (word and period)                                                                                                          
     one after another (if-then-else).                                                                                                                   
     Generate a lexical error message if both DFAs failed.                                                                                               
     Let the tokentype be ERROR in that case.                                                                                                            
  3. If it was a word, check against the reservedwords list.                                                                                             
     If not reserved, tokentype is WORD1 or WORD2                                                                                                        
     decided based on the last character.                                                                                                                
  4. Return the token type & string  (pass by reference)*/
    
   return 0;
}//the end of scanner                                                                                                                                    

/*                                                                                                                                                       
// The temporary test driver to just call the scanner repeatedly                                                                                         
// This will go away after this assignment                                                                                                               
// DO NOT CHANGE THIS!!!!!!                                                                                                                              
// Done by: Louis Krell                                                                                                                                  
 int main()                                                                                                                                              
 {                                                                                                                                                       
   tokentype thetype;                                                                                                                                    
   string theword;                                                                                                                                       
   string filename;                                                                                                                                      
                                                                                                                                                         
   cout << "Enter the input file name: ";                                                                                                                
   cin >> filename;                                                                                                                                      
                                                                                                                                                         
   fin.open(filename.c_str());                                                                                                                           
                                                                                                                                                         
   // the loop continues until eofm is returned.                                                                                                         
   while (true)                                                                                                                                          
     {                                                                                                                                                   
       scanner(thetype, theword);  // call the scanner which sets                                                                                        
                                                                                                                                                         
       // the arguments                                                                                                                                  
       if (theword == "eofm") break;  // stop now                                                                                                        
                                                                                                                                                         
       cout << "Type is:" << tokenName[thetype] << endl;                                                                                                 
       cout << "Word is:" << theword << endl;                                                                                                            
     }                                                                                                                                                   
                                                                                                                                                         
   cout << "End of file is encountered." << endl;                                                                                                        
   fin.close();                                                                                                                                          
                                                                                                                                                         
 }// end                                                                                                                                                 
*/
