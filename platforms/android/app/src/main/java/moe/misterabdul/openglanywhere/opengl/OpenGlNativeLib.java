package moe.misterabdul.openglanywhere.opengl;

public class OpenGlNativeLib {
    private long renderer;

    // Used to load the 'openglanywhere' library on application startup.
    static {
        System.loadLibrary("openglanywhere");
    }

    public OpenGlNativeLib() {
        this.renderer = initialize();
    }

    public void onSurfaceCreated() {
        onSurfaceCreated(this.renderer);
    }

    public void onSurfaceChanged(int width, int height) {
        onSurfaceChanged(this.renderer, width, height);
    }

    public void onDrawFrame() {
        onDrawFrame(this.renderer);
    }

    public void onDestroy() {
        onDestroy(this.renderer);
        deinitialize(this.renderer);
        this.renderer = 0;
    }

    /**
     * A native method that is implemented by the 'openglanywhere' native library,
     * which is packaged with this application.
     */
    private static native long initialize();

    private static native void deinitialize(long renderer);

    private static native void onSurfaceCreated(long renderer);

    private static native void onSurfaceChanged(long renderer, int width, int height);

    private static native void onDrawFrame(long renderer);

    private static native void onDestroy(long renderer);
}
