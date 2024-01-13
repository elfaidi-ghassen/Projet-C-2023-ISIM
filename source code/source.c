#include <stdio.h>
#include <string.h>
#include "structures.h"
#include <stdlib.h>
#include "hpdf.h"
#include <time.h>
#include <locale.h> // encodage


#define invalide -858993460 


void efface_espace(char* str) {
	int i, j;
	for (i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ') {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';  
}



void afficher_services(void) {

	setlocale(LC_ALL, "");
	int i = 0;
	int n;
	struct Service service;
	struct Service services[100];
	FILE* file = NULL;
	fopen_s(&file, "services.dat", "rb");
	while (fread(&service, sizeof(struct Service), 1, file) == 1) {
		services[i] = service;
		i++;
	}
	n = i;
	printf("Nom\t\t\tID\n");
	for (i = 0; i < n; i++) {
		printf("%-12s\t\t%d\n", services[i].nom, services[i].id);

	}
	printf("\n\n");
	fclose(file);
}
void afficher_patients(void) {
	struct Patient patients[100];
	struct Patient pat;
	int i = 0;
	FILE* file = NULL;
	fopen_s(&file, "patients.dat", "rb");
	while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
		patients[i] = pat;
		i++;
	}
	int n = i;

	printf("=======================================================================================================\n");
	printf("Nom\t\tID\t\tDDN\t\tGenre\t\tServices et Medecins\n");
	printf("=======================================================================================================\n");



	for (i = 0; i < n; i++) {
		//printf("Nom: %s / id: %d / description: %s / ddn: %s / services: ", patients[i].nom, patients[i].id, patients[i].desc, patients[i].ddn);
		printf("%-8s\t%04d\t\t%-8s\t\t%-8c\t\t", patients[i].nom, patients[i].id, patients[i].ddn, patients[i].genre);

		printf(" svs: ");

		for (int j = 0; j < sizeof(patients[i].servIDs) / sizeof(patients[i].servIDs[0]); j++) {
			if (patients[i].servIDs[j] == invalide) break;
			printf("#%d ", patients[i].servIDs[j]);
		}
		printf(" md: ");
		for (int j = 0; j < sizeof(patients[i].medIDs) / sizeof(patients[i].medIDs[0]); j++) {
			if (patients[i].medIDs[j] == invalide) break;
			printf("#%d ", patients[i].medIDs[j]);
		}
		printf("\n");
		// new

		
		
	}
	printf("=======================================================================================================\n");

	printf("\n");
	fclose(file);

}
void afficher_medecins(void) {
	struct Medecin medecins[100];
	struct Medecin med;
	int i = 0;
	FILE* file = NULL;
	fopen_s(&file, "medecins.dat", "rb");
	while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
		medecins[i] = med;
		i++;
	}
	int n = i;
	printf("=======================================================================================================\n");
	printf("Nom\t\tID\t\tspecialite\t\tDDN\t\tServices(IDs)\n");
	printf("=======================================================================================================\n");

	for (i = 0; i < n; i++) {

		printf("%-8s\t%04d\t\t%-8s\t\t%-8s\t", medecins[i].nom, medecins[i].medID, medecins[i].specialite, medecins[i].ddn);
		for (int j = 0; j < sizeof(medecins[i].servID) / sizeof(medecins[i].servID[0]); j++) {
			if (medecins[i].servID[j] == invalide) break;
			printf("#%d ", medecins[i].servID[j]);
		}
		printf("\n");
	}
	printf("=======================================================================================================\n");
	fclose(file);
}


