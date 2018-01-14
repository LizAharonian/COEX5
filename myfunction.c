
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
int min(int a, int b) { return (a < b ? a : b); }
int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
void initialize_pixel_sum(pixel_sum *sum) {
	sum->red = sum->green = sum->blue = 0;
	sum->num = 0;
	return;
}

/*
 * assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
 */
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
}

/*
* sum_pixels_by_weight - Sums pixel values, scaled by given number
*/
static void sum_pixels_by_weight(pixel_sum *sum, pixel p, int weight) {
	sum->red += ((int) p.red) * weight;
	sum->green += ((int) p.green) * weight;
	sum->blue += ((int) p.blue) * weight;
	sum->num++;
	return;
}

/*
 *  Applies kernel for pixel at (i,j)
 */
static pixel applyKernel(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

	int ii, jj;
	int currRow, currCol;
	pixel_sum sum;
	pixel current_pixel;

	initialize_pixel_sum(&sum);

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
			sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
		}
	}

	// assign kernel's result to pixel at [i,j]
	assign_sum_to_pixel(&current_pixel, sum, kernelScale);
	return current_pixel;
}

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

	int i, j, halfKer, dMinHalfKer;
    halfKer =kernelSize / 2;
    dMinHalfKer = dim -halfKer;
	for (i = halfKer ; i < dMinHalfKer; i++) {
		for (j =  kernelSize / 2 ; j < dMinHalfKer ; j++) {
			dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale);
		}
	}
}

void charsToPixels(Image *charsImg, pixel* pixels) {

	int row, col, multRNC, multRNC3, multRN, mult2;
	for (row = 0 ; row < m ; row++) {
		multRN = row*n;
		for (col = 0 ; col < n ; col++) {
			multRNC = multRN + col;
			multRNC3 = 3*multRN + 3*col;
			pixels[multRNC].red = image->data[multRNC3];
			pixels[multRNC].green = image->data[multRNC3 + 1];
			pixels[multRNC].blue = image->data[multRNC3 + 2];

		}
	}
}

void pixelsToChars(pixel* pixels, Image *charsImg) {

	int row, col, multRN3C, multRN,multRNC;
	for (row = 0 ; row < m ; row++) {
		multRN =row*n;
		for (col = 0 ; col < n ; col++) {
			multRN3C = 3*multRN + 3*col;
			multRNC =multRN + col;
			image->data[multRN3C] = pixels[multRNC].red;
			image->data[multRN3C + 1] = pixels[multRNC].green;
			image->data[multRN3C + 2] = pixels[multRNC].blue;
		}
	}
}

void copyPixels(pixel* src, pixel* dst) {

	int row, col, multRNC;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {
            multRNC =row*n + col;
			dst[multRNC].red = src[multRNC].red;
			dst[multRNC].green = src[multRNC].green;
			dst[multRNC].blue = src[multRNC].blue;
		}
	}
}

int calcIndex(int i, int j, int n) {
	return ((i)*(n)+(j));
}

void doConvolution(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale) {

	pixel* pixelsImg = malloc(m*n*sizeof(pixel));
	pixel* backupOrg = malloc(m*n*sizeof(pixel));

	charsToPixels(image, pixelsImg);
	copyPixels(pixelsImg, backupOrg);

	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale);

	pixelsToChars(pixelsImg, image);

	free(pixelsImg);
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
	doConvolution(image, 3, blurKernel, 9);

	// write result image to file
	writeBMP(image, srcImgpName, blurRsltImgName);

	//smooth(m, backupOrg, pixelsImg, kernelSize, sharpKernel, 1);

	// sharpen the resulting image
	doConvolution(image, 3, sharpKernel, 1);

	// write result image to file
	writeBMP(image, srcImgpName, sharpRsltImgName);
}
