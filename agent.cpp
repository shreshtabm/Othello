#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>


int ch, depth, i, j, valid[3][60], f = 0, r = -1, temp, cost, mas, x, y, temp1[2][20], r1 = -1, ctr, i4, valid_arr[5][400], temp3, alpha = -9999, beta = 9999, c = 0, dep, al_printed[2][10], p1 = -1, elex, eley;
int ctrm = -1, tempm[2][20], depthm, maxy = -9999, avalid[2][60], posi = 0,betag;
char board[8][8], you, opponent, board2[8][8], you1;
char board1m[8][8], board2m[8][8], board3m[8][8], board4m[8][8], board5m[8][8], board6m[8][8], board7m[8][8], board8m[8][8], board9m[8][8], board10m[8][8], boardi[8][8];
using namespace std;
int nx = -1, ny = 0, nex = -1, ney = -1, nwx = -1, nwy = 1, wx = 0, wy = 1, ex = 0, ey = -1, sx = 1, sy = 0, swx = 1, swy = -1, sex = 1, sey = 1;
int weight[8][8] = { { 99, -8, 8, 6, 6, 8, -8, 99 }, { -8, -24, -4, -3, -3, -4, -24, -8 }, { 8, -4, 7, 4, 4, 7, -4, 8 }, { 6, -3, 4, 0, 0, 4, -3, 6 },
{ 6, -3, 4, 0, 0, 4, -3, 6 }, { 8, -4, 7, 4, 4, 7, -4, 8 }, { -8, -24, -4, -3, -3, -4, -24, -8 }, { 99, -8, 8, 6, 6, 8, -8, 99 } };
fstream temps, out, mains;


void validmove();
void findmoves(int k, int l);
void findmoves1(int k, int l);
int position(int k, int l, int px, int py);
int position1(int k, int l, int px, int py);
void move_try(int x, int y);
void sort_valid();
void turn();
void reint();
void duplicate();
void minimax();
void move();

