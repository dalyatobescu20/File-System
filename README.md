1.FUNCTIA DE TOUCH:
->in cazul in care arb de fisiere era gol, m-am folosit de functia de
 create_file, care creeaza un fisier doar cu numele initializat
->in cazul in care arborele nu era gol,parcurgem tot arborele 
si adaugam in arbore, avand grija pe ce pozitie punem, in ordine 
lexicografica. De asemenea, daca exista un director are acelasi
nume returnam "DIRECTORY ALREADY EXISTS".
->am folosit funcita de check2 care verifica daca un director
anume exista in arbore, daca exista returneaza 1.

2.FUNCTIA DE MKDIR
->am facut o functie care imi creeaza arborele root, doar cu numele
initializat
->am facut o functie care pastreaza si parintele directorului curent
->asemanator ca la functia de touch, daca este gol, adaugam un director,
daca nu este, parcurgem tot arborele de subdirectoare si inseram.
Daca exista un fisier deja cu acelasi nume, afisam
"FILE ALREADY EXISTS".
->am folosit funcita de file_exists care verifica daca un fisier
anume exista in arbore, daca exista returneaza 1.

3.FUNCTIA DE LS
->am folosit implementarea din laborator pentru afisarea unui arbore
in ordine SRD si am aplicat atat pentru subdirectoare cat si pentru fisiere

4.FUNCTIA DE RM
->functia delete_file cauta in arbore fisierul pe care vrem sa-l
eliminam in mod recursiv. Functia returneaza noul arbore

5. FUNCTIA DE RMDIR
-> functia delete_dir cauta in arborele de subdirectoare si daca gaseste
directorul dorit il elimina in mod recursiv. Functia returneaza noul arbore.

6.FUNCTIA DE CD
-> am folosit functia de find care cauta un director si il returneaza
-> daca am gasit directorul in arborele de subdirectoare, ne mutam pe acesta,
astfel root devine acel director si este pastrat in root->parinte, iar atunci
cand dam comanda cd .. se intoarce la cel initial.

7.FUNCTIA DE PWD
->nu este terminata, am stocat intr-un vector toti parintii si apoi i-am afisat,
(cand dau comanda cd, atunci pun acel director in vector);
