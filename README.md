# AlgAssignment2
Submission for the second assignment in Design of Algorithms at the University of Melbourne.

The assignment specification can be found in the a2_spec pdf.

This assignment can be separated into two parts.

The first part included two questions involving the implementation of a hash function and a hashtable.

Here is a quick overview of the hash function:
- string is read from line and each char is converted into 6-bit binary, each bit is enqueued into a queue
- using horner's method to prevent integer overflow, each bit is dequeued and the hash value calculated

Here is a quick overview of the hashtable implementation:
- strings are read and a hash value is obtained from the previous hash function
- the string is inserted into the hashed position and inserted into a sorted array by hash value to preserve their hashed order
- if a string cannot be hashed at the desired location, increment the position by a specified step
- if a full loop has been reached through incrementing by a step, double the hashtable size and reinsert elements using the sorted array

The second part included three questions pertaining to character level tries. The trie structure had to be created before the questions could be attempted

Here is a quick overview of the first question
- insert strings into trie
- print the pre-order traversal of the trie

Here is a quick overview of the second question
- insert strings into trie
- given a prefix length, the prefixes in the trie were collected using recursion and their frequency recorded
- print each prefix in alphabetical order with its associated frequency

Here is a quick overview of the third question
- insert strings into trie
- given a prefix "stub", recursively find all strings beginning with the prefix and record their frequency
- calculate the probability of obtaining a certain word given the prefix
- print the top five most probable strings
