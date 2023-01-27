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

#Byte 0
andi $t0, $a1, 0xF000   # Mask 1111 0000 0000 0000
srl  $t0, $t0, 12       #Shift t0 right in order to get byte into LSB scope for hexasc
move $v0, $t0           #move result into v0
jal hexasc
nop
sb $v0,0($a0)           #Store byte


#Byte 1
andi $t0, $a1, 0x0F00 # Mask 0000 1111 0000 0000
srl  $t0, $t0,  8     #Shift t0 right in order to get byte into LSB scope for hexasc
move $v0, $t0         #move result into v0
jal hexasc
nop
sb $v0,1($a0)         #Store byte


#Colon
li $t0, 0x3A
sb $t0,2($a0)         #Store byte


#Byte 2
andi $t0, $a1, 0x00F0 # Mask  0000 0000 1111 0000
srl  $t0, $t0, 4      #Shift t0 right in order to get byte into LSB scope for hexasc
move $v0, $t0         #move result into v0
jal hexasc
nop
sb $v0,3($a0)         #Store byte


#Byte 3
andi $t0, $a1, 0x000F # Mask  0000 0000 0000 1111
srl  $t0, $t0, 0      #Shift t0 right in order to get byte into LSB scope for hexasc
move $v0, $t0         #move result into v0
jal hexasc
nop
sb $v0,4($a0)         #Store byte

#NULL byte
li $t0, 0x00
sb $t0,5($a0)         #Store byte

POP $ra
nop

#hexasc
hexasc:
        move	$t0 ,$v0    # 0x30 = 0 ||A�0x39 = 9. 0x41 A || 0x46 = F
        bge $t0, 0xA, large
        nop
        addi $t0, $t0, 0x30

        j return
        nop

large:
       addi $t0, $t0, 0x37

return:
       move $v0, $t0
       jr $ra
       nop

#improved delay
#DELAY CONSTANT


delay:
add $t1, $0, $0
li $t0, 1000   #this is MS 
delayloop:
     beqz $t0,delayreturn 
     nop
     addi $t0, $t0, -1     
for:
     addi $t1, $t1, 1
     bge $t1, 2700000, delayloop #Constant
     nop
     j for
     nop  
     
delayreturn:
            jr $ra   
            nop                          

#Stop just because

     stop: j stop
      nop  