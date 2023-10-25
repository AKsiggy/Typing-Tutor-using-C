#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct report{
	double timetaken;
	int accuracy;
	struct report *next;
}report;

report *head = NULL;

void calculate(int ,int ,double);
void begin();
void quit();
void saving();
void progress();
void nextwork();
char*get_para();
void choices();
void save_score();
void store(report *);

void store(report *ptr)
{
	head = ptr;
	head = NULL;	
}

int homepage(void)
{

	saving();
	printf("\nWELCOME TO THE TYPING TUTOR!!");
	sleep(2);
	printf("\n\nAre you ready to begin?\n");
	choices();
	
}

void freemem()
{
	FILE*fp;
	fp=fopen("progress.txt","w");
	fclose(fp);
	printf("\nYour Progress has been deleted\n");
	nextwork();

};
void saving()
{
	char name[20];
    FILE*fp;
	fp=fopen("progress.txt","a");
	printf("\nEnter your Name: ");
	scanf("%s",name);
	fprintf(fp,"\n%s",name);
	fclose(fp);
};

void choices()
{
	int c;
	
	printf("\n\nPress 1 to begin.\nPress 2 to view your progress.\nPress 3 to erase all progress\nPress 4 to Exit.\n\n");
	scanf("%d", &c);
	switch(c){
        	case 1: begin();
        	        break;
		    case 2: progress();
			        break;
		    case 3: freemem();
			        break;
        	case 4: quit();
                	break;
        	default:printf("Please enter a valid option");
			choices();
    	}
}

void begin()
{
	int correct=0, wrong=0, i, x;
	double timetaken;
	clock_t start, end;
	char a[100], c ;
	char b[1000];
	get_para(b);
	printf("\nenter the following words as it is as fast as you can:\n");
	sleep(2);
	printf("\n%s\n", b);
	start= time(NULL);
	scanf(" %[^\n]s", a);
	end= time(NULL);
	x = strlen(b);
	for(i = 0 ; i < x ; i++){
	        if (a[i] == b[i])
	            correct++;
	        else
	            wrong++;
	}
	timetaken = difftime(end,start);
	calculate(correct, wrong, timetaken);
	nextwork();
}

void calculate(int correct,int wrong,double timetaken)
{
	int per;
	report *ptr;
	
	ptr = (report*)malloc(sizeof(report*));
	ptr->timetaken = timetaken;
	printf("\nRight letters: %d\n", correct);
	printf("wrong letters: %d\n", wrong);
	printf("timetaken: %.0lf seconds\n", timetaken);
	ptr->accuracy = (100*correct)/(correct+wrong);
	printf("accuracy: %d", ptr->accuracy);
	printf("%%");
	printf("\n\n");
	store(ptr);
	save_score(ptr->accuracy,timetaken);
}

void nextwork()
{
	int c;
	
	printf("Do you want to continue?(1=Yes/0=No)");
	scanf("%d", &c);
	switch(c){
		case 1: choices();
			break;
		case 0: quit();
			break;
		default:printf("wrong input");
			nextwork();
	}
}
void save_score(int accuracy,double timetaken)
{
    FILE*fp;
	fp=fopen("progress.txt","a");
	fprintf(fp,"\naccuracy:%d\ntimetaken:%.0lf\n",accuracy,timetaken);
	fclose(fp);
}

void progress()
{
	FILE*fp;
	char ch;
	fp=fopen("progress.txt","r");
	while(!feof(fp))
	{
		ch = fgetc(fp);
		fputc(ch,stdout);
	}
	fclose(fp);
	nextwork();

}
void quit()
{
	exit(0);
}

char* get_para(char a[])
{
	FILE*fp;
	fp=fopen("TexT.txt","r");
	srand(time(0));
	int num = (rand() % 11);
	char x[500];
	int i=0; 
	while(fgets(x,500,fp)!=NULL)
	{
		if(i==num)
		{
			break;
		}
		i++;
	}
	strcpy(a, x);
	return a;
}

int main(void)
{ 
        homepage();
        return 0;
}
