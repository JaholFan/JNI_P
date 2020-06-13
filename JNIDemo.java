
public class JNIDemo{
    /*you should load lib in Static Code Block
     *because SCB is invoke before instantiate JNIDemo object  
     */
    static {
        /*1.load native C so lib*/
        System.loadLibrary("native");
    }
    public native void java_hello(); //declaration here,which implementation is in native c source file
    public static void main(String[] args){
        /*2.map:java_hello -- c_hello*/
        /*3.invoke*/
        new JNIDemo().java_hello();
    }
}
