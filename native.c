#include <jni.h> 
#include <stdio.h>

#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif

void c_hello(JNIEnv * jenv, jobject obj)
{
    printf("c hello\n");
}

int c_sum(JNIEnv * jenv, jobject obj,int a,int b)
{
    return a+b;
}

static const JNINativeMethod methods[] = {
	{"java_hello", "()V", (void *)c_hello},
	{"sum", "(II)I", (void *)c_sum},
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    /* 
     *run into here when System.loadLibrary("native");
     */
	JNIEnv *env;
	jclass cls;
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
		return JNI_ERR; /* JNI version not supported */
	}
	cls = (*env)->FindClass(env, "JNIDemo"); //** you should find your java class
	if (cls == NULL) {
		return JNI_ERR;
	}
    /*2.register map:java_hello -- c_hello*/
	if((*env)->RegisterNatives(env, cls, methods, 2) < 0)
        return JNI_ERR;
	return JNI_VERSION_1_2;
}

