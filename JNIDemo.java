
public class JNIDemo{
    /*you should load lib in Static Code Block
     *because SCB is invoke before instantiate JNIDemo object  
     */
    static {
        /*1.load native C so lib*/
        System.loadLibrary("native");
    }
    public native void java_hello(); //declaration here,which implementation is in native c source file
    public native int sum(int a,int b);
    public static void main(String[] args){
        /*2.map:java_hello -- c_hello*/
        /*3.invoke*/
        JNIDemo jd = new JNIDemo();
        jd.java_hello();
        System.out.println("1+2="+jd.sum(1,2));
    }
}
