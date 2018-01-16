//316584960 Liz Aharonian
//todo:handle magic numbers!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
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


/* Compute min and max of two integers, respectively
 * I made these functions because macros are much more efficient then functions */
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
#define WEIGHT_SHARPEN -1
#define WEIGHT_MIDDLE 9


void doConvolutionBlur(Image *image, int kernelSize, int kernelScale) {
    /*I got ride of pixelsImg function and replaced it with casting of image->data
     *by these and by using memcpy func i got ride of:
     *charsToPixels, pixelsToChars, copyPixels because they are no necessary anymore
     *got ride of repetitive calculations using x param*/
    register int x = m * n * 3;
    register pixel *pixelsImg = (pixel *) image->data;
    register pixel *backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg, x);
    /*smooth function is here instead of calling the
     *function with params, because it's much faster to update these values here
     * passing the params cost running time*/
    register int i, j, halfK, dimMinusHalfKernal;
    //calculation of kernalSize/2 was deleted because it's always 1 in our case
    halfK = 1;
    //got ride of repetitive calculations using dimMinusHalfKernal param
    dimMinusHalfKernal = m - halfK;
    for (i = halfK; i < dimMinusHalfKernal; ++i) {
        for (j = halfK; j < dimMinusHalfKernal; ++j) {
            int ii, jj;
            pixel_sum sum;
            pixel current_pixel;
            /*initialize_pixel_sum function is here instead of calling the
             * function with pointer, because it's much faster to update these values here*/
            sum.red = sum.green = sum.blue = 0;
            /*applyKernel function is here instead of calling the function with params
             * in addition I am using Loop unrolling to update the values,
             * it's helps cpu parallel it's actions*/
            ii = max(i - 1, 0);
            jj = max(j - 1, 0);
            int x = calcIndex(ii, jj, m);
            pixel pixel1 = backupOrg[x];
            pixel pixel2 = backupOrg[x + 1];
            pixel pixel3 = backupOrg[x + 2];
            int xm = x + m;
            pixel pixel4 = backupOrg[xm];
            pixel pixel5 = backupOrg[xm + 1];
            pixel pixel6 = backupOrg[xm + 2];
            int xmm = xm + m;
            pixel pixel7 = backupOrg[xmm];
            pixel pixel8 = backupOrg[xmm + 1];
            pixel pixel9 = backupOrg[xmm + 2];
            /*sum_pixels_by_weight function is here instead of calling the
            * function with params, because it's much faster to update these values here*/
            sum.red += ((int) pixel1.red) + ((int) pixel2.red) + ((int) pixel3.red);
            sum.green += ((int) pixel1.green) + ((int) pixel2.green) + ((int) pixel3.green);
            sum.blue += ((int) pixel1.blue) + ((int) pixel2.blue) + ((int) pixel3.blue);

            sum.red += ((int) pixel4.red) + ((int) pixel5.red) + ((int) pixel6.red);
            sum.green += ((int) pixel4.green) + ((int) pixel5.green) + ((int) pixel6.green);
            sum.blue += ((int) pixel4.blue) + ((int) pixel5.blue) + ((int) pixel6.blue);

            sum.red += ((int) pixel7.red) + ((int) pixel8.red) + ((int) pixel9.red);
            sum.green += ((int) pixel7.green) + ((int) pixel8.green) + ((int) pixel9.green);
            sum.blue += ((int) pixel7.blue) + ((int) pixel8.blue) + ((int) pixel9.blue);
            /*assign kernel's result to pixel at [i,j]
            *assign_sum_to_pixel function is here instead of calling the
            * function with params, because it's much faster to update these values here*/
            sum.red = sum.red / kernelScale;
            sum.green = sum.green / kernelScale;
            sum.blue = sum.blue / kernelScale;
            // truncate each pixel's color values to match the range [0,255]
            // max calculation was deleted because blur RGB is always positive
            current_pixel.red = (unsigned char) min(sum.red, 255);
            current_pixel.green = (unsigned char) min(sum.green, 255);
            current_pixel.blue = (unsigned char) min(sum.blue, 255);
            pixelsImg[calcIndex(i, j, m)] = current_pixel;//applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
        }
    }
    free(backupOrg);
}

