#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void set_mode_and_report(const char* filename, int mask)
{
    // если не удается найти файл или неверный параметр доступа
    if (_chmod(filename, mask) == -1)
    {
        switch (errno)
        {
        case EINVAL:
            fprintf(stderr, "Неверный параметр доступа.\n");
            break;
        case ENOENT:
            fprintf(stderr, "Не удается найти файл.\n");
            break;
        default:
            //никогда не будет достигнута
            fprintf(stderr, "Непредвиденная ошибка.\n");
        }
    }
    else
    {
        if (mask == _S_IREAD)
            printf("Режим файла изменен: запрет на запись.\n");
        else if (mask & _S_IWRITE)
            printf("Режим файла изменен: чтение и запись.\n");
        else if (mask == 0)
            printf("Режим файла изменен: запрет на чтение и запись.\n");
    }
    fflush(stderr);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    // создаю файл и пробую его прочесть
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("Не удалось создать и открыть файл.\n");
    }
    else printf("Файл успешно создан, открыт и изменен.\n");
    // запрещаю чтение файла
    set_mode_and_report("crt_chmod.c_input ", 0);
    //пробую прочесть файл
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("Не удалось открыть файл.\n");
    }
    else printf("Файл успешно открыт и изменен.\n");

    //разрешаю чтение файла
    set_mode_and_report("crt_chmod.c_input ", _S_IWRITE);
    //пробую прочесть файл
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("Не удалось открыть файл.\n");
    }
    else printf("Файл успешно открыт и изменен.\n");
    return 0;
}