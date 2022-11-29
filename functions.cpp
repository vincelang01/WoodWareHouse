#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include "functions.h"

using namespace std;

void rendez(fa *fpp, int h){
    for(int i = 0; i < h - 1; i++){
        for(int k = i + 1; k < h; k++){
            if(fpp[k].nev < fpp[i].nev){
                swap(fpp[k].nev, fpp[i].nev);
                swap(fpp[k].ar, fpp[i].ar);
                swap(fpp[k].menny, fpp[i].menny);
                swap(fpp[k].mertegy, fpp[i].mertegy);
            }
        }
    }
}

int ment(){
    char v;
    cin.ignore();
    cout << "\n-------------------\nValtozas tortent!\nSzeretne menteni?(i/n) ";
    cin >> v;
    if(v == 'n'){ cout << "\nValtoztatasok torlese!\n"; return 0;}
    else { cout << "\nValtoztatasok mentese!\n"; return 1; }
}

void betolt(fa *fpp, int h, string fileName){
    if(ment()){
        fstream file;
        file.open(fileName, ios::out);
        for(int i = 0; i < h - 1; i++){
            for(int k = i + 1; k < h; k++){
                if(fpp[k].nev < fpp[i].nev){
                    swap(fpp[k].nev, fpp[i].nev);
                    swap(fpp[k].ar, fpp[i].ar);
                    swap(fpp[k].menny, fpp[i].menny);
                    swap(fpp[k].mertegy, fpp[i].mertegy);
                }
            }
        }
        for(int i = 0; i < h; i++){
            file << fpp[i].id << "\t" << fpp[i].nev << "\t" << fpp[i].ar << "\t" << fpp[i].menny
            << "\t" << fpp[i].mertegy << endl;
        }
        file.close();
    }
}

int mertell(string m){
    if(m == "m3" || m == "m2" || m == "fm" || m == "db"){ return 0; }
    else { cout << "Ervenytelen mertekegyseg!\nAlabbiakbol valaszthat:\nm, m2, m3, db\n"; return 1; }
}

void hozzaAd(fa *fp, int **h, string fileName){
    //fp[1].nev = "Zsalu";
    //cout << fp[1].nev << endl;
    system("cls");
    string nNev, me;
    int j, foly = 0;
    do{
        j = 0;
        cout << "Nev: "; cin >> nNev;
        while(j < **h && fp[j].nev != nNev){
            j++;
        }
        if(j >= **h){ foly = 1; fp[j].nev = nNev; }
        else { foly = 0; cout << "Mar letezik ez a nev, adjon meg egy masikat!\n"; }
    }while( !foly );
    cout << "ar: "; cin >> fp[j].ar;
    cout << "Mennyiseg: "; cin >> fp[j].menny;
    do{
        cout << "Mertekegyseg: "; cin >> fp[j].mertegy;
    }while( mertell(fp[j].mertegy) );
    fp[j].id = fp[j - 1].id + 1;
    (**h)++;
    rendez(fp, **h);
    j = 0;
    while(j < **h && fp[j].nev != nNev){
        j++;
    }
    cout << "Az uj aru azonosotoja: " << j + 1;
    betolt(fp, **h, fileName);
}

void beolvasas(fa *fp, int h, string fileName){
    fstream file;
    file.open(fileName, ios::in);
    for(int i = 0; i < h; i++){
        file >> fp[i].id >> fp[i].nev >> fp[i].ar >> fp[i].menny >> fp[i].mertegy;
    }
    file.close();
}

//vonal options
void vopt(){
    for(int i = 0; i < 65; i++){
        cout << "_";
    }
}

int options(){
    int v;
    system("cls");
    cout << "\nFatelep raktar\n";
    vopt();
    cout << "\n\n 1. Lista\t2. Hozzaadas\t3. Torles\t4. Szerkesztes\n\n\t5. Eladas\t6. Aru feltoltes\t7. Kilepes\n";
    vopt();
    cout << endl;
    cin >> v;
    return v;
}

void kilep(){
    cout << "Nyomj egy ENTER-t a kilepeshez!";
    cin.ignore();
    cin.get();
}

void loading(){
    system("cls");
    cout << "\n\n\n\n\n\n\t\t\t\t\t\tLoading";
    char x = '.';
    cout << x;
    for(int i = 0; i < 4; i++){
        cout << x;
        Sleep(600);
    }
    system("cls");
}

