with open('SRN.txt', 'r') as file:
    text = file.read()

text = text.lower()

words = ['th','he','ar','ing','e','or']

freq = {word: text.count(word) for word in words}

for word in words:
    print(f"{word}: {freq[word]}")
