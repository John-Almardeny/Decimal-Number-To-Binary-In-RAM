#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<windows.h>

char mantissa32[100];
char mantissa64[200];
char exponent32[8];
char exponent64[11];
bool lessThan1;

void lessThanOne(double number);
int makeMantissa(double number);
double doublePart(double number);
void mantissaFn(const char *beforeDP , const char *afterDP);
void exponentFn (int power);
const char *toBinaryBeforeDecimalPoint(int number);
const char *toBinaryAfterDecimalPoint (double number);
void mantissaFnLess(const char *afterDP, double number);
void exponentFnLess (int power);
double validateInput();
void zeroEntry();
int main (void){
printf("\n This program allows you to convert between\n the decimal representation of numbers (like ""1.02"")\n and the binary format used by all modern CPUs.\n\n");
printf(" Author: Yahya Almardeny.\n\n");
printf(" ***************************************************\n\n");

double number;
printf("\n Insert the Decimal Number (Floating Point): ");
number = validateInput();

lessThanOne(number);
if (number){
    if (lessThan1){
        mantissaFnLess(toBinaryAfterDecimalPoint(doublePart(number)), number);
        printf("\n\n                            S       E                M  \n");
        printf("                            --------------------------------------\n");
        printf(" Single Precision (32 bits) %d | %s | %s\n", signPart(number), exponent32, mantissa32);
        printf("                            --------------------------------------\n\n");

        printf("\n\n                             S        E                         \tM  \n");
        printf("                             ----------------------------------------------------------------------\n");
        printf(" Double Precision (64 bits)  %d | %s | %s\n", signPart(number), exponent64, mantissa64);
        printf("                             ----------------------------------------------------------------------\n\n");
    }

    else if (!lessThan1){
        mantissaFn(toBinaryBeforeDecimalPoint(integerPart(number)), toBinaryAfterDecimalPoint(doublePart(number)));
        printf("\n\n                            S       E                M  \n");
        printf("                            --------------------------------------\n");
        printf(" Single Precision (32 bits) %d | %s | %s\n", signPart(number), exponent32, mantissa32);
        printf("                            --------------------------------------\n\n");

        printf("\n\n                             S        E                         \tM  \n");
        printf("                             ----------------------------------------------------------------------\n");
        printf(" Double Precision (64 bits)  %d | %s | %s\n", signPart(number), exponent64, mantissa64);
        printf("                             ----------------------------------------------------------------------\n\n");
    }
}
else{zeroEntry();}
printf("\n\n S: Sign , E: Exponent , M: Mantissa.\n");
getchar();getchar();

return 0;}



void lessThanOne(double number){
if (fabs(number)<1){lessThan1 = true;}
else {lessThan1 = false;}
}

int integerPart(double number){

int integerNumber = number;
if (integerNumber<0){return integerNumber*-1;}
return integerNumber;
}

double doublePart(double number){

int integerNumber = number;
double doubleNumber = number - (double)integerNumber;
if (doubleNumber<0){return doubleNumber*-1;}
return doubleNumber;
}

int signPart(double number){

if (number >= 0) {return 0;}
return 1;
}


const char *toBinaryBeforeDecimalPoint(int number){
static char s[50];
int i =0;
while (number){
    if (dividableTo2(number)){s[i] = '1'; i++;}
    else {s[i] = '0'; i++;}
    number/= 2;
}
s[i] =0;
char s_copy[i];
strcpy(s_copy, s);
i--;
int ii =0;
while (i>=0){
    s[ii]=s_copy[i];
    ii++; i--;
}
s[ii]=0;

return s;
}

int dividableTo2(int number){
int result = number / 2;
if ((result*2)==number){return 0;}
return 1;
}



const char *toBinaryAfterDecimalPoint (double number){
static char s[50];
int i=0;
if (number>0){
    while(number){
        number*=2;
        int integerNumber = number;
        if(integerNumber==1){s[i]='1'; i++; number = number - 1;}
        else{s[i]='0'; i++;}
    }
    s[i]=0;
    return s;
}
else {for (i=0;i<8;i++){s[i]='0';} s[i] =0; return s;}
}


void mantissaFn(const char *beforeDP , const char *afterDP){
int i=1, j=0;

while (beforeDP[i]){
    mantissa32[i-1] = beforeDP[i];
    mantissa64[i-1] = beforeDP[i];
    i++;
}
i--;
exponentFn(i);

while (afterDP[j]){
    mantissa32[i] = afterDP[j];
    mantissa64[i] = afterDP[j];
    j++; i++;
}

while (i<23){
mantissa32[i] ='0';
mantissa64[i] ='0';
i++;
}

while (i<52){
mantissa64[i] ='0';
i++;
}

mantissa32[23] =0;
mantissa64[52] =0;
}


