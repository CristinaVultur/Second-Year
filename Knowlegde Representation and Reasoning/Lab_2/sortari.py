#2

list1 = [52, 73, 61, 38, 45, 29, 31]

#b

sorted_list1 = sorted(list1, key=lambda x: (x%10,x%100) , reverse=False)

print(sorted_list1)

#c

list2 = [522, 73, 6, 23238, 1145, 1342119, 231]
sorted_list2 = sorted(list2, key=lambda x: len(str(x)),reverse=False)
print(sorted_list2)

#d
list3 = [3333, 123, 55552]
sorted_list3 = sorted(list3, key=lambda x: len(set(str(x))))

print(sorted_list3)