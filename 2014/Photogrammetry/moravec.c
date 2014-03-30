/*
 * Moravec Point Feature Detector
 * @Author: Gnat TANG
 * @Email: gnat_tang@yeah.net
 * @Date: Wednesday, March 26 2014
 * On Github: https://github.com/district10/homework/2014/Photogrammetry/moravec.cpp
 */


#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>



/* ============================================================
 * = Define Image Datatype
 * ============================================================*/
typedef struct {
  unsigned char *src;
  int row;
  int col;
} img_t;



/* ============================================================
 * = Declare Functions
 * ============================================================*/
void load_img(img_t img, char *path, int row, int col);
void save_img(img_t img, char *path);

void set_moravec_kernel_size(int k_size, int size);
void set_moravec_threshold(int thresh, int th);

void diff_left_right(img_t in, img_t out);
void diff_top_bottom(img_t in, img_t out);
void diff_topleft_bottomright(img_t in, img_t out);
void diff_topright_bottomleft(img_t in, img_t out);

void sqsum_left_right(img_t in, img_t out, int kernel_size);
void sqsum_top_bottom(img_t in, img_t out, int kernel_size);
void sqsum_topleft_bottomright(img_t in, img_t out, int kernel_size);
void sqsum_topright_bottomleft(img_t in, img_t out, int kernel_size);

void four2one(img_t out, img_t l_r, img_t t_b, img_t lt_br, img_t lr_bl);
void apply_threshold(img_t in, img_t out, int threshold);



/* ============================================================
 * = Main
 * ============================================================*/
int main(int argc, char **argv)
{
  // Define Kernel Size and Moravec Threshold
  int moravec_kernel_size;
  int moravec_threshold;

  // Define raw-image holder 
  img_t raw_src;

  /* ------------------------------------------------------------
   * Load Image and Init Kernel Size and Threshold
   * ------------------------------------------------------------*/
  if (argc == 6) { // Get Parameters from Console
    load_img(&raw_src, argv[1], atoi(argv[2]), atoi(argv[3]));
    set_moravec_kernel_size(&moravec_kernel_size, atoi(argv[4]));
    set_moravec_threshold(&moravec_threshold, atoi(argv[5]));
  } else if (argc == 1) { // Use default(built-in) Params
    load_img(&raw_src, "lena.raw", 300, 300);
    set_moravec_threshold(&moravec_threshold, 30);
    set_moravec_kernel_size(&moravec_kernel_size, 7);
  } else { // Else? Else Print out Usage and then exit!
    printf("============ Moravec Feature Detector ==================\n");
    printf("== Usage: \n");
    printf("==     %s <raw_img_path> <row> <col> <kernel_size> <threshold>\n", argv[0]);
    printf("========================================by Gnat TANG====\n");
    return -1;
  }
  
  /* ------------------------------------------------------------
   *  Define Variables and then Processing
   * ------------------------------------------------------------*/
  // Differences
  img_t raw_diff_l_r, raw_diff_t_b, raw_diff_tl_br, raw_diff_tr_bl;
  // Square Sums of Differences
  img_t raw_sqsum_l_r, raw_sqsum_t_b, raw_sqsum_tl_br, raw_sqsum_tr_bl; 
  // Min of Squares
  img_t output_sqsum_min; 
  // output: as a mask
  img_t output_01_mask; 

  // DIFF 
  diff_left_right(&raw_src,
		  &raw_diff_l_r);
  diff_top_bottom(&raw_src,
		  &raw_diff_t_b);
  diff_topleft_bottomright(&raw_src,
			   &raw_diff_tl_br);
  diff_topright_bottomleft(&raw_src,
			   &raw_diff_tr_bl);
  // SQSUM
  sqsum_left_right(&raw_diff_l_r,
		   &raw_sqsum_l_r,
		   moravec_kernel_size);
  sqsum_top_bottom(&raw_diff_t_b,
		   &raw_sqsum_t_b,
		   moravec_kernel_size);
  sqsum_topleft_bottomright(&raw_diff_tl_br,
			    &raw_sqsum_tl_br,
			    moravec_kernel_size);
  sqsum_topright_bottomleft(&raw_diff_tr_bl,
			    &raw_sqsum_tr_bl,
			    moravec_kernel_size);
  // MIN
  four2one(&output_sqsum_min, 
	   &raw_sqsum_l_r,
	   &raw_sqsum_t_b,
	   &raw_sqsum_tl_br,
	   &raw_sqsum_tr_bl);
 
  apply_threshold(&output_sqsum_min,
		  &output_01_mask,
		  moravec_threshold);

  char *outpath = "output.raw";
  save_img(&output_01_mask,
	   outpath);

  return 0;
}



