/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "flash.h"
#include "i2c-lcd.h"
#include "stm32f1_rc522.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#define DS3231_ADDRESS 0xD0
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//Khai bao chan cua keypad
#define C1_PORT GPIOA
#define C1_PIN GPIO_PIN_8

#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_9

#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_10

#define C4_PORT GPIOA
#define C4_PIN GPIO_PIN_11

#define R1_PORT GPIOB
#define R1_PIN GPIO_PIN_12

#define R2_PORT GPIOB
#define R2_PIN GPIO_PIN_13

#define R3_PORT GPIOB
#define R3_PIN GPIO_PIN_14

#define R4_PORT GPIOB
#define R4_PIN GPIO_PIN_15
/* USER CODE END Includes */
#define maxdigit 10
uint8_t key_val,mathe[30];
static unsigned char index=0;
char dem=0,dem2=0,sophantu=0,m=0,moi=0,dem1=0,demmk=0;
char mp[10],mp1[10],mpxn[10],password[11]="",data[20],chedoxoathe=0,chedoxoatatca=0,mocua1=0;
char saithe=0,chedodoimk=0,chedodoixn=0,chedochonmemu=0,menu=0, smk=0,chedothemthe=0;
uint8_t  serNum[5],mastercard[5],str[MAX_LEN],themthe[5],status,kiemtrathe=0,ktmaster=0,demapp=0,mode=0;
char demmas=0,demchua=0,demco=0;
int coi=0;	
#define ADDRESS_DATA_STORAGE  (0x08000000+ 120*1024)// mat khau
#define ADDRESS_DATA_STORAGE1  (0x08000000+ 121*1024)// master
#define ADDRESS_DATA_STORAGE2  (0x08000000+ 122*1024)// them the



I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

//KeyPad
uint8_t key_val;
uint8_t  keypad_get_key_value(void)
{    
	 int  key;
	 key =' ';
      HAL_GPIO_WritePin(GPIOB,R1_PIN,GPIO_PIN_RESET);
			HAL_Delay(10);
      if(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0) {
				while(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0);
				key= '1';
			}
      if(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0){
				while(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0);
				key= '2';
			}
      if(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0){
				while(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0);
				key= '3';
			}
      if(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0) {
				while(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0);
				key= 'A';
			}
      HAL_GPIO_WritePin(GPIOB,R1_PIN,GPIO_PIN_SET);
      
			HAL_GPIO_WritePin(GPIOB,R2_PIN,GPIO_PIN_RESET);
			HAL_Delay(10);
      if(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0) {
				while(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0);
				key= '4'; 
			}
      if(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0){ 
				while(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0);
				 key= '5';
			 }
      if(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0) {
				while(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0);
				 key= '6';
			 }
      if(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0) {
				while(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0);
				 key= 'B';
			}
      HAL_GPIO_WritePin(GPIOB,R2_PIN,GPIO_PIN_SET);
		
 			HAL_GPIO_WritePin(GPIOB,R3_PIN,GPIO_PIN_RESET);
			HAL_Delay(10);
      if(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0) {
				while(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0);
				key= '7'; 
			}
      if(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0) {
				while(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0);
				 key='8';
			}
      if(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0) {
				while(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0);
				 key='9';
			}
      if(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0) {
				while(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0);
				 key='C';
			}
      HAL_GPIO_WritePin(GPIOB,R3_PIN,GPIO_PIN_SET);
	
 			HAL_GPIO_WritePin(GPIOB,R4_PIN,GPIO_PIN_RESET);
			HAL_Delay(10);
      if(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0) {
				while(HAL_GPIO_ReadPin(C1_PORT,C1_PIN)==0);
				key='*'; 
			}
      if(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0){ 
				while(HAL_GPIO_ReadPin(C2_PORT,C2_PIN)==0);
				 key= '0';
			}
      if(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0) {
				while(HAL_GPIO_ReadPin(C3_PORT,C3_PIN)==0);
				 key='#';
			}
      if(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0) {
				while(HAL_GPIO_ReadPin(C4_PORT,C4_PIN)==0);
				 key= 'D';
			}
      HAL_GPIO_WritePin(GPIOB,R4_PIN,GPIO_PIN_SET);
      
			return  key;
			
}

