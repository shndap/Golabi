#include <stdio.h>
#include <string.h>

#define MOD(a,b) ((((a)%(b))+(b))%(b))
#define NMAX 700
#define SIZE 16
#define SOURCE NMAX-1

const int _U = 11, _R = 12 , _D = 13, _L = 14;
int n = 0;

void connection(int direction, int* i, int* j, int n);
void routes(int arr[4], char product[2], int rotate);
void rotations(int direction, int i, int j, int rotThis, char product[n][n][2], int arr[4]);
int intTo_DirectionConverter(int direction);
void printGraphNode(int s, char product[n][n][2]);


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
    routes(routesArr0, product[i0][j0], MOD(4 - product[i0][j0][1] + '0' + rotThis, 4)); 

    if(down == -1)     index = 0;  if(right == 1)     index = 1; if(down == 1)     index = 2; if(right == -1)     index = 3;

    secondIndex = (index + 2) % 4; 

    if(routesArr0[index] == 0)
    {
        return;
    }
    for(int k = 0; k < 4; k++)
    {
        routes(routesArr, product[i][j], MOD(4 - product[i][j][1] + '0' + k, 4));
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

int newID(int i, int j){
    return n * i + j;
}

int newRow(int _id){
    return _id / n;
}

int newCol(int _id){
    return _id % n;
}

// id of the neighbor cell
int neighbor_id(int _id, int dir){
    int i = newRow(_id);
    int j = newCol(_id);

    int ni = i, nj = j;
    
    switch (dir)
    {
    case 0: //up
        ni = MOD(ni - 1, n);
        break;
    
    case 1: //right
        nj = MOD(nj + 1, n);
        break;

    case 2: //down
        ni = MOD(ni + 1, n);
        break;

    case 3: //left
        nj = MOD(nj - 1, n);
        break;

    default:
        break;
    }

    return newID(i, j);
}

// relative position function (U, R, D, L)
int neighborPos(int _id, int n_id){
    int i = row(_id), ni = row(n_id),
        j = col(_id), nj = col(n_id);

    if(ni - i == 1) return 2;
    if(i - ni == 1) return 0;
    if(nj - j == 1) return 1;
    if(j - nj == 1) return 3;
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

// number of unvisited nodes
int rem;


// !TEMP! adjacency list of the graph
int __adj[NMAX][SIZE + 1];

// !TEMP! of is the node is visited or not
int __visited[NMAX];

// !TEMP! direction of a node
int __dir_node[NMAX];

// !TEMP! number of unvisited nodes
int __rem;

int _rem_;


// initialize graph
void initGraph(){
    rem = n * n;
    for(int i = 0; i < NMAX; i++)
        adj[i][SIZE] = visited[i] = 0;
}

// copy arrays into temp
void copy(){
    memcpy(__adj, adj, sizeof(__adj));
    memcpy(__visited, visited, sizeof(__visited));
    memcpy(__dir_node, dir_node, sizeof(__dir_node));
    __rem = rem;
}

// pase temp into arrays
void paste(){
    memcpy(adj, __adj, sizeof(adj));
    memcpy(visited, __visited, sizeof(visited));
    memcpy(dir_node, __dir_node, sizeof(dir_node));
    rem = __rem;
}


//empty vis and dir
void empty(){
    for(int i = 0; i < NMAX; i++)
        visited[i] = 0;
    
    rem = n * n;
}

// connects v->u
void addEdge(int v, int u){
    if(isComp[idInTable(v)])
        return;
    int size = adj[v][SIZE]++;
    adj[v][size] = u;
    // printf("v:%d u:%d\n", v, u);
}

int _[12][12];
int __[12][12];
int ___;

void copy_prime(int rot[n][n], int vis[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            _[i][j] = rot[i][j];
            __[i][j] = vis[i][j];
        }
    }
    ___ = _rem_;
}

void paste_prime(int rot[n][n], int vis[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            rot[i][j] = _[i][j];
            vis[i][j] = __[i][j];
        }
    }

    _rem_ = ___;
}

