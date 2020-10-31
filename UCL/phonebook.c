#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SEARCH 1
#define LIST 2
#define ADD 3
#define REMOVE 4
#define SAVE 5
#define LOAD 6
#define QUIT 7
#define MAXLINELENGTH 80
#define PHONEBOOKSIZE 1000

struct entry
{
  char *name;
  char *phoneNumber;
};

struct entry *phoneBook[PHONEBOOKSIZE];
void displayMenu(void);
void go(void);
int getMenuOption(void);
void doOption(int);
void listAllEntries(void);
void searchForEntry(void);
void addEntry(void);
void removeEntry(void);
void savePhoneBook(void);
void loadPhoneBook(void);
char* readString(char*);
void removeNewLine(char*);
struct entry *createEntry(char*, char*);
void initialiseSampleData(void);

void go()
{
  while (true)
  {
    displayMenu();
    int option = getMenuOption();
    if (option == QUIT)
    {
      break;
    }
    else
    {
      doOption(option);
    }
  }
}

void displayMenu()
{
  printf("\nPhone Book\n");
  printf("%i. Search for a phone number\n", SEARCH);
  printf("%i. List all entries in the phone book\n", LIST);
  printf("%i. Add a new entry\n", ADD);
  printf("%i. Remove an entry\n", REMOVE);
  printf("%i. Save the phone book to a file\n", SAVE);
  printf("%i. Load a phone book from a file\n", LOAD);
  printf("%i. Quit\n", QUIT);
}

int getMenuOption()
{
  int option = 0;
  char *input = readString("Enter selection: ");
  sscanf(input,"%i",&option);
  free(input);
  return option;
}

void doOption(int option)
{
  switch (option)
  {
    case SEARCH : searchForEntry(); break;
    case LIST : listAllEntries(); break;
    case ADD : addEntry(); break;
    case REMOVE : removeEntry(); break;
    case SAVE : savePhoneBook(); break;
    case LOAD : loadPhoneBook(); break;
    default : printf("\nSorry - don't recognise that option, try again\n");
  }
}

void searchForEntry()
{
  printf("\n\nSearch Phone Book\n");
  char *name = readString("Enter the person's name: ");
  int index = 0;
  while (phoneBook[index] != NULL)
  {
    if (!strcmp(phoneBook[index]->name, name))
    {
      printf("The phone number is: %s\n", phoneBook[index]->phoneNumber);
      free(name);
      return;
    }
    index++;
  }
  printf("Sorry - no entry found\n");
  free(name);
}

void listAllEntries()
{
  if (phoneBook[0] == NULL)
  {
    printf("\nThere are no entries in the phone book\n");
    return;
  }
  int index = 0;
  while (phoneBook[index] != NULL)
  {
    printf("Entry %i: Name: %s  Number: %s\n",
           index + 1, phoneBook[index]->name, phoneBook[index]->phoneNumber);
    index++;
  }
}

void addEntry()
{
  printf("\nAdd entry to phone book\n");
  int index = -1;
  while(phoneBook[++index] != NULL);
  if (index > PHONEBOOKSIZE-2)
  {
    printf("Sorry, the phone book is full\n");
    return;
  }
  
  char *name = readString("Enter the person's name: ");
  char *number = readString("Enter the person's phone number: ");
  struct entry *entry = createEntry(name, number);
  phoneBook[index] = entry;
  phoneBook[index+1] = NULL;
  free(name);
  free(number);
}

void removeEntry()
{
  printf("\nRemove entry from phone book\n");
  char *name = readString("Enter the name of the person to remove: ");
  int index = 0;
  while((phoneBook[index] != NULL) && (strcmp(phoneBook[index]->name, name)))
  {  
    index++;
  }
  if (phoneBook[index] == NULL)
  {
    printf("No entry found for %s, nothing removed\n", name);
    free(name);
    return;
  }
  struct entry *removed = phoneBook[index];
  do 
  {
    phoneBook[index] = phoneBook[index+1];
  } while (phoneBook[++index] != NULL);
  free(removed->name);
  free(removed->phoneNumber);
  free(removed);
  free(name);
}

void savePhoneBook()
{
  printf("\nSave the phone book to a file\n");
  char *fileName = readString("Enter the file name: ");
  FILE *outputFile = fopen(fileName,"w");
  if (outputFile == NULL)
  {
    printf("\nUnable to write to file - phone book not saved.\n");
    free(fileName);
    return;
  }
  int index = 0;
  while (phoneBook[index] != NULL)
  {
    fprintf(outputFile, "%s\n", phoneBook[index]->name);  
    fprintf(outputFile, "%s\n", phoneBook[index]->phoneNumber); 
    index++;
  }
  fclose(outputFile);
  free(fileName);  
}

void loadPhoneBook()
{
  printf("\nLoad a phone book from a file\n");
  char *fileName = readString("Enter the file name: ");
  FILE *inputFile = fopen(fileName,"r");
  if (inputFile == NULL)
  {
    printf("\nUnable to read from file - phone book not loaded.\n");
    free(fileName);
    return;
  }  
  
  int index = 0;
  char name[MAXLINELENGTH];
  char phoneNumber[MAXLINELENGTH];
  while (index < PHONEBOOKSIZE-1)
  {
    fgets(name,MAXLINELENGTH-1,inputFile);
    char *input = fgets(phoneNumber,MAXLINELENGTH-1,inputFile);
    if (input == NULL)
    {
      break;
    }
    removeNewLine(name);
    removeNewLine(phoneNumber);
    phoneBook[index] = createEntry(name, phoneNumber);
    index++;
  }
  
  phoneBook[index] = NULL;
  fclose(inputFile);
  free(fileName);  
}

void removeNewLine(char *buffer)
{
  size_t length = strlen(buffer);
  if (length == 0)
  {
    return;
  }
  if (buffer[length-1] == '\n')
  {
    buffer[length-1] = '\0';
  }
}

char* readString(char* prompt)
{
  char buffer[MAXLINELENGTH];
  printf("%s", prompt);
  fgets(buffer, MAXLINELENGTH, stdin);
  size_t inputLength = strlen(buffer);
  char *input = calloc(sizeof(char), inputLength);
  strncpy(input, buffer, inputLength-1);
  input[inputLength] = '\0';
  return input;
}
struct entry *createEntry(char* name, char* phoneNumber) 
{
  struct entry *entry = calloc(sizeof(struct entry),1);
  entry->name = calloc(sizeof(char), strlen(name) + 1);
  strcpy(entry->name,name);
  entry->phoneNumber = calloc(sizeof(char), strlen(phoneNumber) + 1);
  strcpy(entry->phoneNumber, phoneNumber);
  return entry;
}

void initialiseSampleData()
{
  phoneBook[0] = createEntry("Person 1", "12345");
  phoneBook[1] = createEntry("Someone", "4567");
  phoneBook[2] = NULL;
}

int main (void)
{
  phoneBook[0] = NULL;
  initialiseSampleData();
  go();
  return 0;
}
