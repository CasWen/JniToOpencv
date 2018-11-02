#include <jni.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C"



  JNIEXPORT jintArray JNICALL Java_com_magicing_eigenndk_NDKUtils_gray(
          JNIEnv *env, jclass obj, jintArray buf, int w, int h) {

      jint *cbuf;
      cbuf = env->GetIntArrayElements(buf, JNI_FALSE );
      if (cbuf == NULL) {
          return 0;
      }

      Mat imgData(h, w, CV_8UC4, (unsigned char *) cbuf);

      uchar* ptr = imgData.ptr(0);
      for(int i = 0; i < w*h; i ++){
          //计算公式：Y(亮度) = 0.299*R + 0.587*G + 0.114*B
          //对于一个int四字节，其彩色值存储方式为：BGRA
          int grayScale = (int)(ptr[4*i+2]*0.299 + ptr[4*i+1]*0.587 + ptr[4*i+0]*0.114);
          ptr[4*i+1] = grayScale;
          ptr[4*i+2] = grayScale;
          ptr[4*i+0] = grayScale;
      }

      int size = w * h;
      jintArray result = env->NewIntArray(size);
      env->SetIntArrayRegion(result, 0, size, cbuf);
      env->ReleaseIntArrayElements(buf, cbuf, 0);
      return result;
  }



  JNIEXPORT jintArray JNICALL Java_com_magicing_eigenndk_NDKUtils_canny(
  JNIEnv *env, jclass obj, jintArray buf, int w, int h) {

      jint *cbuf;
      cbuf = env->GetIntArrayElements(buf, false); // 读取输入参数
      if (cbuf == NULL) {
          return 0;
      }

      Mat image(h, w, CV_8UC4, (unsigned char*) cbuf); // 初始化一个矩阵（图像）4通道的图像
      cvtColor(image, image, COLOR_BGR2GRAY); // 转为灰度图
      GaussianBlur(image, image, Size(5,5), 0, 0); // 高斯滤波
      Canny(image, image, 50, 150, 3); // 边缘检测

      // LSD 直线检测
      Mat image2(image.size(), image.type()); // 用于绘制直线
      Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD, 0.80);
      vector<Vec4f> lines_std;
      ls->detect(image, lines_std);

      // LOGD("channels = %d", image.channels());
      ls->drawSegments(image2, lines_std);
      cvtColor(image2, image2, COLOR_BGR2GRAY); // 此处要转为灰度图

      // TODO 这里还可以添加其他的功能

      // 构造返回结果
      int* outImage = new int[w * h];
      int n = 0;
      for(int i = 0; i < h; i++) {
          uchar* data = image.ptr<uchar>(i);
          // uchar* data = image2.ptr<uchar>(i); // 如果是直线检测，就用image2
          for(int j = 0; j < w; j++) {
              if(data[j] == 255) {
                  outImage[n++] = 0;
              }else {
                  outImage[n++] = -1;
              }
          }
      }

      int size = w * h;
      jintArray result = env->NewIntArray(size);
      env->SetIntArrayRegion(result, 0, size, outImage);
      env->ReleaseIntArrayElements(buf, cbuf, 0);
      return result;

  }







