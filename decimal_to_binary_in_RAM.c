#include<stdio.h>

#define ARCH 32 

int main(){
    char binaryInt [ARCH+1]; // one extra place for nul terminator '\0'
    char binaryFract [ARCH+1];
    int  integral,i, leadingzeros=0, tailingzeros=ARCH-1, sign = 0;
    float product, input, fractional;



    for(i=0; i<ARCH; i++){binaryInt[i]='0'; binaryFract[i]='0';} // fill the arrays with zeros
    binaryInt[ARCH]='\0'; binaryFract[ARCH]='\0'; // add nul terminator at index  (last one)
    

    printf("***** Convert Float to Binary *******\n");
    printf("\nEnter float value : ");

    scanf("%f",&input); // take the float number input from user
    
    integral = (int)input; // separate the integer part
    fractional = input - (int)input; // separate the floating part (after the decimal point)

    // converting from decimal to binary for the integer part
    // collect bits from bottom to top
    for(i=ARCH-1; i>=0; i--){
	binaryInt[i] =  integral % 2 + '0'; // we add char '0' to convert number to char rep.
        integral /= 2;
    }
    
    // converting from decimal to binary for the after-decimal-point part
    // collect bits from top to bottom
    for (i=0; i<=ARCH-1; i++){
        product = fractional * 2;
	binaryFract [i] = ((int)product) + '0';
	if(product==1){break;} // once the product is 1, that means the end of operation
	if(product>1){product-=1;}
	fractional = product; 
    }

    // counting leading zeros
    while(binaryInt[leadingzeros]=='0'){leadingzeros++;}
    // counting tailing zeros
    while(binaryFract[tailingzeros]=='0'){tailingzeros--;}
    
    // trim the final answer
    int size = (ARCH-leadingzeros)+tailingzeros+1+1+1; // one for the dot, one for nul terminator, and one for tailing zero cuz it represents the count not the size
    int index=0;
    char float_Rep[size];
    for(i=leadingzeros; i<ARCH; i++){float_Rep[index++] = binaryInt[i];}
    float_Rep[index++] = '.';
    for(i=0; i<tailingzeros+1; i++){float_Rep[index++] = binaryFract[i];}
    float_Rep[index++] = '\0';

    
    
    // finding the sign
    if (input<0){sign = 1;}

    // calculating the exponent
    int e = 0, eCopy;
    char eBinary [8+1];
    while(float_Rep[e]!='.'){e++;}
    if(e==0){while(float_Rep[e]!='1'){e++;} e = (-1*e) + 127;}
    else{e = (e-1) + 127;}
    
    eCopy = e;
    
    for(i=7; i>=0; i--){
	eBinary[i] =  eCopy % 2 + '0';
        eCopy /= 2;
    }
    eBinary[8] = '\0';

   // finding the mantissa
   int x=0;
   char mantissa[23+1]; // one for the nul terminator '\0'
   if(e>=127){
     for(i=1; i<23; i++){
         if(float_Rep[i]!='.'){
            mantissa[x++] = float_Rep[i];
         }     
     }
   }
   
   else{
     int right_shift = 127-e+1;
     for(i=right_shift; i<right_shift+23; i++){
         mantissa[x++] = float_Rep[i];
     }
   
   }
   mantissa[23] = '\0';

   // printing out the result
   printf("\nFloat in Binary: \t%s\n\n", float_Rep);
   printf("                            \t -------------------------------------\n");
   printf("Float Representation in RAM:\t %d | %s | %s\n", sign, eBinary, mantissa);
   printf("                            \t -------------------------------------\n");
   printf("                              Sign | Exponent | Mantissa\n");

   
}
