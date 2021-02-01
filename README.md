# CS50
Code for problem sets in CS50

Here you will find the code I submitted for marking in completing the CS50 course Harvard University offers online for free.  The objectives and specifications for all problem sets can be found here.  https://cs50.harvard.edu/x/2020/ .

## Points of Interest

I enjoyed this course, it was certainly challenging but starting with C gives great insight into the operation of a computer. Having to understand the size of certain primitives in memory as well as having to statically type variables.  This base level interaction with each byte in memory is what gives the language its power if it can make it a bit of headache when compared to newer high-level programming languages. This does mean that when the course moves onto python you have a huge appreciation for how much heavy lifting the language does for you.

I will draw your attention to some of my favorite challenges in the course, some that I found the most interesting. Either they posed a challenge or they introduced some new and fascinating concepts.

### Pset4 - Speller:
  This assignment asked you to take a dictionary file provided as the first argument and read it into memory. Then iterate over all words in a text file passed as the second argument and check them against the words in the dictionary.  I liked this assignment as it introduced many new concepts, eg. structs, malloc, the structures hash table, and trie as well as recursion. 
  
We were given the choice of reading the dictionary into either a hash table or a trie, I chose the trie as its efficiency for this task of storing a large number of strings fascinated me as it has big O o(k) where k is the length of the string to be inserted or search regardless of the number of strings in the structure.  I also chose to implement a recursive function on each node to free the memory used to store the dictionary when it was time to exit the program, which was another concept that fascinated me with its elegance.

### Pset5 - Filter 
  I feel this problem set home how you go about solving a problem algorithmically. For example, the blur filter sets the value of each pixel by calculating a mean average of the target pixel and every adjacent pixel. I didn't know it at the time but I now realize this is a prime example of when writing tests could save you so much time. I tested this solution manually, with pen and paper, calculating the value of each pixel in the, thankfully small test images. The most profound lesson I took from this challenge was just how fast a computer is at arithmetic, when you consider the resolutions we expect a computer to display 30+ times a second, this assignment highlighted how much calculation goes into determining the color of each of those pixels.
