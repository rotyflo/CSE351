#include <stdio.h>

// Returns the binary value (ie, 1 or 0) of the n-th least significant bit.
// Assumes n will always be between 0-31.
char ReadBitN(int x, unsigned char n) {
  // shift x to the right n times
  // and return the value of the LSB
  return (x >> n) & 1;
}

// Sets the binary value of bits 4 and 5 in the passed-in bt to the values passed in
// as four and five respectively. Assume four and five are set to either 0 or 1.
char SetBits45(unsigned char bt, char four, char five) {
  return (bt & 0xCF) | (four << 4) | (five << 5);
}

int main() {
  printf("ReadBitN(0b10011011, 3) -> %d\n", ReadBitN(0b10011011, 3));    
  printf("SetBits45(0b00000101, 1, 1) -> %d\n", SetBits45(0b00000101, 1, 1));

  return 0;
}
