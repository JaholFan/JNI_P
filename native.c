#include <jni.h> 
#include <stdio.h>
#include <stdlib.h>

#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif

void c_hello(JNIEnv * env, jobject obj)
{
    printf("c hello\n");
}

int c_sum(JNIEnv * env, jobject obj,jint a,jint b)
{
    return a+b;
}

jstring c_exchangeString(JNIEnv * env, jobject obj, jstring str)
{
    const jbyte *cstr;
    cstr = (*env)->GetStringUTFChars(env, str, NULL); 
    printf("String from java is: %s\n",cstr);
    (*env)->ReleaseStringUTFChars(env, str, cstr);
    return (*env)->NewStringUTF(env, "handsome man");
}

jintArray c_invertNum(JNIEnv * env, jobject obj, jintArray arr)
{
    jint *carr;
	jint * tempArray;
	jint len = 0;
	jintArray returnArray;
    jint i = 0;
	carr = (*env)->GetIntArrayElements(env, arr, NULL);
	if (carr == NULL) {
        printf("carr is NULL\n");
		return 0; /* exception occurred */
	}
	len = (*env)->GetArrayLength(env,arr);
	tempArray = malloc(sizeof(int)*len);
	if(tempArray == NULL){
        printf("tempArray is NULL\n");
		(*env)->ReleaseIntArrayElements(env,arr,carr,0);
		return 0;
	}
	for(i=0;i<len;i++){
		tempArray[i] = carr[len-i-1];
	}
	(*env)->ReleaseIntArrayElements(env,arr,carr,0);

	returnArray = (*env)->NewIntArray(env,len);
	if( returnArray ==NULL ){
        printf("returnArray is NULL\n");
		return 0;
	}

	(*env)->SetIntArrayRegion(env,returnArray,0,len,tempArray);
	free(tempArray);
	return returnArray;
}

static const JNINativeMethod methods[] = {
	{"java_hello", "()V", (void *)c_hello},
	{"sum", "(II)I", (void *)c_sum},
	{"exchangeString", "(Ljava/lang/String;)Ljava/lang/String;", (void *)c_exchangeString},
	{"invertNum", "([I)[I", (void *)c_invertNum},
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
	if((*env)->RegisterNatives(env, cls, methods, 4) < 0)
        return JNI_ERR;
	return JNI_VERSION_1_2;
}

