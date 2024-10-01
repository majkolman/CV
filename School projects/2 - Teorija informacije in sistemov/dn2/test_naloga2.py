import sys
import json
from pathlib import Path
from timeit import default_timer as timer
from naloga2 import naloga2


def test_naloga2(case_dir, case_id):
    """
    Funkcija za preverjanje naloge 2.
    Primer uporabe kot uvožen modul:
    from test_naloga2 import test_naloga2
    test_naloga2('primeri', 1)
    """
    # Zahtevana natančnost izračunov za r
    tol = 1e-6
    # Zahtevana časovna omejitev (sekunde)
    t_max = 30

    # Naložimo vhodne podatke in rešitev
    base_path = Path(__file__).parent
    file_path = base_path / str(case_dir) / (str(case_id) + '.json')
    json_file = open(file_path, 'r', encoding='utf8')
    data = json.load(json_file, strict=False)

    # Poženemo rešitev domače naloge in izmerimo izvajalni čas
    start = timer()
    izhod, r = naloga2(data['vhod'], data['nacin'])
    end = timer()
    t_elapsed = end - start

    # Ovrednotimo rešitev
    success_izhod = izhod == data['izhod']
    success_r = abs(r - data['r']) < tol
    success = int(success_izhod and success_r)

    # Izpišemo rezultat
    print("-"*72)
    print(f"Rezultat za primer {case_id}: {success} točk")
    if success_izhod != 1:
        print(' ✗ Napačen izhod')
    if success_r != 1:
        print(' ✗ Napačno kompresijsko razmerje')
        print(f"   -> Izračunani r: {r:.4f}")
        print(f"   -> Pravi r:      {data['r']:.4f}")
    print(f"Čas izvajanja: {t_elapsed:.4f} s")
    if t_elapsed > t_max:
        print(
            f" -> Čas izvajanja je daljši od {t_max:.1f} sekund! Razmislite o optimizaciji kode.")


def main(case_dir="primeri", case_id=None, *other):
    """
    Datoteko test_naloga2.py lahko poženemo kot program s podanimi vhodnimi argumenti:
    Primeri uporabe:
        V mapi "testi" poženemo 1. primer (1.json):
        python test_naloga2.py testi 1

        V mapi "testi" poženemo vse tri primere:
        python test_naloga2.py primeri

        V mapi s privzetim imenom "primeri" poženemo vse tri primere:
        python test_naloga2.py
    """

    # Preverimo morebitne odvečne argumente ukazne vrstice (pospravljeni so v other)
    if other:
        print(("Napačno število argumentov! Podali ste {} preveč.\n"
               "Zagon:  python test_naloga2.py [mapa_s_primeri] [stevilka_primera]\n"
               "Primer: python test_naloga2.py primeri 2").format(len(other)))
        exit()

    # Poženemo za vse primere;
    # v primeru določenega case_id, upoštevamo le-tega
    if not case_id:
        [test_naloga2(case_dir, case_id=i) for i in range(1, 4)]
    else:
        test_naloga2(case_dir, case_id)


if __name__ == "__main__":
    # Argumenti ukazne vrstice so v sys.argv
    main(*sys.argv[1:])
