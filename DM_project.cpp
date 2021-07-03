#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Initial coloring
// 0 -> red
// 1 -> green
// 2 -> blue

int p1 = 19; // 2 prime no.s taken by the first party(prover).
int p2 = 73; // We just try to make the second party(verifier) believe that we have 2 primes.


bool isPrime(int n)
{
    int flag = 1;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            flag = 0;
            break;
        }
    }
    if(flag==0)
    {
        return false;
    }
    else{
        return true;
    }
};


int random(int min, int max) // To randomly generate 0 or 1 or 2
{
   static bool first = true;
   if (first)
   {
      srand(time(NULL));
      first = false;
   }
   return min + rand() % ((max+1)-min);
};



/* After each cycle the 3 colors of the graph are permuted randomly , so for eg if the
   verifier chooses the same edge between 2 connected vertices in a row , it will show
   different color pair in the 2 attempts , but the graphs still remain 3-colorable or
   not 3-colorable according to whether the proof statement of the prover is true or false
   respectively*/
void randomise_color(vector<char>& permu_color)
{
    vector<char> color = {'r','g','b'};

    int x = random(0,2);
    permu_color;
    permu_color.push_back(color[x]);
    vector<char>::iterator it1;
    it1 = color.begin()+x;
    color.erase(it1);

    int y =random(0,1);
    permu_color.push_back(color[y]);
    vector<char>::iterator it2;
    it2 = color.begin()+y;
    color.erase(it2);

    permu_color.push_back(color[0]);
};



// To print colors red, green or blue according to whether 'r', 'g' or 'b'
void print_col(char c)
{
    if(c=='r')
    {
        cout<<"red";
    }
    else if(c=='g')
    {
        cout<<"green";
    }
    else{
        cout<<"blue";
    }
};



/* This class contains 2 graphs: 1 3-colorable graph and other non 3-colorable graph,
   and various methods for them*/
class graph
{
private:
    int g1_v = 10;
    int g1_e = 15;
    int *g1 = nullptr;
    vector<int> g1_col;

    int g2_v = 12;
    int g2_e = 21;
    int *g2 = nullptr;
    vector<int> g2_col;

    int itr = 1;
public:
    // The 3-colorable graph
    void graph1()
    {
        int n = g1_v;
        g1 = (int*)malloc(n*n*sizeof(int));

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                *(g1+i*n+j) = 0;
            }
        }

        for(int i=0;i<n-n/2;i++)
        {
            int x = (i+2)%5;
            int y = (i+3)%5;
            int z = i+5;

            *(g1+i*n+x) = 1;
            *(g1+i*n+y) = 1;
            *(g1+i*n+z) = 1;
            *(g1+z*n+i) = 1;
        }

        for(int i=5;i<n;i++)
        {
            if(i==5)
            {
                *(g1+i*n+i+1) = 1;
                *(g1+i*n+9) = 1;
            }
            else if(i==9)
            {
                *(g1+i*n+i-1) = 1;
                *(g1+i*n+5) = 1;
            }
            else
            {
                *(g1+i*n+i-1) = 1;
               *(g1+i*n+i+1) = 1;
            }
        }

        int color[n] = {0,1,1,2,0,1,2,0,1,2};
        for(int i=0;i<n;i++)
        {
            g1_col.push_back(color[i]);
        }
    };



    // The non 3-colorable graph
    void graph2()
    {
        int n = g2_v;
        g2 = (int*)malloc(n*n*sizeof(int));

         for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                *(g2+i*n+j) = 0;
            }
        }

        for(int i=0;i<n-n/2;i++)
        {
            if(i==0)
            {
                *(g2+i*n+i+1) = 1;
                *(g2+i*n+5) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+i+7) = 1;
            }
            else if(i==5)
            {
                *(g2+i*n+i-1) = 1;
                *(g2+i*n+0) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+6) = 1;
            }
            else
            {
                *(g2+i*n+i-1) = 1;
                *(g2+i*n+i+1) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+i+7) = 1;

            }
        }

        for(int i=6;i<n;i++)
        {
            if(i==6)
            {
                *(g2+i*n+5) = 1;
                *(g2+i*n+0) = 1;
            }
            else
            {
                int x = i-7;
                *(g2+i*n+x) = 1;
                *(g2+i*n+x+1) = 1;
            }
        }

        for(int i=6;i<9;i++)
        {
            *(g2+i*n+i+3) = 1;
            *(g2+(i+3)*n+i) = 1;
        }
        int color[n] = {1,2,1,2,0,0,2,0,0,0,1,1};
        for(int i=0;i<n;i++)
        {
            g2_col.push_back(color[i]);
        }
    };



    // To print the graph1 to indicate the connections between the vertices(if any)
    void print_graph1()
    {
        int n = g1_v;
        for(int i=0;i<n;i++){
            cout<<"V"<<i<<" -> ";
            for(int j=0;j<n;j++)
            {
                if(*(g1+i*n+j)==1)
                {
                    cout<<"V"<<j<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    };



    // To print the graph2 to indicate the connections between the vertices(if any)
    void print_graph2()
    {
        int n = g2_v;
        for(int i=0;i<n;i++){
            cout<<"V"<<i<<" -> ";
            for(int j=0;j<n;j++)
            {
                if(*(g2+i*n+j)==1)
                {
                    cout<<"V"<<j<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    };



    /* For graph-1: To print the colors of the 2 vertices connected
       by a edge (requested by the verifier) and update the confidence
       of the verifier accordingly */
    void check_color_g1(int v1,int v2)
    {
        int n = g1_v;
        if(*(g1+v1*n+v2)==1)
        {
            vector<char> tmp;
            randomise_color(tmp);

            if(g1_col[v1]==0)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[0]);
                cout<<")"<<"--------";
            }
            else if(g1_col[v1]==1)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[1]);
                cout<<")"<<"--------";
            }
            else{
                cout<<"V"<<v1<<"(";
;                print_col(tmp[2]);
                cout<<")"<<"--------";
            }


            if(g1_col[v2]==0)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[0]);
                cout<<")";
            }
            else if(g1_col[v2]==1)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[1]);
                cout<<")";
            }
            else{
                cout<<"V"<<v2<<"(";
                print_col(tmp[2]);
                cout<<")";
            }
            cout<<endl;
            double confidence = (1 - pow((1-1.0/g1_e),itr))*100;
            cout<<"Confidence of the verifier: "<<confidence<<"%"<<endl;
            itr++;
        }
        else{
            cout<<"The 2 vertices are not connected by a edge"<<endl;
        }
    };



    /* For graph-1: To print the colors of the 2 vertices connected
       by a edge (requested by the verifier) and update the confidence
       of the verifier accordingly */
    void check_color_g2(int v1,int v2)
    {
        int n = g2_v;
        if(*(g2+v1*n+v2)==1)
        {
            vector<char> tmp;
            randomise_color(tmp);

            if(g2_col[v1]==0)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[0]);
                cout<<")"<<"--------";
            }
            else if(g2_col[v1]==1)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[1]);
                cout<<")"<<"--------";
            }
            else{
                cout<<"V"<<v1<<"(";
;                print_col(tmp[2]);
                cout<<")"<<"--------";
            }


            if(g2_col[v2]==0)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[0]);
                cout<<")";
            }
            else if(g2_col[v2]==1)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[1]);
                cout<<")";
            }
            else{
                cout<<"V"<<v2<<"(";
                print_col(tmp[2]);
                cout<<")";
            }
            cout<<endl;
            if(g2_col[v1]==g2_col[v2])
            {
                cout<<"We got 2 adjacent vertices of same color , therefore , the graph is not 3-colorable!!!"<<endl;
                cout<<"Hence, the verifier now has 0 confidence that the 2 numbers the prover has are primes"<<endl;
                itr = 1;
            }
            else
            {
                double confidence = (1 - pow((1-1.0/g2_e),itr))*100;
                cout<<"Confidence of the verifier: "<<confidence<<"%"<<endl;
                itr++;
            }
        }
        else{
            cout<<"The 2 vertices are not connected by a edge"<<endl;
        }
    };

};

