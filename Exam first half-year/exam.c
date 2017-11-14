#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>

typedef struct 
{
	char first_name[20];
	char last_name[20];
	char phon_number[20];
}Contact;

enum
{
	VIEW = 1, SEARCH, ADD, EXIT
}MainMenu = VIEW;

Contact* displ_list_cont(Contact[],const int);
void book_popul(Contact[],int*);
int sort_fun(const Contact*, const Contact*);
void search_func(Contact[], int, _Bool*);
Contact* view_func(Contact[], int*);

int main()
{
	FILE *a_c;
	fopen_s(&a_c, "amount_cont", "ab+");
	if (a_c == NULL)
	{
		printf_s("File haven't been opened.");
		exit(0);
	}
	//Initial amount of contacts. Programm start.
	int amount_cont = 0;
	fread_s(&amount_cont, sizeof(int), sizeof(int), 1, a_c);
	fclose(a_c);
	//Displaing contacts
	Contact *p_st_book = NULL;
	if (amount_cont == 0)
	{
		printf_s("You don't have any contacts.\n\n\n\n\n\n\n\n\n\n\n\n");
	}
	else
	{
		p_st_book = displ_list_cont(p_st_book, amount_cont);
	}
	//For Search
	_Bool search_view = 0;
	//Main menu
	while (1)
	{
		printf_s("<<1.View contact>> <<2.Search>> <<3.Creat contact>> <<4.Exit>> :");
		do
		{
			scanf_s("%d", &MainMenu);
			getchar();
		} while (MainMenu < 1 || MainMenu > 4);
		switch (MainMenu)
		{
		case VIEW:
			system("cls");
			search_view = 0;
			p_st_book = view_func(p_st_book, &amount_cont);
			break;
		case SEARCH:
			system("cls");
			search_func(p_st_book, amount_cont, &search_view);
			break;
		case ADD:
			system("cls");
			search_view = 0;
			book_popul(p_st_book,&amount_cont);
			break;
		case EXIT:
			system("cls");
			free(p_st_book);
			exit(0);
			break;
		}
		
		if (!search_view)
		{
			system("cls");
			if (amount_cont == 0)
			{
				printf_s("You don't have any contacts.\n\n\n\n\n\n\n\n\n\n\n\n");
			}
			else
			{
				p_st_book = displ_list_cont(p_st_book, amount_cont);
			}
		}
	}
	return 0;
	
}

