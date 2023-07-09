#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COUNT 10

struct node
{
    int x;
    struct node *right;
    struct node *left;
    int nodes;
};

struct node *a[10000000];

int i;

int c_nodes(struct node *ptr)
{
    if (ptr == NULL)
        return 0;
    return ptr->nodes;
}

struct node *add_node(int z)
{
    struct node *ptr;
    ptr = (struct node *)calloc(1, sizeof(struct node));
    ptr->x = z;
    ptr->right = NULL;
    ptr->left = NULL;
    ptr->nodes = 1;
    return ptr;
}

struct node *create_new_tree(int n, int j) // j is th left extreme
{

    if (j > n)
        return NULL;
    int mid;
    struct node *temp;

    mid = (j + n) / 2;
    temp = a[mid];

    temp->left = create_new_tree(mid - 1, j); // left of array of a[mid]
    temp->right = create_new_tree(n, mid + 1); //right of array of a[mid]
    temp->nodes = c_nodes(temp->left) + c_nodes(temp->right) + 1;
    temp = a[mid];

    return temp;
}

void fill_array(struct node *temp)
{
    if (temp == NULL)
    {
        return;
    }

    fill_array(temp->left);
    a[i] = temp;
    i++;

    fill_array(temp->right);
}

struct node *balance(struct node *ptr)
{

    int n;
    n = ptr->nodes;

    i = 0;
    fill_array(ptr); //fill elements of old binary tree in array

    struct node *ret = create_new_tree(n - 1, 0); // new balanced binary tree

    return ret;
}

void free_memory(struct node *ptr)
{

    if (ptr == NULL)
        return;
    free_memory(ptr->left);
    free_memory(ptr->right);
    ptr->left = NULL;
    ptr->right = NULL;
    free(ptr);
}

struct node *insert_new_node(struct node *root, int num)
{

    if (root == NULL)
    {
        return add_node(num);
    }

    struct node *temp;
    struct node *ptr;
    ptr = NULL;
    struct node *store;
    int flag = 0;
    temp = root;
    while (temp->right != NULL)
    {
        temp->nodes++;
        if ((4 * (c_nodes(temp->right) + 1) > 3 * (temp->nodes)) && flag == 0)
        {
            if (temp == root)
            {
                flag = 1;
            }
          else
            {
                store = ptr;
                flag = 2;
            }
        }
        ptr = temp; //ptr is storing parent of temp
        temp = temp->right;
    }

    temp->right = add_node(num);
    temp->nodes++;
    if (flag == 1)
        root = balance(root);
    if (flag == 2)
        store->right = balance(store->right);

        return root;
}


int main()
{
    struct node *root;

    clock_t start_t, end_t;
    double total_t;
    root = NULL;
    int n;
    // scanf("%d", &n);

    int j;
    FILE* f_ptr;
    f_ptr = fopen("dsa-part1.csv", "w");

    for (n = 100000; n <= 100001; n++) // change n to 100000 to 1000000// remove this loop
    {
        root = NULL;
       start_t = clock(); // send inside
        for (j = 1; j <= n; j++) // j from 1 to n
        {
//start_t
            root = insert_new_node(root, j);
            //endt_t , total_t, print
          //  root = check_verify_balance(root);
        }




        free_memory(root);  // dont remove this// create array 10^7 double , storing time // also dont use i (global varibale) use j
        end_t = clock();
        printf("%d  ", n);
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("%lf\n", total_t);
        fprintf(f_ptr, "%d %lf\n", n*50000, total_t);
    }
    fclose(f_ptr);
    return 0;
}
