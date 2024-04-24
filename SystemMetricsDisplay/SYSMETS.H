/*-------------------------------------------------------
* SYSTEM.H -- System metrics display structure
-------------------------------------------------------*/

#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics[0]))	// 3 in this case

struct {
	int		iIndex;
	TCHAR*	szLabel;
	TCHAR*	szDesc;
} sysmetrics[] = {
	SM_CXSCREEN,		TEXT("SM_CXSCREEN"),
						TEXT("Screen width in pixels"),
	SM_CYSCREEN,		TEXT("SM_CYSCREEN"),
						TEXT("Screen height in pixels"),
	SM_CXVSCROLL,		TEXT("SM_CXVSCROLL"),
						TEXT("Vertical scroll width")
};