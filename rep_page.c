#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct frame_bit {
	int temp;
	int bit : 2;
};

int oldest_frame(int *frame, int size){
	int old = 0;
	int min = frame[0];

	for(int i = 0;i<size; i++){
		if(frame[i] < min){
			min = frame[i];
			old = i;
		}
	}

	return old;
}

//reading the input.txt file
void readInput(int *frames, int *pages, int *referenceString){
	char ch;
	char buf[100];
	int page = 0;
	char *fname = (char*) calloc(200,sizeof(char));
	printf("FILE NAME : ");
	scanf("%s",fname);
	FILE *fp = fopen(fname, "r");

	ch = fgetc(fp);
	*frames = atoi(&ch);

	fgetc(fp); // no Enter

	fgets(buf, sizeof(buf), fp);
	char *str = strtok(buf, " ");

	while(str != NULL)
	{
		referenceString[page] = atoi(str);
		page++;
		str = strtok(NULL, " ");
	}
	*pages = page;

	fclose(fp);
	free(fname);
}

int second_chance_page(int frames, int pages, int *referenceString){
	struct frame_bit fb[frames];
	int pageFaults = 0, m, n, s, point = 0;
	char fault;

	printf("Used method : Second-Chance\n");
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
            fb[m].temp = -1;
	    fb[m].bit = 0;
      }
      for(m = 0; m < pages; m++)
      {
            s = 0;
	    fault = 'F';
            for(n = 0; n < frames; n++)
            {
                  if(referenceString[m] == fb[n].temp)
                  {
                        s++;
                        pageFaults--;
			fault = ' ';
			fb[n].bit = 1;
                  }
            }
            pageFaults++;
            if((pageFaults <= frames) && (s == 0))
            {
                  fb[pageFaults-1].temp = referenceString[m];
		  fb[pageFaults-1].bit = 0;
            }
            else if(s == 0)
            {
		    if(point == 0) point = pageFaults-2;
		    if(fb[(point+1) % frames].bit == 0){
			point++;
                  	fb[point % frames].temp = referenceString[m];
		    }
		    else{
			    point++;
			    while(fb[point % frames].bit == 1){
				    fb[point % frames].bit=0;
				    point++;
			 }
			    fb[point % frames].temp = referenceString[m];
		    }
            }

	    printf("%d\t\t",m+1);
            for(n = 0; n < frames; n++)
            {
		  if(fb[n].temp == -1)
			  printf("%c\t", ' ');
		  else
		  	printf("%d\t", fb[n].temp);
            }
	    printf("%c\n", fault);
      }
	    printf("Number of page faults : %d times\n", pageFaults);
	    printf("**************************************************\n");

	return 0;
}

int lru_page(int frames, int pages, int *referenceString){
	int temp[frames];
	int frame[frames];
	int pageFaults = 0, m, n, s;
	char fault;
	int old = 0;

	printf("Used method : LRU\n");
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
			frame[n] = m;
                  }
            }
            pageFaults++;
            if((pageFaults <= frames) && (s == 0))
            {
                  temp[pageFaults-1] = referenceString[m];
		  frame[pageFaults-1] = m;
            }
            else if(s == 0)
            {
			old = oldest_frame(frame, frames);
			temp[old] = referenceString[m];
			frame[old] = m;
		  

            }

	    printf("%d\t\t",m+1);
            for(n = 0; n < frames; n++)
            {
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
			    frame[a] = 0;
		    	for(i = m+1;i<pages;i++){
			    if(referenceString[i] == temp[a]){
				    frame[a] = i;
				    break; }
			}
			if(frame[a] == 0) frame[a] = pages;
		    }
		   
		    if(frame[0]<frame[1]){
			    if(frame[1]<frame[2]){
				    temp[2] = referenceString[m];
				    frame[2] = 0;
			    }
			    else{
				    temp[1] = referenceString[m];
				    frame[1] = 0;
			    }
		    }
		    else {
			    if(frame[0]<frame[2]){
				    temp[2] = referenceString[m];
				    frame[2] = 0;
			    }
			    else{
			    	temp[0] = referenceString[m];
				frame[0] = 0;
			    }
		    }
	    }

	    printf("%d\t\t",m+1);
            for(n = 0; n < frames; n++)
            {
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

      opti_page(frames, pages, referenceString);
      fifo_page(frames, pages, referenceString);
      lru_page(frames, pages, referenceString);
      second_chance_page(frames, pages, referenceString);

      return 0;
}

