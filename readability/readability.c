cd #include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
string text = get_string("Text:  ");
double L = (double)count_letters(text)/(double)count_words(text)*100;
double S = (double)count_sentences(text)/(double)count_words(text)*100;
int CLF =round( 0.0588 * L - 0.296 * S - 15.8);
if ( CLF < 1 )
    printf("Before Grade 1\n");
else if ( CLF > 16)
    printf("Grade 16+\n");
else
    printf("Grade %i\n", CLF);
}


int count_letters(string text)
{
int count_lets = 0;
int total = strlen(text);
for (int i = 0; i < total; i++)
{
    if (isalpha(text[i]))
    {
        count_lets = count_lets + 1;
    }
}
return count_lets;
}

int count_words(string text)
{
int count_words = 0;
int total = strlen(text);
for (int i = 0; i < total; i++)
{
    if (isspace(text[i]))
    {
        count_words = count_words + 1;
    }
}
return count_words +1 ;
}

int count_sentences(string text)
{
int count_sent = 0;
int total = strlen(text);
for (int i = 0; i < total; i++)
{
    if (text[i] == '.')
    {
        count_sent = count_sent + 1;
    }
    else if (text[i] == '!')
    {
        count_sent = count_sent + 1;
    }
    else if (text[i] == '?')
    {
        count_sent = count_sent + 1;
    }
}
return count_sent;
}