int valaszt(fa *fp, int *h, string fileName){
    int val = options();
    switch (val){
        case 1:
            lista(fp, *h);
            folytat();
            break;
        case 2:
            hozzaAd(fp, &h, fileName);
            folytat();
            break;
        case 3:
            del(fp, &h, fileName);
            folytat();
            break;
        case 4:
            editFile(fp, h, fileName);
            folytat();
            break;
        case 5:
            if(elad(fp, *h, fileName)) {cout << "Nincs ilyen azonosito!";}
            folytat();
            break;
        case 6:
            if( feltolt(fp, *h, fileName) ){ cout << "Nincs ilyen azonosito"; }
            folytat();
            break;
        case 7:
            cout << "Kilepes a programbel!\n";
            return 1;
        default:
            cout << "Nem tortent semmi! Probalkozzon masik szammal!\n";
    }
    return 0;
}

int feltolt(fa *fp, int h, string fileName){
    int fAz, mc; // mennyiseg check
    double bemenny;
    system("cls");
    lista(fp, h);
    cout << "Azonosito: "; cin >> fAz;
    int j = 0;
    while(j < h && fp[j].id != fAz){
        j++;
    }
    if(j >= h) { return 1; }
    do{
        if(mc) { cout << "Nem lehet 0-nal kisebb szamot beirni!\n"; }
        cout << "Feltoltes mennyisege (" << fp[j].mertegy << "): "; cin >> bemenny;
        if(bemenny < 0) { mc = 1; }
        else { mc = 0; }
    }while(mc);
    fp[j].menny += bemenny;
    cout << fp[j].nev << " Uj mennyisege: " <<fp[j].menny << " " << fp[j].mertegy << endl;
    elfelBetolt(fp, h, fileName);
    return 0;
}

void elfelBetolt(fa *fp, int h, string fileName){
    fstream file;
    file.open(fileName, ios::out);
    for(int i = 0; i < h; i++){
        file << fp[i].id << "\t" << fp[i].nev << "\t" << fp[i].ar << "\t" << fp[i].menny << "\t" << fp[i].mertegy << "\n";
    }
    file.close();
}

int elad(fa *fp, int h, string fileName){
    int elaz, tov = 0;
    double elMenny, afa = 0.27;
    system("cls");
    lista(fp, h);
    cout << "Azonosito: "; cin >> elaz;
    int j = 0;
    while (j < h && fp[j].id != elaz){
        j++;
    }
    if(j >= h) { return 1; }
    do{
        if(tov == 1) { system("cls"); cout << "Nincs elegendo mennyiseg raktaron!\n"; }
        else if(tov == 2) { system("cls"); cout << "Nem lehet 0-n�l kevesebbet eladni!\n"; }
        cout << fp[j].nev << " kapacitasa: " << fp[j].menny << " " << fp[j].mertegy;
        cout << "\nElad�s mennyisege: "; cin >> elMenny;
        if(elMenny > fp[j].menny){ tov = 1;}
        else if(elMenny < 0) { tov = 2; }
    }while(elMenny > fp[j].menny || elMenny < 0);
    if(elMenny > 0){
        cout.precision(1);
        cout << "\n�ra:\nNetto: " << fixed << fp[j].ar * elMenny  << " Ft\nBrutto:" << fp[j].ar * elMenny + fp[j].ar * afa << " Ft";
        fp[j].menny -= elMenny;
        elfelBetolt(fp, h, fileName);
    }
    return 0;
}

void editV(){
    for(int i = 0; i < 48; i++){
        cout << "_";
    }
    cout << endl;
}

int editOptions(){
    int v;
    cout << "Szerkesztes:\n";
    editV();
    cout<<"\n1. Nev\t\t2. Ar\t\t3. Mertekegyseg\n";
    editV();
    cin >> v;
    return v;
}

void editFile(fa *fp, int *h, string fileName){
    system("cls");
    switch(editOptions()){
    case 1:
        if( editNev(fp, *h, fileName) ) { cout << "Nem letezik ilyen azonosito!"; }
        break;
    case 2:
        if( editAr(fp, *h, fileName) ) { cout << "Nem letezik ilyen azonosito!"; }
        break;
    case 3:
        if( editMert(fp, *h, fileName) ) { cout << "Nem l�tezik ilyen azonos�t�!"; }
        break;
    default: cout<<"Nincs ilyen opcio!\n";
    }
}

int editMert(fa *fp, int h, string fileName){
    //Módosítandó mértékegység azonosító
    int mAz;
    //Új mennyiség
    string nMenny;
    system("cls");
    lista(fp, h);
    cout << "Modositando mennyiseg azonositoja: ";
    cin.ignore(); cin >> mAz;
    int j = 0;
    while(j < h && fp[j].id != mAz){
        j++;
    }
    if(j >= h) { return 1;}
    do{
        cout << endl << mAz << " szamu azonosito uj mennyisege: "; cin.ignore(); cin >> nMenny;
    }while(mertell(nMenny));
    fp[mAz - 1].mertegy = nMenny;
    betolt(fp, h, fileName);
    return 0;
}

