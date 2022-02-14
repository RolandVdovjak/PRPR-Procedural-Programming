/*********************************************************************************************
										FIIT STU
Predmet : Procedurálne programovanie
Semester : ZS 2020 / 2021
Autor : Roland Vdovják

										PROJEKT 2

Funkcia programu : Zoo
**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct zvierata {			//definovanie struktury
	char meno[51];
	char druh[31];
	int vyska;
	float vaha;
	long datnar;
	long datkrm;
	char menoo[51];
	struct zvierata* dalsie;
} ZVIERATA;

int namale(char * string1, char * string2) {			//z velkych pismen na male v stringu
	char pom[51];
	int i = 0, chyba = 0;

	strcpy(pom, string1);			// aby nemenilo zaznami v strukture

	while (pom[i] != '\0') {
		pom[i] = tolower(pom[i]);
		i++;
	}
	while (string2[i] != '\0') {
		string2[i] = tolower(string2[i]);
		i++;
	}
	if (strcmp(pom, string2) != 0) chyba++;
	
	return chyba;
}

ZVIERATA* n(FILE* ztxt, ZVIERATA* zoznam, int *pocetzv) { //nacitanie udajov do struktury
	ZVIERATA* doczoz = NULL, *doc2zoz;
	char riadok[51];
	int index = -0, pocet = +0;
		
	if (ztxt != NULL) {										//ak je subor neprazdny
		doczoz = (ZVIERATA*)malloc(sizeof(ZVIERATA));
		while (fgets(riadok, 51, ztxt) != NULL) {
			
			if (strcmp(riadok, "$$$\n") == 0) pocet++;		
			else {
				switch (index){								//nacitanie do struktury
				case 0:
					strcpy(doczoz->meno, riadok);
					break;

				case 1:
					strcpy(doczoz->druh, riadok);
					break;

				case 2:
					doczoz->vyska = atoi(riadok);
					break;

				case 3:
					doczoz->vaha = atof(riadok);
					break;

				case 4:
					doczoz->datnar = atol(riadok);
					break;

				case 5:
					doczoz->datkrm = atol(riadok);
					break;

				case 6:
					strcpy(doczoz->menoo, riadok);
					break;

				}
				if (index == 6) {
				doczoz->dalsie = NULL;
				
				if (zoznam != NULL) {		//ak je struktura prazdna, ide riadok 100 a nacita sa prvy prvok
						doc2zoz = zoznam;		//uz nacitane sa prilepi do docasneho

						while (doc2zoz->dalsie != NULL) {		//ide na koniec v strukture
							doc2zoz = doc2zoz->dalsie;			
						}
						doc2zoz->dalsie = doczoz;			//nacitany zaznam sa priradi na koniec docasneho
					}
					else zoznam = doczoz;	
					
					doczoz = (ZVIERATA*)malloc(sizeof(ZVIERATA));	//alokacia pre dalsi docasny zoznam
					index = 0;
				}
				else index++;
			}
		}

		free(doczoz);
		doczoz = NULL;

		printf("Nacitalo sa %d zaznamov.\n", pocet);
		*pocetzv = pocet;									//pocet zvierat v zoo
		return zoznam;
	}
	else printf("Subor je prazdny\n");
}

void v(ZVIERATA* zoznam) {				//vypis
	int i = 0;
	
	if (zoznam != NULL) {
		while (zoznam != NULL) {
			i++;
			printf("%d.\n", i);
			printf("Meno: %s", zoznam->meno);
			printf("Druh: %s", zoznam->druh);
			printf("Vyska: %d\n", zoznam->vyska);
			printf("Vaha: %g\n", zoznam->vaha);
			printf("Datum narodenia: %ld\n", zoznam->datnar);
			printf("Datum posledneho krmenia: %ld\n", zoznam->datkrm);
			printf("Meno osetrovatela: %s", zoznam->menoo);
			zoznam = zoznam->dalsie;
		}
	}
	else printf("Zoznam nebol vytvoreny.\n");
}

ZVIERATA* p(ZVIERATA* zoznam, int *pocetzv) {				//pridanie zvierata
	int cislo, poc = 1;
	char nmeno[51];
	ZVIERATA* doczoz = NULL, *novyzoz;

	if (zoznam != NULL) {
		printf("Zadaj poziciu pre novy zaznam.\n");
		scanf("%d", &cislo);							//nacitanie pozicie

		doczoz = (ZVIERATA*)malloc(sizeof(ZVIERATA));

		printf("Zadaj meno.\n");						//nacitanie udajov
		getchar();
		fgets(doczoz->meno, 51, stdin);
		printf("Zadaj druh.\n");
		fgets(doczoz->druh, 31, stdin);
		printf("Zadaj vysku.\n");
		getchar();
		scanf("%d", &doczoz->vyska);
		printf("Zadaj vahu.\n");
		scanf("%f", &doczoz->vaha);
		printf("Zadaj datum narodenia.\n");
		scanf("%ld", &doczoz->datnar);
		printf("Zadaj datum posledneho krmenia.\n");
		scanf("%ld", &doczoz->datkrm);
		printf("Zadaj meno osetrovatela.\n");
		getchar();
		fgets(doczoz->menoo, 51, stdin);
		doczoz->dalsie = NULL;

		novyzoz = zoznam;
			
		if (cislo <= *pocetzv) {			//ak je nacitana pozicia vacsia ako 1	
			if (cislo == 1) {					//prvy zaznam sa prepise
				doczoz->dalsie = zoznam;
				zoznam = doczoz;
			}
			for (int i = 1; i <= cislo; i++) {			//prepis zaznamov
				if (cislo == i + 1) {						//pozicia pred tou, kde sa ma zaznam zapisat
						doczoz->dalsie = novyzoz->dalsie;		//cely zaznam z dalsieho prvku sa premiestnil do nacitaneho zoznamu do dalsieho
						novyzoz->dalsie = doczoz;				//povodny zvysok z zoznamu s pridanym prvom sa prida do povodneho zvysku
						break;
					}
					novyzoz = novyzoz->dalsie;
				}
		}
		else {
			for (int i = 1; i < *pocetzv; i++) novyzoz = novyzoz->dalsie;		//ak sa nacitana pozicia rovna 1, zapise sa do dalsieho prvu povodny zoznam
			novyzoz->dalsie = doczoz;
		}
	}
	

	*pocetzv += 1;
	return zoznam;
}

ZVIERATA* z(ZVIERATA* zoznam, int* pocetzv) {		//zmazanie
	ZVIERATA* doczoz, *doczoz2 = NULL;
	char nmeno[51];
	int i = 1;

	printf("Zadaj meno.\n");
	getchar();
	fgets(nmeno, 51, stdin);
	
	doczoz = zoznam;
	
	while ((namale(&(doczoz->meno), nmeno) != 0) && (doczoz->dalsie != NULL)) {		//ak sa mena rovnaju, tak sa zmaze
		doczoz2 = doczoz;
		doczoz = doczoz->dalsie;
	}
	doczoz2->dalsie = doczoz->dalsie;

	return zoznam;
}

void h(ZVIERATA* zoznam) {		//vypis podla datumu krmenia
	int i = 0;
	long nacitdat;

	printf("Zadaj datum.\n");
	scanf("%ld", &nacitdat);

	if (zoznam != NULL) {
		while (zoznam != NULL) {
			if (zoznam->datkrm < nacitdat) {		//ak je datum ostro mensi, tak sa vypie zaznam
				i++;
				printf("%d.\n", i);
				printf("Meno: %s", zoznam->meno);
				printf("Druh: %s", zoznam->druh);
				printf("Vyska: %d\n", zoznam->vyska);
				printf("Vaha: %g\n", zoznam->vaha);
				printf("Datum narodenia: %ld\n", zoznam->datnar);
				printf("Datum posledneho krmenia: %ld\n", zoznam->datkrm);
				printf("Meno osetrovatela: %s", zoznam->menoo);
			} 
			zoznam = zoznam->dalsie;
		}
		if (i == 0) printf("Vsetky zvierata boli k datumu %ld nakrmene\n", nacitdat);
	}
	else printf("Zoznam nebol vytvoreny.\n");
}

ZVIERATA* a(ZVIERATA* zoznam, int pocetzv) {		//aktualizacia datumu
	ZVIERATA* doczoz;
	char nmeno[51];
	long ndat;

	doczoz = (ZVIERATA*)malloc(sizeof(ZVIERATA));

	printf("Zadaj meno zvierata.\n");
	getchar();
	fgets(nmeno, 51, stdin);
	printf("Zadaj datum krmenia.\n");
	scanf("%ld", &ndat);

	doczoz = zoznam;

	while ((strcmp(doczoz->meno, nmeno) != 0) && (doczoz != NULL)) {		//najde sa zaznam v zozname s rovnakym menom
		doczoz = doczoz->dalsie;
	}
	doczoz->datkrm = ndat; //prepis

	nmeno[strlen(nmeno) - 1] = '\0';
	printf("Zviera s menom %s bolo naposledy nakrmene dna %ld.\n", nmeno, ndat);

	
	return zoznam;
}

void vypisUI(){

	system("clear");
	printf("\n  Stlacte jednotlive pismenka na uskutocnenie ich funkcie.\n");
	printf("\n\tn - nacitanie do struktury ");
	printf("\n\tv - vypis struktury ");
	printf("\n\tp - pridanie zvierata ");
	printf("\n\tz - zmazanie zaznamu ");
	printf("\n\th - vypis zvierat s datumom krmenia mensim ako nacitany datum ");
	printf("\n\ta - zmen datum krmenia ");
	printf("\n\tk - koniec ");
	printf("\n\ti - informacie (MENU)\n\n");
}	

int main(void) {
	char c, d[10];
	int pocetzvierat;
	FILE* subor = NULL, *doc;
	ZVIERATA* struktura = NULL;

	subor = fopen("zvierata.txt", "r");

	vypisUI();

	do {
		c = getchar();
		switch(c){

		case 'i':
			vypisUI();
			break;
		case 'n':
			if ((struktura = n(subor, struktura, &pocetzvierat)) != NULL)
			break;
		case 'v':
			v(struktura);
			break;
		case 'p':
			struktura = p(struktura, &pocetzvierat);
			break;
		case 'z':
			struktura = z(struktura, &pocetzvierat);
			break;
		case 'h':
			h(struktura);
			break;
		case 'a':
			struktura = a(struktura, &pocetzvierat);
			break;
		case 'k':
			if (struktura != NULL) {
				while (struktura != NULL) {		//uvolnenie pamate
					doc = struktura;
					struktura = struktura->dalsie;
					free(doc);
				}
			}
			break;
		}


	} while (c != 'k');
	fclose(subor);

	return 0;
}