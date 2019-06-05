.name		"Sonofabitch"
.comment	"You piece of shit!"

live 	%-1
aff		r1
ld		%-32, r2
st		r2, 256
ld		%-32, r3
st		r3, 256
ldi		%16777216, %0, r4
st		r4, 128
sti 	r4, 128, %82739299
lld		%82739299, r4
st		r4, 128
fork	%-64
