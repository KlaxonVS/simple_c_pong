#include "pong.h"

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int vec_x, vec_y;
    init_vector(&vec_x);
    init_vector(&vec_y);
    int racket_l = 11;
    int racket_r = 11;
    int l_score = 0;
    int r_score = 0;
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
    while (1) {
        calk_coor_score(&ball_x, &vec_x, &ball_y, &vec_y, &l_score, &r_score, racket_l, racket_r);
        erase();
        refresh();
        draw_table(ball_x, ball_y, racket_l, racket_r, l_score, r_score);
        char key = getch();
        while (l_score == 21 || r_score == 21) {
            key = getch();
            if (key == 'q') break;
        }
        if (key == 'q') break;
        if (key == 'a' && racket_l != 1) racket_l--;
        if (key == 'z' && racket_l != 21) racket_l++;
        if (key == 'k' && racket_r != 1) racket_r--;
        if (key == 'm' && racket_r != 21) racket_r++;
    }
    endwin();
    return 0;
}

int random_num(int limit) {
    srand(time(NULL));
    int divisor = RAND_MAX / (limit + 1);
    int result;
    do {
        result = rand() / divisor;
    } while (result > limit);
    return result;
}

int init_vector(int *vec) {
    int random = random_num(1) - 1;
    if (random == 0) {
        *vec = 1;
    } else {
        *vec = -1;
    }
    return 0;
}

void calk_coor_score(int *ball_x, int *vec_x, int *ball_y, int *vec_y, int *l_score, int *r_score,
                     int racket_l, int racket_r) {
    if (*ball_y == 1) *vec_y *= -1;
    if (*ball_y == 23) *vec_y *= -1;
    *ball_x += *vec_x;
    *ball_y += *vec_y;

    if (*ball_x == 76 && (*ball_y >= racket_r && *ball_y <= (racket_r + 2))) {
        *vec_x *= -1;
    } else if (*ball_x >= 77 && (*ball_y < racket_r || *ball_y > (racket_r + 2))) {
        *ball_x = WIDTH / 2;
        *ball_y = HEIGHT / 2;
        *l_score += 1;
    }
    if (*ball_x == 1 && (*ball_y >= racket_l && *ball_y <= (racket_l + 2))) {
        *vec_x *= -1;
    } else if (*ball_x <= 0 && (*ball_y < racket_l || *ball_y > (racket_l + 2))) {
        *ball_x = WIDTH / 2;
        *ball_y = HEIGHT / 2;
        *r_score += 1;
    }
}

int winner(int l_score, int r_score) {
    if (l_score == 21) {
        printw(" Left player is winner!");
    } else if (r_score == 21) {
        printw("Right player is winner!");
    }
    return 0;
}

int linner_with_score(int x_pos, int score_start, int score) {
    if (x_pos >= score_start && x_pos <= score_start + 3) {
        if (score >= 10) printw("%s%d%s", " ", score, " ");
        if (score < 10) printw("%s%d%d%s", " ", 0, score, " ");
    }
    return score_start + 4;
}

int ball_rackets(int x_pos, int y_pos, int racket_l, int racket_r, int ball_x, int ball_y) {
    int racket_l_2 = racket_l + 2;
    int racket_r_2 = racket_r + 2;
    if (x_pos == ball_x && y_pos == ball_y) {
        printw(BALL);
    } else if (x_pos == 0 && y_pos >= racket_l && y_pos <= racket_l_2) {
        printw(L_RAKET);
    } else if (x_pos == 77 && y_pos >= racket_r && y_pos <= racket_r_2) {
        printw(R_RAKET);
    } else {
        printw(" ");
    }
    return 0;
}

int draw_table(int ball_x, int ball_y, int racket_l, int racket_r, int l_score, int r_score) {
    int x_lenght = WIDTH;
    int y_lenght = HEIGHT;
    for (int y_pos = 0; y_pos < y_lenght; y_pos++) {
        if (y_pos == 0 || y_pos == y_lenght - 1) {
            for (int x_pos = 0; x_pos < x_lenght; x_pos++) {
                if (x_pos >= 5 && x_pos <= 8) {
                    x_pos = linner_with_score(x_pos, 5, l_score);
                } else if (x_pos >= 72 && x_pos <= 76) {
                    x_pos = linner_with_score(x_pos, 72, r_score);
                }
                printw(TOP_BOTTOM);
            }
        } else {
            printw(" ");
            for (int x_pos = 0; x_pos < x_lenght - 2; x_pos++) {
                if ((l_score == 21 || r_score == 21) && y_pos == 10 && x_pos == 21) {
                    winner(l_score, r_score);
                    x_pos = 44;
                }
                ball_rackets(x_pos, y_pos, racket_l, racket_r, ball_x, ball_y);
            }
            printw(" ");
        }
        printw("\n");
    }
    return 0;
}