#include "stdafx.h"//for precompile header
#include <Windows.h>
#include "OCRFuncs.h"
#include <iostream>
#include <fstream>
#include <cmath>

OCRDecoder::OCRDecoder(int height,int width, unsigned char** color_rows, Bitmap^ displayBitMap, int divideColorValue) {
	this->height=height;
	this->width=width;
	this->color_rows=color_rows;
	this->displayBitMap=displayBitMap;
	this->divideColorValue=divideColorValue;
}
void OCRDecoder::DivideColorValue(int d) {
	divideColorValue = d;
	int i = 0;
	int j = 0;
}
int OCRDecoder::DivideColorValue() {
	return divideColorValue;
}
void OCRDecoder::LookForUDLines(int* rowDividers) {
	//Pen^ currentPen = gcnew Pen(Color::Red,1.0F); 4d
	//Graphics^ gr = Graphics::FromImage(displayBitMap); 4d

	int h = height;
	int w = width;

	int* isWhiteRow = new int[h];    //only contains 1 and 0
	for (int i = 0; i < h; i++) {    //initialize
		isWhiteRow[i] = 1;
	}
	for (int i = 0; i < 2 * MAX_TROWS + 1; i++) {
		rowDividers[i] = -1;
	}

	for (int i = 0; i < h; i++) {    //looking for white lines
		for (int j = 0; j < w; j++) {
			if (color_rows[i][j] < divideColorValue) {
				isWhiteRow[i] = 0;
				break;
			}
		}
	}
	for (int i = 0, j = 0; i < h; i++) {
		if ((isWhiteRow[i]) + (isWhiteRow[i + 1]) == 1) { //if we have a difference
			if (isWhiteRow[i] == 1) {
				//gr->DrawLine(currentPen,0,i,w,i); 4d
				rowDividers[j] = i;
				j++;
			}

			else {
				//gr->DrawLine(currentPen,0,i+1,w,i+1); 4d
				rowDividers[j] = i + 1;
				j++;
			}
			i++;
		}
	}

	int test[10];
	for (int i = 0; i < 10; i++) {
		test[i] = rowDividers[i];
	}
	delete[] isWhiteRow;
	//return rowDividers;//store the line number of divide lines
}
void OCRDecoder::LookForVerLines(int* rowDividers,
		int colDividers[MAX_TROWS][2 * MAX_TCOLS + 1]) {

	int h = height;
	int w = width;
	int test[20];
	int numsOfTextRows = 0;
	for (int i = 0;; i++) {
		test[i] = rowDividers[i];
		if (rowDividers[i] < 0) {
			numsOfTextRows = i / 2;
			break;
		}
	}

	int ** isWhiteCol = new int *[numsOfTextRows];

	for (int i = 0; i < 2 * numsOfTextRows; i += 2) {
		isWhiteCol[i / 2] = new int[w];
		for (int l = 0; l < w; l++) {
			isWhiteCol[i / 2][l] = 1;
		}
		for (int j = 0; j < w; j++) {
			for (int k = (rowDividers[i] + 1); k < rowDividers[i + 1]; k++) {
				if (color_rows[k][j] < divideColorValue) {
					isWhiteCol[i / 2][j] = 0;
					break;
				}
			}
		}
	}

	for (int i = 0; i < numsOfTextRows; i++) {
		for (int k = 0; k < 2 * MAX_TCOLS + 1; k++) {
			colDividers[i][k] = -1;
		}
		for (int j = 0, l = 0; j < w; j++) {
			if ((isWhiteCol[i][j]) + (isWhiteCol[i][j + 1]) == 1) { //if we have a difference
				if (isWhiteCol[i][j]) {
					colDividers[i][l] = j;
					l++;
				} else {
					colDividers[i][l] = j + 1;
					l++;
				}
			}
		}
	}

	for (int i = 0; i < numsOfTextRows; i++) {
		delete[] isWhiteCol[i];
	}
	delete[] isWhiteCol;
	//return colDividers;
}
void OCRDecoder::LookForLineBoxes() {
	int rowDividers[2 * MAX_TROWS + 1];
	LookForUDLines(rowDividers);
	int colDividers[MAX_TROWS][2 * MAX_TCOLS + 1];
	LookForVerLines(rowDividers, colDividers);

	//Pen^ currentPen = gcnew Pen(Color::Red,1.0F);
	//Graphics^ gr = Graphics::FromImage(displayBitMap);

	for (int i = 0;; i++) {
		if (rowDividers[i] < 0) {
			row = i / 2;
			boxes = new DiagnolPoint*[this->row];
			break;
		}
	}
	col = new int[row];

	for (int i = 0; i < row; i++) {
		for (int j = 0;; j++) {
			if (colDividers[i][j] < 0) {
				col[i] = j / 2;
				boxes[i] = new DiagnolPoint[j / 2];
				break;
			}
		}
	}

	for (int i = 0; i < row; i++) {
		int tempRow1 = rowDividers[2 * i];
		int tempRow2 = rowDividers[2 * i + 1];
		for (int j = 0; j < col[i]; j++) {
			boxes[i][j].y1 = tempRow1;
			boxes[i][j].y2 = tempRow2;
			boxes[i][j].x1 = colDividers[i][2 * j];
			boxes[i][j].x2 = colDividers[i][2 * j + 1];
			//gr->DrawLine(currentPen,boxes[i][j].x1,boxes[i][j].y1,boxes[i][j].x2,boxes[i][j].y2);//4debug
		}
	}

	//initialize result
	result.resultString = new char*[row];
	result.badPx = new int*[row];
	result.totalPx = new int*[row];

	for (int i = 0; i < row; i++) {
		result.resultString[i] = new char[(col[i])];
		result.badPx[i] = new int[(col[i])];
		result.totalPx[i] = new int[(col[i])];
	}

}

