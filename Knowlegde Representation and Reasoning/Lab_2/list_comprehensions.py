#1
list1 = [i for i in range(1,10) if i%2 is 1 ]
print(list1)

#2
list2 = [chr(i) for i in range(ord('a'),ord('z'))]#chr->ascii to letter, #ord->letter to ascii
print(list2)

#3
def functie3(n):
   return [x * -pow(-1, x) for x in range(1,n+1)]

print(functie3(8))

#4
def functie4(list):
    return [x for x in list if x%2 is 1]

print(functie4([1, 2, 3, 4, 5, 6]))

#5

def functie5(list):
    return [list[i] for i in range(0,len(list)) if i%2 is 1]

print(functie5([1, 2, 3, 4, 5, 6]))

#6
old6 = [2,4,1,7,5,1,8,10]

new6 = [old6[i] for i in range(0,len(old6)) if i%2 is old6[i]%2]
print(new6)


#7

def func7(list):
    return [(list[i], list[i+1]) for i in range(0,len(list)-1)]

print(func7([1,2,3,4]))

#8

def func8(n):
    return [[i*y for y in range(1,n) ]for i in range(1,n)]

print(func8(5))

#9

sir = "abcde"

list9 = [sir[i:]+sir[:i] for i in range(0,len(sir))]

print(list9)

#10
def funct10(n):
    return [[i for j in range (0,i)] for i in range(0,n)]

print(funct10(10))