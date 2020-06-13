if [ "$1" == "run" ];then
#gcc -I /usr/lib/jvm/java-1.8.0-openjdk-amd64/include -I /usr/lib/jvm/java-1.8.0-openjdk-amd64/include/linux  -fPIC -shared -o libnative.so native.c
gcc -I /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -fPIC -shared -o libnative.so native.c
javac JNIDemo.java
export LD_LIBRARY_PATH=.
java JNIDemo
else
javac JNIDemo.java
javah -jni JNIDemo
fi
