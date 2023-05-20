# TODO
X = input("Text: ")
Letters=0
Word=0
Sentences=0
for i in X:
    if(i=='!' or i=='.' or i=='?'):
        Sentences+=1
    elif(i==' '):
        Word+=1
    elif(i!=',' and i!=';' and i!='"' and i!='-' and i!=chr(39)):
        Letters+=1
Word+=1
L = Letters/Word
S = Sentences/Word
I = 0.0588*L*100 - 0.296*S*100 -15.8
if(I>=16):
    print("Grade 16+")
elif(I<1):
    print("Before Grade 1")
else:
    print("Grade ",int(round(I)))

