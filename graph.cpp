#include "graph.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <bitset>
#include "boost/dynamic_bitset.hpp"
#include "maximumindependentset.h"

Graph::Graph()
{

}

/*
 *  Dodanie krawedzi
 */

void Graph::addEdge(int v, int w)
{
    adjacentNodes[v][w]=1;
    adjacentNodes[w][v]=1;  // Note: the graph is undirected
}

int isPowerOfTwo (unsigned int x)
{
  return ((x != 0) && ((x & (~x + 1)) == x));
}
/*
 * Funkcja słuzaca do wybrania odpowiedniego wezla
 */
int Graph::getTmp()
{
    int max = -1; // maksymalna wartosc wezla
    int max_i; //zmienna do przechowywania numeru wezla
    for (int i =0; i < V; i++)
        if (color[i] == -1) //jesli wezel jest niepokolorowany
            if (tmp[i]>max) {
                max = tmp[i];
                max_i = i;
            }
    return max_i;
}

/*
 * Funkcja słuzaca do wybrania odpowiedniego wezla dla algorytmow binarnych
 */

int Graph::getLFRBitTmp()
{
    int max = 9999;
    int max_i;
    for (int i =0; i < V; i++)
        if (bitSize[i] == bitSizeMin && marked[i]==bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania
                                                                                 // oraz ilosc bitow potrzebnych do pokolorowania go jest mniejsza niz innych wezlow
            if (tmp[i]<max) {
                max = tmp[i];
                max_i = i;
            }
        }

    return max_i;
}

int Graph::getEqualBitTmp()
{
    int max = -1;
    int max_i;
    for (int i =0; i < V; i++)
        if (bitSize[i] == bitSizeMin && marked[i]==bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania
                                                                                 // oraz ilosc bitow potrzebnych do pokolorowania go jest mniejsza niz innych wezlow
            if (tmp[i]>max) {
                max = tmp[i];
                max_i = i;
            }
        }

    return max_i;
}

int Graph::getRandomNode()
{
    int max = -1;
    int max_i;

    int i = rand() % V;

        if ((color[i] == -1 || marked[i] == true) && bitSize[i] == bitSizeMin) { // jesli wezel jest niepokolorwany albo jest zaznaczony do dalszego kolorowania                                                                                 // oraz ilosc bitow potrzebnych do pokolorowania go jest mniejsza niz innych wezlow
            return i;
        }


}

/*
 * Algorytm kolorowania klasycznego LF
 */

void Graph::LFRColoring()
{
    std::vector<std::vector<int>> adjacentNodes = Graph::adjacentNodes; //inicjalizacja lokalnej listy wezlow
    int uncolored=V; //zmienna sluzaca do okreslenia ile wezlow zostalo do pokolorowania
    int node; //wezel
    int pos;

    vector<int>::iterator i;
    for (int u = 0; u<V; u++) {
        int size = 0;
        for (int j=0; j<V; j++){
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    //ustawienie wszystkich wezlow jako niepokolorowane
    for (int u = 0; u < V; u++) {
        color.push_back(-1);
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany kolor
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(V);
    for (int cr = 0; cr < V; cr++)
        used[cr] = false;

    // glowna petla algorytmu
    while (uncolored>0) {

        node = getTmp(); //wybor wezla

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {//iteracja po sasiednich wezlach
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1) // czy kolor jest uzyty
                used[color[pos]] = true; // zaznacz uzyty kolor
        }

        //wybierz pierwszy dostepny kolor
        int cr;
        for (cr = 0; cr < V; cr++)
            if (used[cr] == false)
                break;

        //przypisz pierwszy wolny kolor do wezla
        color[node] = cr;
        uncolored--;

        // zresetuj wartosci dla kolejnej iteracji
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i){
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1)
                used[color[pos]] = false;
        }
    }

    //wypisz wartosci
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;

    //wyczysc listy
    tmp.clear();
    color.clear();

}