int OCRDecoder::FindAveragePixelColor() {
	int widthAve = 0;
	int heighAve = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			widthAve += color_rows[i][j];
		}
		widthAve /= width;
		heighAve += widthAve;
	}
	heighAve /= height;
	return heighAve;
}
void OCRDecoder::RefineUDEdges(DiagnolPoint& box) {
	bool findBlackLine = false;

	//refine the upper edge
	for (int tempy1 = (box.y1 + 1);; tempy1++) {
		for (int tempx1 = (box.x1 + 1); tempx1 < box.x2; tempx1++) {
			if (color_rows[tempy1][tempx1] < divideColorValue) {
				findBlackLine = true;
				break;
			}
		}
		if (findBlackLine) {
			box.y1 = tempy1 - 1;
			findBlackLine = false;
			break;
		}
	}

	//refine the bottom edge,now findBlackLine=false;
	for (int tempy2 = (box.y2 - 1);; tempy2--) {
		for (int tempx1 = (box.x1 + 1); tempx1 < box.x2; tempx1++) {
			if (color_rows[tempy2][tempx1] < divideColorValue) {
				findBlackLine = true;
				break;
			}
		}
		if (findBlackLine) {
			box.y2 = tempy2 + 1;
			break;
		}
	}
}

void OCRDecoder::RefineAllUDEdge() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col[i]; j++) {
			RefineUDEdges (boxes[i][j]);
			result.totalPx[i][j] = (boxes[i][j].x2 - boxes[i][j].x1 - 1)
					* (boxes[i][j].y2 - boxes[i][j].y1 - 1);
		}
	}
}

void OCRDecoder::DrawLineBoxes() {
	Pen ^ currentPen = gcnew
	Pen(Color::Red, 1.0F);
	Graphics ^ gr = Graphics::FromImage(displayBitMap);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col[i]; j++) {
			gr->DrawLine(currentPen, boxes[i][j].x1, boxes[i][j].y1,
					boxes[i][j].x2, boxes[i][j].y1);
			gr->DrawLine(currentPen, boxes[i][j].x1, boxes[i][j].y2,
					boxes[i][j].x2, boxes[i][j].y2);
			gr->DrawLine(currentPen, boxes[i][j].x1, boxes[i][j].y1,
					boxes[i][j].x1, boxes[i][j].y2);
			gr->DrawLine(currentPen, boxes[i][j].x2, boxes[i][j].y1,
					boxes[i][j].x2, boxes[i][j].y2);
		}
	}
}

String^ OCRDecoder::BoxDataToString() {
	String^ data="";
	for(int i=0;i<row;i++) {
		data+="row "+i+"\r\n";
		for(int j=0;j<col[i];j++) {
			data+="	col "+j+"	";
			data+="	x1: "+boxes[i][j].x1+"	y1: "+boxes[i][j].y1
			+"	x2: "+boxes[i][j].x2+"	y2: "+boxes[i][j].y2+"\r\n";
		}
	}
	return data;
}

