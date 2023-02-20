.text

addi $a0,$0, 1     #set n
add $v0 $0, $0	   #Clear v0



addi $v0,$0, 1

beq $a0, $0, stop #beq if n = 0 0! = 1
add $0,$0,$0	   # NOP

addi  $v1, $0, 1   #Increment v1 counter. v1 = current n

beq $a0, $v0, stop #beq if n = 1
add $0,$0,$0	   # NOP



loop:
addi  $v1, $v1, 1   #Increment v1 counter. v1 = current n
mul $v0, $v1, $v0   #v0 * v1


beq $a0, $v1, stop       #Check if currentnumber has done n additions in run n
add $0,$0,$0	   # NOP	
	
beq $0,$0, loop   #unconditional jump if not done
add $0,$0,$0	   # NOP

stop: 
add  $0,$0,$0	  # NOP
beq $0, $0, stop #beq if done 
add  $0,$0,$0	   # NOP	
