#pragma onece

#define DEBUG
#if defined(DEBUG)
#define _log_(str) do {\
	cout << "[" << __FILE__ << "]" << "<" << __func__ << ">" << "(" << __LINE__ << "): " << str << endl;\
}while(0)
#else
#define _log_(str)
#endif
