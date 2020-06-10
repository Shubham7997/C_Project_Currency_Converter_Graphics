#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<windows.h>
#include<string.h>
	// CURRENCY CONVERTER => C Mini-Project
	// BY
	// SHUBHAM NANDI
	// MCA-I(M)        ROLL NO.: 36

//ALL FUNCTIONS DECLARATION	
void fn_update_screen_one_2_many(char *str , char *curr);
void fn_update_screen_one_2_one(char *curr1 , char *curr2, char *str);
int curr_to_curr(int cur_from , int cur_to , float amt , int xpos , int ypos);
void fn_one_2_one();
void fn_one_2_many();
void fn_headings_screen();

//ALL GLOBAL Initialisation
char options[9][4] = {"INR","USD","EUR","JPY","GBP","KWD","CHF","AUD","CNY"};
char mesg_print[9][30] = {
	"In Indian Rupees (INR):",
	"In US Dollars (USD):",
	"In Euros (EUR):",
	"In Japenese Yen (JPY):",
	"In British Pound (GBP):",
	"In Kuwait Dinar (KWD):",
	"In Swiss Franc (CHF):",
	"In Austrailian Dollars (AUD):",
	"In Chinese Yuan (CNY):"
};
char value_print[9][20];
FILE *fptr;

//MAIN FUNCTION for the program
int main(){
		//Initialisation
		int x = 0 , y = 0;
		static int one_time_loading = 0;
	
		//Dimension of the Screen
		if(one_time_loading == 0){
			initwindow(550,550,"MAIN");
			one_time_loading++;
		}
		fn_headings_screen();
		
		//USER INPUT CHOICE
		settextstyle(10,HORIZ_DIR, 1);
		setbkcolor(11);
		setcolor(9);
		outtextxy(10,150,"SELECT THE CONVERSION TO PERFORM:");
	
		//CHOICE 1: 1 to 1
		setfillstyle(SOLID_FILL,3);
		bar(100,200,270,240);
		outtextxy(110,210,"ONE TO ONE  >>");
	
		//CHOICE 2: 1 to Many
		setfillstyle(SOLID_FILL,9);
		bar(100,260,270,300);
		outtextxy(110,270,"ONE TO MANY >>");
		
		//QUIT THE APPLICATION 
		settextstyle(10,HORIZ_DIR, 3);
		outtextxy(150,400,"QUIT");
		
		//Check for mouse click and wait untill click occurs
		while(!ismouseclick(WM_LBUTTONDOWN)){
			delay(10);
		}
		getmouseclick(WM_LBUTTONDOWN,x, y);
	
		//CHOICE TO ONE 2 ONE OPTION
		if(x >= 100 && x < 270 && y >= 200 && y < 240){
			cleardevice();
			fn_one_2_one();
		}
		//CHOICE TO ONE 2 MANY OPTION
		else if(x >= 100 && x < 270 && y >= 260 && y < 300){
			cleardevice();
			fn_one_2_many();
		}
		//CHOICE TO QUIT OPTION
		else if (x >= 150 && x < 200 && y >= 400 && y < 420){
			MessageBox(NULL , "Hope You Enjoy This App by Shubham Nandi","BYE! BYE!",MB_OK);
			exit (0);
		}	
		//CLICK ON no recognised button area	
		else{
			cleardevice();
			main();  //recurse main fn
		}
	return 0;
}

void fn_headings_screen(){   //Function having headings to be displayed in program.
	setbkcolor(7);
	cleardevice();
	
	//HEADING FORMATTING
	setfillstyle(INTERLEAVE_FILL,12);
	bar(85,20,370,70);
	settextstyle(10,HORIZ_DIR, 3);
	setbkcolor(15);
	setcolor(8);
	outtextxy(100,30,"CURRENCY CONVERTER");
	
	//THE DEVELOPER INFO
	setfillstyle(CLOSE_DOT_FILL,3);
	bar(90,80,375,122);
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(3);
	setcolor(12);
	outtextxy(100,80, "Project By SHUBHAM NANDI");
	outtextxy(100,100, "Roll No. 36     MCA-1(M)");		
}

//Function to manipulate one currency to many option Screen ( Gives just recursive UI to ONE TO MANY Window screen )
void fn_update_screen_one_2_many(char *str , char * curr){
	fn_headings_screen();
	
	//BACK TO MAIN
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(15);
	setcolor(12);
	outtextxy(0,5,"<< BACK");
	
	//USER INPUT FORMATTING
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(11);
	setcolor(9);
	outtextxy(10,150,"ENTER THE AMOUNT IN ");
	
	//TAKE USER INPUT FOR CURRENCY
	setfillstyle(SOLID_FILL,15);
	bar(240,150,290,172);
	settextstyle(10,HORIZ_DIR, 1);
	setcolor(9);
	outtextxy(240,150,curr);
	
	//TAKE USER INPUT
	setfillstyle(SOLID_FILL,15);
	bar(350,150,450,172);
	settextstyle(10,HORIZ_DIR, 1);
	setcolor(9);
	outtextxy(350,150,str);
	
	//PRINT OUTPUT BUTTON
	settextstyle(10,HORIZ_DIR, 3);
	setbkcolor(10);
	setcolor(2);
	outtextxy(150,500,"PRINT OUTPUT");
}

