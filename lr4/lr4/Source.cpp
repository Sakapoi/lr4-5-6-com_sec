#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void set_mode_and_report(const char* filename, int mask)
{
    // ���� �� ������� ����� ���� ��� �������� �������� �������
    if (_chmod(filename, mask) == -1)
    {
        switch (errno)
        {
        case EINVAL:
            fprintf(stderr, "�������� �������� �������.\n");
            break;
        case ENOENT:
            fprintf(stderr, "�� ������� ����� ����.\n");
            break;
        default:
            //������� �� ����� ����������
            fprintf(stderr, "�������������� ������.\n");
        }
    }
    else
    {
        if (mask == _S_IREAD)
            printf("����� ����� �������: ������ �� ������.\n");
        else if (mask & _S_IWRITE)
            printf("����� ����� �������: ������ � ������.\n");
        else if (mask == 0)
            printf("����� ����� �������: ������ �� ������ � ������.\n");
    }
    fflush(stderr);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    // ������ ���� � ������ ��� ��������
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("�� ������� ������� � ������� ����.\n");
    }
    else printf("���� ������� ������, ������ � �������.\n");
    // �������� ������ �����
    set_mode_and_report("crt_chmod.c_input ", 0);
    //������ �������� ����
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("�� ������� ������� ����.\n");
    }
    else printf("���� ������� ������ � �������.\n");

    //�������� ������ �����
    set_mode_and_report("crt_chmod.c_input ", _S_IWRITE);
    //������ �������� ����
    if (system("echo /* End of file */ >> crt_chmod.c_input") == 1)
    {
        printf("�� ������� ������� ����.\n");
    }
    else printf("���� ������� ������ � �������.\n");
    return 0;
}