int terminal(char boardt[8][8], char yo, char op)
{
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (boardt[i][j] == '*')
			{
				a++;
			}
			if (boardt[i][j] == yo)
			{
				b++;
			}
			if (boardt[i][j] == op)
				c++;
		}
	}
	if (a == 0 || b == 0 || c == 0)
		return 1;
	else
		return -1;
}
void greedy() //This is the function for greedy algorithm called from main
{
	validmove();
	move();

}
void move() // making the move depending the maximum fetching valid moves
{
	duplicate();
	x = valid[0][0];
	y = valid[1][0];
	mas = valid[2][0];
	for (i = 1; i <= r; i++)
	{
		if (valid[2][i] > mas)
		{
			x = valid[0][i];
			y = valid[1][i];
			mas = valid[2][i];
		}
	}
	if (r >= 0)
	{
		board[x][y] = you;
		findmoves1(x, y);
	}
	//fstream output;
	//output.open("output.txt", std::fstream::out);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			mains << board[i][j];
		}
		mains << "\n";
	}

	//output.close();
}
void duplicate() //To check whether there are duplicate values
{
	for (i = 0; i < r; i++)
	{
		if (valid[0][i] == valid[0][i + 1] && valid[1][i] == valid[1][i + 1])
		{
			valid[2][i] += valid[2][i + 1];
			valid[2][i + 1] = -999;
			valid[2][i] -= weight[valid[0][i]][valid[1][i]];
		}
	}

}
void move_try(int x, int y) // searching for all opponents coins to be flipped
{
	findmoves1(x, y);
}
void validmove() // checking for the valid move
{
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == you)
			{
				findmoves(i, j);
			}
		}
	}
	sort_valid();

}
void findmoves(int k, int l) // searching for all valid moves
{
	if (board[k + nwx][l + nwy] == opponent)
	{
		cost = 2 * weight[k + nwx][l + nwy];
		position(k + nwx, l + nwy, nwx, nwy);
	}
	if (board[k + nx][l + ny] == opponent)
	{
		cost = 2 * weight[k + nx][l + ny];
		position(k + nx, l + ny, nx, ny);
	}
	if (board[k + nex][l + ney] == opponent)
	{
		cost = 2 * weight[k + nex][l + ney];
		position(k + nex, l + ney, nex, ney);
	}
	if (board[k + ex][l + ey] == opponent)
	{
		cost = 2 * weight[k + ex][l + ey];
		position(k + ex, l + ey, ex, ey);
	}
	if (board[k + sex][l + sey] == opponent)
	{
		cost = 2 * weight[k + sex][l + sey];
		position(k + sex, l + sey, sex, sey);
	}
	if (board[k + sx][l + sy] == opponent)
	{
		cost = 2 * weight[k + sx][l + sy];
		position(k + sx, l + sy, sx, sy);
	}
	if (board[k + swx][l + swy] == opponent)
	{
		cost = 2 * weight[k + swx][l + swy];
		position(k + swx, l + swy, swx, swy);
	}
	if (board[k + wx][l + wy] == opponent)
	{
		cost = 2 * weight[k + wx][l + wy];
		position(k + wx, l + wy, wx, wy);
	}
}
void findmoves1(int k, int l) //searching for opponents coins that needs to be flipped
{
	if (board[k + nwx][l + nwy] == opponent)
	{

		reint();
		position1(k + nwx, l + nwy, nwx, nwy);
	}
	if (board[k + nx][l + ny] == opponent)
	{

		reint();
		position1(k + nx, l + ny, nx, ny);
	}
	if (board[k + nex][l + ney] == opponent)
	{

		reint();
		position1(k + nex, l + ney, nex, ney);
	}
	if (board[k + ex][l + ey] == opponent)
	{

		reint();
		position1(k + ex, l + ey, ex, ey);
	}
	if (board[k + sex][l + sey] == opponent)
	{

		reint();
		position1(k + sex, l + sey, sex, sey);
	}
	if (board[k + sx][l + sy] == opponent)
	{

		reint();
		position1(k + sx, l + sy, sx, sy);
	}
	if (board[k + swx][l + swy] == opponent)
	{
		reint();
		position1(k + swx, l + swy, swx, swy);
	}
	if (board[k + wx][l + wy] == opponent)
	{
		reint();
		position1(k + wx, l + wy, wx, wy);
	}
}
int position(int k, int l, int px, int py) // finding valid moves
{
	if (k + px >= 0 && l + py >= 0 && k + px < 8 && l + py < 8)
	{
		if (board[k + px][l + py] == '*')
		{
			valid[0][++r] = k + px;
			valid[1][r] = l + py;
			valid[2][r] = cost + weight[k + px][l + py];
		}
		if (board[k + px][l + py] == opponent)
		{
			cost = cost + 2 * weight[k + px][l + py];
			return position(k + px, l + py, px, py);
		}
		if (board[k + px][l + py] == you)
		{
			return position(9, 9, px, py);
		}
	}
	return 0;
}
int position1(int k, int l, int px, int py) // flipping all valid opponent's coins
{
	if (ctr == 0)
	{
		temp1[0][++r1] = k;
		temp1[1][r1] = l;
		ctr = 1;
	}
	if (k + px >= 0 && l + py >= 0 && k + px < 8 && l + py < 8)
	{
		if (board[k + px][l + py] == '*')
		{
			return position1(9, 9, px, py);
		}
		if (board[k + px][l + py] == opponent)
		{
			temp1[0][++r1] = k + px;
			temp1[1][r1] = l + py;
			return position1(k + px, l + py, px, py);

		}
		if (board[k + px][l + py] == you)
		{
			turn();
			return position1(9, 9, px, py);
		}
	}
	return 0;
}
void turn() // flippng the coins
{
	for (i = 0; i <= r1; i++)
	{
		board[temp1[0][i]][temp1[1][i]] = you;
	}
}
void sort_valid() // sorting based on how they appear (x,y)
{
	for (i = 0; i < r; i++)
	{
		for (j = i + 1; j <= r; j++)
		{
			if (valid[0][i] > valid[0][j])
			{
				temp = valid[0][i];
				valid[0][i] = valid[0][j];
				valid[0][j] = temp;
				temp = valid[1][i];
				valid[1][i] = valid[1][j];
				valid[1][j] = temp;
				temp = valid[2][i];
				valid[2][i] = valid[2][j];
				valid[2][j] = temp;

			}
			if (valid[0][i] == valid[0][j])
			{
				if (valid[1][i] > valid[1][j])
				{
					temp = valid[0][i];
					valid[0][i] = valid[0][j];
					valid[0][j] = temp;
					temp = valid[1][i];
					valid[1][i] = valid[1][j];
					valid[1][j] = temp;
					temp = valid[2][i];
					valid[2][i] = valid[2][j];
					valid[2][j] = temp;
				}
			}
		}
	}
}
void reint() // reinitializing counter and rear for temp1 so 
{
	ctr = 0;
	r1 = -1;
}
char value(int val)
{
	return 97 + val;
}