void doConvolutionSharpen(Image *image, int kernelSize, int kernelScale) {
    /*I got ride of pixelsImg function and replaced it with casting of image->data
     *by these and by using memcpy func i got ride of:
     *charsToPixels, pixelsToChars, copyPixels because they are no necessary anymore
     *in addition, I got ride of repetitive calculations using dimMinusHalfKernal and x param*/
    register int x = m * n * 3;
    register pixel *pixelsImg = (pixel *) image->data;
    register pixel *backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg, x);
    register int i, j, halfK, dimMinusHalfKernal;
    //calculation of kernalSize/2 was deleted because it's always 1 in our case
    halfK = 1;
    dimMinusHalfKernal = m - halfK;
    for (i = halfK; i < dimMinusHalfKernal; ++i) {
        for (j = halfK; j < dimMinusHalfKernal; ++j) {
            int ii, jj;
            pixel_sum sum;
            pixel current_pixel;
            /*initialize_pixel_sum function is here instead of calling the
             * function with pointer, because it's much faster to update these values here*/
            sum.red = sum.green = sum.blue = 0;
            /*applyKernel function is here instead of calling the function with params
            * in addition I am using Loop unrolling to update the values,
            * it's helps cpu parallel it's actions*/
            jj = max(j - 1, 0);
            ii = max(i - 1, 0);

            int x = calcIndex(ii, jj, m);
            pixel pixel1 = backupOrg[x];
            pixel pixel2 = backupOrg[x + 1];
            pixel pixel3 = backupOrg[x + 2];
            int xm = x + m;
            pixel pixel4 = backupOrg[xm];
            pixel pixel5 = backupOrg[xm + 1];
            pixel pixel6 = backupOrg[xm + 2];
            int xmm = xm + m;
            pixel pixel7 = backupOrg[xmm];
            pixel pixel8 = backupOrg[xmm + 1];
            pixel pixel9 = backupOrg[xmm + 2];
            /*sum_pixels_by_weight function is here instead of calling the
            * function with params, because it's much faster to update these values here
             * in addition I update the weight using my defines instead of using the matrix
             * because define is much faster then memory access to matrix*/
            sum.red += ((int) pixel1.red) * WEIGHT_SHARPEN + ((int) pixel2.red) * WEIGHT_SHARPEN + ((int) pixel3.red) * WEIGHT_SHARPEN;
            sum.green += ((int) pixel1.green) * WEIGHT_SHARPEN + ((int) pixel2.green) * WEIGHT_SHARPEN + ((int) pixel3.green) * WEIGHT_SHARPEN;
            sum.blue += ((int) pixel1.blue) * WEIGHT_SHARPEN + ((int) pixel2.blue) * WEIGHT_SHARPEN + ((int) pixel3.blue) * WEIGHT_SHARPEN;

            sum.red += ((int) pixel4.red) * WEIGHT_SHARPEN + ((int) pixel5.red) * WEIGHT_MIDDLE + ((int) pixel6.red) * WEIGHT_SHARPEN;
            sum.green += ((int) pixel4.green) * WEIGHT_SHARPEN + ((int) pixel5.green) * WEIGHT_MIDDLE + ((int) pixel6.green) * WEIGHT_SHARPEN;
            sum.blue += ((int) pixel4.blue) * WEIGHT_SHARPEN + ((int) pixel5.blue) * WEIGHT_MIDDLE + ((int) pixel6.blue) * WEIGHT_SHARPEN;

            sum.red += ((int) pixel7.red) * WEIGHT_SHARPEN + ((int) pixel8.red) * WEIGHT_SHARPEN + ((int) pixel9.red) * WEIGHT_SHARPEN;
            sum.green += ((int) pixel7.green) * WEIGHT_SHARPEN + ((int) pixel8.green) * WEIGHT_SHARPEN + ((int) pixel9.green) * WEIGHT_SHARPEN;
            sum.blue += ((int) pixel7.blue) * WEIGHT_SHARPEN + ((int) pixel8.blue) * WEIGHT_SHARPEN + ((int) pixel9.blue) * WEIGHT_SHARPEN;
            /*assign kernel's result to pixel at [i,j]
            *assign_sum_to_pixel function is here instead of calling the
            * function with params, because it's much faster to update these values here
             * in addition I removed division by kernel scale because it's always 1 in thise case  */
            // truncate each pixel's color values to match the range [0,255]
            current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
            current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
            current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
            pixelsImg[calcIndex(i, j, m)] = current_pixel;
        }
    }

    free(backupOrg);
}



void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName) {

    /*got ride of blurKernel and sharpKernel matrix because i know their values,
     * replacing it's values with defines*/

    // blur image - made special func for blur operation
    doConvolutionBlur(image, 3, 9);

    // write result image to file
    writeBMP(image, srcImgpName, blurRsltImgName);


    // sharpen the resulting image - made special func for sharpen operation
    doConvolutionSharpen(image, 3, 1);

    // write result image to file
    writeBMP(image, srcImgpName, sharpRsltImgName);
}