//RFID
void sosanhthe(uint8_t keycard[],  uint8_t id_moi[],  uint8_t mastercard[],char sophantu){ 
   if(sophantu==0){	 
		 if(id_moi[0] == mastercard[0] && id_moi[1] == mastercard[1] && id_moi[2] == mastercard[2] && id_moi[3] == mastercard[3]&& id_moi[4] == mastercard[4]){      
			demmas=1;
		 }			
			else{
			demchua=1;}    
	 }
	 else{
   while(m < sophantu) {    
        moi = m + 5;     
      if(id_moi[0] == mastercard[0] && id_moi[1] == mastercard[1] &&id_moi[2] == mastercard[2] && id_moi[3] == mastercard[3]&& id_moi[4] == mastercard[4])  {    
        demchua=0; demco=0; demmas=1; break; 
			}    
     else if(id_moi[0] == keycard[m] && id_moi[1] == keycard[m+1] && id_moi[2] == keycard[m+2] && id_moi[3] == keycard[m+3]&& id_moi[4] == keycard[m+4])  {     
        demchua=0; demco=1; demmas=0;  break; 
		 }      
     else  if(id_moi[0] != keycard[m] || id_moi[1] != keycard[m+1] || id_moi[2] != keycard[m+2] || id_moi[3] != keycard[m+3] || id_moi[4] != keycard[m+4]) {       
        demchua=1; demco=0; demmas=0;  
		 }		      
      m = moi;
    }
	}
}
void xoathe(uint8_t a[], char *n, char viTriXoa,char soLuongXoa){
    for(char i = viTriXoa; i < *n - soLuongXoa; ++i)
        a[i] = a[i+soLuongXoa];
     *n -= soLuongXoa;
}
void nhapmk (char arr[]){
   if(index < maxdigit){		 
        arr[index] = key_val;
		    index++;
		    HAL_Delay(100);			  
				lcd_put_cur (1,5);
	      lcd_send_string(arr) ;									
		  }
}
void xoamk (char arr[]){
   if(index>0){	  
	    index--;
	    arr[index]= '\0';
	    HAL_Delay(100);			
			lcd_put_cur (1,5);
	    lcd_send_string(arr) ;
	  }
}


void xoachuoi (char arr[]){
for(int i=0;i<11;i++){	
	strcpy(&arr[i],"");
	index=0;
	}
}
 uint8_t CheckPass(char *Str1, char *Str2){
	int sosanh;
	if(strlen(Str1)==strlen(Str2)){	
		sosanh=strcmp(Str1,Str2);
		if(sosanh==0) return 1;
		else return 0;
	}
	else return 0;
}
void mocua(){
		mocua1=1;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);  
		HAL_Delay(200);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,1);
	  saithe=0;smk=0;
}
void ktra_nut(){
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0){
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0);
		if(mocua1==1){
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
			HAL_Delay(200);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,0);
			mocua1=0;
		}
		else{
			mocua();
		}
	}
}
void start(){
	

	lcd_put_cur (0,0);
	sprintf(data," Moi quet the      ");
	lcd_send_string (data );
	lcd_put_cur (1,0);
	lcd_send_string("                      ");
	xoachuoi(mp);xoachuoi(mp1);xoachuoi(mpxn);
	demchua=0; demco=0; m=0;moi=0,dem2=0,dem=0,demmas=0,mode=0;
	chedodoimk=0;chedodoixn=0;chedothemthe=0;chedoxoatatca=0;chedoxoathe=0,coi=0;	
	ktra_nut();
	
	dem1=Flash_Read_Int(ADDRESS_DATA_STORAGE);
	Flash_Read_Array(ADDRESS_DATA_STORAGE+2,(uint8_t *)password,dem1);
	sophantu=Flash_Read_Int(ADDRESS_DATA_STORAGE2);	
	Flash_Read_Array(ADDRESS_DATA_STORAGE2+2,(uint8_t *)mathe,sophantu);
}

	int temp=0;



