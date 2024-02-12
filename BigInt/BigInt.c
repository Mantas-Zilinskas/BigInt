/*
By mantas Zilinskas
*/
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BigInt.h"

BigInt bigIntCreate(void){
    BigInt num = NULL;
    num = (struct Node*)malloc(sizeof(struct Node));
    if(num == NULL)
        return NULL;

    num->digit = 0;
    num->next = NULL;
    return num;
}

BigInt bigIntCreateFromInteger(int a){
    BigInt num = NULL;
    BigInt num1 = NULL;
    int temp = a;
    int digits = 1;

    while(temp /= 10)               //get digit count
        ++digits;

    num = bigIntCreate();           //check sign
    if(num == NULL)
        return NULL;
    if(a >= 0){
        num->digit = 1;
    } else{
        num->digit = -1;
        a = abs(a);
    }

    num1 = bigIntCreate();          
    if(num1 == NULL){
        bigIntDone(num);
        return NULL;
    }
    num->next = num1;

    num1->digit = a%10;            //load digits inside BigInt
    for(int i = 10, j = 1; j < digits; i *= 10, ++j){
        num1->next = bigIntCreate();
            if(num1->next == NULL){
                bigIntDone(num);
                return NULL;
            }
        num1 = num1->next;
        num1->digit = (a/i)%10;
    }
    return num;
}

BigInt bigIntCreateFromString(const char *text){
    char sign = 0;
    size_t length = 0;
    size_t remove = 0;  //how many symbols to remove from start of string

    if(text[0] == '-'){            //check sign
        sign = 1;
        remove = 1;
    }

    length = strlen(text);         //check length
    if (length - sign == 0)
            return NULL;

    for(size_t i = sign; i < length - 1; ++i){      //count the amount of symbols to remove
        if(text[i] == '0' && text[i] <= text[i+1]){
            ++remove;
        }else
            break;
    }

    for(int i = sign; i < length; ++i){   //check if string is valid 
        if(text[i] > '9' || text[i] < '0'){
            return NULL;
        }
    }

    BigInt num = bigIntCreate();  // load string inside of BigInt
    BigInt num1 = num;
    if(!num)
        return NULL;
    if(sign){
        num->digit = -1;
    }else
        num->digit = 1;

    for(size_t i = length; i > remove; --i){
        num1->next = bigIntCreate();
        if(!num1->next){
            bigIntDone(num);
            return NULL;
        }
        num1 = num1->next;
        num1->digit = text[i-1] - '0';
    }
    return num;
}

BigInt bigIntCopy(BigInt num){
    if(!num)
        return NULL;
    char *text = bigIntToString(num);
    BigInt num1 = bigIntCreateFromString(text);
    free(text);
    if(!num1){
        free(text);
        return NULL;
    }
    return num1;
}

size_t bigIntCount(BigInt num){
    size_t count = 0;

    if(!num)
        return 0;
    while(num->next){
        num = num->next;
        ++count;
    }
    return count;
}

char bigIntIsEmpty(BigInt num){

    if(bigIntCount(num)){
        return 0;
    }  else
        return 1;
}

char* bigIntToString(BigInt num){
    if(!num || num->digit == 0)
        return NULL;
    size_t count = bigIntCount(num);
    char sign = 0;
    if(num->digit == -1)
        ++sign;
    char *text = malloc(sizeof(char)*(count+1+sign));
    if(!text)
        return NULL;
    char temp[count];
    num = num->next;
    for(int i = 0; num->next ; ++i){
        temp[i] = num->digit + '0';
        num = num->next;
    }
    temp[count-1] = num->digit + '0';

    for(int i = 0, j = count-1+sign; i < count; ++i, --j){
        text[j] = temp[i];
    }

    text[count+sign] = 0;
    if(sign)
        text[0] = '-';
    return text;
}

void bigIntPrint(BigInt num){
    const char *text = bigIntToString(num);
    printf("%s", text);
    free((char*)text);
}

void bigIntDone(BigInt num){
    if(!num)
        return;
    while(num->next){
        BigInt previous = num;
        num = num->next;
        free(previous);
    }
    free(num);
}

void bigIntMakeEmpty(BigInt num){
    BigInt previous;
    if(!num)
        return;
    num->digit = 0;
    if(num->next){
        previous = num;
        num = num->next;
        previous->next = NULL;
        while(num->next){
            previous = num;
            num = num->next;
            free(previous);
        }
        free(num);
    }
}