//Function to do the real calculation in back end for ONE TO MANY Screen.
void fn_one_2_many(){

		//INITIALISATION
		float val = 0;
		int x = 0, y = 0 , i = 0 , j = 0, dot_count = 0 , height = 0 , dot_pos = 0;
		char str[20] = {0} ,ch;
		
		static char *curr = options[0];
		static int p = 0;
	
		//At start gives screen the UI
		fn_update_screen_one_2_many(str,curr);
		
		//While no input from keyboard is given and if so it will flush and this fn recurse again to this point.
		while(!kbhit()){
			//If no keyboard then take mouse position
			getmouseclick(WM_LBUTTONDOWN,x, y);
			
			//BACK TO MAIN option is clicked
			if(x >= 0 && x < 80 && y >= 5 && y < 25){
				cleardevice();
				main();
			}
			//CHOOSE CURRENCY option is clicked
			else if (x >= 240 && x < 290 && y >= 150 && y < 172){
				int nxt = 0;
				//on click display the dropdown
				for( j = 0 ; j < 9 ; j++){
					setfillstyle(SOLID_FILL,8);
					bar(240,150+nxt,290,172+nxt);
					setcolor(15);
					setbkcolor(8);
					outtextxy(240,150+nxt,options[j]);
					nxt = nxt + 22;
				}
				//after displaying drop down wait for mouse to choose from one of them 
				while(!ismouseclick(WM_LBUTTONDOWN)){
					delay(10);
				}	
				//get mouse click
				getmouseclick(WM_LBUTTONDOWN,x,y);
				nxt = 0;
				//check for each option through loop
				for( j = 0 ; j < 9; j++){
					//if it find the option mouse clicked
					if(x >= 240 && x < 290 && y >= 150 + nxt && y < 172 + nxt){
						curr = options[j];
						p = j;
						//one currency set to this and then display the entire screen again with selected option and break from loop
						cleardevice();
						fn_update_screen_one_2_many(str, curr);
						break;
					}
					nxt = nxt + 22;
				}
			}
			//INPUT TAKING in input box 
			else if(x >= 350 && x < 450 && y >= 150 && y < 170){
				while((ch = getch() )!= '\r'){
						
						switch(ch){
							//if entered is number
							case '0' ... '9' :
								str[i] = ch;
								i++;
								fn_update_screen_one_2_many(str,curr);
								break;
							//if entered is dot check for occurrence
							case '.':
								if(dot_count == 0){
									str[i] = ch;
									dot_pos = i;
									i++;
									fn_update_screen_one_2_many(str,curr);
									dot_count++;
								}
								else{
									MessageBox(NULL,"!!! More than One Decimal \n->Please Enter a valid Number","(!) WARNING",MB_OK);
								}
								break;
							//if entered wipe last entry in array
							case '\b':
								i--;
								str[i] = 0;
								fn_update_screen_one_2_many(str,curr);
								if(i == dot_pos){
									dot_count--;
								}
								break;
							//default to all other than numbers entry
							default:
								MessageBox(NULL,"!!! NOT A NUMBER \n->Please Enter a valid Number","(!) WARNING",MB_OK);
								break;
						}
				}
				//when ENTER clicked get out of loop and calculate result
				val = atof(str);
				setcolor(9);
				height = 0;
				for(j = 0 ; j < 9 ; j++){
					//fn to calculate and display output
					curr_to_curr( p , j , val , 20 , 200 + height);
					height = height + 30;
				}
				//Now after output display wait for keyboard hit and check for mouse for print output button
				while(!kbhit()){		
					getmouseclick(WM_LBUTTONDOWN,x, y);
					//print button region
					if(x >= 150 && x < 310 && y >= 500 && y < 530){
						char file_name[10] = {0};
						strcat(file_name,options[p]);
						strcat(file_name,"_To_All.txt");
						fptr = fopen(file_name,"a+");
						if(fptr != NULL){		
							fprintf(fptr,"%s : %s To All:\n",options[p],value_print[p]);
							for(j = 0; j < 9 ; j++){
								fprintf(fptr,"\t%s\t%s\n",mesg_print[j],value_print[j]);
								}
								fprintf(fptr,"\n");
								fclose(fptr);
								MessageBox(NULL,"File is saved \n->Check the file in this project's folder","(::) DONE",MB_OK);
							}
							else{
								MessageBox(NULL,"File is not saved \n->Error overwriting/creating file","(::) Error",MB_OK);
							}	
						}
						//if clicked on other than print region , just wait in loop unitll keyboard hit
					else{
						delay(10);
					}
				}
			}
			//if clicked on other than above mentioned region , just wait in loop unitll keyboard hit
			else{
				delay(10);
			}	
		}
		getch();
		fn_one_2_many();  //Recurse the fn
}

