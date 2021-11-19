#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include<bits/stdc++.h>
#define INFINITE 1000
using namespace std;

ifstream fin("input.in");

struct Point
{
    int seg_number; //indicele in vectorul<Segment> S din main. Basically daca S[seg_number - 1] o sa fie segmentul de pe care
    // se afla punctul
    char label; // Orice punct poate sa fie 'u' - upper, 'l' - lower, 'c' zic eu pentru 'cross' adica intersectie dar poti sa-l
    //codifici cum vrei
    float x;
    float y;
    int cross_number;//daca e de tip cross seg_number si cross_number sunt seg care au format punctul
    bool operator < (const Point & p2) const
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        if(this->y < p2.y)
            return true;
        else if(this->y>p2.y)
            return false;
        else if(this->x<p2.y)
            return true;
        return false;
    }
    bool operator ==(const Point & p2) const
    {
        if(this->y==p2.y)
            if(this->x==p2.x)
                return true;
        return false;
    }
    bool operator !=(const Point &p2) const
    {
        if(y == p2.y)
            if(x  == p2.x)
                return false;
        return true;
    }

    vector<struct Segment> uppers;
    vector<struct Segment> lowers;


};

struct Segment
{
    Point up;       //Componenta upper a segmentului, punctul de sus
    Point low;      //Punctul Lower cu care se termina segmentul
    float slope;   // Panta Ecuatiei dreptei pe care se afla segmentul, i.e. y = slope * x + b;
    float b;       // b din ecuatia de mai sus
    int id;         // asta  am folosit-o mai mult pentru comoditate la afisare.
    int poligon;


    //Metoda care calculeaza "cheia" dupa care te ghidezi cand parcui AVL -ul
    //Din ecatia dreptei , y = slope * x + b, extragem x-ul iar in momentul parcurgerii AVL-ului se compara X-ii segmentului
    //de inserat si a segmetnului din nodul curent
    float get_key(float y)
    {
        return (float)(y - b) / (float)slope ;
    }

    //Functia folosita la initializare, pentru a caulcula ecuatia fiecarui segment odata ce i-am afat upper si lower
    void make_eq()
    {
        if(low.x - up.x == 0)
        {
            if((float)(low.y - up.y) != 0)
                slope = INFINITE * (float)(low.y - up.y);
            else
                slope = INFINITE;
        }
        else
            slope = (float)(low.y - up.y) / (low.x - up.x);
        b = (float)(up.y - slope * up.x);
    }

    bool contains(Point &p)
    {
        if( floor(p.y * 100) == floor((p.x * slope + b) * 100) && p != up && p != low )
            return true;
        return false;
    }
};

//Structura Node a unui BBST

struct Node
{

    Segment s;      //campul principal de informatie care ne intereseaza. Fiecare Node e basically un segment, ca pe desene
    Node *left;     //left child
    Node *right;    //right child
    Node *parent;   //parintele
    Node *succ;
    Node *pred;
    int height;     // "inaltimea" la care se afla Nodul la un moment dat. Inaltimea se calculeaza de la frunze in sus, iar frunzele au inaltime == 0
    int balance;    // left->height - right-> height. Camp folosit doar pentru Implementarea AVL si la functiile de echilibrare
    bool is_leaf;

    //Constructor prin care fac un nou nod
    //Obligatoriu segmentul cu care il initializei, restul campurilor optionale si NULL pe defeault

    Node(Segment &s1, bool leaf = false, Node *l = NULL, Node *r = NULL,Node *p = NULL):height(0),balance(0),is_leaf(leaf),succ(NULL),pred(NULL)
    {
        left = l;
        right = r;
        parent = p;
        s.up = s1.up;
        s.low = s1.low;
        s.b = s1.b;
        s.slope = s1.slope;
        s.id = s1.id;

    }

