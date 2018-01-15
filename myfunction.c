typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;


/* Compute min and max of two integers, respectively */
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
/*void initialize_pixel_sum(pixel_sum *sum) {
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}*/

/*
 * assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
 *//*
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum, int kernelScale) {
    // divide by kernel's weight
    sum.red = sum.red / kernelScale;
    sum.green = sum.green / kernelScale;
    sum.blue = sum.blue / kernelScale;
    // truncate each pixel's color values to match the range [0,255]
    current_pixel->red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel->green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel->blue = (unsigned char) (min(max(sum.blue, 0), 255));
    return;
}*/

/*
* sum_pixels_by_weight - Sums pixel values, scaled by given number
*//*
static void sum_pixels_by_weight(pixel_sum *sum, pixel p, int weight) {
    sum->red += ((int) p.red) * weight;
    sum->green += ((int) p.green) * weight;
    sum->blue += ((int) p.blue) * weight;
    sum->num++;
    return;
}*/

/*
 *  Applies kernel for pixel at (i,j)
 */
/*static pixel applyKernel(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

    int ii, jj;
    int currRow, currCol;
    pixel_sum sum;
    pixel current_pixel;

    sum.red = sum.green = sum.blue = 0;
   // sum.num = 0;

    //initialize_pixel_sum(&sum);

    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) {
        for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {

            int kRow, kCol;

            // compute row index in kernel
            if (ii < i) {
                kRow = 0;
            } else if (ii > i) {
                kRow = 2;
            } else {
                kRow = 1;
            }

            // compute column index in kernel
            if (jj < j) {
                kCol = 0;
            } else if (jj > j) {
                kCol = 2;
            } else {
                kCol = 1;
            }

            // apply kernel on pixel at [ii,jj]
            //sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
            pixel p = src[calcIndex(ii, jj, dim)];
            int weight = kernel[kRow][kCol];
            sum.red += ((int) p.red) * weight;
            sum.green += ((int) p.green) * weight;
            sum.blue += ((int) p.blue) * weight;
           // sum.num++;
        }
    }

    // assign kernel's result to pixel at [i,j]
    // assign_sum_to_pixel(&current_pixel, sum, kernelScale);
    //todo: remove call to func assign_sum_to_pixel

    // divide by kernel's weight
    sum.red = sum.red / kernelScale;
    sum.green = sum.green / kernelScale;
    sum.blue = sum.blue / kernelScale;

    // truncate each pixel's color values to match the range [0,255]
    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
    return current_pixel;
}*/

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {
//todo: get ride of repptive calculations
    int i, j, halfK, dimMinusHalfKernal;
    halfK = kernelSize / 2;
    dimMinusHalfKernal = dim - halfK;
    for (i = halfK ; i < dimMinusHalfKernal; i++) {
        for (j =  halfK ; j < dimMinusHalfKernal ; j++) {

            //*************

            int ii, jj;
            //  int currRow, currCol;
            pixel_sum sum;
            pixel current_pixel;

            sum.red = sum.green = sum.blue = 0;
            //sum.num = 0;

            //initialize_pixel_sum(&sum);

            for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) {
                for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {

                    int kRow, kCol;

                    // compute row index in kernel
                    if (ii < i) {
                        kRow = 0;
                    } else if (ii > i) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }

                    // compute column index in kernel
                    if (jj < j) {
                        kCol = 0;
                    } else if (jj > j) {
                        kCol = 2;
                    } else {
                        kCol = 1;
                    }

                    // apply kernel on pixel at [ii,jj]
                    //sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
                    pixel p = src[calcIndex(ii, jj, dim)];
                    int weight = kernel[kRow][kCol];
                    sum.red += ((int) p.red) * weight;
                    sum.green += ((int) p.green) * weight;
                    sum.blue += ((int) p.blue) * weight;
                   // sum.num++;
                }
            }

            // assign kernel's result to pixel at [i,j]
            // assign_sum_to_pixel(&current_pixel, sum, kernelScale);
            //todo: remove call to func assign_sum_to_pixel

            // divide by kernel's weight
            //todo: kernal size is 1 so i deleted it
           /* sum.red = sum.red / kernelScale;
            sum.green = sum.green / kernelScale;
            sum.blue = sum.blue / kernelScale;*/

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            //return current_pixel;



            //****

            //todo: remove call to applyKernel
            dst[calcIndex(i, j, dim)] = current_pixel;//applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
        }
    }
}
/*
void charsToPixels(Image *charsImg, pixel* pixels) {
    int row, col,rn;
    rn = 0;
    for (row = 0 ; row < m ; row++) {
        for (col = 0 ; col < n ; col++) {
            pixels[row*n + col].red = image->data[3*row*n + 3*col];
            pixels[row*n + col].green = image->data[3*row*n + 3*col + 1];
            pixels[row*n + col].blue = image->data[3*row*n + 3*col + 2];
        }
    }
}
void pixelsToChars(pixel* pixels, Image *charsImg) {
    int row, col;
    for (row = 0 ; row < m ; row++) {
        for (col = 0 ; col < n ; col++) {
            image->data[3*row*n + 3*col] = pixels[row*n + col].red;
            image->data[3*row*n + 3*col + 1] = pixels[row*n + col].green;
            image->data[3*row*n + 3*col + 2] = pixels[row*n + col].blue;
        }
    }
}
void copyPixels(pixel* src, pixel* dst) {
    int row, col;
    for (row = 0 ; row < m ; row++) {
        for (col = 0 ; col < n ; col++) {
            dst[row*n + col].red = src[row*n + col].red;
            dst[row*n + col].green = src[row*n + col].green;
            dst[row*n + col].blue = src[row*n + col].blue;
        }
    }
}
*/


