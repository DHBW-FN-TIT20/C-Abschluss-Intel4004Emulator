;--------------------------------------------------------
; Demonstriert die Schleifenbildung anhand eines Textes
;--------------------------------------------------------
  fim R2R3,LHello	;Laenge in R3, Offset in R2

LoopTxt
  fim R0R1,Hello	;Pointer auf Hello
  ld R1	;Low Adresse in Akku
  add R2	;Speicherzaehler
  xch R1
  fin 0		;Aus ROM-Speicherzelle indirect lesen
		;Ptr steht in R0R1, Ergebnis wird in R0R1
		;geschrieben

  ;Hier muesste jetzt die Verarbeitung der ASCII
  ;Zeichen erfolgen

  inc R2	;Erhoehe Adresse Rom
  isz R3, LoopTxt	;Loop solange R2 nicht 0  
End
  jun End	;Spring endlos zu End
;--------------------------------------------------------
*=32		;Gerade Adresse ist von Vorteil
Hello		;Hello World 
   .byte $48	;'H'
   .byte $65	;'e'
   .byte $6C	;'l'
   .byte $6C	;'l'
   .byte $6F	;'o'
   .byte $20	;' '
   .byte $57	;'W'
   .byte $6F	;'o'
   .byte $72	;'r'
   .byte $6C	;'l'
   .byte $64	;'d'

LHello=5	;Anzeil Zeichen in String Hello (ISZ)
;--------------------------------------------------------
.end
;--------------------------------------------------------