    //Din nou, recalculeaza inaltimea dupa o revenire de la un insert() sau remove(). Pentru implementarea echilibrarii in special
    void update_height()
    {
        if(left != NULL && right != NULL)
        {
            height = ( 1+ max(left->height, right->height));
            return;
        }
        if(left == NULL)
            if(right != NULL)
            {
                height = 1 + right->height;
                return;
            }
        if(right == NULL)
            if(left != NULL)
            {
                height = 1 + left->height;
                return;
            }
        height = 0;

    }

    //Same as above

    void update_balance()
    {
        if(left != NULL && right != NULL)
        {
            balance = left->height - right->height;
            return;
        }
        if(left == NULL)
            if(right != NULL)
            {
                balance =  0 - right->height;
                return;
            }
        if(right == NULL)
            if(left != NULL)
            {
                balance = left->height - 0;
                return;
            }
    }

};

//Clasa care te intereesaza cu care o sa lucrezi tu. Arbore de cautare Binar Echilibrat

class AVL
{
    //Pointer catre radacina arboreului
    Node *Root;
    Node * insert_helper(Node * start,Segment &s1,  float y,bool leaf);
    Node * remove_helper(Node * root, Segment &s1, float y);
    Node * left_rotate(Node *x);
    Node * right_rotate(Node *y);
    Node * get_root()
    {
        return Root;
    };
    void find_interior_helper(Point &p,vector<Segment>& v,Node * node);

public:
    AVL():Root(NULL) {}
    Node * successor(Node *look, float y);
    Node * predecessor(Node *look, float y);
    void print(Node *r);
    void insert(Segment &s1,  float y);
    void remove(Segment &s1,float y);
    Node * find(Segment &s1, float y);
    void preorder();
    void update_sp(Segment &s1);
    vector<Segment> find_interior(Point &p);

};

Node * AVL::left_rotate(Node * x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    if(x == Root)
    {
        y->parent = NULL;
        Root = y;
    }
    else
        y->parent = x ->parent;
    y->left = x;
    x->parent = y;
    x->right = T2;
    if(T2 != NULL)
        T2->parent = x;
    x->update_height();
    y->update_height();
    x->update_balance();
    y->update_balance();
    return y;
}
Node * AVL::right_rotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    if(y == Root)
    {
        x->parent = NULL;
        Root = x;
    }
    else
        y->parent = x ->parent;
    x ->right = y;
    y->parent = x;
    y ->left = T2;
    if(T2 != NULL)
        T2->parent = y;
    x->update_height();
    y->update_height();
    x->update_balance();
    y->update_balance();
    return x;
}

Node * AVL::insert_helper(Node * root, Segment &s1, float y ,bool leaf)
{
    if(root == NULL)
    {
        Node *p = new Node(s1,leaf);
        return p;
    }
    float rk = root->s.get_key(y);
    float sk = s1.get_key(y);
    if(floor(rk * 100) > floor(sk * 100 ))
    {
        root->left = insert_helper(root->left,s1,y,leaf);
        root->left->parent = root;
    }
    else if( floor(rk * 100) < floor(sk * 100 ))
    {
        root->right = insert_helper(root->right,s1,y,leaf);
        root->right->parent = root;
    }

    //Either slope is equal , the two segments are || in which case  compare by y
    //Or They Are the same Segment, in which case introduce second as leaf in correct position
    else
    {
        cout<<"Same origin .";
        if(root->s.low.x  > s1.low.x)
        {
            cout<<s1.id<<" must be on the left of "<<root->s.id<<". Same Y but different lower X-es";
            root->left = insert_helper(root->left,s1,y,leaf);
            root->left->parent = root;
        }
        else
        {
            cout<<s1.id<<" must be on the right of "<<root->s.id<<". Same upper Y but different lower X-es";
            root->right = insert_helper(root->right,s1,y,leaf);
            root->right->parent = root;
        }

    }
    root->update_height();
    root->update_balance();
    if(root->left != NULL)
    {
        rk = root->left->s.get_key(y);
        sk = s1.get_key(y);
        //Left Left Case
        if( root->balance > 1 && root->left !=NULL && floor(sk * 100) < floor(rk * 100))

        {
            return right_rotate(root);

        }
        //Left Right Case
        if(root->balance > 1 && root->left !=NULL &&  floor(sk * 100) >  floor(rk * 100))
        {
            root->left =  left_rotate(root->left);
            root->left->parent = root;
            return right_rotate(root);
        }
    }
    if(root->right != NULL)
    {
        rk = root->right->s.get_key(y);
        sk = s1.get_key(y);
        //Right Right Case
        if(root->balance < -1 && root->right !=NULL && floor(sk * 100) >  floor(rk * 100))
            return left_rotate(root);
        //Right Left Case
        if(root->balance < -1 && root->right !=NULL && floor(sk * 100) < floor(rk * 100))
        {
            root->right =  right_rotate(root->right);
            root->right->parent = root;
            return left_rotate(root);
        }
    }
    return root;

}