void Graph::LFRColoring2()
{
    std::vector<std::vector<int>> adjacentNodes = Graph::adjacentNodes; //inicjalizacja lokalnej listy wezlow
    int uncolored=V; //zmienna sluzaca do okreslenia ile wezlow zostalo do pokolorowania
    int node; //wezel
    int pos;

    vector<int>::iterator i;
    for (int u = 0; u<V; u++) {
        int size = 0;
        for (int j=0; j<V; j++){
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    //ustawienie wszystkich wezlow jako niepokolorowane
    for (int u = 0; u < V; u++) {
        color.push_back(-1);
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany kolor
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(V);
    for (int cr = 0; cr < V; cr++)
        used[cr] = false;

    // glowna petla algorytmu
    while (uncolored>0) {

        node = getTmp(); //wybor wezla



        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {//iteracja po sasiednich wezlach
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1) // czy kolor jest uzyty
                used[color[pos]] = true; // zaznacz uzyty kolor
        }

        //wybierz pierwszy dostepny kolor
        int cr;
        for (cr = 0; cr < V; cr++)
            if ((cr==0 || isPowerOfTwo(cr)) && used[cr] == false){
                color[node] = cr;
                break;
            }

        if (color[node] == -1){
            for (cr = 0; cr < V; cr++)
                if (!isPowerOfTwo(cr) && used[cr] == false){
                    color[node] = cr;
                    break;
                }
        }
        //przypisz pierwszy wolny kolor do wezla
        uncolored--;

        // zresetuj wartosci dla kolejnej iteracji
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i){
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i==1)
                used[color[pos]] = false;
        }
    }

    //wypisz wartosci
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
                  << color[u] << std::endl;

    //wyczysc listy
    tmp.clear();
    color.clear();

}

/*
 * Algorytm kolorowania bitowego LF
 */

void Graph::LFRBitColoring()
{
   std::vector<std::vector<int>> adjacentNodes = Graph::adjacentNodes; //stworzenie lokalnej listy sasiednich wezlow
   // list<int> *coloredAdjacentNodes = new list<int> [V]; //stworzenie listy przetrzymujacej juz pokolorowane sasiednie wezly w danej iteracji

    int V=Graph::V; //stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int node; //zmienna przetrzymujaca numer wezla
    int pos;
    const boost::dynamic_bitset<> bZero(1, 0ul); //0 zapisane binarnie
    vector<int>::iterator i;

    int uncolored=V;
    for (int u = 0; u<V; u++) {
        int size = 0;
        for (int j=0; j<V; j++){
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }


    for (int u = 0; u < V; u++) {
        color.push_back(-1); //lista ktora ustala czy wezel zaczal byc kolorowany
        colorBit.push_back(bZero);  // lista przetrzymujaca kolor wezla w danym momencie (w bitach)
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;


    for (int cr = 0; cr < V; cr++) {
        bitSize.push_back(0); //lista do przetrzymywania wielkosci koloru w bitach (zaczyna się od 0, a nie od 1)
        marked.push_back(0); //oznaczenie wezla do dalszego kolorowania
    }
    bitSizeMin=0; //zmienna ustalajaca jaka jest najmniejsza ilosc bitow do pokolorowania wezla

    int rounds = 0; //ilosc rund w iteracji

    //glowna petla programu
    while (uncolored>0) {
        //cout << "petla, uncolored: " << uncolored << endl;
        node = getLFRBitTmp(); //wybranie wezla
        //cout << "petla, vector: " << node << endl;
        marked[node]++;
        if (bitSize[node]<bitSizeMin){
            continue;
        }

        //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji


        //przypisz bit 0 do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
  //dla kolejnych wezlow
            //sprawdz czy zostal wolny bit
            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                if (used[0]==true && used[1]==true) {
                    break; //jesli oba bity zostaly uzyte przejdz dalej
                }
             //   cout << "i: " << i - adjacentNodes[node].begin() << endl;
                pos = i - adjacentNodes[node].begin();
                if (color[pos] != -1 && *i == 1) { //jesli sasiad jest pokolorowany zaznacz uzyty bit
                    if (colorBit[pos][bitSize[node]]==0) {
                        used[0] = true;
                    } else if (colorBit[pos][bitSize[node]]==1) {
                        used[1] = true;
                    }
                }
            }



        //wybierz bit
        int cr;
        for (cr = 0; cr <= 2; cr++)
            if (used[cr] == false)
                break;


       // cout << "kolor dostepny: " << cr << endl;
        //jesli jeden z bitow jest dostepny
        if (cr == 0 || cr == 1) {
            colorBit[node][bitSize[node]] = cr; //przypisz wybrany bit
            color[node]=1; //ustaw wezel jako pokolorowany
            uncolored--; //zmniejsz ilosc wezlow do pokolorwania
        } else {
            colorBit[node][bitSize[node]] = 0; //przypisz bit 0 do wezla
            bitSize[node]=bitSize[node]+1; //zwieksz ilosc bitow potrzebnych do pokolorowania wezla o 1
            colorBit[node].resize( bitSize[node]+1);
        //    cout << "bitSize: " << bitSize[node]<<endl;
        }

        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (*i==1 && marked[pos]==marked[node]){//sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)

                if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                    if (bitSize[pos] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go do dalszego kolorowania
                        bitSize[pos]=bitSize[node];
                        uncolored++;
                        colorBit[pos].resize( bitSize[node]+1);
                     //   cout << "powiekszam wezel numer: " << *i<<endl;
                    }
                 }else {
                       adjacentNodes[node][pos]=0;
                       adjacentNodes[pos][node]=0;
                }
            }
        }


        used[0] = false; //zresetuj wartosci
        used[1] = false;

       // cout << "rounds" << rounds << endl;
        rounds++;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
        if (rounds == V && uncolored != 0) {
            V=uncolored;
            bitSizeMin++;
         //   cout << "V" << V << endl;
            rounds = 0;
        }
    }

    //wypisz wezly - kolory
    /*V=Graph::V;
    for (int u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }*/

    //wyczysc listy pomocniczne
    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}

