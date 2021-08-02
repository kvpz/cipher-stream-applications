# Text encryption and pseudorandom deck shuffling applications using stream ciphers

## About this project
There were two problems I want to solve, or really, there are two problems my professor wants me to solve, (1) encrypting text using a shift cipher and (2) pseudorandomly shuffling a deck of cards with the least amount of processing time as possible. I had a hunch these problems could be solved using some methods from cryptography. To discover relatable methods, I started skimming the book Applied Cryptography by Bruce Schneier followed by many Wikipedia articles and other auxiliary sources. From Bruce's book and other sources I learned how stream ciphers mixed with pseudo-random sequence generators can be applied to cipher systems. Starting with problem (1), the simplest problem, it became apparent how a stream cipher can be applied. The stream, in this problem, is a sequence of characters that needs to be encoded. Using a shift cipher, it is very simple to determine what a character needs to become for encryption. A stream cipher algorithm has a function that encrypts each bit or character, in this problem, individually. In the case of problem (1), each character in the stream of characters is encrypted independently of all other characters in the stream, but the deck of cards in problem (2) needs to undergo a more delicate encryption process to fulfill the business requirement. At the same abstraction level as problem (1), problem (2) seems simple, and the application of stream cipher algorithms seems appropriate for these two problems; but the complexity of the individual objects, a deck of cards in the case of problem (2), plus the business requirement makes the problem more difficult using stream cipher methodologies. This projects intends to create a solution that is similar, at least in an abstracted form, for both of these problems.  In other words, a generic library with cryptographic capabilities is being created for the purpose of encrypting text or "randomly" shuffling a deck of cards.

## Note to Interested Programmers
The code that makes up the ciphersuite uses some keywords for variable and structure names that are not intuitive for someone that simply wants to use the library to encrypt some text; and to be honest, I did not know whether I was using these keywords appropriately when I first wrote the code. The keywords I used for naming variables and structures were based on the knowledge I accumulated after reading several chapters from Bruce Schneier's Cryptography (2nd Edition). Their meanings and definitions seemed intuitive so I went ahead with using them in my code in an attempt to produce code that is sensible in terms of professional communication. Engineers should share a common vocabulary for effective communication afterall.


## A Quick Lesson on Cryptography

coming soon, eventually

## Text encryptor program
![](/images/encryptor.png)
![](/images/encryptor-1.png)
![](/images/encryptor-2.png)

## Biased card game program
![](/images/cardgame-mainmenu.png)
![](/images/cardgame-ingamemenu.png)
![](/images/cardgame-fourplayer-hands-01.png)
![](/images/cardgame-fourplayer-results.png)
![](/images/cardgame-eightplayer-result.png)
