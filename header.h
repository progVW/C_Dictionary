#ifndef HEADER
#define HEADER

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#define MAX 128

struct Date
{
    int day;
    int mounth;
    int year;
};

struct Person
{
    char surname[MAX];
    char name[MAX];
    char phone[MAX];
    Date birthday;
};

void razbor(char *str, Person &contact); // разбираем строку на ликсемы
void printList(Person *list, int N);     // печать запис. книжки
int menu();                              // вывод меню
void addKontakt(Person *&list, int &N);  // добавить контакт
void delKontakt(Person *&list, int &N);  // удалить контакт
void printSort(Person *list, int N);     // напечатать отсортированную запис. книжку
void findKontakt(Person *list, int N);   // найти контакт
void findBirthdays(Person *list, int N); // найти все контакты по дате рождения
void finish(Person *list, int N);        // завершение работы программы
void printKontakt(Person *kontakt);      // печать одного контакта
void delByNumber(Person *&list, int &N,  // удалить контакт по номеру
                 int i);
void cls();                              // очистка экрана

void cls()
{
    for (int k = 0; k < 30; k++)
    {
        std::cout << '\n';
    }
}

void razbor(char *str, Person &contact)
{
    char *part = NULL;
    part = strtok(str, ";");
    strcpy(contact.surname, part);
    part = strtok(NULL, ";");
    strcpy(contact.name, part);
    part = strtok(NULL, ";");
    strcpy(contact.phone, part);
    part = strtok(NULL, "/");
    contact.birthday.day = atoi(part);
    part = strtok(NULL, "/");
    contact.birthday.mounth = atoi(part);
    part = strtok(NULL, "\n");
    contact.birthday.year = atoi(part);
    return;
}

void printList(Person *list, int N)
{
    cls();
    std::cout << "\nСодержание телефоной книжки: " << '\n';
    for (int k = 0; k < N; k++)
    {
        std::cout << "ФИО: " << list[k].surname << ' ' << list[k].name << " тел.: " << list[k].phone;
        std::cout << " День рождения: " << std::setw(2) << std::setfill('0') << list[k].birthday.day << '.';
        std::cout << std::setw(2) << std::setfill('0') << list[k].birthday.mounth << '.' << list[k].birthday.year;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}

void printKontakt(Person *kontakt)
{
    std::cout << "ФИО: " << kontakt->surname << ' ' << kontakt->name << " тел.: " << kontakt->phone;
    std::cout << " День рождения: " << std::setw(2) << std::setfill('0') << kontakt->birthday.day << '.';
    std::cout << std::setw(2) << std::setfill('0') << kontakt->birthday.mounth << '.' << kontakt->birthday.year;
    std::cout << std::endl;
}

int menu()
{
    std::cout << "1 - добавить запись\n";
    std::cout << "2 - удалить запись\n";
    std::cout << "3 - вывести без сортировки\n";
    std::cout << "4 - вывести список отсортированный по фамилии\n";
    std::cout << "5 - поиск по фамилии\n";
    std::cout << "6 - список именниников в определённом месяце\n";
    std::cout << "7 - выход из программы\n";
    int k;
    std::cout << "Ваш выбор: ";
    std::cin >> k;
    while (k < 1 || k > 7)
    {
        std::cout << "Неверный выбор, повторите попытку.\n";
        std::cout << "Ваш выбор: ";
        std::cin >> k;
    }
    return k;
}

void addKontakt(Person *&list, int &N)
{
    std::cout << std::endl;
    Person *newList = new Person[N + 1];
    for (int k = 0; k < N; k++)
    {
        newList[k] = list[k];
    }
    std::cout << "Введите фамилию: ";
    std::cin >> newList[N].surname;
    std::cout << "Введите имя: ";
    char str[MAX];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';
    strcpy(newList[N].name, str);
    std::cout << "Введите телефон: ";
    std::cin >> newList[N].phone;
    std::cout << "Введите дату рождения через пробел: ";
    std::cin >> newList[N].birthday.day >> newList[N].birthday.mounth >> newList[N].birthday.year;
    delete[] list;
    list = newList;
    N++;
    std::cout << "Контакт добавлен!\n";
}

void delByNumber(Person *&list, int &N, int i)
{
    Person *newList = new Person[N - 1];
    int j = 0;
    for (int k = 0; k < N; k++)
    {
        if (j == i)
            continue;
        newList[j++] = list[k];
    }
    delete[] list;
    list = newList;
    N--;
}

void delKontakt(Person *&list, int &N)
{
    std::cout << "\nУдаление контакта\n";
    char str[MAX];
    std::cout << "\nВведите фамилию контакта для удаления: ";
    std::cin >> str;
    int count = 0;
    char choice;
    for (int k = 0; k < N; k++)
    {
        if (strcmp(list[k].surname, str) == 0)
        {
            printKontakt(&list[k]);
            std::cout << "Удалить контакт? Y/N: ";
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                delByNumber(list, N, k);
                k--;
                count++;
            }
        }
    }
    if (count == 0)
    {
        std::cout << "Контакты не найдены!\n";
    }
    else
    {
        std::cout << "Контакт удален.\n";
    }
}

