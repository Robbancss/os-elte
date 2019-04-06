#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

struct JobData
{
    char address[64];
    int placeSize;

    char painting[1];
    char wrappingCold[1];
    char wrappingHot[1];
    char electricianing[1];
    char heating[1];
    char kitchenFurniture[1];
    char upholsterer[1];

    char endDate[64];
};


int mainMenu();
void listOrders(FILE *fptr);
void newOrder(FILE *fptr);
void deleteOrder(FILE *fptr);
void editOrder(FILE *fptr);

char fileName[] = "orders2.txt";
int fileLineCounter = 0;

int main(int argc, char** argv)
{
    FILE *fptr = fopen(fileName, "r+");

    if (fptr == NULL) {
        fptr = fopen(fileName, "w+");
    }

    char ch;
    do
    {
        ch = fgetc(fptr);
        if (ch == '\n')
        {
            fileLineCounter = fileLineCounter + 1;
        }
    } while (ch != EOF);
    printf("Number of lines in the file: %d", fileLineCounter);    
    fclose(fptr);

    while(0<1){
        int choosenMenuPoint = mainMenu();
        switch (choosenMenuPoint)
        {
            case 1:
                listOrders(fptr);
                break;
            case 2:
                newOrder(fptr);
                break;        
            case 3:
                deleteOrder(fptr);
                break;        
            case 4:
                editOrder(fptr);
                break;
            case 5:
                exit(0);
                break;
            default:
                perror("Rossz billentyut nyomtal meg!");
                // exit(0);
                break;
        }
    }

    return 0;
}

int mainMenu()
{
    printf("\n\n ********* Menu *********\n");
    printf("1 - Megrendelesek listazasa\n");
    printf("2 - Uj megrendeles felvetele\n");
    printf("3 - Megrendeles torlese\n");
    printf("4 - Megrendeles modositasa\n");
    printf("5 - Kilepes\n\n");

    int input;
    scanf("%d", &input);
    return input;
}

void listOrders(FILE *fptr)
{
    fptr = fopen(fileName, "r");
    printf("\n\ni - kert szolgaltatas, n - nem kert szolgaltatas\n");
    printf("Festo, burkolo(hideg), burkolo(meleg), villanyszerelo, viz-gaz-futesszerelo, konyha butor keszito, lakberendezo\n\n");
    printf("Az eddigi megrendelesek listaja:\n");
    if (fileLineCounter == 0 )
    {
        printf("Nincs meg megrendeles\n");
    }
    int tempLineCounter = 1;
    char ch;
    if (fileLineCounter > 0)
    {
        printf("%d) - ", tempLineCounter);
        tempLineCounter = tempLineCounter + 1;
    }
    do
    {
        ch = fgetc(fptr);
        if (ch == '\n')
        {
            putchar(ch);
            if (tempLineCounter <= fileLineCounter)
            {
                printf("%d) - ", tempLineCounter);
                tempLineCounter = tempLineCounter + 1;
            }
        }
        else
        {
            putchar(ch);
        }
    } while (ch != EOF);
    fclose(fptr);
}

void newOrder(FILE *fptr)
{
    fptr = fopen(fileName, "a");
    
    struct JobData nO;
    printf("Kerem adja meg a kovetkezo adatokat!\n");

    printf("Lakoingatlan cime: ");
    scanf("%s", nO.address);
    fputs(nO.address, fptr);
    fputs(" ", fptr);

    printf("Lakoingatlan merete: ");
    scanf("%d", &nO.placeSize);
    fprintf(fptr, "%d", nO.placeSize);
    fputs(" ", fptr);

    printf("Ker festest (i\\n): ");
    scanf("%s", nO.painting);
    fputs(nO.painting, fptr);
    fputs(" ", fptr);

    printf("Ker burkolo(hideg) (i\\n): ");
    scanf("%s", nO.wrappingCold);
    fputs(nO.wrappingCold, fptr);
    fputs(" ", fptr);

    printf("Ker burkolo(meleg) (i\\n): ");
    scanf("%s", nO.wrappingHot);
    fputs(nO.wrappingHot, fptr);
    fputs(" ", fptr);

    printf("Ker villanyszerelot (i\\n): ");
    scanf("%s", nO.electricianing);
    fputs(nO.electricianing, fptr);
    fputs(" ", fptr);

    printf("Ker viz-gaz-futesszerelot (i\\n): ");
    scanf("%s", nO.heating);
    fputs(nO.heating, fptr);
    fputs(" ", fptr);

    printf("Ker konyha butor keszito (i\\n): ");
    scanf("%s", nO.kitchenFurniture);
    fputs(nO.kitchenFurniture, fptr);
    fputs(" ", fptr);

    printf("Ker lakberendezo (i\\n): ");
    scanf("%s", nO.upholsterer);
    fputs(nO.upholsterer, fptr);
    fputs(" ", fptr);

    printf("Munka elvegzesenek a hatarideje: ");
    scanf("%s", nO.endDate);
    fputs(nO.endDate, fptr);
    
    // Put new line after the new order
    fputs("\n", fptr);
    fileLineCounter = fileLineCounter + 1;
    fclose (fptr);
}

