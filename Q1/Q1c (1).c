#include <stdio.h>

#define MOD(a,b) ((((a)%(b))+(b))%(b))
#define NMAX (50 * 50)
#define SIZE 16
#define SOURCE NMAX-1

const int _U = 11, _R = 12 , _D = 13, _L = 14;
int n = 0;

void connection(int direction, int* i, int* j, int n);
void routes(int arr[4], char product[2], int rotate);
void rotations(int direction, int i, int j, int rotThis, char product[n][n][2], int arr[4]);
int intTo_DirectionConverter(int direction);

/*to be developed*/
int canConnect(char typeThis, char typeThat, int rotThis, int rotThat, int dirThisToThat);


// computers
int isComp[NMAX];

//in case if you want to loop directions 0 ~> _U, 1 ~> _R, 2 ~> _D, 3 ~> _L:
int intTo_DirectionConverter(int direction)
{
    if(direction == 0)
        return _U;
    if(direction == 1)
        return _R;
    if(direction == 2)
        return _D;
    if(direction == 3)
        return _L;
}

//opposite of int to direction converter
int directionTo_IntConverter(int num)
{
    if(num == _U)
        return 0;
    if(num == _R)
        return 1;
    if(num == _D)
        return 2;
    if(num == _L)
        return 3;
}

// function that for a part of product and a direction changes an array with rotations of destination that can connect to first part
// arr = {0,1,2,3} -> 0 & 1:
void rotations(int direction, int i, int j, int rotThis, char product[n][n][2], int arr[4])
{
    int down = 0, right = 0;
    if(direction == _U)
        down = -1;
    if(direction == _D)
        down = 1;
    if(direction == _R)
        right = 1;
    if(direction == _L)
        right = -1;

    for(int k = 0; k < 4; k++)
        arr[k] = 0;
    int i0 = i, j0 = j, index = 0, secondIndex = 0;
    connection(direction, &i, &j, n);
    int routesArr0[4] = {0}, routesArr[4] = {0};
    routes(routesArr0, product[i0][j0], rotThis); 

    if(down == -1)     index = 0;  if(right == 1)     index = 1; if(down == 1)     index = 2; if(right == -1)     index = 3;

    secondIndex = (index + 2) % 4; 

    if(routesArr0[index] == 0)
    {
        return;
    }
    for(int k = 0; k < n; k++)
    {
        routes(routesArr, product[i][j], k);
        if(routesArr[secondIndex] == 1)
        {
            arr[k] = 1;
        }
    }

}

// function that for every kind of block and rotation changes an array that contains available routes:
// arr = {up, right, down, left}, 0 := not available, 1 := available
void routes(int arr[4], char product[2], int rotate)
{
     for(int i = 0; i < 4; i++)
        arr[i] = 0;
    int rotateCount = (product[1] - '0' + rotate) % 4;
    switch (product[0])
    {
    case 'T':
    case 'S':
        for(int i = 0; i < 4; i++)
        {
            if(i == rotateCount)
            {
                arr[i] = 0;
            }
            else
                arr[i] = 1;
        }
        break;
    case 'I':
            if(rotateCount % 2 == 0)
            {
                arr[0] = 1; arr[1] = 0; arr[2] = 1; arr[3] = 0;
            }
            else
            {
                arr[0] = 0; arr[1] = 1; arr[2] = 0; arr[3] = 1;
            }
        break;
    case 'L':
            for(int i = 0; i < 4; i++)
            {
                if(i < 2)
                    arr[(rotateCount + i) % 4] = 1;
                else
                    arr[(rotateCount + i) % 4] = 0;
            }
        break;
    case 'C':
        for(int i = 0; i < 4; i++)
        {
         if(i == rotateCount)
            {
                arr[i] = 1;
            }
            else
                arr[i] = 0;
        }
        break;

    default:
        break;
    }
}

// function that connects up to bot and left to right: down = -1 * steps : up, right = -1 * steps: left, 0 = nothing. 
// pass pointer of indices to function: &i, &j:

void connection(int direction, int* i, int* j, int n)
{
    int down = 0, right = 0;
    if(direction == _U)
        down = -1;
    if(direction == _D)
        down = 1;
    if(direction == _R)
        right = 1;
    if(direction == _L)
        right = -1;

    if(*i + down > n - 1 || *i + down < 0)
    {
         *i = MOD((*i + down), n);
         return;
    }
    if(*j + right > n - 1 || *j + right < 0)
    {
        *j = MOD((*j + right), n);
        return;
    }
        *j += right;
        *i += down;
}

