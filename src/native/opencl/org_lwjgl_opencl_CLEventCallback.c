/*
 * Copyright LWJGL. All rights reserved.
 * License terms: http://lwjgl.org/license.php
 */
#include "common_tools.h"
#include "OpenCL.h"

static jmethodID CLEventCallbackInvoke;

static void CL_CALLBACK CLEventCallbackProc(
	cl_event event,
	cl_int event_command_exec_status,
	void *user_data
) {
	ATTACH_THREAD()

    (*env)->CallVoidMethod(env, (jobject)user_data, CLEventCallbackInvoke,
        (jlong)(intptr_t)event,
        (jint)event_command_exec_status
    );

	// Delete the global reference, will not be needed anymore
	(*env)->DeleteGlobalRef(env, (jobject)user_data);

	DETACH_THREAD()
}

CALLBACK_SETUP(org_lwjgl_opencl_CLEventCallback, CLEventCallback)