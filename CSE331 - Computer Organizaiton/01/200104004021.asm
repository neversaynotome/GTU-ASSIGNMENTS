.data
    myarray:.space 400
    st:.asciiz "Enter the N: "
	nd:.asciiz "Enter the K: "
	er:.asciiz "Invalid Input!\n"
	rd:.asciiz "Enter the elements:\n"
	ls:.asciiz "Number of adequate pairs: "
.text    
	input:
    li $v0,4
    la $a0,st
    syscall
	li $v0,5
    syscall
    move $s0,$v0 	# N is stored in $s0
    li $v0,4
    la $a0,nd
    syscall
	li $v0,5
    syscall
    move $s1,$v0 	# K is stored in $s1
    bgt $s0,100,error
    blt $s0,2,error
  	bgt $s1,100,error
    blt $s1,1,error
    jal fill 
    jal divisibleSumPairs
    li $v0,10
    syscall
    error:
    li $v0,4
    la $a0,er
    syscall
    j input

fill:        
    li $v0,4
    la $a0,rd
    syscall
    size:
    beq $s0,$t2,get
    add $t2,$t2,1
    add $t1, $t1,4
    j size
    get:
    beq $t0,$t1,exitf
    li $v0,5
    syscall
    sw $v0,myarray($t0)
    add $t0,$t0,4
    j get

exitf:
    jr $ra
    
    divisibleSumPairs:
    addi $t5,$t4,1 #index+1 j
    addi $t6,$t3,4 #address+1 to compare j address
    inner: #get the rest of the elements w/o out of bounds
	    bge $t5,$s0,cont     	# t5 <= s0
	    lw $s2,myarray($t3) # outer element i
	    lw $s3,myarray($t6) # inner element j
	    add $t9,$s2,$s3 # t9 holds the sum
	    div $t9,$s1 # division of the sum
	    mfhi $s5 # remainder
	    
	    bne $s5,$zero,nInc # t3 + $t3+count % s1 == 0 then count
	    addi $s6,$s6,1 # count++
	    nInc: 
	add $t5,$t5,1
    add $t6,$t6,4
    ble $t5,$s0,inner
    cont:
    add $t4,$t4,1 #index
    add $t3, $t3,4 #address to compare
	ble $t4,$s0,divisibleSumPairs
	
	li $v0,4 # print the 
    la $a0,ls
    syscall
    li $v0,1
    move $a0,$s6
    syscall
exit:
    jr $ra
