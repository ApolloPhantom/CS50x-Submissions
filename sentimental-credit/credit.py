# TODO
N = input("Number: ")
Z = 0
P = int(N)
i=1
while(P!=0):
    t=P%10
    if(i%2!=0):
        Z+=t
    else:
        if(2*t>=10):
            Z+= 2*t % 10 + 1
        else:
            Z+= 2*t
    i+=1
    P=P//10

K = int(N[0])*10 + int(N[1])
if((Z%10==0) and ((K==34) or (K==37) or (K>=51 and K<=55) or (K>=40 and K<= 49))):
    if((K==34 or K==37) and len(N)==15):
        print("AMEX")
    elif(K>=51 and K<=55 and len(N)==16):
        print("MASTERCARD")
    elif(K>=40 and K<=49 and (len(N)==16 or len(N)==13)):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
print(Z,K,len(N))