// dfs algorithm, returns 1 if it ended in a source
int dfsp(int s, char product[n][n][2], int rot[n][n], int vis[n][n], int preRot){
    int _i = newRow(s);
    int _j = newCol(s);
    printf("%c%c\n", product[_i][_j][0], product[_i][_j][1]);
    printf("%d\n", _rem_);
    if(_rem_ == 0)
        return 2;
    vis[_i][_j] = 1;
    _rem_--;
    
    int rt[4] = {0, 0, 0, 0};

    if(product[_i][_j][0] == 'C' && !_rem_){
        
        int curRot = product[_i][_j][1];
        rot[_i][_j] = MOD(preRot - curRot, 4);
        return 1;
    }

    for(int r = 0; r < 4; r++){
        routes(rt, product[_i][_j], r);
        if(preRot != -1 && rt[preRot] == 0)
            continue;

        int worked = 1;
        for(int rix = 0; rix < 4; rix++){
            if(rt[rix]){
                int _i_ = _i, _j_ = _j;
                connection(intTo_DirectionConverter(rix), &_i_, &_j_, n);

                if(!vis[_i_][_j_]){
                    int kirkhar = dfsp(newID(_i_, _j_), product, rot, vis, ((preRot + 2) % 4));
                    copy_prime(rot, vis);
                    if(!kirkhar){
                        paste_prime(rot, vis);
                        worked = 0;
                        break;
                    }


                } 
            }
        }

        if(worked){
            rot[_i][_j] = r;
            return 1;
        }
    }
    return 0;
}

/** Graph Builder **/

// connect possible cases of two nodes 
// e.g. Neighbor = _U : i' = i - 1, j' = j
void addPossibleEdges(int i, int j, int neighbor, char product[n][n][2]){
    // neighbor's coordinates
    int ni, nj, i0, j0;
    i0 = i, j0 = j;
    connection(neighbor, &i, &j, n);
    ni = i; nj = j;
 
    int rotationsArr[4] = {0};

        
    for(int rotThis = 0; rotThis < 4; rotThis++)
    {
        rotations(neighbor, i0, j0, rotThis, product, rotationsArr);
        for(int rotThat = 0; rotThat < 4; rotThat++)
        if(rotationsArr[rotThat])
        {
            // printf("%d->%d %d->%d\n", i, ni, j, nj);
            addEdge(
                    id(i0,  j0, intTo_DirectionConverter(rotThis)),
                    id( i,  j, intTo_DirectionConverter(rotThat))
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
        addEdge(SOURCE, id(n / 2, n / 2, intTo_DirectionConverter(i))); 
}



/**Solver**/

void print(char product[n][n][2]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j != n - 1)
                printf("%d ", MOD(directionTo_IntConverter(dir_node[4 * (i * n + j)]) - (product[i][j][1] - '0'), 4));
            else
                printf("%d", MOD(directionTo_IntConverter(dir_node[4 * (i * n + j)]) - (product[i][j][1] - '0'), 4));
        }
        printf("\n");
    }
}

// for debugging
void printVis(){
    printf("\n\t%d\n", rem);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j != n - 1)
                printf("%d ", visited[4 * (i * n + j)]);
            else
                printf("%d ", visited[4 * (i * n + j)]);
        }
        printf("\n");
    }
}

//for debugging
void checkTableId(){
    printf("CHECK\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int d = 0; d < 4; d++){
                printf("%d|", idInTable(id(i, j, intTo_DirectionConverter(d))));
            }
            printf(" ");
        }
        printf("\n");
    }
}

//for debugging 
void printGraphNode(int s, char product[n][n][2]){
    int t_id = idInTable(s);
    int c_dir = dir(s);
    int c_i = row(s);
    int c_j = col(s);

    printf("(%d %d)(%c)(%d)(%d)[%d]", c_i, c_j, product[c_i][c_j][0], t_id, s, directionTo_IntConverter(c_dir));
}

void printGraph(char product[n][n][2]){
    int MAX = 4 * ((n - 1) * n + n - 1) + 3;

    for(int i = 0; i < MAX; i++){
        printGraphNode(i, product);
        printf(":\n");
        for(int z = 0; z < adj[i][SIZE]; z++){
            printf("\t");
            printGraphNode(adj[i][z], product);
            printf("\n");
        }
    }
}

void solve(char product[n][n][2]){
    // checkTableId();


    initGraph();
    // printf("DONE");
    build(product);

    printGraph(product);

    // printf("DONE2");
    for(int i = 0; i < 4; i++){
        // dfs(id(n / 2, n / 2, intTo_DirectionConverter(i)), product); 
        printVis();
        empty();
    }
        print(product);
    // // printf("DONE3");    
}

void solveprime(char product[n][n][2]){
    int _vis[n][n];
    int _rot[n][n];
    _rem_ = n*n;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            _vis[i][j] = _rot[i][j] = 0;

    dfsp(newID(n / 2, n / 2), product, _rot, _vis, -1);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", _rot[i][j]);
        }
        printf("\n");
    }
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

    solveprime(product); 
}

// ignore:
    // int arr[4] = {0};
    // rotations(_L, 3, 0, product, arr);
    // for(int i = 0; i < 4; i++)
    // {
    //     printf("%d", arr[i]);
    // }
    // 
    /*
3
C0 T3 C2
L3 S2 C3
L0 I2 C0
    */
    /*
3
C1 T0 C3
L1 S2 C3
L0 I1 C3
    */