Node * AVL::remove_helper(Node * root,Segment &s1, float y)
{
    if(root == NULL)
        return NULL;
    float rk = root->s.get_key(y);
    float sk = s1.get_key(y);
    if( floor(rk * 100) > floor(sk * 100 ))
        root->left = remove_helper(root->left,s1,y);
    else if( floor(rk * 100) < floor(sk * 100 ))
        root->right = remove_helper(root->right,s1,y);
    else
    {

        if(root->s.low.x  > s1.low.x)
            root->left = remove_helper(root->left,s1,y);
        else if(root->s.low.x  < s1.low.x)
            root->right = remove_helper(root->right,s1,y);
        //Means we landed on the right segment
        else
        {
            //Case 1 : No Children
            if(root->left == NULL && root->right == NULL )
            {
                root = NULL;
                delete(root);
            }
            else
                //Case 2: One Child
                if(root->left == NULL && root->right != NULL)
                {
                    Node * temp = root;
                    root->right->parent = root->parent;
                    root = root->right;
                    temp = NULL;
                    delete(temp);
                }
                else if(root->left != NULL && root->right == NULL)
                {
                    Node * temp = root;
                    root->left->parent = root->parent;
                    root = root->left;
                    delete(temp);
                }
                else
                    //Case 3: Both Children
                {
                    Node * succ  = successor(root,y);
                    root->is_leaf = succ->is_leaf;
                    root->s = succ->s;
                    root->right = remove_helper(root->right,succ->s,y);
                }
        }
    }

    if( root == NULL)
        return NULL;

    root->update_height();
    root->update_balance();
    //Left Left Case
    if( root->balance > 1 && root->left !=NULL && root->left->balance > 0)
        return right_rotate(root);
    //Left Right Case
    if(root->balance > 1 && root->left !=NULL &&  root->left->balance < 0)
    {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }

    //Right Right Case
    if(root->balance < -1 && root->right !=NULL && root->right->balance < 0)
        return left_rotate(root);
    //Right Left Case
    if(root->balance > 1 && root->right !=NULL && root->right->balance > 0)
    {
        root->right =  right_rotate(root->right);
        return left_rotate(root);
    }
    return root;

}
void AVL::print(Node * root)
{
    if(root == NULL)
        return;
    print(root->left);
    cout<<root->s.id<<" ";
    if(root== Root)
        cout<< "(is the root )";
    print(root->right);
}

