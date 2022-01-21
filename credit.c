#include <stdio.h>
#include <cs50.h>
#include <math.h>

void processCard(long number);
string checkCard(int length, int checkSum, int firstDigit, int secondDigit);

int main(void)
{
    long cardNumber = get_long("Please enter your credit card number: ");

    processCard(cardNumber);
}

// Cycles through each digit of the card number, passing each one through Luhn's Algorithm and checking card type
void processCard(long number)
{
    int length = 0;
    int doubledSum = 0;
    int undoubledSum = 0;
    int firstDigit = 0;
    int secondDigit = 0;

    // Cycles through each number from end to start, ultimately storing the first and second digit of the long
    for (long mod = 10; (double)mod / ((double)number * 10) <= 1; mod *= 10)
    {
        length++;

        int digit = (int)floor((number % mod) / (mod / 10));
        secondDigit = firstDigit;
        firstDigit = digit;

        // Luhn's Algorithm
        if (length % 2 == 0 && digit != 0)
        {
            digit *= 2;
            for (long modY = 10; modY / (digit * 10) <= 1; modY *= 10)
            {
                doubledSum += (int)floor((digit % modY) / (modY / 10));
            }
        }
        else
        {
            undoubledSum += digit;
        }
    }

    // Checks numbers and prints card validity
    printf("%s\n", checkCard(length, doubledSum + undoubledSum, firstDigit, secondDigit));
}

// Passes processed card data through checklists for different card types and returns result
string checkCard(int length, int checkSum, int firstDigit, int secondDigit)
{
    int firstTwoDigits = (firstDigit * 10) + secondDigit;

    // CheckSum
    if (checkSum % 10 == 0)
    {
        // American Express
        if (length == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            return "AMEX";
        }
        // MasterCard
        else if (length == 16 && (firstTwoDigits > 50 && firstTwoDigits < 56))
        {
            return "MASTERCARD";
        }
        // Visa
        else if ((length == 13 || length == 16) && firstDigit == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }

}
