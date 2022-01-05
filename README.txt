# Progetto Laboratorio di programmazione:  Scacchiera-elettronica
Gruppo formato da:
  Nicola Busato   2009663
  Riccardo Miele  2008594
  
  
  
Note programma
 * Main         (Nicola Busato 2009663)
   - Ho aggiunto l'argomento argomento riga di comando "PP" per partite Player vs Player, usato per il debug
   - Oltre ai comandi per lo spostamento "A1 H8" e "XX XX" ho aggiunto "clear" e "patta" (case insensitive) rispettivamente per ripulire la console e per fare la patta
   - Ci sono due metodi print_green, print_red che funzionano solo con linux per stampare in verde o in rosso
 * Chessboard   (Nicola Busato 2009663)
   - Abbiamo deciso di gestire la scacchiera come matrice (8x8) di Piece
   - Il random move cattura le eccezioni Arrocco e Promotion che contengono al loro interno un pair(y,x) delle coordinate di arrivo del random move, queste vengono convertite in stringa valida per il metodo move di chessboard e successivamente salvate nel file di log.  
 *
 
 *
 
-non funziona l'arrocco (dovrebbe essere sistemato)
-l'alfiere non si puo' muovere più di una casella all'inizio della partita (risolto)
-durante l'arrocco il re non può passare nelle posizioni di scacco (Fatto ma non testato)