/*
 * Algorytm kolorowania bitowego równomiernego
 */


void Graph::EqualBitColoring()
{
    std::vector<std::vector<int>> adjacentNodes = Graph::adjacentNodes; //stworzenie lokalnej listy sasiednich wezlow

    int V=Graph::V;//stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int node; //zmienna przetrzymujaca numer wezla
    int pos;
    const boost::dynamic_bitset<> bZero(1, 0ul); //0 zapisane binarnie

    int uncolored=V;

    for (int u = 0; u<V; u++) {
        int size = 0;
        for (int j=0; j<V; j++){
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }
    vector<int> color (V,-1);
    vector<boost::dynamic_bitset<> > colorBit (V,boost::dynamic_bitset<>(V,0) );
    int zero = 0, one = 0; //zainicjowanie zmiennych przetrzymujących ilość bitów o wartości 0 oraz 1

    for (int u = 0; u < V; u++) {
      //  color.push_back(-1);//lista ktora ustala czy wezel zaczal byc kolorowany
        bitSize.push_back(0);//lista do przetrzymywania wielkosci koloru w bitach (zaczyna się od 0, a nie od 1)
        marked.push_back(0); //oznaczenie wezla do dalszego kolorowania
      //  colorBit.push_back(bZero);  // lista przetrzymujaca kolor wezla w danym momencie (w bitach)
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<bool> used(2);
  //  vector<int> marked(V);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;

    bitSizeMin=0; //zmienna ustalajaca jaka jest najmniejsza ilosc bitow do pokolorowania wezla
    int rounds=0; //ilosc rund w iteracji
    vector<int>::iterator i;
        //glowna petla programu
    while (uncolored>0) {
       // cout << "petla, uncolored: " << uncolored << endl;
        node = getEqualBitTmp(); //wybranie wezla
        marked[node]++;


        //cout << "petla, vector: " << node << endl;

        if (bitSize[node]<bitSizeMin){
            continue;
        }

        //przypisz bit do pierwszego wybranego wezla ktorego lista pokolorowanych sasiadow jest pusta
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            if (used[0]==true && used[1]==true) {
                break; //jesli oba bity zostaly uzyte przejdz dalej
            }
         //   cout << "i: " << i - adjacentNodes[node].begin() << endl;
            pos = i - adjacentNodes[node].begin();
            if (color[pos] != -1 && *i == 1) { //jesli sasiad jest pokolorowany zaznacz uzyty bit
                if (colorBit[pos][bitSize[node]]==0) {
                    used[0] = true;
                } else if (colorBit[pos][bitSize[node]]==1) {
                    used[1] = true;
                }
            }
        }


        //jesli oba bity są dostępne
        if (used[0] == false && used[1] == false) {
            if (zero<=one) {
                colorBit[node][bitSize[node]] = 0; // przypisz bit 0
                color[node]=1; //ustaw wezel jako pokolorowany
                uncolored--; //zmniejsz ilosc wezlow do pokolorwania
                zero++; //zwieksz ilosc wykorzystanych bitow 0

            } else {
                colorBit[node][bitSize[node]] = 1; // przypisz bit 1
                color[node]=1;
                uncolored--;
                one++; //zwieksz ilosc wykorzystanych bitow 1

            }
        } else if (used[0] == false) { //jesli tylko bit 0 jest dostepny
            colorBit[node][bitSize[node]] = 0;
            color[node]=1;
            uncolored--;
            zero++;

        } else if (used[1] == false) { //jesli tylko bit 1 jest dostepny
            colorBit[node][bitSize[node]] = 1; // Assign the found color
            color[node]=1;
            uncolored--;
            one++;

        } else { //jesli oba bity sa uzyte
            if (zero<=one) { //jesli jest wiecej bitow 1 niz 0 lub jest ich tyle samo
                colorBit[node][bitSize[node]] = 0;
                zero++;
            } else { //jesli jest wiecej bitow 0 niz 1
                colorBit[node][bitSize[node]] = 1;
                one++;
            }

            bitSize[node]=bitSize[node]+1; //zwieksz ilosc bitow potrzebnych do pokolorowania wezla o 1
            //cout << "bitSize: " << bitSize[node]<<endl;
        }

            for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                pos = i - adjacentNodes[node].begin();
                if (*i==1 && marked[pos]==marked[node]){//sprawdz sasiednie wezly ktore zostaly juz pokolorowane tez tego nie wymagaja (maja ten same bit)

                    if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]) {
                        if (bitSize[pos] < bitSize[node]) { //zwieksz liczbe bitow potrzebnych do kolorowania i zaznacz go do dalszego kolorowania
                            bitSize[pos]=bitSize[node];
                            uncolored++;
                         //   cout << "powiekszam wezel numer: " << *i<<endl;
                        }
                     }else {
                           adjacentNodes[node][pos]=0;
                           adjacentNodes[pos][node]=0;
                    }
                }
        }

        used[0] = false;
        used[1] = false;

        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
       // cout << "rounds" << rounds << endl;
        rounds++;
        if (rounds == V && uncolored != 0) {
            V=uncolored;
            bitSizeMin++;
            rounds = 0;
        }
    }


    //wypisz wezly - kolory
   /* V=Graph::V;
    for (int u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }*/

    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}

