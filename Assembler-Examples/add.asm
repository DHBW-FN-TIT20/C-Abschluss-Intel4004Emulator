;--------------------------------------------------------
; Beispiel fuer eine Binaer-Addition
;--------------------------------------------------------
  FIM R0R1,15	;15
  FIM R2R3,101	;101
  FIM R4R5,$00	;Ergebnis
  
  CLC						;Loesche Carry
  
  LD R1					;Register R1 in Akku
  ADD R3				;Addiere Summe R1/R3 + Carry
  XCH R5				;Ergebnis in Register R5 (Low)

  LD R0					;Register R0 in Akku
  ADD R2				;Addiere R0 und R2 incl. Carry
  XCH R4				;Ergebnis in Register R4 (High)
  
  ;Wenn jetzt alles funktioniert hat steht 
  ;das Ergebnis 116 (0x74) in R4R5
  
