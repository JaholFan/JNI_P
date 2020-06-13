
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
    public native String exchangeString(String str);
    public native int [] invertNum(int [] a);
    public static void main(String[] args){
        /*2.map:java_hello -- c_hello*/
        /*3.invoke*/
        JNIDemo jd = new JNIDemo();
        int [] a = {1,2,3};
        int [] b = null;
        jd.java_hello();
        System.out.println("1+2="+jd.sum(1,2));
        System.out.println("the String from C is: "+jd.exchangeString("Jahol Fan"));
        b = jd.invertNum(a);
        System.out.println(""+a[0]+" "+a[1]+" "+a[2]+" invert to "+b[0]+" "+b[1]+" "+b[2]);
    }
}
