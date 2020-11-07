/*Nadav Buchwalter 313367690*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#define TRUE 0
#define FALSE 1

const int MAX_NUMS=20;
const int MAX_DEC_NUMBER=255;
const int OCT=8,BIN=2,DEC=10;

int charToInt(char c);
int stringToInt(char number[ ], int base);
int intToString(int num, char numStr[ ], int base);
void printMenu(int base);
int isValidDigit(int digit, int base);
int enterNumber(int numbers[ ], int totalNums, int base);
int find(int numbers[ ], int numKey, int totalNums);
int howManyEven(int numbers[ ], int totalNums);
void printArray(int numbers[], int totalNums);

int isBIN(char number[ ]);
int stringToBIN(char number[ ]);
int stringToOCT(char number[ ]);

int calcBaseToDec(char number[ ],int base);
int calcDecToBase(char number[ ],int base);
int sizeCheck(char number[],int base);
int validMainPath(int choose);
void printBinMenu(int base);
void printOctMenu(int base);
int enterNumber(int numbers[ ], int totalNums, int base);
void printArray(int numbers[], int totalNums);
int subMenu(int base);
int conditionsCalc(char number[ ], int base);
void bubbleSort(int numbers[], int totalNums);



int main()
{

    int numsArr[MAX_NUMS];//Stores the numbers
    int totalNums=0;//Counter for how many numbers stored until now in the array
    int choose1,choose2;
    int currBase=DEC;
    char c[MAX_NUMS];


    printMenu(currBase);
    while(choose1!=6)
    {

        scanf("%d",&choose1);
        if(choose1==1)  //Change bases
        {
            currBase=subMenu(currBase);
        }

        else if(choose1==2)  //Enter Numbers
        {

            if(totalNums==MAX_NUMS)
            {
                printf("Array is full\n"); // if the array is full
                printMenu(currBase);
            }
            else
            {


                while(enterNumber(numsArr, totalNums,currBase)==FALSE);

                totalNums++;
                printMenu(currBase);

            }

        }
        else if(choose1==3)  //Search for a number
        {
            char numsNums[9];
            int numKey=-1;
            while(numKey==-1)
            {
                numKey=conditionsCalc(numsNums,currBase);
            }
            find(numsArr,numKey,totalNums);
            printMenu(currBase);

        }

        else if(choose1==4)  //Count the even numbers
        {
            printf("%d\n",howManyEven(numsArr,totalNums));
            printMenu(currBase);
        }
        else if (choose1==5)  //Print the array in 3 bases
        {

            printArray(numsArr,totalNums);


        }

        else  // Exit the program
        {
            break;
        }
    }
    return 0;

}

/* Uses ASCII Calculate to define if it is a 1 char number */
int charToInt(char c)
{
    if(c<48 || c>57)
    {
        return -1;
    }
    int cTi=c;
    return cTi-48;
}

/*Change string to int if possible*/
int stringToInt(char number[ ], int base)
{
    int res;
    if(base==BIN)
    {
        if(isBIN(number)==0) //If the string is a valid number in a bin base
        {
            res=stringToBIN(number);//Calculate the number
            return res;
        }
        else
        {
            return -1;
        }
    }

    if(base==OCT)
    {
        for(int i=0; i<=strlen(number)-1; i++) //Octal number conditions check
        {
            if(isValidDigit(charToInt(number[i]),OCT)==0)
            {
                continue;
            }
            if(isValidDigit(charToInt(number[i]),OCT)==1)
            {
                return -1;

            }
        }
        res=stringToOCT(number); //If its A valid input return the num
        return res;
    }
    if(base=DEC)
    {
        for(int i=0; i<=strlen(number)-1; i++)
        {
            if(isValidDigit(charToInt(number[i]),DEC)==-1)
            {
                return -1;
            }
        }

        res=stringToDEC(number); //If its a valid input return the num
        return res;


    }
}

