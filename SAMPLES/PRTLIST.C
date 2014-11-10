/************************************************************************/
/*					Print Query Sample Program											*/
/************************************************************************/
/* Function		Display all connected printers.						 			*/
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

#define	MMF_NAME		"PrtQuery"

/*======================================================================*/
/*	Function: main																		 	*/ 
/*======================================================================*/

SHORT main(SHORT sArgCounter, PUCHAR *pszArgVariables)
{
	/*-------------------------------------------------------------------*/
	/* Automatic variables															 	*/ 
	/*-------------------------------------------------------------------*/

	IAPP_MMF				hMMFFile								= NULL;

	P_IAPP_PRINT_QUERY pxPrintQuery						= NULL;

	USHORT				usBufferSize						= 0;

	/*-------------------------------------------------------------------*/
	/* Display program title															*/
	/*-------------------------------------------------------------------*/

	printf("Print Query Sample Program Version 3.00 - (c) Copyright Infoline AG 1995\n");
	printf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
	printf("\n");

	/*-------------------------------------------------------------------*/
	/* Check program arguments															*/
	/*-------------------------------------------------------------------*/

	if (sArgCounter != 1)
	{
		printf("Usage: PrtList\n");
		exit(4);
	}

	/*-------------------------------------------------------------------*/
	/* Obtain current printer configuration										*/
	/*-------------------------------------------------------------------*/

	IAppPrintQuery(MMF_NAME);

	/*-------------------------------------------------------------------*/
	/* Open the created memory mapped file											*/
	/*-------------------------------------------------------------------*/

	hMMFFile = IAppMMFOpen(MMF_NAME, 'R');

	/*-------------------------------------------------------------------*/
	/* Display column title																*/
	/*-------------------------------------------------------------------*/

	printf("Name         Server          Device   Driver                           Def\n");
	printf("컴컴컴컴컴컴 컴컴컴컴컴컴컴� 컴컴컴컴 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 컴�\n");

	/*-------------------------------------------------------------------*/
	/* Read thru the memory mapped file and format the records				*/
	/*-------------------------------------------------------------------*/

	while (IAppMMFRead(hMMFFile, (PVOID) &pxPrintQuery, &usBufferSize))
	{
		printf("%-12.12s %-15.15s %-8.8s %-32.32s %s\n",
			pxPrintQuery->szName,
			pxPrintQuery->szServer,
			pxPrintQuery->szDevice,
			pxPrintQuery->szDriver,
			pxPrintQuery->fDefault ? "Yes" : "No");
	}

	/*-------------------------------------------------------------------*/
	/* Close the memory mapped file													*/
	/*-------------------------------------------------------------------*/

	IAppMMFClose(hMMFFile);

	/*-------------------------------------------------------------------*/
	/* Delete the memory mapped file													*/
	/*-------------------------------------------------------------------*/

	IAppMMFDelete(MMF_NAME);

	/*-------------------------------------------------------------------*/
	/*	Return to caller												 			 		*/
	/*-------------------------------------------------------------------*/

	return (0);
}