int** OCRDecoder::GetTemplateCoordinatesInPixels(double pxPerMm, char target,
		int *numOfLines, int* MaxCOL, int* MinCOL, double angle) {
	double sine = sin(angle * PI / 180);	//4 rotate debug
	double cosine = cos(angle * PI / 180);
	double x = 0, y = 0;	//debug end

	char route[] = TEMPLATE_DIRECTORY;
	route[11] = target;
	std::ifstream source(route);
	source >> (*numOfLines);
	int** templateDots = new int*[*numOfLines];

	double temp = 0.0;
	for (int i = 0; i < (*numOfLines); i++) {
		templateDots[i] = new int[5];
		for (int j = 0; j < 4; j += 2) {
			/*source>>temp;
			 temp*=pxPerMm;
			 templateDots[i][j]=(int)floor(temp+0.5);*/

			source >> x;	//4 rotate debug
			source >> y;
			templateDots[i][j] = (int) floor(
					((x * cosine - y * sine) * pxPerMm) + 0.5);
			templateDots[i][j + 1] = (int) floor(
					((x * sine + y * cosine) * pxPerMm) + 0.5);	//debug end
		}
		source >> templateDots[i][4];
	}
	*MaxCOL = CALCULATE_MAXCOL;
	*MinCOL = CALCULATE_MINCOL;
	return templateDots;	//need to be deleted
}

void OCRDecoder::RotateTemplate(int ** templateDots, int numOfLines,
		double angle) {
	double sine = sin(angle * PI / 180);
	double cosine = cos(angle * PI / 180);

	for (int i = 0; i < numOfLines; i++) {
		for (int j = 0; j < 4; j += 2) {
			int x = templateDots[i][j];
			int y = templateDots[i][j + 1];
			templateDots[i][j] = (int) floor(
					(((double) x) * cosine - ((double) y) * sine) + 0.5);
			templateDots[i][j + 1] = (int) floor(
					(((double) x) * sine + ((double) y) * cosine) + 0.5);
		}
	}
}
void OCRDecoder::SetLine(char** compareMatrix, int width, int height, int* line,
		int radius) {//setting the line to black(1) and white(0) with square mode,matrix should contain all 0 initially
	//Using Bresenham Algorithm to find every pixel on the line
	int x = line[0], y = line[1], x2 = line[2], y2 = line[3];
	int w = x2 - x;
	int h = y2 - y;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w < 0)
		dx1 = -1;
	else if (w > 0)
		dx1 = 1;
	if (h < 0)
		dy1 = -1;
	else if (h > 0)
		dy1 = 1;
	if (w < 0)
		dx2 = -1;
	else if (w > 0)
		dx2 = 1;
	int longest = abs(w);
	int shortest = abs(h);
	if (!(longest > shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h < 0)
			dy2 = -1;
		else if (h > 0)
			dy2 = 1;
		dx2 = 0;
	}
	int numerator = longest >> 1;
	for (int i = 0; i <= longest; i++) {
		if (line[4] == 1) {
			SetSquareArrPx(x, y, radius, compareMatrix, width, height);
		} else if (line[4] == 0) {
			SetRoundArrPx(x, y, radius, compareMatrix, width, height);
		}
		numerator += shortest;
		if (!(numerator < longest)) {
			numerator -= longest;
			x += dx1;
			y += dy1;
		} else {
			x += dx2;
			y += dy2;
		}
	}
}

void OCRDecoder::SetSquareArrPx(int x, int y, int radius, char ** compareMatrix,
		int width, int height) {
	for (int i = 0 - radius; i < radius; i++) {		//for a certain pixel
		if ((y + i) < 0 || (y + i) >= height)
			continue;
		for (int j = 0 - radius; j < radius; j++) {
			if ((x + j) < 0 || (x + j) >= width)
				continue;
			if (compareMatrix[y + i][x + j] == '+')
				continue;
			if (i == 0 && j == 0) {
				compareMatrix[y + i][x + j] = '+';
				continue;
			}
			compareMatrix[y + i][x + j] = '-';
		}
	}
}
void OCRDecoder::SetRoundArrPx(int x, int y, int radius, char ** compareMatrix,
		int width, int height) {
	for (int i = 0 - radius; i < radius; i++) {		//for a certain pixel
		if ((y + i) < 0 || (y + i) >= height)
			continue;
		int r = (int) floor(sqrt((double) (radius * radius - i * i)) + 0.5);
		for (int j = 0 - r; j < r; j++) {
			if ((x + j) < 0 || (x + j) >= width)
				continue;
			if (compareMatrix[y + i][x + j] == '+')
				continue;
			if (i == 0 && j == 0) {
				compareMatrix[y + i][x + j] = '+';
				continue;
			}
			compareMatrix[y + i][x + j] = '-';
		}
	}
}

