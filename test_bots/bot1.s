.name		"Sonofabitch"
.comment	"You piece of shit!"

live 	%-1
aff		r1
ld		%-32, r2
st		r2, 256
ld		%-32, r3
st		r3, 256
ldi		%16777216, %0, r4
add		r2, r3, r10
sub		r2, r4, r9
st		r4, 128
sti 	r4, 128, %82739299
lld		%82739299, r4
st		r4, 128
ldi		%-32, %5, r8
fork	%-64
