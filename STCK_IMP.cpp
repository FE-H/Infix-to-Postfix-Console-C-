//AUTHOR    :   HTHNN07
//Status    :   Finished, Updated (18.03.16)
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

//Common@Required libraries includes
//NIL - Included in the declaration file (.h)

//Uncommon@Files includes
#include "STCK_IMP.h"

STCK_IMP::STCK_IMP()
{
    STCK_IMP_INIT();
}

void STCK_IMP::STCK_IMP_INIT()
{
    validCHAR = "+-*/";

    std::string inputSTCK = "";
    int count = 0;

    std::cout << "Please input the string(s) you wish to convert. (Enter -1 to exit)\n";

    while(true)
    {
        std::cout << "(" << count+1 << ")\t" ;
        std::getline(std::cin, inputSTCK);

        count++;

        if(inputSTCK == "-1")
        {
            std::cout << "\nInput sequence : Terminated.\n";
            break;
        }

        EQN_POST.push(inputSTCK);
        std::cout << "\nConversion completed.\n";
        std::cout << "Enter the next equation or -1 to exit\n";
    }
}

//Stack Implementation - Destructor
STCK_IMP::~STCK_IMP()
{
}

//Stack Implementation - Stack Level
void STCK_IMP::infx_pstfx_STCKLVL()
{
    std::string eqn;

    std::stack <std::string> EQN_COPYzwei = EQN_POST;

    while(!EQN_COPYzwei.empty())
    {
        EQN_COPY.push(EQN_COPYzwei.top());
        EQN_COPYzwei.pop();
    }

    EQN_COPYzwei = EQN_COPY;

    while(!EQN_COPYzwei.empty())
    {
        eqn= EQN_COPYzwei.top();
        infx_pstfx_EQNLVL(eqn);

        EQN_COPYzwei.pop();
        EQN_COPY.push(eqn);
    }
}

//Stack Implementation - Equation Level
void STCK_IMP::infx_pstfx_EQNLVL(std::string eqn)
{
    bool unevenPRNTHSS = infxREAD(eqn);

    if(unevenPRNTHSS)
        std::cout << "\nERROR : UNEVEN PARENTHESES COUNT!\n";

}

//Stack Implementation - Infix Read
bool STCK_IMP::infxREAD(std::string& red)
{
    int prnthssCOUNT_L = 0, prnthssCOUNT_R = 0;
    std::stack <std::string> mathOPR;

    std::string readNOCHAR; //too lazy to convert string to char
    std::string::iterator read;
    char readDEREF;

    for(read = red.begin(); read != red.end(); read++ )
    {
        readDEREF = *read;  //to prevent error -> string literal comparison with string (prohibited in C++11)

        //Detection of parentheses
        if(readDEREF == '(' || readDEREF == ')')
        {
            readNOCHAR = *read;

            if(readDEREF == '(')
            {
                prnthssCOUNT_L+=1;
                mathOPR.push(readNOCHAR);
            }
            else
            {
                prnthssCOUNT_R+=1;
                mathOPR.push(readNOCHAR);
            }

            //Will always pop the first pair of left and right parentheses to complete
            if(prnthssCOUNT_L >= 1 && prnthssCOUNT_R >=1)
            {
                //pops the right parenthesis
                mathOPR.pop();
                std::cout << " ";

                //pops the content in between the parentheses
                while(mathOPR.top() != "(")
                {
                    std::cout << mathOPR.top() << " ";
                    mathOPR.pop();
                }

                //pops the left parenthesis
                mathOPR.pop();
            }
            else if(prnthssCOUNT_L != prnthssCOUNT_R)
            {
                return true;
            }
        }
        else
        {
            //To determine whether the character is an alphanumeric character or operator
            if(std::isalnum(readDEREF))
            {
                std::cout << readDEREF;
            }
            else
            {
                std::size_t foundVALID =validCHAR.find(readDEREF);  //find() returns size_t type var

                if(foundVALID != std::string::npos)                 //find() will return string::npos if no matches found
                {
                    std::cout << " ";

                    //Evaluates the operator
                    if(!oprEVAL(mathOPR, readDEREF))
                    {
                        readNOCHAR = *read;
                        mathOPR.push(readNOCHAR);
                    }
                    else
                    {
                        readNOCHAR = *read;
                        std::cout << mathOPR.top() << " ";

                        mathOPR.pop();
                        mathOPR.push(readNOCHAR);
                    }
                }
                else
                    continue;

            }
        }
    }

    //Pops out all the remainder of the stack to not miss anything
    while(!mathOPR.empty())
    {
        std::cout  << " " << mathOPR.top();
        mathOPR.pop();
    }

    std::cout << "\n";

    return false;
}

//Stack Implementation - Operator Evaluation
bool STCK_IMP::oprEVAL(std::stack <std::string>& mathOPR, char& opr)
{
    //What happens when this method returns true?
    //  Top of the math operator stack will be displayed first, then popped. The current character will be pushed in, hence, the new top.

    //False?
    //  The character will be pushed into the stack.

    if(mathOPR.empty()) //If math operator stack is empty
    {
        return false;
    }
    else
    {
        if((mathOPR.top() == "/" || mathOPR.top() == "*") && (opr == '+' || opr== '-'))
        {
            //std::cout << "\n*+ / *- / /+ / /-\n";
            return true;
        }
        else if((mathOPR.top() == "+" || mathOPR.top() == "-") && (opr == '*' || opr == '/'))
        {
            //std::cout << "\n*+ / *- / /+ / /-\n";
            return false;
        }
    }
}
