#include <stdio.h>

void firstFit() {
  int block_arr[10], file_arr[10], allocated[10] = {0};
  int fragments[10] = {0}, blocks[10], files[10];
  int m, n, number_of_blocks, number_of_files, temp;
  int externalFragmentation = 0;
  printf("\nEnter the Total Number of Blocks:\t");
  scanf("%d", &number_of_blocks);
  printf("Enter the Total Number of Files:\t");
  scanf("%d", &number_of_files);
  printf("\nEnter the Size of the Blocks:\n");
  for (m = 0; m < number_of_blocks; m++) {
    printf("Block No.[%d]:\t", m + 1);
    scanf("%d", &blocks[m]);
  }
  printf("Enter the Size of the Files:\n");
  for (m = 0; m < number_of_files; m++) {
    printf("File No.[%d]:\t", m + 1);
    scanf("%d", &files[m]);
  }
  for (m = 0; m < number_of_files; m++) {
    for (n = 0; n < number_of_blocks; n++) {
      if (block_arr[n] != 1) {
        temp = blocks[n] - files[m];
        if (temp >= 0) {
          file_arr[m] = n;
          allocated[m] = 1;
          break;
        }
      }
    }
    if (!allocated[m]) {
      printf("No block can be allocated for file %d\n", m + 1);
      continue;
    }
    fragments[m] = temp;
    block_arr[file_arr[m]] = 1;
  }
  printf("\nFile Number\tBlock Number\tFile Size\tBlock Size\tFragment");
  for (m = 0; m < number_of_files; m++) {
    externalFragmentation += fragments[m];
    if (allocated[m])
      printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", m, file_arr[m], files[m],
             blocks[file_arr[m]], fragments[m]);
  }
  printf("\nThe external fragmentation is: %d\n\n", externalFragmentation);
}

void bestFit() {
  int fragments[10] = {0}, block[10], file[10], m, n, number_of_blocks,
      number_of_files, temp, lowest = 10000, allocated[10] = {0};
  static int block_arr[10], file_arr[10];
  int externalFragmentation;
  printf("\nEnter the Total Number of Blocks:\t");
  scanf("%d", &number_of_blocks);
  printf("\nEnter the Total Number of Files:\t");
  scanf("%d", &number_of_files);
  printf("\nEnter the Size of the Blocks:\n");
  for (m = 0; m < number_of_blocks; m++) {
    printf("Block No.[%d]:\t", m + 1);
    scanf("%d", &block[m]);
  }
  printf("Enter the Size of the Files:\n");
  for (m = 0; m < number_of_files; m++) {
    printf("File No.[%d]:\t", m + 1);
    scanf("%d", &file[m]);
  }
  for (m = 0; m < number_of_files; m++) {
    for (n = 0; n < number_of_blocks; n++) {
      if (block_arr[n] != 1) {
        temp = block[n] - file[m];
        if (temp >= 0) {
          if (lowest > temp) {
            file_arr[m] = n;
            lowest = temp;
          }
        }
      }
      if (lowest != 10000) {
        fragments[m] = lowest;
        allocated[m] = 1;
        block_arr[file_arr[m]] = 1;
      }
      lowest = 10000;
    }
    if (!allocated[m] && n == number_of_blocks - 1) {
      printf("No block can be allocated for block %d\n", m + 1);
    }
  }
  printf("\nFile Number\tFile Size\tBlock Number\tBlock Size\tFragment");
  for (m = 0; m < number_of_files && file_arr[m] != 0; m++) {
    externalFragmentation += fragments[m];
    if (allocated[m])
      printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", m, file[m], file_arr[m],
             block[file_arr[m]], fragments[m]);
  }
  printf("\nThe external fragmentation is: %d\n\n", externalFragmentation);
}

void worstFit() {
  int externalFragmentation;
  int fragments[10] = {0}, blocks[10], files[10];
  int m, n, number_of_blocks, number_of_files, temp, top = 0,
                                                     allocated[10] = {0};
  static int block_arr[10], file_arr[10];
  printf("\nEnter the Total Number of Blocks:\t");
  scanf("%d", &number_of_blocks);
  printf("Enter the Total Number of Files:\t");
  scanf("%d", &number_of_files);
  printf("\nEnter the Size of the Blocks:\n");
  for (m = 0; m < number_of_blocks; m++) {
    printf("Block No.[%d]:\t", m + 1);
    scanf("%d", &blocks[m]);
  }
  printf("Enter the Size of the Files:\n");
  for (m = 0; m < number_of_files; m++) {
    printf("File No.[%d]:\t", m + 1);
    scanf("%d", &files[m]);
  }
  for (m = 0; m < number_of_files; m++) {
    for (n = 0; n < number_of_blocks; n++) {
      if (block_arr[n] != 1) {
        temp = blocks[n] - files[m];
        if (temp >= 0) {
          if (top < temp) {
            file_arr[m] = n;
            top = temp;
          }
        }
      }
      if (top) {
        allocated[m] = 1;
        fragments[m] = top;
        block_arr[file_arr[m]] = 1;
      }
      top = 0;
      if (!allocated[m] && n == number_of_blocks - 1) {
        printf("No block can be allocated for block %d\n", m + 1);
      }
    }
  }
  printf("\nFile Number\tFile Size\tBlock Number\tBlock Size\tFragment");
  for (m = 0; m < number_of_files; m++) {
    externalFragmentation += fragments[m];
    if (allocated[m])
      printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", m, files[m], file_arr[m],
             blocks[file_arr[m]], fragments[m]);
  }
  printf("\nThe external fragmentation is: %d\n\n", externalFragmentation);
}

int main() {
  int option;
  printf("1. First fit\n2. Best fit\n3.Worst fit\n");
  printf("Enter your choice: ");
  scanf("%d", &option);
  switch (option) {
    case 1:
      firstFit();
      break;
    case 2:
      bestFit();
      break;
    case 3:
      worstFit();
      break;
  }
  return 0;
}