//Fn ONE TO ONE SCREEN UI
void fn_update_screen_one_2_one(char *curr1 , char *curr2 , char *str){
	fn_headings_screen();
	
	//BACK TO MAIN
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(15);
	setcolor(12);
	outtextxy(0,5,"<< BACK");
	
	//CURRENCY 1 FROM
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(11);
	setcolor(9);
	outtextxy(30,150,"FROM:");
	
	//TAKE USER INPUT FOR CURRENCY 1
	setfillstyle(SOLID_FILL,15);
	bar(100,150,150,172);
	settextstyle(10,HORIZ_DIR, 1);
	setcolor(9);
	outtextxy(100,150,curr1);
	
	//CURRENCY 1 TO
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(11);
	setcolor(9);
	outtextxy(300,150,"TO:");
	
	//TAKE USER INPUT FOR CURRENCY 2
	setfillstyle(SOLID_FILL,15);
	bar(350,150,400,172);
	settextstyle(10,HORIZ_DIR, 1);
	setcolor(9);
	outtextxy(350,150,curr2);
	
	//ENTER THE AMOUNT Message
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(11);
	setcolor(9);
	outtextxy(10,250,"ENTER THE AMOUNT:");
	
	//TAKE USER INPUT
	setfillstyle(SOLID_FILL,15);
	bar(250,250,450,272);
	settextstyle(10,HORIZ_DIR, 1);
	setcolor(9);
	outtextxy(250,250,str);
	
	//PRINT OUTPUT BUTTON
	settextstyle(10,HORIZ_DIR, 3);
	setbkcolor(10);
	setcolor(2);
	outtextxy(150,500,"PRINT OUTPUT");
}
void fn_one_2_one(){
		//INITIALISATION
		float val = 0;
		int x = 0, y = 0 , i = 0 , j = 0, dot_count = 0 , dot_pos = 0;
		
		char str[20] = {0} , ch;
		
		static char *curr1 = options[0] , *curr2 = options[1];
		static int m = 0 , n = 1;
		
		fn_update_screen_one_2_one(curr1,curr2 , str);
		
		while(!kbhit()){
			getmouseclick(WM_LBUTTONDOWN,x, y);
			
			if(x >= 0 && x < 80 && y >= 5 && y < 25){
				cleardevice();
				main();
			}
			//CHOOSE CURRENCY 1
			else if (x >= 100 && x < 150 && y >= 150 && y < 172){
				int nxt = 0;
				for( j = 0 ; j < 9 ; j++){
					setfillstyle(SOLID_FILL,8);
					bar(100,150+nxt,150,172+nxt);
					setcolor(15);
					setbkcolor(8);
					outtextxy(100,150+nxt,options[j]);
					nxt = nxt + 22;
				}
				
				while(!ismouseclick(WM_LBUTTONDOWN)){
					delay(10);
				}	
				getmouseclick(WM_LBUTTONDOWN,x, y);
				nxt = 0;
				for( j = 0 ; j < 9; j++){
					if(x >= 100 && x < 150 && y >= 150 + nxt && y < 172 + nxt){
						curr1 = options[j];
						m = j;
						cleardevice();
						fn_update_screen_one_2_one(curr1,curr2,str);
						break;
					}
					nxt = nxt + 22;
				}
			}
			//CHOOSE CURRENCY 2
			else if (x >= 350 && x < 400 && y >= 150 && y < 172){
				int nxt = 0;
				for( j = 0 ; j < 9 ; j++){
					setfillstyle(SOLID_FILL,8);
					bar(350,150+nxt,400,172+nxt);
					setcolor(15);
					setbkcolor(8);
					outtextxy(350,150+nxt,options[j]);
					nxt = nxt + 22;
				}
				
				while(!ismouseclick(WM_LBUTTONDOWN)){
					delay(10);
				}	
				getmouseclick(WM_LBUTTONDOWN,x, y);
				nxt = 0;
				for( j = 0 ; j < 9; j++){
					if(x >= 350 && x < 400 && y >= 150 + nxt && y < 172 + nxt){
						curr2 = options[j];
						n = j;
						cleardevice();
						fn_update_screen_one_2_one(curr1,curr2 , str);
						break;
					}
					nxt = nxt + 22;
				}
			}
			//TAKING INPUT
			else if(x >= 250 && x < 450 && y >= 250 && y < 272){
				while((ch  = getch()) != '\r'){
						switch(ch){
							case '0' ... '9' :
								str[i] = ch;
								i++;
								fn_update_screen_one_2_one(curr1,curr2,str);
								break;
							
							case '.':
								if(dot_count==0){
									str[i] = ch;
									dot_pos = i;
									i++;
									fn_update_screen_one_2_one(curr1,curr2 , str);
									dot_count++; 
								}
								else{
									MessageBox(NULL,"!!! More than one Decimal \n->Please Enter a valid Number","(!) WARNING",MB_OK);
								}
								break;
								
							case '\b':
								i--;
								str[i] = 0;
								fn_update_screen_one_2_one(curr1,curr2 , str);
								if(i == dot_pos){
									dot_count--;
								}
								break;
								
							default:
								MessageBox(NULL,"!!! NOT A NUMBER \n->Please Enter a valid Number","(!) WARNING",MB_OK);
								break;
						}
				}
				val = atof(str);
				curr_to_curr( m , m , val , 20, 300);
				curr_to_curr( m , n , val , 20, 350);
				
				//Print button procedure
				while(!kbhit()){
					getmouseclick(WM_LBUTTONDOWN,x, y);
					if(x >= 150 && x < 310 && y >= 500 && y < 530){
						char file_name[10] = {0};
						strcat(file_name,options[m]);
						strcat(file_name,"_To_");
						strcat(file_name,options[n]);
						strcat(file_name,".txt");
						fptr = fopen(file_name,"a+");
						if(fptr != NULL){
							fprintf(fptr,"%s : %s To %s:\n",options[m],value_print[m],options[n]);		
							fprintf(fptr,"\t%s\t%s\n",mesg_print[m],value_print[m]);
							fprintf(fptr,"\t%s\t%s\n\n",mesg_print[n],value_print[n]);	
							fclose(fptr);
							MessageBox(NULL,"File is saved \n->Check the file in this project's folder","(::) DONE",MB_OK);
						}else{
							MessageBox(NULL,"File is not saved \n->Error overwriting/creating file","(::) Error",MB_OK);
						}
					}
					else{
						delay(10);
					}
				}
			}
			else{
				delay(10);
			}
		}
		getch();
		fn_one_2_one();
}