String^ OCRDecoder::CharMatrixToString(char** compareMatrix,int width,int height) {
	String^ matrixString="";

	//loose mode
	/*for(int i=0;i<height;i++){//display compareMatrix
	 if(i==0){
	 matrixString+="    ";
	 for(int j=0;j<width;j++){
	 matrixString+=j+"	";
	 }
	 matrixString+="\r\n";
	 }
	 for(int j=0;j<width;j++){
	 if(j==0) matrixString+=i+"  ";
	 matrixString+=Char::ToString(compareMatrix[i][j])+"	";
	 }
	 matrixString+="\r\n";
	 }*/

	//condense mode
	for(int i=0;i<height;i++) {		//display compareMatrix
		for(int j=0;j<width;j++) {
			matrixString+=Char::ToString(compareMatrix[i][j])+" ";
		}
		matrixString+="\r\n";
	}
	return matrixString;
}
char** OCRDecoder::CreateCompareMatrix(int width, int height, char target,
		int maxMinFlag, double angle) {	//create the matrix for compare, maxMinFlag=?,1:maxCOL, 0:minCOL
	int numOfLines = 0;
	double pxPerMm = 0;
	if ((target >= 'A' && target <= 'Z') || target == '<') {
		pxPerMm = height / HEIGHT_B;
	} else if (target >= '0' && target <= '9') {
		pxPerMm = height / HEIGHT_A;
	}
	int maxCOL = 0, minCOL = 0;

	int** templateDots = GetTemplateCoordinatesInPixels(pxPerMm, target,
			&numOfLines, &maxCOL, &minCOL, angle);
	//RotateTemplate(templateDots, numOfLines,-30);
	char** compareMatrix = new char*[height];		//constructing compareMatrix
	for (int i = 0; i < height; i++) {
		compareMatrix[i] = new char[width];
		for (int j = 0; j < width; j++) {
			compareMatrix[i][j] = 'w';
		}
	}
	if (maxMinFlag == 0) {
		for (int i = 0; i < numOfLines; i++) {
			SetLine(compareMatrix, width, height, templateDots[i], minCOL);
		}
	} else if (maxMinFlag == 1) {
		for (int i = 0; i < numOfLines; i++) {
			SetLine(compareMatrix, width, height, templateDots[i], maxCOL);
		}
	}

	for (int i = 0; i < numOfLines; i++) {
		delete[] templateDots[i];
	}
	delete[] templateDots;

	return compareMatrix;
}
int OCRDecoder::CompMatrixWithSampleInnerContour(int y, int x,
		char** compareMatrix) {
	double score = 0;
	int x1 = this->boxes[y][x].x1;
	int x2 = this->boxes[y][x].x2;
	int y1 = this->boxes[y][x].y1;
	int y2 = this->boxes[y][x].y2;
	int width = x2 - x1 - 1;
	int height = y2 - y1 - 1;
	int badPx = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {		//go through every pixel
			if (compareMatrix[i][j] == '+' || compareMatrix[i][j] == '-') {	//if it inside the inner contour
				if (color_rows[y1 + i + 1][x1 + j + 1] >= divideColorValue) {//if it is white in the sample
					compareMatrix[i][j] = '#';		//4 debug
					badPx++;
				}
			}
		}
	}
	return badPx;
}

int OCRDecoder::CompMatrixWithSampleOuterContour(int y, int x,
		char** compareMatrix) {
	int x1 = this->boxes[y][x].x1;
	int x2 = this->boxes[y][x].x2;
	int y1 = this->boxes[y][x].y1;
	int y2 = this->boxes[y][x].y2;
	int width = x2 - x1 - 1;
	int height = y2 - y1 - 1;
	int badPx = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {		//go through every pixel
			if (color_rows[y1 + i + 1][x1 + j + 1] < divideColorValue) {//if it is black
				if (compareMatrix[i][j] == 'w') {//and also outside of the outer contour
					compareMatrix[i][j] = '#';		//4 debug
					badPx++;
				}
			}
		}
	}
	return badPx;
}

