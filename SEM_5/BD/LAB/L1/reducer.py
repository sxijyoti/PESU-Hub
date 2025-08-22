#!usr/bin/env python3
import sys

prev_word = None
count = 0

for line in sys.stdin:
	curr_word, value = line.split(",")
	value = list(value)
	if(curr_word == prev_word):
		count+=value
	else:
		if(prev_word):
				print(prev_word,count)
		count = 1
	prev_word = curr_word
print(prev_word,count)