void printSort(Person *list, int N)
{
    cls();
    std::cout << "\nСортировка по фамилии:\n";
    Person **master_ptr = new Person *[N];
    for (int k = 0; k < N; k++)
    {
        master_ptr[k] = &list[k];
    }
    for (int k = N - 1; k > 0; k--)
    {
        for (int i = 0; i < k; i++)
        {
            if (strcmp(master_ptr[i]->surname, master_ptr[i + 1]->surname) > 0)
            {
                std::swap(master_ptr[i], master_ptr[i + 1]);
            }
        }
    }

    for (int k = 0; k < N; k++)
    {
        printKontakt(master_ptr[k]);
    }
    std::cout << std::endl;
    delete[] master_ptr;
}

void findKontakt(Person *list, int N)
{
    cls();
    char str[MAX];
    std::cout << "\nВведите фамилию: ";
    std::cin >> str;
    int count = 0;
    std::cout << "Резултат поиска: \n";
    for (int k = 0; k < N; k++)
    {
        if (strcmp(list[k].surname, str) == 0)
        {
            printKontakt(&list[k]);
            count++;
        }
    }
    if (count == 0)
    {
        std::cout << "Контакт не найден.";
    }
    std::cout << std::endl;
}

void findBirthdays(Person *list, int N)
{
    int goal;
    std::cout << "\nВведите месяц рождения: ";
    std::cin >> goal;
    int count = 0;
    for (int k = 0; k < N; k++)
    {
        if (list[k].birthday.mounth == goal)
            count++;
    }
    if (count == 0)
    {
        std::cout << "В этом месяце именинников нет.\n";
        return;
    }
    Person **master_ptr = new Person *[count];
    int i = 0;
    for (int k = 0; k < N; k++)
    {
        if (list[k].birthday.mounth == goal)
        {
            master_ptr[i++] = &list[k];
        }
    }
    for (int k = N - 1; k > 0; k++)
    {
        for (int i = 0; i > k; i++)
        {
            if (master_ptr[i]->birthday.day > master_ptr[i + 1]->birthday.day)
            {
                std::swap(master_ptr[i], master_ptr[i + 1]);
            }
        }
    }
    std::cout << "Именинники в этом месяце: \n";
    for (int k = 0; k < count; k++)
    {
        printKontakt(master_ptr[k]);
    }
    delete[] master_ptr;
}

void finish(Person *list, int N)
{
    std::cout << "Завершение работы. Сохранить записи в файл? Y/N: ";
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        FILE *output = fopen("data.txt", "w");
        if (output == nullptr)
        {
            std::cout << "Ошибка открытия файла.";
            return;
        }
        fprintf(output, "%d\n", N);
        for (int k = 0; k < N; k++)
        {
            fprintf(output, "%s;%s;%s;%d/%d/%d\n", list[k].surname, list[k].name, list[k].phone,
                    list[k].birthday.day, list[k].birthday.mounth, list[k].birthday.year);
        }
        if (fclose(output) != 0)
        {
            std::cout << "Ошибка закрытия файла!\n";
        }
    }
}

#endif