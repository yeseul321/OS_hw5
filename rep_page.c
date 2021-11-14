#include <stdio.h>
#include <stdlib.h>

//reading the input.txt file
void readInput(int *frames, int *pages, int *referenceString){
	char ch;
	int page = 0;
	FILE *fp = fopen("input.txt", "r");
	ch = fgetc(fp);
	*frames = atoi(&ch);
	while((ch = fgetc(fp)) != EOF)
	{
		if((ch != ' ')&&(ch != '\n')){
			referenceString[page] = atoi(&ch);
			page++;
		}
	}
	*pages = page;
	fclose(fp);
}

int lru_page(int frames, int page, int *referenceString){

	return 0;
}

int opti_page(int frames, int pages, int *referenceString){
	int temp[frames];
	int frame[frames];
	int pageFaults = 0, m, n, s;
	char fault;

	printf("Used method : OPT\n");
	printf("page reference string : ");
	for(int m = 0; m < pages; m++)
      	{
           printf("%d ", referenceString[m]);
      	}
	printf("\n\n");
	printf("\tframe   ");

	for(int m = 1; m<=frames;m++){
		printf("%d\t",m);
	}
	printf("page fault\ntime\n");

	/*****************************************/
	for(m = 0; m < frames; m++)
      {
            temp[m] = -1;
      }
      for(m = 0; m < pages; m++)
      {
            s = 0;
	    fault = 'F';
            for(n = 0; n < frames; n++)
            {
                  if(referenceString[m] == temp[n])
                  {
                        s++;
                        pageFaults--;
			fault = ' ';
                  }
            }
            pageFaults++;
            if((pageFaults <= frames) && (s == 0))
            {
                  temp[pageFaults-1] = referenceString[m];
            }
	    else if(s == 0){
		    int i = 0;
		    for(int a = 0;a<frames;a++){
		    	for(i = m+1;i<pages;i++){
			    if(referenceString[i] == temp[a]){
				    frame[a] = i;
				    break; }
			}
			if(frame[a] == 0) frame[a] = pages;
		    }
		    if(frame[0]<frame[1]){
			    if(frame[1]<frame[2])
				    temp[2] = referenceString[m];
			    else
				    temp[1] = referenceString[m];
		    }
		    else temp[0] = referenceString[m];
	    }

	    printf("%d\t\t",m+1);
            for(n = 0; n < frames; n++)
            {
                  //printf("%d\t\t",n+1);
		  if(temp[n] == -1)
			  printf("%c\t", ' ');
		  else
		  	printf("%d\t", temp[n]);
            }
	    printf("%c\n", fault);
      }
	    printf("Number of page faults : %d times\n", pageFaults);
	    printf("**************************************************\n");
	return 0;
}

int fifo_page(int frames, int pages, int *referenceString){
	int temp[frames];
	int pageFaults = 0, m, n, s;
	char fault;

	//printf("frames : %d, pages : %d\n", frames, pages);
	printf("Used method : FIFO\n");
	printf("page reference string : ");
	for(int m = 0; m < pages; m++)
      	{
           printf("%d ", referenceString[m]);
      	}
	printf("\n\n");
	printf("\tframe   ");
	for(int m = 1; m<=frames;m++){
		printf("%d\t",m);
	}
	printf("page fault\ntime\n");

	for(m = 0; m < frames; m++)
      {
            temp[m] = -1;
      }
      for(m = 0; m < pages; m++)
      {
            s = 0;
	    fault = 'F';
            for(n = 0; n < frames; n++)
            {
                  if(referenceString[m] == temp[n])
                  {
                        s++;
                        pageFaults--;
			fault = ' ';
                  }
            }
            pageFaults++;
            if((pageFaults <= frames) && (s == 0))
            {
                  temp[pageFaults-1] = referenceString[m];
            }
            else if(s == 0)
            {
                  temp[(pageFaults - 1) % frames] = referenceString[m];
            }
	    
	    printf("%d\t\t",m+1);
            for(n = 0; n < frames; n++)
            {
                  //printf("%d\t\t",n+1);
		  if(temp[n] == -1)
			  printf("%c\t", ' ');
		  else
		  	printf("%d\t", temp[n]);
            }
	    printf("%c\n", fault);
      }
	    printf("Number of page faults : %d times\n", pageFaults);
	    printf("**************************************************\n");
	    return 0;
}
int main()
{
      int referenceString[30], pageFaults = 0, m, n, s, pages, frames;

      readInput(&frames, &pages, referenceString);

      //for(int m = 0; m < pages; m++)
      //{
      //     printf("%d ", referenceString[m]);
      //}

      opti_page(frames, pages, referenceString);
      fifo_page(frames, pages, referenceString);
      return 0;
}

