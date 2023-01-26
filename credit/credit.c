#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long lund(long Number, long nDigits);
long type(long Number, long nDigits);

int main(void)
{
long Number = get_long("Enter card number");
long nDigits = floor(log10(labs(Number))) + 1;

long checksum = lund(Number, nDigits);
long End_num =type(Number, nDigits);

//printf("%li\n", checksum);
if(checksum % 10 == 0)
{
    if(nDigits == 15 || nDigits == 16 || nDigits == 13)
    {
        if(End_num == 34 || End_num == 37)
            printf("AMEX\n");
        else if(End_num == 51 || End_num == 52 || End_num == 53 || End_num == 54 || End_num == 55 )
            printf("MASTERCARD\n");
        else if(End_num/10 == 4)
            printf("VISA\n");
        else
        {
            printf("INVALID\n");
    }
    }
    else
    {
    printf("INVALID\n");
    }
    }
else
{
printf("INVALID\n");
}
    }









long lund(long Number, long nDigits)
{
long n = 10;
long x = 1;
long total = 0;
long odds = 0;
long even = 0;
for (int i=0; i < nDigits; i++)
{
    long digits =  Number % n;
    digits = ((digits - total)/x);
    //printf("%li\n", digits);
    if(i % 2 == 1 )
    {
        digits = digits*2;
        if (digits >= 10)
        {
            digits = 1 + digits % 10;
        }
        odds = odds + digits;
        //printf("%li\n", odds);
        total = total + digits;
        n = n*10;
        x = x*10;
    }
    else
    {
        even = even + digits;
        //printf("%li\n", even);
        total = total + digits;
        n = n*10;
        x = x*10;
    }
}
long checksum = even + odds;
return checksum;
}

long type(long Number, long nDigits)
{
long p=1;
    for (int j = 0; j < nDigits-2; j++)
        p = p*10;
long End_num = Number/p;

return End_num;
}