# Name : Wei Chieh Huang
# Class ID : 792
# Assignment Number : 4

.data				# add any strings at this point as needed
.text
.globl main

main:
addi $a0,$a0,0			# set a0 = 0
jal getsum			# call function to print sum of input
ori $a0, $v0, 0			# copy sum to $a0
ori $v0, $0, 1			# set output command
syscall				# execute to end


end:   
ori $v0, $0, 10			# set command to stop program
syscall				# end program


getsum:				# get sum func
addi $v0,$0,5			# command to read input
syscall				# execute
slti $t1,$v0,0			# if input less than zero return 1 else 0
beq $t1,1,endsum		# if input is negative jump to the end
j isodd				# call isodd: function to check if input is odd

finishCheck:			# when finish checking jump to this place
bne $t0,0,getsum		# if is not even jump back to getsum
add $a0,$a0,$v0			# add input to a0 if is even and not negative number
j getsum			# use jump instead of jal because it will mess up the jal from main function

endsum:				# to end the sum function
add $v0,$a0,$0			# put the result in v0 since the given code in main: will copy the number over
jr $ra				# return to the main function

isodd:
andi $t0,$v0,0x1		# compare the input to 0x1 so it will be 0 when even, and 1 when odd
j finishCheck			# use jump instead of jr $ra beacause it prevent it to jump back to main: function




