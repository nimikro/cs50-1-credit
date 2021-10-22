#include <cs50.h>
#include <stdio.h>
#include <math.h>

int mod(int power, int card_number);

int main(void)
{
    long card = get_long("Number: ");
    int checksum=0,i,sum_odd=0,final_sum;
    long digits;
    long digit;

    //loop for EVEN digits to calculate checksum
    for(i = 2; i < 17; i = i+2)
    {
        digits = fmod(card, pow(10,i)); //mod function for long numbers:breaks the card number at i digit, saves the left half to digits
        digit = digits / pow(10,i-1); //saves the left most digit(i digit) to digit
        digit = digit*2; //multiply digit by 2
        checksum = checksum + digit/10 + digit%10; //calculate checksum: using div and mod to add the products' digits together
    }

    //loop for ODD digits to calculate sum
    for(i = 1; i < 17; i = i+2)
    {
        digits = fmod(card, pow(10,i)); //mod function for long numbers:breaks the card number at i digit, saves the left half to digits
        digit = digits / pow(10,i-1); //saves the left most digit(i digit) to digit
        sum_odd = sum_odd + digit; //calculate sum of odd digits
    }

    final_sum = sum_odd + checksum;

    if((final_sum%10) != 0)//check invalid
    {
        printf("INVALID\n");
    }
    else //card is definitely valid, move to check card type
    {
        //calculate 16th, 15th 14th and 13th digits to check card type:
        //AMEX(15th == 3 AND 14th == 4 or 7), MCARD (16th == 5 AND 14th == 1,2,3,4 or 5), VISA (16th == 4)
        digits = fmod(card, pow(10,16));
        int digit_mcard1 = digits / pow(10,15);
        int digit_visa1 = digit_mcard1;

        digits = fmod(card, pow(10,15));
        int digit_mcard2 = digits / pow(10,14);

        digits = fmod(card, pow(10,15));
        int digit_amex1 = digits / pow(10,14);

        digits = fmod(card, pow(10,14));
        int digit_amex2 = digits / pow(10,13);

        digits = fmod(card, pow(10,13));
        int digit_visa2 = digits / pow(10,12);

        if(digit_amex1 == 3 && (digit_amex2 == 4 || digit_amex2 == 7)) //check AMERICAN_EXP (15 digits)
        {
            printf("AMEX\n");
        }
        else if(digit_mcard1 == 5 && (digit_mcard2 == 1 || digit_mcard2 == 2 || digit_mcard2 == 3 || digit_mcard2 == 4 || digit_mcard2 == 5)) //check MASTER CARD (16d igits)
        {
            printf("MASTERCARD\n");
        }
        else if(digit_visa1 == 4 || digit_visa2 == 4) //check VISA (16 or 13 digits)
        {
            printf("VISA\n");
        }
        else printf("INVALID\n");
    }
}
