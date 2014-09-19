Tera Staten
tns26

Abstract:
This report is for Project 1 under Dr. Duan from 3460:435 Algorithms. This project implements RSA Encryption an algorithm which is used for safely transferring messages using large prime numbers with the equation:
		(M^e) % n to encode the message and  (C^e) % n to decode the message. 
		
Introduction:
This project generates large prime numbers up to 10 digits using Fermat's Little Theorem to ensure that the numbers are prime. It also follows RSA encryption 

Previous Work:
Work done on this project before I was assigned would be the BigInt class including BigInt.h and BigInt.cpp. This work was done by a previous University of Akron student, and is used to store large integers as a 
list<uchar> for C++ users. This is important because C++ does not naturally accept large integers to 10 digits, thus this class was needed for overloaded operators, storage, and creation of BigInt integers.

Novel aspects of own work:
This project starts off with generating a prime number from 1 digit long to 10 digits long depending on what the user enters.  The user will need 2 primes (p, q) which are multiplied together to calculate n.
e is chosen by the user, it needs to be a number that is relatively prime to (p, q). Then the project computes d and displays d by printing (x, y) where x is the d. Once a user has n, e, and a message they can calculate
the message as an integer by typing 'e' e n message through the CLI. This prints an integer that represents the encoded message. To decode that message, a user types 'd' d n message(as integer) and will receive 
the decoded message.
The exact use cases are as follows:
·       yourProgram.exe  s   //your program should output a prime with s digit to the console
·       yourProgram.exe  a b   //your program should output (x,y) s.t. gcd(a,b) = ax+by and y>0
·       yourProgram.exe  e p q //your program should output (d,n) s.t. ed=1%(p-1)(q-1), n=pq
·       yourProgram.exe  ‘e’ e n message   //your program should output the encrypted message
·       yourProgram.exe  ‘d’ d n message   // your program should output the decrypted message

*RandomPrime is used to generate a random odd number that is then tested for primality using Fermat's Little Test. If it is not a prime the number will be incremented by two and tested against Fermat's Little Test
again.  These numbers are output to the user to encourage the user that the program has not frozen, Fermat's Little Test takes a long time to do with 10 digit numbers due to the modExp() function. It is not the most
efficient algorithm for modExp() but it works! A 10 digit prime number usually only takes 2 or less minutes to find but could be around 4 at maximum. 
*RSAEncryption is used to calculate the X(D), Y, N, message as an integer, and convert from the integer back to a message.  MessageToInt() multiplies each character's ASCII code by 128 to encode the message, then 
follows normal RSA rules by taking (M^e) % n  for the final message as an integer. IntToMessage() takes this integer and first computes (C^d) % n where  d is the private value that only the keyholder should know.
Then it takes that number and calculates that number % 128 to "pop a letter off" the integer. Then we store that popped off letter as a character and then divide that message(as an int) by 128. This repeats until
our message is complete. But the message is backwards! So we return a message in the proper direction. This should match the original message that was encoded, if it does not then shorten the message you input to 
encode.  M has to be less than n. I have a check for that, but sometimes it does not seem to work.

Conclusions:
This project is fun, it may not efficiently generate a random prime number but it does its job. I have generated a 15 digit prime using it, but it took about 4-6 minutes since my modExp() function is a little slow.
I have learned a lot about RSA Encryption and algorithms. My favorite part of this project was the message encoding/decoding by popping off letters and watching it work while debugging! I had no idea there were so
many prime numbers out there either. I found out how to use command line arguments with Visual Studio too, so hopefully my project will still work on Linux and Macs but I believe it should. 

References/appendices:
Used BigInt.h and BigInt.cpp made by a University of Akron Student.