int main(void) {
	// system("color 0c")
	setlocale(LC_ALL, "");

	int type;
	char admin_name[30];
	char admin_mdp[30];
	struct Admin admin;
	

	
	// Main Menu
	// Choose user type
	
		do {
			printf("Choisir: (1-3)\n1) Admin\n2) Medecin\n3) Patient\n->");
			scanf_s("%d", &type);
		} while (type < 1 || type > 6); // SHOULD BE 3
		system("cls");



		switch (type)
		{
			// if ADMIN option is chosen
			case 1: {
				//  Admin Login
				printf("=== Admin Login ===\n");

				// get the admin structure from the admin.dat file
				file_to_struct(&admin, sizeof(struct Admin), "admin.dat");

				do {
					// read name and password from user
					printf("nom:\n-> ");
					scanf_s("%s", admin_name, sizeof(admin_name));

					printf("mot de passe \n-> ");
					scanf_s("%s", admin_mdp, sizeof admin_mdp);
					// TESTING

					// if admin name and password are correct
					//
					if (strcmp(admin_name, admin.nom) == 0 && strcmp(admin_mdp, admin.mdp) == 0) {
						break;
					}
					else {
						printf("invalide\n");


					}

				} while (1);
				system("cls");
				printf("Bienvenu mr. %s\n", admin.nom);

				// =====================================================================================
				// =====================================================================================
				// Services
				// reading a service structure from user, then, add it to the services.dat file

				// options de l'admin
				// repeating loop
				do {
					do {
						printf("Choisir un option\n");
						printf("1. Gerer les services\n");
						printf("2. Gerer les medecins\n");
						printf("3. Gerer les patients\n");
						printf("4. Gerer les rendez-vous\n");
						printf("5. Ajouter les jours feriers\n");


						scanf_s("%d", &type);
					} while (type < 1 || type > 5);
					// Variables


					struct Service service;
					struct Service new_service;

					char service_name[20] = { 0 };
					int id = 0;
					FILE* file = NULL;
					int n;
					int i;
					struct Service services[100];


					// Variables
					struct Medecin medecins[100];
					struct Medecin med;
					char nom_med[30] = {0};
					char specialie[50] = { 0 };
					char ddn[20];

					// Variables
					
					char reponse;
					char date_fer[100];

					system("cls");

					switch (type) {
						// gerer les services
						case 1: {
							// gerer les services
							do {
								printf("Choisir un option\n");
								printf("1. Ajouter un service\n");
								printf("2. Supprimer un service\n");
								printf("3. Modifier un service\n");
								printf("4. Afficher les service\n->");

								scanf_s("%d", &type);
							} while (type < 1 || type > 4);

							system("cls");
							switch (type) {
							// Adding a service 
							case 1: { 
								// read service data from user
								//struct Service service;
								//struct Service new_service;

								//char service_name[20] = { 0 };
								//int id = 0;
								id = 0;
								do {
									printf("nom de service: ");
									scanf_s("%s", service_name, (unsigned)sizeof(service_name));
									if (strlen(service_name) != 0) {
										break;  // Exit the loop if an empty string is entered
									}

								} while (1);  // Infinite loop; use a break statement to exit when needed

								fopen_s(&file, "services.dat", "rb");
								while (fread(&service, sizeof(struct Service), 1, file) == 1) {
									if (id < service.id) id = service.id;
								}
								id++;
								fclose(file);

								// ok, now we have the name and id!
								strcpy_s(new_service.nom, sizeof(service_name), service_name);
								new_service.id = id;
								//printf("%d, %s", new_service.id, new_service.nom);
								fopen_s(&file, "services.dat", "ab");
								fwrite(&new_service, sizeof(struct Service), 1, file);
								fclose(file);


								break;
							}
							// Deleting a service
							case 2: { // supprimer un service
								// Afficher au début:
								//struct Service services[100];
								//struct Service service;
								//struct Service services[100];

								afficher_services();
								i = 0;
								fopen_s(&file, "services.dat", "rb");
								while (fread(&service, sizeof(struct Service), 1, file) == 1) {
									services[i] = service;
									i++;
								}
								n = i;
								fclose(file);
								// =======================supprimer=======================
								/*int id;*/
								printf("donner l'identifiant de service à supprimer: ");
								scanf_s("%d", &id);
								// now, rewrite
								fopen_s(&file, "services.dat", "wb");
								for (i = 0; i < n; i++) {
									if (services[i].id != id) {
										fwrite(&services[i], sizeof(struct Service), 1, file);

									}
								}
								fclose(file);



								break;
							}

							// modifier un service
							// donner l'id => array => modify
							case 3: {
								afficher_services();
								i = 0;
								fopen_s(&file, "services.dat", "rb");
								while (fread(&service, sizeof(struct Service), 1, file) == 1) {
									services[i] = service;
									i++;
								}
								n = i;
								fclose(file);
								// ======================= Modifer =======================
								/*int id;*/
								printf("donner l'identifiant de service a modifier: ");
								scanf_s("%d", &id);
								// rewrite
								fopen_s(&file, "services.dat", "wb");
								for (i = 0; i < n; i++) {
									if (services[i].id != id) {
										fwrite(&services[i], sizeof(struct Service), 1, file);
									}
									else {
										service_name[0] = '\0';
										printf("donner le nouveau nom de service: ");
										scanf_s("%s", service_name, (unsigned)sizeof(service_name));
										strcpy_s(services[i].nom, sizeof(service_name), service_name);
										fwrite(&services[i], sizeof(struct Service), 1, file);

									}
								}
								fclose(file);

								break;
							}

							// Showing services
							case 4: {
								afficher_services();
								printf("\n\n");
								break;
							}
							}
				
					break; /*end gerer les services*/ }
						// gerer les medecins
						case 2: {

							do {
								printf("Choisir un option\n");
								printf("1. Ajouter un medecin\n");
								printf("2. Supprimer un medecin\n");
								printf("3. Modifier un medecin\n");
								printf("4. Afficher les medecins\n->");
								scanf_s("%d", &type);
							} while (type < 1 || type > 4);

							system("cls");

							switch (type) {
								// add a doctor
							
								case 1: {
									// read doctor data from user
									struct Medecin medecin;
									struct Medecin new_med;
									char nom_medecin[30] = { 0 };
									char ddn[20] = { 0 };
									char genre;
									int servID[30];
									char specialite[50] = { 0 };
									int id = 0;
									int i;
									printf("donner le nom: ");
									while (getchar() != '\n');
									
									gets_s(&nom_medecin, sizeof(nom_medecin));
									printf("donner date de naissance: ");
									gets_s(&ddn, sizeof(ddn));
									printf("donner la specialité: ");
									gets_s(&specialite, sizeof(specialite));

									printf("donner le genre (m/f)");
									do {
										scanf_s("%c", &genre, (unsigned) sizeof(genre));
									} while (genre != 'm' && genre != 'f');

									printf("donner les services: (ecrire '-1' pour terminer)\n");
									i = 0;
									int numid;
									struct Service service;
									int is_found = 0;
									FILE* file2 = NULL;
									do {
										is_found = 0;
										printf("donner service n%d: ", i+1);
										scanf_s("%d", &numid);
										if (numid == -1) break;
										// test if service if exists:
										fopen_s(&file2, "services.dat", "rb");
										while (fread(&service, sizeof(struct Service), 1, file2) == 1 && !is_found) {
											if (service.id == numid) {
												is_found = 1;
											}
										}

										fclose(file2);

										if (is_found) { new_med.servID[i] = numid; }
										else {
											printf("\nid n'existe pas!\n");
											i--;
										}
										i++;
										
									} while (1);
									// calculate the new id
									FILE* file = NULL;
									fopen_s(&file, "medecins.dat", "rb");
									while (fread(&medecin, sizeof(struct Medecin), 1, file) == 1) {
										if (id < medecin.medID) id = medecin.medID;
									}
									id++;
									fclose(file);
									// ok, now we have all the data!

									strcpy_s(new_med.nom, sizeof(nom_medecin), nom_medecin);
									strcpy_s(new_med.ddn, sizeof(ddn), ddn);
									strcpy_s(new_med.specialite, sizeof(specialite), specialite);
									new_med.genre = genre;
									new_med.medID = id;
									fopen_s(&file, "medecins.dat", "ab");
									fwrite(&new_med, sizeof(struct Medecin), 1, file);
									fclose(file);

									break;
								} // FIN: adding a doctor
								// supprimer
								case 2: {
									int id;
									FILE* file = NULL; 
									int i = 0;
									struct Medecin meds[100];
									struct Medecin med;
									// afficher et creé un array
									fopen_s(&file, "medecins.dat", "rb");
									while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
										meds[i] = med;
										i++;
									}
									int n = i;
									//afficher_medecins();
									fclose(file);

									printf("donner l'ID de medecin a supprimer: ");
									scanf_s("%d", &id);
									// now, rewrite
									fopen_s(&file, "medecins.dat", "wb");
									for (i = 0; i < n; i++) {
										if (meds[i].medID != id) {
											fwrite(&meds[i], sizeof(struct Medecin), 1, file);
										}
									}
									fclose(file);


									break;
								}
								// modifier un doc
								case 3: {
									FILE* file = NULL;
									afficher_medecins();
									i = 0;
									fopen_s(&file, "medecins.dat", "rb");
									while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
										medecins[i] = med;
										i++;
									}
									n = i;
									int k;
									
									/*for (i = 0; i < n; i++) {
										printf("%d / ", medecins[i].medID);
									}*/
									// ======================= Modifer =======================
									/*int id;*/
									printf("donner l'identifiant de medecin a modifier: ");
									scanf_s("%d", &id);
									// rewrite
									fclose(file);
									fopen_s(&file, "medecins.dat", "wb");
									if (!file) {
										perror("fopen");
										break;
									}
									for (i = 0; i < n; i++) {
										if (medecins[i].medID != id) {
											fwrite(&medecins[i], sizeof(struct Medecin), 1, file);
										}
										else {
											// NOM
											printf("donner le nouveau nom de medecin: ");
											while (getchar() != '\n');

											gets_s(&nom_med, sizeof(nom_med));
											if (strlen(nom_med)) {
												strcpy_s(medecins[i].nom, sizeof(nom_med), nom_med);
											}
											// SPECIALITE
											printf("donner le nouveau specialite de medecin: ");
											gets(&specialie, sizeof(specialie));
											printf("donner le nouveau ddn de medecin: ");
											if (strlen(specialie) > 0) {
												strcpy_s(medecins[i].specialite, sizeof(specialie), specialie);

											}

											// DDN
											gets(&ddn, sizeof(ddn));

											if (strlen(ddn) > 0) {
												strcpy_s(medecins[i].ddn, sizeof(ddn), ddn);
											}
											fwrite(&medecins[i], sizeof(struct Medecin), 1, file);




										}
									}
									fclose(file);
									break;
								}
								// Afficher 
								case 4: {
									// afficher les medecins
								//test: {
									afficher_medecins();
									break;
									//}
								}
							}




							break;
						} // fin gerer les medecins
						// gerer les patients
						case 3: {
							//test: {

							do {
								printf("Choisir un option\n");
								printf("1. Ajouter un patinet\n");
								printf("2. Supprimer un patient\n");
								printf("3. Modifier un patient\n");
								printf("4. Afficher les patients\n->");
								scanf_s("%d", &type);
							} while (type < 1 || type > 4);


							system("cls");
							switch (type) {
								// ajouter un patient
								case 1: {
									struct Patient pat;
									struct Patient new_pat;
									char nom_pat[30] = { 0 };
									char ddn[20] = { 0 };
									char genre;
									int servID[30];
									int medIDs[30];
									char desc[50] = { 0 };
									int id = 0;
									int i;

									while (getchar() != '\n');
									printf("donner le nom: ");
									gets(&nom_pat);
									printf("donner date de naissance: ");
									gets(&ddn);


									printf("donner le genre (m/f)");
									do {
										scanf_s("%c", &genre, (unsigned)sizeof(genre));
									} while (genre != 'm' && genre != 'f');

									printf("donner les services: (ecrire '-1' pour terminer)\n");
									i = 0;
									int numid;
									struct Service service;
									int is_found = 0;
									FILE* file2 = NULL;
									do {
										is_found = 0;
										printf("donner service n%d: ", i + 1);
										scanf_s("%d", &numid);
										if (numid == -1) break;
										// test if service if exists:
										fopen_s(&file2, "services.dat", "rb");
										while (fread(&service, sizeof(struct Service), 1, file2) == 1 && !is_found) {
											if (service.id == numid) {
												is_found = 1;
											}
										}
										fclose(file2);

										if (is_found) { new_pat.servIDs[i] = numid; }
										else {
											printf("\nid n'existe pas!\n");
											i--;
										}
										i++;
									} while (1);


									// ajouter les medecins!
									printf("donner les medecins: (ecrire '-1' pour terminer)\n");
									struct Medecin medecin;
									i = 0;
									is_found = 0;
									do {
										is_found = 0;
										printf("donner l'id d'un medecin n%d: ", i + 1);
										scanf_s("%d", &numid);
										if (numid == -1) break;
										// test if service if exists:
										fopen_s(&file2, "medecins.dat", "rb");
										while (fread(&medecin, sizeof(struct Medecin), 1, file2) == 1 && !is_found) {
											if (medecin.medID == numid) {
												is_found = 1;
												break;
											}
										}
										fclose(file2);

										if (is_found) { new_pat.medIDs[i] = numid; }
										else {
											printf("\nid n'existe pas!\n");
											i--;
											break;
										}

										i++;
									} while (1);


									// calculate the new id
									FILE* file = NULL;
									fopen_s(&file, "patients.dat", "rb");
									while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
										if (id < pat.id) id = pat.id;
									}
									id++;
									fclose(file);
									// ok, now we have all the data!

									strcpy_s(new_pat.nom, sizeof(nom_pat), nom_pat);
									strcpy_s(new_pat.ddn, sizeof(ddn), ddn);
									new_pat.genre = genre;
									new_pat.id= id;
									// DEBUG
									// printf("%d", new_pat.id);

									fopen_s(&file, "patients.dat", "ab");
									fwrite(&new_pat, sizeof(struct Patient), 1, file);
									fclose(file);

									// create array of meds

									





									break; // of test label
							

								// supprimer un patient
								case 2: {
									int id;
									FILE* file = NULL;
									int i = 0;
									struct Patient pats[100];
									struct Patient pat;
									// afficher et creé un array
									fopen_s(&file, "patients.dat", "rb");
									while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
										pats[i] = pat;
										i++;
									}
									int n = i;
									for (i = 0; i < n; i++) {
										printf("Nom: %s | Id: %d\n", pats[i].nom, pats[i].id);
									}
									fclose(file);

									printf("donner l'ID de patient à supprimer: ");
									scanf_s("%d", &id);
									// now, rewrite
									fopen_s(&file, "patients.dat", "wb");
									for (i = 0; i < n; i++) {
										if (pats[i].id != id) {
											fwrite(&pats[i], sizeof(struct Patient), 1, file);

										}
									}
									fclose(file);



									break;
								}

								// Afficher les patients
								case 4: {
									afficher_patients();
									/*struct Patient patients[100];
									struct Patient pat;
									int i = 0;
									FILE* file = NULL;
									fopen_s(&file, "patients.dat", "rb");
									while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
										patients[i] = pat;
										i++;
									}
									int n = i;
									for (i = 0; i < n; i++) {
										printf("Nom: %s / id: %d / description: %s / ddn: %s / services: ", patients[i].nom, patients[i].id, patients[i].desc, patients[i].ddn);
										for (int j = 0; j < sizeof(patients[i].servIDs) / sizeof(patients[i].servIDs[0]); j++) {
											if (patients[i].servIDs[j] == -858993460) break;
											printf("#%d ", patients[i].servIDs[j]);
										}
										printf(" medecins: ");
										for (int j = 0; j < sizeof(patients[i].medIDs) / sizeof(patients[i].medIDs[0]); j++) {
											if (patients[i].medIDs[j] == -858993460) break;
											printf("#%d ", patients[i].medIDs[j]);
										}

										printf("\n");
									}*/


									break;
								}
						
							}
						
						
							}


							break;
						}

						case 4: {
							/*
								now, the admin checks the list of appointments, we'll give him the latest one;
									we check the validation :
								-number of patients who already have an appointment
									with the doctor i.e.
									[readStruct.date == rendzevous.date
									&& readStruct.med_id == rendervous.id
									&& readStruct.status == "accepted"]
									if that's valid,
										we check if the date is not one of the holidays...
										seach in joursferiers.dat, we shouldn't find it.
							*/

							// CERT
						/*	i = 0;
							struct Certificat cert;
							struct Certificat certs[100];
							int nb_cert = 0;
							int nb_cert_total = 0;*/
							// open rendizvous file and create an array


					//// SIDE UNREALTED NOTE => afficher la liste de medecin et patient choisir

							int valide = 1;
							struct Rendezvous rend;
							struct Rendezvous rends[100];

							int n_fer = 0;
							char jours_fer[100][50];

							i = 0;
							int nb_requests = 0;
							int rendiv_index;

							int nb_autres = 0;
							fopen_s(&file, "rendezvous.dat", "rb");
							while (fread(&rend, sizeof(struct Rendezvous), 1, file) == 1) {
								rends[i] = rend;
								if (strcmp(rend.status, "Waiting") == 0) {
									rendiv_index = i;
									nb_requests++;
								}



								i++;
							}
							fclose(file);
							n = i;


							/*	for (i = 0; i < n; i++) {
									printf("%s\n", rends[i].status);
								}*/

							char date_fer[30];
							fopen_s(&file, "datesfer.txt", "r");
							while (fgets(date_fer, sizeof(date_fer), file) != NULL) {
								strcpy_s(jours_fer[n_fer], sizeof(jours_fer[0]), date_fer);
								n_fer++;
							}
							/*for (i = 0; i < n_fer; i++) {
								printf("%s\n", jours_fer[i]);
							}*/
							// printf("nb fer: %d", n_fer);
							fclose(file);









							if (nb_requests == 0) {
								printf("Il n'ya pas de demandes\n");
							}
							else {
								printf("Il ya %d demandes.\n", nb_requests);
								printf("Le patient %s a demandé un rendez vous avec dr. %s pour le date: %s\n", rends[rendiv_index].nom_pat, rends[rendiv_index].nom_med, rends[rendiv_index].date);

								for (i = 0; i < n; i++) {
									// 2004/22/14
									if (strcmp(rends[i].status, "Accepted") == 0 && strcmp(rends[i].date, rends[rendiv_index].date) == 0) {
										nb_autres++;
									}
								}
								//nb_autres = 20;
								printf("il ya %d rendivous pour la date %s", nb_autres, rends[rendiv_index].date);
								if (nb_autres < 20) {
									printf("\x1B[32m [Valide]\n");
								}
								else {
									printf("\x1B[31m [Invalide]\n");
									valide = 0;
									// ...
								}
								printf("\x1B[37m"); // reset color
								printf("le jours %s ", rends[rendiv_index].date);
								for (i = 0; i < n_fer; i++) {
									jours_fer[i][strlen(jours_fer[i]) - 1] = '\0';
									if (strcmp(rends[rendiv_index].date, jours_fer[i]) == 0) {
										printf("est un jour férié");
										printf("\x1B[31m [Invalide]\n");
										valide = 0;
										break;
									}
								}
								
								if (i == n_fer) {
									printf("n'est pas un jour férié");
									printf("\x1B[32m [Valide]\n");
								}
								printf("\x1B[37m"); // reset color

								char reponse_admin[30];
								if (valide == 1) {
									printf("i = %d", i);
									printf("%d", n_fer);

									printf("Conclusion: le demande de patient est \x1B[32mvalide\x1B[37m\n");
									printf("ceder à accepter le rendez vous? (oui)\n");
									while (getchar() != '\n');
									gets_s(&reponse_admin, sizeof reponse_admin);

									if (strcmp(reponse_admin, "oui") == 0) {
										printf("Le rendez vous a été accepté.\n");
										strcpy_s(rends[rendiv_index].status, sizeof rends, "Accepted");
									}
								}
								else {
									printf("Conclusion: le demande de patient est\x1B[31m invalide\x1B[37m\n");
									printf("ceder à refuser le rendez vous? (oui)\n");
									while (getchar() != '\n');
									gets_s(&reponse_admin, sizeof & reponse_admin);
									strcpy_s(rends[rendiv_index].status, sizeof rends[rendiv_index].status, "Refused");
									printf("Le rendez vous a été refusé.\n");

								}

							
							}
							// rewrite
							fopen_s(&file, "rendezvous.dat", "wb");
							for (i = 0; i < n; i++) {
								fwrite(&rends[i], sizeof(struct Rendezvous), 1, file);
							}
							fclose(file);
				





						
							break;
						}

						case 5: {
							fopen_s(&file, "datesfer.txt", "w");

							do {
								printf("donner un jour ferié (yyyy/mm/jj)\n-> ");
								while (getchar() != '\n');
								gets_s(date_fer, sizeof(date_fer));
								fprintf(file, "%s\n", date_fer);
								printf("%s", date_fer);
								printf("continue? (y/n)\n-> ");

								while (getchar() != '\n');
								scanf_s("%c", &reponse, (unsigned)sizeof(reponse));
								while (getchar() != '\n');
								if (reponse == 'n') {
									break;
								}
							} while (1);




							fclose(file);

							/*fopen_s(&file, "datesfer.txt", "r");
							char text[30];
							fread(text, sizeof(char), sizeof(text), file);
							printf("res: %s\n", text);


							fclose(file);*/


							break;
						}
					} 

				} while (1);
				break;


			} // case one: admin space
			
			// if MEDECIN option is chosen
			case 2: { //go med


				char med_name[30];
				char pat_name[30];
				int med_id;
				printf("=== Medecin Login ===\n");
				struct Medecin med;
				struct Medecin meds[100];
				struct Patient pat;
				struct Patient pats[100];
				FILE* file = NULL;
				int i = 0;
				char med_ddn[20];
				char pat_ddn[20];
				int found = 0;
				int n;
				int med_index;





				do {
					printf("nom:\n-> ");
					while (getchar() != '\n');
					gets_s(&med_name, sizeof(med_name));

					printf("ID:\n-> ");
					scanf_s("%d", &med_id);
					// TESTING
					i = 0;
					// open med file!
					fopen_s(&file, "medecins.dat", "rb");
					while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
						meds[i] = med;
						i++;
					}
					n = i;

					for (i = 0; i < n; i++) {
						if (med_id == meds[i].medID && (strcmp(med_name, meds[i].nom) == 0)) {
							found = 1;
							med_index = i;
							break;
						}
					}
					if (!found) {
						system("cls");
						printf("Invalide!\n");

					}

					fclose(file);




				} while (!found);
				system("cls");
				printf("Bienvenu mr. %s\n", med_name);

				int pat_id;
				int cert_index = -1;

				// CERT
				i = 0;
				struct Certificat cert;
				struct Certificat certs[100];
				int nb_cert = 0;
				int nb_cert_total = 0;

				//new
				char desc[500];
				int k = 0;
				int pat_index = 0;
				struct Ordonnance ord;
				struct Ordonnance copy_ord;
				char medicaments[200];

				int id;
				char reponse;
				char cause[200];

				char text[200];
				time_t now = time(NULL);
				struct tm t; // built in date/time structure

				do { // repeat after completing
					cert_index = -1;
					found = 0;
					pat_index = 0;
					nb_cert = 0;
					nb_cert_total = 0;
					i = 0;

					fopen_s(&file, "certificats.dat", "rb");
					while (fread(&cert, sizeof(struct Certificat), 1, file) == 1) {
						certs[i] = cert;

						i++;
						/*printf("test 1: %d", certs[i].med_id == med_id);
						printf("test 2: %d", strcmp(certs[i].status, "Waiting") == 0);*/
						if (cert.med_id == meds[med_index].medID && strcmp(cert.status, "Waiting") == 0) {
							cert_index = i - 1;
							nb_cert++;
						}
					}
					nb_cert_total = i;

					//printf("total cert = %d", nb_cert_total);





					fclose(file);



					do {
						printf("\nChoisir un option\n");
						printf("1. Rédiger un dossier de maladie\n");
						printf("2. Rédiger un ordonnance\n");
						printf("3. Rédiger des certificats (%d)\n", nb_cert);
						scanf_s("%d", &type);
					} while (type < 1 || type > 4);

					switch (type) {
					case 1: {
						system("cls");




						/*	found = 0;
							int pat_index = 0;
							char desc[500];
							int n;*/

						found = 0;
						pat_index = 0;


						do {
							printf("Choisr un patient pour rediger sa dossier: \n");
							// get user id
							// loop the pat file and check if valid,
							// if valid => change desc
							printf("nom:\n-> ");
							while (getchar() != '\n');
							gets_s(&pat_name, sizeof(pat_name));

							printf("ID:\n-> ");
							scanf_s("%d", &pat_id);

							i = 0;
							// open pat file!
							fopen_s(&file, "patients.dat", "rb");
							while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
								pats[i] = pat;
								i++;
							}
							n = i;

							for (i = 0; i < n; i++) {
								if (pat_id == pats[i].id && strcmp(pat_name, pats[i].nom) == 0) {
									found = 1;
									pat_index = i;
									break;
								}
							}
							if (!found) {
								system("cls");
								printf("Invalide!\n");
							}

							fclose(file);
						} while (!found);
						// write desc

						printf("Ecrire la description de maladie: ");
						while (getchar() != '\n');
						gets_s(&desc, sizeof(desc));
						strcpy_s(pats[pat_index].desc, sizeof(desc), desc);

						// overwrite pat file
						fopen_s(&file, "patients.dat", "wb");
						for (i = 0; i < n; i++) {
							fwrite(&pats[i], sizeof(struct Patient), 1, file);
						}
						fclose(file);

						break;
					}
					case 2: {
						// cree un structure ORDONNANCE
						// checher un patient, 
						/* go to

							 => redifer des ordonnances => {
							DONE: 1. choose a patient: through ID
							// not really important: check if the doctor is the one of the patient's doctors
							2. write "medicaments" in an array and add it to a buffer structure
							3. create the structure; add it to a file
							add the id of the strucutre to the patient
							GENERATE A PDF!
							struct ord added to ord.dat
							ord := id, name, sig de medecin; id, nom, liste de medicaments;
							}

						*/

						//struct Ordonnance ord;
						//struct Ordonnance copy_ord;
						//char medicaments[200];
						//found = 0;
						//int pat_index = 0;
						//int n;

						found = 0;
						pat_index = 0;






						do {

							printf("Choisr un patient pour rediger un ordonnance: \n");
							// get user id
							// loop the pat file and check if valid,
							// if valid => change desc
							printf("nom:\n-> ");
							while (getchar() != '\n');
							gets_s(&pat_name, sizeof(pat_name));

							printf("ID:\n-> ");
							scanf_s("%d", &pat_id);

							i = 0;
							// open pat file!
							fopen_s(&file, "patients.dat", "rb");
							while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
								pats[i] = pat;
								i++;
							}
							n = i;

							for (i = 0; i < n; i++) {
								if (pat_id == pats[i].id && strcmp(pat_name, pats[i].nom) == 0) {
									found = 1;
									pat_index = i;
									break;
								}
							}
							if (!found) {
								system("cls");
								printf("Invalide!\n");
							}

							fclose(file);
						} while (!found);
						// write desc
						//printf("Ecrire la description de maladie: ");
						//while (getchar() != '\n');
	//						gets_s(&desc, sizeof(desc));
			//				strcpy_s(pats[pat_index].desc, sizeof(desc), desc);

						while (getchar() != '\n');
						printf("Ecrire la liste de medicaments: (spepare par ,):");
						gets_s(&medicaments, sizeof(medicaments));
						strcpy_s(&ord.medicaments, sizeof ord.medicaments, medicaments);

						ord.id_pat = pats[pat_index].id;
						// int id = 0;

						id = 0;
						fopen_s(&file, "ord.dat", "rb");
						while (fread(&copy_ord, sizeof(struct Ordonnance), 1, file) == 1) {
							if (id < copy_ord.id) id = copy_ord.id;
						}
						id++;
						fclose(file);
						ord.id = id;
						strcpy_s(ord.nom_pat, sizeof(ord.nom_pat), pats[pat_index].nom);
						strcpy_s(ord.nom_med, sizeof(ord.nom_pat), med_name);

						fopen_s(&file, "ord.dat", "ab");
						fwrite(&ord, sizeof(struct Ordonnance), 1, file);
						fclose(file);

						// overwrite pat file
										// add ord id to patient
						k = 0;
						while (pats[pat_index].ordIDs[k] > 0) {
							k++;
						}
						pats[pat_index].ordIDs[k] = id;
						/*printf("\nliste d'ord: ");
						for (int z = 0; z < k + 1; z++) {
							printf("#%d ", pats[pat_index].ordIDs[z]);
						}*/

						// overwrite
						fopen_s(&file, "patients.dat", "wb");
						for (i = 0; i < n; i++) {
							fwrite(&pats[i], sizeof(struct Patient), 1, file);
						}
						fclose(file);
















						break;
					}
					case 3: {
						/*
						Rediger les certificats
						=> a patient asks for a certificate
						how?
						the patient sends a request, stating his ID, medID, name
						generate the requestID, status="Waiting"
						the structure then is appended to the cert-request.dat file
						in that file
						THEN, the doctor goes through that file,
						we show him a notification e.g. (5)
						then, we show one of the certificate requests
						he can refuse => status = "Accepted"
						he can accept => status = "Refused"
						he adds the "cause"
						date of creation is automatically added
						now we return to the PDF record, we loop through cert-request.dat file
						and add information to the PDF record.
						*/ // go to

						//char reponse;
						//char cause[200];
						if (nb_cert == 0) {
							printf("il n ya pas des demandes");
						}
						else {
							printf("En total, il ya %d demandes pour les certificats.\n", nb_cert);
							printf("Le nom de patient: %s\n", certs[cert_index].pat_name);
							printf("L'état de patient: %s\n", certs[cert_index].status);
							printf("voulez vous accepter la demande? o/n: ");
							do {
								while (getchar() != '\n');
								scanf_s("%c", &reponse, (unsigned)sizeof(reponse));
								if (reponse == 'o' || reponse == 'n') {
									break;
								}
								else {
									printf("valeur erronée!\n");
								}
							} while (1);
							if (reponse == 'o') {
								printf("completer les informations de certificat:");
								printf("ecrire la cause de la certificat: .\n");
								while (getchar() != '\n');
								gets_s(&cause, sizeof cause);
								strcpy_s(certs[cert_index].cause, sizeof cause, cause);
								strcpy_s(certs[cert_index].status, sizeof certs[cert_index].status, "Accepted");
								strcpy_s(certs[cert_index].med_nom, sizeof certs[cert_index].med_nom, med_name);

								/*
								char text[200];
								time_t now = time(NULL);
								struct tm t; // built in date/time structure
								*/
								now = time(NULL);
								localtime_s(&t, &now);
								strftime(text, sizeof(text) - 1, "%d-%m-%Y %H:%M", &t);
								strcpy_s(certs[cert_index].date, sizeof certs[cert_index].date, text);
							}



							else {
								now = time(NULL);

								/*
								char text[200];
								time_t now = time(NULL);
								struct tm t; // built in date/time structure
								*/
								localtime_s(&t, &now);
								strftime(text, sizeof(text) - 1, "%d-%m-%Y %H:%M", &t);
								strcpy_s(certs[cert_index].date, sizeof certs[cert_index].date, text);
								strcpy_s(certs[cert_index].med_nom, sizeof certs[cert_index].med_nom, med_name);
								strcpy_s(certs[cert_index].status, sizeof certs[cert_index].status, "Refused");

							}

							fopen_s(&file, "certificats.dat", "wb");
							for (i = 0; i < nb_cert_total; i++) {

								/*printf("DEBUGGING reading a request: \n");
								printf("cert.pat_name: %s\n", certs[i].pat_name);
								printf("id: %d\n", certs[i].id);
								printf("pat id: %d\n", certs[i].pat_id);
								printf("pat name: %s\n", certs[i].pat_name);
								printf("status: %s\n", certs[i].status);
								printf("med id: %d\n", certs[i].med_id);
								printf("date: %s\n", certs[i].date);
								printf("cause: %s\n", certs[i].cause);*/

								fwrite(&certs[i], sizeof(struct Certificat), 1, file);

							}
							fclose(file);

						}



						break;
					}
					}

			} while (1);

				// Options Medecins

				break;
			}



			// if PATIENT chosen
			case 3: {


				int pat_id;
				char pat_name[30];
				struct Patient pat;
				struct Patient pats[100];
				FILE* file = NULL;
				int i = 0;
				char pat_ddn[20];
				int found = 0;
				int n;
				int pat_index;


				printf("=== Patient Login ===\n");
				do {
					printf("nom:\n-> ");
					while (getchar() != '\n');
					gets_s(&pat_name, sizeof(pat_name));

					printf("ID:\n-> ");
					scanf_s("%d", &pat_id);
					// TESTING

					i = 0;
					// open pat file!
					fopen_s(&file, "patients.dat", "rb");
					while (fread(&pat, sizeof(struct Patient), 1, file) == 1) {
						pats[i] = pat;
						i++;
					}
					n = i;

					for (i = 0; i < n; i++) {
						if (pat_id == pats[i].id && (strcmp(pat_name, pats[i].nom) == 0)) {
							found = 1;
							pat_index = i;
							break;
						}
					}

					if (!found) {
						system("cls");
						printf("invalide!\n");
					}

					fclose(file);


				} while (!found);
				system("cls");
				printf("Bienvenu mr. %s\n", pat_name);




			// rappel, create an array for rendezvous, check, if rendez there's a rendez vous in the next 7 days, alert
				struct Rendezvous rend;
				char text[100];
				time_t now = time(NULL);
				struct tm t; // built in date/time structure
				now = now + (long) ((7) * 3600 * 24);
				localtime_s(&t, &now);
				strftime(text, sizeof(text) - 1, "%Y/%m/%d", &t);
				fopen_s(&file, "rendezvous.dat", "rb");

				while (fread(&rend, sizeof(struct Rendezvous), 1, file) == 1) {
					if (strcmp(rend.status, "Accepted") == 0 && strcmp(rend.date, text) == -1 && rend.id_pat == pats[pat_index].id) {
						printf("[Notification] Il un rendez vous la semaine prochaine avec mr. %s dans %s\n", rend.nom_med, rend.date);
					}
				}
				fclose(file);











				
				do {
					printf("Choisir un option\n");
					printf("1. Demander un certifcat\n");
					printf("2. Demander un rendez-vous\n");
					printf("3. Consulter le dossier medicale\n->");
					scanf_s("%d", &type);
				} while (type < 1 || type > 4);

				switch (type) {
				// demander un cert
				case 1: {
					/*
						Rediger les certificats
						=> a patient asks for a certificate
						how?
						the patient sends a request, stating his ID, medID, name
						DONE ===== generate the requestID, status="Waiting"
						DONE ===== the structure then is appended to the cert-request.dat file
						in that file
						
						THEN, the doctor goes through that file,
						we show him a notification e.g. (5)
						then, we show one of the certificate requests
						he can refuse => status = "Accepted"
						he can accept => status = "Refused"
						he adds the "cause"
						date of creation is automatically added
						now we return to the PDF record, we loop through cert-request.dat file
						and add information to the PDF record.
						*/
					int med_id;
					struct Medecin med;
					struct Medecin meds[100];
					char med_name[30];
					struct Certificat cert;
					int id = 0;

					printf("Demander un certificat\n");

					
					int found = 0;
					int med_index = 0;

					do {
						printf("Choisir un medecin (id)\n");
						while (getchar() != '\n');
						scanf_s("%d", &med_id);
						i = 0;
						// open med file!
						fopen_s(&file, "medecins.dat", "rb");
						while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
							meds[i] = med;
							i++;
						}
						n = i;

						for (i = 0; i < n; i++) {
							if (med_id == meds[i].medID) {
								found = 1;
								med_index = i;
								break;
							}
						}
						if (!found) {
							system("cls");
							printf("Invalide!\n");

						}

						fclose(file);
					} while (!found);

					strcpy_s(cert.status, sizeof cert.status, "Waiting");


					strcpy_s(cert.pat_name, sizeof cert.pat_name, pats[pat_index].nom);
					cert.med_id = meds[med_index].medID;

					cert.pat_id = pats[pat_index].id;

					
					// calculate the id!

					struct Certificat test_cert;

					
					FILE* file = NULL;
					fopen_s(&file, "certificats.dat", "rb");
					while (fread(&test_cert, sizeof(struct Certificat), 1, file) == 1) {
						/*printf("calculating ID!\n");
						printf("id cert = %d\n", test_cert.id);
						printf("id = %d\n", id);*/


						if (id < test_cert.id) {
							id = test_cert.id;
						}
					}
					id++;
					fclose(file);

					cert.id = id;

					// add to file
					fopen_s(&file, "certificats.dat", "ab");
					fwrite(&cert, sizeof(struct Certificat), 1, file);

				/*	printf("DEBUGGING user sending a request: \n");
					printf("cert.pat_name: %s\n", cert.pat_name);
					printf("cause: %s\n", cert.cause);
					printf("id: %d\n", cert.id);
					printf("pat id: %d\n", cert.pat_id);
					printf("pat name: %s\n", cert.pat_name);
					printf("status: %s\n", cert.status);*/


					fclose(file);
					printf("demande envoyé avec success!");




					break;
				}

				case 2: {
					/*
					" # missing modify patient
					  # missing loops in the doctor and patient interfaces
					  # missing signature



					patient requests an appointment => same way as certs, in renderzvous.dat
					rendez vous contains; rendez-vous date [input], nom pat, id pat, nom med, id med,
					status (accepted, waiting, invalid)
					the user sends the request...
					###### but the doctor can also send a request, using the same logic.
					-----DONE------


					now, the admin checks the list of appointments, we'll give him the latest one;
					we check the validation:
						- number of patients who already have an appointment 
						with the doctor i.e. 
						[readStruct.date == rendzevous.date 
						&& readStruct.med_id == rendervous.id
						&& readStruct.status == "accepted"]
						if that's valid, 
						we check if the date is not one of the holidays...
						seach in joursferiers.dat, we shouldn't find it.
						
					=====
					jours feriers
					=> we should add an option to the Admin panel, they can add the holiday dates
					to joursferiers.dat
					# DONE
					=====
					after that, we should display the list and number of appointments to the patient
					and, we should display the number of upcoming appointments too.
					*/
					

					int med_id;
					struct Medecin med;
					struct Medecin meds[100];
					//char med_name[30];
					struct Rendezvous rendezvous;
					int id = 0;

					printf("Demander un rendez vous\n");

					// we already  have the patient's ID

					int found = 0;
					int med_index = 0;

					do {
						printf("Choisir un medecin (id)\n");
						while (getchar() != '\n');
						scanf_s("%d", &med_id);
						i = 0;
						// open med file!
						fopen_s(&file, "medecins.dat", "rb");
						while (fread(&med, sizeof(struct Medecin), 1, file) == 1) {
							meds[i] = med;
							i++;
						}
						n = i;

						for (i = 0; i < n; i++) {
							if (med_id == meds[i].medID) {
								found = 1;
								med_index = i;
								break;
							}
						}
						if (!found) {
							system("cls");
							printf("Invalide!\n");

						}

						fclose(file);
					} while (!found);
					// we found the medecin id inside the file, now we have the med_id




					strcpy_s(rendezvous.status, sizeof rendezvous.status, "Waiting");


					strcpy_s(rendezvous.nom_pat, sizeof rendezvous.nom_pat, pats[pat_index].nom);
					strcpy_s(rendezvous.nom_med, sizeof rendezvous.nom_med, meds[med_index].nom);

					rendezvous.id_med = meds[med_index].medID;

					rendezvous.id_pat= pats[pat_index].id;


					// calculate the id!

					struct Rendezvous test_rendezvous;


					fopen_s(&file, "rendezvous.dat", "rb");
					while (fread(&test_rendezvous, sizeof(struct Rendezvous), 1, file) == 1) {
						if (id < test_rendezvous.id) {
							id = test_rendezvous.id;
						}
					}
					id++;
					fclose(file);
					rendezvous.id = id;
					// Ask for the date
					char date[200];
					printf("donner la date de rendezvous (sous la forme aaaa/mm/jj)\n-> ");
					while (getchar() != '\n');
					gets_s(&date, sizeof(date));

					strcpy_s(rendezvous.date, sizeof rendezvous.date, date);



					// add to file
					fopen_s(&file, "rendezvous.dat", "ab");
					fwrite(&rendezvous, sizeof(struct Rendezvous), 1, file);
					fclose(file);

					//printf("Date: %s\n", rendezvous.date);
					//printf("ID: %d\n", rendezvous.id);
					//printf("Patient Name: %s\n", rendezvous.nom_pat);
					//printf("Doctor Name: %s\n", rendezvous.nom_med);
					//printf("Patient ID: %d\n", rendezvous.id_pat);
					//printf("Doctor ID: %d\n", rendezvous.id_med);
					//printf("Status: %s\n", rendezvous.status);

					printf("demande envoyé avec success!");







					break;
				}

				// Consulter le dossier medicale
				case 3: {
					// go through the pat file and print : desciption + ords
					// afficher leur desc
					int minus_height = 50;
					//PDF
					HPDF_Doc pdf;
					pdf = HPDF_New("error_handler", NULL);

					HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

					HPDF_Page page;

					HPDF_Font font = HPDF_GetFont(pdf, "Times-Roman", "WinAnsiEncoding");
					HPDF_Font fontHelvB = HPDF_GetFont(pdf, "Helvetica-Bold", "WinAnsiEncoding");
					HPDF_Font fontHelv = HPDF_GetFont(pdf, "Helvetica", "WinAnsiEncoding");

					HPDF_Font fontRomB = HPDF_GetFont(pdf, "Times-Bold", "WinAnsiEncoding");


					page = HPDF_AddPage(pdf);


					HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
					HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, "Images/tunisie.png");
					HPDF_Page_DrawImage(page, image, 20, HPDF_Page_GetHeight(page) - 70, 216/3, 162/3);

					HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
					image = HPDF_LoadPngImageFromFile(pdf, "Images/signature.png");
					HPDF_Page_DrawImage(page, image, HPDF_Page_GetWidth(page) - 175, 70, 1222 / 9, 446 / 9);
					



					/*HPDF_Page_SetFontAndSize(page, fontHelv, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 20, HPDF_Page_GetHeight(page) - 20);
					HPDF_Page_ShowText(page, "Ministere de la sante - republique Tunisienne ");
					HPDF_Page_EndText(page);*/
					minus_height += 50;





					HPDF_Page_BeginText(page);
					HPDF_Page_SetFontAndSize(page, fontHelvB, 30);

					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					minus_height += 40;
					
					// Heading
					HPDF_Page_ShowText(page, "Dossier Medical");
					HPDF_Page_EndText(page);

					HPDF_Page_SetFontAndSize(page, font, 14);
					
					// DATE
					char text[100];
					time_t now = time(NULL);
					struct tm t; // built in date/time structure
					localtime_s(&t, &now);
					strftime(text, sizeof(text) - 1, "%d-%m-%Y %H:%M", &t);
					


					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, text);
					HPDF_Page_EndText(page);
					minus_height += 20;




					// Line 2
					
					HPDF_Page_SetFontAndSize(page, fontRomB, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, "Informations de patient: ");
					HPDF_Page_EndText(page);
					minus_height += 20;

					char str[1000];
					strcpy_s(str, sizeof str, "Nom: ");
					strcat_s(str, sizeof str, pats[pat_index].nom);

					HPDF_Page_SetFontAndSize(page, font, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, str);
					HPDF_Page_EndText(page);
					minus_height += 20;

					str[0] = '\0';

					strcpy_s(str, sizeof str, "Date de naissance: ");
					strcat_s(str, sizeof str, pats[pat_index].ddn);

					HPDF_Page_SetFontAndSize(page, font, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, str);
					HPDF_Page_EndText(page);
					minus_height += 20;





					HPDF_Page_SetFontAndSize(page, fontRomB, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, "Description de maladie: ");
					HPDF_Page_EndText(page);
					minus_height += 20;




					HPDF_Page_SetFontAndSize(page, font, 14);
					if (strlen(pats[pat_index].desc) > 0) {
						HPDF_Page_BeginText(page);
						HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
						

						HPDF_Page_ShowText(page, pats[pat_index].desc);
						HPDF_Page_EndText(page);
						minus_height += 20;
					}
					else {
						HPDF_Page_BeginText(page);
						HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
						HPDF_Page_ShowText(page, "empty");
						HPDF_Page_EndText(page);
						minus_height += 20;

					}

					


					// Line 3
					HPDF_Page_SetFontAndSize(page, fontRomB, 14);

					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, "Liste d'ordonnnces");
					HPDF_Page_EndText(page);
					minus_height += 20;
					HPDF_Page_SetFontAndSize(page, font, 14);


					// i have the patient's ID; I can go through the ord file, and find them!
					struct Ordonnance ord;
					struct Ordonnance ords[100];

					fopen_s(&file, "ord.dat", "rb");
					while (fread(&ord, sizeof(struct Ordonnance), 1, file) == 1) {
						ords[i] = ord;
						i++;
					}
					int n = i;
					for (i = 0; i < n; i++) {
						if (ords[i].id_pat == pats[pat_index].id) {
							HPDF_Page_BeginText(page);
							HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
							HPDF_Page_ShowText(page, ords[i].medicaments);
							HPDF_Page_EndText(page);
							minus_height += 20;


						}
					}

					fclose(file);


					// Line 4
					HPDF_Page_SetFontAndSize(page, fontRomB, 14);

					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, "Liste de certificats");
					HPDF_Page_EndText(page);
					minus_height += 20;
					HPDF_Page_SetFontAndSize(page, font, 14);

					// CERTS
					// CERT

					// NOT WORKING PROPERLY
					// FOPEN NOT OPENING
					// It seems the Problem is in rewriting
					FILE* f2 = NULL;
					struct Certificat cert;
					fopen_s(&f2, "certificats.dat", "rb");
					// rewind(f2);
					
					while (fread(&cert, sizeof(struct Certificat), 1, f2) == 1) {
						if (cert.pat_id == pats[pat_index].id && strcmp(cert.status, "Waiting") != 0) {
							str[0] = '\0';
							strcpy_s(str, sizeof str, "La date de creation de certificat: ");
							strcat_s(str, sizeof str, cert.date);
							strcat_s(str, sizeof str, " [");
							strcat_s(str, sizeof str, strcmp(cert.status, "Refused") == 0 ? "Refusée" : "Acceptée");
							strcat_s(str, sizeof str, "]");
							strcat_s(str, sizeof str, " [Dr. ");
							strcat_s(str, sizeof str, cert.med_nom);
							strcat_s(str, sizeof str, "]");


							HPDF_Page_BeginText(page);
							HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
							HPDF_Page_ShowText(page, str);
							HPDF_Page_EndText(page);
							minus_height += 20;


						}
					}

					fclose(f2);



					HPDF_Page_SetFontAndSize(page, fontRomB, 14);
					HPDF_Page_BeginText(page);
					HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
					HPDF_Page_ShowText(page, "Liste de rendez-vous");
					HPDF_Page_EndText(page);
					minus_height += 20;
					HPDF_Page_SetFontAndSize(page, font, 14);




					struct Rendezvous rend;
					fopen_s(&f2, "rendezvous.dat", "rb");
					// rewind(f2);

					while (fread(&rend, sizeof(struct Rendezvous), 1, f2) == 1) {
						if (rend.id_pat == pats[pat_index].id && strcmp(rend.status, "Waiting") != 0) {
							str[0] = '\0';
							strcpy_s(str, sizeof str, "La date de rendez-vous: ");
							strcat_s(str, sizeof str, rend.date);
							strcat_s(str, sizeof str, " [");
							strcat_s(str, sizeof str, strcmp(rend.status, "Refused") == 0 ? "Refusée" : "Acceptée");
							strcat_s(str, sizeof str, "]");
							strcat_s(str, sizeof str, " [Dr. ");
							strcat_s(str, sizeof str, rend.nom_med);
							strcat_s(str, sizeof str, "]");


							HPDF_Page_BeginText(page);
							HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - minus_height);
							HPDF_Page_ShowText(page, str);
							HPDF_Page_EndText(page);
							minus_height += 20;


						}
					}

					fclose(f2);














					char chemin[150] = "dossiers-patients/DOSSIER_";
					efface_espace(pats[pat_index].nom);
					strcat_s(chemin, sizeof chemin, pats[pat_index].nom);
					strcat_s(chemin, sizeof chemin, ".pdf");
					HPDF_SaveToFile(pdf, chemin);

					HPDF_Free(pdf);
					printf("Une fichier PDF sous le nom %s a été generé.", chemin);
					char command[200] = {0};

					strcat_s(&command, sizeof(command), "start ");
					strcat_s(&command, sizeof(command), chemin);
					printf("%s", command);
					system(command);
					break;
				}
				}


				break;
			}

			

		}
		


			// =====================================================================================
			// =====================================================================================

	

	return 0;
}


