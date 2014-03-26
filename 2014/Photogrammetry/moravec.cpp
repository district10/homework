/*
 * Moravec Point Feature Detector
 * @Author: Gnat TANG
 * @Email: gnat_tang@yeah.net
 * @Date: Wednesday, March 26 2014
 * On Github: https://github.com/district10/homework/2014/Photogrammetry/moravec.cpp
 */

typedef struct {
  unsigned char *src;
  int row;
  int col;
} img_t;


/* ------------------------------------------------------------
 * Global variables
 * ------------------------------------------------------------*/

// images 
img_t raw_src;
img_t raw_diff_l_f, raw_diff_t_b, raw_diff_tl_br, raw_diff_tr_bl; 
img_t raw_sqsum_l_f, raw_sqsum_t_b, raw_sqsum_tl_br, raw_sqsum_tr_bl;
img_t raw_output;

// moravec kernel size
int moravec_kernel_size;

/* ------------------------------------------------------------
 * Declare Functions 
 * ------------------------------------------------------------*/

void load_img(img_t &img_src, char *img_path);
bool set_moravec_kernel_size(int size); 

void diff_left_right(img_t img_from, img_t &img_to);
void diff_top_bottom(img_t img_from, img_t &img_to);
void diff_topleft_bottomright(img_t img_from, img_t &img_to);
void diff_topright_bottomleft(img_t img_from, img_t &img_to);

void sqsum_left_right(img_t input, int kernel_size);
void sqsum_top_bottom(img_t input, int kernel_size);
void sqsum_topleft_bottomright(img_t input, int kernel_size);
void sqsum_topright_bottomleft(img_t input, int kernel_size);

#include <iostream>
#include <cassert>
#include <map>
#include <stringstream>
#include <stdio.h>
 
using namespace std;

/* ------------------------------------------------------------
 * Main, take in img path 
 * ------------------------------------------------------------*/
int main(int argc, char **argv)
{
  if (argc == 3) {
    stringstream ss;
    int row, col, k_size;
    ss << argv[2]; ss >> row;
    ss << argv[3]; ss >> col;
    ss << argv[4]; ss >> k_size; set_moravec_kernel_size(k_size);
    load_img(&raw_src, argv[1], row, col);
  }
  

}




/* ------------------------------------------------------------
 * Implement Functions 
 * ------------------------------------------------------------*/

void load_img(img_t img_src, char *img_path, int row, int col)
{
  img_src.row = row;
  img_src.col = col;
  img_src.src = (unsigned char *)malloc(sizeof(unsigned char) * row * col); 
  FILE file;
  file = fopen(img_path, "r"); 
  for (int i = 0; i < row * col; ++i) {
    img_src.src[i] = file;    
  }
}

bool set_moravec_kernel_size(int size)
{
  if (size % 2 == 1) { // odd kernel size
    moravec_kernel_size = size;
    return TRUE;  
  } else { // we don't accept even kernel size
    return FALSE;
  }
}

void diff_left_right(img_t img_from, img_t img_to)
{
  int row = img_from.row;
  int col = img_from.col - 1;
  img_to.row = row;
  img_to.col = col;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = img_from.src[i * (col + 1) + j + 1] - img_from.src[i * (col + 1) + j]; 
      img_to.src[i * col + j] = abs(tmp);
    }
  }
}



void diff_top_bottom(img_t img_from, img_t img_to)
{
  int row = img_from.row - 1;
  int col = img_from.col;
  img_to.row = row;
  img_to.col = col;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = img_from.src[(i + 1) * col + j] - img_from.src[i * col + j];
      img_to.src[i * col + j] = abs(tmp);
    }
  }
}


void diff_topleft_bottomright(img_t img_from, img_t img_to);
{
  int row = img_from.row - 1;
  int col = img_from.col - 1;
  img_to.row = row;
  img_to.col = col;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = img_from.src[(i + 1) * col + j + 1] - img_from.src[i * col + j];
      img_to.src[i * col + j] = abs(tmp);
    }
  }
}


void diff_topright_bottomleft(img_t img_from, img_t img_to);
{
  int row = img_from.row - 1;
  int col = img_from.col - 1;
  img_to.row = row;
  img_to.col = col;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = img_from.src[(i  1) * col + j + 1] - img_from.src[i * col + j];
      img_to.src[i * col + j] = abs(tmp);
    }
  }
}

void sqsum_left_right(img_t input, int kernel_size);


void sqsum_top_bottom(img_t input, int kernel_size);
void sqsum_topleft_bottomright(img_t input, int kernel_size);
void sqsum_topright_bottomleft(img_t input, int kernel_size);
