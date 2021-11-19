#a

dictionary = {
    (1,4): "mic",
    (4,8): "mediu",
    (8,15):"mare"
}

#b

sir_list =  ["bau-bau", "bobocel", "14 pisici", "1pitic", "pisicel", "botosel", "414", "ham", "-hau", "bob", "bocceluta"]

dictionar_litere = {} # chr(k):set() for k in range(ord('a'),ord('z')+1)}

for cuvant in sir_list:
    for chr in cuvant:
            if chr in dictionar_litere:
                dictionar_litere[chr].add(cuvant)
            else:
                dictionar_litere[chr] = set()
                dictionar_litere[chr].add(cuvant)


print(dictionar_litere)

for key in list(dictionar_litere):
    if key.isalpha() is False:
        print(key,dictionar_litere.get(key))
        del dictionar_litere[key]

print(len(dictionar_litere))