/* Metoda de cautare a unui segement dupa un Y dat.
    Cred ca cel mai ok ar fi sa folosesti s1.up.y , adica y-ul upper-ului, pentru ca
    Insertia se bazeaza pe y-ul upper-ului
    returns:
        Pointer catre Node din AVL care are s1 respectiv
*/
Node * AVL::find(Segment &s1, float y)
{
    Node *current = Root;
    float rk, sk;
    while( current != NULL )
    {
        rk = current->s.get_key(y);
        sk = s1.get_key(y);
        if(floor(rk * 100) > floor(sk * 100 ) )
            current = current->left;
        else if( floor(rk * 100) < floor(sk * 100 ))
            current = current->right;
        else
        {
            if(current->s.low.x  > s1.low.x)
                current = current -> left;
            else if(current->s.low.x < s1.low.x)
                current = current->right;
            else
                return current;
        }
    }
    return NULL;
}
/*Functia predecessor, cauta cel mai mare child din subarborele din stanga
    returns:
    Pointer Catre Predecesorul Node-ului dat ca parametru, i.e cel mai apropiat
    Segment din stanga
*/
Node * AVL::predecessor(Node * node, float y)
{
    if(node -> left != NULL)
    {
        Node *x = node->left;
        while( x->right != NULL)
            x = x->right;
        return x;
    }
    Node *x  = node->parent;
    if(x == NULL)
        return node;
    float rk = x->s.get_key(y);
    float sk = node->s.get_key(y);
    while( x ->parent != NULL && ((rk == sk && x->s.low.x > node->s.low.x) || (floor(rk * 100) > floor(sk * 100 ))))
    {
        x = x->parent;
        rk = x->s.get_key(y);
    }
    if( floor(rk * 100) > floor(sk * 100 ) )
        return node;
    if(floor(rk * 100) < floor(sk * 100 ))
        return x;
    if(x->s.low.x < node->s.low.x)
        return x;
    if(x->s.low.x > node->s.low.y)
        return node;
    return x;
}
/*Succesor similara cu predecesor, obtine cel mai mic element din subarborele din dreapta
    returns:
    Pointer catre Node-ul din AVL care e cel mai apropiat la stanga de Node dat ca parametru
*/
Node * AVL::successor(Node * node,float y)
{
    if(node -> right != NULL)
    {
        Node *x = node->right;
        while( x->left != NULL)
            x = x->left;
        return x;
    }
    Node *x  = node->parent;
    if(x == NULL)
        return node;
    float rk = x->s.get_key(y);
    float sk = node->s.get_key(y);
    while( x ->parent != NULL && ((rk == sk && x->s.low.x < node->s.low.x) || (floor(rk * 100) < floor(sk * 100 ))))
    {

        x = x->parent;
        rk = x->s.get_key(y);
    }
    if( floor(rk * 100) < floor(sk * 100 ) )
        return node;
    if(floor(rk * 100) > floor(sk * 100 ))
        return x;
    if(x->s.low.x > node->s.low.x)
        return x;
    if(x->s.low.x < node->s.low.x)
        return node;
}
/*Functia insert insereaza un anumit segment transmis ca parametru, dupa un Y transmis ca parametru
    In mod normal, Y-ul transmis ca parametru o sa fie mereu Y-ul punctului extras din EQ
*/
void AVL::insert(Segment &s1, float y)
{
    Root = insert_helper(Root,s1,y,false);
    //update_sp(s1);


}
/*Functia remove sterge la fel segmentul transmis dupa Y-ul transmis.
    Again, segmentele is inserate pe baza Y-ului  punctului upper al segmentului, deci cred
    ca ar fi ok sa transmiti la remove ca parametru tot Y-ul upper-ului (v. main)
*/

void AVL::remove(Segment &s1,float  y)
{
    Root = remove_helper(Root,s1,y);
}

/*Metoda care printeaza SRD-ul, segmentele in ordine de la stanga la dreapta
*/
void AVL::preorder()
{
    cout<<endl;
    print(Root);
    cout<<endl;
}

void AVL::update_sp(Segment &s1)
{
    Node *node = find(s1,s1.up.y);
    if( node != NULL)
    {
        node->succ = successor(node, node->s.up.y);
        node->pred = predecessor(node, node->s.up.y);
        cout<<"Updated for "<<s1.id<<" Succ : "<<node->succ->s.id<<" Pred: "<<node->pred->s.id<<endl;
    }
}

