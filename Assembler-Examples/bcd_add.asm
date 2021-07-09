;--------------------------------------------------------
; Beispiel fuer eine BCD-Addition
;--------------------------------------------------------
  				;BCD und HEX teilen sich die Zahlen
  FIM R0R1,$29	;BCD 29
  FIM R2R3,$61	;BCD 61
  FIM R4R5,$00	;Ergebnis
  
  CLC					;Loesche Carry
  
  LD R1					;Register R1 in Akku
  ADD R3				;Addiere Summe R1/R3 + Carry
  DAA					;BCD Korrektur (Carry beruecksichtigen)
  XCH R5				;Ergebnis in Register R5 (Low)

  LD R0					;Register R0 in Akku
  ADD R2				;Addiere R0 und R2 incl. Carry
  DAA					;BCD Korrektur (Carry beruecksichtigen)
  XCH R4				;Ergebnis in Register R4 (High)
  
  ;Wenn jetzt alles funktioniert hat steht das Ergebnis
  ;in R4R5
  
