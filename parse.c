//Arxeio: parse.c
//YLOPOIISI KAI TWN EPEKTASEWN A, B, C, D ME PERETERW EXIDIKEYSI.
/*EPEXIGISI METABLITWN:
errors:    METRITIS ERROR.
Code:      KWDIKOS ERROR.
line:      ARITHMOS GRAMMIS.
column:    ARITHMOS STILIS.
lastchar:  PROIGOUMENOS XARAKTIRAS
current:   TREXON XARAKTIRAS
space:     METRITIS KENWN - TAB
flag:      GINETAI 1 OTAN YPARXEI PERISEYMA STIS AGILES META APO ','
depth:     MEGISTO BATHOS SINOLWN GRAMMIS
sets:      SYNOLIKA ZEYGI SYNOLWN GRAMMIS
digit:     METRITIS PSIFIWN
integers:  METRITIS AKERAIWN
L:         ELENXOS KAI METRISI GIA ARISTERI AGILI '{'
R:         ELENXOS KAI METRISI GIA DEXIA AGILI '}'
*/
#include <stdio.h>
int errors=0;

 //function error(ARITHMOS ERROR,GRAMMI,STILI,PROIGOUMENOS XARAKTIRAS,TREXON XARAKTIRAS);
int error(int code,int line,int column,int lastchar,int current){   
errors++;
 //TA MINIMATA THA EFMANIZONTE MONO GIA TO PRWTO ERROR LOGO APETISIS TIS ASKISIS.
 if(errors==1){ 
   switch(code){
   case 1:
   printf("%d:%d: error: '%c' is invalid character!\n",line,column,current);
   break;
   case 2:
   printf("%d:%d: error: Extra closing brace(s)\n",line,column);
   break;
   case 3:
   printf("%d:%d: error: Missing closing brace(s)\n",line,column);
   break;
   case 4:
   printf("%d:%d: error: Digit expected between '%c' and '%c'\n",line,column,lastchar,current);
   break;
   case 5:
   printf("%d:%d: error: Unexpected end of line\n",line,column);
   break;    
   case 6:
   printf("%d:%d: error: Expected ',' between '%c' and '%c'\n",line,column,lastchar,current);
   break; 
   case 7:
   printf("%d:%d: error: Digit expected after '%c'\n",line,column,lastchar);
   break;
   case 8:
   printf("%d:%d: error: Syntax error, '%c' after '%c'\n",line,column,current,lastchar);
   break;
   case 9:
   printf("%d:%d: error: Digit or bracket expected before '%c'\n",line,column,current);
   break;
   default: //SE AYTI TIN PERIPTWSI EMFANIZETE MONO O KWDIKOS TWN ERROR POY DEN ANIKOYN SE KAPOIA APO
   printf("%d:%d: error:%d\n",line,column,code); //TIS PARAPANW PERIPTWSEIS.
   break;
   }   
  }   
}

