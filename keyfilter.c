#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void ABECEDNE_SERADIT(int ascii_k_serazeni[], int delka)
{
    const int podporovane_znaky[95] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126}; //pole cisel 32 az 126
    int pocitadlo = 0; //lokalni promenna - urcuje misto vysledneho pole razeni znaku, aby nedoslo k preteceni nebo nepresnemu umisteni znaku
    int mezi[delka]; //pole jako mezistupen kopirovani do pozadovaneho pole, ktere ma byt serazeno
    for (size_t i = 0; i < sizeof(podporovane_znaky)/sizeof(podporovane_znaky[0]); i++) //na zaklade velkych znaku ascii projde pole - kolik ma pole znaku - bere prvni znak
        for (int j = 0; j < delka; j++) //prochazi pole cisel ascii - vezme kazdy znak z ascii
            if (ascii_k_serazeni[j] == podporovane_znaky[i]) //pokud najde cislo odpovidajici cislu z pole posune se na B a zapise a na zacatek pole pocatecni
                {
                    mezi[pocitadlo] = ascii_k_serazeni[j];
                    pocitadlo++;
                }
    for(int j = 0; j < delka; j++) //cyklus, ktery presne prepise serazene pole do pole, se kterym se dale pracuje
        ascii_k_serazeni[j] = mezi[j];
}                     //funkce, ktera pomoci konstantniho pole cisel od 32 do 126 radi vsechny podporovane znaky z ASCII tabulky
void NA_VELKA_BEZ_MEZER(char *argument, int delka, int CHCI_BEZ_MEZER)
{
    for (int i = 0; i < delka; i++) //cyklus, ktery prochazi pole argument a narazi-li na pismeno tak jej prevede na velke
        if (isalpha(argument[i]))
            argument[i] = toupper(argument[i]);
        else if((argument[i] == ' ') && (CHCI_BEZ_MEZER == 1)){ //obohaceno o cyklus, ktery detekuje mezeru a odstranuje je posunutim celeho pole, pokud si o to uzivatel zazada 0/1 - NE/ANO
            for (int j = 0; j < (delka - i); j++)
                argument[i + j] = argument[i + j + 1];
            i--;
        }
}       //funkce prevede vsechny znaky na velke a neresi mezerovost, prebira argument, ktery rozhoduje zda chceme odstranit mezery nebo ne
void ODSTRANIT_DUPLICITU(char *argument, int delka)
{
    for (int j = 0; j < delka; j++)
        for (int i = 0; i < delka; i++)
            if ((argument[j] == argument[i]) && (i != j))
                argument[i] = ' ';
}                          //fukce odstranujici duplicitu v poli
int main(int argc, char *argv[])
{
    char radek[102];                    //promenna pro jeden radek ze STDINu(souboru) o maximalni delce 100 znaku(2 rezervovany pro \n a \0)
    char radek_cele_mesto[102];         //vystupni promenna pro vybrana pismena mest, doplnujici pismena atd
    char rezervni_radek[102];           //radek slouzi pro pamatovani si soucasneho radku ve sve PUVODNI podobe
    char vystup_mest[102] = {'\0'};     //pole plne koncu stringu, kvuli problemum s merenim velikosti pole
    int pocet = 0;                      //jednoduchy counter
    int cele = 0;                       //promenna pro uchovavani stavu nalezeni cele adresy

    if(argc < 0 || argc > 2)
    {
        printf("Prilis mnoho nebo malo argumentu!");
        return 1;
    }

    if (argc == 1)
    {
        char poc_pismena_mest[95] = { [0 ... 94] = ' ' };   //pole pro vsechny pocatecni znaky o velikosti presne vsech podporovanych znaku + 2
        int pocet_adres = 0;                                //counter, ktery urcuje kolik potencialnich adres je v danem soboru
        while(fgets(radek, sizeof(radek), stdin) != NULL) //dostane radek z STDINu dokud neni NULL nebo dokud ma co cist
        {
            int pocet_znaku_v_radku = 0;                     //pocita kolik presne podporovanych znaku je v radku
            if((radek[0] != '\n'))                           //naslednujici rozhodovani pocita mozne adresy na kazdem radku, POKUD RADEK NEZACINA \0 nebo \n tak se jedna o PLATNOU ADRESU
                if(radek[0] != '\0')
                    pocet_adres++;                           //inkrementuje pocet platnych adres
            strcpy(rezervni_radek, radek);      //prekopiruje soucasny radek do DOCASNE PAMETI pro uchovani puvodni hodnoty nacteneho radku
            for(size_t i = 0; i < strlen(radek); i++)   //cyklus kontroluje kolik je v radku podporovanych znaku
                if((radek[i] >= 32) && (radek[i] <= 126))
                    pocet_znaku_v_radku++;                  //inkrementuje pocet znaku pokud najde podporovany
            if(pocet_znaku_v_radku > 100)
                return 0;
            if(strlen(radek) == 100)                    //pokud je pocet znaku v radku presne roven 100 tak vlozi na posledni misto pole znak noveho radku \n
                radek[100] = '\n';


            for (size_t i = 0; i < strlen(poc_pismena_mest); i++)                       //cyklus uklada pocatecni pismena kazdeho radku na misto v poli, ktere je prazdne a zaroven zde neni jiz stejne pismeno
                if ((poc_pismena_mest[i] != radek[0]) && (poc_pismena_mest[i] == ' '))      //pokud je misto prazdne ulozi na nej nove pismeno
                {
                    poc_pismena_mest[i] = toupper(radek[0]);
                    pocet++;
                    break;
                }
                else if(poc_pismena_mest[i] == radek[0])    //pokud nalezne v poli pismeno, ktere tam jiz bylo ulozeno z predchoziho radku tak skonci cyklus jelikoz by se jednalo o duplicitu
                    break;
                else if(poc_pismena_mest[i] != radek[0])    //pokud jsou pismena proste ruzna tak pokracuje a hleda neobsazane misto v poli
                    continue;
        }

        if(pocet_adres == 1)                                //podminka rozhodujici o automatickem vypsani adresy z rezevrniho radku,
        {
            printf("Found: ");
            for (size_t i = 0; i < strlen(rezervni_radek); ++i)
                printf("%c", toupper(rezervni_radek[i]));
            return 0;
        }

        int poc_pismena_mest_fit_ascii[pocet];                                      //priprava pole cisel pro abecedni usporadani
        for(int i = 0; i < pocet; i++)
            poc_pismena_mest_fit_ascii[i] = poc_pismena_mest[i];                    //prevadeni charu na int

        ABECEDNE_SERADIT(poc_pismena_mest_fit_ascii, pocet);    //volani funkce seradit abecedne

        printf("Enable: ");                                                 //vypis serazenych hodnot z funkce
        for (int i = 0; i < pocet; i++)
            printf("%c", poc_pismena_mest_fit_ascii[i]);
    }
    else if (argc == 2)
    {
        int pocet_moznych_adres = 0;                                                //pocitadlo moznych adres v souboru
        char *argument = argv[1]; //pointer na argument
        NA_VELKA_BEZ_MEZER(argument, strlen(argument), 1); //volani funkce prevodu na velka pismena s argumentem ANO(1) pro odstraneni mezer

        while(fgets(radek, sizeof(radek), stdin) != NULL)         //dostane radek ze souboru
        {
            int pocet_znaku_v_radku = 0;                                            //counter poctu znaku v radku
            for(size_t i = 0; i < strlen(radek); i++)
                if((radek[i] >= 32) && (radek[i] <= 126))
                    pocet_znaku_v_radku++;
            if(pocet_znaku_v_radku > 100)                                           //najde-li vice nez 100 znaku v radku tak program automaticky ukonci
                return 0;
            if(strlen(radek) == 100)                                            //radek o poctu presnych 100 znaku bude ukoncen \n a \0
                radek[100] = '\n';

            strcpy(radek_cele_mesto, radek);                            //prekopirovani soucasneho radku do DOCASNE PAMETI
            NA_VELKA_BEZ_MEZER(radek, strlen(radek), 1);        //volani funkce na velka s odrstranenim mezer ANO(1)

            for(size_t j = 0; j < strlen(argument); j++)                                      //cyklus kontroluje zda je argument identicky s radkem
                if((argument[j] == radek[j]) && (j == strlen(argument)-1))
                {
                    pocet_moznych_adres++;
                    strcpy(rezervni_radek, radek_cele_mesto);
                }
                else if(argument[j] != radek[j])
                    break;


            if (strlen(argument) <= strlen(radek))                              //pokud ma argument vice pismen nez porovnavane mesto
            {
                for (size_t i = 0; i < strlen(argument); i++)                       //cyklus s opakovanim poctu pismen argumentu
                    if ((argument[i] == radek[i]) && (i == strlen(argument)-1))     //pokud se posledni a vsechna predesla pismena shoduji
                    {
                        if (radek[i+1] != '\n')                                         //pokud je dalsi index pismeno a ne konec radku
                            vystup_mest[strlen(vystup_mest)] = radek[i+1];
                        else
                        {
                            cele = 1;
                            NA_VELKA_BEZ_MEZER(radek_cele_mesto, strlen(radek_cele_mesto), 0);
                            strcat(vystup_mest, radek_cele_mesto);         //do vybrana mesta ulozi cely radek, bylo nalezeno cele mesto
                        }
                    }
                    else if(argument[i] != radek[i])                                    //pokud se v cemkoliv neshoduje argument s radkem tak se vysledek zahodi, neni to nase adresa
                        break;
            }

        }

        if(cele == 1)                                   //pokud bylo nalezeno prave jedno cele mesto(zadano cele a nalezeno cele)
        {
            printf("Found: ");                  //probehne vypis tohoto mesta
            for(size_t j = 0; j < strlen(vystup_mest); j++)
                printf("%c", vystup_mest[j]);
            return 0;
        }

        if(pocet_moznych_adres == 1)                 //pokud byla nalezena prave jedna mozna adresa odpovidajici prefixu
        {
            printf("Found: ");                //probehne jeji vypis
            for(size_t j = 0; j < strlen(rezervni_radek); j++)
                printf("%c", toupper(rezervni_radek[j]));
            return 0;
        }

        if(strlen(vystup_mest) >= 1)            //pokud adresa potrebuje doplneni, tedy bylo nalezeno jedno a vice pismen
        {
            int ascii_arr[strlen(vystup_mest)]; //priprava na usporadani, prevod na ciselne pole
            ODSTRANIT_DUPLICITU(vystup_mest, strlen(vystup_mest));                         //odstraneni duplicit
            NA_VELKA_BEZ_MEZER(vystup_mest, strlen(vystup_mest), 1);        //prevod na velka pismena bez mezer
            for (size_t j = 0; j < strlen(vystup_mest); j++)
                ascii_arr[j] = vystup_mest[j];
            ABECEDNE_SERADIT(ascii_arr, strlen(vystup_mest));                          //abcedni serazeni vyslednych pismen
            printf("Enable: "); //vypis na output
            for (size_t j = 0; j < strlen(vystup_mest); j++)
                printf("%c", ascii_arr[j]);
        }
        else                                                                                                 //nebylo-li nalezeno ani jedno pismeno mozne k doplneni nebo zadna z podminek neprobehla tak adresa neexistuje
            printf("Not found");
        return 0;
    }
    return 0;
}