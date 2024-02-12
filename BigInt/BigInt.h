#ifndef BIG_INT_H
#define BIG_INT_H

#include <stddef.h>

typedef struct Node{
char digit;
struct Node *next;

}*BigInt;
/*
first BigInt Node is dedicated to signify the sign of BigInt:
1 -> possitive number or zero
0 -> uninitialized
-1 -> negative number

all other nodes signify digits

digits are stored in reverse order
for example:
(in here '->' shows that the digit is in the next node)
159
would be stored as:
1->9->5->1

-5698
would be stored as:
-1->8->9->6->5
*/

/*
All functions return NULL or 0 on error
unless stated otherwise
*/
BigInt bigIntCreate(void);                          //return a BigInt node. Will have to use bigIntSet() functions
BigInt bigIntCreateFromInteger(int a);              //return a BigInt set to integer provided by parameter
BigInt bigIntCreateFromString(const char *text);    //return a BigInt set to string provided by parameter
BigInt bigIntCopy(BigInt num);                      //return a copy of num


size_t bigIntCount(BigInt num);                     //return BigInt digit count
char bigIntIsEmpty(BigInt num);                     //return 1 if BigInt has zero digits else return 0


int bigIntSet(BigInt num, BigInt num1);             //set num to the value of num1
int bigIntSetInt(BigInt num, int num1);             //set num to the value of num1
int bigIntSetString(BigInt num, const char *text);  //set num to the value of text
int bigIntAdd(BigInt num, BigInt num1);             //add bigInts together and save the result in num
int bigIntSub(BigInt num, BigInt num1);             //subtract num1 from num and save the result in num
int bigIntMul(BigInt num, BigInt num1);             //multiply num with num1 and save result in num
int bigIntDiv(BigInt num, BigInt num1);             //divide num by num1 and save result in num
int bigIntMod(BigInt num, BigInt num1);             
int bigIntCmp(BigInt num, BigInt num1);             /*return 1 if num > num1; return 0 if num == num1;
                                                    return -1 if num < num1; return -2 if error    */


char* bigIntToString(BigInt num);       //return num in string form


void bigIntPrint(BigInt num);           //print content to stdout
void bigIntDone(BigInt num);            //free the memory allocated to BigInt
void bigIntMakeEmpty(BigInt num);       //remove all digits from BigInt
void bigIntAbs(BigInt num);             //absolute value
void bigIntChangeSign(BigInt num);      //change the sign of BigInt

#endif
