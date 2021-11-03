.section .text.boot
.global _start

_start:
	# TODO: We'll need a trap vector to handle trap

	# For the hart that id != 0, hanging in a infinite for loop
	csrr	t0, mhartid
	bnez	t0, 3f
	
        # .bss section is reset to be zero
	la 	a0, _bss_start
	la	a1, _bss_end
	bgeu	a0, a1, 2f
1:
	sd	zero, (a0)
	addi	a0, a0, 8
	bltu	a0, a1, 1b

2:   
        la      sp, _stack_end
 
	j	lib_main

3:
	wfi
	j	3b
