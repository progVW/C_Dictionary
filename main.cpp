#include <iostream>
#include <stdio.h>
#include "header.h"
#define MAX 128

int main()
{
    FILE *input = fopen("data.txt", "r");
    if (input == nullptr)
    {
        std::cout << "Ошибка открытия файла для чтения\n";
        return 0;
    }
    int N;
    fscanf(input, "%d\n", &N);
    Person *list = new Person[N];
    char str[MAX];
    for (int i = 0; i < N; i++)
    {
        fgets(str, MAX, input);
        razbor(str, list[i]);
    }
    if (fclose(input) != 0)
    {
        std::cout << "Ошибка закрытия файла для чтения\n";
    }
    int choice;
    while (true)
    {
        choice = menu();
        switch (choice) {
            case 1: addKontakt(list, N); break;
            case 2: delKontakt(list, N); break;
            case 3: printList(list, N); break;
            case 4: printSort(list, N); break;
            case 5: findKontakt(list, N); break;
            case 6: findBirthdays(list, N); break;
            case 7: finish(list, N);
            delete[] list;
            return 0;
        }
    }
    return 0;
}