void Menu(){
	
	dem=0;
	dem2=0;
	lcd_put_cur (0,0);
	 lcd_send_string("C:Man hinh chinh         ") ;
	 lcd_put_cur (1,0);
	 lcd_send_string("A:Menu                 ") ;	
	temp=1;
	while(temp==1){
		ktra_nut();
		key_val=keypad_get_key_value ();
		if(key_val!= 0x20 && key_val=='A'){
			lcd_clear();
			dem++;
			HAL_Delay(100);
		}
		if(key_val!= 0x20 && key_val=='C'){
			temp=0;
			HAL_Delay(500);
			lcd_clear();
		}
		
		if(dem==1){
			//lcd_clear();
			lcd_put_cur(0,0);
			lcd_send_string("->THEM THE      ");
			lcd_put_cur(1,0);
			lcd_send_string("XOA THE BAT KI      ");
			if (key_val!= 0x20 && key_val=='B'){
				lcd_clear();
				dem2=1;
			}
			while(dem2==1){
				key_val=keypad_get_key_value ();
				//lcd_clear();
				lcd_put_cur(0,0);
				lcd_send_string("THEM THE MOI       ");
				lcd_put_cur(1,0);
				lcd_send_string("MOI NHAP THE....");
				chedothemthe=1;
				
				if(chedothemthe==1){	
						if(key_val=='C'){
							dem2=0;
							chedothemthe=0;
							HAL_Delay(100);
							lcd_clear();
						}					
							 sophantu=Flash_Read_Int(ADDRESS_DATA_STORAGE2);         					      			
							 m=0;moi=0;					
							 if(MFRC522_Request(PICC_REQIDL , str)==MI_OK) {	       
								if(MFRC522_Anticoll(str)==MI_OK) {          
									memcpy(themthe, str, 5);						                      
									sosanhthe(mathe,  themthe,  mastercard, sophantu);
									if(demmas==1&&demchua==0){							
									 lcd_clear();
									 lcd_put_cur (0,0);
									 lcd_send_string("The da ton tai    ") ;
									 HAL_Delay(1000);
										dem2=0;
									}
									if(demco==1 && demchua==0){
										lcd_clear();
										lcd_put_cur (0,0);
										lcd_send_string(" The da ton tai    ") ;
										HAL_Delay(1000);
										dem2=0;
									}
									 if (demchua==1) {            
										memcpy(&mathe[sophantu],themthe,5);
										lcd_put_cur (0,0);
										lcd_send_string ("Them thanh cong!       ");
										lcd_put_cur (1,0);
										lcd_send_string ("                        ");
										HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
										HAL_Delay(100);
										HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
										HAL_Delay(500);
										sophantu=sophantu+5;
										Flash_Erase(ADDRESS_DATA_STORAGE2);
										HAL_Delay(100);
										Flash_Write_Array(ADDRESS_DATA_STORAGE2+2,(uint8_t*)mathe,sophantu);
										HAL_Delay(100);
										Flash_Write_Int(ADDRESS_DATA_STORAGE2,sophantu);
										HAL_Delay(100);
										lcd_clear();
										dem2=0;	
										demchua=0;
									}		
							}							 
						}			
				}
			}
		}
		else if(dem==2){
			
			lcd_put_cur(0,0);
			lcd_send_string("THEM THE      ");
			lcd_put_cur(1,0);
			lcd_send_string("->XOA THE BAT KI    ");
			if (key_val!= 0x20 && key_val=='B'){
				lcd_clear();
				dem2=2;
			}
			while(dem2==2){
				key_val=keypad_get_key_value ();
				lcd_put_cur(0,0);
         lcd_send_string("XOA THE BAT KY   ");
         lcd_put_cur(1,0);
         lcd_send_string("MOI NHAP THE....  ");                
         chedoxoathe=1;		
				if(chedoxoathe==1){	
					if(key_val=='C'){
						dem2=0;
						chedoxoathe=0;
						HAL_Delay(100);
						lcd_clear();
					}					
		     sophantu=Flash_Read_Int(ADDRESS_DATA_STORAGE2);         					 		     	
           m=0;moi=0;
				   if(sophantu==0) {				
						 HAL_Delay(1000);
						 lcd_clear();
						 lcd_put_cur(0,0);
						 lcd_send_string("  KHONG CO THE   ");
						 HAL_Delay(2000);
						 dem2=0;
						}
           if(sophantu>0){					 						 
						 if(MFRC522_Request(PICC_REQIDL , str)==MI_OK){		        
							if(MFRC522_Anticoll(str)==MI_OK) {           
								memcpy(themthe, str, 5);						                      
								sosanhthe(mathe,  themthe,  mastercard, sophantu);
								if(demchua==1 ){							
									 lcd_clear();
									 lcd_put_cur(0,0);
									 lcd_send_string("The chua co");
									 lcd_put_cur(1,1);
									 lcd_send_string("Xoa that bai");
									 HAL_Delay(1000);
									 dem2=0;
								}								
								else if (demco==1){	              														
									xoathe(mathe,&sophantu , m,5);
									lcd_clear();
									lcd_put_cur (1,1);
									lcd_send_string ("Xoa thanh cong");
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
									HAL_Delay(100);
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
									HAL_Delay(1000);								
									Flash_Erase(ADDRESS_DATA_STORAGE2);
									HAL_Delay(100);
									Flash_Write_Array(ADDRESS_DATA_STORAGE2+2,(uint8_t*)mathe,sophantu);
									HAL_Delay(100);
									Flash_Write_Int(ADDRESS_DATA_STORAGE2,sophantu);
									HAL_Delay(100);              
									dem2=0;							
								}	
							}							 
					 }
					}
				}	
			}
		}
//THAY DOI MAT KHAU
		else if(dem==3){
			lcd_put_cur(0,0);
			lcd_send_string("->DOI MAT KHAU      ");
			lcd_put_cur(1,0);
			lcd_send_string("                      ");
			if (key_val!= 0x20 && key_val=='B'){
				lcd_clear();
				dem2=3;
			}
			while(dem2==3){
				key_val=keypad_get_key_value ();
				chedodoimk=1;  
				if(chedodoimk==1){
				 	if(key_val=='C'){
						dem2=0;
						chedodoimk=0;
						xoachuoi(mpxn);
						HAL_Delay(100);
						lcd_clear();
					}					

						//lcd_clear();
						lcd_put_cur(0,0);
						lcd_send_string("Nhap key moi      ");
						lcd_put_cur(1,1);
						lcd_send_string("Key:");						                    	 
						if (key_val >= '0' && key_val<= '9' && chedodoimk==1 ){           							 
								nhapmk(mpxn);}           	
					 else if (key_val=='*' && chedodoimk==1) {	            
						xoachuoi(mpxn); 
						lcd_clear(); }               
					 else if (key_val=='D' && chedodoimk==1 ){           							           								 
						Flash_Erase(ADDRESS_DATA_STORAGE);
						lcd_put_cur(0,0);
						lcd_send_string("   Thanh cong         ");
						lcd_put_cur(1,0);
						lcd_send_string("                         ");
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
						HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
						demmk=strlen(mpxn);
						Flash_Write_Int(ADDRESS_DATA_STORAGE,demmk);
						Flash_Write_Array(ADDRESS_DATA_STORAGE+2,(uint8_t*)mpxn,demmk);
						HAL_Delay(1000);
						xoachuoi(mpxn);
						xoachuoi(password);
						HAL_Delay(100);
						 dem2=0;
					  }	
					 
				 }
			}
		}
		if(dem>3) dem=1;
	}
		
}




