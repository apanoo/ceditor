package cn.apanoo.ceditor;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import static android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY;

public class MainActivity extends AppCompatActivity {

    private final int CONTEXT_CLIENT_VERSION = 2;
    private GLSurfaceView mGLSurfaceView;
    RendererJNI mRenderer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mGLSurfaceView = new GLSurfaceView(this);
        mRenderer=new RendererJNI(this);
        if (detectOpenGLES20()) {
            // set OpenGL ES version
            mGLSurfaceView.setEGLContextClientVersion(CONTEXT_CLIENT_VERSION);
            // bind OpenGL renderer(from jni) to GLSurfaceView
            mGLSurfaceView.setRenderer(mRenderer);
            // set render mode
            mGLSurfaceView.setRenderMode(RENDERMODE_WHEN_DIRTY);
        } else {
            Log.e("opengles20", "OpenGL ES 2.0 not supported on device.  Exiting...");
            finish();
        }
        // set OpenGL view fullscreen
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        // show GLSurfaceView
        setContentView(mGLSurfaceView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLSurfaceView.onPause();
    }

    // check OpenGL ES 2.0 support
    private boolean detectOpenGLES20() {
        ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();

        return (info.reqGlEsVersion >= 0x20000);
    }
}
