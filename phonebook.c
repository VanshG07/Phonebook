#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    char name[40];
    char phone_no[10];
    struct node*left;
    struct node*right;
};
struct node*head=NULL;
char temp_n[40];
char temp_p[10];

struct node* createNode(char *name,char *phone_no){
    struct node*new_node=(struct node*)malloc(sizeof(struct node));
    strcpy(new_node->name,name);
    strcpy(new_node->phone_no,phone_no);
    new_node->left=new_node->right=NULL;
    return new_node;
}


void insert(char *name,char *phone_no){
    struct node*root=head;
    struct node *prev = NULL;
    if(root==NULL){
        struct node*new_node=createNode(name,phone_no);
        head=new_node;
        return;
    }
    while(root!=NULL){
        prev = root;
        if(strcmp(root->name,name)==0){
            printf("Name is already present !");
            return;
        }
        else if(strcmp(root->name,name)>0){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    struct node* new = createNode(name,phone_no);
    if(strcmp(prev->name,name)>0){
        prev->left = new;
    }
    else{
        prev->right = new;
    }
}

struct node* inorderpre(struct node* node)
{
    while (node->right != NULL)
        node = node->right;
 
    return node;
}

struct node* deleteNode(struct node* root, char*name)
{
    if (root == NULL)
        return root;
 
    if (strcmp(root->name,name)>0)
        root->left = deleteNode(root->left, name);
 
    else if (strcmp(root->name,name)<0)
        root->right = deleteNode(root->right, name);

    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = inorderpre(root->left);
        strcpy(root->name,temp->name);
        root->left = deleteNode(root->left, temp->name);
    }
    return root;
}

void search(struct node*root,char *phone){
    if(root!=NULL){
        search(root->left,phone);
        if(strstr(root->phone_no,phone)){
            printf(" Name : %-12s , Phone No.: %-10s \n",root->name,root->phone_no);
        }
        search(root->right,phone);
    }
}

void show_ascending(struct node*root){
    if(root!=NULL){
        show_ascending(root->left);
        printf(" Name : %-12s , Phone No.: %-10s \n",root->name,root->phone_no);
        show_ascending(root->right);
    }
}

void show_descending(struct node*root){
    if(root!=NULL){
        show_descending(root->right);
        printf(" Name : %-12s , Phone No.: %-10s \n",root->name,root->phone_no);
        show_descending(root->left);
    }
}

int main(){
    menu:
    printf("\n-----MENU-----\n");
    printf("1. Add Contact\n");
    printf("2. Delete Contact\n");
    printf("3. Search Contact\n");
    printf("4. Show in Ascending Order\n");
    printf("5. Show in Descending Order\n");
    printf("6. Exit Program\n");
    int choice;
    printf("Enter Choice :\n");
    scanf("%d",&choice);
    printf("\n");
    if(choice==1){
        printf("Enter Name : ");
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_n);

        printf("Enter Phone no. : ");
        scanf("%[^\n]%*c",temp_p);
        insert(temp_n,temp_p);
    }
    else if(choice==2){
        if(head==NULL){
            printf("No contacts to delete !\n");
            goto menu;
        }
        printf("Enter Exact Name to delete : ");
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_n);
        head=deleteNode(head,temp_n);
    }
    else if(choice==3){
        struct node*root=head;
        if(root==NULL){
            printf("\nNo Contacts to search !\n");
            goto menu;
        }
        printf("Enter Phone no. : ");
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_p);
        printf("\n");
        search(root,temp_p);
        printf("\n");
    }
    else if(choice==4){
        struct node*root=head;
        if(root==NULL){
            printf("\nNo Contacts are there !\n");
            goto menu;
        }
        printf("\nPrinting in Ascending Order :\n");
        show_ascending(root);
        printf("\n");
    }
    else if(choice==5){
        struct node*root=head;
        if(root==NULL){
            printf("\nNo Contacts are there !\n");
            goto menu;
        }
        printf("\nPrinting in Descending Order :\n");
        show_descending(root);
        printf("\n");
    }
    else if(choice==6){
        exit(0);
    }
    else{
        printf("Enter correct number !\n");
    }
    goto menu;
return 0;
}
