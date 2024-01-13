#ifndef STRUCTURES_H // if not defined => prevent it from being loaded more than once
#define STRUCTURES_H
/*
- **id(int) * *
-**nom(string) * *
-liste_med(array of med IDs)
- liste_pat(array of patient IDs)
*/

struct Service {
	int id;
	char nom[20];
};

struct Certificat {
	int id;
	char status[10];
	char pat_name[100];
	int pat_id;
	int med_id;
	char cause[200];
	char date[200];
	char med_nom[30];
};


struct Rendezvous {
	int id;
	char date[200];
	char nom_pat[30];
	char nom_med[30];
	int id_pat;
	int id_med;
	char status[10];
};



struct Admin {
	char nom[30];
	char mdp[30];
};

struct Medecin {
	int medID;
	char nom[30];
	char ddn[20];
	char genre;
	// char signature[50];
	int servID[30];
	char specialite[50];
};



struct Patient {
	int id;
	char nom[30];
	char ddn[20];
	char genre;
	char desc[500];
	int servIDs[30];
	int rendivIDs[100];
	int ordIDs[100];
	int medIDs[30];
	int certIDs[30];
};

struct Ordonnance {
	// ord := id, name, sig de medecin; id, nom, liste de medicaments;
	int id;
	char nom_med[30];
	char id_pat;
	char nom_pat[30];
	char medicaments[200];
};


// put Struct in file
// size_t => C type for the size of a structure
// example:
// 	 struct_to_file(&test, sizeof(struct Admin), "admin.dat");
// 	 struct Admin test = { "test1", "test2" };
// tested: works for structures containing arrays!
void struct_to_file(void* structure, size_t size, char source[30]) {
	FILE* file = NULL;
	fopen_s(&file, source, "wb");
	fwrite(structure, size, 1, file);
	fclose(file);
}

// example
// 	struct Admin testLire;
// 	file_to_struct(&testLire, sizeof(struct Admin), "admin.dat");
// printf("%s - %s\n", testLire.nom, testLire.mdp);



void file_to_struct(void* structure, size_t size, char source[30]) {
	FILE* file = NULL;
	fopen_s(&file, source, "rb");
	fread(structure, size, 1, file);
	fclose(file);
}

void saisir(char *chaine[]) {
	do {
		scanf_s("%s", chaine, (unsigned)sizeof(chaine));
		if (strlen(chaine) != 0) {
			break;  // Exit the loop if an empty string is entered
		}

	} while (1);  // Infinite loop; use a break statement to exit when needed
}




#endif