Contact* view_func(Contact list_cont[], int *amount_cont)
{
	//Choise parameters
	Contact for_cmp;
	printf_s("Enter the first name:");
	scanf_s("%s", for_cmp.first_name, 20);
	getchar();
	puts("");
	printf_s("Enter the last name:");
	scanf_s("%s", for_cmp.last_name, 20);
	getchar();
	puts("");
	printf_s("Enter the phone number:");
	scanf_s("%s", for_cmp.phon_number, 20);
	//concurrence index
	int contact_index;

	for (int i = 0; i < *amount_cont; ++i)
	{
		if (strcmp(list_cont[i].first_name, for_cmp.first_name) == 0 && strcmp(list_cont[i].last_name, for_cmp.last_name) == 0 &&
			strcmp(list_cont[i].phon_number, for_cmp.phon_number) == 0)
		{
			contact_index = i;
			break;
		}
		else if (i + 1 == *amount_cont)
		{
			system("cls");
			printf_s("!!!Contact does not exist!!!");
			Sleep(2000);
			return list_cont;
		}
	}
	//view menu
	system("cls");
	printf_s("%-20s  %-20s  %-20s\n", list_cont[contact_index].first_name, list_cont[contact_index].last_name, list_cont[contact_index].phon_number);
	puts("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf_s("<<1.For call>> <<2.For edit>> <<3.For delet>> <<4.To main menu>> :");
	int choice;
	do
	{
		scanf_s("%d", &choice);
		getchar();
	} while (choice < 1 || choice > 4);

	if (choice == 1)
	{
		system("cls");
		printf_s("Calling %s...\n\n\n\n\n<<Press Enter>> - Hang up", list_cont[contact_index].first_name);
		getchar();
		return list_cont;
	}
	else if (choice == 2)
	{
		system("cls");
		while (choice != 4)
		{
			system("cls");
			printf_s("%-20s  %-20s  %-20s\n", list_cont[contact_index].first_name, list_cont[contact_index].last_name, list_cont[contact_index].phon_number);
			puts("\n\n\n\n\n\n\n\n\n\n\n\n");
			printf_s("<<1.Change first name>> <<2.Change last name>> <<3.Change number>> <<4.Save and Exit>>");
			do
			{
				scanf_s("%d", &choice);
				getchar();
			} while (choice < 1 || choice > 4);
			if (choice == 1)
			{
				system("cls");
				printf_s("Enter new first name:");
				scanf_s("%s", list_cont[contact_index].first_name, 20);
				getchar();
			}
			else if (choice == 2)
			{
				system("cls");
				printf_s("Enter new last name:");
				scanf_s("%s", list_cont[contact_index].last_name, 20);
				getchar();
			}
			else if (choice == 3)
			{
				system("cls");
				printf_s("Enter new number:");
				scanf_s("%s", list_cont[contact_index].phon_number, 20);
				getchar();
			}
		}
		//save changes
		FILE *fbook;
		fopen_s(&fbook, "book.txt", "w");
		fwrite(list_cont, sizeof(Contact), *amount_cont, fbook);
		fclose(fbook);
	}
	else if (choice == 3)
	{
		//deleting contact
		system("cls");
		puts("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf_s("Are you sure that you desire delet {%s %s %s}? (yes/no)",
			list_cont[contact_index].first_name, list_cont[contact_index].last_name, list_cont[contact_index].phon_number);
		char agree[5];
		do
		{
			scanf_s("%s", agree, 5);
			getchar();
			for (unsigned i = 0; i < strlen(agree); ++i)
			{
				agree[i] = toupper(agree[i]);
			}
		} while (strcmp(agree, "YES") != 0 && strcmp(agree, "NO") != 0);
		if (strcmp(agree, "YES") == 0)
		{
			FILE *fcount_cont, *fbook;
			fopen_s(&fcount_cont, "amount_cont", "wb");
			fopen_s(&fbook, "book.txt", "w");
			if (fcount_cont == NULL || fbook == NULL)
			{
				printf_s("File haven't opened!");
				exit(0);
			}

			list_cont[contact_index] = list_cont[*amount_cont - 1];
			list_cont = (Contact*)realloc(list_cont, sizeof(Contact) * (*amount_cont - 1));
			*amount_cont -= 1;
			fwrite(amount_cont, sizeof(int), 1, fcount_cont);
			fwrite(list_cont, sizeof(Contact), *amount_cont, fbook);

			fclose(fbook);
			fclose(fcount_cont);
		}
	}
	else
	{
		return list_cont;
	}

	return list_cont;
}

void search_func(Contact list_cont[], int amount_cont, _Bool *search_view)
{
	//Search menu
	displ_list_cont(list_cont, amount_cont);
	printf_s("<<1.By name>> <<2.By number>> <<3.Show entire list>> <<4.To Main menu>> :");
	int mode_search;
	do
	{
		scanf_s("%d", &mode_search);
		getchar();
	} while (mode_search > 4 || mode_search < 1);
	if (mode_search == 1)
	{
		char first_name[20];
		system("cls");
		printf_s("Enter a first name or part of it:");
		scanf_s("%s", first_name, 20);
		getchar();
		system("cls");
		*search_view = 1;
		for (int i = 0; i < amount_cont; ++i)
		{
			if (strstr(list_cont[i].first_name, first_name))
			{
				printf_s("%-20s  %-20s  %-20s\n", list_cont[i].first_name, list_cont[i].last_name, list_cont[i].phon_number);
			}
		}
		puts("\n\n\n\n\n\n\n\n\n\n\n");
	}
	else if (mode_search == 2)
	{
		char number[20];
		system("cls");
		printf_s("Enter a number or part of it:");
		scanf_s("%s", number, 20);
		getchar();
		system("cls");
		*search_view = 1;
		for (int i = 0; i < amount_cont; ++i)
		{
			if (strstr(list_cont[i].phon_number, number))
			{
				printf_s("%-20s  %-20s  %-20s\n", list_cont[i].first_name, list_cont[i].last_name, list_cont[i].phon_number);
			}
		}
		puts("\n\n\n\n\n\n\n\n\n\n\n");
	}
	else if (mode_search == 3)
	{
		*search_view = 0;
	}
	else
	{
		return;
	}
}
//for qsort()
int sort_fun(const Contact* arg1, const Contact* arg2)
{
	return strcmp(arg1->first_name, arg2->first_name);
}

Contact* displ_list_cont(Contact list_cont[],const int amount_cont)
{
	FILE *book;
	fopen_s(&book, "book.txt", "r");
	if (book == NULL)
	{
		printf_s("File haven't been opened.");
		exit(0);
	}
	list_cont = (Contact*)calloc(amount_cont, sizeof(Contact));
	if (list_cont == NULL)
	{
		printf_s("Malloc don't allocate a memory.");
		exit(0);
	}
	fread_s(list_cont, sizeof(Contact) * amount_cont, sizeof(Contact), amount_cont, book);
	//display by increasing order
	qsort(list_cont, amount_cont, sizeof(Contact), sort_fun);
	for (int i = 0; i < amount_cont; ++i)
	{
		printf_s("%-20s   %-20s   %-20s\n", list_cont[i].first_name, list_cont[i].last_name, list_cont[i].phon_number);
	}
	puts("\n\n\n\n\n\n\n\n\n\n\n");
	fclose(book);
	
	return list_cont;
}

void book_popul(Contact list_cont[], int *amount_cont)
{
	FILE *fbook;
	fopen_s(&fbook, "book.txt", "a+");
	if (fbook == NULL)
	{
		printf_s("File haven't opened!");
		exit(0);
	}
	fseek(fbook, 0l, SEEK_END);
	//add new cont
	Contact new_cont;
	printf_s("Enter the first name:");
	scanf_s("%s", new_cont.first_name, 20);
	getchar();
	puts("");
	printf_s("Enter the last name:");
	scanf_s("%s", new_cont.last_name, 20);
	getchar();
	puts("");
	printf_s("Enter the phone number:");
	scanf_s("%s", new_cont.phon_number, 20);
	getchar();
	//checking for existing contact
	if (*amount_cont > 0)
	{
		for (int i = 0; i < *amount_cont; ++i)
		{
			if (strcmp(list_cont[i].first_name, new_cont.first_name) == 0 && strcmp(list_cont[i].last_name, new_cont.last_name) == 0 && 
				strcmp(list_cont[i].phon_number, new_cont.phon_number) == 0)
			{
				system("cls");
				printf_s("!!!Contact already exist!!!");
				Sleep(2000);
				fclose(fbook);
				return;
			}
		}
	}
	fwrite(&new_cont, sizeof(Contact), 1, fbook);
	
	FILE *fcount_cont;
	fopen_s(&fcount_cont, "amount_cont", "rb+");
	if (fcount_cont == NULL)
	{
		printf_s("File haven't opened!");
		exit(0);
	}
	//increment amount of contacts
	*amount_cont += 1;
	fwrite(amount_cont, sizeof(int), 1, fcount_cont);
	
	fclose(fcount_cont);
	fclose(fbook);
}