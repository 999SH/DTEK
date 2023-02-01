  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr  #load timestr adress into a0 
	li	$v0,4       #Load Print string for syscall 
	syscall
	nop
	# wait a little 
	li	$a0,2      #Load 2 into a0. Used for delay
	jal	delay     
	nop
	# call tick
	la	$a0,mytime #Load adress of mytime into a0 
	jal	tick       #Tick time
	nop
	# call your function time2string
	la	$a0,timstr  #Load adress of timestr into a0 
	la	$t0,mytime  #Load adress of mytime into t0
	lw	$a1,0($t0)  #Dereference t0 and load into a1
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
	
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
	
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #


              
                     
time2string:

PUSH ($ra)
nop
PUSH ($s0)
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


#SURPRISE ASSIGNMENT
lw $t0, 0($s0)
li $t1, 0x303a3030
bne $t0, $t1, skipding
nop

lb $t0, 4($s0)
li $t1, 0x30
bne $t0, $t1, skipding
nop

li $t0, 0x474E4944
sw $t0, 0($s0)

li $v0, 0x00
sb $v0,4($s0)         #Store byte

#________________________
	
skipding:

POP ($s0)
nop

POP ($ra)
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
delay:
PUSH ($ra)
nop
add $t1, $0, $0    #Reset t0

while:
     blez $a0, delayreturn    #If while loop is done
     nop
     addi $a0, $a0, -1        #Decrement ms
for:
     addi $t1, $t1, 1         #Increase i 
     bge $t1, 2000, while      #constant
     nop     
     j for
     nop  
     
delayreturn:
	POP ($ra)
	nop
        jr $ra
        nop                             

#Stop just because 
stop: j stop
      nop


