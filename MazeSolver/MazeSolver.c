
/* Note:
To store data permanently, write it in EEPROM of atmega8
*/

#include <avr/io.h>

/* Global variables */
char maze[20][3];
/* First op, Second op, Suggested Correct Option */
int curJunction = 0;
char forcedDirn = 'n';
/* can be l,f,r or n for none */

void maze_init() {
	for(int i=0;i<20;i++) {
		for(int j=0;j<3;j++) 
			maze[i][j] = '#';
	}
}
void speed(int j) {
	if(j>100) j=100;
	if(j<0) j=0;
		PORTB = 0x0c;
			
		for(int i=0;i!=j;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
		}
		PORTB = 0x00;
		for(int k=0;k!=100-j;k++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); 
		}

}
void mvfwd() {
	speed(50);
}


void mvfwdpulse() {
	PORTB = 0x00;
	for(int i=0;i!=1000;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */	
		}
	PORTB = 0x0c;
	for(int i=0;i!=500;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */	
		}
	PORTB = 0x00;
	
}
void mvbwdpulse() {
	PORTB = 0x00;
	for(int i=0;i!=1000;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */	
		}
	PORTB = 0x12
	;
	for(int i=0;i!=1000;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */	
		}
	PORTB = 0x00;
	
}
void turnleft() {
	int f1,f2 = 0;
	while (f1==0 || f2==0) {
		PORTB = 0x14;
		if(!(PIND & 0x01)) f1=1;
		if(!(PIND & 0x02)) f2=1;
	}
}

void turnright() {
	int f1,f2 = 0;
	while (f1==0 || f2==0) {
		PORTB = 0x0A;
		if(!(PIND & 0x04)) f1=1;
		if(!(PIND & 0x02)) f2=1;
	}
}

void uturn() {
	if(maze[curJunction-1][0]==maze[curJunction-1][2]) {
		maze[curJunction-1][2]=maze[curJunction-1][1];
		if(maze[curJunction-1][0]=='l' & maze[curJunction-1][1]=='r')
			forcedDirn = 'f';
		else
			forcedDirn = 'l';
	}
	else if(maze[curJunction-1][1]==maze[curJunction-1][2]) {
		if(maze[curJunction-1][1]=='r')
			forcedDirn='t';
		else
			forcedDirn='d';
		curJunction-=1;
		maze[curJunction][0]='#';
		maze[curJunction][1]='#';
		maze[curJunction][2]='#';
		
	}  
	
}

