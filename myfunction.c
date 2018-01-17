//316584960 Liz Aharonian
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
 * I made these macros because macros are much more efficient then functions */
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define calcIndex(i,j,n) ((i)*(n)+(j))
#define multByNine(a) (((a)<<3) + (a))
#define isEven(a) ((a)%2 == 0) ? 1 : 0
#define multThree(a, b, c) ((a)*(b)*(c))
#define WEIGHT_SHARPEN -1

/**
 * doConvolutionBlur function.
 * the function blurs the image
 * improvements are specified inside the function
 * @param image - image to be blurred
 * @param kernelSize - represents kernel size
 * @param kernelScale - represent kernel scale
 */
void doConvolutionBlur(Image *image, int kernelSize, int kernelScale) {
    /*I got ride of pixelsImg function and replaced it with casting of image->data
     *by this and by using memcpy func i got ride of:
     *charsToPixels, pixelsToChars, copyPixels because they are not necessary anymore.
     *in addition, I got ride of repetitive calculations using x param*/
    register int x = multThree(m,n,3);
    register pixel *pixelsImg = (pixel *) image->data;
    register pixel *backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg, x);
    /*smooth function is here instead of calling the
     *function with params, because it's much faster to update these values here
     *passing the params cost running time*/
    register int i, j, halfK, dimMinusHalfKernel;
    //calculation of kernelSize/2 was deleted because it's always 1 in our case
    halfK = 1;
    //took these declarations out of the loop
    pixel_sum sum;
    pixel current_pixel;
    //got ride of repetitive calculations using dimMinusHalfKernel param
    dimMinusHalfKernel = m - halfK;
    int isEven = isEven(m);
    int ii, jj;
    if (!isEven) {
        for (i = halfK; i < dimMinusHalfKernel; ++i) {
            ii = max(i - 1, 0);
            for (j = halfK; j < dimMinusHalfKernel; ++j) {

                /*got ride of initialize_pixel_sum function, there is no need to initialize these values
                 * because i override them each iteration*/
                /*applyKernel function is here instead of calling the function with params
                 *in addition I am using Loop unrolling to update the values,
                 *it's helps cpu parallel it's actions*/
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
                sum.red = ((int) pixel1.red) + ((int) pixel2.red) + ((int) pixel3.red);
                sum.green = ((int) pixel1.green) + ((int) pixel2.green) + ((int) pixel3.green);
                sum.blue = ((int) pixel1.blue) + ((int) pixel2.blue) + ((int) pixel3.blue);

                sum.red += ((int) pixel4.red) + ((int) pixel5.red) + ((int) pixel6.red);
                sum.green += ((int) pixel4.green) + ((int) pixel5.green) + ((int) pixel6.green);
                sum.blue += ((int) pixel4.blue) + ((int) pixel5.blue) + ((int) pixel6.blue);

                sum.red += ((int) pixel7.red) + ((int) pixel8.red) + ((int) pixel9.red);
                sum.green += ((int) pixel7.green) + ((int) pixel8.green) + ((int) pixel9.green);
                sum.blue += ((int) pixel7.blue) + ((int) pixel8.blue) + ((int) pixel9.blue);
                /*assign kernel's result to pixel at [i,j]
                *assign_sum_to_pixel function is here instead of calling the
                *function with params, because it's much faster to update these values here*/
                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;
                /*truncate each pixel's color values to match the range [0,255]
                *max calculation was deleted because blur RGB is always positive
                *min calculation was deleted because RGB values are not more than 255 */
                current_pixel.red = (unsigned char) sum.red;
                current_pixel.green = (unsigned char) sum.green;
                current_pixel.blue = (unsigned char) sum.blue;
                pixelsImg[calcIndex(i, j, m)] = current_pixel;
            }
        }
    }else {
        /**
         * if m is even I can "double" loop unrolling.
         * it's helps cpu parallel it's actions
         */
        for (i = halfK; i < dimMinusHalfKernel; ++i) {
            ii = max(i - 1, 0);
            for (j = halfK; j < dimMinusHalfKernel; ++j) {
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

                sum.red = ((int) pixel1.red) + ((int) pixel2.red) + ((int) pixel3.red);
                sum.green = ((int) pixel1.green) + ((int) pixel2.green) + ((int) pixel3.green);
                sum.blue = ((int) pixel1.blue) + ((int) pixel2.blue) + ((int) pixel3.blue);

                sum.red += ((int) pixel4.red) + ((int) pixel5.red) + ((int) pixel6.red);
                sum.green += ((int) pixel4.green) + ((int) pixel5.green) + ((int) pixel6.green);
                sum.blue += ((int) pixel4.blue) + ((int) pixel5.blue) + ((int) pixel6.blue);

                sum.red += ((int) pixel7.red) + ((int) pixel8.red) + ((int) pixel9.red);
                sum.green += ((int) pixel7.green) + ((int) pixel8.green) + ((int) pixel9.green);
                sum.blue += ((int) pixel7.blue) + ((int) pixel8.blue) + ((int) pixel9.blue);

                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;

                current_pixel.red = (unsigned char) sum.red;
                current_pixel.green = (unsigned char) sum.green;
                current_pixel.blue = (unsigned char) sum.blue;
                pixelsImg[calcIndex(i, j, m)] = current_pixel;

                //additional calculations in the same iteration
                ++j;
                jj = max(j - 1, 0);
                int x1 = calcIndex(ii, jj, m);
                pixel pixel11 = backupOrg[x1];
                pixel pixel22 = backupOrg[x1 + 1];
                pixel pixel33 = backupOrg[x1 + 2];
                int xm1 = x1 + m;
                pixel pixel44 = backupOrg[xm1];
                pixel pixel55 = backupOrg[xm1 + 1];
                pixel pixel66 = backupOrg[xm1 + 2];
                int xmm1 = xm1 + m;
                pixel pixel77 = backupOrg[xmm1];
                pixel pixel88 = backupOrg[xmm1 + 1];
                pixel pixel99 = backupOrg[xmm1 + 2];

                sum.red = ((int) pixel11.red) + ((int) pixel22.red) + ((int) pixel33.red);
                sum.green = ((int) pixel11.green) + ((int) pixel22.green) + ((int) pixel33.green);
                sum.blue = ((int) pixel11.blue) + ((int) pixel22.blue) + ((int) pixel33.blue);

                sum.red += ((int) pixel44.red) + ((int) pixel55.red) + ((int) pixel66.red);
                sum.green += ((int) pixel44.green) + ((int) pixel55.green) + ((int) pixel66.green);
                sum.blue += ((int) pixel44.blue) + ((int) pixel55.blue) + ((int) pixel66.blue);

                sum.red += ((int) pixel77.red) + ((int) pixel88.red) + ((int) pixel99.red);
                sum.green += ((int) pixel77.green) + ((int) pixel88.green) + ((int) pixel99.green);
                sum.blue += ((int) pixel77.blue) + ((int) pixel88.blue) + ((int) pixel99.blue);

                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;

                current_pixel.red = (unsigned char) sum.red;
                current_pixel.green = (unsigned char) sum.green;
                current_pixel.blue = (unsigned char) sum.blue;
                pixelsImg[calcIndex(i, j, m)] = current_pixel;

            }
        }
    }
    free(backupOrg);
}
/**
 * doConvolutionSharpen function.
 * the function sharpen the image
 * improvements are specified inside the function
 * @param image - image to be sharpen
 * @param kernelSize - represents kernel size
 * @param kernelScale - represent kernel scale
 */
