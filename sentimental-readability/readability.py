from cs50 import get_string


def main():
    text = get_string("Text:  ")
    L = count_letters(text)/count_words(text)*100
    S = count_sentences(text)/count_words(text)*100
    CLF = round( 0.0588 * L - 0.296 * S - 15.8)
    if ( CLF < 1 ):
        print("Before Grade 1")
    elif ( CLF > 16):
        print("Grade 16+")
    else:
        print(f"Grade {CLF}")




def count_letters(text):
    count_lets = 0
    total = len(text)
    for i in range(total):
        char = text[i]
        if (char.isalpha()):
            count_lets = count_lets + 1
    return count_lets

def count_words(text):
    count_words = 0
    total = len(text)
    for i in range(total):
        char = text[i]
        if (char.isspace() == True):
            count_words = count_words + 1
    return count_words + 1


def count_sentences(text):
    count_sent = 0
    total = len(text)
    for i in range(total):
        if (text[i] == '.'):
            count_sent = count_sent + 1
        elif(text[i] == '!'):
            count_sent = count_sent + 1
        elif (text[i] == '?'):
            count_sent = count_sent + 1
    return count_sent

main()