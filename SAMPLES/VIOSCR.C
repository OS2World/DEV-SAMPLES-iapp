/************************************************************************/
/*					VIO Screen Sample Program											*/
/************************************************************************/
/* Function		Display a sample panel on the screen.				 			*/
/* Author		(c) Copyright Infoline AG 1995									*/
/*					Schaffhauserstrasse 121												*/
/*					CH-8302 Kloten - Switzerland										*/
/*					Phone: +41 1 803 07 06 / Fax: +41 1 881 17 55				*/
/* History		V3.00 01/Mar/1995 Andy Brunner	Initial program version	*/
/************************************************************************/

#define	INCL_BASE
#define	USER_OS2

#include "user.h"								/* Include the necessary files	*/
#include "iapp.h"								/* Include IAPP user file			*/

/*======================================================================*/
/*	Function: main																		 	*/ 
/*======================================================================*/

SHORT main(SHORT sArgCounter, PUCHAR *pszArgVariables)
{
	/*-------------------------------------------------------------------*/
	/* Automatic variables																*/
	/*-------------------------------------------------------------------*/

	UCHAR					szWorkString[10];

	USHORT				usCounter							= 0;

	/*-------------------------------------------------------------------*/
	/* Check program arguments															*/
	/*-------------------------------------------------------------------*/

	if (sArgCounter != 1)
		IAppAbortProgram("Usage: VIOSCR");

	/*-------------------------------------------------------------------*/
	/* Disable Ctrl-Break and Ctrl-C signals										*/
	/*-------------------------------------------------------------------*/

	IAppDisableKill(TRUE);
	IAppDisableBreak(TRUE);

	/*-------------------------------------------------------------------*/
	/* Display screen panel																*/
	/*-------------------------------------------------------------------*/

	IAppScreenClear(1, 1, 25, 80, IAPP_COLOR_WHITE_ON_BLUE);

	IAppScreenWrite(1, 1, "VIO Screen Sample Program Version 3.00            (c) Copyright Infoline AG 1995", IAPP_COLOR_YELLOW_ON_BLUE);
	IAppScreenWrite(2, 1, "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴", IAPP_COLOR_WHITE_ON_BLUE);

	IAppScreenWrite(24, 1, "컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�", IAPP_COLOR_WHITE_ON_BLUE);
	IAppScreenWrite(25, 1, "Please wait ...", IAPP_COLOR_WHITE_ON_BLUE);

	IAppScreenSetCursor(25,80);

	/*-------------------------------------------------------------------*/
	/* Show counter																		*/
	/*-------------------------------------------------------------------*/

	IAppScreenWrite(10, 10, "Counter:", IAPP_COLOR_WHITE_ON_BLUE);

	for (usCounter = 0; usCounter <= 10000; usCounter++)
	{
		sprintf(szWorkString, "%hu", usCounter);
		IAppScreenWrite(10, 19, szWorkString, IAPP_COLOR_WHITE_ON_BLUE);
	}

	/*-------------------------------------------------------------------*/
	/* Wait until user press enter key												*/
	/*-------------------------------------------------------------------*/

	IAppScreenClear(25, 1, 25, 80, IAPP_COLOR_WHITE_ON_BLUE);
	IAppScreenWrite(25, 1, "Press [Enter] to terminate", IAPP_COLOR_WHITE_ON_BLUE);

	for (;;)
	{
		IAppKeyboardFlush();

		if (IAppKeyboardRead() == IAPP_KBD_ENTER)
			break;

		IAppBeep();
	}

	/*-------------------------------------------------------------------*/
	/* Return to the caller																*/
	/*-------------------------------------------------------------------*/

	IAppScreenClear(1, 1, 25, 80, IAPP_COLOR_WHITE_ON_BLUE);
	IAppScreenSetCursor(1, 1);

	return (0);
}
