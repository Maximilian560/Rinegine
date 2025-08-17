#pragma once
//#include "MyLib.h"
#include <cstddef>
#include <malloc.h>
#include <cmath>
//#include <iostream>
//#include <vector>
//using namespace std;
//double* temp = (double*)malloc(2 * sizeof(double));

int* bytes = (int*)calloc(1024, sizeof(int));



class GradientNoise
{
    //byte[] permutationTable;

public:
    void SetSeed(int seed)
    {
        srand(seed);
        //var rand = new System.Random(seed);
        //bytes = new byte[1024];
        //rand.NextBytes(bytes);
        for (int i = 0; i < 1024; i++)
        {
            bytes[i] = rand();
        }
    }

private:
    double* GetPseudoRandomGradientVector(int x, int y)
    {
        int v = (int)(( ((x * 1836311903) ^ (y * 2971215073)) + 4807526976) & 1023);
        v = bytes[v] & 4;

        double* temp = nullptr;
        do
        {
            temp = (double*)malloc(2 * sizeof(double));
        } while (temp == nullptr);
        switch (v)
        {
        case 0:  temp[0] =  1; temp[1] =  0; break;
        case 1:  temp[0] = -1; temp[1] =  0; break;
        case 2:  temp[0] =  0; temp[1] =  1; break;
        default: temp[0] =  0; temp[1] = -1; break;

        }
        return temp;
    }


