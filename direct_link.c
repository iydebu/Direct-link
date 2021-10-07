#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <conio.h>
#endif
void logo()
{
    printf("    ____  _                __     ___       __  \n");
    printf("   / __ \\(_)_______  _____/ /_   / (_)___  / /__ \n");
    printf("  / / / / / ___/ _ \\/ ___/ __/  / / / __ \\/ //_/ \n");
    printf(" / /_/ / / /  /  __/ /__/ /_   / / / / / / , <    \n");
    printf("/_____/_/_/   \\___/\\___/\\__/  /_/_/_/ /_/_/|_|   \n\n");
}

#ifdef _WIN32
int clip(const char *output)
{
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return 1;
}
#endif

int main()
{
#ifdef _WIN32
    SetConsoleTitle("Direct-link");
#endif
    int i = 0;
    char *link = (char *)malloc(sizeof(char) * 100);
    char *id = (char *)malloc(sizeof(char) * 100);
    logo();
    printf("\nEnter the link: ");
    fgets(link, 100, stdin);
    char *index = strstr(link, "d/");
    if (index == NULL)
    {
        printf("\ninvalid link\n");
        system("pause");
        return 0;
    }
    index += 2;
    for (i = 0; index[i] != '/' && i <= 100; i++)
        ;
    if (i >= 100)
    {
        printf("\ninvalid link\n");
        system("pause");
        return 0;
    }
    index[i] = '\0';
    strcpy(id, index);
    strcpy(link, "https://drive.google.com/uc?export=download&id=");
    strcat(link, id);
    printf("\nYour link:- %s\n", link);
    (clip(link) == 1) ? printf("\nCopied succesfully...\n") : printf("\nfailed to copy!\n");
    printf("\n*****DEBU******\n");
#ifdef _WIN32
    system("pause");
#else
    getch();
#endif
}