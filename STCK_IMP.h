//AUTHOR    :   HTHNN07
//Status    :   Finished, Upgraded (18.03.16)
//              Capabilities
//                  -Use stacks to keep a stack of equations (Objects)
//                      >User can either enter a bulk of equations one by one or choose to enter only one
//                          >Clarification on instruction so the user realises he/she is going to enter the 2nd or the Nth equation or quit. [Update 18.03.2016]
//                  -Use stack to implement the classic infix to postfix conversion
//                      >Basic Infix to Postfix with support up to parentheses differentiation
//                      >Right to left alignment due to using basic stack algorithm that is LIFO
//                      >Only recognises addition (+), deduction (-), division (/), multiplication (*) [Update 18.03.2016]

//              Unimplemented Feature(s)
//                  -Support/Identification of the following scenarios :
//                      >Other types of operator
//                          > factorial sign (!), power sign (^), percentage (%), magnitude(|), size comparison (<, >) [Found 18.03.2016]
//                      >Negative or Positive signs on the initial operand
//                          > Expected behaviour :  Assumes the sign as an operator therefore will return true for this condition [Found 18.03.2016]
//                                                                      **if(!oprEVAL(mathOPR, readDEREF))**
//                                                  causing it to be displayed accordingly to the algorithm that is meant to sort
//                                                  the operators and parentheses.

//Glossary
//  eine        :   Used to denote the first copy or the object of the class/type
//  zwei        :   Used to denote the second copy or the object of the class/type
//  stck        :   Stack
//  imp         :   Implementation
//  eqn         :   Equation
//  lvl         :   level
//  opr         :   operator
//  eval        :   evaluate/evaluation
//  init        :   initialise
//  parenthesis :   '(' or ')'

//Common@Required libraries include
#include <iostream>     //basic IO
#include <string>
#include <stack>
#include <cctype>       //isalphanum() - to differentiate between operator and operand

//Uncommon@Files includes
//NIL

//Stack Implementation Class
class STCK_IMP
{
private:
    void STCK_IMP_INIT();
    void infx_pstfx_EQNLVL(std::string);
    bool infxREAD(std::string&);
    bool oprEVAL(std::stack <std::string>&, char&);

    std::stack <std::string> EQN_POST;
    std::stack <std::string> EQN_COPY;

    std::string validCHAR;

public:
    STCK_IMP();
    ~STCK_IMP();

    void infx_pstfx_STCKLVL();
};