int main(void){ 
int col=0,line=1,space=0,lastchar=0,current=0,flag=0,depth=0,sets=0,digit=0,integers=0,L=0,R=0;  

while(current!=EOF){                       //EPANALIPSI OSO O TREXON XARAKTIRAS EINAI DIAFOROS TOU EOF
col++;                                    //KATAMETRISI STILWN GRAMMIS.
current=getchar();                       

if((current >=0   && current <=  8)||   //ELENXOS TWN XARAKTIRWN POY DEN EINAI EPITREPTOI KAI KLISI
   (current >=11  && current <= 31)||  // TIS SYNARTISIS error ME ERROR CODE = 1.
   (current >='!' && current <='*')||
   (current >='.' && current <='/')||
   (current >=':' && current <='z')|| 
   (current =='|')                 || 
   (current >='~' && current <= 127)) error(1,line,col,lastchar,current);

                                                        //EYRESI AKERAIWN.
 if(current>='0' && current<='9'){                    //AN O TREXON EINAI METAXI TWN PSIFIWN 0-9 TOTE..
 digit++;                                            //KATAMETRISI TON PSIFIWN.
 }
 else
 {                                   
  if(digit!=0) integers++;             //AN YPARXOYN ARITHMOI APO TIN PROIGOUMENI KATAMETRISI TOTE..
  digit=0;                            //AYXISI TIS METABLITIS integers KATA 1 KAI MIDENISMOS TIS digit.
 }

 if(current=='{') L++;                              //KATAMETRISI ARISTERWN AGILWN.
 if(current=='}') R++;                             //KATAMETRISI DEXIWN AGILWN.
            
//printf("%d:%d 1 x=%c\tL=%d\tR=%d\tplus=%d\tsets=%d\n",line,col,current,L,R,flag,sets);
      
 if(current==',' && L!=R){       //AN O TREXON EINAI ',' KAI OI L KAI R EXOYN DIAFORA METAXI TOYS TOTE..
   flag=1;                   //PERISSEYEI KATI!, OPOTE I METABLITI flag PAIRNEI TIMI 1
   if(L<R) error(2,line,col,lastchar,current); //AN OI R EINAI PERISOTERES TOTE ERROR CODE = 2

 }
 else{ //current!=',' || L==R             ////AN TREXON DEN EINAI KOMMA H L=R TOTE..
   if(L==R && flag==1){                  //AN OI AGILES EINAI ISODINAMES KAI YPARXEI 
   flag=0;                              //PERISEYMA APO PRIN (flag==1) TOTE..
   sets+=R;                            //AFOY EINAI ISODINAMES PLEON (EKLISE ENA ZEYGOS AGILWN)
   L=0;                               //OPOTE H flag THA PAREI TIN TIMI 0. STH METABLITI
   R=0;                              //sets POY KATAMETRA TA ZEYGI AGILWN EKXORITE TO R. STH SYNEXIA
                                    //OI METABLITES L,R ARXIKOPOIOYNTE ME TIMI 0.
//printf("%d:%d 2 x=%c\tL=%d\tR=%d\tplus=%d\tsets=%d\n",line,col,current,L,R,flag,sets);
   }   //(L==R && flag==1)
 }    //if(current==',' && L!=R).....else

 //AN O TREXON EINAI ',' KAI DEN EXEI PATHTHEI ENTER TOTE..
 if(current!=',' && current!='\n'){    
   if(flag==1 && L>R ){                         //AN YPARXEI PERISEYMA AGILWN APO PRIN KAI L>R TOTE..
   sets+=R;                                    //EKXORISI PLITHOUS APO R AGILES STI sets
//printf("%d:%d 3 x=%c\tL=%d\tR=%d\tplus=%d\tsets=%d\n",line,col,current,L,R,flag,sets);
   L-=R;                                      //MEIOSI TWN L AGILWN KATA R AGILES
   R=0;                                      //MIDENISMOS TWN R AGILWN.
   }

    if(depth<L) depth=L;                         //EYRESI MEGISTOU BATHOUS ME 
                                                //TI MEGISTI TIMI POY THA PAREI H L.

    if(L!=0 && L==R && flag==0){               //OTAN H L=R ALLA OXI STIN PERIPTWSI POU EINAI 0
                                              //KAI DEN YPARXEI PROIGOUMENOS PERISEYMA APO AGILLES
    sets+=R;                                 //(EPIDI PROFANOS DEN EXEI PROIGITHEI KAPOIO ',' METAXI 
                                            //TOYS KAI OI AGILES EINAI APLOS EMFOLEYMENES), TOTE STI 
                                           //sets THA EKXORITHEI KAI TO YPOLOIPO PLITHOS. KAI STH
    L=0;                                  //SYNEXIA L KAI R MIDENIZONTE.
    R=0; 
//printf("%d:%d 4 x=%c\tL=%d\tR=%d\tplus=%d\tsets=%d\n",line,col,current,L,R,flag,sets);
    }
 }

//printf("%d:%d 5 x=%c\tL=%d\tR=%d\tplus=%d\tsets=%d\n",line,col,current,L,R,flag,sets);
  if(col==1 && current==',') error(9,line,col,lastchar,current);        
  if (lastchar==','){                                      //AN O PROIGOUMENOS EINAI ',' KAI EPOMENOS..
       if(current==',')  error(7,line,col,lastchar,current);   //',' ,ERROR CODE = 7 
       if(current=='}')  error(4,line,col,lastchar,current);  //'}' ,ERROR CODE = 4
       if(current=='\n') error(5,line,col,lastchar,current); //'\n',ERROR CODE = 5
       }
  else if(lastchar=='{'){                                  //AN O PROIGOUMENOS EINAI '{' KAI EPOMENOS..
       if(current==',')  error(4,line,col,lastchar,current); //',' ,ERROR CODE = 4
       }
  else if(lastchar=='}'){                                  //AN O PROIGOUMENOS EINAI '}' KAI EPOMENOS..
       if(current=='{')  error(6,line,col,lastchar,current);   //'{' ,ERROR CODE = 6
       if(current=='+')  error(6,line,col,lastchar,current);  //'+' ,ERROR CODE = 6
       if(current=='-')  error(6,line,col,lastchar,current); //'-' ,ERROR CODE = 6
       if(current>='0' && current<='9') error(6,line,col,lastchar,current);
       }
  else if(lastchar=='+'){                                  //AN O PROIGOUMENOS EINAI '+' KAI EPOMENOS..
       if(current=='{')  error(4,line,col,lastchar,current);        //'{' , ERROR CODE = 4             
       if(current=='}')  error(4,line,col,lastchar,current);       //'}' , ERROR CODE = 4
       if(current=='+')  error(8,line,col,lastchar,current);      //'+' , ERROR CODE = 8
       if(current=='-')  error(8,line,col,lastchar,current);     //'-' , ERROR CODE = 8
       if(current==',')  error(4,line,col,lastchar,current);    //',' , ERROR CODE = 4
       if(current==' ')  error(7,line,col,lastchar,current);   //' ' , ERROR CODE = 7
       if(current=='\t') error(7,line,col,lastchar,current);  //'\t', ERROR CODE = 7
       if(current=='\n') error(7,line,col,lastchar,current); //'\n', ERROR CODE = 7
       }
  else if(lastchar=='-'){                                 //AN O PROIGOUMENOS EINAI '-' KAI EPOMENOS..  
       if(current=='{')  error(4,line,col,lastchar,current);        //'{' , ERROR CODE = 4
       if(current=='}')  error(4,line,col,lastchar,current);       //'}' , ERROR CODE = 4
       if(current=='+')  error(8,line,col,lastchar,current);      //'+' , ERROR CODE = 8
       if(current=='-')  error(8,line,col,lastchar,current);     //'-' , ERROR CODE = 8
       if(current==',')  error(4,line,col,lastchar,current);    //',' , ERROR CODE = 4            
       if(current==' ')  error(7,line,col,lastchar,current);   //' ' , ERROR CODE = 7
       if(current=='\t') error(7,line,col,lastchar,current);  //'\t', ERROR CODE = 7
       if(current=='\n') error(7,line,col,lastchar,current); //'\n', ERROR CODE = 7
       }
  else if(lastchar>='0' && lastchar<='9'){               //AN O PROIGOUMENOS EINAI '0-9' KAI EPOMENOS..
       if(current=='{')  error(6,line,col,lastchar,current);   //'{' , ERROR CODE = 6
       if(current=='+')  error(6,line,col,lastchar,current);  //'+' , ERROR CODE = 6
       if(current=='-')  error(6,line,col,lastchar,current); //'-' , ERROR CODE = 6
       if(space>0 && (current>='0' && current<='9')) error(6,line,col,lastchar,current);
       }

              if(current==' ' || current=='\t')           //AN O TREXON EINAI KENO H TAB TOTE..
               space++;                                  //KATAMETRISI KENWN - TAB
                else                                    //AN current!=' ' && current!='\t' TOTE..
                 space=0;                              //MIDENISMOS space
    //EKXORISI TOU TREXON XARAKTIRA STH METABLITI lastchar GIA XRISI STIN EPOMENH STILI (AN YPARXEI)
    if(current!='\n' && current!=32 && current!='\t') lastchar=current; 
                                       
   if(current=='\n'){         //AN O TREXON XARAKTIRAS EINAI O '\n' (DILADI EXEI PATITHEI ENTER) TOTE..
   if(L!=R){                                //AN OI AGILES DEN EINAI ISES TOTE PERISSEYEI AGILI..
    if(L>R)                                //AN PERISSEYEI H ARISTERH TOTE..
    error(3,line,col,lastchar,current);   //ERROR CODE = 3
    else                                 //AN PERISSEYEI H DEXIA TOTE..
    error(2,line,col,lastchar,current); //ERROR CODE = 2
   }
       //AN DEN YPARXOYN LATHI TOTE.. EKTYPWSH APOTELESMATWN
       if(errors==0) printf("depth = %d\tsets = %d\tintegers = %d\n",depth,sets,integers);
              col=0;                          
            space=0;           
           errors=0;                    //PROETIMASIA - ARXIKOPOIISI    
                L=0;                   //METABLITWN GIA EPOMENH GRAMMI
                R=0;                  //(AN YPARXEI..)
         lastchar=0;
             flag=0;    
            depth=0;
             sets=0;
         integers=0;
             line++;             //KATAMETRISI TREXOUSAS GRAMMIS.
    }                           //if(current=='\n')
  }                            //while(current!=EOF)
}                             //int main(void)