int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
	lcd_init();
	MFRC522_Init();
	Flash_Read_Array(ADDRESS_DATA_STORAGE1,(uint8_t*) mastercard,5);


start();

  while (1)
  {
		key_val=keypad_get_key_value ();

		if (key_val!= 0x20 && key_val=='*'){
			mode=1;
		}
		while (mode==1){
			key_val=keypad_get_key_value ();
			if (key_val=='C'){
				mode=0;
			}
			lcd_put_cur (0,0);
			lcd_send_string("Nhap mat khau     ") ;
			lcd_put_cur(1,1);
			lcd_send_string("Key:");
			
			if (key_val >= '0' && key_val<= '9'){ 				               						 
				nhapmk(mp);
			}	
			else if (key_val=='*' ) {			  
				xoachuoi(mp); 
				lcd_clear();
				lcd_put_cur (0,0);
				lcd_send_string("Nhap mat khau     ") ;
				lcd_put_cur(1,1);
				lcd_send_string("Key:");
			} 
			else if  (key_val=='D' ) {				  
				if(CheckPass(mp,password)==1)	{					
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string(" Mat khau dung");				
					lcd_put_cur(1,1);
					lcd_send_string("                ");	 
					xoachuoi(mp);
					mocua();

					HAL_Delay(2000);
					Menu();
					start();
				}
				else{
					lcd_clear();
					lcd_put_cur (0,1);
					lcd_send_string("mat khau sai") ;
					lcd_put_cur(1,0);
					lcd_send_string("                ");
					xoachuoi(mp);
					smk++;
					HAL_Delay(1500);
					lcd_clear();
					lcd_put_cur(0,0);
					lcd_send_string("Nhap mat khau") ;
					lcd_put_cur (1,1);
					sprintf(data,"Key:") ;
					lcd_send_string(data);								
				}		
		 }
				if (smk==3){
					
					lcd_put_cur (0,0);
					lcd_send_string("Sai qua 3 lan"    );
					lcd_put_cur(1,0);
					lcd_send_string("                ");
					int time =10;
					
					while(coi<4){
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
						 HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
						 HAL_Delay(100);
						 coi++;
					}
					while(time>=0){
						lcd_put_cur (1,0);
						sprintf(data,"Doi: %d giay       ",time) ;
						lcd_send_string(data);  
						HAL_Delay(1000);
						time--;
					}
					 start();
				}
			}

			start();		
			if(MFRC522_Request(PICC_REQIDL , str)==MI_OK){
				if(MFRC522_Anticoll(str)==MI_OK){		
					HAL_Delay(500);
					 memcpy(serNum, str, 5);
					 sosanhthe(mathe,serNum,mastercard,sophantu);
				}
				if(demmas==1){						
					 HAL_Delay(100);
					 lcd_clear();
					 lcd_put_cur (0,0);
					 lcd_send_string("The Master");
						
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
						HAL_Delay(200);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,1);
						saithe=0;smk=0;
						mocua();
					 HAL_Delay(2000);
					 lcd_clear();
						Menu();
						start();		
				}
				if(demco==1){		
					 HAL_Delay(100);
					 lcd_clear();
					 lcd_put_cur (0,0);
					 lcd_send_string("  The Dung!         ");
						lcd_put_cur (1,0);
					 lcd_send_string("                       ");
					 mocua();
					while(mocua1==1){
						lcd_put_cur (0,0);
					 lcd_send_string("  The Dung!         ");
						lcd_put_cur (1,0);
					 lcd_send_string("Cua Da Mo         ");
						ktra_nut();
					}
					lcd_clear();
					start();					
				}
				if(demchua==1){		
					mocua1=10;
				 lcd_clear();
				 lcd_put_cur (0,0);
				 lcd_send_string("  The sai  ") ;		
				 lcd_put_cur (1,1);
				 lcd_send_string("Quet lai the  ") ;
				 saithe=saithe+1;
				 HAL_Delay(1000);
				 if(saithe>3 ){
					 int time=10;							 
					 lcd_clear();
					 lcd_put_cur (0,1);		 
					 lcd_send_string("Sai qua 3 lan    "  ) ;
					 while(coi<4){
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,1);
						 HAL_Delay(100);
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,0);
						 HAL_Delay(100);
						 coi++;
						}
					 while(time>=0){
						lcd_put_cur(1,1);	
						sprintf(data,"Doi: %d giay    ",time);
						lcd_send_string(data) ;	
						HAL_Delay(1000);
						time--;								 
					 }
				saithe=0;							 
				}
				 start();
			 }
			}

				
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 64;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2499;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 PB13 PB14
                           PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
