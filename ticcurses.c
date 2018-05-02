#include <ncurses.h>

int table[8][3] = {{1,5,9},{3,5,7},{4,5,6},{1,2,3},{7,8,9},{1,4,7},{2,5,8},{3,6,9}};

int main(){
	initscr();
	int t[9] = {0,0,0,0,0,0,0,0,0};
	curs_set(0);
	noecho();
	pintado();
	char turno[2] = {'x','c'};
	int index = 0;
	while(queden(t) && !fin(t)){
		if(turno[index] == 'x'){
			int mov = getch();
			while( ((mov-49) < 0 || (mov-49) >= 9)  ||  t[mov-49] != 0){
				mov = getch();
			}
			colocar(mov-48, turno[index]);
			t[mov-49] = 1;
		}else{
			getch();
			int decision = minimaxdecision(t);
			colocar(decision, turno[index]);
			t[decision-1] = 2;
			
		}
		
		index = (index+1)%2;
	}

	move(21,0);
	if(utility(t) == 3){
		printw("COMPUTER WINS");
	}else if(utility(t) == -3){
		printw("HUMAN WINS");
	}else{
		printw("NOBODY WINS");
	}
	getch();
	endwin();
	return 0;
}

int fin(int t[]){
	return (utility(t) == 3 || utility(t) == -3);
}

int utility(int t[]){
	int max = 0;
	int min = 0;
	int c = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 3; j++){
			if(t[table[i][j]-1] == 2){
				c++;
			}else if(t[table[i][j]-1] == 1){
				c--;
			}
		}
		
		if(max < c){
			max = c;
		}
		if(c < min){
			min = c;
		}

		c = 0;
	}

	int total;
	if((-1)*min > max){
		total = min;
	}else{
		total = max;
	}

	return total;
}

int maximo(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int minimo(int a, int b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

/*void result(int t[], int a){
	t[a] = 2;

}*/

int minimaxdecision(int t[]){
	int max = -50;
	int c = 0;
	int decision = -1;
	for(int i = 1; i < 10; i++){
		if(t[i-1] == 0){
			t[i-1] = 2;
			c = minvalue(t,1);
			t[i-1] = 0;
			if(c > max){
				max = c;
				decision = i;
			}
		}
	}
	return decision;
}

int maxvalue(int t[], int tur){
	int turp = 0;
	if (tur == 2) turp = 1;
	if (tur == 1) turp = 2;
	if(!queden(t) || fin(t)){
		return utility(t);
	}else{
		int v = -50;
		for(int i = 1; i <= 9; i++){
			if(t[i-1] == 0){
				t[i-1] = tur;
				v = maximo(v, minvalue(t, turp));
				t[i-1] = 0;
			}
		}
		return v;
	}
}

int minvalue(int t[], int tur){
	int turp = 0;
	if (tur == 2) turp = 1;
	if (tur == 1) turp = 2;
	if(!queden(t) || fin(t)){
		return utility(t);
	}else{
		int v = 50;
		for(int j = 1; j <= 9; j++){
			if(t[j-1] == 0){
				t[j-1] = tur;
				v = minimo(v, maxvalue(t, turp));
				t[j-1] = 0;
			}
		}
		return v;
	}
}

int queden(int t[]){
	int v = 0;
	int c = 0;
	while(v == 0 && c < 9 ){
		if(t[c] == 0){
			v = 1;	
		}
		c++;
	}
	return v;
}

void pintado(){
	printw("\n");
	for (int x = 0; x < 3; x++){
		for (int i = 0; i < 19; i++){
			printw("* ");
		}
		printw("\n");
		for (int h = 0; h < 5; h++){
			for (int j = 0; j < 19; j++){
				if (j== 0 || j == 6 || j == 12 || j == 18){
					printw("* ");
				}else{
					printw("  ");
				}
			}
			printw("\n");
		}
	}

	for (int p = 0; p < 19; p++){
		printw("* ");
	}
	printw("\n\n");
}

void colocar(int p, char c){
	int x = 0;
	if (p % 3 == 0) x = 28;
	else if (p % 3 == 1) x = 4; 
	else if (p % 3 == 2) x = 16;

	int y = 0;
	if ((p-1) / 3 == 0) y = 3;
	else if ((p-1) / 3 == 1) y = 9;
	else if ((p-1) / 3 == 2) y = 15;
	if (c == 'c'){
		pintacir(x,y);
	}else {
		pintax(x,y);
	}
}

void pintacir(int x, int y){
	x += 2;
	move(y,x);
	addch('*');
	y++;
	move(y,x);
	addch('*');
	x--;
	move(y,x);
	addch('*');
	x += 2;
	move(y,x);
	addch('*');
	x--;
	y++;
	move(y,x);
	addch('*');
}

void pintax(int x, int y){
	move(y,x);
	addch('*');
	x += 4;
	move(y,x);
	addch('*');
	x -= 2;
	y ++;
	move(y,x);
	addch('*');
	y++;
	x -= 2;
	move(y,x);
	addch('*');
	x += 4;
	move(y,x);
	addch('*');
}
