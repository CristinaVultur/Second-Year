#2 siruti de caractere sunt anagrame sau nu

sir1 = input("primul cuvant: ") #citire de la tastatura, mereu un string
sir2 = input("al doilea cuvant: ")

if(len(sir1)!=len(sir2)):
    print("Nu sunt anagrame1")
else:
    for i in range(0,len(sir1)):
        index = sir2.find(sir1[i])
        if(index > -1):
            sir2 = sir2.replace(sir2[index],"",1)#third parameter for the number of times it repalces the character
        else:
            print("Nu sunt anagrame2")
            break

    if(len(sir2)==0):
        print("ANAGRAME")
