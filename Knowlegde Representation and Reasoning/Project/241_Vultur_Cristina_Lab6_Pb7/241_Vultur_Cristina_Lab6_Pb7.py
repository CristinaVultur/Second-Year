#241 Vultur Cristina
""" definirea problemei """

from dataclasses import dataclass
from copy import deepcopy
from math import sqrt
import timeit

@dataclass
class Punct:
    x: float
    y: float

@dataclass
class Frunza:
    id: int
    coordonate: Punct
    nr_insecte: int
    gmax: int


input = ["input_1.txt","input_2.txt","input_3.txt","input_4.txt"]
output = ["output_1.txt","output_2.txt","output_3.txt","output_4.txt"]
#fisierele de intrare/iesire

class Nod:
    def __init__(self, frunze,id_frunza,greutate,insecte = 0):
        self.frunze = frunze #dictionarul de frunze corespunzator nodului (se schimba nr de insect)
        self.greutate = greutate #(greutatea curenta a broastei)
        self.id_frunza= id_frunza
        self.info = (frunze, id_frunza, greutate)
        self.insecte_mancate = insecte #insectele mancate pe frunza
        self.h = self.euristica_consistenta(self.frunze[self.id_frunza].coordonate)

    def __repr__(self):
        return f"({self.frunze[self.id_frunza]}, {self.greutate}, h={self.h})"

    #euristica = distanta de la punct la malul apei impartita la greutatea curenta a broastei/3
    #aceasta euristica determina salturile minime care trebuie facute de la punct la mal avand greutatea curenta
    #un salt poate avea maxim greutatea/3, deci aceasta euristica da nr de salturi la capacitate maxima pe care il face broasca daca ar exista puncte  in drum drept pe care sa mearga

    def euristica(self,p):
        return distanta_cerc(p)/(self.greutate/3)

    # aceasta euristica determina salturile minime care trebuie facute de la punct la mal avand greutatea maxima posibila
    #consistenta

    def euristica_consistenta(self,p): #h(tata)<= 1 + h(fiu) este consistenta
        return distanta_cerc(p)/(max/3) #max calculata in main este cea mai mare greutate suportata dintre frunze

    #euristica incorecta
    #supraestimeaza h^ input_4 id8 = 3 dar h(id8) adevarat este 2, deci nu este admisibila
    def euristica_incorecta(self, p): #nr de frunze care se afla mai aproape de mal decat frunza pe care suntem
        nr = 0
        for frunza in frunze.values():
            if distanta_cerc(p) > distanta_cerc(frunza.coordonate):
                nr+=1
        return nr
class Arc:
	def __init__(self, capat, varf, cost):
		self.capat = capat
		self.varf = varf
		self.cost = cost


class Problema:
    def __init__(self):
        self.noduri = [Nod(frunze,id_start,greutate_initiala)]  # de tip Nod
        #self.nod_scop = [['b','c'],[],['d','a']]  # doar info (fara h)
        self.nod_start = self.noduri[0]

    def cauta_nod_nume(self, info):
        """Stiind doar informatia "info" a unui nod,
        trebuie sa returnati fie obiectul de tip Nod care are acea informatie,
        fie None, daca nu exista niciun nod cu acea informatie."""
        for nod in self.noduri:
            if nod.info == info:
                return nod
        return None


""" Sfarsit definire problema """

""" Clase folosite in algoritmul A* """


