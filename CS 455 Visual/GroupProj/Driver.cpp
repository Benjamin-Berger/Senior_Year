#include "Sudoku.h"

int main(int argc, char **argv) {
	if(argc != 2) {
		cout << "USAGE: skeleton <input file path>" << endl;
	   	return -1;
	}

  	Mat original_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
 	Rect myROI(304, 610, 675, 655);
	Mat modified_image = original_image(myROI);
 	Mat *image = &modified_image;

	//Check that the images loaded
	if(!original_image.data || !modified_image.data) {
		cout << "ERROR: Could not load image data." << endl;
	    return -1;
	}

	  //Create the display window
	  namedWindow("Sudoku");



  vector<vector<int> > puzzle;

  createPuzzle(modified_image, puzzle);



  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    moveWindow("Unix Sample Skeleton", 10, 30);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image){
          image = &modified_image;
        }
        else{
          image = &original_image;
        }
        break;
      default:
        break;
    }
  }


}