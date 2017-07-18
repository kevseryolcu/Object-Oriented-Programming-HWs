
// * File:   main.cpp
 //* Author: Kevser Yolcu
 //*              131044072
 //*
 //* Created on October 6, 2015, 10:11 PM
 

#include <iostream>
using namespace std;

void fill_the_board(char board[][20], int n);
void print_the_board(char board[][20], int n);
int choose_position_for_user(char board[][20],int* x_pos, int* y_pos, int n);
int choose_position_for_computer(char board[][20],int* x_pos, int* y_pos, int n);
int counting_recursive(int road, int i, int j, char board[][20], int *count, char who, int n);
int chage_X_or_O(char board[][20], int i, int j, char who_plays, int n);
int changing_recursive(int road, int i, int j, char board[][20], char user_or_comp, int n);
void final_counter_printer(char board[][20], int n);
int counter_position_for_user(char board[][20], int n);


int main(int argc, char** argv) {

    char board[20][20];
    int n,
		y_pos,
		x_pos,
		comp_move,
		pos,
		users_move;

    cout << "Enter value of n for matrix."
         << "Enter (cift) number from 4 to 20." << endl;

    cin >> n;

    while(n%2 != 0 || (n > 20 || n < 4))
    {
        cout << "You entered wrong number, Enter (cift) number from 4 to 20." << endl;
        cin >> n;
    }

    fill_the_board(board,n);
	print_the_board(board, n);
	do{
		users_move = choose_position_for_user(board, &x_pos, &y_pos, n);

		pos = chage_X_or_O(board, y_pos, x_pos, 'u',n);//u = who plays; user

		if(pos)
		{
			board[y_pos][x_pos] = 'O';
			pos = 0;
		}

		print_the_board(board, n);

		comp_move = choose_position_for_computer(board, &x_pos, &y_pos, n);

		if(comp_move > 0)
		{
			pos = chage_X_or_O(board, y_pos, x_pos, 'c', n);//u = who plays; user
			board[y_pos][x_pos] = 'X';
		}
		print_the_board(board, n);

	}while(users_move != 0 || comp_move != 0);

	final_counter_printer(board, n);

    return (0);
}

//matrisi girilen n degerine gore doldurur ve dondurur
void fill_the_board(char board[][20],int n)
{
	int i, j;

	for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            board[i][j] = '.';

    board[n/2][n/2] = 'X';
    board[n/2][n/2-1] = 'O';
    board[n/2 - 1][n/2] = 'O';
    board[n/2 - 1][n/2 - 1] = 'X';

}

//matrisi ekrana basar
void print_the_board(char board[][20], int n)
{
	int i, j, k;
    cout << "  ";
    for(k=1; k<=n; ++k)
        cout << " " << static_cast<char>(k+96);
    cout << endl;

    for(i = 0; i < n; ++i)
    {
        cout << "" << i+1;
         if(i < 9)
		cout << " " ;
        for(j = 0; j < n; ++j)
            cout << " " << board[i][j];
        cout << endl;
    }
    
    cout << endl;


}


//konsoldan userin hamlelerini alir kontrol eder
int choose_position_for_user(char board[][20],int* x_pos, int* y_pos, int n)
{
	char ch_x_pos;
	int result = 0,
		 pos = -1,
		 count = 0;

	count = counter_position_for_user(board, n);

	if(count > 0)
	{
		cout << "Choose a position, like 4b 6c." << endl;
		cout << "Please don't put space character between x and y positions" << endl;
		cout << "Use lower case" << endl;

		cin >> (*y_pos);
		cin >> ch_x_pos;

		*x_pos = static_cast<int>(ch_x_pos-96);

		*x_pos -= 1;
		*y_pos -= 1;

		pos = chage_X_or_O(board, *y_pos, *x_pos, 'u', n);//u = who plays; user

		if(pos == 0 )
		{
			result = 1;

			while(((*y_pos >= n || *y_pos < 0) || (*x_pos >= n || *x_pos < 0)) )
			{
				cout << "You chose wrong position." << endl
					 << "Choose a position again, like 4b 6c." << endl
					 << "Please don't put space character between x and y positions" << endl
					 << "Use lower case" << endl;

				cin >> (*y_pos);
				cin >> ch_x_pos;

				cout << "" << (*y_pos);
				cout << "" << ch_x_pos << endl;

				*x_pos = static_cast<int>(ch_x_pos-96);

				*x_pos -= 1;
				*y_pos -= 1;

				pos = chage_X_or_O(board, *y_pos, *x_pos, 'u',n);//u = who plays; user

				count = counter_position_for_user(board, n);

				if(pos > 0 || count == 0 )
				{
					result = 1;
					break;
				}
				else
					result = 0;

			}

		}
	}
	else if(pos > 0)
		result = 1;
	else
		result = 0;

	return result;
}



