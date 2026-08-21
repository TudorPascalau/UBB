#include "UI.h"

#include <iostream>
using std::cin;
using std::cout;
using std::getline;

void UI::printMenu() const {
	cout << "\n===== MENIU BIBLIOTECA =====\n";
	cout << "1. Adauga carte\n";
	cout << "2. Sterge carte\n";
	cout << "3. Modifica carte\n";
	cout << "4. Cauta carte dupa id\n";
	cout << "5. Afiseaza toate cartile\n";
	cout << "6. Adauga sample data\n";
	cout << "7. Sorteaza dupa titlu\n";
	cout << "8. Sorteaza dupa autor\n";
	cout << "9. Sorteaza dupa an + gen\n";
	cout << "10. Filtreaza dupa titlu\n";
	cout << "11. Filtreaza dupa an\n";
	cout << "12. Adauga carte in cos dupa titlu\n";
	cout << "13. Goleste cosul\n";
	cout << "14. Genereaza cos\n";
	cout << "15. Exporta cos in CSV\n";
	cout << "16. Raport genuri\n";
	cout << "0. Iesire din aplicatie\n";
	cout << ">>> ";
}

void UI::addSampleData() {
	try {
		srv.addCarte(1, "1984", "George Orwell", "distopie", 1949);
		srv.addCarte(2, "To Kill a Mockingbird", "Harper Lee", "roman", 1960);
		srv.addCarte(3, "The Great Gatsby", "F. Scott Fitzgerald", "roman", 1925);
		srv.addCarte(4, "Moby Dick", "Herman Melville", "aventura", 1851);
		srv.addCarte(5, "War and Peace", "Leo Tolstoy", "istoric", 1869);
		srv.addCarte(6, "Pride and Prejudice", "Jane Austen", "roman", 1813);
		srv.addCarte(7, "The Hobbit", "J.R.R. Tolkien", "fantasy", 1937);
		srv.addCarte(8, "Crime and Punishment", "Fyodor Dostoevsky", "psihologic", 1866);
		srv.addCarte(9, "Brave New World", "Aldous Huxley", "distopie", 1932);
		srv.addCarte(10, "The Catcher in the Rye", "J.D. Salinger", "roman", 1951);

		cout << "Date sample adaugate cu succes.\n";
	}
	catch (const ValidationError& e) {
		cout << e.getMessage();
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::printCarte(const Carte& c) const {
	cout << "ID: " << c.getId()
		<< " | Titlu: " << c.getTitlu()
		<< " | Autor: " << c.getAutor()
		<< " | Gen: " << c.getGen()
		<< " | An: " << c.getAn() << '\n';
}

void UI::printLista(const Lista<Carte>& l) const {
	if (l.size() == 0) {
		cout << "Nu exista carti.\n";
		return;
	}

	for (const auto& carte : l) {
		printCarte(carte);
	}
}

void UI::printListaIndex(const Lista<int>& l) const {
	if (l.size() == 0) {
		cout << "Nu exista carti.\n";
		return;
	}

	const Lista<Carte>& all = srv.getAll();

	for (const int poz : l) {
		printCarte(all.getElem(poz));
	}
}

void UI::printCos() const {
	const Lista<int>& cos = srv.getCos();
	const Lista<Carte>& all = srv.getAll();

	if (cos.size() == 0) {
		cout << "Cosul este gol.\n";
		return;
	}

	Lista<int> pozitii;

	for (const int id : cos) {
		auto it = std::find_if(all.begin(), all.end(),
			[id](const Carte& c) {
				return c.getId() == id;
			});

		if (it != all.end()) {
			int poz = static_cast<int>(std::distance(all.begin(), it));




			pozitii.add(poz);
		}
	}

	cout << "\nCosul contine " << srv.sizeCos() << " carti:\n";
	printListaIndex(pozitii);
}

bool UI::readInt(const string& mesaj, int& val) const {
	cout << mesaj;
	cin >> val;

	if (!cin) {
		cout << "Input invalid!\n";
		cin.clear();
		cin.ignore(1000, '\n');
		return false;
	}

	cin.ignore(1000, '\n');
	return true;
}

void UI::uiAddCarte() {
	int id;
	if (!readInt("Id: ", id))
		return;

	string titlu;
	string autor;
	string gen;

	cout << "Titlu: ";
	getline(cin, titlu);

	cout << "Autor: ";
	getline(cin, autor);

	cout << "Gen: ";
	getline(cin, gen);

	int an;
	if (!readInt("An aparitie: ", an))
		return;

	try {
		srv.addCarte(id, titlu, autor, gen, an);
		cout << "Carte adaugata cu succes.\n";
	}
	catch (const ValidationError& e) {
		cout << e.getMessage();
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiDeleteCarte() {
	int id;
	if (!readInt("Id-ul cartii de sters: ", id))
		return;

	try {
		srv.deleteCarte(id);
		cout << "Carte stearsa cu succes.\n";
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiUpdateCarte() {
	int id;
	if (!readInt("Id-ul cartii de modificat: ", id))
		return;

	string titlu;
	string autor;
	string gen;

	cout << "Titlu nou: ";
	getline(cin, titlu);

	cout << "Autor nou: ";
	getline(cin, autor);

	cout << "Gen nou: ";
	getline(cin, gen);

	int an;
	if (!readInt("An aparitie nou: ", an))
		return;

	try {
		srv.updateCarte(id, titlu, autor, gen, an);
		cout << "Carte modificata cu succes.\n";
	}
	catch (const ValidationError& e) {
		cout << e.getMessage();
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiFindCarte() const {
	int id;
	if (!readInt("Id-ul cautat: ", id))
		return;

	try {
		const Carte& rezultat = srv.findCarte(id);
		cout << "Cartea a fost gasita:\n";
		printCarte(rezultat);
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiShowAll() const {
	cout << "\nLista de carti:\n";
	printLista(srv.getAll());
}

void UI::uiSortByTitlu() const {
	cout << "\nCarti sortate dupa titlu:\n";
	printListaIndex(srv.sortByTitlu());
}

void UI::uiSortByAutor() const {
	cout << "\nCarti sortate dupa autor:\n";
	printListaIndex(srv.sortByAutor());
}

void UI::uiSortByAnGen() const {
	cout << "\nCarti sortate dupa an + gen:\n";
	printListaIndex(srv.sortByAnGen());
}

void UI::uiFilterByTitlu() const {
	string titlu;
	cout << "Titlul dupa care se filtreaza: ";
	getline(cin, titlu);

	cout << "\nCarti filtrate dupa titlu:\n";
	printListaIndex(srv.filterByTitlu(titlu));
}

void UI::uiFilterByAn() const {
	int an;
	if (!readInt("Anul dupa care se filtreaza: ", an))
		return;

	cout << "\nCarti filtrate dupa an:\n";
	printListaIndex(srv.filterByAn(an));
}

void UI::uiAdaugaCos() {
	string titlu;
	cout << "Titlul cartii de adaugat in cos: ";
	getline(cin, titlu);

	try {
		srv.adaugaCos(titlu);
		cout << "Carte adaugata in cos cu succes.\n";
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiGolesteCos() {
	srv.golesteCos();
	cout << "Cos golit cu succes.\n";
}

void UI::uiGenereazaCos() {
	int nr;
	if (!readInt("Numarul de carti pentru generare: ", nr))
		return;

	try {
		srv.genereazaCos(nr);
		cout << "Cos generat cu succes.\n";
		cout << "Numar carti in cos: " << srv.sizeCos() << '\n';
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiShowCos() const {
	cout << "\nContinut cos:\n";
	printCos();
}

void UI::uiExportCosCSV() const {
	string numeFisier;
	cout << "Numele fisierului pentru export (ex: cos.csv): ";
	getline(cin, numeFisier);

	try {
		srv.exportCosCSV(numeFisier);
		cout << "Cos exportat in " << numeFisier << " cu succes.\n";
	}
	catch (const RepoError& e) {
		cout << e.getMessage();
	}
}

void UI::uiRaportGenuri() const {
	auto raport = srv.raportGen();
	for (const auto& dto : raport) {
		cout << "Gen: " << dto.getGen() << ", Numar carti: " << dto.getCount() << '\n';
	}
}

void UI::run() {
	while (true) {
		uiShowCos();
		printMenu();
		int cmd;

		if (!readInt("", cmd))
			continue;

		switch (cmd) {
		case 1:
			uiAddCarte();
			break;
		case 2:
			uiDeleteCarte();
			break;
		case 3:
			uiUpdateCarte();
			break;
		case 4:
			uiFindCarte();
			break;
		case 5:
			uiShowAll();
			break;
		case 6:
			addSampleData();
			break;
		case 7:
			uiSortByTitlu();
			break;
		case 8:
			uiSortByAutor();
			break;
		case 9:
			uiSortByAnGen();
			break;
		case 10:
			uiFilterByTitlu();
			break;
		case 11:
			uiFilterByAn();
			break;
		case 12:
			uiAdaugaCos();
			break;
		case 13:
			uiGolesteCos();
			break;
		case 14:
			uiGenereazaCos();
			break;
		case 15:
			uiExportCosCSV();
			break;
		case 16:
			uiRaportGenuri();
			break;
		case 0:
			cout << "La revedere!\n";
			return;
		default:
			cout << "Optiune invalida.\n";
			break;
		}
	}
}