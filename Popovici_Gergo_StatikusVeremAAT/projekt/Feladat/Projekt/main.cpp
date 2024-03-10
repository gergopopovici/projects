#include <iostream>
#include <string>
#include "verem.h"
#include <time.h>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#define BLACKJACK 21
using namespace std;
struct kartya
{
	char forma[10];
	int ertek;
};
struct jatekosok
{
	int pontok=0;
	float penz=0;
	Stack<kartya, 20>kezben;
	string nev;
};
struct oszt
{
	int pontok=0;
	Stack<kartya, 20>kezben;
};
void szabalyzat()
{
	cout << "	A jatekos az oszto ellen jatszik. A Blackjack jatek celja annyi kartyat gyujteni, hogy azok osszege kozelebb legyen 21-hez, mint az osztoe, de ne haladja meg a 21-et. " << endl << " Minden lapnak kulon erteke van, amiket osszeadva kapjuk meg a teljes leosztas erteket. A lapok megfelelnek a nevertekuknek, kiveve a Kiraly, a Dama es a Bubi, ezek 10 - et ernek, az Asz pedig 1 - et vagy 11 - et er." << endl << "	A szineknek nincs jelentosege ebben a jatekban. Nincs kulon szabaly, hogy az Asz mikor er 1 - et vagy 11 - et.Onnek nem kell valasztania, mindig az az ertek szamit ami a legjobb az On lapjaihoz." << endl << "	Egy leosztasnak puha osszege van ha az Asz erteke 1 es 11 is lehet anelkul, hogy a 21 - et tullepne.A jatekos uj lapot kerhet es a kisebb osszerteket is valaszthatja, hogy elkerulje a besokallast."<<endl<<"	Ha az egyik erteket hasznalnia kell akkor, azt kemeny osszegnek nevezik.A jatekot egy pakli kartyaval jatsszak, a lapokat minden leosztas utan megkeverik.A program csak egy leosztasos, egyszemelyes blackjacket kinal.Szigoruan csak On jatszhat az oszto ellen, tobb jatekos nem vehet reszt a jatekban." << endl << " Egyszerre csak egy leosztassal jatszhat.";
	cout << endl<<endl;
	cout << "	A tet megtetele utan On es az oszto is ket lapot kap. Az oszto felfedi egyik lapjat, a masik a jatek vegeig leforditva marad. A jatek kezdetekor a jatekos kivalasztja hogyan szeretne cselekedni."<<endl<<"	Miutan a jatekos befejezte a leosztasat, az oszto lejatssza a sajatjat, majd kifizeti a nyeremenyt, vagy begyujti a tetet. Ha az elso ket lap erteke 21 (Asz es 10), akkor blackjackje van."<<" A blackjack azt jelenti, hogy a feltett tet masfelszereset nyeri meg." << endl;
}
void Pakli_letrehoz(Stack<kartya, 52>& pakli)
{
	kartya bemenet;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j <= 13; ++j)
		{
			switch (i)
			{
			case 0: strcpy_s(bemenet.forma, "R");		break;
			case 1: strcpy_s(bemenet.forma, "Sz");	    break;
			case 2: strcpy_s(bemenet.forma, "T");		break;
			case 3: strcpy_s(bemenet.forma, "P");		break;
			}
			bemenet.ertek = j;
			pakli.push(bemenet);
		}
	}
	
}
void Keverd_pakli(Stack<kartya, 52>& pakli ,int k)//Fisher-Yates kevero algoritmusa O(N)-es ido bonyolultsagu
{
	kartya bemenet[52];
	for (int i = 0; i < 52 - k; ++i)
	{
		bemenet[i] = pakli.pop();
	}
	kartya csere;
	srand(time(NULL));
	for (int i = 51-k; i > 0; --i)
	{
		int j = rand() % (i + 1);
		swap(bemenet[i], bemenet[j]);
	}
	for (int i = 51 - k; i>=0; --i)
	{
		pakli.push(bemenet[i]);

	}
}
void elsokor(jatekosok& jatekos, oszt& oszto, Stack<kartya, 52>& pakli)
{
	kartya egy, ketto;
	egy = pakli.pop();
	jatekos.kezben.push(pakli.pop());
	ketto = pakli.pop();
	jatekos.kezben.push(pakli.pop());
	oszto.kezben.push(ketto);
	oszto.kezben.push(egy);
}
void ir_jatekos(jatekosok& jatekos)
{
	vector<kartya> bemenet;
	int n = jatekos.kezben.size();
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(jatekos.kezben.pop());
	}
	cout << jatekos.nev << " kartyai:" << endl;
	for (int i = 0; i < bemenet.size(); ++i)
	{
		switch (bemenet[i].ertek)
		{
		case 1:cout << "A"; break;
		case 2:cout << bemenet[i].ertek; break;
		case 3:cout << bemenet[i].ertek; break;
		case 4:cout << bemenet[i].ertek; break;
		case 5:cout << bemenet[i].ertek; break;
		case 6:cout << bemenet[i].ertek; break;
		case 7:cout << bemenet[i].ertek; break;
		case 8:cout << bemenet[i].ertek; break;
		case 9:cout << bemenet[i].ertek; break;
		case 10:cout << bemenet[i].ertek; break;
		case 11:cout << "J"; break;
		case 12:cout << "Q"; break;
		case 13:cout << "K"; break;
		}
		if (strcmp(bemenet[i].forma, "R") == 0)
		{
			cout<<"\xE2\x99\xA6";
		}
		else
		{
			if (strcmp(bemenet[i].forma, "Sz") == 0)
			{
				cout << "\xE2\x99\xA5";
			}
			else
			{
				if (strcmp(bemenet[i].forma, "T") == 0)
				{
					cout << "\xE2\x99\xA4";
				}
				else
				{
					cout << "\xE2\x99\xA5";
				}
			}
		}
		cout << " ";
	}
	cout << endl;
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		jatekos.kezben.push(bemenet[i]);
	}
}
void ir_oszto(oszt& oszto, bool rejtve)
{
	vector<kartya> bemenet;
	int n = oszto.kezben.size();
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(oszto.kezben.pop());
	}
	cout << "Az oszto kartyai: " << endl;
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if(i!=1 || !rejtve)
		{
		switch (bemenet[i].ertek)
		{
		case 1:cout << "A"; break;
		case 2:cout << bemenet[i].ertek; break;
		case 3:cout << bemenet[i].ertek; break;
		case 4:cout << bemenet[i].ertek; break;
		case 5:cout << bemenet[i].ertek; break;
		case 6:cout << bemenet[i].ertek; break;
		case 7:cout << bemenet[i].ertek; break;
		case 8:cout << bemenet[i].ertek; break;
		case 9:cout << bemenet[i].ertek; break;
		case 10:cout << bemenet[i].ertek; break;
		case 11:cout << "J"; break;
		case 12:cout << "Q"; break;
		case 13:cout << "K"; break;
		}
		if (strcmp(bemenet[i].forma, "R") == 0)
		{
			cout << "\xE2\x99\xA6";
		}
		else
		{
			if (strcmp(bemenet[i].forma, "Sz") == 0)
			{
				cout << "\xE2\x99\xA5";
			}
			else
			{
				if (strcmp(bemenet[i].forma, "T") == 0)
				{
					cout << "\xE2\x99\xA4";
				}
				else
				{
					cout << "\xE2\x99\xA5";
				}
			}
		}
		cout << " ";
		}
	}
	cout << endl;
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		oszto.kezben.push(bemenet[i]);
	}
}
bool blackjack_jatekos(jatekosok& jatekos)
{
	int s=0;
	int asz = 0;
	vector<kartya> bemenet;
	int n = jatekos.kezben.size();
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(jatekos.kezben.pop());
	}
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				++asz;
			}
			else
			{
				s = s + 10;
			}
		}
	}
	while (s > BLACKJACK && asz>0)
	{
		s = s - 10;
		asz--;
	}
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		jatekos.kezben.push(bemenet[i]);
	}
	if (s != BLACKJACK)
	{
		return false;
	}
	return true;
}
bool blackjack_oszto(oszt& oszto)
{
	int s = 0;
	int asz = 0;
	int n = oszto.kezben.size();
	vector<kartya> bemenet;
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(oszto.kezben.pop());
	}
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				++asz;
			}
			else
			{
				s = s + 10;
			}
		}
	}
	while (s > BLACKJACK && asz>0)
	{
		s = s - 10;
		asz--;
	}
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		oszto.kezben.push(bemenet[i]);
	}
	if (s != BLACKJACK)
	{
		return false;
	}
	return true;
}
int oszto_kartya_huz(oszt& oszto)
{
	int s = 0;
	int asz = 0;
	int n = oszto.kezben.size();
	vector<kartya> bemenet;
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(oszto.kezben.pop());
	}
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				asz++;
			}
			else
			{
				s += 10;
			}
		}
	}
	while (s > BLACKJACK && asz > 0)
	{
		s = s - 10;
		asz--;
	}
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		oszto.kezben.push(bemenet[i]);
	}
	return s;
}
int jatekos_vegso(jatekosok& jatekos)
{
	int s = 0;
	int asz = 0;
	int n = jatekos.kezben.size();
	vector<kartya> bemenet;
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(jatekos.kezben.pop());
	}
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				++asz;
			}
			else
			{
				s = s + 10;
			}
		}
	}
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		jatekos.kezben.push(bemenet[i]);
	}
	while (s > BLACKJACK && asz > 0)
	{
		s = s - 10;
		asz--;
	}
	return s;
}
bool oszto_kifutott(oszt& oszto)
{

	int s = 0;
	int asz = 0;
	int n = oszto.kezben.size();
	vector<kartya> bemenet;
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(oszto.kezben.pop());
	}	
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				++asz;
			}
			else
			{
				s += 10;
			}
		}
	}
	for (int i = bemenet.size() - 1; i >= 0; --i)
	{
		oszto.kezben.push(bemenet[i]);
	}
	while (s > BLACKJACK && asz>0)
		{
			s = s - 10;
			asz--;
		}
	if (s > BLACKJACK)
		return true;
	return false;
}
bool jatekos_kifutott(jatekosok& jatekos)
{

	int s = 0;
	int asz = 0;
	int n = jatekos.kezben.size();
	vector<kartya> bemenet;
	for (int i = 0; i < n; ++i)
	{
		bemenet.push_back(jatekos.kezben.pop());
	}
	for (int i = 0; i < bemenet.size(); ++i)
	{
		if (bemenet[i].ertek != 1 && bemenet[i].ertek <= 10)
		{
			s = s + bemenet[i].ertek;
		}
		else
		{
			if (bemenet[i].ertek == 1)
			{
				s = s + 11;
				++asz;
			}
			else
			{
				s += 10;
			}
		}
	}
	while (s > BLACKJACK && asz > 0)
		{
			s = s - 10;
			asz--;
		}
	for (int i = bemenet.size() - 1; i >= 0; --i)
		{
			jatekos.kezben.push(bemenet[i]);
		}
	if (s > BLACKJACK)
		return true;
	return false;
}
void BlackJack(jatekosok& jatekos,Stack<kartya,52>&pakli)
{

	int kor = 1;
	oszt oszto;
	jatekos.penz = 100;
	float tetel;
	string x;
	bool fuccs = false;
	bool jo = false;
	bool jatszok = true;
	while (jatekos.penz > 0 &&jatszok)
	{
		tetel = 0;
		jo = false;
		pakli.pop_all();
		cout << jatekos.nev << " -nek/nak " << jatekos.penz << " leje van" << endl;
		cout << "Szeretnel jatszani a "<<kor<<" korben " << jatekos.nev << " ? I/N" << endl;
		while (!jo)
		{
			getline(cin, x);
			if (x == "I" || x == "i")
			{
				cout << "Mekkora tetet szeretnel rakni?" << endl;
				cin >> tetel;
				cin.ignore();
				jo = true;
			}
			else
			{
				if (x == "N" || x == "n")
				{
					jo = true;
					jatszok = false;
				}
				else
				{
					cout << "Nem jo ertek, csak I/N lehet" << endl;
				}
			}
		}
		if (jatszok)
		{
			if (tetel > jatekos.penz || tetel==0)
			{
				while (tetel > jatekos.penz || tetel==0)
				{
					cout << "Mondj egy uj tetet az elozo teted nem jo " <<jatekos.penz <<" lejed van. " << endl;
					cin >> tetel;
					cin.ignore();
				}
			}
			system("CLS");
			Pakli_letrehoz(pakli);
			Keverd_pakli(pakli, 0);
			elsokor(jatekos, oszto, pakli);
			if (blackjack_jatekos(jatekos))
			{
				cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
				cout << endl << endl;
				ir_jatekos(jatekos);
				cout << endl;
				cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
				cout << endl << endl;
				ir_oszto(oszto, false);
				cout << endl;
				cout << "Nyerted a kort, Blackjack" << endl;
				jatekos.penz = jatekos.penz + (tetel * 1.5);
				jatekos.pontok++;

			}
			else
			{
				if (blackjack_oszto(oszto))
				{
					cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
					cout << endl << endl;;
					ir_jatekos(jatekos);
					cout << endl;
					cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
					cout << endl << endl;
					ir_oszto(oszto, false);
					cout << endl;
					_getch();
					system("CLS");
				}
				else
				{
					Keverd_pakli(pakli, 4);
					jo = false;
					fuccs = false;
					while (!jo)
					{
						cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
						cout << endl << endl;;
						ir_jatekos(jatekos);
						cout << endl;
						cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
						cout << endl << endl;
						ir_oszto(oszto, true);
						cout << endl << endl;
						cout << "Szeretnel lapot huzni I/N" << endl;
						getline(cin, x);
						cin.clear();
						system("CLS");
						if (x == "I" || x == "i")
						{
							jatekos.kezben.push(pakli.pop());
						}
						else
						{
							if (x == "N" || x == "n")
							{
								jo = true;
							}
							else
							{
								cout << "Nem jo ertek, csak I/N lehet" << endl;
							}
						}
						if (jatekos_kifutott(jatekos))
						{
							cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
							cout << endl << endl;;
							ir_jatekos(jatekos);
							cout << endl;
							cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
							cout << endl << endl;
							ir_oszto(oszto, true);
							cout << endl;
							cout << "Fuccsot kaptal, a kort az oszto nyerte" << endl << endl;
							jatekos.penz = jatekos.penz - tetel;
							oszto.pontok++;
							jo = true;
							fuccs = true;
						}
						else
						{
							if (jatekos_vegso(jatekos) == 21)
							{
								cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
								cout << endl << endl;;
								ir_jatekos(jatekos);
								cout << endl;
								cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
								cout << endl << endl;
								ir_oszto(oszto, true);
								jo = true;
								system("cls");
							}
						}
					}
					Keverd_pakli(pakli, jatekos.kezben.size()+2);
					if (!fuccs)
					{
						cout << "Az oszto felfedi kartyajat: ";
						cout << endl << endl;
						cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
						cout << endl << endl;;
						ir_jatekos(jatekos);
						cout << endl;
						cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
						cout << endl << endl;
						ir_oszto(oszto, false);
						_getch();
						system("CLS");
						cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
						cout << endl << endl;;
						ir_jatekos(jatekos);
						cout << endl;
						cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
						cout << endl << endl;
						ir_oszto(oszto, false);
						if (oszto_kartya_huz(oszto) >= 17)
						{
							cout << "Az oszto nem huzz kartyat" << endl;
							_getch();
							system("cls");
						}
						else
							while ((oszto_kartya_huz(oszto)) < 17)
							{
								system("CLS");
								oszto.kezben.push(pakli.pop());
								cout << jatekos.nev << " kartyainak osszege: " << jatekos_vegso(jatekos) << " " << endl;
								cout << endl << endl;;
								ir_jatekos(jatekos);
								cout << endl;
								cout << "Az oszto kartyainak osszege " << oszto_kartya_huz(oszto) << endl;
								cout << endl << endl;
								ir_oszto(oszto, false);
								_getch();
							}
						if (oszto_kifutott(oszto))
						{
							cout << "Az oszto fuccsott kapott, a kort " << jatekos.nev << " nyerte" << endl;
							jatekos.penz = jatekos.penz + tetel;
							jatekos.pontok++;
						}
						else
						{
							if (jatekos_vegso(jatekos) > oszto_kartya_huz(oszto))
							{
								jatekos.pontok++;
								jatekos.penz = jatekos.penz + tetel;
								cout << "A kort " << jatekos.nev << " nyerte" << endl;
							}
							else
							{
								if (jatekos_vegso(jatekos) < oszto_kartya_huz(oszto))
								{
									oszto.pontok++;
									jatekos.penz = jatekos.penz - tetel;
									cout << "A kort az oszto nyerte" << endl;
								}
								else
								{
									if (jatekos_vegso(jatekos) == oszto_kartya_huz(oszto))
									{
										cout << "Dontetlen" << endl;
									}
								}
							}
						}
					}
				}
			}
			_getch();
			system("CLS");
			cout << jatekos.nev << " " << jatekos.pontok << " kort nyert" << endl;
			cout << "Az oszto" << " " << oszto.pontok << " kort nyert" << endl;
			kor++;
			jatekos.kezben.pop_all();
			oszto.kezben.pop_all();
			_getch();
			system("CLS");
		}
	}
	system("CLS");
	cout << "A jateknak vege" << endl;
	return ;
}
int main()
{
	string x;
	bool ok = false;
	SetConsoleOutputCP(CP_UTF8); 
	cout << "Szeretned el olvasni a szabalyzatot? I/N" << endl;
	while (!ok)
	{
		getline(cin, x);
		if (x == "I" || x == "i")
		{
			system("CLS");
			szabalyzat();
			_getch();
			ok = true;
		}
		else
		{
			if (x == "N" || x == "n")
			{
				ok = true;
			}
			else
			{
				cout << "Nem jo valasz, csak I/N lehet" << endl;

			}
		}
	}
	system("CLS");
	cout << "Kezdodik a jatek" << endl;
	jatekosok jatekos;
	Stack<kartya, 52>pakli;
	cout << "Kerem a jatekos nevet: " << endl;
	getline(cin, jatekos.nev);
	system("CLS");
	BlackJack(jatekos, pakli);
	return 0;
}