//user ın hamle sayisini bulur
//counting_recursive fonksiyonu ile birlikte calisir
int counter_position_for_user(char board[][20], int n)
{
	int count = 0,
		total = 0,
		i ,
		j ,
		result = 0;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			if(board[i][j] == '.')
			{
				if(i-1 >= 0 && board[i-1][j] == 'X')
					total += counting_recursive(1, i-1, j, board, &count, 'O', n);

				if((i-1 >= 0 && j+1 < n) && board[i-1][j+1] == 'X')
					total += counting_recursive(2, i-1, j+1, board, &count, 'O', n);

				if(j+1 < n && board[i][j+1] == 'X')
					total += counting_recursive(3, i, j+1, board, &count, 'O', n);

				if((i+1 < n && j+1 < n) && board[i+1][j+1] == 'X')
					total += counting_recursive(4, i+1, j+1, board, &count, 'O', n);

				if(i+1 < n && board[i+1][j] == 'X')
					total += counting_recursive(5, i+1, j, board, &count, 'O', n);

				if((i+1 < n && j-1 >= 0) && board[i+1][j-1] == 'X')
					total += counting_recursive(6, i+1, j-1, board, &count, 'O', n);

				if(j-1 >= 0 && board[i][j-1] == 'X')
					total += counting_recursive(7, i, j-1, board, &count, 'O', n);

				if((i-1 >= 0 && j-1 >= 0) && board[i-1][j-1] == 'X')
					total += counting_recursive(8, i-1, j-1, board, &count, 'O', n);
			}
	if(total > 0)
		result = 1;

	return result;
}



//computer icin en iyi hamleyi bulur ve dondurur.
//counting_recursive fonksiyonu ile birlikte calisir
int choose_position_for_computer(char board[][20],int* x_pos, int* y_pos, int n)
{
	int count = 0,
		temp_count = 0,
		result = 0,
		i , j ;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			if(board[i][j] == '.')
			{
				if(i-1 >= 0 && board[i-1][j] == 'O')
					result += counting_recursive(1, i-1, j, board, &count, 'X', n);

				if((i-1 >= 0 && j+1 < n) && board[i-1][j+1] == 'O')
					result += counting_recursive(2, i-1, j+1, board, &count, 'X', n);

				if(j+1 < n && board[i][j+1] == 'O')
					result += counting_recursive(3, i, j+1, board, &count, 'X', n);

				if((i+1 < n && j+1 < n) && board[i+1][j+1] == 'O')
					result += counting_recursive(4, i+1, j+1, board, &count, 'X', n);

				if(i+1 < n && board[i+1][j] == 'O')
					result += counting_recursive(5, i+1, j, board, &count, 'X', n);

				if((i+1 < n && j-1 >= 0) && board[i+1][j-1] == 'O')
					result += counting_recursive(6, i+1, j-1, board, &count, 'X', n);

				if(j-1 >= 0 && board[i][j-1] == 'O')
					result += counting_recursive(7, i, j-1, board, &count, 'X', n);

				if((i-1 >= 0 && j-1 >= 0) && board[i-1][j-1] == 'O')
					result += counting_recursive(8, i-1, j-1, board, &count, 'X', n);


				if(count > temp_count)
				{
					temp_count = count;
					count = 0;
					*x_pos = j;
					*y_pos = i;
				}
			}

	return result;
}

//user ve computer icin yapilabilecek hamle sayisini bulur
//choose_position_for_computer ve choose_position_for_user ile birlikte calisir
//onlarin recursive fonksiyonudur
		//--tum yonleri belirtmek icin road i kullandim. 1 yonu kuzeyi
		//gosterir ve diger yonler sirasiyla saat yonunde ilerlemektedir
                  //              8 1 2
                   //             7 X 3
                   //             6 5 4

