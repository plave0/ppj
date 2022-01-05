import re
import sys
from datetime import date

pacijenti = []
flag = ""
opcija = ""

def ucitaj_pacijente():

    global pacijenti

    ulazni_fajl = "pacijenti.txt"
    if re.match(r".*\.txt", ulazni_fajl) == None:
        print("error: no file")
        exit()
    
    with open(ulazni_fajl, "r") as f:
        podaci = f.read()

    izraz = r'<pacijent rbr="(?P<rbr>[1-9][0-9]*)">\s*'
    izraz += r'(?=.*?<klinika>(?P<klinika>[A-Za-z0-9-][A-Za-z0-9-]*)</klinika>\s*)'
    izraz += r'(?=.*?<odeljenje>(?P<odeljenje>[IVXLDCM]+/[0-9]*)</odeljenje>\s*)'
    izraz += r'(?=.*?<ime>(?P<ime>[A-Z][a-z]+( [A-Z][a-z]+)+)</ime>\s*)'
    izraz += r'(?=.*?<bp>(?P<protokol>[A-Za-z0-9.,?!/-]*)</bp>\s*)'
    izraz += r'(?=.*?<drodjenja>(?P<rdan>[0-9]{2})/(?P<rmesec>[0-9]{2})/(?P<rgodina>[0-9]{4})</drodjenja>\s*)'
    izraz += r'(?=.*?<dprijema>(?P<pdan>[0-9]{2})/(?P<pmesec>[0-9]{2})/(?P<pgodina>[0-9]{4})</dprijema>\s*)'
    izraz += r'(?=.*?<stanje>(?P<stanje>(lakse|srednje tesko|tesko|zivotno ugrozen))</stanje>\s*)'
    izraz += r'(?=.*?<o2>(?P<ktip>(ne|maska|respirator))(:(?P<kkolicina>[0-9]*)l)?</o2>\s*)'
    izraz += r'.*?'
    izraz += r'</pacijent>'

    ri_pacijent = re.compile(izraz, re.S)

    for m in ri_pacijent.finditer(podaci):

        drodjenja = date(int(m.group("rgodina")), int(m.group("rmesec")), int(m.group("rdan")))
        dprijema = date(int(m.group("pgodina")), int(m.group("pmesec")), int(m.group("pdan")))
        pacijent = {
                "rbr" : m.group("rbr"),
                "klinika" : m.group("klinika"),
                "odeljenje" : m.group("odeljenje"),
                "ime" : m.group("ime"),
                "protokol" : m.group("protokol"),
                "drodjenja" : drodjenja,
                "dprijema" : dprijema,
                "stanje" : m.group("stanje"),
                "kiseonik" : {"tip" : m.group("ktip"), "kolicina": m.group("kkolicina") }
                }
        # print(pacijent)
        pacijenti.append(pacijent)

def print_pacijent(pacijent):

    out = pacijent["rbr"] + "; "
    out += pacijent["ime"] + "; "
    out += "r: " + pacijent["drodjenja"].strftime("%d/%m/%Y") + "; "
    out += "p: " + pacijent["dprijema"].strftime("%d/%m/%Y") + "; "
    out += pacijent["klinika"] + "; "
    out += pacijent["odeljenje"] + "; "
    out += pacijent["protokol"] + "; "
    out += pacijent["stanje"] + "; "
    out += pacijent["kiseonik"]["tip"]     
    if pacijent["kiseonik"]["kolicina"] != None:
        out += ":" + pacijent["kiseonik"]["kolicina"] + "l"

    print(out)

def parsiraj_argumente():

    global flag
    global opcija

    if len(sys.argv) == 1:
        flag = "all"
    elif len(sys.argv) == 2:
        if sys.argv[1][1] == "o":
            flag = "o"
        else:
            print("error: bad args")
            exit()
    elif len(sys.argv) == 3:
        if sys.argv[1][1] in {"s", "g", "k"}:
            flag = sys.argv[1][1]
            opcija = sys.argv[2]
        else:
            print("error: bad args")
            exit()
    else:
        print("error: bad args")
        exit()
    

def main():
   
    parsiraj_argumente()
    ucitaj_pacijente()

    if flag == "all":
        spac = sorted(pacijenti,key=lambda x : x["dprijema"])
        for pac in spac:
            print_pacijent(pac)
    elif flag == "s":
        for pac in pacijenti:
            if pac["stanje"] == opcija:
                print_pacijent(pac)
    elif flag == "g" :
        for pac in pacijenti:
            if pac["drodjenja"].year < int(opcija):
                print_pacijent(pac)
    elif flag == "o" :
        for pac in pacijenti:
            if pac["stanje"] == "lakse":
                print_pacijent(pac)
    elif flag == "k":
        for pac in pacijenti:
            if pac["kiseonik"]["kolicina"] != None and int(pac["kiseonik"]["kolicina"]) >= int(opcija):
                print_pacijent(pac)
                
        
if __name__ == "__main__":
    main()
