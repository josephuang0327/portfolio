.data
.asciiz "Hello World"
.text

main:
lui $a0,0x1001
addi $v0,$0,4
syscall
addi $v0,$0,10
syscall