void deleteOrder(FILE *fptr)
{
    listOrders(fptr);
    int deletedLine = 0;
    FILE *tempfptr = fopen("temp.txt", "w");
    fptr = fopen(fileName, "r");
    if (fileLineCounter != 0)
    {
        printf("Adja meg annak a sornak a szamat amit torolni szeretne:");
        scanf("%d", &deletedLine);

        int temp = 1;
        char ch = 'A';
        while (ch != EOF)
        {
            ch = fgetc(fptr);
            if (temp != deletedLine)
            {
                if (ch != EOF)
                {
                    fputc(ch, tempfptr);
                }
            }
            if (ch == '\n')
            {
                temp = temp + 1;
            }
        }
        fileLineCounter = fileLineCounter - 1;
        fclose(tempfptr);
        fclose(fptr);
        remove(fileName);
        rename("temp.txt", fileName);
    }
    else
    {
        printf("A fajl ures, nem tudsz torolni..\n");
    }
}

void editOrder(FILE *fptr)
{
    listOrders(fptr);
    int deletedLine = 0;
    FILE *tempfptr = fopen("temp.txt", "w");
    fptr = fopen(fileName, "r");
    if (fileLineCounter != 0)
    {
        printf("Adja meg annak a sornak a szamat amit akar irni:");
        scanf("%d", &deletedLine);

        int onlyOnce = 1;
        int temp = 1;
        char ch = 'A';
        while (ch != EOF)
        {
            ch = fgetc(fptr);
            if (temp != deletedLine)
            {
                if (ch != EOF)
                {
                    fputc(ch, tempfptr);
                }
            }
            else
            {
                if (onlyOnce == 1)
                {
                    struct JobData nO;
                    printf("Kerem adja meg a kovetkezo adatokat!\n");

                    printf("Lakoingatlan cime: ");
                    scanf("%s", nO.address);
                    fputs(nO.address, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Lakoingatlan merete: ");
                    scanf("%d", &nO.placeSize);
                    fprintf(tempfptr, "%d", nO.placeSize);
                    fputs(" ", tempfptr);

                    printf("Ker festest (i\\n): ");
                    scanf("%s", nO.painting);
                    fputs(nO.painting, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker burkolo(hideg) (i\\n): ");
                    scanf("%s", nO.wrappingCold);
                    fputs(nO.wrappingCold, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker burkolo(meleg) (i\\n): ");
                    scanf("%s", nO.wrappingHot);
                    fputs(nO.wrappingHot, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker villanyszerelot (i\\n): ");
                    scanf("%s", nO.electricianing);
                    fputs(nO.electricianing, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker viz-gaz-futesszerelot (i\\n): ");
                    scanf("%s", nO.heating);
                    fputs(nO.heating, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker konyha butor keszito (i\\n): ");
                    scanf("%s", nO.kitchenFurniture);
                    fputs(nO.kitchenFurniture, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Ker lakberendezo (i\\n): ");
                    scanf("%s", nO.upholsterer);
                    fputs(nO.upholsterer, tempfptr);
                    fputs(" ", tempfptr);

                    printf("Munka elvegzesenek a hatarideje: ");
                    scanf("%s", nO.endDate);
                    fputs(nO.endDate, tempfptr);
                    // Put new line after the new order
                    fputs("\n", tempfptr);
                    onlyOnce = 2;
                }
            }
            if (ch == '\n')
            {
                temp = temp + 1;
            }
        }
        fclose(tempfptr);
        fclose(fptr);
        remove(fileName);
        rename("temp.txt", fileName);
    }
    else
    {
        printf("A fajl ures, nem tudsz atirni megrendelest..\n");
    }
}