int eval(char boardm[8][8], char yo, char op)
{
	int costm = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (boardm[i][j] == yo)
				costm += weight[i][j];
			else if (boardm[i][j] == op)
				costm -= weight[i][j];
		}
	}
	return costm;
}
int positionm(int k, int l, int px, int py, int validm[2][60], char yo, char op, char boardm[8][8]) // finding valid moves
{
	if (k + px >= 0 && l + py >= 0 && k + px < 8 && l + py < 8)
	{
		if (boardm[k + px][l + py] == '*')
		{
			validm[0][++r] = k + px;
			validm[1][r] = l + py;
		}
		if (boardm[k + px][l + py] == op)
		{
			return positionm(k + px, l + py, px, py, validm, yo, op, boardm);
		}
		if (boardm[k + px][l + py] == yo)
		{
			return positionm(9, 9, px, py, validm, yo, op, boardm);
		}
	}
	return 0;
}
void findmovesm(char boardm[8][8], char op, char yo, int k, int l, int validm[2][60]) // searching for all valid moves
{
	if (boardm[k + nwx][l + nwy] == op)
	{
		positionm(k + nwx, l + nwy, nwx, nwy, validm, yo, op, boardm);
	}
	if (boardm[k + nx][l + ny] == op)
	{
		positionm(k + nx, l + ny, nx, ny, validm, yo, op, boardm);
	}
	if (boardm[k + nex][l + ney] == op)
	{
		positionm(k + nex, l + ney, nex, ney, validm, yo, op, boardm);
	}
	if (boardm[k + ex][l + ey] == op)
	{
		positionm(k + ex, l + ey, ex, ey, validm, yo, op, boardm);
	}
	if (boardm[k + sex][l + sey] == op)
	{
		positionm(k + sex, l + sey, sex, sey, validm, yo, op, boardm);
	}
	if (boardm[k + sx][l + sy] == op)
	{
		positionm(k + sx, l + sy, sx, sy, validm, yo, op, boardm);
	}
	if (boardm[k + swx][l + swy] == op)
	{
		positionm(k + swx, l + swy, swx, swy, validm, yo, op, boardm);
	}
	if (boardm[k + wx][l + wy] == op)
	{
		positionm(k + wx, l + wy, wx, wy, validm, yo, op, boardm);
	}
}
void sort_validm(int validm[2][60])
{
	int temp;
	for (int i = 0; i < r; i++)
	{
		for (int j = i + 1; j <= r; j++)
		{
			if (validm[0][i] > validm[0][j])
			{
				temp = validm[0][i];
				validm[0][i] = validm[0][j];
				validm[0][j] = temp;
				temp = validm[1][i];
				validm[1][i] = validm[1][j];
				validm[1][j] = temp;

			}
			if (validm[0][i] == validm[0][j])
			{
				if (validm[1][i] > validm[1][j])
				{
					temp = validm[0][i];
					validm[0][i] = validm[0][j];
					validm[0][j] = temp;
					temp = validm[1][i];
					validm[1][i] = validm[1][j];
					validm[1][j] = temp;
				}
			}
		}
	}
}
int duplicatem(int validm[2][60]) //To check whether there are duplicate values
{
	for (int i = 0; i < r; i++)
	{
		if (validm[0][i] == validm[0][i + 1] && validm[1][i] == validm[1][i + 1])
		{
			for (int j = i + 1; j < r; j++)
			{
				validm[0][j] = validm[0][j + 1];
				validm[1][j] = validm[1][j + 1];
			}
			r--;
		}
	}
	return r;
}
int valid_m(char boardm[8][8], char yo, char op, int validm[2][60])
{
	r = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (boardm[i][j] == yo)
			{
				findmovesm(boardm, op, yo, i, j, validm);
			}
		}
	}
	sort_validm(validm);
	r = duplicatem(validm);
	return r;
}
void turnm(char board[8][8], char yo, int temp1[2][20]) // flippng the coins
{
	for (int i = 0; i <= r1; i++)
	{
		board[temp1[0][i]][temp1[1][i]] = yo;
	}
}
int position1m(int k, int l, int px, int py, char boardm[8][8], char yo, char op) // flipping all valid opponent's coins
{
	if (ctr == 0)
	{
		tempm[0][++r1] = k;
		tempm[1][r1] = l;
		ctr = 1;
	}
	if (k + px >= 0 && l + py >= 0 && k + px < 8 && l + py < 8)
	{
		if (boardm[k + px][l + py] == '*')
		{
			return position1m(9, 9, px, py, boardm, yo, op);
		}
		if (boardm[k + px][l + py] == op)
		{
			tempm[0][++r1] = k + px;
			tempm[1][r1] = l + py;
			return position1m(k + px, l + py, px, py, boardm, yo, op);

		}
		if (boardm[k + px][l + py] == yo)
		{
			turnm(boardm, yo, tempm);
			return position1m(9, 9, px, py, boardm, yo, op);
		}
	}
	return 0;
}
void findmoves1m(int k, int l, char boardm[8][8], char yo, char op) //searching for opponents coins that needs to be flipped
{
	if (boardm[k + nwx][l + nwy] == op)
	{

		reint();
		position1m(k + nwx, l + nwy, nwx, nwy, boardm, yo, op);
	}
	if (boardm[k + nx][l + ny] == op)
	{

		reint();
		position1m(k + nx, l + ny, nx, ny, boardm, yo, op);
	}
	if (boardm[k + nex][l + ney] == op)
	{

		reint();
		position1m(k + nex, l + ney, nex, ney, boardm, yo, op);
	}
	if (boardm[k + ex][l + ey] == op)
	{

		reint();
		position1m(k + ex, l + ey, ex, ey, boardm, yo, op);
	}
	if (boardm[k + sex][l + sey] == op)
	{

		reint();
		position1m(k + sex, l + sey, sex, sey, boardm, yo, op);
	}
	if (boardm[k + sx][l + sy] == op)
	{

		reint();
		position1m(k + sx, l + sy, sx, sy, boardm, yo, op);
	}
	if (boardm[k + swx][l + swy] == op)
	{
		reint();
		position1m(k + swx, l + swy, swx, swy, boardm, yo, op);
	}
	if (boardm[k + wx][l + wy] == op)
	{
		reint();
		position1m(k + wx, l + wy, wx, wy, boardm, yo, op);
	}
}
void save(char boardm[8][8], int depth)
{
	if (depth == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board1m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board2m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board3m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 3)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board4m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 4)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board5m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 5)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board6m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 6)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board7m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 7)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board8m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 8)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board9m[i][j] = boardm[i][j];
			}
		}
	}
	if (depth == 9)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board10m[i][j] = boardm[i][j];
			}
		}
	}
}
void reset(char boardm[8][8], int depth)
{
	if (depth == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board1m[i][j];
			}
		}
	}
	if (depth == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board2m[i][j];
			}
		}
	}
	if (depth == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board3m[i][j];
			}
		}
	}
	if (depth == 3)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board4m[i][j];
			}
		}
	}
	if (depth == 4)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board5m[i][j];
			}
		}
	}
	if (depth == 5)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board6m[i][j];
			}
		}
	}
	if (depth == 6)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board7m[i][j];
			}
		}
	}
	if (depth == 7)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board8m[i][j];
			}
		}
	}
	if (depth == 8)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board9m[i][j];
			}
		}
	}
	if (depth == 9)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				boardm[i][j] = board10m[i][j];
			}
		}
	}
}

