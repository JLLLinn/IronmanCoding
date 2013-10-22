#ifndef OCRFUNC
#define OCRFUNC

#define BLUR_RADIUS			1
#define MAX_TROWS			5
#define MAX_TCOLS			44
#define COMPUTE_W_ROTAT		0 //if 1 then compare with rotation. otherwise without
#define CALCULATE_MAXCOL	(int)floor(pxPerMm*(0.35+0.08)/2+0.5)//0.35 is the nominal strokewidth, data taken from P21 1073
#define CALCULATE_MINCOL	(int)floor(pxPerMm*(0.35-0.08)/2+0.5)
#define TEMPLATE_DIRECTORY	"./Template/ .txt"//if this path is changed, please also change the position of target character in GetTemplateCoordinatesInPixels()
#define HEIGHT_B			2.46//taken from Doc 1073 P4
#define HEIGHT_A			2.66
#define PI					3.14159265
#define ANGLE				3
#define ANGLE_STEP			50

#include <vcclr.h>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

struct DiagnolPoint{
	int x1;
	int y1;
	int x2;
	int y2;
};

struct Result{
	char** resultString;
	int** badPx;
	int** totalPx;
	double** angle;
};


class OCRDecoder{
private:
	int height;// height of Displaymap (px)
	int width;
	int row;
	int* col;//specify how many columns(characters) are there in the row
	unsigned char** color_rows;//color_rows[y][x]
	gcroot<Bitmap^> displayBitMap;
	int divideColorValue;//number being used to distinguish background and text pixels
	DiagnolPoint** boxes;//boxes[y][x]
	Result result;
public:
	OCRDecoder(int height,int width, unsigned char** color_rows, Bitmap^ displayBitMap, int divideColorValue);
	void DivideColorValue(int d);	//set DivideColorValue
	int DivideColorValue();	//get DivideColorValue


	void Blur();
	void OtsuThreshold();
	void LoadColorRowsIntoBitmap();
	/*
	 * getting boundaries of characters
	 */
	int FindAveragePixelColor();
	void LookForUDLines(int* rowDividers);
	void LookForVerLines(int* rowDividers,int colDividers[MAX_TROWS][2*MAX_TCOLS+1]);
	void LookForLineBoxes();
	void RefineUDEdges(DiagnolPoint& box);
	void RefineAllUDEdge();//refine every boxes, makes them fit the character. Need to be called after the look for line boxes is called
	void LineBox_All();
	void DrawLineBoxes();
	String^ BoxDataToString();

	/*
	 * Create Matrix for Comparing
	 */
	int** GetTemplateCoordinatesInPixels(double pxPerMm,char target,int *numOfLines,int* MaxCOL,int* MinCOL,double angle);//return the template dots in pixel, rotation is done here
	void SetLine(char** compareMatrix, int width, int height, int* line, int radius);//setting the line to black('+' or '-') and white('w') with square or circle mode,matrix should contain all 'w' initially
	void SetSquareArrPx(int x, int y, int radius ,char ** compareMatrix, int width, int height);//used in SetLine function
	void SetRoundArrPx(int x, int y, int radius ,char ** compareMatrix, int width, int height);
	char** CreateCompareMatrix(int width, int height, char target, int maxMinFlag,double angle);//create the matrix for compare, maxMinFlag=?,1:maxCOL, 0:minCOL
	String^ CharMatrixToString(char** compareMatrix,int width,int height);//turn char matrix to String^ for displaying
	

	/*
	 * Compare Matrix with the sample
	 */
	int CompMatrixWithSampleInnerContour(int Y, int X, char** compareMatrix);// Takes in a compareMatrix with the same width and height of box[Y][X]. returns the score of comparing with the inner contour.Set bad pixels as '#'
	int CompMatrixWithSampleOuterContour(int Y, int X, char** compareMatrix);// Takes in a compareMatrix with the same width and height of box[Y][X]. returns the score of comparing with the outer contour. Set bad pixels as '#'
	int ComputeTotalBadPx(int y,int x, char target,double angle);//do box[y][x]
	int ComputeTotalBadPxWRotation(int y, int x, char target,double* minAngle);//for every rotation, do ComputeTotalBadPx(), returns the lowest (best) score. minAngle stores the angle at which score has the minimum
	void Recognize();
	String^ ResultStringToString();
	String^ ResultScoreToString();
	String^ CreateAndCompare(int Y, int X, char target,double angle);//for debug only .Create 2 matrix according to the target (inner and outer contour), and compare with the sample, output the matrix after compare (with '#' indicator),and scores for two contours

};




#endif