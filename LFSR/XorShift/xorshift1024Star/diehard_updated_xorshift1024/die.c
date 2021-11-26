
#include "header.h"
#include "macro.h"

void do_test(char *fn)
{
  int i, status[16], tmp, id, flag=0, order=0;
  char c;

  for(i=0; i<16; ++i){
    status[i]=0;
  }

  //while( (c=getchar())!='\n' ){
    //if( c==' ' ) continue;

   // ungetc( c, stdin );
    //scanf("%d", &tmp);
   tmp=16;

    ++order;
    if(tmp>0){
      id=tmp-1;
      flag=status[id]=order;
    }
    else{
      id=-tmp-1;
      status[id]=-order;
    }
  //}

  if(order==0) return;

  if(flag<order && status[15]!=-order){
    status[15]=flag+1;
  }  
       
  if(status[15]>0){
    for(i=0; i<15; ++i){
      if( ABS(status[i])<status[15] && status[i]<=0){
        ++order;
        status[i]=order;
      }
    }
 }

  status[15]=1000;
  do{
    tmp=15;

    for(id=0; id<15; ++id){
      if(status[id]<=0){
        continue;
      }
   
      if(status[tmp]>status[id]){
        tmp=id;
        continue;
      }
    }    

    switch(tmp+1){
      case 1: bday(fn); break;
      case 2: operm5(fn); break;  
      case 3: binrnk(fn,"31x31"); binrnk(fn,"32x32"); break;
      case 4: binrnk(fn,"6x8"); break;   
      case 5: bitst(fn); break;
      case 6: monky(fn, "OPSO"); monky(fn, "OQSO"); monky(fn, "DNA"); break;
      case 7: cnt1s(fn, "stream"); break;
      case 8: cnt1s(fn, "specific"); break;   
      case 9: park(fn); break;
      case 10: mindist(fn); break; 
      case 11: sphere(fn); break;
      case 12: squeez(fn); break;
      case 13: osum(fn); break;
      case 14: runtest(fn); break;
      case 15: craptest(fn); break;
      default: break;
    }
   
    status[tmp]=0;
  }while(tmp!=15);

  return;
}

void diehard(char * filename)
{

  char c, fn[100];

  strcpy(fn, filename);

  /*while((c=getchar())==' ') ;

  if(c=='\n'){
    return;
  }

  ungetc(c, stdin);

  gets(fn);

  
  puts("\tEnter your choices.");*/
	//printf("testing %s",fn);
  do_test(fn);

   return;
}


/*main()
{
  diehard();

   return;
}*/