int  max_val(char boardm[8][8], int depth, int yo, int op, int alpha, int beta, int k, int l);
int min_val(char boardm[8][8], int depth, char yo, char  op, int alpha, int  beta, int k, int l)
{
	int first = 0;
	int cost;
	int a = k;
	int b = l;
	int validm[2][60];
	if (depth == depthm)
	{
		return eval(boardm, op, yo);
	}
	int v = 9999;
	int no = valid_m(boardm, yo, op, validm);
	/*if (no == -1)
	{
		out << "pass," << depth + 1 << ",";
		if (v == -9999 || v == 9999)
		{
			out << "Infinity\n";
		}
		else
		{
			out << v << endl;
		}
		return eval(boardm, op, yo);
	}*/
	if (no == -1 && terminal(boardm, yo, op) == 1)
	{
		return eval(boardm, op, yo);
	}
	if (no == -1 && terminal(boardm, yo, op) == -1)
	{

		out << "pass," << depth + 1 << ",";

		out << eval(boardm, op, yo) << endl;


		return eval(boardm, op, yo);
	}
	save(boardm, depth);
	int i;

	for (i = 0; i <= no; i++)
	{
		/*if (depthm % 2 == 1 || i == no + 1)
		{
		v = 9999;
		}*/
		reset(boardm, depth);
		boardm[validm[0][i]][validm[1][i]] = yo;
		findmoves1m(validm[0][i], validm[1][i], boardm, yo, op);
		if (depth + 1 == depthm || terminal(boardm, yo, op) == 1)
		{
			cost = max_val(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << "," << cost << endl;
		}
		else
		{
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << ",";
			if (v == -9999 || v == 9999 || first==0)
			{
				first++;
				out << "-Infinity\n";
			}
			else out << v << endl;
			cost = max_val(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
		}


		if (cost  <v)
		{
			v = cost;
		}

		/*if (beta > v)
		beta = v;
		if (v <= alpha)
		{
		out << value(b) << a + 1 << "," << depth << "," << v << "," << alpha << "," << beta << endl;
		return v;
		}*/
		if (a != -1 && b != -1)
		{
			if (cost > v && depth == 0 && depth == 2)
			{
				v = cost;
			}

			out << value(b) << a + 1 << "," << depth << ",";
			if (v == 9999 || v == -9999)
			{
				out << "Infinity\n";
			}
			else out << v << endl;
		}
		first = 0;
	}
	return v;
}
int  max_val(char boardm[8][8], int depth, int yo, int op, int alpha, int beta, int k, int l)
{

	int cost;
	int c = k;
	int d = l;
	int validm[2][60];
	int no;
	int first = 0;
	if (depth == depthm)
	{
		return eval(boardm, yo, op);
	}
	int v = -9999;
	no = valid_m(boardm, yo, op, validm);
	if (no == -1)
	{
		if (depth == 0 && depthm != 1)
		{
			out << "root,0,-Infinity\n";
		}
		out << "pass," << depth + 1 << ",";
		if (v == -9999 || v == 9999)
		{
			out << "Infinity\n";
		}
		else
		{
			out << v << endl;
		}
		if (depth == 0 && depthm != 1)
		{

			cost = min_val(boardm, depth + 1, op, yo, alpha, beta, -1, -1);
			out << "pass" << "," << depth + 1 << "," << cost << endl;
		}
		return eval(boardm, yo, op);
	}
	save(boardm, depth);
	int i;
	if (no == -1)
	{
		out << "pass," << depth + 1 << ",";
		if (v == -9999 || v == 9999)
		{
			out << "-Infinity\n";
		}
		else
		{
			out << v << endl;
		}
		return eval(boardm, yo, op);
	}
	for (i = 0; i <= no; i++)
	{

		if (depth == 0)
		{
			ctrm++;
			out << "root,0,";
			if (maxy<v)
			{
				posi = ctrm;
				maxy = v;

			}
			if (maxy == -9999 || maxy == 9999)
			{
				out << "-Infinity\n";
			}
			else
				out << maxy << "\n";

		}
		/*if (depthm >1 && i == no + 1)
		{
		v = -9999;
		}*/


		reset(boardm, depth);
		boardm[validm[0][i]][validm[1][i]] = yo;
		findmoves1m(validm[0][i], validm[1][i], boardm, yo, op);
		if (depth + 1 == depthm || terminal(boardm, yo, op) == 1)
		{
			cost = min_val(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << "," << cost << endl;
		}
		else
		{
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << ",";
			if (v == 9999 || v == -9999 || first == 0)
			{
				first++;
				out << "Infinity\n";
			}
			else
				out << v << "\n";
			cost = min_val(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
		}
		if (cost > v)
		{
			v = cost;
		}
		/*if (v >= beta)
		{
		out << value(d) << c + 1 << "," << depth << "," << v << "," << alpha << "," << beta << endl;
		return v;
		if (alpha < v)
		alpha = v;*/
		if (d != -1 && c != -1)
		{
			if (cost < v && depth == 1 && depth == 3)
			{
				v = cost;
			}
			out << value(d) << c + 1 << "," << depth << ",";
			if (v == -9999 || v == 9999)
			{
				out << "-Infinity\n";
			}
			else { out << v << endl; }
		}
		first = 0;
	}

	return v;

}
void minimax(char boardm[8][8], int depth, char yo, char op)
{
	if (terminal(boardm, yo, op) == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mains << boardi[i][j];
			}
			mains << endl;
		}
		mains << "Node,Depth,Value\n";
		mains << "root,0," << eval(boardm, yo, op) << endl;
	}
	else{
		out << "Node,Depth,Value\n";
		int v = max_val(boardm, 0, yo, op, -9999, 9999, -1, -1);
		if (maxy < v)
		{
			maxy = v;
			ctrm++;
			posi = ctrm;
		}

		out << "root,0," << maxy << endl;
		posi = posi - 1;
		//out << posi;
		if (posi != -1)
		{
			boardi[avalid[0][posi]][avalid[1][posi]] = yo;
			findmoves1m(avalid[0][posi], avalid[1][posi], boardi, yo, op);
		}
		out.close();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mains << boardi[i][j];
			}
			mains << endl;
		}

		out.open("temp.txt");
		string str;

		while (getline(out, str))
		{
			mains << str << endl;
		}
	}
}
int  max_val_a(char boardm[8][8], int depth, int yo, int op, int alpha, int beta, int k, int l);
int min_val_a(char boardm[8][8], int depth, char yo, char  op, int alpha, int  beta, int k, int l)
{
	int first = 0;
	int cost;
	int a = k;
	int b = l;
	int validm[2][60];
	if (depth == depthm)
	{
		return eval(boardm, op, yo);
	}
	int v = 9999;
	int no = valid_m(boardm, yo, op, validm);
	if (no == -1 && terminal(boardm, yo, op) == 1)
	{
		return eval(boardm, op, yo);
	}
	if (no == -1 && terminal(boardm, yo, op) == -1)
	{

		out << "pass," << depth + 1 << ",";

		out << eval(boardm, op, yo) << ",";
		if (eval(boardm, op, yo) < beta)
			beta = eval(boardm, op, yo);
		if (alpha == -9999 || alpha == 9999)
		{
			out << "-Infinity,";
		}
		else out << alpha << ",";
		if (beta == -9999 || beta == 9999)
		{
			out << "Infinity\n";
		}
		else out << beta << endl;
		if (alpha < eval(boardm, op, yo))
			alpha = eval(boardm, op, yo);

		return eval(boardm, op, yo);
	}
	save(boardm, depth);
	int i;

	for (i = 0; i <= no; i++)
	{
		/*if (depthm % 2 == 1 || i == no + 1)
		{
		v = 9999;
		}*/
		reset(boardm, depth);
		boardm[validm[0][i]][validm[1][i]] = yo;
		findmoves1m(validm[0][i], validm[1][i], boardm, yo, op);
		if (depth + 1 == depthm || terminal(boardm, yo, op) == 1)
		{
			cost = max_val_a(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << "," << cost << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
		}
		else
		{
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << ",";
			if (v == -9999 || v == 9999 ||first)
			{
				first++;
				out << "-Infinity,";
			}
			else out << v << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
			cost = max_val_a(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
		}


		if (cost  <v)
		{
			v = cost;
		}

		if (beta > v)
			beta = v;
		if (beta>betag)
		{
			betag = beta;
		}
		if (v <= alpha)
		{
			out << value(b) << a + 1 << "," << depth << ",";
			if (v == 9999 || v == -9999)
			{
				out << "Infinity,";
			}
			else out << v << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;

			return v;
		}
		if (a != -1 && b != -1)
		{
			if (cost > v && depth == 0 && depth == 2)
			{
				v = cost;
			}

			out << value(b) << a + 1 << "," << depth << ",";
			if (v == 9999 || v == -9999)
			{
				out << "Infinity,";
			}
			else out << v << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
		}
		first = 0;
	}
	return v;
}
int  max_val_a(char boardm[8][8], int depth, int yo, int op, int alpha, int beta, int k, int l)
{

	int cost;
	int c = k;
	int d = l;
	int validm[2][60];
	int no;
	int first = 0;
	if (depth == depthm)
	{
		return eval(boardm, yo, op);
	}
	int v = -9999;
	no = valid_m(boardm, yo, op, validm);
	if (no == -1)
	{
		if (depth == 0 && depthm != 1)
		{
			out << "root,0,-Infinity,-Infinity,Infinity\n";
		}
		out << "pass," << depth + 1 << ",";
		if (v == -9999 || v == 9999)
		{
			out << "Infinity,";
		}
		else
		{
			out << v << ",";
		}
		if (alpha == -9999 || alpha == 9999)
		{
			out << "-Infinity,";
		}
		else out << alpha << ",";
		if (beta == -9999 || beta == 9999)
		{
			out << "Infinity\n";
		}
		else out << beta << endl;
		if (depth == 0 && depthm != 1)
		{

			cost = min_val_a(boardm, depth + 1, op, yo, alpha, beta, -1, -1);
			out << "pass" << "," << depth + 1 << "," << cost << ",";
			if (cost < beta)
				beta = cost;
			if (betag<beta)
				betag = beta;
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
			if (alpha < cost)
				alpha = cost;
		}
		return eval(boardm, yo, op);
	}
	save(boardm, depth);
	int i;

	for (i = 0; i <= no; i++)
	{

		if (depth == 0)
		{
			ctrm++;
			out << "root,0,";
			if (maxy<v)
			{
				posi = ctrm;
				maxy = v;

			}
			if (maxy == -9999 || maxy == 9999)
			{
				out << "-Infinity,";
			}
			else
				out << maxy << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;

		}
		/*if (depthm >1 && i == no + 1)
		{
		v = -9999;
		}*/


		reset(boardm, depth);
		boardm[validm[0][i]][validm[1][i]] = yo;
		findmoves1m(validm[0][i], validm[1][i], boardm, yo, op);
		if (depth + 1 == depthm || terminal(boardm, yo, op) == 1)
		{
			cost = min_val_a(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << "," << cost << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
		}
		else
		{
			out << value(validm[1][i]) << validm[0][i] + 1 << "," << depth + 1 << ",";
			if (v == 9999 || v == -9999 || first == 0)
			{
				first++;
				out << "Infinity,";
			}
			else
				out << v << ",";
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
			cost = min_val_a(boardm, depth + 1, op, yo, alpha, beta, validm[0][i], validm[1][i]);
		}
		if (cost > v)
		{
			v = cost;
		}
		if (v >= beta)
		{
			out << value(d) << c + 1 << "," << depth << ",";

			if (v == -9999 || v == 9999)
			{
				out << "-Infinity,";
			}
			else { out << v << ","; }
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;

			return v;
		}
		if (alpha < v)
			alpha = v;
		if (d != -1 && c != -1)
		{
			if (cost < v && depth == 1 && depth == 3)
			{
				v = cost;
			}
			out << value(d) << c + 1 << "," << depth << ",";
			if (v == -9999 || v == 9999)
			{
				out << "-Infinity,";
			}
			else { out << v << ","; }
			if (alpha == -9999 || alpha == 9999)
			{
				out << "-Infinity,";
			}
			else out << alpha << ",";
			if (beta == -9999 || beta == 9999)
			{
				out << "Infinity\n";
			}
			else out << beta << endl;
		}
		first = 0;
		
	}
	
	return v;

}
void alphabeta(char boardm[8][8], int depth, char yo, char op)
{
	if (terminal(boardm, yo, op) == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mains << boardi[i][j];
			}
			mains << endl;
		}
		mains << "Node,Depth,Value,Alpha,Beta\n";
		mains << "root,0," << eval(boardm, yo, op) << ",-Infinity,Infinity\n";
	}

	else {
		out << "Node,Depth,Value,Alpha,Beta\n";
		int v = max_val_a(boardm, 0, yo, op, -9999, 9999, -1, -1);
		if (maxy < v)
		{
			maxy = v;
			ctrm++;
			posi = ctrm;
		}
		out << "root,0," << maxy<< "," << maxy << "," << "Infinity" << endl;
		posi = posi - 1;
		//out << posi;
		out.close();
		if (posi != -1){
			boardi[avalid[0][posi]][avalid[1][posi]] = yo;
			findmoves1m(avalid[0][posi], avalid[1][posi], boardi, yo, op);
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mains << boardi[i][j];
			}
			mains << endl;
		}
		out.open("temp.txt");
		string str;

		while (getline(out, str))
		{
			mains << str << endl;
		}

	}
}



int main() // main funtion of the program
{
	char boardm[8][8], yo, op;
	fstream input;
	input.open("input.txt");
	out.open("temp.txt", std::fstream::out);
	mains.open("output.txt", std::fstream::out);
	input >> ch;
	input >> you;
	input >> depth;
	depthm = depth;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			input >> board[i][j];
		}
	}
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			boardm[i][j] = board[i][j];

		}
	}
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			board2m[i][j] = boardm[i][j];
			boardi[i][j] = boardm[i][j];
		}
	}
	you1 = you;
	input.close();
	if (you == 'X')
	{
		opponent = 'O';
	}
	else
		opponent = 'X';
	yo = you;
	op = opponent;
	if (ch == 1)
	{
		greedy();
	}
	valid_m(boardm, yo, op, avalid);
	if (ch == 2)
	{
		minimax(boardm, 0, yo, op);
	}
	if (ch == 3)
	{
		alphabeta(boardm, 0, yo, op);
	}
	mains.close();
	out.close();


}

/*out.open("temp.txt");
output.open("output.txt", std::fstream::app);
string str;

while (getline(out, str))
{
output << str<<endl;
}
out.close();
output.close();*/
