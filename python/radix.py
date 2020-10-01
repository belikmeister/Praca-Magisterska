import radix_lib as radix
import random
<<<<<<< HEAD
import argparse

parser = argparse.ArgPars
parser.add_argument('integers', metavar='N', type=int, nargs='+',
                   help='equator of 2')
=======
import time
import argparse
parser = argparse.ArgPars
>>>>>>> d83a9e46ae978dc3c5588651b9e781efb29ed846

arr = []
for item in range(0,1000000):
	arr.append(random.randint(0,1000000))
start = time.time()
sorted_tab=radix.radix(arr)
elapsed = time.time() - start

print("Posortowano w czasie:", elapsed)