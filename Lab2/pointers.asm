
# pointers.asm
# By David Broman, 2015-09-14
# This file is in the public domain


.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

.data


text1: 	  .asciiz "This is a string."
text2:	  .asciiz "Yet another thing."

.align 2
list1: 	.space 80
list2: 	.space 80
count:	.word  0

.text
main:
	jal	work
stop:	j	stop

# function work()
work:
	PUSH	($ra)
	la 	$a0,text1 # load adress of text 1 into argument
	la	$a1,list1 # load adress of list 1 into argument
	la	$a2,count # load adress of count into argument
	jal	copycodes # Copies text 1 into list1 and adds ascii numbering
	
	la 	$a0,text2 # 
	la	$a1,list2 # 
	la	$a2,count #
	jal	copycodes #
	POP	($ra)
	
	
# function copycodes()
copycodes:
loop:
	lb	$t0,0($a0)  # load "textx" adress into t0	
	beq	$t0,$0,done # if list is empty, go to done
	sw	$t0,0($a1)  # store "textx" into a1. 

	addi	$a0,$a0,1   # text1/2 = textx + 1. Used to increment string
	addi	$a1,$a1,4   # text1/2 = textx + 4. Used to increment ?
	
	lw	$t1,0($a2)  #  
	addi	$t1,$t1,1   #  count = count + 1;
	sw	$t1,0($a2)  #
	j	loop
done:
	jr	$ra
		