void junction(char dir1, char dir2) {
	PORTB = 0x00;
	if(forcedDirn == 'n') {
		maze[curJunction][0]= dir1;
		maze[curJunction][1]= dir2;
		maze[curJunction][2]= dir1;
		curJunction+=1;
	}
	else if(forcedDirn == 'l'|| forcedDirn== 't')
		turnleft();
	else if(forcedDirn=='f'|| forcedDirn == 'd') 
		mvfwd();
	if(forcedDirn != 'n') {
		if(forcedDirn == 'l' || forcedDirn == 'f') 
			forcedDirn = 'n';
		else {
			if(maze[curJunction-1][0]==maze[curJunction-1][2]) {
				maze[curJunction-1][2]=maze[curJunction-1][1];
		                if(maze[curJunction-1][0]=='l' & maze[curJunction-1][2]=='r')
                		        forcedDirn = 'f';
                		else
                        		forcedDirn = 'l';
        		}				
			else {
				if(maze[curJunction-1][1]=='r')
                        		forcedDirn='t';
                		else
                        		forcedDirn='d';
                		curJunction-=1;
                		maze[curJunction][0]='#';
                		maze[curJunction][1]='#';
                		maze[curJunction][2]='#';
			}
		}	

	}	
	
}
int main(void) {

	TCNT0 = 0x63;
	TCCR0 = 0x03;
	
	DDRB = 0x1E;
	PORTB = 0x1E;
	
	DDRD = 0xc0;
	PORTD = 0x0F;
	
	maze_init();

	/* 	PORT D0 : Left sensor
		PORT D1 : Front sensor
		PORT D2 : Right sensor
	*/
		
	
	int solved = 0;
	/* Assume white is high */
	while(1) {
	if(!solved) {
		if( (PIND & 0x07) == 0x07 )  {
			/* Left sensor is on white, front on white, right on white */
			PORTB = 0x14;
			int turnFlag = 0;
			while (!turnFlag) {
				if((PIND & 0x07) == 0x03) {
					turnFlag +=1;
					while((PIND & 0x07 == 0x05));
					PORTB = 0x00;
					uturn();
				}
				if((PIND & 0x07) == 0x05) {
					turnFlag +=1;
					mvfwd();
				}
				if((PIND & 0x07) == 0x01) { 
					turnFlag+=1;
					mvfwd();
				}
			}
		}
		if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			mvfwd();
			
		}
		if((PIND & 0x07) == 0x01) {
			/* Left sensor is on black, front on black, right on white */
			mvfwdpulse();
			if((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				turnleft();
			}
			else if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			/* Junction !! , left and front, we are already on front path */
			junction('l','f');
			}
		}
		if((PIND & 0x07) == 0x04) {
			/* Left sensor is on white, front on black, right on black */
			mvfwdpulse();
			if((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				turnright();
			}
			else if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			/* Junction !! , right and front, we are already on front path */
			junction('f','r');
			}
		}
		if((PIND & 0x07) == 0x00) {
			/* Left sensor is on black, front on black, right on black */
			mvfwdpulse();
			if ((PIND & 0x07) == 0x00) {
				solved = 1;
			}
			else if ((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				/* Junction !!, right and left, we have already overshot it. */
				junction('l','r');
			}
		}
		if((PIND & 0x07) == 0x06) { 
			/* Left sensor is on white, front on white, right on black */
			while((PIND & 0x07) != 0x05)
				PORTB = 0x08;
			/* turn right */
		}
		if((PIND & 0x07) == 0x03) { 
			/* Left sensor is on black, front on white, right on white */
			while((PIND & 0x07) != 0x05)
				PORTB = 0x04;
			/* turn left */
		}
	}	

	/* Now maze is solved. */
	PORTB = 0x00;
	/* Glow the LED's and wait for switch 2 to be pressed. */
	PORTD |= 0xc0;
	while(!(PIND & 0x08));
	/* wait till switch 2 is pressed */
	
	int reached = 0;
	curJunction=0;
	
	if(!reached) {
		if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			mvfwd();
			
		}
		if((PIND & 0x07) == 0x01) {
			/* Left sensor is on black, front on black, right on white */
			mvfwdpulse();
			if((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				turnleft();
			}
			else if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			/* Junction !! , left and front, we are already on front path */
				if(maze[curJunction][2]=='l')
					turnleft();
				else
					mvfwd();
				curJunction+=1;
			}
		}
		if((PIND & 0x07) == 0x04) {
			/* Left sensor is on white, front on black, right on black */
			mvfwdpulse();
			if((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				turnright();
			}
			else if((PIND & 0x07) == 0x05) {
			/* Left sensor is on white, front on black, right on white */
			/* Junction !! , right and front, we are already on front path */
			if(maze[curJunction][2]=='r')
					turnright();
				else
					mvfwd();
				curJunction+=1;
			}
		}
		if((PIND & 0x07) == 0x00) {
			/* Left sensor is on black, front on black, right on black */
			mvfwdpulse();
			if ((PIND & 0x07) == 0x00) {
				reached = 1;
			}
			else if ((PIND & 0x07) == 0x07) {
				/* All 3 are on white */
				/* Junction !!, right and left, we have already overshot it. */
				if(maze[curJunction][2]=='l')
					turnleft();
				else
					turnright();
				curJunction+=1;
			}
		}
		if((PIND & 0x07) == 0x06) { 
			/* Left sensor is on white, front on white, right on black */
			while((PIND & 0x07) != 0x05)
				PORTB = 0x08;
			/* turn right */
		}
		if((PIND & 0x07) == 0x03) { 
			/* Left sensor is on black, front on white, right on white */
			while((PIND & 0x07) != 0x05)
				PORTB = 0x04;
			/* turn left */
		}
		
	}

	
	
	}
	return 0;
}
