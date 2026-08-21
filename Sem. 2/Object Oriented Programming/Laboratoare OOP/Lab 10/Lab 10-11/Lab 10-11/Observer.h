#pragma once

#include <algorithm>
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    vector<Observer*> observers;

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

protected:
    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};