void doConvolutionSharpen(Image *image, int kernelSize, int kernelScale) {
    /*I got ride of pixelsImg function and replaced it with casting of image->data
     *by these and by using memcpy func i got ride of:
     *charsToPixels, pixelsToChars, copyPixels because they are not necessary anymore.
     *in addition, I got ride of repetitive calculations using dimMinusHalfKernel and x param*/
    register int x = multThree(m,n,3);
    register pixel *pixelsImg = (pixel *) image->data;
    register pixel *backupOrg = malloc(x);
    memcpy(backupOrg, pixelsImg, x);
    register int i, j, halfK, dimMinusHalfKernel;
    //calculation of kernelSize/2 was deleted because it's always 1 in our case
    halfK = 1;
    //took these declarations out of the loop
    pixel_sum sum;
    pixel current_pixel;
    dimMinusHalfKernel = m - halfK;
    int isEven = isEven(m);
    int ii, jj;

    if (!isEven) {
        for (i = halfK; i < dimMinusHalfKernel; ++i) {
            ii = max(i - 1, 0);
            for (j = halfK; j < dimMinusHalfKernel; ++j) {
                /*got ride of initialize_pixel_sum function, no need to initialize these values
                 * because i override them each iteration*/
                /*applyKernel function is here instead of calling the function with params
                *in addition I am using Loop unrolling to update the values,
                *it's helps cpu parallel it's actions*/
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
                *function with params, because it's much faster to update these values here
                *in addition I update the weight using my defines instead of using the matrix
                *because define is much faster then memory access to matrix.
                *in addition, I use macro multByNine and shift to calculate multiplying of nine
                *much more efficient*/
                sum.red = ((int) pixel1.red) * WEIGHT_SHARPEN + ((int) pixel2.red) * WEIGHT_SHARPEN +
                          ((int) pixel3.red) * WEIGHT_SHARPEN;
                sum.green = ((int) pixel1.green) * WEIGHT_SHARPEN + ((int) pixel2.green) * WEIGHT_SHARPEN +
                            ((int) pixel3.green) * WEIGHT_SHARPEN;
                sum.blue = ((int) pixel1.blue) * WEIGHT_SHARPEN + ((int) pixel2.blue) * WEIGHT_SHARPEN +
                           ((int) pixel3.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel4.red) * WEIGHT_SHARPEN + multByNine((int) pixel5.red) +
                           ((int) pixel6.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel4.green) * WEIGHT_SHARPEN + multByNine((int) pixel5.green) +
                             ((int) pixel6.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel4.blue) * WEIGHT_SHARPEN + multByNine((int) pixel5.blue) +
                            ((int) pixel6.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel7.red) * WEIGHT_SHARPEN + ((int) pixel8.red) * WEIGHT_SHARPEN +
                           ((int) pixel9.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel7.green) * WEIGHT_SHARPEN + ((int) pixel8.green) * WEIGHT_SHARPEN +
                             ((int) pixel9.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel7.blue) * WEIGHT_SHARPEN + ((int) pixel8.blue) * WEIGHT_SHARPEN +
                            ((int) pixel9.blue) * WEIGHT_SHARPEN;
                /*assign kernel's result to pixel at [i,j]
                *assign_sum_to_pixel function is here instead of calling the
                *function with params, because it's much faster to update these values here
                *in addition I removed division by kernel scale because it's always 1 in this case  */
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[calcIndex(i, j, m)] = current_pixel;
            }
        }
    } else {
        /**
         * if m is even I can "double" loop unrolling.
         * it's helps cpu parallel it's actions
         */
        for (i = halfK; i < dimMinusHalfKernel; ++i) {
            ii = max(i - 1, 0);
            for (j = halfK; j < dimMinusHalfKernel; ++j) {

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

                sum.red = ((int) pixel1.red) * WEIGHT_SHARPEN + ((int) pixel2.red) * WEIGHT_SHARPEN +
                          ((int) pixel3.red) * WEIGHT_SHARPEN;
                sum.green = ((int) pixel1.green) * WEIGHT_SHARPEN + ((int) pixel2.green) * WEIGHT_SHARPEN +
                            ((int) pixel3.green) * WEIGHT_SHARPEN;
                sum.blue = ((int) pixel1.blue) * WEIGHT_SHARPEN + ((int) pixel2.blue) * WEIGHT_SHARPEN +
                           ((int) pixel3.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel4.red) * WEIGHT_SHARPEN + multByNine((int) pixel5.red) +
                           ((int) pixel6.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel4.green) * WEIGHT_SHARPEN + multByNine((int) pixel5.green) +
                             ((int) pixel6.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel4.blue) * WEIGHT_SHARPEN + multByNine((int) pixel5.blue) +
                            ((int) pixel6.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel7.red) * WEIGHT_SHARPEN + ((int) pixel8.red) * WEIGHT_SHARPEN +
                           ((int) pixel9.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel7.green) * WEIGHT_SHARPEN + ((int) pixel8.green) * WEIGHT_SHARPEN +
                             ((int) pixel9.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel7.blue) * WEIGHT_SHARPEN + ((int) pixel8.blue) * WEIGHT_SHARPEN +
                            ((int) pixel9.blue) * WEIGHT_SHARPEN;

                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[calcIndex(i, j, m)] = current_pixel;

                //additional calculations in the same iteration
                ++j;
                jj = max(j - 1, 0);

                int x1 = calcIndex(ii, jj, m);
                pixel pixel11 = backupOrg[x1];
                pixel pixel22 = backupOrg[x1 + 1];
                pixel pixel33 = backupOrg[x1 + 2];
                int xm1 = x1 + m;
                pixel pixel44 = backupOrg[xm1];
                pixel pixel55 = backupOrg[xm1 + 1];
                pixel pixel66 = backupOrg[xm1 + 2];
                int xmm1 = xm1 + m;
                pixel pixel77 = backupOrg[xmm1];
                pixel pixel88 = backupOrg[xmm1 + 1];
                pixel pixel99 = backupOrg[xmm1 + 2];

                sum.red = ((int) pixel11.red) * WEIGHT_SHARPEN + ((int) pixel22.red) * WEIGHT_SHARPEN +
                          ((int) pixel33.red) * WEIGHT_SHARPEN;
                sum.green = ((int) pixel11.green) * WEIGHT_SHARPEN + ((int) pixel22.green) * WEIGHT_SHARPEN +
                            ((int) pixel33.green) * WEIGHT_SHARPEN;
                sum.blue = ((int) pixel11.blue) * WEIGHT_SHARPEN + ((int) pixel22.blue) * WEIGHT_SHARPEN +
                           ((int) pixel33.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel44.red) * WEIGHT_SHARPEN + multByNine((int) pixel55.red) +
                           ((int) pixel66.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel44.green) * WEIGHT_SHARPEN + multByNine((int) pixel55.green) +
                             ((int) pixel66.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel44.blue) * WEIGHT_SHARPEN + multByNine((int) pixel55.blue) +
                            ((int) pixel66.blue) * WEIGHT_SHARPEN;

                sum.red += ((int) pixel77.red) * WEIGHT_SHARPEN + ((int) pixel88.red) * WEIGHT_SHARPEN +
                           ((int) pixel99.red) * WEIGHT_SHARPEN;
                sum.green += ((int) pixel77.green) * WEIGHT_SHARPEN + ((int) pixel88.green) * WEIGHT_SHARPEN +
                             ((int) pixel99.green) * WEIGHT_SHARPEN;
                sum.blue += ((int) pixel77.blue) * WEIGHT_SHARPEN + ((int) pixel88.blue) * WEIGHT_SHARPEN +
                            ((int) pixel99.blue) * WEIGHT_SHARPEN;

                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[calcIndex(i, j, m)] = current_pixel;
            }
        }
    }
    free(backupOrg);
}

/**
 * myfunction function.
 * @param image - image to be blurred and sharpen.
 * @param srcImgpName - source image name
 * @param blurRsltImgName - blur image name
 * @param sharpRsltImgName - sharpen image name
 */
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