/* ============================================================
 * = Implement Functions
 * ============================================================*/
void load_img(img_t img, char *path, int row, int col)
{
  img.row = row;
  img.col = col;
  img.src = (unsigned char *)malloc(sizeof(unsigned char) * img.row * img.col); 
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    perror("Error Opening Raw Image File.\n");
    exit(-1);
  }
  fgets(img.src, img.row * img.col, fp);
  fclose(fp);
  return;
}


void save_img(img_t img, char *path)
{
  FILE *fp = fopen(img_path, "w");
  if (fp == NULL) {
    perror("Error Opening Raw Image File.\n");
    exit(-1);
  }
  fputs(img.src, fp);
  fclose(fp);
  return;
}


void set_moravec_kernel_size(int k_size, int size)
{
  // odd kernel size 
  k_size = size % 2 == 1? size : size + 1;
  if (k_size < 0 || k_size > 10) {
    k_size = 7;
  }
  return;
}


void set_moravec_threshold(int thresh, int th)
{
  thresh = (th < 200 && th > 10)? th : 20;
  return;
}


void diff_left_right(img_t in, img_t out)
{
  int row = in.row;
  int col = in.col - 1;
  out.row = row;
  out.col = col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = in.src[i * in.col + j + 1] - in.src[i * in.col + j]; 
      out.src[i * col + j] = (unsigned char)abs((int)tmp);
    }
  }
  return; 
}


void diff_top_bottom(img_t in, img_t out)
{
  int row = in.row - 1;
  int col = in.col;
  out.row = row;
  out.col = col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = in.src[(i + 1) * in.col  + j] - in.src[i * in.col + j];
      out.src[i * col + j] = (unsigned char)abs((int)tmp);
    }
  }
  return; 
}


void diff_topleft_bottomright(img_t in, img_t out);
{
  int row = in.row - 1;
  int col = in.col - 1;
  out.row = row;
  out.col = col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = in.src[(i + 1) * in.col + j + 1] - in.src[i * in.col + j];
      out.src[i * col + j] = (unsigned char)abs((int)tmp);
    }
  }
  return; 
}


void diff_topright_bottomleft(img_t in, img_t out);
{
  int row = in.row - 1;
  int col = in.col - 1;
  out.row = row;
  out.col = col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp;
      tmp = in.src[(i + 1) * in.col + j] - in.src[i * in.col + j + 1];
      out.src[i * col + j] = (unsigned char)abs((int)tmp);
    }
  }
  return; 
}


void sqsum_left_right(img_t in, img_t out, int kernel_size)
{
  int row = in.row;
  int col = in.col + 1; 
  out.row = row - (kernel_size - 1);
  out.col = col - (kernel_size - 1);
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  int max_offset = (kernel_size - 1) / 2;
  int tmp_sqsum = 0;
  for (int i = 0; i < out.row; ++i) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum first kernel_size elems to tmp_sqsum
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[(i + max_offset) * in.col + k] * in.src[(i + max_offset) * in.col + k];
    }
    // assign first elem of the ith row
    out.src[i * col + 0] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
    // assign other elems
    for (int j = 1; j < out.col; ++j) {
      static int add = in.src[(i + max_offset) * in.col + j + max_offset + max_offset];
      static int sub = in.src[(i + max_offset) * in.col + j + max_offset - max_offset];
      tmp_sqsum = tmp_sqsum - sub * sub + add * add;
      out.src[i * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
    }
  }
  return;
}


void sqsum_top_bottom(img_t in, img_t out, int kernel_size)
{
  int row = in.row + 1;
  int col = in.col; 
  out.row = row - (kernel_size - 1);
  out.col = col - (kernel_size - 1);
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  int max_offset = (kernel_size - 1) / 2;
  int tmp_sqsum = 0;

  // first row
  for (int j = 0; j < out.col; ++j) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum kernel_size elems,
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[k * in.col + j + max_offset] * in.src[k * in.col + j + max_offset];
    }
    // assign the first row
    out.src[0 * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
  }

  // others rows
  for (int i = 1; j < out.row; ++i) {
    for (int j = 0; j < out.col; ++j) {
      tmp_sqsum = out.src[(i - 1) * col + j]; // assign sqsum to previous row 
      static int add = in.src[(i + max_offse + max_offset) * in.col + j + max_offset];
      static int sub = in.src[(i + max_offse - max_offset) * in.col + j + max_offset];
      tmp_sqsum = tmp_sqsum - sub * sub + add * add;
      out.src[i * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
    }
  }
  return;
}


