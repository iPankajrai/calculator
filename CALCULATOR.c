#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#define lcd PORTC
#include<ilibrary/lcd_library.h>
#include<ilibrary/keypad.h> 

unsigned long int no1, no2, set=0,set1=0,set2=0;
char op, x=0,y=0; 
float ans;

void main()
{ 
  DDRC=0xff;  //lcd
  lcd_init();        //initiating lcd
  DDRA= 0b11110000;  // input for keypad
  PORTA=0b00001111; //PULL UP 
  DDRD= 0b11111111;  // output row value  for keypad
  lcd_command(0x80);
   
  while(1)
  { 
     while(set==0)
	 { 
	    x= keypad_calc();
	    if(x=='+' | x=='-' | x== '*' | x=='/')
		{
		  op=x;
		  // lcd_data(x)  is removed, coz it caused two op signs
		  set++; 
        }
	
		else  
	    {
	     no1= (x-48) + (no1*10) ;
	    }
	    lcd_data(x);
		
     }

     while(set1==0)
	 {
		   y= keypad_calc();
		   
		    if(y=='=')
		   { 
		     lcd_data('=');
			 set1++;
			 
           }
		   else
		   {
		     no2= (y-48)+(no2*10);
		     lcd_data(y);
		   }
      }
       switch(op)
	   {  
	      case '+':ans= (no1+no2) ;
		           lcd_command(0xcf);
                   lcd_number_infinite(ans);
				     
		           break;
                   
	      case '-': if(no1 >= no2)
		            {
					ans= (no1-no2);
					lcd_command(0xcf);
                    lcd_number_infinite(ans);  
					}
					else
					{
					
					
					ans= (no2-no1);
				    lcd_command(0xcf);
                    lcd_number_infinite(ans); 
					lcd_data('-');
 
		            }
					break;

          case '*':ans= (no1*no2) ;
		           lcd_command(0xcf);
                   lcd_number_infinite(ans);  
                    break;
                    
	      case '/': if(no2== 0)
		            {
					lcd_command(0xc0);
			        lcd_string("oops!!!          ");
			        
					} 
					else
		            {
					ans= (no1/no2);
					lcd_command(0xcf);
                    lcd_number_infinite(ans);  
		            }
		            break;
		 
		     
       }
	   
      
   }
}


















/*
while(1)
  {
     while(set==0)
	 { 
	    x= keypad_calc();
		if(x=='+')
		{
		  op=x;
		  lcd_data(op);
		  set++;
		  goto level1;
        }
		no1= (x-48) + (no1*10) ;
		lcd_data(x);
     }
	 
  level1: while(set1==0)
		 {
		   y= keypad_calc();
		   if(y=='=')
		   {
		     
			 set1++;
			 goto level2 ;

           }
		  
		   no2= (y-48)+(no2*10);
		   lcd_data(y);
         }
     
  level2: lcd_command(0xc0);
          lcd_string("=");
          ans= (no1+no2) ;
         lcd_command(0xcf);
		 lcd_number_infinite(ans);
  }
}
*/