    double QunticCurve(double t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double Lerp(double a, double b, double t)
    {
        return a + (b - a) * t;
    }

    double Dot(double* a, double* b)
    {
        return a[0] * b[0] + a[1] * b[1];
    }

public:
    double Noise1(double i, double j, double size)
    {
        double fx = i / size;
        double fy = j / size;
        int left = (int)floor(fx);
        int top = (int)floor(fy);
        double pointInQuadX = fx - left;
        double pointInQuadY = fy - top;
        //cout << "//" << fy << "\\\\" << endl;
        double* topLeftGradient;
        double* topRightGradient;
        double* bottomLeftGradient;
        double* bottomRightGradient;

        topLeftGradient = GetPseudoRandomGradientVector(left, top);
        topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
        bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
        bottomRightGradient = GetPseudoRandomGradientVector(left + 1, top + 1);

        //cout <<endl<< topLeftGradient[0] << endl << topLeftGradient[1]<<endl;

        double* distanceToTopLeft = nullptr;
        do {
            distanceToTopLeft = (double*)calloc(2, sizeof(double));
        } while (distanceToTopLeft == nullptr);

        double* distanceToTopRight = nullptr;
        do {
            distanceToTopRight = (double*)calloc(2, sizeof(double));
        } while (distanceToTopRight == nullptr);

        double* distanceToBottomLeft = nullptr;
        do {
            distanceToBottomLeft = (double*)calloc(2, sizeof(double));
        } while (distanceToBottomLeft == nullptr);

        double* distanceToBottomRight = nullptr;
        do {
            distanceToBottomRight = (double*)calloc(2, sizeof(double));
        } while (distanceToBottomRight == nullptr);

        distanceToTopLeft[0] = pointInQuadX; distanceToTopLeft[1] = pointInQuadX;
        distanceToTopRight[0] = pointInQuadX - 1; distanceToTopRight[1] = pointInQuadX;
        distanceToBottomLeft[0] = pointInQuadX; distanceToBottomLeft[1] = pointInQuadX - 1;
        distanceToBottomRight[0] = pointInQuadX - 1; distanceToBottomRight[1] = pointInQuadX - 1;

        //cout << distanceToTopLeft[0] <<"|" << distanceToTopLeft[1] << endl;

        double tx1 = Dot(distanceToTopLeft, topLeftGradient);
        double tx2 = Dot(distanceToTopRight, topRightGradient);
        double bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
        double bx2 = Dot(distanceToBottomRight, bottomRightGradient);

        pointInQuadX = QunticCurve(pointInQuadX);
        pointInQuadY = QunticCurve(pointInQuadY);

        double tx = Lerp(tx1, tx2, pointInQuadX);
        double bx = Lerp(bx1, bx2, pointInQuadX);
        double tb = Lerp(tx, bx, pointInQuadY);

        //cout << tx1 << endl;
        //free(distanceToTopLeft); 
        //free(distanceToTopRight);
        //free(distanceToBottomLeft);
        //free(distanceToBottomRight);
        //
        //free(topLeftGradient);
        //free(topRightGradient);
        //free(bottomLeftGradient);
        //free(bottomRightGradient);

        return tb;
    }

    double Noise(double fxx, double fyy, int oct, double size, double persistence = 0.5,double amp = 1)
    {
        double amplitude = amp;

        double max = 0;
        double result = 0;
        double fx = fxx;
        double fy = fyy;
        int octaves = oct;

        while (octaves > 0)
        {
            octaves--;
            max += amplitude;
            result += Noise1(fx, fy, size) * amplitude;
            amplitude *= persistence;
            fx *= 2;
            fy *= 2;
        }

        return (double)result / (double)max;
    }
    double MyNoise(double fxx, double fyy, int oct, double sss, double persistence = 0.5,double amp = 1)
    {
        double amplitude = amp;

        double max = 0;
        double result = 0;
        double fx = fxx;
        double fy = fyy;
        int octaves = oct;
        double size = sss;
        
        while (octaves > 0)
        {
            octaves--;
            max += amplitude;
            result += Noise1(fx, fy, size) * amplitude;
            amplitude *= persistence;
            size*=2;
            fx /= 2;
            fy /= 2;
        }

        return (double)result / (double)max;
    }
};






//class GradientNoise
//{
//    int byte[1024];
//public:
//    GradientNoise(int seed = 0)
//    {
//        srand(seed);
//        //int rand =rand();
//        //byte[1024];
//        //rand.NextBytes(permutationTable); // ��������� ���������� �������
//        for (int i = 0; i < 1024; i++)
//        {
//            byte[i]= rand();
//        }
//
//
//    }
//
//private: 
//    double* GetPseudoRandomGradientVector(int x, int y)
//    {
//        // ���-������� � �������� �������, �������� ���������� �� ������� ������� �� ���������� �������
//        int v = (int)(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & 1023);
//        v = byte[v] & 3;
//        //double temp(2);
//
//         //array<double, 2>;
//        switch (v)
//        {
//        
//        
//        
//        
//        case 0:  return new double[2] {  1, 0 };
//        case 1:  return new double[2] { -1, 0 };
//        case 2:  return new double[2] {  0, 1 };
//        default: return new double[2] {  0, -1 };
//        }
//    }
//	
//    double Lerp(double a, double b, double t)
//    {
//        // return a * (t - 1) + b * t; ����� ���������� � ����� ���������� (�������� ������, ����� � ������ ������):
//        return a + (b - a) * t;
//    }
//
//	double QunticCurve(double t)
//	{
//		return t * t * t * (t * (t * 6 - 15) + 10);
//	}
//
//	double Dot(double* a, double* b)
//	{
//		return a[0] * b[0] + a[1] * b[1];
//	}
//
//    
//
//public:
//    double Noise2(double fx, double fy)
//    {
//        // ����� ������� ���������� ����� ������� ������� ��������
//        int left = (int)floor(fx);
//        int top = (int)floor(fy);
//
//        // � ������ ��������� ���������� ����� ������ ��������
//        double pointInQuadX = fx - left;
//        double pointInQuadY = fy - top;
//
//        // ��������� ����������� ������� ��� ���� ������ ��������:
//       // double* topLeftGradient = (double*)malloc(2 * sizeof(double));
//       // double* topRightGradient = (double*)malloc(2 * sizeof(double));
//       // double* bottomLeftGradient = (double*)malloc(2 * sizeof(double));
//       // double* bottomRightGradient = (double*)malloc(2 * sizeof(double));
//        double* topLeftGradient;
//        double* topRightGradient;
//        double* bottomLeftGradient;
//        double* bottomRightGradient;
//        topLeftGradient = GetPseudoRandomGradientVector(left, top);
//        //topLeftGradient = (double*)realloc(topLeftGradient,2 * sizeof(double));
//
//        topRightGradient = GetPseudoRandomGradientVector(left + 1, top);
//        //topRightGradient = (double*)realloc(topRightGradient, 2 * sizeof(double));
//
//        bottomLeftGradient = GetPseudoRandomGradientVector(left, top + 1);
//        //bottomLeftGradient = (double*)realloc(bottomLeftGradient, 2 * sizeof(double));
//
//        bottomRightGradient = GetPseudoRandomGradientVector(left + 1, top + 1);
//        //bottomRightGradient = (double*)realloc(bottomRightGradient, 2 * sizeof(double));
//
//        // ������� �� ������ �������� �� ����� ������ ��������:
//       
//        double* distanceToTopLeft = (double*)malloc(2*sizeof(double));
//        double* distanceToTopRight = (double*)malloc(2 * sizeof(double));
//        double* distanceToBottomLeft = (double*)malloc(2 * sizeof(double));
//        double* distanceToBottomRight = (double*)malloc(2 * sizeof(double));
//
//
//        distanceToTopLeft[0] = pointInQuadX; distanceToTopLeft[1] = pointInQuadY;
//        distanceToTopRight[0] = pointInQuadX - 1; distanceToTopRight[1] = pointInQuadY;
//        distanceToTopLeft[0] = pointInQuadX; distanceToTopLeft[1] = pointInQuadY - 1;
//        distanceToTopLeft[0] = pointInQuadX - 1; distanceToTopLeft[1] = pointInQuadY - 1;
//
//  
//       
//
//        // ������� ��������� ������������ ����� �������� ����� ���������������
///*
// tx1--tx2
//  |    |
// bx1--bx2
//*/
//        double tx1 = Dot(distanceToTopLeft, topLeftGradient);
//        double tx2 = Dot(distanceToTopRight, topRightGradient);
//        double bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
//        double bx2 = Dot(distanceToBottomRight, bottomRightGradient);
//
//        // ������� ��������� ������������, ����� ��� �� ���� ��������:
//        pointInQuadX = QunticCurve(pointInQuadX);
//        pointInQuadY = QunticCurve(pointInQuadY);
//
//        // ����������, ������������:
//        double tx = Lerp(tx1, tx2, pointInQuadX);
//        double bx = Lerp(bx1, bx2, pointInQuadX);
//        double tb = Lerp(tx, bx, pointInQuadY);
//
//        // ���������� ���������:
//        return tb;
//    }
//
//    double Noise(double fx, double fy, int octaves, double persistence = 0.5f)
//    {
//        double amplitude = 1;
//        double max = 0;
//        double result = 0;
//
//        while (octaves-- > 0)
//        {
//            max += amplitude;
//            result += Noise2(fx, fy) * amplitude;
//            amplitude *= persistence;
//            fx *= 2;
//            fy *= 2;
//        }
//
//        return result / max;
//    }
//
//};