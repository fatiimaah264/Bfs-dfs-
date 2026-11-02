#include <stdio.h>
#include <string.h>

#define MAX 20

char names[MAX][30];          /* file / directory names */
int  adj[MAX][MAX];           /* adjacency matrix */
int  n = 0;                   /* number of nodes */

int findIndex(const char *name) {
    for (int i = 0; i < n; i++)
        if (strcmp(names[i], name) == 0) return i;
    return -1;
}

/* ---------- BFS ---------- */
int bfs(int start, const char *target) {
    int visited[MAX] = {0}, queue[MAX], front = 0, rear = 0, found = 0;
    printf("BFS traversal: ");
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear) {
        int u = queue[front++];
        printf("%s ", names[u]);
        if (strcmp(names[u], target) == 0) { found = 1; break; }
        for (int v = 0; v < n; v++)
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
    }
    printf("\n");
    return found;
}

/* ---------- DFS ---------- */
int dfsUtil(int u, const char *target, int visited[]) {
    visited[u] = 1;
    printf("%s ", names[u]);
    if (strcmp(names[u], target) == 0) return 1;
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !visited[v])
            if (dfsUtil(v, target, visited)) return 1;
    return 0;
}

int dfs(int start, const char *target) {
    int visited[MAX] = {0};
    printf("DFS traversal: ");
    int found = dfsUtil(start, target, visited);
    printf("\n");
    return found;
}

int main() {
    int e;
    char a[30], b[30], startName[30], target[30];

    printf("Enter number of files/directories: ");
    scanf("%d", &n);
    printf("Enter names:\n");
    for (int i = 0; i < n; i++) scanf("%s", names[i]);

    printf("Enter number of connections (edges): ");
    scanf("%d", &e);
    printf("Enter each connection as: parent child\n");
    for (int i = 0; i < e; i++) {
        scanf("%s %s", a, b);
        int u = findIndex(a), v = findIndex(b);
        if (u == -1 || v == -1) { printf("Invalid name, skipped.\n"); continue; }
        adj[u][v] = 1;
        adj[v][u] = 1;   /* undirected; remove this line for a directed tree */
    }

    printf("\nAdjacency Matrix:\n      ");
    for (int i = 0; i < n; i++) printf("%-8.7s", names[i]);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%-6.5s", names[i]);
        for (int j = 0; j < n; j++) printf("%-8d", adj[i][j]);
        printf("\n");
    }

    printf("\nEnter starting node: ");
    scanf("%s", startName);
    printf("Enter file to search: ");
    scanf("%s", target);

    int s = findIndex(startName);
    if (s == -1) { printf("Starting node not found.\n"); return 1; }

    printf("\n");
    printf("BFS result: %s\n\n", bfs(s, target) ? "File FOUND" : "File NOT found");
    printf("DFS result: %s\n",   dfs(s, target) ? "File FOUND" : "File NOT found");
    return 0;
}
