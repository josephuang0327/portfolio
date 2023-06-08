# Name : Wei Chieh Huang
# Class ID : 792
# Assignment Number : 3
.data 
.word 0 
.word 0 
.word 0
.word 0
.globl main 
.text 
main:
# Above was given

addi $v0,$0,5	# Command to read a number
syscall		# execute
lui $t0,0x1001	# load s1 with address 0x10010000
sw $v0,($t0)	# store the word of the input from v0 to - 0x10010000
add $s0,$v0,$0	# put the value to s0

addi $v0,$0,5	# Command to read another number
syscall		# execute
sw $v0,4($t0)	# store the word of the input from v0 to - 0x10010004
add $s1,$v0,$0	# put the value to s1

slt $t1,$s1,$s0	# if true t1 = 1 , if not true t1 = 0
beq $t1,$0,else	# check if the first input is greater than second input, if not jump to else

# t1 = 1, s0 is greater than s1
sw $s0,8($t0)	# store value of s0 to 0x10010008
sw $s1,12($t0)	# store value of s1 to 0x10001000C
j endIf		# jump to endif

# t1 = 0, s1 is greater than s0
else:
sw $s1,8($t0)	# store value of s1 to 0x10010008
sw $s0,12($t0)	# store value of s0 to 0x10001000C

endIf:
addi $v0,$0,10	# command to end program
syscall		# end program