int OCRDecoder::ComputeTotalBadPx(int y, int x, char target, double angle) {//do box[y][x]
	int width = boxes[y][x].x2 - boxes[y][x].x1 - 1;
	int height = boxes[y][x].y2 - boxes[y][x].y1 - 1;
	int totalBadPx = 0;

	char** compareMatrix = CreateCompareMatrix(width, height, target, 1, angle);
	totalBadPx += CompMatrixWithSampleOuterContour(y, x, compareMatrix);
	for (int i = 0; i < height; i++) {
		delete[] compareMatrix[i];
	}
	delete[] compareMatrix;

	compareMatrix = CreateCompareMatrix(width, height, target, 0, angle);
	totalBadPx += CompMatrixWithSampleInnerContour(y, x, compareMatrix);
	for (int i = 0; i < height; i++) {
		delete[] compareMatrix[i];
	}
	delete[] compareMatrix;

	return totalBadPx;

}

int OCRDecoder::ComputeTotalBadPxWRotation(int y, int x, char target) {
	int minScore = ComputeTotalBadPx(y, x, target, -ANGLE);
	int counter = 0;
	for (double i = -ANGLE; i < ANGLE; i += (ANGLE / ANGLE_STEP)) {
		int score = ComputeTotalBadPx(y, x, target, i);
		if (score < minScore) {
			minScore = score;
		}
		double temp = ANGLE / ANGLE_STEP;
		counter++;
	}
	int j = 0;
	return minScore;

}

String^ OCRDecoder::CreateAndCompare(int Y, int X, char target,double angle) {
	String^ compareMatrixString="\r\n";

	int width = boxes[Y][X].x2-boxes[Y][X].x1-1;
	int height= boxes[Y][X].y2-boxes[Y][X].y1-1;

	char** compareMatrix=CreateCompareMatrix(width,height,target,1,angle);
	int outerBadPx=CompMatrixWithSampleOuterContour(Y, X, compareMatrix);//compare with the sample picture
	compareMatrixString+=CharMatrixToString(compareMatrix,width,height)+outerBadPx+"\r\n";
	for(int i=0;i<height;i++) {
		delete[] compareMatrix[i];
	}
	delete[] compareMatrix;

	compareMatrix=CreateCompareMatrix(width,height,target,0,angle);
	int innerBadPx=CompMatrixWithSampleInnerContour(Y, X, compareMatrix);//compare with the sample picture
	compareMatrixString+=CharMatrixToString(compareMatrix,width,height)+innerBadPx+"\r\n";
	for(int i=0;i<height;i++) {
		delete[] compareMatrix[i];
	}
	delete[] compareMatrix;
	return compareMatrixString;
}

void OCRDecoder::RecognizeEAnd1() {
	int score[4];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col[i]; j++) {
			if (COMPUTE_W_ROTAT) {
				score[0] = ComputeTotalBadPxWRotation(i, j, '1');
				score[1] = ComputeTotalBadPxWRotation(i, j, 'B');
				score[2] = ComputeTotalBadPxWRotation(i, j, 'E');
				score[3] = ComputeTotalBadPxWRotation(i, j, '8');
			} else {
				score[0] = ComputeTotalBadPx(i, j, '1', 0);
				score[1] = ComputeTotalBadPx(i, j, 'B', 0);
				score[2] = ComputeTotalBadPx(i, j, 'E', 0);
				score[3] = ComputeTotalBadPx(i, j, '8', 0);
			}

			int min = score[0], minPosition = 0;
			for (int k = 1; k < 4; k++) {
				if (min > score[k]) {
					min = score[k];
					minPosition = k;
				}
			}
			switch (minPosition) {
			case 0:
				result.badPx[i][j] = score[0];
				result.resultString[i][j] = '1';
				break;
			case 1:
				result.badPx[i][j] = score[1];
				result.resultString[i][j] = 'B';
				break;
			case 2:
				result.badPx[i][j] = score[2];
				result.resultString[i][j] = 'E';
				break;
			case 3:
				result.badPx[i][j] = score[3];
				result.resultString[i][j] = '8';
				break;
			}
		}
	}
}

String^ OCRDecoder::ResultStringToString() {
	String^ resultString="";
	for(int i=0;i<row;i++) {
		resultString+=gcnew String(result.resultString[i],0,col[i]);
		resultString+="\r\n";
	}
	return resultString;
}

String^ OCRDecoder::ResultScoreToString() {
	String^ scoreString="";
	double similarity=0;
	for(int i=0;i<row;i++) {
		scoreString+="row: "+i+"\r\n";
		for(int j=0;j<col[i];j++) {
			similarity=1.0-(double)result.badPx[i][j]/(double)result.totalPx[i][j];
			scoreString+="col: "+j+"	bad pixels: "+result.badPx[i][j]+"	total pixels: "+result.totalPx[i][j]+"	similarity: "+similarity+"\r\n";
		}
	}
	return scoreString;
}