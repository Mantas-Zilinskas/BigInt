#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "BigInt.h"



int main(){

BigInt n, n1, n2, n3, n4, n5, n6, n7;



n = bigIntCreateFromString("-0000987654321098765432109876543210");
n1 = bigIntCreateFromString("0123456789");
n2 = bigIntCreateFromString("000000000");
n3 = bigIntCreateFromString("0");
n4 = bigIntCreateFromString("-45f");
n5 = bigIntCreateFromString("-");
n6 = bigIntCreateFromString("");

assert(strcmp(bigIntToString(n),"-987654321098765432109876543210") == 0);
assert(strcmp(bigIntToString(n1),"123456789") == 0);
assert(strcmp(bigIntToString(n2),"0") == 0);
assert(strcmp(bigIntToString(n3),"0") == 0);
assert(n4 == NULL);
assert(n5 == NULL);
assert(n6 == NULL);

printf("bigIntCreateFromString() passed\n");

assert(bigIntCount(n) == 30);
assert(bigIntCount(n1) == 9);
assert(bigIntCount(n2) == 1);
assert(bigIntCount(n3) == 1);
assert(bigIntCount(n4) == 0);
assert(bigIntCount(n5) == 0);
assert(bigIntCount(n6) == 0);

printf("bigIntCount() passed\n");

n4 = bigIntCopy(n);
n5 = bigIntCopy(n1);
n6 = bigIntCopy(n2);
assert(strcmp(bigIntToString(n4),"-987654321098765432109876543210") == 0);
assert(strcmp(bigIntToString(n5),"123456789") == 0);
assert(strcmp(bigIntToString(n6),"0") == 0);

printf("bigIntCopy() passed\n");

bigIntChangeSign(n);
bigIntChangeSign(n1);
bigIntChangeSign(n2);

assert(strcmp(bigIntToString(n),"987654321098765432109876543210") == 0);
assert(strcmp(bigIntToString(n1),"-123456789") == 0);
assert(strcmp(bigIntToString(n2),"0") == 0);

printf("bigIntChangeSign() passed\n");

bigIntMakeEmpty(n);
bigIntMakeEmpty(n1);
bigIntMakeEmpty(n2);
bigIntMakeEmpty(n3);
bigIntMakeEmpty(n4);
bigIntMakeEmpty(n5);
bigIntMakeEmpty(n6);

assert(bigIntIsEmpty(n));
assert(bigIntIsEmpty(n1));
assert(bigIntIsEmpty(n2));
assert(bigIntIsEmpty(n3));
assert(bigIntIsEmpty(n4));
assert(bigIntIsEmpty(n5));
assert(bigIntIsEmpty(n6));

printf("bigIntIsEmpty() passed\n");

bigIntSetString(n, "123456");
bigIntSetString(n1, "987654");
bigIntSetString(n2, "-789");
bigIntSetString(n3, "-11568");
bigIntSetString(n4, "123456789");
bigIntSetString(n5, "-987654321");
bigIntSetString(n6, "-789");

assert(bigIntCmp(n,n1) == -1);
assert(bigIntCmp(n1,n) == 1);
assert(bigIntCmp(n2,n3) == 1);
assert(bigIntCmp(n4,n5) == 1);
assert(bigIntCmp(n2,n2) == 0);

printf("bigIntCmp() passed\n");

n7 = bigIntCreate();

bigIntSetString(n, "9999");
bigIntSetString(n1, "0");
bigIntSetString(n2, "-9876543210");
bigIntSetString(n3, "100000000000000000000000");
bigIntSetString(n4, "0");
bigIntSetString(n5, "-9630");
bigIntSetString(n6, "-963");
bigIntSetString(n7, "9630");

bigIntSet(n4, n);
bigIntSet(n5, n1);
bigIntSet(n6, n2);
bigIntSet(n7, n3);

assert(strcmp(bigIntToString(n),"9999") == 0);
assert(strcmp(bigIntToString(n1),"0") == 0);
assert(strcmp(bigIntToString(n2),"-9876543210") == 0);
assert(strcmp(bigIntToString(n3),"100000000000000000000000") == 0);
assert(strcmp(bigIntToString(n4),"9999") == 0);
assert(strcmp(bigIntToString(n5),"0") == 0);
assert(strcmp(bigIntToString(n6),"-9876543210") == 0);
assert(strcmp(bigIntToString(n7),"100000000000000000000000") == 0);

printf("bigIntSet() passed\n");


bigIntSetString(n, "9999");
bigIntSetString(n1, "1");
bigIntSetString(n2, "-9876543210");
bigIntSetString(n3, "-123456789");
bigIntSetString(n4, "963");
bigIntSetString(n5, "-9630");
bigIntSetString(n6, "-963");
bigIntSetString(n7, "9630");

bigIntAdd(n, n1);
bigIntAdd(n2, n3);
bigIntAdd(n4, n5);
bigIntAdd(n6, n7);

assert(strcmp(bigIntToString(n),"10000") == 0);
assert(strcmp(bigIntToString(n1),"1") == 0);
assert(strcmp(bigIntToString(n2),"-9999999999") == 0);
assert(strcmp(bigIntToString(n3),"-123456789") == 0);
assert(strcmp(bigIntToString(n4),"-8667") == 0);
assert(strcmp(bigIntToString(n5),"-9630") == 0);
assert(strcmp(bigIntToString(n6),"8667") == 0);
assert(strcmp(bigIntToString(n7),"9630") == 0);

printf("bigIntAdd() passed\n");


bigIntSetString(n, "100");
bigIntSetString(n1, "1");
bigIntSetString(n2, "-9876543210");
bigIntSetString(n3, "-123456789");
bigIntSetString(n4, "963");
bigIntSetString(n5, "9630");
bigIntSetString(n6, "-963");
bigIntSetString(n7, "-9630");

bigIntSub(n,n1);
bigIntSub(n2,n3);
bigIntSub(n4,n5);
bigIntSub(n6,n7);

assert(strcmp(bigIntToString(n),"99") == 0);
assert(strcmp(bigIntToString(n1),"1") == 0);
assert(strcmp(bigIntToString(n2),"-9753086421") == 0);
assert(strcmp(bigIntToString(n3),"-123456789") == 0);
assert(strcmp(bigIntToString(n4),"-8667") == 0);
assert(strcmp(bigIntToString(n5),"9630") == 0);
assert(strcmp(bigIntToString(n6),"8667") == 0);
assert(strcmp(bigIntToString(n7),"-9630") == 0);


bigIntSetString(n, "1000");
bigIntSetString(n1, "0");
bigIntSetString(n2, "3456789");
bigIntSetString(n3, "-123456789");
bigIntSetString(n4, "-123456789");
bigIntSetString(n5, "3456789");
bigIntSetString(n6, "0");
bigIntSetString(n7, "0");

bigIntSub(n,n1);
bigIntSub(n2,n3);
bigIntSub(n4,n5);
bigIntSub(n6,n7);


assert(strcmp(bigIntToString(n),"1000") == 0);
assert(strcmp(bigIntToString(n1),"0") == 0);
assert(strcmp(bigIntToString(n2),"126913578") == 0);
assert(strcmp(bigIntToString(n3),"-123456789") == 0);
assert(strcmp(bigIntToString(n4),"-126913578") == 0);
assert(strcmp(bigIntToString(n5),"3456789") == 0);
assert(strcmp(bigIntToString(n6),"0") == 0);
assert(strcmp(bigIntToString(n7),"0") == 0);

printf("bigIntSub() passed\n");


bigIntSetString(n, "70");
bigIntSetString(n1, "0");
bigIntSetString(n2, "-25");
bigIntSetString(n3, "-10");
bigIntSetString(n4, "-12");
bigIntSetString(n5, "1200");
bigIntSetString(n6, "1000000");
bigIntSetString(n7, "-1000000000000");

bigIntMul(n,n1);
bigIntMul(n2,n3);
bigIntMul(n4,n5);
bigIntMul(n6,n7);

assert(strcmp(bigIntToString(n),"0") == 0);
assert(strcmp(bigIntToString(n1),"0") == 0);
assert(strcmp(bigIntToString(n2),"250") == 0);
assert(strcmp(bigIntToString(n3),"-10") == 0);
assert(strcmp(bigIntToString(n4),"-14400") == 0);
assert(strcmp(bigIntToString(n5),"1200") == 0);
assert(strcmp(bigIntToString(n6),"-1000000000000000000") == 0);
assert(strcmp(bigIntToString(n7),"-1000000000000") == 0);

printf("bigIntMul() passed\n");


bigIntSetString(n, "0");
bigIntSetString(n1, "1");
bigIntSetString(n2, "-596");
bigIntSetString(n3, "-15");
bigIntSetString(n4, "-12");
bigIntSetString(n5, "12");
bigIntSetString(n6, "-1000000000000000000");
bigIntSetString(n7, "-1000000000000");

bigIntDiv(n,n1);
bigIntDiv(n2,n3);
bigIntDiv(n4,n5);
bigIntDiv(n6,n7);


assert(strcmp(bigIntToString(n),"0") == 0);
assert(strcmp(bigIntToString(n1),"1") == 0);
assert(strcmp(bigIntToString(n2),"39") == 0);
assert(strcmp(bigIntToString(n3),"-15") == 0);
assert(strcmp(bigIntToString(n4),"-1") == 0);
assert(strcmp(bigIntToString(n5),"12") == 0);
assert(strcmp(bigIntToString(n6),"1000000") == 0);
assert(strcmp(bigIntToString(n7),"-1000000000000") == 0);

printf("bigIntDiv() passed\n");


bigIntSetString(n, "0");
bigIntSetString(n1, "1");
bigIntSetString(n2, "-32");
bigIntSetString(n3, "-15");
bigIntSetString(n4, "-60");
bigIntSetString(n5, "12");
bigIntSetString(n6, "895");
bigIntSetString(n7, "1000");

bigIntMod(n,n1);
bigIntMod(n2,n3);
bigIntMod(n4,n5);
bigIntMod(n6,n7);


assert(strcmp(bigIntToString(n),"0") == 0);
assert(strcmp(bigIntToString(n1),"1") == 0);
assert(strcmp(bigIntToString(n2),"-2") == 0);
assert(strcmp(bigIntToString(n3),"-15") == 0);
assert(strcmp(bigIntToString(n4),"0") == 0);
assert(strcmp(bigIntToString(n5),"12") == 0);
assert(strcmp(bigIntToString(n6),"895") == 0);
assert(strcmp(bigIntToString(n7),"1000") == 0);

printf("bigIntMod() passed\n");

return 0;
}
