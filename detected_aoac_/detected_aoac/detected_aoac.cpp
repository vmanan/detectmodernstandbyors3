// detected_aoac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "winnt.h"
#include "Powerbase.h"
#include <WinDef.h>


int _tmain(int argc, _TCHAR* argv[])
{

	DWORD  status;
	SYSTEM_POWER_CAPABILITIES  systemPowerCapabilities;
	//Get the current system admin policy first

	OSVERSIONINFOEX osvi;
	BOOL  	bOsVersionInfoEx;

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi);

	if(bOsVersionInfoEx == FALSE) { 
		 printf("GetVersionEx failed\n");
		return 1;
	}

	if ( osvi.dwMajorVersion == 6 )
      {

		  if ( osvi.wProductType == VER_NT_WORKSTATION && osvi.dwMinorVersion >= 2) {
                printf("OS is Windows 8 \n");
		  }

		  else {
			  printf("OS is older than Windows 8. Minor version 0x%x\n",osvi.dwMinorVersion);
			  //return if it is not windows 8
			  //Connected standby was supported from Windows 8 onwards 
			  return 1;
		  }
	}
	else {
			  printf("OS is older than Windows 8. Major  version 0x%x\n",osvi.dwMajorVersion);
			  //return if it is not windows 8
			  //Connected standby was supported from Windows 8 onwards 
			  return 1;
	}

        status = CallNtPowerInformation(
                                       SystemPowerCapabilities, 
                                       NULL, 
                                       0, 
                                       &systemPowerCapabilities, 
                                       sizeof(systemPowerCapabilities));

        if (status != 0)
        {
            printf("CallNtPowerInformation returns error 0x%x\n", status);
			return 1;
        }


		if (systemPowerCapabilities.AoAc) {
			printf("System supports AOAC\n");
		}
		else {
			printf("System DOESNT supports AOAC\n");
		}

        return 0;
}

