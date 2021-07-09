;--------------------------------------------------------
; Demonstriert die Schleifenbildung mit Hilfe von ISZ
;--------------------------------------------------------
  fim R0R1,200	;Register R0/R1 mit 200 laden
		;Rechnung 256 - 200 = 56 (0x38) Loops
  fim R2R3,0	;Zaehler wieviel Loops gemacht werden

Loop

  clc		;Carry loeschen
  ldm 1		;Akku auf 1
  add R3	;Wert von R3 mit Akku addieren
  xch R3	;Wert von Akku in R3
  tcc		;Carry in Akku schreiben, Carry loeschen
  add R2	;Wert von R3 mit Akku addieren
  xch R2	;Wert von Akku in R2

  isz R1,Loop	;Loop Low Byte
  isz R0,Loop	;Loop High Byte

End
  jun End	;Spring endlos zu End
.end

