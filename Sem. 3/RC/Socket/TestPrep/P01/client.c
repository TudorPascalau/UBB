// Un client trimite serverului un șir de numere întregi. Serverul îi returnează suma numerelor prime din șir. Comunicarea se desfășoară astfel:
// Clientul creează un socket UDP, apoi se conectează prin TCP la server și îi trimite portul UDP pe care așteaptă răspunsuri.
// Serverul îi transmite prin TCP portul propriului socket UDP. Adresele IP se determină din conexiunea TCP.
// Clientul trimite prin UDP o datagramă care conține numărul de elemente și șirul de numere, de lungime cel mult 100.
// Serverul calculează suma numerelor prime și trimite rezultatul prin UDP la adresa IP a clientului și portul comunicat la pasul 1. Dacă șirul nu conține numere prime, rezultatul este 0.
// Clientul afișează rezultatul și trimite prin TCP mesajul STOP, după care ambele părți închid socketurile asociate sesiunii.