.text

addi $a0,$0, 5     #set n
addi $v0 $0, 1	   #Clear #Set v0 to 1 since it doesnt work otherwise

beq $a0, $0, stop #beq if n = 0
add $0,$0,$0	   # NOP

beq $a0, $v0, stop #beq if n = 1
add $0,$0,$0	   # NOP

loop:
addi  $v1, $v1, 1   #Increment v1 counter
addi  $a1, $0, 0     #Load/Clear a1 
addi  $a2, $0, 0     #Load/Clear a2 

	currentnumber:
	add $a2, $a2, $v0   #v0 * v1
	addi $a1 $a1, 1    #Increment a1 counter
	
	beq $a1, $v1, donecheck       #Check if currentnumber has done n additions in run n
	add $0,$0,$0	   # NOP	
	
	beq $0,$0, currentnumber   #unconditional jump if not done
	add $0,$0,$0	   # NOP



donecheck:
addi  $v0, $a2, 0  #Load v0 since its going to loop or be done, v0 is used for the next multiplication
beq $a0, $v1, stop #beq if done 
add $0,$0,$0	   # NOP
beq $0,$0, loop    #unconditional jump if not done
add $0,$0,$0	   # NOP

stop: 
add  $0,$0,$0	  # NOP
beq $0, $0, stop #beq if done 
add  $0,$0,$0	   # NOP	