void doConvolutionBlur(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {
/*
    pixel* pixelsImg = malloc(m*n*sizeof(pixel));
    pixel* backupOrg = malloc(m*n*sizeof(pixel));
    charsToPixels(image, pixelsImg);
    copyPixels(pixelsImg, backupOrg);
*/
    //todo: delete these stupid conversions.
    int x = m*n*3;
    pixel* pixelsImg = (pixel*)image->data;
    pixel* backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg , x);

    // smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);
    //todo: get ride of calling to smooth func

    //todo: get ride of repptive calculations
    int i, j, halfK, dimMinusHalfKernal;
    halfK = kernelSize / 2;
    dimMinusHalfKernal = m - halfK;
    for (i = halfK ; i < dimMinusHalfKernal; i++) {
        for (j =  halfK ; j < dimMinusHalfKernal ; j++) {

            //*************



            int ii, jj;
            int currRow, currCol;
            pixel_sum sum;
            pixel current_pixel;

            sum.red = sum.green = sum.blue = 0;
          //  sum.num = 0;

            //initialize_pixel_sum(&sum);

            for(ii = max(i-1, 0); ii <= min(i+1, m-1); ii++) {
                jj = max(j-1, 0);
               /* for(jj = max(j-1, 0); jj <= min(j+1, m-1); jj++) {

                    *//*int kRow, kCol;
                    // compute row index in kernel
                    if (ii < i) {
                        kRow = 0;
                    } else if (ii > i) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }
                    // compute column index in kernel
                    if (jj < j) {
                        kCol = 0;
                    } else if (jj > j) {
                        kCol = 2;
                    } else {
                        kCol = 1;
                    }*//*

                    // apply kernel on pixel at [ii,jj]
                    //sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
                    pixel p = backupOrg[calcIndex(ii, jj, m)];
                    //int weight = 1;//kernel[kRow][kCol];
                    sum.red += ((int) p.red);
                    sum.green += ((int) p.green);
                    sum.blue += ((int) p.blue);
                   // sum.num++;
                }*/
                int x= calcIndex(ii, jj, m);
                pixel pixel1 = backupOrg[x];
                pixel pixel2 = backupOrg[x+1];
                pixel pixel3 = backupOrg[x+2];

                sum.red += ((int) pixel1.red) +((int) pixel2.red) + ((int)pixel3.red);
                sum.green += ((int) pixel1.green) +((int) pixel2.green) + ((int)pixel3.green);
                sum.blue += ((int) pixel1.blue) +((int) pixel2.blue) + ((int)pixel3.blue);
            }

            // assign kernel's result to pixel at [i,j]
            // assign_sum_to_pixel(&current_pixel, sum, kernelScale);
            //todo: remove call to func assign_sum_to_pixel

            // divide by kernel's weight
            sum.red = sum.red / kernelScale;
            sum.green = sum.green / kernelScale;
            sum.blue = sum.blue / kernelScale;

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            //return current_pixel;



            //****

            //todo: remove call to applyKernel
            pixelsImg[calcIndex(i, j, m)] = current_pixel;//applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
        }
    }





    // pixelsToChars(pixelsImg, image);

    //free(pixelsImg);
    free(backupOrg);
}





