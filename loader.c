#include "jaakkos.h"

void __attribute__ ((constructor)) my_load(void);
void __attribute__ ((destructor)) my_unload(void);

// fork or die
pid_t try_fork() {
	pid_t forkpid = fork();

	if(forkpid == -1) {
		perror("fork()");
		exit(1);
	}

	return forkpid;
}

// Called when the library is loaded and before dlopen() returns
void my_load(void) {
	uint32_t INJECT_STARSIGN = 0, STAROFF = 0;

	// Get ADOM version number
	char *version = getenv("ADOM_VERSION");
	int adom_version = 0;

	if (version != NULL)
	{
		sscanf(version, "%i", &adom_version);
	}

	/*
	INJECT_* is the address in memory to overwrite with the location of our function.
	 See http://www.adom.de/forums/showthread.php/1134-Choosing-star-sign?p=72882#post72882
	 for information on finding these offsets.
	*/
	if (adom_version == 111) {
		INJECT_STARSIGN = 0x813ee0a; 
	}
	else if (adom_version == 100) {
		INJECT_STARSIGN = 0x813ac6a; 
	}
	else if (adom_version == 1203) {
                INJECT_STARSIGN =  0x081387ba;
	}
	else if (adom_version == 1204) {
                INJECT_STARSIGN =  0x0813a09a;
	}
	else if (adom_version == 1205) {
                INJECT_STARSIGN =  0x0813a94a;
        }
        else if (adom_version == 1206) {
                INJECT_STARSIGN =  0x0813c05a;
        }
        else if (adom_version == 1207) {
                INJECT_STARSIGN =  0x0814068a;
        }
	else if (adom_version == 1208) {
                INJECT_STARSIGN =  0x814571a;
        }
	if (INJECT_STARSIGN == 0) {
		printf("ERROR:\nDon't know where to inject my starsign function to.\nUnknown ADOM version %i? Try the 32-bit Debian version.\n", adom_version);
		return;
	}

	STAROFF = INJECT_STARSIGN + 4;
	
	if(
			mprotect(PAGEBOUND(INJECT_STARSIGN), getpagesize(), RWX_PROT) 
	  ) {
		perror("mprotect()");
		exit(1);
	}

	// inject starsign selector
	*((void**)INJECT_STARSIGN) = &starsign_select - STAROFF;

}

void my_unload(void) {}