class NodParcurgere:
    """O clasa care cuprinde informatiile asociate unui nod din listele open/closed
        Cuprinde o referinta catre nodul in sine (din graf)
        dar are ca proprietati si valorile specifice algoritmului A* (f si g).
        Se presupune ca h este proprietate a nodului din graf
    """

    problema = None  # atribut al clasei (se suprascrie jos in __main__)

    def __init__(self, nod_graf, parinte=None, g=0, f=None):
        self.nod_graf = nod_graf  # obiect de tip Nod
        self.parinte = parinte  # obiect de tip NodParcurgere
        self.g = g  # costul drumului de la radacina pana la nodul curent
        self.f = self.g + self.nod_graf.h


    def drum_arbore(self):
        """
            Functie care calculeaza drumul asociat unui nod din arborele de cautare.
            Functia merge din parinte in parinte pana ajunge la radacina
        """
        nod_c = self
        drum = [nod_c]
        while nod_c.parinte is not None:
            drum = [nod_c.parinte] + drum
            nod_c = nod_c.parinte
        return drum

    def contine_in_drum(self, nod):
        """
            Functie care verifica daca nodul "nod" se afla in drumul dintre radacina si nodul curent (self).
            Verificarea se face mergand din parinte in parinte pana la radacina
            Se compara doar informatiile nodurilor (proprietatea info)
            Returnati True sau False.

            "nod" este obiect de tip Nod (are atributul "nod.info")
            "self" este obiect de tip NodParcurgere (are "self.nod_graf.info")
        """
        nod_c = self
        while nod_c.parinte is not None:
            if nod.info == self.nod_graf.info:
                return True
            nod_c = nod_c.parinte
        return False

    # se modifica in functie de problema
    def expandeaza(self):
        """Pentru nodul curent (self) parinte, trebuie sa gasiti toti succesorii (fiii)
        si sa returnati o lista de tupluri (nod_fiu, cost_muchie_tata_fiu),
        sau lista vida, daca nu exista niciunul.
        (Fiecare tuplu contine un obiect de tip Nod si un numar.)
        """
        frunza = self.nod_graf.frunze[self.nod_graf.id_frunza] #unde se afla
        successors = []
        #vrem sa ne deplasam pe alta frunza, acea potentiala frunza va fi adaugata in lista cu succesori daca indeplineste conditiile de mai jos
        for frunza_noua in self.nod_graf.frunze.values(): #luam fiecare frunza din "dictionar"
            if frunza_noua.id == frunza.id: #daca e aceeasi frunza nu e admisibil
                continue
            for insecte_mancate in range(0, frunza.nr_insecte + 1): #pe o frunza poate manca oricate insecte daca g se supune conditiilor de mai jos
                    gnou = self.nod_graf.greutate + insecte_mancate #noua greutate

                    #conditii daca un succesor este admisibil sau nu
                    #daca distanta e prea mare nu este admisibil
                    dist = distanta_euclidiana(frunza.coordonate, frunza_noua.coordonate)
                    if dist > float(gnou)/3:
                        continue

                    #daca broasca devine prea grea pentru frunza pe care se afla nu este admisibil
                    #if gnou > frunza.gmax:
                        #continue
                    gnou += -1 #greutatea de dupa saltul pe care l-ar face

                    if gnou > frunza_noua.gmax: #daca greutatea de dupa salt este mai mare decat greutatea pe care o permite frunza nu este admisibil
                        continue

                    if gnou == 0: #daca broscuta moare nu este admisibil
                        continue

                    #paramerii noului nod succesor, trebuie schimbate nr_insecte si insecte_mancare
                    frunze_noi = deepcopy(frunze)
                    frunze_noi[frunza.id] = Frunza(frunza.id, frunza.coordonate, frunza.nr_insecte - insecte_mancate, frunza.gmax)
                    nod = Nod(frunze_noi, frunza_noua.id, gnou,insecte_mancate)
                    successors.append((nod,dist)) #g este 1 pentru ca broscuta pierde doar o unitate de energie pe fiecare salt
        return successors



    # se modifica in functie de problema
    def test_scop(self):
        #testm starea finala : daca are destul de multe energie (greutate) sa faca salt de pe frunza pe mal
        frunza = self.nod_graf.frunze[self.nod_graf.id_frunza]
        greutate = self.nod_graf.greutate
        return distanta_cerc(frunza.coordonate) <= float(greutate)/3


    def __str__(self):
        parinte = self.parinte if self.parinte is None else self.parinte.nod_graf.info
        return f"({self.nod_graf}, parinte={parinte}, f={self.f}, g={self.g})"


""" Algoritmul A* """


def distanta_euclidiana(a, b):
    return sqrt((a.x - b.x) ** 2 + (a.y - b.y) ** 2)


def distanta_cerc(p,centru = Punct(0, 0)):
    #distanta de la p la malul lacului
    return raza - distanta_euclidiana(p, centru)


