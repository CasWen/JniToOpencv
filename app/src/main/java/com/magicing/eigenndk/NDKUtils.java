package com.magicing.eigenndk;


public class NDKUtils {

   // public native String invokeCmethod();

    public static native int[] gray(int[] buf, int w, int h);
//    canny
    public static native int[] canny(int[] buf, int w, int h);

    static  {
        System.loadLibrary("OpenCV");//导入生成的链接库文件
    }

}
