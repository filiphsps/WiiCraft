/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

#ifndef _STFDEBUG_
	#define _STFDEBUG_

	#if defined(HW_RVL)

	#ifdef __cplusplus
	extern "C" {
	#endif
	/* __cplusplus */

	//Uncomment this next line to enable DEBUG mode
	//#define USBGECKO

	s32 DebugStart (bool gecko, char *fn);
	void DebugStop (void);
	void Debug (const char *text, ...);
	void Debug_hexdump(void *d, int len);
	void gprintf (const char *format, ...);

	#ifdef __cplusplus
	}
	#endif /* __cplusplus */

	#endif /* defined(HW_RVL) */

#endif