/*Check valid digits per bases*/
int isValidDigit(int digit, int base)
{
    if(base==BIN)
    {
        if(digit!=1 && digit!=0)  // Only 1 /0 is allow for binary
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(base==OCT)
    {
        if(digit>=0 && digit <=7)  // Only 1-7 is allow in octal
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(base==DEC)
    {
        if(digit>=0 && digit<=9)  // 0-9 numbers is allow in decimal
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}


/*Binary condition check*/
int isBIN(char number[ ])
{


    for(int i=0; i<=strlen(number)-1; i++) //possible digits check
    {
        if(isValidDigit(charToInt(number[i]),BIN)==0)
        {
            continue;
        }
        if(isValidDigit(charToInt(number[i]),BIN)==1)
        {
            return -1;

        }
    }
    return 0;

}

/*Change string into a binary number*/
int stringToBIN(char number[ ])
{
    int res=calcBaseToDec(number,BIN);
    return res;
}

/*Change string into an octal number*/
int stringToOCT(char number[ ])
{
    int res=calcBaseToDec(number,OCT);
    return res;
}

/*Change string into a decimal number*/
int stringToDEC(char number[ ])
{
    int res=0,counter=1;

    for(int i=0; i<=strlen(number)-1; i++)
    {
        res=res*10;
        counter*10;
        res+=charToInt(number[i]);
        counter*10;
    }
    return res;

}

/*Calculate the bases change result*/
int calcBaseToDec(char number[ ],int base)
{
    int j=strlen(number)-1;
    int counter=0;
    double res=0;

    for(j; j>=0; j--)
    {

        res+=charToInt(number[j])*(pow(base,counter));
        counter++;
    }
    return (int)res;
}

/*Check conditions of the number and alart if there is a problem*/
int conditionsCalc(char number[ ], int base)
{


    char input[9];
    scanf("%s",input);

    if(stringToInt(input,base)==-1)  //if the input is an invalid input
    {
        printf("Invalid input, Please enter a valid number\n");
        return -1;
    }
    if(sizeCheck(input,base)==1) //if the input is a big number
    {
        printf("Invalid input,the number you entered is too big, Please enter a smaller number\n");
        return -1;
    }
    return stringToInt(input,base);


}

/*Prints the main menu*/
void printMenu(int base)
{

    int choose1,choose2;
    char input[MAX_NUMS];

    if(base==DEC)
    {
        printf("You are in Decimal Mode\n");
        printf("1. Change Base.\n");
        printf("2. Enter a number.\n");
        printf("3. Find a number.\n");
        printf("4. Get the amount  of even numbers.\n");
        printf("5. Print. \n");
        printf("6. Exit. \n");
    }

    if(base==BIN)
    {
        printf("You are in Binary Mode\n");
        printf("1. Change Base.\n");
        printf("2. Enter a number.\n");
        printf("3. Find a number.\n");
        printf("4. Get the amount  of even numbers.\n");
        printf("5. Print. \n");
        printf("6. Exit. \n");
    }
    if(base==OCT)
    {
        printf("You are in Octal Mode\n");
        printf("1. Change Base.\n");
        printf("2. Enter a number.\n");
        printf("3. Find a number.\n");
        printf("4. Get the amount  of even numbers.\n");
        printf("5. Print. \n");
        printf("6. Exit. \n");
    }

}

/*Size check for the number*/
int sizeCheck(char number[],int base)
{

    if(base==DEC)
    {
        if(stringToDEC(number)>255)  // Max num exception for a decimal number
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(calcBaseToDec(number,BIN)>MAX_DEC_NUMBER)  //Max num exception for a binary number
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*Enter a number to the array*/
int enterNumber(int numbers[ ], int totalNums, int base)
{
    int res=conditionsCalc(numbers,base);
    if (res==-1)
    {
        return FALSE;
    }
    else
    {
        numbers[totalNums]=res;
        return TRUE;
    }

}


/*navigate between the menus*/
int subMenu(int base)
{
    int choose;

    printf("1.Decimal\n");
    printf("2.Binary\n");
    printf("3.Octal\n");


    scanf("%d",&choose);
    if(choose==1)
    {
        printMenu(DEC);
        return DEC;
    }
    if(choose==2)
    {
        printMenu(BIN);
        return BIN;
    }
    if(choose==3)
    {
        printMenu(OCT);
        return OCT;

    }
}

/*Search for a number in the array*/
int find(int numbers[ ], int numKey, int totalNums)
{

    int i;
    for(i=0; i<totalNums; i++)
    {
        if(numbers[i]==numKey)
        {
            printf("Found it!\n");
            return TRUE;
        }

    }

    printf("Does not found!\n");
    return FALSE;

}

/*Prints how many even numbers are in the array*/
int howManyEven(int numbers[ ], int totalNums)
{
    int i;
    int counter=0;

    for(i=0; i<totalNums; i++) // Calc odd numbers
    {
        (1&numbers[i]&&counter++);
    }

    return totalNums-counter; // Sub odd from the total
}

/*Change a number to a string*/
int intToString(int num, char numStr[ ], int base)
{
    //scanf("%d",&num);
    int size=9;
    int i,j;
    int remain;
    int original=num;



    for(i=7; i>=0; i--)
    {
        remain=num%base; //General calculation for base changes
        num=num/base;

        if(base==BIN)
        {

            if(remain==0)
            {
                numStr[i]='0';
            }
            else
            {
                numStr[i]='1';
            }
        }
        if(base!=BIN)  // if it is a decimal or a octal base
        {

            for(j=7; j>=5; j--)
            {
                if(i<5)
                {
                    numStr[i]=' ';
                }
                else if((base==OCT && original<64 && i<6) || (base==DEC && original<100 && i<6 ))
                {
                    numStr[i]=' ';
                }
                else if((base==DEC && original<10 && i<7) || (base==OCT && original<8 && i<7))
                {
                    numStr[i]=' ';
                }


                else
                {

                    if(remain==0)
                        numStr[i]='0';

                    if(remain==1)
                        numStr[i]='1';

                    if(remain==2)
                        numStr[i]='2';

                    if(remain==3)
                        numStr[i]='3';

                    if(remain==4)
                        numStr[i]='4';

                    if(remain==5)
                        numStr[i]='5';

                    if(remain==6)
                        numStr[i]='6';

                    if(remain==7)
                        numStr[i]='7';

                    if(remain==8)
                        numStr[i]='8';

                    if(remain==9)
                        numStr[i]='9';
                }

            }
        }
    }






    return TRUE;

}

/*print the array in 3 bases format*/
void printArray(int numbers[], int totalNums)
{

    bubbleSort(numbers,totalNums); //Always arrange the array before print
    char numStr[9];
    int num;
    int i;

    printf("List of Numbers\n");
    printf("= = = = = = = = =\n");
    printf("DEC     BIN	      OCT");


    for(i=0; i<totalNums; i++)
    {
        printf("\n");
        intToString(numbers[i],numStr,DEC);
        printf("%c%c%c\t",numStr[5],numStr[6],numStr[7]);
        intToString(numbers[i],numStr,BIN);
        printf("%s      ",numStr);
        intToString(numbers[i],numStr,OCT);
        printf("%c%c%c",numStr[5],numStr[6],numStr[7]);
    }

}


/*Sort the array*/
void bubbleSort(int numbers[],int totalNum)
{
    int i,j;
    for (i = 0; i < totalNum-1; i++)
        for (j = 0; j < totalNum-i-1; j++)
            if (numbers[j] > numbers[j+1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
}
