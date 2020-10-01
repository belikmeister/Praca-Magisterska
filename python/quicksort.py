# setup; build a list with random elements
import random
import time

lNums = []
rangeEnd=pow(2,16)
for item in range(0,rangeEnd):
	lNums.append(random.randint(0,1000))

#print (lNums)

#quicksort using python's list comprehensions
def quicksort( tempList ):
	if tempList == []:
		return []
	else:
		# select and remove pivot element from list
		# there are several options for how to do this
		pivotValue = tempList[0]
		lesserList = quicksort( [x for x in tempList[1:] if x < pivotValue])
		greaterList = quicksort( [x for x in tempList[1:] if x >= pivotValue])
		return lesserList + [pivotValue] + greaterList
start = time.time()
sortedList=quicksort(lNums)
elapsed = time.time() - start
print("Sortowanie trwało:", elapsed)