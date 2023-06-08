# Wei Chieh Huang
# ASUID:1215427213
# Assignment2
.data 
.globl main 
.text 
main:
addi $s0,$zero,15	#set s0 = 15
addi $s1,$zero,-4	#set s1 = -4
addi $v0,$zero,5	#command to read int input
syscall			#execute
addi $s2,$v0,0		#set s2 = input
sub $s3,$s1,$s0		#set s3 = s1-s0 = -4 -15 = -19
add $s3,$s3,$s2		# s3 = s3+s2 = -19+input
add $s4,$s3,$s2		#set s4 = s3+s2
addi $s4,$s4,-7		# s4 = s4-7
addi $s5,$s1,20		#set s5 = -4+20 = 16
sub $s5,$s5,$s2		# s5 = s5-input
add $t0,$s0,$zero	#set t0 = s0
add $s0,$s1,$zero	#s0 copy s1
add $s1,$t0,$zero	#s1 copy t0
add $t1,$s2,$zero	#set t1 = s2
sub $s2,$s2,$t1		# s2 - t1 = 0
sub $s2,$s2,$t1		# s2 - t1 = -s2

addi $v0,$zero,1	#command to print
add $a0,$s0,$zero	# print s0
syscall			#execute

addi $v0,$zero,1	#command to print
add $a0,$s1,$zero	# print s1
syscall			#execute

addi $v0,$zero,1	#command to print
add $a0,$s2,$zero	# print s2
syscall			#execute

addi $v0,$zero,1	#command to print
add $a0,$s3,$zero	# print s3
syscall			#execute

addi $v0,$zero,1	#command to print
add $a0,$s4,$zero	# print s4
syscall			#execute

addi $v0,$zero,1	#command to print
add $a0,$s5,$zero	# print s5
syscall			#execute

addi $v0,$zero,10	#command to stop
syscall			#execute