void exponentFn (int power){
int power64 = power;

if (power>127){power -= 127;}
else if (power == 0) {power = 127;}
else {power += 127;}

if (power64>1023){power64 -= 1023;}
else if (power64 == 0) {power64 = 1023;}
else {power64 += 1023;}

char receiver[9];
char receiver64[12];
strcpy(receiver, toBinaryBeforeDecimalPoint(power));
strcpy(receiver64, toBinaryBeforeDecimalPoint(power64));
int i=0, j=0, ii=0, jj=0;
while (receiver[i]){i++;}
if (i>8){strcpy(exponent32, receiver);}
else {while(i<8){exponent32[j]='0'; j++;i++;} strcat(exponent32, receiver);}

while (receiver64[ii]){ii++;}
if (ii>11){strcpy(exponent64, receiver64);}
else {while(ii<11){exponent64[jj]='0'; jj++;ii++;} strcat(exponent64, receiver64);}
}


void mantissaFnLess(const char *afterDP, double number){
int i=0, j=0;

while (afterDP[i]!='1'){
       i++;
}
i++;
exponentFnLess(i);

while (afterDP[i]){
    mantissa32[j] = afterDP[i];
    mantissa64[j] = afterDP[i];
    j++;i++;
}

while (j<23){
    mantissa32[j] ='0';
    mantissa64[j] = '0';
    j++;
}
while (j<52){
    mantissa64[j] = '0';
    j++;
}

mantissa32[23] =0;
mantissa64[52] = 0;
}

void exponentFnLess (int power){
int power64 = 1023 - power;
power = 127 - power;
char receiver[9];
char receiver64[12];
strcpy(receiver, toBinaryBeforeDecimalPoint(power));
strcpy(receiver64, toBinaryBeforeDecimalPoint(power64));
int i=0, j=0, ii=0, jj=0;
while (receiver[i]){i++;}
if (i>8){strcpy(exponent32, receiver);}
else {while(i<8){exponent32[j]='0'; j++;i++;} strcat(exponent32, receiver);}

while (receiver64[ii]){ii++;}
if (ii>11){strcpy(exponent64, receiver64);}
else {while(ii<11){exponent64[jj]='0'; jj++;ii++;} strcat(exponent64, receiver64);}

}


double validateInput(){
int attempts =0;
while (attempts<10){
    bool invalidDetected = false;
    bool minusSign = false;
    bool plusSign = false;
    int x,y, counter=0;
    double number;
    char line[256];
    char *ptr = line;
    char *ptr1 = line;
if (fgets(line, sizeof(line), stdin)){
    while(*ptr1!='\n'){
        *ptr1 = *ptr;
        if(*ptr1!=' '){ptr1++;}
        ptr++;
    }
    ptr1 = &line[0];
    while(*ptr1!='\n'){
          if(!isdigit(*ptr1)){
            if ((*ptr1!='.') && (*ptr1!='-') && (*ptr1!='+')){
                printf("Invalid Input\n");
                invalidDetected = true;
                break;
            }
          }
     ptr1++;
     counter++;
    }
    if(invalidDetected==false){
        for(x=0;x<counter;x++){
            for(y=0;y<counter;y++){
                if(x!=y){
                    if((!isdigit(line[x])) && (!isdigit(line[y])) && (line[x] == line[y])){
                        printf("Invalid Input\n");
                        invalidDetected = true;
                        x = counter;
                        break;
                    }
                }
            }
        }
    }

    if(invalidDetected==false){
        x=0;
        while(line[x]){
            if(line[x] == '-'){minusSign=true;}
            else if (line[x]=='+'){plusSign=true;}
            if (minusSign==true && plusSign==true){
                    printf("Invalid Input\n");
                    invalidDetected = true;
                    break;
            }
        x++;
        }
    }

    if (invalidDetected == false){
        sscanf(line, "%lf", &number);
        return number;
    }
}

    attempts++;
    if (attempts==10){printf("\n**Failure To Retrieve Valid Input, No More Retries!\n"); Sleep(2000); getchar(); exit(0);}
}
}


void zeroEntry(){
printf("\n\n                            S       E                M  \n");
printf("                            --------------------------------------\n");
printf(" Single Precision (32 bits) 0 | 00000000 | 00000000000000000000000\n");
printf("                            --------------------------------------\n\n");
printf("\n\n                             S        E                         \tM  \n");
printf("                             ----------------------------------------------------------------------\n");
printf(" Double Precision (64 bits)  0 | 00000000000 | 0000000000000000000000000000000000000000000000000000\n");
printf("                             ----------------------------------------------------------------------\n\n");
}



