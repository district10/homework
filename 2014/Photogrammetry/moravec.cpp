/*
 * Moravec Point Feature Detector
 * @Author: Gnat TANG
 * @Email: gnat_tang@yeah.net
 * @Date: Wednesday, March 26 2014
 * On Github: https://github.com/district10/homework/2014/Photogrammetry/moravec.cpp
 */


#include <stdio.h>
#include <stdlib.h> 



/* ------------------------------------------------------------
 * Define Image Datetype
 * ------------------------------------------------------------*/
typedef struct {
  unsigned char *src;
  int row;
  int col;
} img_t;


/* ------------------------------------------------------------
 * Declare Functions 
 * ------------------------------------------------------------*/
void load_img(img_t &img_src, char *img_path);

void set_moravec_kernel_size(int kernel_size, int size); 
void set_moravec_threshold(int threshold, int th);

void diff_left_right(img_t img_from, img_t &img_to);
void diff_top_bottom(img_t img_from, img_t &img_to);
void diff_topleft_bottomright(img_t img_from, img_t &img_to);
void diff_topright_bottomleft(img_t img_from, img_t &img_to);

void sqsum_left_right(img_t input, int kernel_size);
void sqsum_top_bottom(img_t input, int kernel_size);
void sqsum_topleft_bottomright(img_t input, int kernel_size);
void sqsum_topright_bottomleft(img_t input, int kernel_size);

void four2one(img_t l_r, img_t t_b, img_t lt_br, img_t lr_bl, int k_size);

/* ------------------------------------------------------------
 * Main
 * ------------------------------------------------------------*/
int main(int argc, char **argv)
{
  int moravec_kernel_size;
  int moravec_threshold;

  // images 
  img_t raw_src;

  ///////////////////////////////////////////////////
  /// Load Images and Init Kernel Size and Threshold 
  if (argc == 3) { // Get Parameters from Console
    load_img(&raw_src, argv[1], atoi(argv[2]), atoi(argv[3]));
    set_moravec_kernel_size(&moravec_kernel_size, atoi(argv[4]));
    set_moravec_threshold(&moravec_threshold, atoi(argv[5]));
  } else if (argc == 0) { // Use default(built-in) Params
    set_moravec_threshold(&moravec_threshold, 30);
    set_moravec_kernel_size(&moravec_kernel_size, 7);
    load_img(&raw_src, "lena.raw", row, col);
  } else { // Else? Else Print out Usage!
    printf("============ Moravec Feature Detector ==================\n");
    printf("== Usage: \n");
    printf("==     %s <raw_img_path> <row> <col> <kernel_size> <threshold>\n", argv[0]);
    printf("========================================by Gnat TANG====\n");
  }
  
  img_t raw_diff_l_r, raw_diff_t_b, raw_diff_tl_br, raw_diff_tr_bl; 
  img_t raw_sqsum_l_r, raw_sqsum_t_b, raw_sqsum_tl_br, raw_sqsum_tr_bl;
  img_t raw_max_min;

  diff_left_right(&raw_src, &raw_diff_l_r);
  diff_top_bottom(&raw_src, &raw_diff_t_b);
  diff_topleft_bottomright(&raw_src, &raw_diff_tl_br);
  diff_topright_bottomleft(&raw_src, &raw_diff_tr_bl);

  sqsum_left_right(&raw_diff_l_r, moravec_kernel_size);
  sqsum_top_bottom(&raw_diff_t_b, moravec_kernel_size);
  sqsum_topleft_bottomright(&raw_diff_tl_br, moravec_kernel_size);
  sqsum_topright_bottomleft(&raw_diff_tr_bl, moravec_kernel_size);
  

}




/* ------------------------------------------------------------
 * Implement Functions 
 * ------------------------------------------------------------*/

void load_img(img_t img, char *img_path, int row, int col)
{
  img.row = row;
  img.col = col;
  img.src = (unsigned char *)malloc(sizeof(unsigned char) * row * col); 
  FILE *fp = fopen(img_path, "r");
  if (fp == NULL) {
    perror("Error Opening Raw Image File.\n");
    exit(-1);
  }
  fgets(img.src, row * col, fp);
  
  //for (int i = 0; i < row * col; ++i) {
  //  img.src[i] = file;    
  //}
}

void set_moravec_kernel_size(int size)
{
  if (size % 2 == 1) { // odd kernel size
    moravec_kernel_size = size;
    return;  
  } else { // we don't accept even kernel size
    exit(-1);
  }
}

void set_moravec_threshold(int thresh, int th)
{
  thresh = th;
  return;
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
      img_to.src[i * col + j] = (unsigned char)abs((int)tmp);
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
      img_to.src[i * col + j] = (unsigned char)abs((int)tmp);
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

void sqsum_left_right(img_t in, img_t out, int kernel_size)
{
  out.row = in.row - (kernel_size - 1);
  out.col;
  for (int i = 0; i < in.row; ++i) {
    out.src[i * col] = 0;
    for (int t = 0; t < kernel_size; ++t) {
      out.src[i * col] += in.row[i * col + t];
    }
    for (int j = 0; j < in.col; ++j) {
      static add = ;
      static sub = ;
      out.src[i * col + j] = out.src[i * col + j - 1] - sub + add;
    }
  }
}


void sqsum_top_bottom(img_t in, img_t out, int kernel_size)
{

}
void sqsum_topleft_bottomright(img_t in, img_t out, int kernel_size)
{

}
void sqsum_topright_bottomleft(img_t in, img_t out, int kernel_size)
{

}


void four2one(img_t l_r, img_t t_b, img_t lt_br, img_t lr_bl, int k_size);
