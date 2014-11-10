/************************************************************************/
/*					TCP/IP Socket Sample Program	 									*/
/************************************************************************/
/* Function		Client / Server sample program using TCP/IP socket calls.*/
/* Author		(c) Copyright Infoline AG 1995									*/
/*					Schaffhauserstrasse 121												*/
/*					CH-8302 Kloten - Switzerland										*/
/*					Phone: +41 1 803 07 06 / Fax: +41 1 881 17 55				*/
/* History		V3.00 01/Mar/1995 Andy Brunner	Initial program version	*/
/************************************************************************/

/************************************************************************/
/*					Do not forget to add the service entry in \ETC\SERVICES	*/
/*					e.g. iappecho 5000/tcp												*/
/************************************************************************/

#define	INCL_BASE
#define	USER_OS2

#include "user.h"								/* Include necessary files			*/
#include "iapp.h"								/* Include necessary files			*/

/*----------------------------------------------------------------------*/
/*	Function prototypes																	*/
/*----------------------------------------------------------------------*/

VOID	ErrorHandler(P_IAPP_SOCKET pxControl);

/*======================================================================*/
/*	Function: main																		 	*/ 
/*======================================================================*/

SHORT main(SHORT sArgCounter, PUCHAR *pszArgVariables)
{
	/*-------------------------------------------------------------------*/
	/* Automatic variables															 	*/ 
	/*-------------------------------------------------------------------*/

	P_IAPP_SOCKET		pxControl							= NULL;

	UCHAR					Buffer[100];

	PUCHAR				pszMessage							= "Test Message";

	USHORT				usCounter							= 0;
	USHORT				usBufferSize						= 0;

	/*-------------------------------------------------------------------*/
	/* Display program title															*/
	/*-------------------------------------------------------------------*/

	printf("TCP/IP Socket Sample Program Version 3.00 - (c) Copyright Infoline AG 1995\n");
	printf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
	printf("\n");

	/*-------------------------------------------------------------------*/
	/* Check program arguments															*/
	/*-------------------------------------------------------------------*/

	if ((sArgCounter == 1) || (sArgCounter > 3))
	{
		printf("Usage: TCPEcho ServiceName           (for Server)\n");
		printf("       TCPEcho ServiceName HostName  (for Client)\n");
		exit(4);
	}

	/*-------------------------------------------------------------------*/
	/* Initialize TCP/IP socket connection											*/
	/*-------------------------------------------------------------------*/

	if (sArgCounter == 2)
	{
		/*----------------------------------------------------------------*/
		/* Initialize server 												  			*/
		/*----------------------------------------------------------------*/

		printf("Server: Waiting for client to connect.\n");

		if (!IAppSocketOpen(&pxControl, NULL, pszArgVariables[1]))
			ErrorHandler(pxControl);
		
		printf("Server: Connected with client.\n");
	}
	else
	{
		/*----------------------------------------------------------------*/
		/* Initialize client 												  			*/
		/*----------------------------------------------------------------*/

		printf("Client: Waiting for server to answer.\n");

		if (!IAppSocketOpen(&pxControl, pszArgVariables[2], pszArgVariables[1]))
			ErrorHandler(pxControl);
		
		printf("Client: Connected with server.\n");
	}

	/*-------------------------------------------------------------------*/
	/* Perform data transfer															*/
	/*-------------------------------------------------------------------*/

	if (sArgCounter == 3)
	{
		/*----------------------------------------------------------------*/
		/*	Client: Send data to server and read answer							*/
		/*----------------------------------------------------------------*/

		while (++usCounter < 4)
		{
			if (!IAppSocketWrite(pxControl, pszMessage, strlen(pszMessage)))
				ErrorHandler(pxControl);
			
			printf("Client: Sent to server <%s>.\n", pszMessage);

			Buffer[0] = '\0';
			usBufferSize = 100;

			if (!IAppSocketRead(pxControl, Buffer, &usBufferSize))
				ErrorHandler(pxControl);

			Buffer[usBufferSize] = '\0';
			
			printf("Client: Received from server <%s>.\n", Buffer);
		}
	}
	else
	{
		/*----------------------------------------------------------------*/
		/*	Server: Read client data and echo back to client as uppercase	*/
		/*----------------------------------------------------------------*/

		while (TRUE)
		{
			Buffer[0] = '\0';
			usBufferSize = 100;

			if (!IAppSocketRead(pxControl, Buffer, &usBufferSize))
				ErrorHandler(pxControl);

			Buffer[usBufferSize] = '\0';

			printf("Server: Received from client <%s>.\n", Buffer);

			IAppUpperCase(Buffer);

			if (!IAppSocketWrite(pxControl, Buffer, strlen(Buffer)))
				ErrorHandler(pxControl);

			printf("Server: Sent to client <%s>.\n", Buffer);
		}
	}

	/*-------------------------------------------------------------------*/
	/* Terminate TCP/IP socket connection											*/
	/*-------------------------------------------------------------------*/

	if (!IAppSocketClose(pxControl))
		ErrorHandler(pxControl);

	/*-------------------------------------------------------------------*/
	/*	Return to the caller											 			 		*/
	/*-------------------------------------------------------------------*/

	return (0);
}

/*======================================================================*/
/*	Function: ErrorHandler															 	*/ 
/*======================================================================*/

VOID ErrorHandler(P_IAPP_SOCKET pxControl)
{
	printf("\n");
	printf("%s\n", pxControl->szErrorMessage);

	IAppBeep();

	exit(4);
}