void bigIntAbs(BigInt num){
    if(num && num->digit != 0)
        num->digit = 1;
}

int bigIntAdd(BigInt num, BigInt num1){
    BigInt numTemp;
    BigInt numTempHead;

    int flag = 0;

    if(!num || !num1 || num->digit == 0 || num1->digit == 0)
        return 0;
    numTemp = bigIntCopy(num);
    numTempHead = numTemp;
    if (!numTemp)
        return 0;

    if(numTemp->digit != num1->digit){
        bigIntChangeSign(num1);
        if(bigIntSub(numTemp, num1) == 0){
            bigIntDone(numTemp);
            return 0;
        }
        bigIntChangeSign(num1);
        num->digit = numTemp->digit;
        flag = 1;
    }

    if(flag == 0){
        numTemp = numTemp->next;
        num1 = num1->next;
        while(num1->next){
            numTemp->digit += num1->digit;
            if(numTemp->next == NULL){
                numTemp->next = bigIntCreate();
                if(!numTemp->next){
                    bigIntDone(numTempHead);
                    return 0;
                }
            }
            numTemp = numTemp->next;
            num1 = num1->next;
        }
        numTemp->digit += num1->digit;

        numTemp = numTempHead->next;

        while(numTemp->next){
            if(numTemp->digit > 9){
                numTemp->digit -= 10;
                ++numTemp->next->digit;
            }
            numTemp = numTemp->next;
        }
        if(numTemp->digit > 9){
            numTemp->next = bigIntCreate();
            if(!numTemp->next){
                bigIntDone(numTempHead);
                return 0;
            }

            numTemp->digit -= 10;
            ++numTemp->next->digit;
        }
    }
    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;
    bigIntDone(numTempHead);
    return 1;
}

int bigIntSub(BigInt num, BigInt num1){
    BigInt numTemp;
    BigInt numTempHead;
    BigInt num1Temp;
    BigInt num1TempHead;

    int flag = 0;
    int sign = 0;

    if(!num || !num1)
        return 0;
    numTemp = bigIntCopy(num);
    numTempHead = numTemp;
    if(!numTemp)
        return 0;
    num1Temp = bigIntCopy(num1);
    num1TempHead = num1Temp;
    if (!num1Temp){
        bigIntDone(numTempHead);
        return 0;
    }

    if(numTemp->digit != num1Temp->digit){  //+-; -+;
        bigIntChangeSign(num1TempHead);
        if(bigIntAdd(numTempHead, num1TempHead) == 0){
            bigIntDone(numTempHead);
            bigIntDone(num1TempHead);
            return 0;
        }
        bigIntChangeSign(num1TempHead);
    }

    if(numTemp->digit ==  num1Temp->digit){ //++;--;
        sign = num->digit;
        numTempHead->digit = 1;
        num1TempHead->digit = 1;
        if(bigIntCmp(numTemp, num1Temp) == -1){
            numTemp = num1TempHead;
            num1Temp = numTempHead;
            flag = 1;
        }
            while(1){
                numTemp = numTemp->next;
                num1Temp = num1Temp->next;

                numTemp->digit -= num1Temp->digit;

                if(!num1Temp->next)
                    break;
            }
            if(flag){
                numTemp = num1TempHead;
            }else
                numTemp = numTempHead;
            while(numTemp->next){
                if(numTemp->digit < 0){
                    --numTemp->next->digit;
                    numTemp->digit += 10;
                }
                numTemp = numTemp->next;
            }
        numTempHead->digit = sign;
        num1TempHead->digit = sign;

        if(flag){
            bigIntChangeSign(num);
            numTemp = numTempHead;
            numTempHead = num1TempHead;
            num1TempHead = numTemp;
        }
    }

    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;
    bigIntDone(numTempHead);
    bigIntDone(num1TempHead);

    if(bigIntCount(num) > 1){       //remove leading zeroes
        num = num->next;
        numTemp = num;
        while(1){
            num = num->next;
            if(num->digit != 0)
                numTemp = num;
            if(!num->next)
                break;
        }
        if(numTemp->next){
            bigIntDone(numTemp->next);
            numTemp->next = NULL;
        }
    }
    return 1;
}

