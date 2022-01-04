import re
import sys
import datetime

pacijenti = []

flag = ""
opcija = ""

def print_pacijent(pacijent):

    red = ""
    red += pacijent["rbr"] + "; "
    red += pacijent["ime_prezime"] + "; "
    red += pacijent["datum"].strftime("%d.%m.%Y") + "; "
    red += pacijent["prelezao"] + "; "
    red += pacijent["vakcine"][0]
    for v in pacijent["vakcine"][1:]:
        red += ", " + v
    red += "; "
    red += pacijent["stanja"][0]
    for s in pacijent["stanja"][1:]:
        red += ", " + s
    print(red)

def ucitaj_pacijent():

    ulazni_fajl = "pacijenti.txt"

    fajl_izraz = r".*\.txt"
    if re.match(fajl_izraz, ulazni_fajl, re.I) == None:
        print("error: input file must have .txt extension")
        exit()

    with open(ulazni_fajl, "r") as f:
        tekst = f.read()

    izraz = r"(?P<rbr>[1-9][0-9]*); "
    izraz += r"(?P<ime_prezime>[A-Z][a-z]+( [A-Z][a-z]+)+); "
    izraz += r"(?P<dan>[0-3][0-9])\.(?P<mesec>[01][0-9])\.(?P<godina>[12][0-9]{3}); "
    izraz += r"(?P<prelezao>(da|ne|nepoznato))[ ]*; "
    izraz += r"(?P<vakcine>(Phizer|Sputnjik-V|SinoPharm)(, (Phizer|Sputnjik-V|SinoPharm))*); "
    izraz += r"(?P<stanja>[A-Za-z0-9-]*(, [A-Za-z0-9-]*)*)"

    re_pacijent = re.compile(izraz, re.S);

    for m in re_pacijent.finditer(tekst):
        
        ispravan_ulaz = True
        datum = datetime.date(int(m.group("godina")),int(m.group("mesec")), int(m.group("dan"))) 
        
        ispravan_ulaz = datum >= datetime.date(1910,1,1)

        if ispravan_ulaz:
            pacijent = {
                    "rbr": m.group("rbr"),
                    "ime_prezime": m.group("ime_prezime"),
                    "datum": datum,
                    "prelezao" : m.group("prelezao"),
                    "vakcine": m.group("vakcine").split(", "),
                    "stanja": m.group("stanja").split(", ")
                    }
            pacijenti.append(pacijent)
    

def parsiraj_argumente():

    global flag
    global opcija
    if len(sys.argv) == 1:
        flag = "all"
    elif len(sys.argv) == 2:
        if sys.argv[1][1] == "n":
            flag = "n"
        else:
            print("erro:r: bad args")
            exit()
    elif len(sys.argv) == 3:
        if sys.argv[1][1] == "v" or sys.argv[1][1] == "g":
            flag = sys.argv[1][1]
            opcija = sys.argv[2]
        else:
            print("error: bad args")
            exit()
    else:
        print("error: bad args")
        exit()

def main():

    ucitaj_pacijent()
    parsiraj_argumente()

    if flag == "all":
        sortirano = sorted(pacijenti, key=lambda x : x["vakcine"][0])
        for pacijent in sortirano:
            print_pacijent(pacijent)
    if flag == "v":
        for pacijent in pacijenti:
            if opcija in pacijent["vakcine"]:
                print_pacijent(pacijent)
    if flag == "g":
        for pacijent in pacijenti:
            if datetime.date.today().year - pacijent["datum"].year >= int(opcija):
                print_pacijent(pacijent)
    if flag == "n":
        for pacijent in pacijenti:
            godine = datetime.date.today().year - pacijent["datum"].year;
            alergija = False
            for s in pacijent["stanja"]:
                if "alergija" in s:
                    alergija = True
                    break
            if godine < 18 or alergija or pacijent["prelezao"] != "ne":
                print_pacijent(pacijent)

if __name__ == "__main__":
    main()
