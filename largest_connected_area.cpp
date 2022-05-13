
#include <list>
#include <iostream>
using namespace std;

long global_max = 0;


struct vrchol
{
    long velikost;
    list<vrchol *> hrany; //list pointeru na vrcholy
    bool navstiven = false;

    vrchol(long size){//obsah
        velikost = size;
    }
};

list<vrchol> seznam_vrcholu;


struct interval
{
    int delka;
    vrchol *v;//z intervalu si muzeme zvolit libovolny, protoze stejne sousedí
};

struct hranice
{
    list<interval> horni;
    list<interval> dolni;
    list<interval> levy;
    list<interval> pravy;

    hranice(int size, vrchol *v){//konstruktor pro pripady 0 a 1, nikoli slozitejsi intervaly
        interval i;
        i.delka=size;
        i.v=v;
        horni.push_back(i);
        dolni.push_back(i);
        levy.push_back(i);
        pravy.push_back(i);
    }

    hranice(list<interval> h, list<interval> d, list<interval> l, list<interval> p){//zkusit reference
        horni = h;
        dolni = d;
        levy = l;
        pravy = p;
    }
};


void slepovani(list<interval>& a, list<interval>& b){
    //jsem na zacatku intervalu, pokud jsou oba bile, natahnu hranu, pokud ne, posunu se ze vsech cernych na bile, 
    //podivam se, jestli se intervaly prekryvaji (pozice intervalu = lokalni pocitadlo pro pozici kazdeho z nich - pocit.+jeho_delka)
    //posouvam pointer, ktery je bliz ke startu
    int pozice_a = a.front().delka;
    int pozice_b = b.front().delka;
    while (!a.empty() && !b.empty())
    {
        if (a.front().v != NULL && b.front().v != NULL){
            a.front().v->hrany.push_back(b.front().v);
            b.front().v->hrany.push_back(a.front().v);
        }
        if (pozice_a < pozice_b){
            a.pop_front();
            if (!a.empty()){
                pozice_a += a.front().delka;
            }
        }
        else if (pozice_b < pozice_a){
            b.pop_front();
            if (!b.empty()){
                pozice_b += b.front().delka;
            }
        } 
        else
        {
            a.pop_front();
            b.pop_front();
            if (!a.empty()){
                pozice_a += a.front().delka;
            }
            if (!b.empty()){
                pozice_b += b.front().delka;
            }
        }
    }
}

void spojovani(list<interval>& a, list<interval>& b){
    if ((a.back().v != NULL && b.front().v != NULL)||(a.back().v == NULL && b.front().v == NULL)){
        a.back().delka += b.front().delka;
        b.pop_front();
    }
    a.splice(a.begin(), b);
}


hranice solve(int size){//"DFS"
    char znak = getchar();
    if (znak == '0'){
        return hranice(size, NULL);
    }
    else if (znak == '1'){
        vrchol v = vrchol(size*(long)size);
        seznam_vrcholu.push_back(v);
        return hranice(size, &seznam_vrcholu.back()); //new znamena, ze jsem vrchol dala do globalni dynamicke pameti a musim ho pak i smazat
    }
    else if(znak == '('){ //musime pak smazat zaviraci zavorku
        hranice levy_horni_kvadrant = solve(size/2);
        hranice pravy_horni_kvadrant = solve(size/2);
        hranice levy_dolni_kvadrant = solve(size/2);
        hranice pravy_dolni_kvadrant = solve(size/2);
        getchar();
        slepovani(levy_horni_kvadrant.pravy, pravy_horni_kvadrant.levy);
        slepovani(pravy_horni_kvadrant.dolni, pravy_dolni_kvadrant.horni);
        slepovani(levy_dolni_kvadrant.pravy, pravy_dolni_kvadrant.levy);
        slepovani(levy_horni_kvadrant.dolni, levy_dolni_kvadrant.horni);
        
        spojovani(levy_horni_kvadrant.horni, pravy_horni_kvadrant.horni);
        spojovani(pravy_horni_kvadrant.pravy, pravy_dolni_kvadrant.pravy);
        spojovani(levy_dolni_kvadrant.dolni, pravy_dolni_kvadrant.dolni);
        spojovani(levy_horni_kvadrant.levy, levy_dolni_kvadrant.levy);

        return hranice(levy_horni_kvadrant.horni, levy_dolni_kvadrant.dolni, levy_horni_kvadrant.levy, pravy_horni_kvadrant.pravy);
    }

        //slepovani
        //spojovani - prodluzovani 
    


    //precte 1 znak:
        //bud basecase - cislo - vraci 4 hrance vymyslene na miste
        //nebo to je zavorka - volam 4 syny a slepuji dohromady, vraci 4 hranice
        //stavi graf

}


// def spoj_kvadranty()
    //vstup... 4 x 4 listy(spojaky)
    //vraci seznamy 

long local_max = 0;


void dfs(vrchol &v){
    local_max += v.velikost;
    v.navstiven = true;
    for(vrchol *hrana : v.hrany){
        if (!(*hrana).navstiven){
            dfs(*hrana);
        }
    }
}

void najdi_komponenty(){
    for(vrchol &v : seznam_vrcholu){
        if (!v.navstiven){
            local_max = 0;
            dfs(v);
            if (local_max > global_max){
                global_max = local_max;
            }
        }
    }
}



int main(){

    //zavolej solve
    //prohledat vytvoreny graf
    //vypis global_max
    solve(1<<4);
    najdi_komponenty();
    cout << global_max;
    
}
