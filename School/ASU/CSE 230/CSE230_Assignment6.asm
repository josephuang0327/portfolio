# Name : WeiChieh Huang
# Class ID : 792
# Assignment Number : 6
.data
str1: .asciiz "WeiChieh Huang\n"
str2: .asciiz "Enter a number "
space: .asciiz "\n"
.globl main
.text

main:
lui $a0, 0x1001		# load string 1 to a0
addi $v0,$0,4		# command to print string (name)
syscall			# execute

add $t1,$0,$0		# set counter2 = 0

startLoop1:
add $t0,$0,$0		# set counter1 = 0
add $s0,$0,$0		# set sum = 0

startLoop2:
lui $a0,0x1001		# load upper address
addi $a0,$a0,16		# load string 2 to a0
addi $v0,$0,4		# command to print string
syscall			# execute

addi $v0,$0,5		# read integer
syscall			# execute

add $s0,$s0,$v0		# sum if input
addi $t0,$t0,1		# counter1++
bne $t0,5,startLoop2	# loop back
endLoop2:

add $a0,$0,$s0		# a0 = sum
addi $v0,$0,1		# command to print integer
syscall			# execute

lui $a0,0x1001		# print newline
addi $a0,$a0,32		# print newline
addi $v0,$0,4		# command to print string
syscall			# execute


div $a0,$s0,$t0		# sum divide by counter
addi $v0,$0,1		# command to print integer
syscall			# call print command

mtc1 $s0,$f0		# convert sum from int to float
mtc1 $t0,$f1		# convert counter from int to float
cvt.s.w $f0,$f0		# conver sum to single digit
cvt.s.w $f1,$f1		# conver counter to single digit

lui $a0,0x1001		# print newline
addi $a0,$a0,32		# print newline
addi $v0,$0,4		# command to print string
syscall			# execute

div.s $f12,$f0,$f1	# divide float of sum and counter
addi $v0,$0,2		# command to print float
syscall			# execute

lui $a0,0x1001		# print newline
addi $a0,$a0,32		# print newline
addi $v0,$0,4		# command to print string
syscall			# execute

addi $t1,$t1,1		# counter2++
bne $t1,3,startLoop1	# loop back
endLoop1:

addi $v0,$0,10		# command to end
syscall			# execute
















