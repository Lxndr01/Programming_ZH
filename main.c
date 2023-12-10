#define _CRT_NO_SECURE_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// #define PART2
// #define PART3
// #define PART4
// #define PART5
// #define PART6

struct ceg
{
	char telephely[31];
	unsigned int dolgozok;
	double ertekeles;
	unsigned int epuletek;
};

// 1. feladat ->
struct ceg* kellmemoria(int number_of_companies) {
	struct ceg* cegek = (struct ceg*)malloc(sizeof(struct ceg) * number_of_companies);
	return cegek;
}

void torol(struct ceg* cegek) {
	free(cegek);
}


void cegEgyetBeker(struct ceg* ceg) {
	scanf("%s %u %lf %u", ceg->telephely, &ceg->dolgozok, &ceg->ertekeles, &ceg->epuletek);
}

void kiirtomb(struct ceg* cegek, int number) {
	for (int i = 0; i < number; i++) {
		printf("%s %u %lf %u'\n", cegek[i].telephely, cegek[i].dolgozok, cegek[i].ertekeles, cegek[i].epuletek);
	}
}
// <- 1. feladat 

// 2. feladat ->
unsigned int feladat2(struct ceg* cegek, int number) {
	unsigned int counter = 0;
	for (int i = 0; i < number; i++) {
		if (cegek[i].dolgozok < 714)
			counter++;
	}
	return counter;
}

// <- 2. feladat 

// 3. feladat ->
void feladat3(const char* filename) {
	FILE* file = fopen(filename, "r");

	struct ceg cegek[4];
	for (int i = 0; i < 4; i++) {
		fscanf(file, "%s %u %lf %u", cegek[i].telephely, &cegek[i].dolgozok, &cegek[i].ertekeles, &cegek[i].epuletek);
	}
	fclose(file);

	for (int i = 0; i < 4; ++i) {
		printf("%s %u %.2lf %u\n", cegek[i].telephely, cegek[i].dolgozok, cegek[i].ertekeles, cegek[i].epuletek);
	}

	// Kisebb dolgozószámú cégek számlálása
	int kisebb_dolgozok_szama = 0;
	for (int i = 0; i < 4; ++i) {
		if (cegek[i].dolgozok < 714) {
			kisebb_dolgozok_szama++;
		}
	}
	printf("%d", kisebb_dolgozok_szama);
}

// <- 3. feladat 

// 4. feladat ->
void fajlba(struct ceg* cegek, int number, const char* filename) {
	FILE* file = fopen(filename, "w");

	for (int i = 0; i < number; i++) {
		fprintf(file, "%u\n", cegek[i].dolgozok);
	}
	fclose(file);
}

// <- 4. feladat 

// 5. feladat ->
struct cseretarolo {
	struct ceg* ceg1;
	struct ceg* ceg2;
};

void kigyujtes(struct ceg* tomb, int index1, int index2, struct cseretarolo* tarolo) {
	tarolo->ceg1 = &tomb[index1];
	tarolo->ceg2 = &tomb[index2];
}

void modosito(struct cseretarolo* tarolo) {
	unsigned int temp = tarolo->ceg1->epuletek;
	tarolo->ceg1->epuletek = tarolo->ceg2->epuletek;
	tarolo->ceg2->epuletek = temp;
}


// <- 5. feladat 

// 6. feladat ->
struct ceg* nagytombcsinalo(struct ceg* tomb1, int meret1, struct ceg* tomb2, int meret2) {
	// Számítjuk ki az új tömb méretét
	int ujMeret = meret1 + meret2;

	// Foglaljuk le az új tömböt az összes elem tárolására
	struct ceg* ujTomb = (struct ceg*)malloc(ujMeret * sizeof(struct ceg));

	if (ujTomb == NULL) {
		printf("Nem sikerult helyet foglalni az uj tombnek.\n");
		return NULL;
	}

	// Másoljuk az első tömböt az új tömb elejére
	memcpy(ujTomb, tomb1, meret1 * sizeof(struct ceg));

	// Másoljuk a második tömböt az első után az új tömbbe
	memcpy(ujTomb + meret1, tomb2, meret2 * sizeof(struct ceg));

	return ujTomb;
}

// <- 6. feladat 

int main()
{
	printf("\n--START OF PART1--\n");
	unsigned int meret;
	scanf("%u", &meret);
	struct ceg* tomb;
	tomb = kellmemoria(meret);
	{
		unsigned int i;
		for (i = 0; i < meret; i++)
			cegEgyetBeker(&tomb[i]);
	}
	kiirtomb(tomb, meret);

	printf("\n--END OF PART1--\n");


#ifdef PART2
	printf("\n--START OF PART2--\n");
	unsigned int szamlalas = feladat2(tomb, meret);
	printf("%u\n", szamlalas);
	printf("\n--END OF PART2--\n");
#endif

	char fajlnev3[50];
	scanf("%s", fajlnev3);
#ifdef PART3
	printf("\n--START OF PART3--\n");
	feladat3(fajlnev3);
	printf("\n--END OF PART3--\n");
#endif

	char fajlnev4[50];
	scanf("%s", fajlnev4);
#ifdef PART4
	printf("\n--START OF PART4--\n");
	fajlba(tomb, meret, fajlnev4);
	printf("Fajl tartalma:\n");
	FILE* fp = fopen(fajlnev4, "r");
	char buffer[255];
	if (fp)
	{
		while (fgets(buffer, 255, fp)) {
			printf("%s", buffer);
		}
		fclose(fp);
	}
	printf("\n--END OF PART4--\n");
#endif

	int index1, index2;
	scanf("%d %d", &index1, &index2);
#ifdef PART5
	printf("\n--START OF PART5--\n");
	// Lemásoljuk, hogy ne az eredetit babráljuk
	struct ceg* masolat = kellmemoria(meret);
	unsigned int i;
	for (i = 0; i < meret; i++)
		masolat[i] = tomb[i];
	struct cseretarolo gyujtemeny;
	kigyujtes(masolat, index1, index2, &gyujtemeny);
	modosito(&gyujtemeny);
	printf("Modositas utan:\n");
	kiirtomb(masolat, meret);
	torol(masolat);
	printf("\n--END OF PART5--\n");
#endif

	unsigned int masikmeret;
	scanf("%u", &masikmeret);
#ifdef PART6
	printf("\n--START OF PART6--\n");
	{
		// Lemásoljuk, hogy ne az eredetit babráljuk
		struct ceg* egyiktomb = kellmemoria(meret);
		unsigned int i;
		for (i = 0; i < meret; i++)
			egyiktomb[i] = tomb[i];
		struct ceg* masiktomb = kellmemoria(masikmeret);
		for (i = 0; i < masikmeret; i++)
			cegEgyetBeker(&masiktomb[i]);
		struct ceg* nagytomb = nagytombcsinalo(egyiktomb, meret, masiktomb, masikmeret);
		kiirtomb(nagytomb, meret + masikmeret);
		torol(egyiktomb);
		torol(masiktomb);
		torol(nagytomb);
	}
	printf("\n--END OF PART6--\n");
#endif

	printf("\n--START OF PART1--\n");
	torol(tomb);
	printf("\n--END OF PART1--\n");

	return 0;
}