#include <iostream>
#include <stdlib.h>
#include "functions.h"

using namespace std;

int main(){
    fa *f;
    string fileNev;
    int ujra = 0, hossz = 0, again, beolv = 0;
    setlocale(LC_ALL, "hun");
    while(again = foglal(&hossz, &fileNev)){
        if(again == -1) { again = file_ujra(); }
        if(again) { return 0; }
    }
    do{
        hosszV(&hossz, fileNev);
        f = new fa[hossz + 1];
        beolvasas(f, hossz, fileNev);
        rendez(f, hossz);
        ujra = valaszt(f, &hossz, fileNev);
        delete[] f;
    }while( !ujra );
    kilep();
    return 0;
}
