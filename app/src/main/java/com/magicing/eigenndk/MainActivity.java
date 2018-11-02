package com.magicing.eigenndk;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.media.Image;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NDKUtils ndk = new NDKUtils();

        Bitmap bitmap = ((BitmapDrawable) getResources().getDrawable(
                R.mipmap.tupian)).getBitmap();
        int w = bitmap.getWidth(), h = bitmap.getHeight();
        int[] pix = new int[w * h];
        bitmap.getPixels(pix, 0, w, 0, 0, w, h);
        int [] resultPixes=ndk.gray(pix,w,h);
        Bitmap result = Bitmap.createBitmap(w,h, Bitmap.Config.RGB_565);
        result.setPixels(resultPixes, 0, w, 0, 0,w, h);

        ImageView img = (ImageView)findViewById(R.id.img2);
        img.setImageBitmap(result);




       /* bitmap.getPixels(pix, 0, w, 0, 0, w, h);
        int[] resultPixels2 = ndk.canny(pix, w, h);

        Bitmap resultBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixels2, 0, w, 0, 0, w, h);

        // 将边缘图显示出来
        ImageView view = (ImageView) findViewById(R.id.img3);
        view.setImageBitmap(resultBitmap);
*/
    }



}
