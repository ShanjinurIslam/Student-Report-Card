// as we don't know the fixed number of number students any user would want to add we will dynamic array of struct

/*

Here struct Record contains 4 data types, 1) first_name 2) family_name 3) up_number 4) marks array of length 3

initial dynamic array size is chosen to be 4.

1. void init() initializes the vector to an initial array of 4 
2. void add_data() function addes data which are given as a parameter if size overflows the max size is reallocates the memory and then stores data record
3. void search_data() function searches data which are given up_number as a parameter
4. void modify_data() function modify data which are given up_number as a parameter and when it is found module number is asked and then it is edited
5. void delete_data() function deletes data which are given up_number as a parameter
6. void show_records() functions prints all records stored in the dynamic array
7. void print_to_file() current array to file given file pointer

8. main() function:
    user is asked for for option selection
    -> each option contains route to above functions() { add, search, modify,delete } and user can repeat this function unless he/she wants to go back to decide to main menu
    -> read from file option tries to read "input.txt" if it does not exist then creates it (user dependent) and if it is empty saves current array to the file
    -> save to file option tries to write to "output.txt" if it does not exist then creates it (user dependent) and saves current array to output file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX = 4;

struct Record{
    char first_name[40];
    char family_name[40];
    int  up_number ;
    int  marks[3] ;
};

typedef struct Record StudentRecord ;

StudentRecord *records ;
int size ;

void init_dynamic_array(){
    size = 0 ;
    records = malloc(MAX*sizeof(StudentRecord));
}

void add_data(char *first_name,char *family_name,int up_number,int marks[]){
    if(size>MAX){
        records = realloc(records,(2*MAX)*sizeof(StudentRecord));
        MAX = 2*MAX;
    }

    StudentRecord new_record ;
    strcpy(new_record.first_name,first_name);
    strcpy(new_record.family_name,family_name);
    new_record.up_number = up_number ;
    int i;
    for(i=0;i<3;i++){
        new_record.marks[i] = marks[i]; 
    }

    records[size++] = new_record ;
}

void search_data(int up_number){
    int i = 0;
    int index = -1 ;
    for(i = 0 ;i<size;i++){
        if(records[i].up_number==up_number){
            printf("\nFIRST_NAME,FAMILY_NAME,UP_NUMBER,ARTIFECT_1,ARTIFECT_2,ARTIFECT_3,OVERALL_GRADE\n\n");
            printf("%s,%s,%d,",records[i].first_name,records[i].family_name,records[i].up_number);
            for(int j=0;j<3;j++){
                printf("%d,",records[i].marks[j]);
            }
            printf("%lf ",(records[i].marks[0]*.3 +records[i].marks[1]*.4 + records[i].marks[2]*.3));
            printf("\n\n");
            index = i ;
            break ;
            
        }
    }

    if(index==-1){
        printf("\n\nRecord Not Found\n\n");
    }
    
}

void modify_data(int up_number){
    int i = 0;
    int index = -1;
    for(i = 0 ;i<size;i++){
        if(records[i].up_number==up_number){
            index = i ;
            break;
        }
        
    }
    if(index!=-1){
        int module_number ;
        printf("Enter module number (1-3): ");
        scanf("%d",&module_number);
        if(module_number<1 && module_number>3){
            printf("Invalid module number");
        }
        else{
            int mark ;
            printf("Edit mark (Previous mark : %d): ",records[index].marks[module_number-1]);
            scanf("%d",&mark);
            records[index].marks[module_number-1] = mark;
        }
    }
    else{
        printf("\n\nRecord Not Found\n\n");
    }
}

void delete_data(int up_number){
    int i = 0;
    int index = -1;
    for(i = 0 ;i<size;i++){
        if(records[i].up_number==up_number){
            index = i ;
            break;
        }
        
    }
    if(index!=-1){
        for(i = index ;i<size-1;i++){
            records[i+1] = records[i] ;
        }
        size-- ;

        printf("Deleted Successfully!!!\n\n");
    }
    else{
        printf("\n\nRecord Not Found\n\n");
    }
}

void show_records(){
    int i ;
    printf("\nFIRST_NAME,FAMILY_NAME,UP_NUMBER,ARTIFECT_1,ARTIFECT_2,ARTIFECT_3,OVERALL_GRADE\n\n");
    for(i=0;i<size;i++){
        printf("%s,%s,%d,",records[i].first_name,records[i].family_name,records[i].up_number);
        for(int j=0;j<3;j++){
            printf("%d,",records[i].marks[j]);
        }
        printf("%lf ",(records[i].marks[0]*.3 +records[i].marks[1]*.4 + records[i].marks[2]*.3));
        printf("\n");
    }
    printf("\n\n");
}

void print_to_file(FILE *fp){
    int i ;
    for(i=0;i<size;i++){
        fprintf(fp,"%s %s %d ",records[i].first_name,records[i].family_name,records[i].up_number);
        for(int j=0;j<3;j++){
            fprintf(fp,"%d ",records[i].marks[j]);
        }
        fprintf(fp,"\n");
    }
}


int main(){
    int read = 0 ;
    // initialization
    init_dynamic_array();
    
    // main menu sector 
    while(1){
        printf("Welcome to Student Report Card system\nAvailable Options:\n1. Add New Record\n2. Read records from file\n3. Search Record\n4. Save Records to File\n5. Modify Student Record\n6. Delete Record\n7. Print Records\n8. Exit\nSelect Option : ");
        int c ;
        scanf("%d",&c);

        if(c==1){
            while(1){
                char first_name[40];
                char family_name[40];
                int  up_number ;
                int  marks[3] ;
                printf("Enter First Name: ");
                scanf("%s",first_name);
                printf("Enter Family Name: ");
                scanf("%s",family_name);
                printf("Enter Up Number: ");
                scanf("%d",&up_number);
                printf("Enter Artifect Numbers: ");
                int i,d ;
                for(i=0;i<3;i++){
                    int d ;
                    scanf("%d",&d) ;
                    marks[i] = d ;
                }
                add_data(first_name,family_name,up_number,marks);
                show_records();
                int s ;
                printf("1. Add Another One?\n2. Back to Main Menu\nSelect an option: ");
                scanf("%d",&s);
                if(s==1){
                    continue ;
                }
                else{
                    break;
                }
            }
        }

        if(c==2){
            FILE *fp = fopen("input.txt","r");
            if(fp==NULL){
                printf("Can not open specific file\nDo you want to create it? 1. YES 2. NO\nSelect Option: ");
                int option ;
                scanf("%d" ,&option);
                if(option==1){
                    fclose(fp);
                    fp = fopen("input.txt","w");
                    fclose(fp);
                }  
                else{
                    
                }
            }
            fp = fopen("input.txt","r");
            int c = fgetc(fp);
            if (c == EOF) {
                printf("File is empty! Saving current records to file...\n");
                ungetc(c, fp);
                fclose(fp);
                fp = fopen("input.txt","w");
                print_to_file(fp);
                fclose(fp);
            } else {
                if(!read){
                    ungetc(c, fp);
                    fp = fopen("input.txt","r");
                    char first_name[40];
                    char family_name[40];
                    int  up_number ;
                    int  marks[3] ;
                    while(fscanf(fp, "%s %s %d %d %d %d \n", first_name, family_name, &up_number, &marks[0],&marks[1],&marks[2])!=EOF){
                        add_data(first_name,family_name,up_number,marks);
                    }
                    read = 1 ;
                }
                show_records();
            } 
        }

        if(c==3){
            while(1){
                int  up_number ;
                printf("Enter Up Number: ");
                scanf("%d",&up_number);
                search_data(up_number);
                int s ;
                printf("1. Search Another One?\n2. Back to Main Menu\nSelect an option: ");
                scanf("%d",&s);
                if(s==1){
                    continue ;
                }
                else{
                    break;
                }
            }
        }

        if(c==4){
            FILE *fp = fopen("output.txt","r");
            if(fp==NULL){
                printf("Can not open specific file\nDo you want to create it? 1. YES 2. NO\nSelect Option: ");
                int option ;
                scanf("%d" ,&option);
                if(option==1){
                    fclose(fp);
                    fp = fopen("output.txt","w");
                    fclose(fp);
                }  
                else{
                    
                }
            }
            fclose(fp);
            fp = fopen("output.txt","w");
            print_to_file(fp);
            printf("\n\nSaved to file successfully!!\n\n");
            fclose(fp);
        }

        if(c==5){
            while(1){
                int  up_number ;
                printf("Enter Up Number: ");
                scanf("%d",&up_number);
                modify_data(up_number);
                int s ;
                printf("1. Modify Another One?\n2. Back to Main Menu\nSelect an option: ");
                scanf("%d",&s);
                if(s==1){
                    continue ;
                }
                else{
                    break;
                }
            }
        }

        if(c==6){
            while(1){
                int  up_number ;
                printf("Enter Up Number: ");
                scanf("%d",&up_number);
                delete_data(up_number);
                int s ;
                printf("1. Delete Another One?\n2. Back to Main Menu\nSelect an option: ");
                scanf("%d",&s);
                if(s==1){
                    continue ;
                }
                else{
                    break;
                }
            }
        }

        if(c==7){
            show_records();
        }

        if(c==8){
            break ;
        }
    }
    
    return 0 ;
}