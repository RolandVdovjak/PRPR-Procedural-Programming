/*******************************************************************
							  FIIT STU
Predmet: Procedurálne programovanie
Semester: ZS 2020/2021
Autor: Roland Vdovják

							 ZADANIE 1

Funkcia programu: Praca s databazou pacientov
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int overRodneCislo(char riadok[]) {
	int i = 0, chyba = 0;
	long long rodne_c = 0;

	while ((riadok[i] != '\n') && (i < 13) && (chyba == 0)) {
		if (riadok[i] >= '0' && riadok[i] <= '9');
		else chyba++;
		i++;
	}
	//1954-2020  =>  54-99 00-20  =>  00-19 || 60-99 || 20 || 54-59 
	if (
		(((riadok[0] >= '0') && (riadok[0] <= '1')) || ((riadok[0] >= '6') && (riadok[0] <= '9'))) ||
		(((riadok[0] == '2') && (riadok[1] == '0')) || ((riadok[0] == '5') && (riadok[1] >= '4')))
		);
	else chyba++;

	//01-12 || 51-62  =>  01-09 || 51-59 || 10-12 || 60-62
	if (
		(((riadok[2] == '0') && (riadok[3] >= '1')) || ((riadok[2] == '5') && (riadok[3] >= '1'))) ||
		(((riadok[2] == '1') && (riadok[3] <= '2')) || ((riadok[2] == '6') && (riadok[3] <= '2')))
		);
	else chyba++;

	//01-31 => 01-09 || 30-31 || 10-29
	if (
		((riadok[4] == '0') && (riadok[5] >= '1')) || ((riadok[4] == '3') && (riadok[5] <= '1')) || ((riadok[4] == '1') || (riadok[4] == '2'))
		);
	else chyba++;

	if (i != 10) chyba++;
	if (chyba == 0) rodne_c = strtoll(riadok, NULL, 10);

	if ((rodne_c % 11 != 0) || (chyba != 0)) return 0;
	else return 1;

}

int overDatum(char datum[]) {
	int chyba, rok, i = 0;
	chyba = 0;

	while ((datum[i] != '\n')  && (chyba == 0)) {
		if (datum[i] >= '0' && datum[i] <= '9');
		else chyba++;
		if (i == 8) chyba++;
		i++;
	}

	if (i != 8) chyba++;

	if (
		(((datum[4] == '0') && (datum[5] >= '1')) || ((datum[4] == '1') && (datum[5] <= '2'))) && // overenie mesiaca
		(((datum[0] == '2') && (datum[1] == '0') && (datum[2] <= '2')) || ((datum[0] == '1') && (datum[1] == '9'))) // overenie roka
		); else chyba++;

	if (datum[4] == '0')		//dni v mesiaci
		switch (datum[5]) {
		case '1': case '3': case '5': case '7': case '8':
			if ((datum[6] == '3' && datum[7] <= '1') || (datum[6] < '3'));
			else chyba++;
			break;

		case '2':
			rok = strtol(datum, NULL, 10) / 10000;
			if (rok % 4 == 0) if ((datum[6] == '2' && datum[7] <= '9') || (datum[6] <= '2'));
			else chyba++;
			else if ((datum[6] == '2' && datum[7] <= '8') || (datum[6] < '2'));
			else chyba++;
			break;

		case '4': case '6': case '9':
			if ((datum[6] == '3' && datum[7] == '0') || (datum[6] < '3'));
			else chyba++;
			break;
		}
	else if (datum[4] == '1')
		if (datum[5] == '0' || datum[5] == '2') if ((datum[6] == '3' && datum[7] <= '1') || (datum[6] < '3'));
		else chyba++;
		else if (datum[5] == '1') if ((datum[6] == '3' && datum[7] == '0') || (datum[6] < '3'));
		else chyba++;

	if (chyba == 0) return 1;
	else return 0;
}

void v(FILE **pacienti, char *c) {
	int index = 0, counter = 0, chyba = 0, i, c5_desbodka = 0;
	char riadok[52];
	long long rodne_c = 0;
	long rok = 0;


	if ((*pacienti = fopen(".\\pacienti1.txt", "r")) != NULL) {
		while (fgets(riadok, 52, *pacienti) != NULL) {		 //nacita max 50 znakov v riadku
			i = 0;
			chyba = 0;
			if (riadok[0] == '\n') { index = 0; counter++; }
			else index++;

			switch (index) {
			case 1:					//MENO
				while ((riadok[i] != '\n') && (i < 52) && (chyba == 0)) {
					if ((riadok[i] >= 'A' && riadok[i] <= 'Z') || (riadok[i] >= 'a' && riadok[i] <= 'z') || riadok[i] == ' ');
					else chyba++;
					i++;
					if (i == 52) {
						chyba++;
						index = 0;
					}
				}

				if (chyba > 0) printf("Nekorektne zadany vstup: meno- %s\n", riadok);
				else printf("meno priezvisko: %s", riadok);
				break;

			case 2:					//RODNE CISLO  (RR MM DD CCCC)

				if (overRodneCislo(riadok) == 0) {
					printf("Nekorektne zadany vstup: rodne cislo- %s \n", riadok);
					chyba++;
				}
				else printf("rodne cislo: %s", riadok);
				break;
				
			case 3:					//DIAGNOZA
				while ((riadok[i] != '\n') && (chyba == 0)) {
					if (i == 3) chyba++;
					i++;
				}
				if ((riadok[0] >= 'A') && (riadok[0] <= 'Z')); else chyba++;
				if ((riadok[1] >= '0') && (riadok[1] <= '9')); else chyba++;
				if ((riadok[2] >= '0') && (riadok[2] <= '9')); else chyba++;

				if (chyba > 0) printf("Nekorektne zadany vstup: diagnoza- %s\n", riadok);
				else printf("diagnoza: %s", riadok);
				break;

			case 4:					//VYSETRENIE
				while ((riadok[i] != '\n') && (chyba == 0)) {
					if (i == 51) chyba++;
					i++;
				}

				if (chyba > 0) printf("Nekorektne zadany vstup: vysetrenie- %s\n", riadok);
				else printf("vysetrenie: %s",riadok);
				break;

			case 5:					//VYSLEDOK
				while ((riadok[i] != '\n') && (chyba == 0)) {
					if ((riadok[i] >= '0' && riadok[i] <= '9') || (riadok[i] == '.' || riadok[i] == ','));
					else chyba++;
					if (riadok[i] == '.' || riadok[i] == ',') c5_desbodka = i;
					if (i == 9) chyba++;
					i++;
				}
				if (i - c5_desbodka <= 5); else chyba++;

				if (chyba > 0) printf("Nekorektne zadany vstup: vysledok- %s\n", riadok);
				else printf("vysledok: %s", riadok);
				break;

			case 6:					//DATUM (RRRR MM DD)
				
				if (overDatum(riadok) == 0) {
					printf("Nekorektne zadany vstup: datum- %s \n", riadok);
					chyba++;
				}
				else printf("datum: %s", riadok);
				break;

			case 0:
				printf("\n");
			}

			if (chyba > 0) {
				*c = 'k';
				break;
			}
		}
	}
	else {
		printf("Subor sa nepodarilo otvorit.\n");
		*c = 'k';
	}
}

void o(FILE **pacienti) {
	long nacitanydat = 0, dat;
	int index = 0, counter = 0, i;
	char riadok[52], nacitanydatstring[10];
	
	if (*pacienti != NULL) {
		scanf("%s", &nacitanydatstring);   //zadany datum

		strcat(nacitanydatstring, "\n");
		if (overDatum(nacitanydatstring) == 1) nacitanydat = strtol(nacitanydatstring, NULL, 10); else printf("Zadany zly datum.");


		if (overDatum(nacitanydatstring) == 1) {
			rewind(*pacienti);
			while (fgets(riadok, 52, *pacienti) != NULL) {
				if (riadok[0] == '\n') counter++;
			}rewind(*pacienti);


			long* datumy;
			datumy = malloc((counter + 1) * sizeof(long*));

			int* indexydatumov;
			indexydatumov = (int*)malloc((counter + 1) * sizeof(int*));

			char** diagnoza;
			diagnoza = (char*)malloc((counter + 1) * sizeof(char*));

			counter = 0;
			index = 0;
			i = 0;
			while (fgets(riadok, 52, *pacienti) != NULL) {
				if (riadok[0] == '\n') { index = 0; counter++; }
				else index++;
				if (index == 6) {
					dat = strtol(riadok, NULL, 10);
					if (dat < nacitanydat) {
						datumy[i] = dat;
						indexydatumov[i] = counter;
						i++;
					}
				}
			}rewind(*pacienti);

			counter = 0;
			index = 0;
			i = 0;


			while (fgets(riadok, 52, *pacienti) != NULL) {
				if (riadok[0] == '\n') { index = 0; counter++; }
				else index++;

				if ((counter == indexydatumov[i]) && (index == 3)) {
					diagnoza[i] = (char*)malloc(sizeof(char*) * 5);
					strcpy(diagnoza[i], riadok);
					i++;
				}
			}

			char pam[6];
			int pom, naj = 0, l;
			for (int j = 0; j < i; j++) {
				pom = 0;
				for (l = j; l < i; l++) {
					if (strcmp(diagnoza[l], diagnoza[j]) == 0) pom++;
					if (naj < pom) {
						strcpy(pam, diagnoza[l]);
						naj = pom;
					}
				}

			}
			printf("Najcastejsie vysetrovana diagnoza do %ld je %s", nacitanydat, pam);
			free(datumy);
			free(indexydatumov);
			for (int n = 0; n < i; n++) free(diagnoza[n]);
			free(diagnoza);
		}
		else printf("Chybne zadany datum.\n");

	}else printf("Neotvoreny subor.\n");
}

void n(FILE **pacienti, char ***MenoPriezvisko, char ***RodneCislo, char ***Diagnoza, char ***Vysetrenie, char ***Vysledok, char ***Datum, int *dlzkapola) {
	int counter = 0, index = 0;
	char riadok[52];

	if (*pacienti != NULL) {
	rewind(*pacienti);
	while (fgets(riadok, 52, *pacienti) != NULL) {
		if (riadok[0] == '\n') counter++;
	} rewind(*pacienti); 
	*dlzkapola = counter;
	
	if (*MenoPriezvisko) {
		for (int i = 1; i <= counter; i++) {
			free((*MenoPriezvisko)[i]);
			(*MenoPriezvisko)[i] = NULL;
			free((*RodneCislo)[i]);
			(*RodneCislo)[i] = NULL;
			free((*Diagnoza)[i]);
			(*Diagnoza)[i] = NULL;
			free((*Vysetrenie)[i]);
			(*Vysetrenie)[i] = NULL;
			free((*Vysledok)[i]);
			(*Vysledok)[i] = NULL;
			free((*Datum)[i]);
			(*Datum)[i] = NULL;
			
		}
		free(*MenoPriezvisko);
		*MenoPriezvisko = NULL;
		free(*RodneCislo);
		*RodneCislo = NULL;
		free(*Diagnoza);
		*Diagnoza = NULL;
		free(*Vysetrenie);
		*Vysetrenie = NULL;
		free(*Vysledok);
		*Vysledok = NULL;
		free(*Datum);
		*Datum = NULL;
	}

	*MenoPriezvisko = (char**)malloc((counter + 1) * sizeof(char*));
	*RodneCislo = (char**)malloc((counter + 1) * sizeof(char*));
	*Diagnoza = (char**)malloc((counter + 1) * sizeof(char*));
	*Vysetrenie = (char**)malloc((counter + 1) * sizeof(char*));
	*Vysledok = (char**)malloc((counter + 1) * sizeof(char*));
	*Datum = (char**)malloc((counter + 1) * sizeof(char*));

	
	counter = 0;
	while (fgets(riadok, 52, *pacienti) != NULL) {
		if (riadok[0] == '\n') { index = 0; counter++; }
		else index++;

		switch (index) {
		case 0: //prazdny riadok
			break;

		case 1: //MenoPriezvisko
			(*MenoPriezvisko)[counter] = (char*)malloc(52 * sizeof(char*));
			strcpy((*MenoPriezvisko)[counter], riadok);
			break;

		case 2: //RodneCislo
			(*RodneCislo)[counter] = (char*)malloc(12 * sizeof(char*));
			strcpy((*RodneCislo)[counter], riadok);
			break;

		case 3: //Diagnoza
			(*Diagnoza)[counter] = (char*)malloc(5 * sizeof(char*));
			strcpy((*Diagnoza)[counter], riadok);
			break;

		case 4: //Vysetrenie
			(*Vysetrenie)[counter] = (char*)malloc(52 * sizeof(char*));
			strcpy((*Vysetrenie)[counter], riadok);
			break;

		case 5: //Vysledok
			(*Vysledok)[counter] = (char*)malloc(11 * sizeof(char*));
			strcpy((*Vysledok)[counter], riadok);
			break;

		case 6: //Datum
			(*Datum)[counter] = (char*)malloc(10 * sizeof(char*));
			strcpy((*Datum)[counter], riadok);
			break;

		}
	} rewind(*pacienti);
	}
	else printf("Neotvoreny subor.\n");
}

void s(char **RodneCislo, char **Vysetrenie, char **Vysledok, int *dlzka ) {
	char nacitaneRC[12], riadok[52], pom[52], pom2[12];
	int i = 1;
		
		scanf("%s", &nacitaneRC);
		strcat(nacitaneRC, "\n");

		if (overRodneCislo(nacitaneRC) == 1) {
			do {
				if (strcmp(RodneCislo[i], nacitaneRC) == 0) {
					strcpy(pom, Vysetrenie[i]);
					pom[strlen(pom) - 1] = '\0';
					strcpy(pom2, nacitaneRC);
					pom2[strlen(pom2) - 1] = '\0';
					printf("Vysledky vysetreni, ktore boli vykonane pacientovi s rodnym cislom %s su nasledovne: \n%s: %s", pom2, pom, Vysledok[i]);
					break;
				}
				i++;
			} while (i <= dlzka);
		}
		else printf("Chybne zadane rodne cislo.\n");
}

void h(char ** RodneCislo, char ** Diagnoza, int * dlzka) {//RodneCislo, Diagnoza, dlzkapola)
	char nacitD[6], pom[12];
	long DnesnyDatum = 201112;																		//!!!!!! v pripade potreby treba aktualizovat dnesny datum
	int i = 1, j = 1, pocetludi = 0, d = dlzka, m = 0, z = 0;

	scanf("%s", nacitD);
	strcat(nacitD, "\n");

	int* indexy = NULL;
	indexy = (int*)malloc((d + 1) * sizeof(int*));

	while (i <= dlzka) {
		if (strcmp(Diagnoza[i], nacitD) == 0) {
			pocetludi++;
			indexy[j] = i;
			j++;
		}		// j - 1 = pocet ludi s ronvakou diagnozou
		i++;
	}

	long * RCM;
	RCM = malloc(j * sizeof(long*));
	long * RCZ;
	RCZ = malloc(j * sizeof(long*));

	for (int k = 1; k <= j-1; k++) {
		strcpy(pom, RodneCislo[indexy[k]]);
		if (pom[2] == '0' || pom[2] == '1') {
			RCM[m] = (strtoll(RodneCislo[indexy[k]], NULL, 10) / 10000);
			m++;		//m - 1 = pocet muzov
		}
		else if (pom[2] == '5' || pom[2] == '6'){
			RCZ[z] = (strtoll(RodneCislo[indexy[k]], NULL, 10) / 10000);
			z++;		//z - 1 = pocet zien
		}
	}

	int* VEKM;
	VEKM = malloc(j * sizeof(int*));
	int* VEKZ;
	VEKZ = malloc(j * sizeof(int*));
	
	int rok, arok, mes, ames, den, aden;

	arok = DnesnyDatum / 10000;
	ames = (DnesnyDatum / 100) - (arok * 100);
	aden = DnesnyDatum - (arok * 10000) - (ames * 100);

	for (i = 0; i < m; i++) {
		rok = (RCM[i] / 10000);
		mes = (RCM[i] / 100) - (rok * 100);
		den = RCM[i] - (100 * mes) - (10000 * rok);

		if ((mes < ames) || ((mes == ames) && (den < aden))) {
			if (rok / 10 >= 5) VEKM[i] = 100 - (rok - arok); else VEKM[i] = (arok - rok);
		}
		else if (rok / 10 >= 5) VEKM[i] = 100 - (rok - arok) - 1; else VEKM[i] = (arok - rok) - 1;
		
	}

	for (i = 0; i < z; i++) {
		rok = (RCZ[i] / 10000);
		mes = (RCZ[i] / 100) - (rok * 100) - 50;
		den = RCZ[i] - (100 * mes) - (10000 * rok);

		if ((mes < ames) || ((mes == ames) && (den < aden))) {
			if (rok / 10 >= 5) VEKZ[i] = 100 - (rok - arok); else VEKZ[i] = (arok - rok);
		}
		else if (rok / 10 >= 5) VEKZ[i] = 100 - (rok - arok) - 1; else VEKZ[i] = (arok - rok) - 1;
		
	}
	
	int doc, k;
	for (i = 0; i < m; i++) {
		for (k = 0; k < m; k++) {
			if (VEKM[k] > VEKM[i]) {
				doc = VEKM[i];
				VEKM[i] = VEKM[k];
				VEKM[k] = doc;
			}

		}
		
	}
	for (i = 0; i < z; i++) {
		for (k = 0; k < z; k++) {
			if (VEKZ[k] > VEKZ[i]) {
				doc = VEKZ[i];
				VEKZ[i] = VEKZ[k];
				VEKZ[k] = doc;
			}

		}

	}
	//for (i = 0; i < m; i++) printf("%d ", VEKM[i]);
	//for (i = 0; i < z; i++) printf("%d ", VEKZ[i]);

	int poc;
	printf("Muzi\n");
	for (i = 0; i < m; i++) {
		poc = 0;
		for (k = 0; k < m; k++) {
			if (VEKM[i] == VEKM[k]) poc++;

		}
		if (poc > 1) i += poc-1;
		printf("%d: %d\n", VEKM[i], poc);
	}
	
	printf("Zeny\n");
	for (i = 0; i < z; i++) {
		poc = 0;
		for (k = 0; k < z; k++) {
			if (VEKZ[i] == VEKZ[k]) poc++;

		}
		if (poc > 1) i += poc - 1;
		printf("%d: %d\n", VEKZ[i], poc);
	}

	free(indexy);
	free(RCM);
	free(RCZ);
	free(VEKM);
	free(VEKZ);
}

void p(FILE **pacienti, char **RodneCislo, char **Vysetrenie, char ***Vysledok, char ***Datum, char *dlzka) {
	char nacitRC[10], nacitVYS[52], nacitDT[8] ;


}

void z() {

}

int main(void){
	
	char c, **MenoPriezvisko = NULL, **RodneCislo = NULL, **Diagnoza = NULL, **Vysetrenie = NULL, **Vysledok = NULL, **Datum = NULL;
	int dlzkapola;
	FILE *pacienti = NULL;

	printf("\t\tZADAJTE PRISLUSNE PISMENKO\n\n");

	do {
		c = getchar();
			switch (c) {
				case 'v':
					v(&pacienti, &c);
					break;

				case 'o':
					o(&pacienti);
					break;

				case 'n':
					n(&pacienti, &MenoPriezvisko, &RodneCislo, &Diagnoza, &Vysetrenie, &Vysledok, &Datum, &dlzkapola);
					break;

				case 's':
					if (MenoPriezvisko != NULL) s(RodneCislo, Vysetrenie, Vysledok, dlzkapola);
					else printf("Polia nie su vytvorene.\n");
					break;

				case 'h':
					if (MenoPriezvisko != NULL) h(RodneCislo, Diagnoza, dlzkapola);
					else printf("Polia nie su vytvorene.\n");
					break;

				case 'p':
					if (MenoPriezvisko != NULL) p(&pacienti, RodneCislo, Vysetrenie, &Vysledok, &Datum, dlzkapola);
					else printf("Polia nie su vytvorene.\n");
					break;

				case 'z':
					z();
					break;

				case 'k':
				if (pacienti != NULL) fclose(pacienti);
				if (MenoPriezvisko) {
					for (int i = 1; i <= dlzkapola; i++) {
						free(MenoPriezvisko[i]);
						MenoPriezvisko[i] = NULL;
						free(RodneCislo[i]);
						RodneCislo[i] = NULL;
						free(Diagnoza[i]);
						Diagnoza[i] = NULL;
						free(Vysetrenie[i]);
						Vysetrenie[i] = NULL;
						free(Vysledok[i]);
						Vysledok[i] = NULL;
						free(Datum[i]);
						Datum[i] = NULL;

					}
					free(MenoPriezvisko);
					MenoPriezvisko = NULL;
					free(RodneCislo);
					RodneCislo = NULL;
					free(Diagnoza);
					Diagnoza = NULL;
					free(Vysetrenie);
					Vysetrenie = NULL;
					free(Vysledok);
					Vysledok = NULL;
					free(Datum);
					*Datum = NULL;
				}
					break;
			
			}
	} while (c != 'k');
	
	
	return 0;
}