# CSE 178: Computers and Network Security

## About
This repository contains the AES-128 project that was done for my Network Security class, implemented in C++.

## What It Does
- Takes a hexadecimal string from the user
  - Plaintext input
  - Example: *1f2e3d4c5b6a79*
- Takes another hexadecimal string from the user, maximum 32 characters (as it has to be a 128-bit key)
  - The key used for encrypting the plaintext input
- Performs the AES-128 encryption algorithm on that input, in 32 character/128-bit chunks
- Outputs the input, encrypted
  - Known as ciphertext

- Can be used for variable amounts of plaintext input of length greater than 0, as long as std::string can handle that input. The program will account for odd numbered inputs (by placing a 0 prior to the last character) and strings less than 32 characters by appending 0s to them until it is 32 characters.

## What It **Doesn't** Do
- Anything else
