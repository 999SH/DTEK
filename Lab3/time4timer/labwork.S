  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
.globl time2string
.globl delay



.text


time2string:

PUSH $ra
nop
PUSH $s0
nop

move $s0, $a0

#Byte 0
andi $a0, $a1, 0xF000   # Mask 1111 0000 0000 0000
srl  $a0, $a0, 12       #Shift t0 right in order to get byte into LSB scope for hexasc
jal hexasc
nop
sb $v0,0($s0)           #Store byte


#Byte 1
andi $a0, $a1, 0x0F00 # Mask 0000 1111 0000 0000
srl  $a0, $a0,  8     #Shift t0 right in order to get byte into LSB scope for hexasc
jal hexasc
nop
sb $v0,1($s0)         #Store byte


#Colon
li $a0, 0x3A
sb $a0,2($s0)         #Store byte


#Byte 2
andi $a0, $a1, 0x00F0 # Mask  0000 0000 1111 0000
srl  $a0, $a0, 4      #Shift t0 right in order to get byte into LSB scope for hexasc
jal hexasc
nop
sb $v0,3($s0)         #Store byte


#Byte 3
andi $a0, $a1, 0x000F # Mask  0000 0000 0000 1111
srl  $a0, $a0, 0      #Shift t0 right in order to get byte into LSB scope for hexasc
jal hexasc
nop
sb $v0,4($s0)         #Store byte

#NULL byte
li $a0, 0x00
sb $a0,5($s0)         #Store byte


POP $s0
nop 

POP $ra
nop

jr $ra
nop

hexasc:
	andi $v0, $a0, 0xF    # 0x30 = 0 || 0x39 = 9. 0x41 A || 0x46 = F
  bge $v0, 0xA, large
  nop
  addi $v0, $v0, 0x30

  j return
  nop

large:
       addi $v0, $v0, 0x37

return:
       jr $ra
       nop

#improved delay
#DELAY CONSTANT
delay:
PUSH $ra
nop    
 
while:
	blez $a0, delayreturn 
	nop
	addi $a0, $a0, -1
  add $t1, $0, $0    

for:
     addi $t1, $t1, 1
     bge $t1, 4711, while
     nop     
     j for
     nop  
     
delayreturn:
	POP $ra
	nop
  jr $ra
  nop                             

#Stop just because

     stop: j stop
      nop  
