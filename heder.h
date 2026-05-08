#ifndef HEDER_H
#define HEDER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SUCCESS 1
#define FAILURE 2
#define P_SUCCESS 3

extern int update_status;
extern int create_status;

typedef struct sub_node{
    int w_count;
    char *f_name;
    struct sub_node *link;

}Sub_node;

typedef struct main_node{
    char *word;
    int f_count;
    int len;
    Sub_node *S_link;
    struct main_node *M_link;
}Main_node;

typedef struct hash
{
    int index;
    Main_node *link;

}Hash;

typedef struct node
{
    char *f_name;
    struct node *link;
}Node;


int validate(int argc, char *argv[],Node **head);
int create_file_list(Node **head,char *word);
int create_database(Hash *HT,Node *head);
int create_mainNode(Hash *HT,int index,char *word,char *filename);
int is_file_already_indexed(Hash *HT, char *filename);
int search_database(Hash *arr,char *word);
int display_database(Hash *arr,int size);
int print_list(Node *head);
int save_database(Hash *arr);
int insert_last(Node **head,char *word);
int update_database(Hash *arr);

#endif