void AVL::find_interior_helper(Point &p, vector <Segment> &result, Node * node)
{
    if(node == NULL)
        return;
    find_interior_helper(p,result,node->left);
    if(node->s.contains(p) == true)
    {
        cout<<node->s.id<<" cointains "<<p.x<<" "<<p.y<<endl;
        result.push_back(node->s);

    }
    find_interior_helper(p,result,node->right);

}
vector<Segment> AVL::find_interior(Point &p)
{
    vector<Segment> result;
    if(Root == NULL)
        return result;
    find_interior_helper(p,result,Root);
    return result;
}

struct point_compare
{
    bool operator()(const Point &p1, const Point &p2) const
    {
        if(p1.y == p2.y)
            return p1.x < p2.x;
        return p1.y > p2.y;
    }
};

typedef map<Point,vector<Segment>,point_compare> intersection_list;
typedef map<Point,Point,point_compare> event_map;

float det(float a1, float a2,float b1,float b2)
{
    return (a1*b2)-(b1*a2);
}
void intersectie(Node *a,Node *b,event_map & evq)
{
    cout<<endl<<"Intersection of "<<a->s.id<<" and "<<b->s.id<<" :";
    if(a == NULL || b == NULL)
        return;
    if(a->s.id == b->s.id)
    {
        cout<<"Same Segment. Not interested"<<endl;
        return;
    }
    Point i;
    pair < event_map::iterator ,bool > locator;

    vector<Point> v(4);
    v[0]=a->s.up;
    v[1]=a->s.low;
    v[2]=b->s.up;
    v[3]=b->s.low;
    double a1 = v[1].x - v[0].x;
    double b1 = v[2].x - v[3].x;
    double a2 = v[1].y - v[0].y;
    double b2 = v[2].y - v[3].y;
    double delta = det(a1,b1,a2,b2);
    double c1 = v[2].x - v[0].x;
    double c2 = v[2].y - v[0].y;
    if(delta != 0)
    {
        //case 0
        double alfa = det(c1,b1,c2,b2) / delta;
        double miu = det(a1,c1,a2,c2) / delta;
        float x = (1-alfa) *v[0].x + alfa*v[1].x;
        float y = (1-alfa) *v[0].y + alfa*v[1].y;
        if(v[0].x == v[1].x)
        {
            if (y >= min(v[0].y,v[1].y) && y <= max(v[0].y,v[1].y))
            {
                if(y >= min(v[2].y,v[3].y) && y <= max(v[2].y,v[3].y))
                {
                    cout<<x<<" "<<y<<endl;

                    i.x=x;
                    i.y=y;
                    i.uppers.push_back(a->s);
                    i.uppers.push_back(b->s);
                    i.lowers.push_back(a->s);
                    i.lowers.push_back(b->s);
                    if(evq.count(i) == 0)
                    {
                        cout<<"Inserted "<<i.x<<i.y<<" as intersection point"<<endl;
                        locator = evq.insert(make_pair(i,i));
                    }
                    else
                        cout<<"Already in Queue"<<endl;

                }
                else
                    cout<<"M nu apartine segmetului [CD]"<<endl;
            }
            else if(y >= min(v[2].y,v[3].y) && y <= max(v[2].y,v[3].y))
                cout<<"M apartine segmentului CD, dar nu si segmentului AB: "<<x<<" "<<y;
            else
                cout<<"M NU apartine segmentelor"<<endl;
        }
        else if( x >= min(v[0].x,v[1].x) && x<= max(v[0].x,v[1].x))
        {
            if(v[2].x == v[3].x)
            {
                if( y >= min(v[2].y,v[3].y) && y <= max(v[2].y,v[3].y))
                {
                    cout<<x<<" "<<y<<endl;
                    i.x=x;
                    i.y=y;
                    i.uppers.push_back(a->s);
                    i.uppers.push_back(b->s);
                    i.lowers.push_back(a->s);
                    i.lowers.push_back(b->s);

                    i.seg_number=a->s.id;
                    i.cross_number=b->s.id;
                    if(evq.count(i) == 0)
                    {
                        cout<<"Inserted "<<i.x<<i.y<<" as intersection point";
                        locator = evq.insert(make_pair(i,i));
                    }
                    else
                        cout<<"Already in Queue."<<endl;


                }
                else
                    cout<<"M NU apartine segmentului CD"<<endl;
            }
            else if(x >= min(v[2].x,v[3].x) && x <= max(v[2].x,v[3].x) ) //&& y > v[2].y && y < v[3].y)
            {
                cout<<x<<" "<<y<<endl;
                i.x=x;
                i.y=y;
                i.label='c';
                i.seg_number=a->s.id;
                i.cross_number=b->s.id;
                i.uppers.push_back(a->s);
                i.uppers.push_back(b->s);
                i.lowers.push_back(a->s);
                i.lowers.push_back(b->s);
                if(evq.count(i) == 0)
                {
                    cout<<"Inserted "<<i.x<<i.y<<" as intersection point";
                    locator = evq.insert(make_pair(i,i));
                }
                else
                    cout<<"Already in Queue."<<endl;


            }
            else
                cout<<"No Intersection"<<endl;
        }
        else
            cout<<"No Intersection"<<endl;
    }
    else if(delta == 0)
    {
        double d1 = det(a1,c1,a2,c2);
        double d2 = det(b1,c1,b2,c2);

        Point k1;
        k1.x = max(v[0].x ,v[1].x);
        if(k1.x == v[0].x)
            k1.y = v[0].y;
        else
            k1.y = v[1].y;
        Point k2;
        k2.x = min(v[2].x ,v[3].x);
        if(k2.x == v[2].x)
            k2.y = v[2].y;
        else
            k2.y = v[3].y;
        if(k1.x >= min(v[2].x,v[3].x)  &&  k2.x >= min(v[0].x , v[1].x ))
        {
            k1.label='c';
            k2.label='c';
            k1.seg_number=a->s.id;
            k1.cross_number=b->s.id;
            k1.seg_number=a->s.id;
            k2.cross_number=b->s.id;
        }
        else
            cout<<"NO Intersection;";
    }

}
;

