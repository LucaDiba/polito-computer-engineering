		.data
 op1:	.byte 150
 op2:	.byte 100

		.text
		.globl main
		.ent main
main:	lb $t0, op1
		lb $t1, op2
    	add $a0, $t0, $t1
		li $v0, 1
		syscall
		li $v0, 10
		syscall
		.end main