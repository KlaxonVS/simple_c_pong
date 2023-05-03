#ifndef PONG_H
#define PONG_H

#define WIDTH 80
#define HEIGHT 25
#define BALL "@"
#define TOP_BOTTOM "="
#define LEFT_RIGHT " "
#define L_RAKET "]"
#define R_RAKET "["

int random_num(int limit);
int init_vector(int *vec);
void calk_coor_score(int *ball_x, int *vec_x, int *ball_y, int *vec_y, int *l_score, int *r_score,
                     int racket_l, int racket_r);
int winner(int l_score, int r_score);
int linner_with_score(int x_pos, int score_start, int score);
int ball_rackets(int x_pos, int y_pos, int racket_l, int racket_r, int ball_x, int ball_y);
int draw_table(int ball_x, int ball_y, int racket_l, int racket_2, int l_score, int r_score);

#endif