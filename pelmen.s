.name "Decomposing Pelmen"
.comment "We want to validate this project"
	
    sti     r1, %:live, %1
    sti     r1, %:live2, %1
    ld      %1, r3
    ld      %33, r6

forks:
    add     r2, r3, r2
    add     r4, r5, r8
    xor     r2, %15, r4
live2:
	live 	%4
    zjmp	%:endwhile
    fork	%:forks
    zjmp	%:forks
    live    %4

endwhile:
    ld      %0, r4
live:
    live    %4
    zjmp    %:live
live3:
    live    %2
    zjmp    %:live