int counting_recursive(int road, int i, int j, char board[][20], int *count, char who, int n)
{
	int result = 0;

	if(((i >= n || j >= n) || (i < 0 || j < 0)) || board[i][j] == '.')
	{
		*count = 0;
		return 0;
	}
	else if(board[i][j] == who)
		return 1;
	else
	{
		if(road == 1)
		{
			result = counting_recursive(road, i-1, j, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 2)
		{
			result = counting_recursive(road, i-1, j+1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 3)
		{
			result = counting_recursive(road, i, j+1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 4)
		{
			result = counting_recursive(road, i+1, j+1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 5)
		{
			result = counting_recursive(road, i+1, j, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 6)
		{
			result = counting_recursive(road, i+1, j-1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 7)
		{
			result = counting_recursive(road, i, j-1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
		else if(road == 8)
		{
			result = counting_recursive(road, i-1, j-1, board, count, who, n);
			if(result)
				*count += 1;

			return result;
		}
	}
	return result;
}


//bu fonksiyon oynayana gore(user ya da computer) x veya o yu degistirir
//changing_recursive ile birlikte calisir onu cagiran fonksiyondur
int chage_X_or_O(char board[][20], int i, int j, char who_plays, int n)
{
	char user_or_comp,
		 other;
	int  result1=0,
		 result2=0,
		 result3=0,
		 result4=0,
		 result5=0,
		 result6=0,
		 result7=0,
		 result8=0;


	if(who_plays == 'u')//user
	{
		user_or_comp = 'O';
		other = 'X';
	}
	else//computer
	{
		user_or_comp = 'X';
		other = 'O';
	}

	if((i >= 0 && i < n) && (j >= 0 && j < n) && board[i][j] == '.')
	{
		//--tum yonleri belirtmek icin road i kullandim. 1 yonu kuzeyi
		//gosterir ve diger yonler sirasiyla saat yonunde ilerlemektedir
                  //              8 1 2
                   //             7 X 3
                   //             6 5 4


		if(i-1 >= 0 && board[i-1][j] == other)
			result1 = changing_recursive(1, i-1, j, board, user_or_comp, n);

		if((i-1 >= 0 && j+1 < n) && board[i-1][j+1] == other)
			result2 = changing_recursive(2, i-1, j+1, board, user_or_comp, n);

		if(j+1 < n && board[i][j+1] == other)
			result3 = changing_recursive(3, i, j+1, board, user_or_comp, n);

		if((i+1 < n && j+1 < n) && board[i+1][j+1] == other)
			result4 = changing_recursive(4, i+1, j+1, board, user_or_comp, n);

		if(i+1 < n && board[i+1][j] == other)
			result5 = changing_recursive(5, i+1, j, board, user_or_comp, n);

		if((i+1 < n && j-1 >= 0) && board[i+1][j-1] == other)
			result6 = changing_recursive(6, i+1, j-1, board, user_or_comp, n);

		if((j-1 >= 0 ) && board[i][j-1] == other)
			result7 = changing_recursive(7, i, j-1, board, user_or_comp, n);

		if((i-1 >= 0 && j-1 >= 0) && board[i-1][j-1] == other)
			result8 = changing_recursive(8, i-1, j-1, board, user_or_comp, n);
	}

	if(board[i][j] == '.' && (((result1 || result2) || (result3 || result4)) || ((result5|| result6) || (result7 || result8))))
	{
		board[i][j] = user_or_comp;
		return 1;
	}
	else
		return 0;

}

//eger degisecek karakter var ise 2 o arasinda kalmis x ler gibi
//onlari chage_X_or_O fonksiyonu ile birlikte calisarak degistirir,
//recursive bir fonksiyondur
int changing_recursive(int road, int i, int j, char board[][20], char user_or_comp, int n)
{
	int result = 0;
	
	if( (i >= n || j >= n) || (i < 0 || j < 0) || (board[i][j] == '.') )
		return 0;
	else if(board[i][j] == user_or_comp)
		return 1;
	else
	{
		if(road == 1)
		{
			result = changing_recursive(road, i-1, j, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 2)
		{
			result = changing_recursive(road, i-1, j+1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 3)
		{
			result = changing_recursive(road, i, j+1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 4)
		{
			result = changing_recursive(road, i+1, j+1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 5)
		{
			result = changing_recursive(road, i+1, j, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 6)
		{
			result = changing_recursive(road, i+1, j-1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 7)
		{
			result = changing_recursive(road, i, j-1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
		else if(road == 8)
		{
			result = changing_recursive(road, i-1, j-1, board, user_or_comp, n);
			if(result)
				board[i][j] = user_or_comp;

			return result;
		}
	}
	return result;
}




//oyunun sonunda x ve o lari sayar ve kimin
//kazandigini ekrana basar
void final_counter_printer(char board[][20], int n)
{
	int i, j,
		user = 0,
		computer = 0;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
		{
			if(board[i][j] == 'O')
				user += 1;
			else if(board[i][j] == 'X')
				computer += 1;
		}

	cout << "user : " << user << endl;
	cout << "computer : " << computer << endl;

	if(computer == user)
		cout << "Nobody won!" << endl;
	else if(computer < user)
		cout << "You won. Congratulation :D" << endl;
	else
		cout << "Game Over!" << endl;

}