void doConvolutionSharpen(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {
/*
    pixel* pixelsImg = malloc(m*n*sizeof(pixel));
    pixel* backupOrg = malloc(m*n*sizeof(pixel));
    charsToPixels(image, pixelsImg);
    copyPixels(pixelsImg, backupOrg);
*/
    //todo: delete these stupid conversions.
    int x = m*n*3;
    pixel* pixelsImg = (pixel*)image->data;
    pixel* backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg , x);


    //smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);


    //todo: get ride of repptive calculations
    int i, j, halfK, dimMinusHalfKernal;
    halfK = kernelSize / 2;
    dimMinusHalfKernal = m - halfK;
    for (i = halfK ; i < dimMinusHalfKernal; i++) {
        for (j =  halfK ; j < dimMinusHalfKernal ; j++) {

            //*************

            int ii, jj;
            //  int currRow, currCol;
            pixel_sum sum;
            pixel current_pixel;

            sum.red = sum.green = sum.blue = 0;
            //sum.num = 0;

            //initialize_pixel_sum(&sum);
            int weight;
            int once =0;
            jj = max(j-1, 0);

            for(ii = max(i-1, 0); ii <= min(i+1, m-1); ii++) {
                ++once;
               /* for(jj = max(j-1, 0); jj <= min(j+1, m-1); jj++) {
                   // int kRow, kCol;
                    weight = -1;
                    //todo: change the weight only if it the middle
                    // compute row index in kernel
                    if (ii==i && jj==j)
                    {
                        weight =9;
                    }
                   *//* if (ii < i) {
                        kRow = 0;
                    } else if (ii > i) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }

                    // compute column index in kernel
                    if (jj < j) {
                        kCol = 0;
                    } else if (jj > j) {
                        kCol = 2;
                    } else {
                        kCol = 1;
                    }*//*

                    // apply kernel on pixel at [ii,jj]
                    //sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
                   *//* pixel p = backupOrg[calcIndex(ii, jj, m)];

                    sum.red += ((int) p.red) * weight;
                    sum.green += ((int) p.green) * weight;
                    sum.blue += ((int) p.blue) * weight;*//*
                    // sum.num++;
                }*/

                int x= calcIndex(ii, jj, m);
                pixel pixel1 = backupOrg[x];
                pixel pixel2 = backupOrg[x+1];
                pixel pixel3 = backupOrg[x+2];
                int multMiddlePharam=-1;
                if(once==2){
                    multMiddlePharam =9;
                }
                weight =-1;

                sum.red += ((int) pixel1.red)* weight +((int) pixel2.red)* multMiddlePharam + ((int)pixel3.red)* weight;
                sum.green += ((int) pixel1.green)* weight +((int) pixel2.green)* multMiddlePharam + ((int)pixel3.green)* weight;
                sum.blue += ((int) pixel1.blue)* weight +((int) pixel2.blue)* multMiddlePharam + ((int)pixel3.blue)* weight;



                /*int x= calcIndex(ii, jj, m);
                pixel pixel1 = backupOrg[x];
                pixel pixel2 = backupOrg[x+1];
                pixel pixel3 = backupOrg[x+2];

                sum.red += ((int) pixel1.red) +((int) pixel2.red) + ((int)pixel3.red);
                sum.green += ((int) pixel1.green) +((int) pixel2.green) + ((int)pixel3.green);
                sum.blue += ((int) pixel1.blue) +((int) pixel2.blue) + ((int)pixel3.blue);*/

            }

            // assign kernel's result to pixel at [i,j]
            // assign_sum_to_pixel(&current_pixel, sum, kernelScale);
            //todo: remove call to func assign_sum_to_pixel

            // divide by kernel's weight
            //todo: kernal size is 1 so i deleted it
            /* sum.red = sum.red / kernelScale;
             sum.green = sum.green / kernelScale;
             sum.blue = sum.blue / kernelScale;*/

            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            //return current_pixel;



            //****

            //todo: remove call to applyKernel
            pixelsImg[calcIndex(i, j, m)] = current_pixel;//applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
        }
    }





    // pixelsToChars(pixelsImg, image);

    //free(pixelsImg);
    free(backupOrg);
}


void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName) {

    /*
    * [1, 1, 1]
    * [1, 1, 1]
    * [1, 1, 1]
    */
    int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    /*
    * [-1, -1, -1]
    * [-1, 9, -1]
    * [-1, -1, -1]
    */
    int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

    // blur image
    doConvolutionBlur(image, 3, blurKernel, 9);

    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);

    //smooth(m, backupOrg, pixelsImg, kernelSize, sharpKernel, 1);

    // sharpen the resulting image
    doConvolutionSharpen(image, 3, sharpKernel, 1);

    // write result image to file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}