void print_evq(event_map & evq)
{
    event_map::iterator it;
    for( it = evq.begin(); it != evq.end(); it ++)
    {
        cout<< it->second.x<<" "<<it->second.y<<" UPPERS: ";
        for(int i = 0 ; i < it->second.uppers.size(); i++)
            cout<<it->second.uppers[i].id<<" ";
        cout<<endl;
        cout<<" LOWERS: ";
        for(int i = 0 ; i < it->second.lowers.size(); i++)
            cout<<it->second.lowers[i].id<<" ";
        cout<<endl;
    }
}

void print_intersections(intersection_list & inter)
{
    intersection_list::iterator it;
    for( it = inter.begin(); it != inter.end(); it ++)
    {
        cout<<"Point "<<it->first.x<<" "<<it->first.y<<" intersection of :";
        for(int i =0 ; i< it->second.size(); i ++)
            cout<<it->second[i].id<<" ";
        cout<<endl;

    }
}
int main()
{
    int n,ap;
    fin>>n;
    vector<Segment> S(n); //vectorul de segmente, care o sa fie n + 1 / 2 numarul de puncte citite
    vector<Point> v; // vectorul de puncte. Noi cred ca primim ca input puncte si sa vedem ce e de capul lor desi nu stiu sigur
    vector<int> active(n);//n va fi nr de segmente

    event_map evq;
    intersection_list result;
    Point input1,input2;
    for(int i = 0; i < n; i++)
    {
        fin>>input1.x>>input1.y>>input2.x>>input2.y>>ap;
        input1.label='u';
        input2.label='l';
        input1.seg_number=i+1;
        input2.seg_number=i+1;
        S[input1.seg_number - 1].up = input1;
        S[input1.seg_number - 1].low = input2;
        v.push_back(input1);
        v.push_back(input2);
        S[input1.seg_number-1].poligon=ap;
    }
    for(int i = 0; i < S.size(); i++)
    {
        S[i].make_eq();
        S[i].id = i + 1;
        cout<<S[i].id<<":"<<S[i].up.x<<S[i].up.y<<" "<<S[i].low.x<<S[i].low.y<<" . Ecuatia : y = ("<<S[i].slope<<" * x + "<<S[i].b<<") "<<S[i].poligon<<endl;
    }

    AVL a;
    for(int i = 0; i < v.size(); i++)
        cout<<v[i].x<<" "<<v[i].y<<" "<<v[i].label<<",  ";
    cout<<endl<<"******"<<endl;
    //USING THE MAP TO INSERT ELEMENTS INTO EVENTS QUEUE

    pair<event_map::iterator,bool> locator;
    for(int i=0; i<v.size(); i++)
    {
        locator = evq.insert(make_pair(v[i],v[i]));
        //element has not been inserted yet
        if(locator.second == true)
        {
            //means locator.first returns iterator to positon of new element
            if(v[i].label == 'u')
                locator.first->second.uppers.push_back(S[v[i].seg_number - 1]);
            else
                locator.first->second.lowers.push_back(S[v[i].seg_number - 1]);
        }
        else
            //means the point already exists
            if(locator.second == false)
            {
                if(v[i].label == 'u')
                    locator.first->second.uppers.push_back(S[v[i].seg_number - 1]);
                else
                    locator.first->second.lowers.push_back(S[v[i].seg_number - 1]);
            }

    }
    print_evq(evq);
    while(!evq.empty())
    {
        Point current = evq.begin()->second;

        cout<<endl<<"Detected :"<<current.x<<" "<<current.y;
        vector<Segment> inter = a.find_interior(current);
        vector<Segment> none;
        cout<<endl<<"Checking for segments containing current: ";
        if(inter.size() == 0 )
            cout<<"None ";
        else
            for(int i =0 ; i< inter.size(); i++)
            {
                cout<<inter[i].id<<" ";
            }

        //if upper x lower x inter is more than one
        if(current.uppers.size() + current.lowers.size() + inter.size() > 1)
        {
            //report current as intersection point of all the segments;
            cout<<endl<<"Current is mulit-segment intersection ";
            pair<intersection_list::iterator ,bool> locator;
            for(int i =0 ; i< current.uppers.size(); i++)
            {
                locator = result.insert(make_pair(current,current.uppers));
                locator.first->second.push_back(current.uppers[i]);
            }
            for(int i =0 ; i< current.lowers.size(); i++)
            {
                locator = result.insert(make_pair(current,current.lowers));
                locator.first->second.push_back(current.lowers[i]);
            }
            for(int i =0 ; i< inter.size(); i++)
            {
                locator = result.insert(make_pair(current,inter));
                locator.first->second.push_back(inter[i]);
            }

        }

        //erase all the lowers and inters segs for p from AVL
        cout<<endl<<"Erasing all the inter and lower Segments for current from AVL";
        for(int i =0 ; i< current.lowers.size(); i++)
        {
            a.remove(current.lowers[i],current.y);
        }
        for(int i =0 ; i< inter.size(); i++)
        {
            a.remove(inter[i],current.y);
        }
        a.preorder();
        cout<<endl<<"Inserting all Upper Segments ";
        //insert all the upper sides into the AVL
        for(int i =0 ; i< current.uppers.size(); i++)
        {
            a.insert(current.uppers[i],current.y);
        }
        a.preorder();

        //If the current point is no starting point nor an interior point,it means it only is a lower for some segs
        if(current.uppers.size() + inter.size() == 0)
        {
            cout<<endl<<" Current is only lower point for several segments ";
            Segment s;
            s.up = current;
            s.low = current;
            s.make_eq();
            s.id = 0;
            a.insert(s,current.y);
            a.preorder();
            Node * locator = a.find(s,current.y);
            Node * pred = a.predecessor(locator,current.y);
            Node * succ = a.successor(locator,current.y);
            cout<<"Predecessor of vertical line Current is :"<<pred->s.id<<"; ";
            cout<<"Successor of vertical line Current is :"<<succ->s.id<<"; "<<endl;
            if(succ->s.id != pred->s.id)
                intersectie(pred,succ,evq);
            a.remove(s,current.y);
        }
        else
        {
            Segment left_most;
            Segment right_most;

            if(current.uppers.size() > 0 )
            {
                left_most = current.uppers[0];
                right_most = current.uppers[0];
            }
            else if(inter.size() > 0)
            {
                left_most = inter[0];
                right_most = inter[0];
            }
            for(int i = 0; i< current.uppers.size(); i++)
            {
                if(current.uppers[i].low.x < left_most.low.x)
                    left_most = current.uppers[i];
                if(current.uppers[i].low.x  > right_most.low.x)
                    right_most = current.uppers[i];
            }
            for(int i = 1; i< inter.size(); i++)
            {
                if(inter[i].low.x < left_most.low.x)
                    left_most = current.uppers[i];
                if(inter[i].low.x  > right_most.low.x)
                    right_most = current.uppers[i];
            }
            cout<<"Found Right-Most: " <<right_most.id<<" | Found left-Most: " <<left_most.id<<endl;
            Node * left_in_tree = a.find(left_most,current.y);
            Node * left_neighbour = a.predecessor(left_in_tree,current.y);
            Node * right_in_tree = a.find(right_most,current.y);
            Node * right_neighbour = a.successor(right_in_tree,current.y);
            cout<<"Found Right -Neightbour: "<<right_neighbour->s.id<<" | Found Left-Neighbour: "<<left_neighbour->s.id<<endl;
            intersectie(left_in_tree,left_neighbour,evq);
            intersectie(right_in_tree,right_neighbour,evq);


        }
        evq.erase(evq.begin());
        print_evq(evq);


    }
    print_intersections(result);
    cout<<endl;
    cout<<"Final intersection points:"<<endl;
    intersection_list fin;
    intersection_list::iterator it;
    for( it = result.begin(); it != result.end(); it ++)
    {
        bool ok=false;
        //cout<<"Point "<<it->first.x<<" "<<it->first.y<<" intersection of :";
        // for(int i =0 ;i< it->second.size(); i ++)
        //    cout<<it->second[i].id<<" ";
        //cout<<endl;
        for(int i =1 ; i< it->second.size(); i++)
            if(S[it->second[i-1].id-1].poligon!=S[it->second[i].id-1].poligon)
            {
                fin.insert(*it);
            }

    }
    print_intersections(fin);
    int nr=0;
    for( it = fin.begin(); it != fin.end(); it ++)
        nr++;
    if(nr==0)
        cout<<"intersectia este multimea vida";
    else
    {
        if(nr==1)
            cout<<"intersectia este un punct";
        else
        {
            if(nr>2)
                cout<<"intersectia este un poligon";
            else
            {
                set<int> seg1,seg2;
                intersection_list::iterator i1,i2;
                i2=i1=fin.begin();
                i2++;
                for(int i =1 ; i< i1->second.size(); i++)
                    seg1.insert(i1->second[i].id);
                for(int i =1 ; i< i2->second.size(); i++)
                    seg2.insert(i2->second[i].id);
                set<int>::iterator itr;
                for (itr = seg1.begin(); itr != seg1.end(); ++itr)
                {
                    cout<< *itr<<" ";
                }
                cout << endl;
                for (itr = seg2.begin(); itr != seg2.end(); ++itr)
                {
                    cout<< *itr<<" ";
                }
                cout << endl;
                nr=0;
                for (itr = seg1.begin(); itr != seg1.end(); ++itr)
                {
                    if(seg2.find(*itr)!=seg2.end())
                        nr++;
                }
                if(nr>=2)
                    cout<<"intersectia este un segment";
                else cout<<"intersectia este un poligon";
            }
        }

    }
    return 0;
}
