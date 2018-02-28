# CSE 178: Computers and Network Security

## About
This repository contains the AES-128 project that was done for my Network Security class, implemented in C++.

## What It Does
- Takes a hexadecimal string from the user
  - Known as plaintext
  - Example: *1f2e3d4c5b6a79*
- Takes another hexadecimal string from the user, maximum 32 characters (as it has to be a 128-bit key)
  - The key used for encrypting the plaintext input
- Performs the AES-128 encryption algorithm on that input, in 32 character/128-bit chunks
- Outputs the input, encrypted
  - Known as ciphertext

- Can be used for variable amounts of plaintext input of length greater than 0, as long as std::string can handle that input. The program will account for odd numbered inputs (by placing a 0 prior to the last character) and strings less than 32 characters by appending 0s to them until it is 32 characters.

## What It **Doesn't** Do
- Anything else

## Examples
### Example 1: Plaintext < 32 characters, Key contains exactly 32 characters
    Enter hexadecimal-based plaintext (i.e., 0x1f, 0x2f is inputted as 1f2f): 1f2e3d4c5b6a79
    Enter key in a similar way as above: 1f2f3f4f5f6f7f8f9fafbfcfdfefff

    Key before conversion: 1f2f3f4f5f6f7f8f9fafbfcfdfefff (string)

    Key after conversion (from string to int):
    1f 5f 9f df
    2f 6f af ef
    3f 7f bf ff
    4f 8f cf 00

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    Plaintext before conversion: 1f2e3d4c5b6a79 (string)

    Plaintext after conversion (from string to int):
    1f 5b 00 00
    2e 6a 00 00
    3d 79 00 00
    4c 00 00 00

    4x4 Matrix Ciphertext:
    ee 2a d7 e0
    f5 fe cb 54
    55 46 b2 f4
    14 bb b7 c5

    Inline Ciphertext: eef555142afe46bbd7cbb2b7e054f4c5

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    The combined ciphertext: ee f5 55 14 2a fe 46 bb d7 cb b2 b7 e0 54 f4 c5

### Example 2: Neither plaintext nor key contain >= 32 characters
    Enter hexadecimal-based plaintext (i.e., 0x1f, 0x2f is inputted as 1f2f): 1f2f3f
    Enter key in a similar way as above: 999999

    Key before conversion: 999999 (string)

    Key after conversion (from string to int):
    99 00 00 00
    99 00 00 00
    99 00 00 00
    00 00 00 00

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    Plaintext before conversion: 1f2f3f (string)

    Plaintext after conversion (from string to int):
    1f 00 00 00
    2f 00 00 00
    3f 00 00 00
    00 00 00 00

    4x4 Matrix Ciphertext:
    84 f9 01 b1
    3f 42 d1 f3
    1e fa c2 cb
    f1 1b 64 2d

    Inline Ciphertext: 843f1ef1f942fa1b01d1c264b1f3cb2d

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    The combined ciphertext: 84 3f 1e f1 f9 42 fa 1b 01 d1 c2 64 b1 f3 cb 2d

## Example 3: Plaintext contains > 32 characters
    Enter hexadecimal-based plaintext (i.e., 0x1f, 0x2f is inputted as 1f2f): ffeeddccbbaa9988776655443322111f2f3f4f5f6f7f8f9fafbfcfdfefff
    Enter key in a similar way as above: 112233445566778899aabbccddeeff

    Key before conversion: 112233445566778899aabbccddeeff (string)

    Key after conversion (from string to int):
    11 55 99 dd
    22 66 aa ee
    33 77 bb ff
    44 88 cc 00

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    Plaintext before conversion: ffeeddccbbaa9988776655443322111f (string)

    Plaintext after conversion (from string to int):
    ff bb 77 33
    ee aa 66 22
    dd 99 55 11
    cc 88 44 1f

    4x4 Matrix Ciphertext:
    ee 3e 80 b3
    f3 63 d3 a5
    7e 4a a0 39
    b2 77 77 26

    Inline Ciphertext: eef37eb23e634a7780d3a077b3a53926

    ---------------------------------------------------------------------------------------------------------

    Plaintext before conversion: 2f3f4f5f6f7f8f9fafbfcfdfefff (string)

    Plaintext after conversion (from string to int):
    2f 6f af ef
    3f 7f bf ff
    4f 8f cf 00
    5f 9f df 00

    4x4 Matrix Ciphertext:
    35 a0 63 f6
    6f 43 f0 2e
    83 67 72 c8
    fb 37 e5 ba

    Inline Ciphertext: 356f83fba043673763f072e5f62ec8ba

    ---------------------------------------------------------------------------------------------------------
    ---------------------------------------------------------------------------------------------------------

    The combined ciphertext: ee f3 7e b2 3e 63 4a 77 80 d3 a0 77 b3 a5 39 26 35 6f 83 fb a0 43 67 37 63 f0 72 e5 f6 2e c8 ba