void Graph::MaxCutRandomBitColoring()
{
    std::vector<std::vector<int>> adjacentNodes = Graph::adjacentNodes; //stworzenie lokalnej listy sasiednich wezlow
    MaximumIndependentSet maxSet;
    int V=Graph::V;//stworzenie lokalnej zmiennej przetrzymujacej ilosc wezlow dostepnych w danej iteracji
    int pos;
    int node;
    const boost::dynamic_bitset<> bZero(1, 0ul); //0 zapisane binarnie

    int uncolored=V;

    for (int u = 0; u<V; u++) {
        int size = 0;
        for (int j=0; j<V; j++){
            if (adjacentNodes[u][j]==1)
                ++size;
        }
        tmp.push_back(size); //stworzenie listy przetrzymujacej ilosc sasiadow dla poszczegolnych wezlow
    }

    for (int u = 0; u < V; u++) {
        color.push_back(-1);//lista ktora ustala czy wezel zaczal byc kolorowany
        colorBit.push_back(bZero);  // lista przetrzymujaca kolor wezla w danym momencie (w bitach)
    }

    // Tymczasowa tablica sluzaca do ustalenia czy dany bit
    // zostal uzyty do pokolorowania sasiedniego wezla
    vector<int> marked(V);
    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;

    for (int cr = 0; cr < V; cr++) {
        bitSize.push_back(0);//lista do przetrzymywania wielkosci koloru w bitach (zaczyna się od 0, a nie od 1)
        marked.push_back(0); //oznaczenie wezla do dalszego kolorowania
    }

    bitSizeMin=0; //zmienna ustalajaca jaka jest najmniejsza ilosc bitow do pokolorowania wezla
    //int rounds=0; //ilosc rund w iteracji
    vector<int>::iterator i;
    vector<int> cover;

        //glowna petla programu
    while (uncolored>0) {
       // cout << "petla, uncolored: " << uncolored << endl;
        //cout << "petla, vector: " << node << endl;

       // srand(static_cast<unsigned int>(time(0)));
        cover = maxSet.process(adjacentNodes, V, 1);
       for(node=0; node<cover.size(); node++) {if(cover[node]==0) {cout<<node<<" ";
          //sprawdzenie czy pierwszy wezel w nowej iteracji ma mniej bitow kolorujacych niz minimalna ilosc dla iteracji
        if (bitSize[node]<bitSizeMin){
            continue;
        }
        cout << "teraz procesuje wezel " << node << endl;
        colorBit[node][bitSize[node]] = 0; // Assign the found color
        marked[node]++;
        uncolored--;
        cout << "node: " << node << " color: " << colorBit[node][bitSize[node]] << endl;
        for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
            pos = i - adjacentNodes[node].begin();
            if (*i==1 && marked[pos]==marked[node]){
                    if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]){
                        if (bitSize[node]==bitSizeMin){
                            bitSize[node]=bitSize[node]+1;
                            colorBit[node].resize(bitSize[node]+1);
                            uncolored++;
                            cout << "zwiekszam wielkosc node wybranego w tej turze: " << node << endl;
                        }
                        if (bitSize[pos]<bitSize[node]){
                            bitSize[pos]=bitSize[node];
                            colorBit[pos].resize(bitSize[node]+1);
                            uncolored++;
                            cout << "zwiekszam wielkosc node sasiedniego: " << pos << endl;
                        }
                    } else {

                        //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji
                        cout << "usuwam sasiada: " << pos << endl;
                            adjacentNodes[node][pos]=0;
                            adjacentNodes[pos][node]=0;
                    }
            }
        }
           }else {  if (bitSize[node]<bitSizeMin){
                   continue;
               }
               cout << "teraz procesuje wezel " << node << endl;
               colorBit[node][bitSize[node]] = 1; // Assign the found color
               marked[node]++;
               uncolored--;
               cout << "node: " << node << " color: " << colorBit[node][bitSize[node]] << endl;
               for (i = adjacentNodes[node].begin(); i != adjacentNodes[node].end(); ++i) {
                   pos = i - adjacentNodes[node].begin();
                   if (*i==1 && marked[pos]==marked[node]){
                           if (colorBit[node][bitSizeMin]==colorBit[pos][bitSizeMin]){
                               if (bitSize[node]==bitSizeMin){
                                   bitSize[node]=bitSize[node]+1;
                                   colorBit[node].resize(bitSize[node]+1);
                                   uncolored++;
                                   cout << "zwiekszam wielkosc node wybranego w tej turze: " << node << endl;
                               }
                               if (bitSize[pos]<bitSize[node]){
                                   bitSize[pos]=bitSize[node];
                                   colorBit[pos].resize(bitSize[node]+1);
                                   uncolored++;
                                   cout << "zwiekszam wielkosc node sasiedniego: " << pos << endl;
                               }
                           } else {

                               //jesli nie spelnia tych wymogow zaznacz go do usuniecia z listy sasiednich wezlow dla nastepnej iteracji
                               cout << "usuwam sasiada: " << pos << endl;
                                   adjacentNodes[node][pos]=0;
                                   adjacentNodes[pos][node]=0;
                           }
                   }
               }

           }
        }


        //jesli liczba rund w iteracji jest rowna liczbie dostepnych do kolorowania wezlow, przejdz do nastepnej iteracji
       // cout << "rounds" << rounds << endl;
            bitSizeMin++;


    }


    //wypisz wezly - kolory
    V=Graph::V;
    for (int u = 0; u < V; u++) {
        std::cout << "Vertex " << u << " --->  Size "
                  << colorBit[u].size() << std::endl;
        for (int i = 0; i<=bitSizeMin-1; i++)
            if(i>bitSize[u]) {
                std::cout << "Vertex " << u << " --->  Color -"
                          << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                          << colorBit[u][i] << std::endl;
    }

    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}