def str_info_noduri(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = "["
    for x in l:
        sir += str(x) + "  "
    sir += "]"
    return sir


def afis_succesori_cost(l):
    """
        o functie folosita strict in afisari - poate fi modificata in functie de problema
    """
    sir = ""
    for (x, cost) in l:
        sir += "\nnod: " + str(x) + ", cost arc:" + str(cost)

    return sir


def in_lista(l, nod):
    """
    lista "l" contine obiecte de tip NodParcurgere
    "nod" este de tip Nod
    """
    for i in range(len(l)):
        if l[i].nod_graf.info == nod.info:
            return l[i]
    return None

def a_star(o):
    """
        Functia care implementeaza algoritmul A-star
    """
    ### TO DO ... DONE
    nod_start = Nod(frunze, id_start, greutate_initiala)
    rad_arbore = NodParcurgere(nod_start)
    open = [rad_arbore]  # open va contine elemente de tip NodParcurgere
    closed = []  # closed va contine elemente de tip NodParcurgere
    gasit = False

    while len(open) > 0 :
       # print(str_info_noduri(open))	# afisam lista open
        #print(str_info_noduri(closed))
        #print("\n")

        nod_curent = open.pop(0)	# scoatem primul element din lista open
        closed.append(nod_curent)	# si il adaugam la finalul listei closed

        #testez daca nodul extras din lista open este nod scop (si daca da, ies din bucla while)
        if nod_curent.test_scop():
            gasit = True
            break

        l_succesori = nod_curent.expandeaza()	# contine tupluri de tip (Nod, numar)
        for (nod_succesor, cost_succesor) in l_succesori:
            # "nod_curent" este tatal, "nod_succesor" este fiul curent

            # daca fiul nu e in drumul dintre radacina si tatal sau (adica nu se creeaza un circuit)
            if (not nod_curent.contine_in_drum(nod_succesor)):

                # calculez valorile g si f pentru "nod_succesor" (fiul)
                g_succesor = nod_curent.g + cost_succesor # g-ul tatalui + cost muchie(tata, fiu)
                f_succesor = g_succesor + nod_succesor.h # g-ul fiului + h-ul fiului

                #verific daca "nod_succesor" se afla in closed
                # (si il si sterg, returnand nodul sters in nod_parcg_vechi
                nod_parcg_vechi = in_lista(closed, nod_succesor)

                if nod_parcg_vechi is not None:	# "nod_succesor" e in closed
                    # daca f-ul calculat pentru drumul actual este mai bun (mai mic) decat
                    # 	   f-ul pentru drumul gasit anterior (f-ul nodului aflat in lista closed)
                    # atunci actualizez parintele, g si f
                    # si apoi voi adauga "nod_nou" in lista open
                    if (f_succesor < nod_parcg_vechi.f):
                        closed.remove(nod_parcg_vechi)	# scot nodul din lista closed
                        nod_parcg_vechi.parinte = nod_curent # actualizez parintele
                        nod_parcg_vechi.g = g_succesor	# actualizez g
                        nod_parcg_vechi.f = f_succesor	# actualizez f
                        nod_nou = nod_parcg_vechi	# setez "nod_nou", care va fi adaugat apoi in open

                else :
                    # daca nu e in closed, verific daca "nod_succesor" se afla in open
                    nod_parcg_vechi = in_lista(open, nod_succesor)

                    if nod_parcg_vechi is not None:	# "nod_succesor" e in open
                        # daca f-ul calculat pentru drumul actual este mai bun (mai mic) decat
                        # 	   f-ul pentru drumul gasit anterior (f-ul nodului aflat in lista open)
                        # atunci scot nodul din lista open
                        # 		(pentru ca modificarea valorilor f si g imi va strica sortarea listei open)
                        # actualizez parintele, g si f
                        # si apoi voi adauga "nod_nou" in lista open (la noua pozitie corecta in sortare)
                        if (f_succesor < nod_parcg_vechi.f):
                            open.remove(nod_parcg_vechi)
                            nod_parcg_vechi.parinte = nod_curent
                            nod_parcg_vechi.g = g_succesor
                            nod_parcg_vechi.f = f_succesor
                            nod_nou = nod_parcg_vechi

                    else: # cand "nod_succesor" nu e nici in closed, nici in open
                        nod_nou = NodParcurgere(nod_graf=nod_succesor, parinte=nod_curent, g=g_succesor)
                        # se calculeaza f automat in constructor

                if nod_nou:
                    # inserare in lista sortata crescator dupa f
                    # (si pentru f-uri egale descrescator dupa g)
                    i=0
                    while i < len(open):
                        if open[i].f < nod_nou.f:
                            i += 1
                        else:
                            while i < len(open) and open[i].f == nod_nou.f and open[i].g > nod_nou.g:
                                i += 1
                            break

                    open.insert(i, nod_nou)


    if len(open) == 0 and not gasit:
            o.write("Broscuta nu ajunge la mal\n")
    else:
            drum = nod_curent.drum_arbore()
            for i in range(0,len(drum)):
                nod_graf = drum[i].nod_graf
                frunzi, ident_frunza, greutate = nod_graf.info
                if ident_frunza == id_start:
                    o.write(f"Broscuta se afla pe frunza initiala {ident_frunza}.Greutate broasca:{greutate}\n")
                else:
                    nod_parinte = drum[i-1].nod_graf
                    o.write(f"Broscuta a sarit de la {nod_parinte.id_frunza} la {ident_frunza}. Broscuta a mancat {nod_graf.insecte_mancate} insecte. Greutate: {nod_parinte.greutate -1 + nod_graf.insecte_mancate}\n")
            o.write(f"Broscuta a ajuns la mal in {len(drum)} sarituri\n")


max = 0

if __name__ == "__main__":
    #problema = Problema()
    #NodParcurgere.problema = problema
    start_time_h1 = timeit.default_timer() #timpul de start
    for f in range(0,len(input)): #luam fiecare fisier
        with open(input[f], "r") as date:  # citim datele
            raza = float(date.readline())
            greutate_initiala = float(date.readline())
            id_start = date.readline().strip('\n')
            frunze = {}  # dictionar cu key = idX, x={1,2,3,..,cate frunze avem}
            for line in date.readlines():
                i, x, y, nr, gm = line.split()
                coord = Punct(float(x), float(y))
                frunze[i] = Frunza(i, coord, int(nr), float(gm))
            max = 0
            for frunza in frunze.values():
                if frunza.gmax > max:
                    max = frunza.gmax

        with open(output[f], "a") as o:
            a_star(o)
            stop_time_h1 = timeit.default_timer()
            o.write("Timpul pentru euristica = functia distanta cerc " + str(stop_time_h1 - start_time_h1) +'\n')
            o.write('\n')
            o.write('\n')
