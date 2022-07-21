extern "C" {
void image_thresholding_kernel (
	unsigned char *input_image,
    unsigned char *output_image,
    unsigned int   n,
    unsigned int   m,
    unsigned int   threshold,
    unsigned int   maxVal
)
{

	unsigned char input_pixel;
	unsigned char output_pixel;

	for (unsigned int i = 0; i < n*m; i++) {
		input_pixel = input_image[i];
		output_pixel = (input_pixel > threshold)? maxVal : 0;
		output_image[i] = output_pixel;
	}
}
}