//Fn for conversions of one currency to RS. and then to required currency
int curr_to_curr( int curr_from , int curr_to , float amt , int xpos , int ypos){
	float cn = 0 , cn_final = 0;
	char str[20];
	int width = 350;
	settextstyle(10,HORIZ_DIR, 1);
	setbkcolor(11);
	setcolor(2);
	
	//CONVERT TO RS CURRENCY first
	switch(curr_from){
		case 0:
			cn = amt;
			break;
		case 1:
			cn = amt*70.90;
			break;
		case 2: 
			cn = amt*77.80;
			break;	
		case 3: 
			cn = amt*0.66;
			break;
		case 4: 
			cn = amt*87.46;
			break;
		case 5: 
			cn = (amt*70.90)/3.29;
			break;	
		case 6: 
			cn = (amt*70.90)/1.04;
			break;
		case 7: 
			cn =(amt*70.90)/0.73;
			break;
		case 8: 
			cn = (amt*9.93);
			break;		
	}
	
	//then TO CURRENCY
	switch(curr_to){
		case 0:
			cn_final = cn;
			sprintf(str,"%.2f",cn_final);  
			strcpy(value_print[0],str);
			outtextxy(xpos,ypos,mesg_print[0]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 1:
			cn_final = cn/70.90;
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[1],str);
			outtextxy(xpos,ypos,mesg_print[1]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 2:
			cn_final = cn/77.80;
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[2],str);
			outtextxy(xpos,ypos,mesg_print[2]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 3:
			cn_final = cn/0.66;
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[3],str);
			outtextxy(xpos,ypos,mesg_print[3]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 4:
			cn_final = cn/87.46;
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[4],str);
			outtextxy(xpos,ypos,mesg_print[4]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 5:
			cn_final = 3.29*(cn/70.90);
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[5],str);
			outtextxy(xpos,ypos,mesg_print[5]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 6:
			cn_final =  1.04*(cn/70.90);
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[6],str);
			outtextxy(xpos,ypos,mesg_print[6]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 7:
			cn_final = 0.73*(cn/70.90);
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[7],str);
			outtextxy(xpos,ypos,mesg_print[7]);
			outtextxy(xpos+width,ypos, str);
			break;
		case 8:
			cn_final = (cn/9.93);
			sprintf(str,"%.2f",cn_final);
			strcpy(value_print[8],str);
			outtextxy(xpos,ypos,mesg_print[8]);
			outtextxy(xpos+width,ypos, str);
			break;
		default:
			break;
	}
	return 0;
}
