class ValidatorMelodie:
    def validate(self, m):
        # titlu, artist: nevide
        # gen: ['pop', 'rock','folk', 'hip-hop']
        # durata: x.y: x>=1, x<=15, 0<=y<=59
        errors = []
        if m.get_titlu() == "":
            errors.append("Titlul nu poate fi vid.")
        if m.get_artist() == "":
            errors.append("Artistul nu poate fi vid.")
        if m.get_gen() not in ['pop', 'rock', 'folk', 'hip-hop']:
            errors.append("Genul trebuie sa fie dintre: pop, rock, folk, hip-hop.")

        # maybe add get_minutes, get_seconds
        # maybe model it with a whole new class - Durata
        minute = int(m.get_durata())
        # 13.59 -> 13; 13.59-13 = 0.59
        secunde = (m.get_durata() - minute) * 100
        if not 1 <= minute <= 15:
            errors.append("Minutele trebuie sa fie intre 1 si 15")
        if not 0 <= secunde <= 59:
            errors.append("Secundele trebuie sa fie intre 0 si 59")

        if len(errors) > 0:
            raise ValueError('\n'.join(errors))


class ValidatorPersoana:
    def validate(self, persoana):
        errors = []

        if len(persoana.cnp) != 13:
            errors.append("CNP trebuie sa fie format din 13 cifre.")

        if len(persoana.nume.split()) < 2:
            errors.append("Persoana trebuie sa aiba nume si prenume (i.e. cel putin 2 cuvinte).")

        if len(errors) > 0:
            error_str = '\n'.join(errors)
            raise ValueError(error_str)

class ValidatorRating:
    def validate(self, rating):
        errors = []

        if not 1 <= rating.get_scor() <= 5:
            errors.append("Scorul evaluarii trebuie sa fie intre 1 si 5.")

        if len(errors) > 0:
            error_str = '\n'.join(errors)
            raise ValueError(error_str)