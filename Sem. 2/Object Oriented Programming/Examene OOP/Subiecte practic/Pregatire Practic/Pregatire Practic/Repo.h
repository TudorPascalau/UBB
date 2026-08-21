// === Repo.h ===
#pragma once
#include "Produs.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::exception;
using std::string;
using std::vector;

class RepoException : public exception {
    string message;
public:
    explicit RepoException(string message) : message{ std::move(message) } {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Repo {
    vector<Produs> elems;
    string filename;

    void loadFromFile();
    void saveToFile() const;

public:
    explicit Repo(string filename) : filename{ std::move(filename) } {
        loadFromFile();
    }

    const vector<Produs>& getAll() const noexcept { return elems; }

    void store(const Produs& e) {
        auto it = std::find_if(elems.begin(), elems.end(), [&](const Produs& x) {
            return x.getId() == e.getId();
            });
        if (it != elems.end()) {
            throw RepoException{ "Id existent!" };
        }
        elems.push_back(e);
        saveToFile();
    }

    void update(const Produs& e) {
        auto it = std::find_if(elems.begin(), elems.end(), [&](const Produs& x) {
            return x.getId() == e.getId();
            });
        if (it == elems.end()) {
            throw RepoException{ "Id inexistent!" };
        }
        *it = e;
        saveToFile();
    }

    void remove(int id) {
        auto it = std::find_if(elems.begin(), elems.end(), [&](const Produs& x) {
            return x.getId() == id;
            });
        if (it == elems.end()) {
            throw RepoException{ "Id inexistent!" };
        }
        elems.erase(it);
        saveToFile();
    }

    const Produs& find(int id) const {
        auto it = std::find_if(elems.begin(), elems.end(), [&](const Produs& x) {
            return x.getId() == id;
            });
        if (it == elems.end()) {
            throw RepoException{ "Id inexistent!" };
        }
        return *it;
    }
};

// === Repo.cpp ===
#include "Repo.h"

void Repo::loadFromFile() {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw RepoException{ "Nu se poate deschide fisierul!" };
    }

    elems.clear();
    string line;
    while (std::getline(fin, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        string idStr, nume, tip, pretStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nume, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, pretStr, ',');

        int id = std::stoi(idStr);
        double pret = std::stod(pretStr);
        elems.emplace_back(id, nume, tip, pret);
    }
}

void Repo::saveToFile() const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw RepoException{ "Nu se poate salva in fisier!" };
    }

    for (const auto& e : elems) {
        fout << e.getId() << ','
            << e.getNume() << ','
            << e.getTip() << ','
            << e.getPret() << '\n';
    }
}