void sqsum_topleft_bottomright(img_t in, img_t out, int kernel_size)
{
  int row = in.row + 1;
  int col = in.col + 1; 
  out.row = row - (kernel_size - 1);
  out.col = col - (kernel_size - 1);
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  int max_offset = (kernel_size - 1) / 2;
  int tmp_sqsum = 0;

  // first row
  for (int j = 0; j < out.col; ++j) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum kernel_size elems,
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[k * in.col + j + k] * in.src[k * in.col + j + k];
    }
    // assign the first row
    out.src[0 * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
  }

  // first col, (except the first elem, aka topleft elem)
  for (int i = 1; i < out.row; ++i) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum kernel_size elems,
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[(i + k) * in.col + k] * in.src[(i + k) * in.col + k];
    }
    // assign the first col
    out.src[i * col + 0] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
  }

  // others elems
  for (int i = 1; j < out.row; ++i) {
    for (int j = 1; j < out.col; ++j) {
      tmp_sqsum = out.src[(i - 1) * col + j - 1]; // assign sqsum to its parent(northwest)
      static int add = in.src[(i + max_offse + max_offset) * in.col + j + max_offset];
      static int sub = in.src[(i + max_offse - max_offset) * in.col + j + max_offset];
      tmp_sqsum = tmp_sqsum - sub * sub  + add * add;
      out.src[i * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
    }
  }
  return;
}


void sqsum_topright_bottomleft(img_t in, img_t out, int kernel_size)
{
  int row = in.row + 1;
  int col = in.col + 1; 
  out.row = row - (kernel_size - 1);
  out.col = col - (kernel_size - 1);
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  int max_offset = (kernel_size - 1) / 2;
  int tmp_sqsum = 0;

  // first row
  for (int j = out.col - 1; j >= 0; --j) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum kernel_size elems,
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[k * in.col + j + max_offset + max_offset  - k] * in.src[k * in.col + j + max_offset + max_offset  - k];
    }
    // assign the first row
    out.src[0 * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
  }

  // last col, (except the first elem, aka topright elem)
  for (int i = 1; i < out.row; ++i) {
    // init tmp sqsum to 0
    tmp_sqsum = 0;
    // sum kernel_size elems,
    for (int k = 0; k < kernel_size; ++t) {
      tmp_sqsum += in.src[(i - max_offset + k) * in.col + in.col - 1 - k] * in.src[(i - max_offset + k) * in.col + in.col - 1 - k];
    }
    // assign the first col
    out.src[i * col + i] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
  }

  // others elems
  for (int i = 1; j < out.row; ++i) {
    for (int j = out.col - 1; j >= 0; ++j) {
      tmp_sqsum = out.src[(i - 1) * col + j + 1]; // assign sqsum to its parent(northeast)
      static int add = in.src[(i + max_offset + max_offset) * in.col + j + max_offset];
      static int sub = in.src[(i + max_offset - max_offset) * in.col + j + max_offset];
      tmp_sqsum = tmp_sqsum - sub * sub + add * add;
      out.src[i * col + j] = tmp_sqsum < 255? (unsigned char)tmp_sqsum : 255;
    }
  }
  return;
}


void four2one(img_t out, img_t l_r, img_t t_b, img_t lt_br, img_t lr_bl)
{
  int row = l_r.row;
  int col = l_r.col;
  assert(row == t_b.row &&
	 row == lt_br.row &&
	 row == lr_bl.row &&
	 "Same num of row.");
  assert(col == t_b.col &&
	 col == lt_br.col &&
	 col == lr_bl.col &&
	 "Same num of col.");
  out.row = row;
  out.col = col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      static unsigned char tmp1, tmp2, tmp3;
      tmp1 = l_r < lt_br? l_r : lt_br;
      tmp2 = t_b < lr_bl? t_b : lr_bl;
      tmp3 = tmp1 < tmp2? tmp1 : tmp2;
      out.src[i * col + j] = tmp3;
    }  
  }
  return;
}


void apply_threshold(img_t in, img_t out, int threshold)
{
  out.row = in.row;
  out.col = in.col;
  out.src = (unsigned char *)malloc(sizeof(unsigned char) * out.row * out.col); 
  
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      out.src[i * col + j] = in.src[i * col + j] > threshold? 0 : 1; 
    }
  }
  return;
}
