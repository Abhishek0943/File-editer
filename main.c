#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_TEXT_LENGTH 10000

void createFile(char *filename) {
  FILE *file = fopen(filename, "w");
  if (file) {
    printf("File created: %s\n", filename);
    fclose(file);
  } else {
    printf("Error creating file: %s\n", filename);
  }
}

void loadFile(char *filename, char *text) {
  FILE *file = fopen(filename, "r");
  if (file) {
    printf("Loading %s...\n", filename);
    fread(text, sizeof(char), MAX_TEXT_LENGTH, file);
    fclose(file);
  } else {
    printf("Error loading file: %s\n", filename);
  }
}

void saveFile(char *filename, char *text) {
  FILE *file = fopen(filename, "w");
  if (file) {
    printf("Saving %s...\n", filename);
    fwrite(text, sizeof(char), strlen(text), file);
    fclose(file);
  } else {
    printf("Error saving file: %s\n", filename);
  }
}

void searchAndReplace(char *text, char *search, char *replace) {
  char *found = strstr(text, search);
  if (found) {
    int searchLength = strlen(search);
    int replaceLength = strlen(replace);
    int offset = found - text;
    memmove(text + offset + replaceLength, text + offset + searchLength,
            strlen(text) - offset - searchLength + 1);
    memcpy(text + offset, replace, replaceLength);
  }
}

int main() {
  char filename[MAX_FILENAME_LENGTH];
  char text[MAX_TEXT_LENGTH] = "";

  printf("Console Text Editor\n");

  while (1) {
    printf("\nOptions:\n");
    printf("1. Create New File\n");
    printf("2. Load File\n");
    printf("3. Save File\n");
    printf("4. Edit Text\n");
    printf("5. Search and Replace\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    switch (choice) {
    case 1:
      printf("Enter the filename: ");
      scanf("%s", filename);
      createFile(filename);
      break;
    case 2:
      printf("Enter the filename: ");
      scanf("%s", filename);
      loadFile(filename, text);
      break;
    case 3:
      if (filename[0] != '\0') {
        saveFile(filename, text);
      } else {
        printf("No file to save. Create or load a file first.\n");
      }
      break;
    case 4:
      if (filename[0] != '\0') {
        printf("Enter text to append (empty line to finish):\n");
        while (1) {
          char line[MAX_TEXT_LENGTH];
          if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // End of input
          }
          if (line[0] == '\n') {
            break; // Empty line signals the end
          }
          strncat(text, line, sizeof(text) - strlen(text) - 1);
        }
      } else {
        printf("No file to edit. Create or load a file first.\n");
      }
      break;
    case 5:
      if (filename[0] != '\0') {
        char search[MAX_TEXT_LENGTH], replace[MAX_TEXT_LENGTH];
        printf("Enter the search string: ");
        scanf("%s", search);
        printf("Enter the replacement string: ");
        scanf("%s", replace);
        searchAndReplace(text, search, replace);
      } else {
        printf("No file to edit. Create or load a file first.\n");
      }
      break;
    case 6:
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
