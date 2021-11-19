#a
from typing import List, Union


def gen_matrice():
    matrice = []
    matrice.append([chr(x) for x in range(ord('a')-1,ord('z')+1)])
    for x in range(ord('a'),ord('z')):
        list = [chr(x)]
        for x in range(ord('a'), ord('z')):
            list.append(0)
        matrice.append(list)
    return matrice

mat = gen_matrice()
cuvinte =  ["papagal", "pisica","soarece","bolovan","soparla","catel", "pasare"]

def completeaza_matrice(list, matrice):

    for cuv in list:
        for i in range(0,len(cuv)-1):
            matrice[ord(cuv[i])-ord('a')+1][ord(cuv[i+1])-ord('a')+1]+=1
    return matrice

print(completeaza_matrice(cuvinte, mat))