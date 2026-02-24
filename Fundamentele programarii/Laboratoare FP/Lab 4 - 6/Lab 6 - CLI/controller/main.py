"""
Aplicatie de gestionare a participantilor la un concurs de informatica
"""

from ui import console
from utils import test


def main():

    console.run()
    test.test_all()

if __name__ == "__main__":
    main()


"""
Exemple date de intrare:

305
10 9 8 7 9 10 8 9 9 10  ; 89
306
10 9 8 7 9 10 8 9 9 10 ; 89
310
10 9 8 7 9 6 8 9 9 10 ; 85
204
10 9 8 8 9 8 8 8 9 10 ; 87
"""