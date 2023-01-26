from cs50 import get_int

Number = input("Number: ")
nDigits = len(Number)

n = 10
x = 1
total = 0
odds = 0
even = 0
Number = int(Number)
for i in range(nDigits):
    digits =  Number % n
    digits = ((digits - total)/x)
    if(i % 2 == 1 ):
        digits = digits*2
        total = total + (digits/2)*x
        if (digits >= 10):
            digits = 1 + digits % 10
        odds = odds + digits
        n = n*10
        x = x*10
    else:
        even = even + digits
        total = total + digits*x
        n = n*10
        x = x*10
checksum = even + odds

p = 1
for j in range(nDigits - 2):
    p = p*10
    End_num = round(Number/p)

if(checksum % 10 == 0):
    if(nDigits == 15 or nDigits == 16 or nDigits == 13):
        if(End_num == 34 or End_num == 37):
            print("AMEX")
        elif(End_num == 51 or End_num == 52 or End_num == 53 or End_num == 54 or End_num == 55 ):
            print("MASTERCARD")
        elif(round(End_num/10) == 4):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
