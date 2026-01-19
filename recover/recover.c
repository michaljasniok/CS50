// biblioteki
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
// prototypy
bool header(unsigned char *block);
void new_file(int counter, char *name, FILE **jpg);
// main
int main(int argc, char *argv[])
{
    // sprawdz czy jest wystarczajaca ilosc agumentów
    if (argc != 2)
    {
        printf("invalid input\n");
        return 1;
    }
    // otwórz plik i sprawdź czy wszystko działa
    char *disk_name = argv[1];
    FILE *disk = fopen(disk_name, "r");
    if (disk == NULL)
    {
        printf("Can not open file\n");
        return 1;
        fclose(disk);
    }
    unsigned char block[512];
    int jpgs_counter = 0;
    FILE *jpg = NULL;
    char file_name[8];
    // odczytaj plik
    fseek(disk, 0, SEEK_END);
    long file_size = ftell(disk);
    fseek(disk, 0, SEEK_SET);
    if (file_size < 512)
    {
        printf("Wrong file format\n");
        return 3;
        fclose(disk);
    }
    while (fread(&block, 512, 1, disk) == 1)
    {
        // szukaj nagłówka jpg
        if (header(block))
        {
            if (jpgs_counter > 0)
            {
                fclose(jpg);
            }
            // stwórz nowy plik
            new_file(jpgs_counter, file_name, &jpg);
            if (jpg == NULL)
            {
                printf("Can't create new file\n");
                return 4;
                fclose(jpg);
                fclose(disk);
            }
            jpgs_counter++;
        }
        // zapisz wszystko (do nowego pliku jpg)
        if (jpgs_counter > 0)
        {
            fwrite(&block, 512, 1, jpg);
        }
    }
    // powtarzaj dopóki nie skończy sie dysk
    // zamknij wszystkie pliki
    if (disk != NULL)
    {
        fclose(disk);
    }
    if (jpg != NULL)
    {
        fclose(jpg);
    }
    return 0;
}
bool header(unsigned char *block)
{
    unsigned char check[16] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                               0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
    {
        for (int i = 0; i < 16; i++)
        {
            if (check[i] == block[3])
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}
void new_file(int counter, char *name, FILE **jpg)
{
    if (counter < 10)
    {
        sprintf(name, "00%i.jpg", counter);
        *jpg = fopen(name, "w");
    }
    else if (counter < 100)
    {
        sprintf(name, "0%i.jpg", counter);
        *jpg = fopen(name, "w");
    }
    else if (counter > 100)
    {
        sprintf(name, "%i.jpg", counter);
        *jpg = fopen(name, "w");
    }
    return;
}
