HMONITOR getPrimaryMonitor()
{
	const POINT ptZero = { 0, 0 };
	return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getMonitor(int x, int y) {
	const POINT point = { x, y };
	return MonitorFromPoint(point, MONITOR_DEFAULTTOPRIMARY);
}

HMONITOR getNearestMonitor(HWND hwnd) {
	return MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
}

MONITORINFO info(int x, int y) {
	/*
		DWORD cbSize;
		RECT  rcMonitor;
		RECT  rcWork;
		DWORD dwFlags;
	*/
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(getMonitor(x, y), &mi);

	return mi;
}

MONITORINFO info(HMONITOR hmonitor) {
	/*
		DWORD cbSize;
		RECT  rcMonitor;
		RECT  rcWork;
		DWORD dwFlags;
	*/
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hmonitor, &mi);
	return mi;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	/*
		DWORD cbSize;
		RECT  rcMonitor;
		RECT  rcWork;
		DWORD dwFlags;
	*/
	MONITORINFO mi;
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);

	vector<MONITORINFO>* monitors = (vector<MONITORINFO>*) dwData;
	monitors->insert(monitors->begin(), mi);

	return TRUE;
}

void listMonitors(vector<MONITORINFO>* monitors) {
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)monitors);
}

void getDesktopResolution(RWH* rwh) {
	rwh->width = GetSystemMetrics(SM_CXSCREEN);
	rwh->height = GetSystemMetrics(SM_CYSCREEN);
}

void getAllResolution(RWH* rwh) {
	rwh->width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	rwh->height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

JNIEXPORT jintArray JNICALL Java_components_dll_window_C_CHeader_allResolution(JNIEnv* env, jobject obj) {
	RWH rwh;
	getAllResolution(&rwh);

	jintArray arr = env->NewIntArray(2);
	env->SetIntArrayRegion(arr, 0, 2, (jint*) new int[2]{ rwh.width, rwh.height });

	return arr;
}

JNIEXPORT jintArray JNICALL Java_components_dll_window_C_CHeader_resolution(JNIEnv* env, jobject obj) {
	RWH rwh;
	getDesktopResolution(&rwh);

	jintArray arr = env->NewIntArray(2);
	env->SetIntArrayRegion(arr, 0, 2, (jint*) new int[2]{ rwh.width, rwh.height });

	return arr;
}

JNIEXPORT jobjectArray JNICALL Java_components_dll_window_C_CHeader_allDisplays(JNIEnv* env, jobject obj) {
	vector<MONITORINFO> monitors;
	listMonitors(&monitors);

	jclass classObject = env->FindClass("components/dll/window/C/Monitor");
	jmethodID method = env->GetMethodID(classObject, "<init>", "([I[IJ)V");

	jobjectArray ms = env->NewObjectArray(monitors.size(), classObject, 0);

	int count = 0;
	for (MONITORINFO mi : monitors) {
		jlongArray size = env->NewLongArray(4);
		env->SetLongArrayRegion(size, 0, 4, (jlong*) new LONG[4]{ mi.rcMonitor.left, mi.rcMonitor.right, mi.rcMonitor.top, mi.rcMonitor.bottom });

		jlongArray workSize = env->NewLongArray(4);
		env->SetLongArrayRegion(size, 0, 4, (jlong*) new LONG[4]{ mi.rcWork.left, mi.rcWork.right, mi.rcWork.top, mi.rcWork.bottom });

		jobject newObject = env->NewObject(classObject, method, size, workSize, (jlong*)mi.dwFlags);
		env->SetObjectArrayElement(ms, count++, newObject);
	}

	return ms;
}

JNIEXPORT jobject JNICALL Java_components_dll_window_C_CHeader_focusedDisplay(JNIEnv* env, jobject obj, jstring title) {
	char* tit = (char*)env->GetStringChars(title, NULL);
	HWND hwnd = findWindow(tit);

	if (hwnd == NULL) return NULL;

	HMONITOR hmonitor = getNearestMonitor(hwnd);
	if (hmonitor == NULL) return NULL;
	MONITORINFO mi = info(hmonitor);

	jclass classObject = env->FindClass("components/dll/window/C/Monitor");
	jmethodID method = env->GetMethodID(classObject, "<init>", "([I[IJ)V");

	jlongArray size = env->NewLongArray(4);
	env->SetLongArrayRegion(size, 0, 4, (jlong*) new LONG[4]{ mi.rcMonitor.left, mi.rcMonitor.right, mi.rcMonitor.top, mi.rcMonitor.bottom });
	jlongArray workSize = env->NewLongArray(4);
	env->SetLongArrayRegion(workSize, 0, 4, (jlong*) new LONG[4]{ mi.rcWork.left, mi.rcWork.right, mi.rcWork.top, mi.rcWork.bottom });
	return env->NewObject(classObject, method, size, workSize, (jlong*)mi.dwFlags);
}

JNIEXPORT jobject JNICALL Java_components_dll_window_C_CHeader_getDisplay(JNIEnv* env, jobject obj, jint x, jint y) {
	HMONITOR hmonitor = getMonitor((int)x, (int)y);
	if (hmonitor == NULL) return NULL;
	MONITORINFO mi = info(hmonitor);

	jclass classObject = env->FindClass("components/dll/window/C/Monitor");
	jmethodID method = env->GetMethodID(classObject, "<init>", "([I[IJ)V");

	jlongArray size = env->NewLongArray(4);
	env->SetLongArrayRegion(size, 0, 4, (jlong*) new LONG[4]{ mi.rcMonitor.left, mi.rcMonitor.right, mi.rcMonitor.top, mi.rcMonitor.bottom });
	jlongArray workSize = env->NewLongArray(4);
	env->SetLongArrayRegion(workSize, 0, 4, (jlong*) new LONG[4]{ mi.rcWork.left, mi.rcWork.right, mi.rcWork.top, mi.rcWork.bottom });
	return env->NewObject(classObject, method, size, workSize, (jlong*)mi.dwFlags);
}