int editAr(fa *fp, int h, string fileName){
    //Módosítandó ár azonosító
    int aAz;
    //Új ár
    double nAr;
    system("cls");
    lista(fp, h);
    cout << "Modositando ar azonositoja: ";
    cin.ignore(); cin >> aAz;
    int j = 0;
    while(j < h && fp[j].id != aAz){
        j++;
    }
    if(j >= h) { return 1;}
    cout << endl << aAz << " szamu azonosito uj ara: "; cin.ignore(); cin >> nAr;
    fp[aAz - 1].ar = nAr;
    betolt(fp, h, fileName);
    return 0;
}

int editNev(fa *fp, int h, string fileName){
    //Módosítandó név azonosító
    int nAz;
    //Új név
    string nNev;
    system("cls");
    lista(fp, h);
    cout << "Modositando nev azonositoja: ";
    cin.ignore(); cin >> nAz;
    int j = 0;
    while(j < h && fp[j].id != nAz){
        j++;
    }
    if(j >= h) { return 1;}
    do{
        j = 0;
        cout << endl << nAz << " szamu azonosito uj neve: "; cin.ignore(); cin >> nNev;
        while(j < h && nNev != fp[j].nev){
            j++;
        }
        if(j < h){ cout << "Ez a nev mar letezik! Adjon meg egy masik nevet!"; }
    }while(j < h);
    fp[nAz - 1].nev = nNev;
    betolt(fp, h, fileName);
    return 0;
}

void del(fa *fp, int **h, string fileName){
    system("cls");
    lista(fp, **h);
    fstream temp;
    temp.open("temp.txt", ios::out);
    int da; //delete azonosito
    cout << "Terlendo aru azonositoja: "; cin >> da;
    for(int i = 0; i < **h; i++){
        if(fp[i].id != da) {
            if(fp[i].id < da){
                temp << fp[i].id << "\t" << fp[i].nev << "\t" << fp[i].ar << "\t"
                << fp[i].menny << "\t" << fp[i].mertegy << endl;
            }
            else if(fp[i].id > da) {
                temp << fp[i].id - 1 << "\t" << fp[i].nev << "\t" << fp[i].ar << "\t"
                << fp[i].menny << "\t" << fp[i].mertegy << endl;
            }
        }
    }
    temp.close();
    temp.open("temp.txt", ios::in);
    int j = 0;
    while(j < **h && temp.good()){
        temp >> fp[j].id >> fp[j].nev >> fp[j].ar >> fp[j].menny >> fp[j].mertegy;
        j++;
    }
    (**h)--;
    temp.close();
    remove("temp.txt");
    betolt(fp, **h, fileName);
    cout << "Sikeres torles!";
}

//vonal lista
void vl(){
    for(int i = 0; i < 50; i++){
        cout << "_";
    }
    cout << endl;
}

void lista(fa *f, int h){
    system("cls");
    int limit = 10000;
    for(int i = 0; i < h; i++){
        cout<<f[i].id<<"\t" << f[i].nev;
        if(f[i].nev.length() < 8) cout << "\t\t";
        else cout << "\t";
        cout << f[i].ar << " Ft";
        if(f[i].ar < limit) cout << "\t";
        cout << "\t" << f[i].menny << " " << f[i].mertegy << endl;
    }
    vl();
    cout<<"Id\tNev\t\tAr\t\tMennyiseg\n\n";
}

void folytat(){
    cout << "\nNyomj egy ENTER-t a folytatashoz!";
    cin.ignore();
    cin.get();
    system("cls");
}

int foglal(int *h, string *fileName){
    string ch;
    fstream file;
    cout << "\n\n\n\n\n\n\t\t\t\t\tMegnyitando fajl neve: "; cin >> *fileName;
    file.open(*fileName, ios::in);
    loading();
    if( (file.fail()) ) {
        cout << "\n\n\n\n\n\n\t\t\t\t\t\tFajl betoltese sikertelen!";
        Sleep(1000);
        file.close();
        return -1;
    }
    while(file.good()){
        getline(file, ch);
        (*h)++;
    }
    (*h)--;
    file.close();
    cout << "\n\n\n\n\n\n\t\t\t\t\t\tFajl betoltve!";
    Sleep(1000);
    return 0;
}

void hosszV(int *h, string fileName){
    fstream file;
    *h = 0;
    file.open(fileName, ios::in);
    string ch;
    while(file.good()){
        getline(file, ch);
        (*h)++;
    }
    (*h)--;
    file.close();
}

int file_ujra(){
    char ujraa;
    system("cls");
    cout << "\n\n\n\n\n\n\t\t\t\t\tHiba tortent! Ujra szeretne probalni? (i/n)"; cin >> ujraa;
    if(ujraa == 'i') { system("cls"); return 0; }
    else { system("cls"); cout << "\n\n\n\n\n\n\t\t\t\t\tViszlat!\n"; return 1; }
}