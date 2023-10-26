#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using namespace std;

fstream finn("alfabet.in");
ofstream fout("remaining_words.txt");
fstream fin("remaining_words.txt");

int nrincercari = 4;

int vascii[26];

bool jocterminat = false, auxbool = false;

vector <string> incercari_ramase;

char incercare;

int de_cate_ori, aux = 0, nrlitere, maxim = -1, aux2[26], aux3;

string cuvant, repetitie, y_n = "k";

vector <string> cuvant_ghicit;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cate_litere_are_cuvantul()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(21, 1);
    cout << "Bine ai venit la jocul Spanzuratoarea!";
    Sleep(1500);
    gotoxy(1, 4);
    cout << "Gandestete la un cuvant de ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "3-9 litere, fara nume de persoane sau locuri,";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(1, 5);
    cout << "pentru a incerca sa il ghicesc.\n";
    Sleep(1500);
    gotoxy(1, 7);
    cout << "Din cate litere este format cuvantul?: ";
    cin >> nrlitere; cout << endl << endl;
    while ((int)nrlitere < 3 || (int)nrlitere > 9)
    {
        cout << "Cuvantul trebuie sa fie format din 3 pana la 9 litere!\n";
        cout << "Din cate litere este format cuvantul?: ";
        cin >> nrlitere; cout << endl << endl;
    }
}

void elimina_cuvintele_care_nu_au_numarul_de_litere()
{
    while (true)
    {
        finn >> cuvant;
        if (cuvant == repetitie)
        {
            break;
        }
        repetitie = cuvant;
        if (cuvant.length() == nrlitere)
        {
            incercari_ramase.push_back(cuvant);
        }
    }
    repetitie = '\0';
}

void care_e_cea_mai_frecventa_litera()
{

    for (int k = 0; k < incercari_ramase.size(); k++)
    {
        cuvant = incercari_ramase[k];
        for (int i = 0; i < nrlitere; i++)
        {
            for (char j = 'a'; j <= 'z'; j++)
            {
                if (cuvant[i] == j)
                {
                    if (aux2[aux] != 1)
                    {
                        vascii[aux]++;
                        break;
                    }
                    break;
                }
                aux++;
            }
            aux = 0;
        }
    }
    aux = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (maxim < vascii[aux])
        {
            maxim = vascii[aux];
            incercare = i;
        }
        aux++;
    }
    maxim = -1;
    aux2[incercare - 97] = 1;
    vascii[incercare - 97] = -1;
    for (int i = 0; i < 26; i++)
    {
        if (aux2[i] != 1)
        {
            vascii[i] = 0;
        }
    }
    cout << "";
}

void scrie_cuvantul()
{
    for (int i = 0; i < nrlitere; i++)
    {
        if (cuvant_ghicit[i] == "{")
        {
            cout << '.';
        }
        else
            cout << cuvant_ghicit[i];
    }
    cout << endl;
    for (int i = 1; i <= nrlitere; i++)
        cout << i;
    cout << endl;
}

void yes_no()
{
    while (y_n.compare(0, y_n.length(), "y") != 0 && y_n.compare(0, y_n.length(), "n") != 0)
    {
        cout << "Cuvantul tau contine litera '" << incercare << "'? (y/n)";
        cin >> y_n;
    }
}

void yes()
{
    cout << "De cate ori se repeta litera '" << incercare << "' in cuvantul tau? ";
    cin >> de_cate_ori;
    cout << "Introdu toate pozitiile literelor (1-" << nrlitere << ") in care apare litera '" << incercare << "'. ";
    for (int i = 1; i <= de_cate_ori; i++)
    {
        cin >> aux;
        cuvant_ghicit[aux - 1] = incercare;
    }
    cout << endl;
    //  cout<<"Asa: "<<cuvant_ghicit<<" ? (y/n)\n";
    //  cin>>y_n;
    //  if(y_n == 'n')
    //  {
    //      while()
    //  }
    for (int k = 0; k < incercari_ramase.size(); k++)
    {
        cuvant = incercari_ramase[k];
        for (int i = 0; i < nrlitere; i++)
        {
            if (cuvant_ghicit[i] != "{")
            {
                if (cuvant.compare(i, 1, cuvant_ghicit[i], 0, 1) != 0)
                {
                    incercari_ramase.erase(incercari_ramase.begin() + k);
                    k--;
                    break;
                }
            }
        }
    }
}

void no()
{
    if (y_n == "n")
    {
        if (nrincercari - 1 == 0)
        {
            cout << "Ai reusit sa ma bati la acest joc!";
            //return 0;
        }
        nrincercari -= 1;
        cout << "Am gresit o incercare, mai am " << nrincercari << " incercari\n";
        for (int k = 0; k < incercari_ramase.size(); k++)
        {
            cuvant = incercari_ramase[k];
            for (int i = 0; i < nrlitere; i++)
            {
                if (cuvant[i] == incercare)
                {
                    incercari_ramase.erase(incercari_ramase.begin() + k);
                    k--;
                    break;
                }
            }
        }
    }
}

int main()
{
    //1.

    for (int i = 0; i < 26; i++)
    {
        aux2[i] = -1;
    }

    cate_litere_are_cuvantul();

    //2.
    elimina_cuvintele_care_nu_au_numarul_de_litere();

    for (int i = 0; i < nrlitere; i++)
        cuvant_ghicit.push_back("{");

    cout << "Am " << nrincercari << " incercari pentru a ghici cuvantul.\n";

    //3.

    while (nrincercari != 0 && jocterminat == false)
    {
        care_e_cea_mai_frecventa_litera();

        //3.1.
        scrie_cuvantul();

        yes_no();

        if (y_n == "y")
        {
            yes();
        }
        else
        {
            no();
        }
        y_n = "=";

        aux = 0;
        for (int i = 0; i < nrlitere; i++)
        {
            if (cuvant_ghicit[i] != "{")
            {
                aux++;
            }
        }
        if (aux == nrlitere)
        {
            scrie_cuvantul();
            jocterminat = true;
        }
        aux = 0;

    }
    for (int i = 0; i < incercari_ramase.size(); i++)
        fout << incercari_ramase[i] << endl;

    //1.Citeste din cate litere e cuvantul ----
    //2.Scrie incercarile ramase ----
    //3.Cautarea care e cea mai frecventa litera in fiecare cuvant
    //3.1.Ghicirea acelei litere
    //{
    //      Daca contine litera sa vada pe ce spatii si sa stearga cuvintele nepotrivite
    //      Altfel sa scada o incercare si sa stearga cuvintele cu aceea litera
    //}
    //4.Repeta 3 pana se termina jocul/ramane fara incercari
    return 0;
}