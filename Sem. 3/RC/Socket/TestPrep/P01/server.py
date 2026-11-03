# Clientul alege un port UDP liber pe calculatorul său, creează un socket UDP și îl leagă la portul ales. Apoi se conectează prin TCP la server și îi transmite numărul portului.
# Serverul creează un socket UDP pentru sesiunea curentă și încearcă să îl lege la același număr de port, pe propria adresă IP. Serverul confirmă prin TCP dacă portul este disponibil. Dacă portul este ocupat, clientul poate alege altul. După confirmare, conexiunea TCP se închide.
# Clientul trimite la adresa IP a serverului, pe portul confirmat, o singură datagramă care conține numărul de elemente și șirul de cel mult 100 de numere întregi.
# Serverul calculează suma numerelor prime din șir și o trimite de pe același socket UDP la adresa IP a clientului, pe același număr de port. Dacă șirul nu conține numere prime, serverul trimite 0. Clientul primește și afișează rezultatul.
# Serverul deservește clienții pe rând. După ce trimite rezultatul, închide socketul UDP al sesiunii și revine la accept() pentru a prelua următorul client.

