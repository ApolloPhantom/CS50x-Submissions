# TODO
from cs50 import get_int

N = get_int("Height: ")
while(1):
    if(N<1 or N>8):
        N = get_int("Height")
    else:
        break

for i in range(1,N+1):
    print(" "*(N-i)+"#"*i+"  "+"#"*i)
