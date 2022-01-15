# Progetto Laboratorio di programmazione:  Scacchiera-elettronica
Gruppo formato da:
  Nicola Busato   2009663
  Riccardo Miele  2008594
  Martino Scagnet 2000134
  
Note generali
  Dopo ogni spostamento dei pezzi viene eseguito un controllo per verificare se il re del giocatore che ha mosso non sia sotto scacco a causa della sua mossa, 
  se ciò avviene la mossa viene bloccata e si ritorna alla situazione iniziale chiedendo al giocatore una nuova mossa; 
  questo è utilizzato anche con le mosse generate dal computer che quindi sono (un po') piu' intelligenti.
  In alcuni casi durante le partite computer vs computer in caso di scacco la mossa ci impiega più tempo a generarsi perchè il random deve creare uno spostamento che bocchi lo scacco.
  
  Vengono controllati tutti i tipi di scacco/scacco matto e patta.
  
  La scacchiera permette l'arrocco (con controllo dello scacco del re durante il movimento d'arrocco), la promozione (il computer decide randomicamente il pezzo a cui promuovere) e l'en passant.
  
  
  
  
Note Codice
 * Scacchiera.cpp   (Nicola Busato 2009663)
   - Ho aggiunto l'argomento argomento riga di comando "PP" (case insensitive) per partite Player vs Player, usato per il debug
   - Oltre ai comandi per lo spostamento "A1 H8" e "XX XX" ho aggiunto "clear" e "patta" (case insensitive) rispettivamente per ripulire la console e per fare la patta
   - Ci sono due metodi print_green, print_red che funzionano solo con linux per stampare in verde o in rosso (uso estetici)
   
 * Chessboard.cpp   (Nicola Busato 2009663)
   - abbiamo deciso di realizzare la scacchiera come matrice (8x8) di puntatori di Piece
   - Il random move cattura le eccezioni Arrocco e Promotion che contengono al loro interno un pair(y,x) delle coordinate di arrivo del random move, queste vengono convertite in stringa valida per il metodo move di chessboard e successivamente salvate nel file di log.  
   La promozione genera una riga di codice formata da [stringa mossa normale] + " " + lettera_pezzo es "A7 A8 d"
   - il metodo move è utilizzato sia da Scacchiera.cpp che replay.cpp e restituisce un intero che rappresenta il tipo di errore
   
 * Replay.cpp       (Nicola Busato 2009663)
   - E' come se fosse una partita tra due giocatori, con la differenza che le mosse sono lette da file, quindi ci sono tutti i controlli di una partita normale ma con la stampa ad ogni mossa, inoltre se c'e' presente una mossa non valida nei file di log il replay viene interrotto 
 
 *Rules.cpp      (Martino Scagnet 2000134)
  -Il rilevamento dello scacco si differenzia in due casi: Controllo se l'avversario mi ha fatto scacco e controllo di non essermi fatto scacco da solo. 
	Nel primo caso il rilevamento di uno scacco si basa sull'ultima mossa eseguita (o il pezzo mosso minaccia il re o ha scoperto la traiettoria ad un pezzo che potrebbe minacciarlo), se rilevato uno scacco, viene invocato il controllo dello scaccomatto in base al numero di minacce rilevate. 
	(Se sono due non è scaccomatto solo se il re si può muovere, se è una è possibile difendere catturando la minaccia o occupando la traiettoria)
	Nel secondo caso controllo se il re del giocatore che ha mosso è minacciato da ogni direzione, 
	controllo inoltre che non vi siano cavalli che lo possano catturare.
-La patta rileva ed identifica tutti i casi: Materiale insufficiente, stessa posizione ripetuta 3 volte, 50 mosse senza catture o movimenti di pedone, stallo (il giocatore di cui è il turno non ha mosse valide disponibili). Nel caso venga rilevato uno dei casi la partita termina automaticamente in patta.
 
