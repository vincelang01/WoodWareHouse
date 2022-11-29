#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct fa{
    string nev, mertegy;
    double ar, menny;
    int id;
}fa;

void loading();
int valaszt(fa *fp, int *h, string fileName);
int options();
void vopt();
void kilep();
int foglal(int *h, string *fileName);
void hosszV(int *h, string fileName);
void beolvasas(fa *fp, int h, string fileName);
int file_ujra();
void hozzaAd(fa *fpp, int **h, string fileName);
int mertell(string m);
void del(fa *fp, int **h, string fileName);
void editFile(fa *fp, int *h, string fileName);
int editOptions();
void editV();
int editNev(fa *fp, int h, string fileName);
int editAr(fa *fp, int h, string fileName);
int editMert(fa *fp, int h, string fileName);
void elfelBetolt(fa *fp, int h, string fileName);
int elad(fa *fp, int h, string fileName);
int feltolt(fa *fp, int h, string fileName);
void betolt(fa *fpp, int h, string fileName);
void rendez(fa *fpp, int h);
void folytat();
int ment();
void lista(fa *f, int h);
void vl();
