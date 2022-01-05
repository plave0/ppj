import re
import sys

televizori = []

flag = ""
opcija1 = ""
opcija2 = ""

def print_televizor(tv):

    out = ""
    out += str(tv["godina"]) + " "
    out += tv["rmarka"] + " "
    out += tv["model"] + " "
    out += str(tv["diag"]) + "in "
    out += tv["panel"] + " "
    out += str(tv["cena"]) + "din: "
    out += str(tv["kolicina"]) + " komada na stanju "
    print(out)


def ucitaj_podatke():

    ulazni_fajl = "televizori.xml"

    with open(ulazni_fajl, "r") as f:
        podaci = f.read()

    izraz = r'<televizor id="(?P<id>[1-9][0-9]*)">\s*'
    izraz += r'(?=.*?\s*<rmarka>(?P<marka>[A-Za-z0-9 ]*)</rmarka>\s*)'
    izraz += r'(?=.*?\s*<model>(?P<model>[A-Za-z0-9]*)</model>\s*)'
    izraz += r'(?=.*?\s*<godina>(?P<godina>[0-9]{4})</godina>\s*)'
    izraz += r'(?=.*?<diag>(?P<diag>[1-9][0-9]+(.[1-9])?)</diag>)'
    izraz += r'(?=.*?<kolicina>(?P<kolicina>[0-9]*)</kolicina>)'
    izraz += r'(?=.*?<panel>(?P<panel>(TN|VA|IPS|LED)-(HD|FHD|UHD))</panel>)'
    izraz += r'(?=.*?<cena>(?P<cena>[0-9]*)</cena>)'
    izraz += r'.*?'
    izraz += r'</televizor>'

    re_televizor = re.compile(izraz,re.S)

    for m in re_televizor.finditer(podaci):
        televizor = {
                "id" : m.group("id"),
                "rmarka" : m.group("marka"),
                "model" : m.group("model"),
                "godina" : int(m.group("godina")),
                "diag": int(m.group("diag")),
                "kolicina" : int(m.group("kolicina")),
                "panel" : m.group("panel"),
                "cena" : int(m.group("cena"))
                }
        televizori.append(televizor)

def parsiraj_argument():
    
    global flag
    global opcija1
    global opcija2

    if len(sys.argv) == 1:
        flag = "all"
    elif len(sys.argv) == 3:
        if sys.argv[1][1] in {"r", "g"}:
            flag = sys.argv[1][1]
            opcija1 = sys.argv[2]
        else:
            print("error: bad args")
            exit()
    elif len(sys.argv) == 4:
        if sys.argv[1][1] in {"c", "d"}:
            flag = sys.argv[1][1]
            opcija1 = sys.argv[2]
            opcija2 = sys.argv[3]
        else:
            print("error: bad args")
            exit()
    else:
        print("error: bad args")
        exit()

def main():

    ucitaj_podatke()
    parsiraj_argument()

    if flag == "all":
        for tv in televizori:
            if tv["kolicina"] > 0:
                print_televizor(tv)
    elif flag == "r":
        for tv in televizori:
            if tv["rmarka"] == opcija1:
                print_televizor(tv)
    elif flag == "c":
        for tv in televizori:
            if tv["cena"] >= int(opcija1) and tv["cena"] <= int(opcija2):
                print_televizor(tv)
    elif flag == "d":
        for tv in televizori:
            if tv["diag"] >= int(opcija1) and tv["diag"] <= int(opcija2):
                print_televizor(tv)
    elif flag == "g":
        for tv in televizori:
            if tv["godina"] == int(opcija1):
                print_televizor(tv)



if __name__ == "__main__":
    main()