int bigIntMul(BigInt num, BigInt num1){
    if(!num1 || !num || num->digit == 0 || num1->digit == 0)
        return 0;
    int flag = 0;
    int temp = 0;
    BigInt num1Temp = bigIntCopy(num1);
    BigInt numTemp = bigIntCreateFromInteger(0);
    BigInt num1TempHead = num1Temp;
    BigInt numTempHead = numTemp;
    BigInt zero = bigIntCreateFromInteger(0);
    if(!zero || !num1Temp || !numTemp){
        bigIntDone(numTemp);
        bigIntDone(num1Temp);
        bigIntDone(zero);
        return 0;
    }

    if(num->digit != num1->digit){
        flag = 1;
    }
        bigIntAbs(num);

        num1Temp = num1Temp->next;
        while(num1Temp->next){
            while(num1Temp->digit){
                temp = numTemp->digit;
                numTemp->digit = 1;
                if(!bigIntAdd(numTemp, num)){
                    bigIntDone(numTempHead);
                    bigIntDone(num1TempHead);
                    bigIntDone(zero);
                }
                numTemp->digit = temp;
                --num1Temp->digit;
            }
            num1Temp = num1Temp->next;

            if(!numTemp->next){
                numTemp->next = bigIntCreate();
                if(!numTemp->next){
                    bigIntDone(numTempHead);
                    bigIntDone(num1TempHead);
                    bigIntDone(zero);
                    return 0;
                }
            }
            if(!numTemp->next->next){
                numTemp->next->next = bigIntCreate();
                if(!numTemp->next->next){
                    bigIntDone(numTempHead);
                    bigIntDone(num1TempHead);
                    bigIntDone(zero);
                    return 0;
                }
            }

            numTemp = numTemp->next;
        }
        temp = numTemp->digit;
        numTemp->digit = 1;
        while(num1Temp->digit){
            if(!bigIntAdd(numTemp, num)){
                bigIntDone(numTempHead);
                bigIntDone(num1TempHead);
                bigIntDone(zero);
            }
            --num1Temp->digit;
        }
        numTemp->digit = temp;

        bigIntSub(numTempHead, zero);
    if(flag){
        num->digit = -1;
    }


    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;

     bigIntDone(numTempHead);
     bigIntDone(num1TempHead);
     bigIntDone(zero);
     return 1;
}

void bigIntChangeSign(BigInt num){
    if(!num || num->digit == 0)
        return;
    if(bigIntCount(num) == 1 && num->next->digit == 0){
        return;
    }
    if(num->digit == 1){
        num->digit = -1;
    }else
        num->digit = 1;
}

int bigIntCmp(BigInt num, BigInt num1){

    size_t length = 0;

    if(!num || !num1 || num->digit == 0 || num->digit == 0)
        return -2;

    if(num->digit > num1->digit){
        return 1;
    }else if(num->digit < num1->digit){
        return -1;
    }

    if(bigIntCount(num) > bigIntCount(num1)){
        if(num->digit == -1)
            return -1;
        return 1;
    }else if(bigIntCount(num) < bigIntCount(num1)){
        if(num->digit == -1)
            return 1;
        return -1;
    }

    const char *text, *text1;
    text = bigIntToString(num);
    text1 = bigIntToString(num1);

    length = strlen(text);

    for(size_t i = 0; i < length; ++i){
        if(text[i] == text1[i]){
            continue;
        }else if(text[i] > text1[i]){
            if(text[0] == '-'){
                free((char*)text);
                free((char*)text1);
                return -1;
            }
            free((char*)text);
            free((char*)text1);
            return 1;
        }else if(text[i] < text1[i]){
            if(text[0] == '-'){
                free((char*)text);
                free((char*)text1);
                return 1;
            }
            free((char*)text);
            free((char*)text1);
            return -1;
        }
    }
    return 0;
}

