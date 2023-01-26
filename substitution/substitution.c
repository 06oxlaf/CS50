#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string alpha(string Plaintext, string argv[]);

int main(int argc, string argv[])
{
if (argc != 2)
{
    printf("Usage: ./substitution key\n");
    return 1;
}
int total = strlen(argv[1]);
for (int i = 0; i < total; i++)
{
    if (isalpha(argv[1][i]))
    {

    }
    else
        return 1;
}

for (int i = 0; i < total; i++)
{
    argv[1][i] = tolower(argv[1][i]);
    char lets = (argv[1][i]);
    for (int j = 0; j < total; j++)
        if (j == i)
        {
        }
        else if (lets == argv[1][j])
            return 1;
}

if (total != 26)
{
    printf("Key must contain 26 characters.\n");
    return 1;
}

else
{
    string Plaintext = get_string("Plain Text: ");
    Plaintext = alpha(Plaintext, argv);
    printf("ciphertext: %s\n", Plaintext);
}
}

string alpha(string Plaintext, string argv[])
{
int lets = 0;
int total = strlen(Plaintext);
for (int i = 0; i < total; i++)
{
    if (islower(Plaintext[i]))
    {
        int j = i;
        Plaintext[i] = tolower(argv[1][Plaintext[j] + -97]);
    }
    else if (isupper(Plaintext[i]))
    {
        int j = i;
        int n = Plaintext[j];
        Plaintext[i] = toupper(argv[1][Plaintext[j] - 65]);
    }
}
return Plaintext;
}