int main()
{
    int n;

    graph g;
    g.graph1();
    g.graph2();

    cout<<"Hello Verifier!!!"<<endl;
    cout<<endl;
    cout<<"The prover is claiming to have 2 prime numbers"<<endl;
    cout<<endl;
    cout<<"And to demonstrate the correctness of this statement ";
    cout<<"the verifier has converted the statement that he has 2 primes into ";
    cout<<"a 3-colorable map and given them to you(the verifier) without making ";
    cout<<"any subsequent changes in the arrangement of the graph other than the colors of the vertices"<<endl;
    cout<<endl;
    cout<<"To check the correctness of the claim, you(the verifier)";
    cout<<"select the adjacent vertices to see if they are of different colors or not and make your confidence accordingly"<<endl;
    cout<<endl;
    cout<<"If at any point the 2 adjacent edges have the same color then this means the map is not 3-colorable,";
    cout<<"therefore the prover's claim is false"<<endl;
    cout<<endl;


    /* This is a small application of zero-knowledge proof where through the colored graphs the tries to increases the
       the confidence of the verifier without actually telling the verifier what those 2 primes are.*/

    /* It may seem vague as to how to we can generate a one-to-one relation between the proof statement(in this case,
       the claim that the prover has to prime no.s) and a 3-colorable graph. But it is known that any proof which is
       true can be converted into a valid 3-colorable graph but a false proof cannot be.*/

    /* Here without actually using the correct steps to find one-to-one relation between the statement and its colorable graph
       (which is actually difficult to do), I have directly put a hard-relation between then for the simplicity of the demonstration*/

    /* NOTE: Right now both numbers are primes, to check what happens when even atleast 1 number is not prime , just change them
             and select some pair of vertices , and after some selections select the V4---v5 and see what happens */

    cout<<"1. To continue asking for the color of adjacent vertices of the graph"<<endl;
    cout<<"You can select the vertices according to the list of vertex connections given below"<<endl;
    cout<<endl;
    cout<<"2. To EXIT"<<endl;

    do
    {
        cin>>n;
        if(isPrime(p1) && isPrime(p2))
        {
            int a,b;
            g.print_graph1();
            cout<<"Enter 2 vertex numbers to see their color: ";
            cin>>a>>b;
            g.check_color_g1(a,b);
        }
        else
        {
            int a,b;
            g.print_graph2();
            cout<<"Enter 2 vertices 2 see their color: ";
            cin>>a>>b;
            g.check_color_g2(a,b);
        }
    }while(n!=2);



    return 0;
}