int bigIntDiv(BigInt num, BigInt num1){
    int count = -1;
    int temp = 0;
    int flag = 0;
    int sign = 1;

    if(num->digit != num1->digit){
        flag = 1;
    }

    sign = num1->digit;

    bigIntAbs(num1);
    bigIntAbs(num);

    BigInt numTemp = bigIntCopy(num);
    BigInt num1Temp = bigIntCopy(num1);
    BigInt two = bigIntCreateFromInteger(2);
    BigInt zero = bigIntCreateFromInteger(0);
    BigInt numTempHead = numTemp;
    if(!numTemp || !num1Temp || !two || !zero){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        bigIntDone(two);
        bigIntDone(zero);
        return 0;
    }

    if(bigIntCmp(num1, zero) == 0){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        bigIntDone(two);
        bigIntDone(zero);
        return 0;
    }

    while(bigIntCmp(numTemp, zero) == 1){
        count = -1;
        while(bigIntCmp(numTemp, num1Temp) >= 0){
            if(!bigIntMul(num1Temp, two)){
                bigIntDone(numTempHead);
                bigIntDone(num1Temp);
                bigIntDone(two);
                bigIntDone(zero);
                return 0;
            }
            ++count;
        }
        if(count == -1)
            break;
        temp += pow(2 ,count);
        if(!bigIntSet(num1Temp, num1)){
            bigIntDone(numTempHead);
            bigIntDone(num1Temp);
            bigIntDone(two);
            bigIntDone(zero);
            return 0;
        }
        for(int i = 0; i < count ; ++i){
            if(!bigIntMul(num1Temp, two)){
                bigIntDone(numTempHead);
                bigIntDone(num1Temp);
                bigIntDone(two);
                bigIntDone(zero);
                return 0;
            }
        }
        if(!bigIntSub(numTemp, num1Temp)){
            bigIntDone(numTempHead);
            bigIntDone(num1Temp);
            bigIntDone(two);
            bigIntDone(zero);
            return 0;
        }
        if(!bigIntSet(num1Temp, num1)){
            bigIntDone(numTempHead);
            bigIntDone(num1Temp);
            bigIntDone(two);
            bigIntDone(zero);
            return 0;
        }
    }

    if(!bigIntSetInt(numTemp, temp)){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        bigIntDone(two);
        bigIntDone(zero);
        return 0;
    }

    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;

    num1->digit = sign;
    if(flag){
        num->digit = -1;
    }else
        bigIntAbs(num);

    bigIntDone(numTempHead);
    bigIntDone(num1Temp);
    bigIntDone(two);
    bigIntDone(zero);

    return 1;
}

int bigIntSet(BigInt num, BigInt num1){
        if(!num || !num1)
            return 0;

        BigInt numTemp = bigIntCopy(num1);
        if(!numTemp)
            return 0;
        BigInt numTempHead = numTemp;

        num->digit = numTempHead->digit;
        numTemp = num->next;
        num->next = numTempHead->next;
        numTempHead->next = numTemp;

        bigIntDone(numTempHead);
    return 1;
}

int bigIntSetInt(BigInt num, int num1){
    if(!num)
        return 0;

    BigInt numTemp = bigIntCreateFromInteger(num1);
    if(!numTemp)
        return 0;
    BigInt numTempHead = numTemp;

    num->digit = numTempHead->digit;
    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;

    bigIntDone(numTempHead);
    return 1;

}

int bigIntSetString(BigInt num, const char *text){
    if(!num)
        return 0;

    BigInt numTemp = bigIntCreateFromString(text);
    if(!numTemp)
        return 0;
    BigInt numTempHead = numTemp;

    num->digit = numTempHead->digit;
    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;

    bigIntDone(numTempHead);
    return 1;
}

int bigIntMod(BigInt num, BigInt num1){
    BigInt numTemp = bigIntCopy(num);
    BigInt num1Temp = bigIntCopy(num1);
    BigInt numTempHead = numTemp;
    if(!numTemp || !num1Temp){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        return 0;
    }

    if(!bigIntDiv(numTemp, num1Temp)){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        return 0;
    }
    if(!bigIntMul(num1Temp, numTemp)){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        return 0;
    }
    if(!bigIntSet(numTemp, num)){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        return 0;
    }
    if(!bigIntSub(numTemp, num1Temp)){
        bigIntDone(numTempHead);
        bigIntDone(num1Temp);
        return 0;
    }

    numTemp = num->next;
    num->next = numTempHead->next;
    numTempHead->next = numTemp;

    if(bigIntCount(num) == 1 && num->next->digit == 0)
        num->digit = 1;

    bigIntDone(numTempHead);
    bigIntDone(num1Temp);
    return 1;
}