/** ID functions **/

// turns a node into an int, corresponding to its vertex number in the graph
int id(int i, int j, int dir){
    return 4 * ((i * n) + j) + directionTo_IntConverter(dir);
}

// gets i * j value of a node
int idInTable(int _id){
    return (_id / 4) * 4;
}

// gets row number of a node in the graph
int row(int _id){
    return (_id / 4) / n;
}

// gets column number of a node in the graph
int col(int _id){
    return (_id / 4) % n;
}

// gets direction of a node in the graph
int dir(int _id){
    return intTo_DirectionConverter(_id % 4);
}


/** Graph **/

// adjacency list of the graph
int adj[NMAX][SIZE + 1];

// is the node is visited or not
int visited[NMAX];

// direction of a node
int dir_node[NMAX];

// initialize graph
void initGraph(){
    for(int i = 0; i < NMAX; i++)
        adj[i][SIZE] = visited[i] = 0;
}

// connects v->u
void addEdge(int v, int u){
    int size = adj[v][SIZE]++;
    adj[v][size] = u;
}

// dfs algorithm, returns 1 if it ended in a source
int dfs(int s){
    visited[idInTable(s)] = 1;
    dir_node[idInTable(s)] = dir(s);

    if(!visited[IdinTable(s)] && isComp[IdinTable(s)])
        return 1;

    int tempadj[NMAX][SIZE + 1];
    int tempvis[NMAX];

    for(int i = 0; i < adj[s][SIZE]; i++){
        int u = adj[s][i];
        int t_id = idInTable(u);

        memcpy(tempadj, adj, sizeof(tempadj));
        memcpy(tempvis, visited, sizeof(tempvis));

        if(!visited[t_id]){
            if(!dfs(u)){
                memcpy(adj, tempadj, sizeof(adj));
                memcpy(visited, tempvis, sizeof(visited));
                return 0;
            }
        }
    }

    return 1;
}

/** Graph Builder **/

// connect possible cases of two nodes 
// e.g. Neighbor = _U : i' = i - 1, j' = j
void addPossibleEdges(int i, int j, int neighbor, char product[n][n][2]){
    // neighbor's coordinates
    int ni, nj, i0, j0;
    int i0 = i, j0 = j;
    connection(neighbor, &i, &j, n);
    ni = i; nj = j;
    i = i0; j = j0;
    
    // type of this and its neighbor
    int rotationsArr[4] = {0};

    for(int rotThis = 0; rotThis < 4; rotThis++)
    {
        rotations(neighbor, i, j, rotThis, product, rotationsArr);
        for(int rotThat = 0; rotThat < 4; rotThat++)
        if(rotationsArr[rotThat])
        {
            addEdge(
                    id(i,  j,  MOD(product[ i][ j][1] + rotThis, 4)),
                    id(ni, nj, MOD(product[ni][nj][1] + rotThat, 4))
                );
        }

    }
}

void build(char product[n][n][2]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 4; k++){
                addPossibleEdges(i, j, intTo_DirectionConverter(k), product);
            }
        }
    }

    for(int i = 0; i < 4; i++)
        addEdge(SOURCE, id(n / 2, n / 2, i)); 
}



/**Solver**/

void print(char product[n][n][2]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", MOD(dir_node[4 * (i * n + j)] - product[i][j][1], 4));
        }
        printf("\n");
    }
}

void Solve(char product[n][n][2]){
    initGraph();
    build(product);
    dfs(SOURCE);
    print(product);
}

int main()
{
    scanf("%d", &n);
    // n * n array with 2 length string: product[n][n][0] = {S, C, L, I, T}, product[n][n][1] = {0, 1, 2, 3} :
    char product[n][n][2];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%s", product[i][j]);
            isComp[4 * (i * n + j)] = (product[i][j][0] == 'C');
        }
    } 

    solve(product); 
}

// ignore:
    // int arr[4] = {0};
    // rotations(_L, 3, 0, product, arr);
    // for(int i = 0; i < 4; i++)
    // {
    //     printf("%d", arr[i]);
    // }