#include <iostream>
#include <string>

struct node{
    int num;
    node *next;
    node *prev;
};

int rand_num();
void swap_classic(int & , int &);
void swap_by_num(node * , node *);
void node_reader(node *&);
void node_rand_fill(node *& , int);
void node_printer(node *);
void node_append(node *& , int);
void node_delete_el(node *);

void node_merge(node * , node * , node * , node *);
void merge_sort(node * , node * );
void merge_init(node *&);

int main(){
    node *L = nullptr;
    std::cout << "random:\n";
    node_rand_fill(L , 100);
    node_printer(L);
    merge_init(L);
    std::cout << "sorted:\n";
    node_printer(L);
    return 0;
}

int rand_num(){
    static int a = 124125;
    static int b = 87153;
    a *= 12531;
    b *= 6153;
    return (a + b + 1273864) % 1000;
}

void swap_classic(int &a , int &b){
    int t = a;
    a = b;
    b = t;
    return;
}

void swap_by_num(node *L1 , node *L2){
    int t = L1->num;
    L1->num = L2->num;
    L2->num = t;
    return;
}

void node_reader(node *&L){
    if(!std::cin) return;
    std::string s;
    int t;
    std::cin >> s;
    if(s == "") return;
    t = std::stoi(s);
    node_append(L , t);
    if(L->next != nullptr) node_reader(L->next);
    else node_reader(L);
    return;
}

void node_rand_fill(node *&L , int n){
    if(n <= 0) return;
    node_append(L , rand_num());
    if(L->next != nullptr) node_rand_fill(L->next , --n);
    else node_rand_fill(L , --n);
    return;
}

void node_printer(node *L){
    while(L != nullptr){
        std::cout << L->num << ' ';
        L = L->next;
    }
    std::cout << '\n';
    return;
}

void node_append(node *&L , int n){
    if(L == nullptr){
        L = new node;
        L->next = L->prev = nullptr;
        L->num = n;
    }
    else if(L->next != nullptr) node_append(L->next , n);
    else{
        node *t = new node;
        t->next = nullptr;
        t->prev = L;
        t->num = n;
        L->next = t;
    }
    return;
}

void node_delete_el(node *L){
    if(L->prev != nullptr) L->prev->next = L->next;
    if(L->next != nullptr) L->next->prev = L->prev;
    delete L;
    return;
}

// sort functions

void insert_fm(node *L1 , node *L2){
    L1->prev->next = L2;
    node *t = L1->prev;
    L1->prev = L2;
    L2->prev->next = L2->next;
    L2->next->prev = L2->prev;
    L2->next = L1;
    L2->prev = t;
    return;
}

void node_merge(node *L1_b , node *L1_e , node *L2_b , node *L2_e){
    L2_e = L2_e->next;
    while(L1_b != L1_e->next && L2_b != L2_e){
        if(L1_b->num <= L2_b->num){
            L1_b = L1_b->next;
        }
        else{
            node *t = L2_b->next;
            insert_fm(L1_b , L2_b);
            L2_b = t;
        }
    }
    return;
}

void merge_sort(node *L1_b , node *L1_e){
    if(L1_b->next == L1_e->prev) return;
    node *Lf , *Ls;
    Lf = Ls = L1_b->next;
    while(Lf != L1_e->prev){
        Lf = Lf->next;
        if(Lf == L1_e->prev) break;
        Lf = Lf->next;
        Ls = Ls->next;
    }
    merge_sort(L1_b , Ls->next);
    Lf = Ls = L1_b->next;
    while(Lf != L1_e->prev){
        Lf = Lf->next;
        if(Lf == L1_e->prev) break;
        Lf = Lf->next;
        Ls = Ls->next;
    }
    merge_sort(Ls , L1_e);
    Lf = Ls = L1_b->next;
    while(Lf != L1_e->prev){
        Lf = Lf->next;
        if(Lf == L1_e->prev) break;
        Lf = Lf->next;
        Ls = Ls->next;
    }
    node_merge(L1_b->next , Ls , Ls->next , L1_e->prev);
    return;
}

void merge_init(node *&L){
    if(L == nullptr) return;
    node_append(L , 123456);
    node *L_bar = L; // create barrier el from both side
    while (L_bar->next != nullptr) {
        L_bar = L_bar->next;
    }
    node *L_b_bar = new node;
    L_b_bar->prev = nullptr;
    L_b_bar->next = L;
    L_b_bar->num = 123456;
    L->prev = L_b_bar;
    merge_sort(L_b_bar , L_bar);
    L = L_b_bar->next;
    node_delete_el(L_bar);
    node_delete_el(L_b_bar);
    return;
}
